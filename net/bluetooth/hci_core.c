<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated
   Copyright (C) 2011 ProFUSION Embedded Systems

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/* Bluetooth HCI core. */

#समावेश <linux/export.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/crypto.h>
#समावेश <linux/property.h>
#समावेश <linux/suspend.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "hci_request.h"
#समावेश "hci_debugfs.h"
#समावेश "smp.h"
#समावेश "leds.h"
#समावेश "msft.h"
#समावेश "aosp.h"

अटल व्योम hci_rx_work(काष्ठा work_काष्ठा *work);
अटल व्योम hci_cmd_work(काष्ठा work_काष्ठा *work);
अटल व्योम hci_tx_work(काष्ठा work_काष्ठा *work);

/* HCI device list */
LIST_HEAD(hci_dev_list);
DEFINE_RWLOCK(hci_dev_list_lock);

/* HCI callback list */
LIST_HEAD(hci_cb_list);
DEFINE_MUTEX(hci_cb_list_lock);

/* HCI ID Numbering */
अटल DEFINE_IDA(hci_index_ida);

/* ---- HCI debugfs entries ---- */

अटल sमाप_प्रकार dut_mode_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_DUT_MODE) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार dut_mode_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	काष्ठा sk_buff *skb;
	bool enable;
	पूर्णांक err;

	अगर (!test_bit(HCI_UP, &hdev->flags))
		वापस -ENETDOWN;

	err = kstrtobool_from_user(user_buf, count, &enable);
	अगर (err)
		वापस err;

	अगर (enable == hci_dev_test_flag(hdev, HCI_DUT_MODE))
		वापस -EALREADY;

	hci_req_sync_lock(hdev);
	अगर (enable)
		skb = __hci_cmd_sync(hdev, HCI_OP_ENABLE_DUT_MODE, 0, शून्य,
				     HCI_CMD_TIMEOUT);
	अन्यथा
		skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य,
				     HCI_CMD_TIMEOUT);
	hci_req_sync_unlock(hdev);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);

	hci_dev_change_flag(hdev, HCI_DUT_MODE);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dut_mode_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= dut_mode_पढ़ो,
	.ग_लिखो		= dut_mode_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार venकरोr_diag_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_VENDOR_DIAG) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार venकरोr_diag_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	bool enable;
	पूर्णांक err;

	err = kstrtobool_from_user(user_buf, count, &enable);
	अगर (err)
		वापस err;

	/* When the diagnostic flags are not persistent and the transport
	 * is not active or in user channel operation, then there is no need
	 * क्रम the venकरोr callback. Instead just store the desired value and
	 * the setting will be programmed when the controller माला_लो घातered on.
	 */
	अगर (test_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks) &&
	    (!test_bit(HCI_RUNNING, &hdev->flags) ||
	     hci_dev_test_flag(hdev, HCI_USER_CHANNEL)))
		जाओ करोne;

	hci_req_sync_lock(hdev);
	err = hdev->set_diag(hdev, enable);
	hci_req_sync_unlock(hdev);

	अगर (err < 0)
		वापस err;

करोne:
	अगर (enable)
		hci_dev_set_flag(hdev, HCI_VENDOR_DIAG);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_VENDOR_DIAG);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations venकरोr_diag_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= venकरोr_diag_पढ़ो,
	.ग_लिखो		= venकरोr_diag_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल व्योम hci_debugfs_create_basic(काष्ठा hci_dev *hdev)
अणु
	debugfs_create_file("dut_mode", 0644, hdev->debugfs, hdev,
			    &dut_mode_fops);

	अगर (hdev->set_diag)
		debugfs_create_file("vendor_diag", 0644, hdev->debugfs, hdev,
				    &venकरोr_diag_fops);
पूर्ण

अटल पूर्णांक hci_reset_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	BT_DBG("%s %ld", req->hdev->name, opt);

	/* Reset device */
	set_bit(HCI_RESET, &req->hdev->flags);
	hci_req_add(req, HCI_OP_RESET, 0, शून्य);
	वापस 0;
पूर्ण

अटल व्योम bredr_init(काष्ठा hci_request *req)
अणु
	req->hdev->flow_ctl_mode = HCI_FLOW_CTL_MODE_PACKET_BASED;

	/* Read Local Supported Features */
	hci_req_add(req, HCI_OP_READ_LOCAL_FEATURES, 0, शून्य);

	/* Read Local Version */
	hci_req_add(req, HCI_OP_READ_LOCAL_VERSION, 0, शून्य);

	/* Read BD Address */
	hci_req_add(req, HCI_OP_READ_BD_ADDR, 0, शून्य);
पूर्ण

अटल व्योम amp_init1(काष्ठा hci_request *req)
अणु
	req->hdev->flow_ctl_mode = HCI_FLOW_CTL_MODE_BLOCK_BASED;

	/* Read Local Version */
	hci_req_add(req, HCI_OP_READ_LOCAL_VERSION, 0, शून्य);

	/* Read Local Supported Commands */
	hci_req_add(req, HCI_OP_READ_LOCAL_COMMANDS, 0, शून्य);

	/* Read Local AMP Info */
	hci_req_add(req, HCI_OP_READ_LOCAL_AMP_INFO, 0, शून्य);

	/* Read Data Blk size */
	hci_req_add(req, HCI_OP_READ_DATA_BLOCK_SIZE, 0, शून्य);

	/* Read Flow Control Mode */
	hci_req_add(req, HCI_OP_READ_FLOW_CONTROL_MODE, 0, शून्य);

	/* Read Location Data */
	hci_req_add(req, HCI_OP_READ_LOCATION_DATA, 0, शून्य);
पूर्ण

अटल पूर्णांक amp_init2(काष्ठा hci_request *req)
अणु
	/* Read Local Supported Features. Not all AMP controllers
	 * support this so it's placed conditionally in the second
	 * stage init.
	 */
	अगर (req->hdev->commands[14] & 0x20)
		hci_req_add(req, HCI_OP_READ_LOCAL_FEATURES, 0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_init1_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	BT_DBG("%s %ld", hdev->name, opt);

	/* Reset */
	अगर (!test_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks))
		hci_reset_req(req, 0);

	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		bredr_init(req);
		अवरोध;
	हाल HCI_AMP:
		amp_init1(req);
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unknown device type %d", hdev->dev_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bredr_setup(काष्ठा hci_request *req)
अणु
	__le16 param;
	__u8 flt_type;

	/* Read Buffer Size (ACL mtu, max pkt, etc.) */
	hci_req_add(req, HCI_OP_READ_BUFFER_SIZE, 0, शून्य);

	/* Read Class of Device */
	hci_req_add(req, HCI_OP_READ_CLASS_OF_DEV, 0, शून्य);

	/* Read Local Name */
	hci_req_add(req, HCI_OP_READ_LOCAL_NAME, 0, शून्य);

	/* Read Voice Setting */
	hci_req_add(req, HCI_OP_READ_VOICE_SETTING, 0, शून्य);

	/* Read Number of Supported IAC */
	hci_req_add(req, HCI_OP_READ_NUM_SUPPORTED_IAC, 0, शून्य);

	/* Read Current IAC LAP */
	hci_req_add(req, HCI_OP_READ_CURRENT_IAC_LAP, 0, शून्य);

	/* Clear Event Filters */
	flt_type = HCI_FLT_CLEAR_ALL;
	hci_req_add(req, HCI_OP_SET_EVENT_FLT, 1, &flt_type);

	/* Connection accept समयout ~20 secs */
	param = cpu_to_le16(0x7d00);
	hci_req_add(req, HCI_OP_WRITE_CA_TIMEOUT, 2, &param);
पूर्ण

अटल व्योम le_setup(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* Read LE Buffer Size */
	hci_req_add(req, HCI_OP_LE_READ_BUFFER_SIZE, 0, शून्य);

	/* Read LE Local Supported Features */
	hci_req_add(req, HCI_OP_LE_READ_LOCAL_FEATURES, 0, शून्य);

	/* Read LE Supported States */
	hci_req_add(req, HCI_OP_LE_READ_SUPPORTED_STATES, 0, शून्य);

	/* LE-only controllers have LE implicitly enabled */
	अगर (!lmp_bredr_capable(hdev))
		hci_dev_set_flag(hdev, HCI_LE_ENABLED);
पूर्ण

अटल व्योम hci_setup_event_mask(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* The second byte is 0xff instead of 0x9f (two reserved bits
	 * disabled) since a Broadcom 1.2 करोngle करोesn't respond to the
	 * command otherwise.
	 */
	u8 events[8] = अणु 0xff, 0xff, 0xfb, 0xff, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	/* CSR 1.1 करोngles करोes not accept any bitfield so करोn't try to set
	 * any event mask क्रम pre 1.2 devices.
	 */
	अगर (hdev->hci_ver < BLUETOOTH_VER_1_2)
		वापस;

	अगर (lmp_bredr_capable(hdev)) अणु
		events[4] |= 0x01; /* Flow Specअगरication Complete */
	पूर्ण अन्यथा अणु
		/* Use a dअगरferent शेष क्रम LE-only devices */
		स_रखो(events, 0, माप(events));
		events[1] |= 0x20; /* Command Complete */
		events[1] |= 0x40; /* Command Status */
		events[1] |= 0x80; /* Hardware Error */

		/* If the controller supports the Disconnect command, enable
		 * the corresponding event. In addition enable packet flow
		 * control related events.
		 */
		अगर (hdev->commands[0] & 0x20) अणु
			events[0] |= 0x10; /* Disconnection Complete */
			events[2] |= 0x04; /* Number of Completed Packets */
			events[3] |= 0x02; /* Data Buffer Overflow */
		पूर्ण

		/* If the controller supports the Read Remote Version
		 * Inक्रमmation command, enable the corresponding event.
		 */
		अगर (hdev->commands[2] & 0x80)
			events[1] |= 0x08; /* Read Remote Version Inक्रमmation
					    * Complete
					    */

		अगर (hdev->le_features[0] & HCI_LE_ENCRYPTION) अणु
			events[0] |= 0x80; /* Encryption Change */
			events[5] |= 0x80; /* Encryption Key Refresh Complete */
		पूर्ण
	पूर्ण

	अगर (lmp_inq_rssi_capable(hdev) ||
	    test_bit(HCI_QUIRK_FIXUP_INQUIRY_MODE, &hdev->quirks))
		events[4] |= 0x02; /* Inquiry Result with RSSI */

	अगर (lmp_ext_feat_capable(hdev))
		events[4] |= 0x04; /* Read Remote Extended Features Complete */

	अगर (lmp_esco_capable(hdev)) अणु
		events[5] |= 0x08; /* Synchronous Connection Complete */
		events[5] |= 0x10; /* Synchronous Connection Changed */
	पूर्ण

	अगर (lmp_snअगरfsubr_capable(hdev))
		events[5] |= 0x20; /* Snअगरf Subrating */

	अगर (lmp_छोड़ो_enc_capable(hdev))
		events[5] |= 0x80; /* Encryption Key Refresh Complete */

	अगर (lmp_ext_inq_capable(hdev))
		events[5] |= 0x40; /* Extended Inquiry Result */

	अगर (lmp_no_flush_capable(hdev))
		events[7] |= 0x01; /* Enhanced Flush Complete */

	अगर (lmp_lsto_capable(hdev))
		events[6] |= 0x80; /* Link Supervision Timeout Changed */

	अगर (lmp_ssp_capable(hdev)) अणु
		events[6] |= 0x01;	/* IO Capability Request */
		events[6] |= 0x02;	/* IO Capability Response */
		events[6] |= 0x04;	/* User Confirmation Request */
		events[6] |= 0x08;	/* User Passkey Request */
		events[6] |= 0x10;	/* Remote OOB Data Request */
		events[6] |= 0x20;	/* Simple Pairing Complete */
		events[7] |= 0x04;	/* User Passkey Notअगरication */
		events[7] |= 0x08;	/* Keypress Notअगरication */
		events[7] |= 0x10;	/* Remote Host Supported
					 * Features Notअगरication
					 */
	पूर्ण

	अगर (lmp_le_capable(hdev))
		events[7] |= 0x20;	/* LE Meta-Event */

	hci_req_add(req, HCI_OP_SET_EVENT_MASK, माप(events), events);
पूर्ण

अटल पूर्णांक hci_init2_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	अगर (hdev->dev_type == HCI_AMP)
		वापस amp_init2(req);

	अगर (lmp_bredr_capable(hdev))
		bredr_setup(req);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_BREDR_ENABLED);

	अगर (lmp_le_capable(hdev))
		le_setup(req);

	/* All Bluetooth 1.2 and later controllers should support the
	 * HCI command क्रम पढ़ोing the local supported commands.
	 *
	 * Unक्रमtunately some controllers indicate Bluetooth 1.2 support,
	 * but करो not have support क्रम this command. If that is the हाल,
	 * the driver can quirk the behavior and skip पढ़ोing the local
	 * supported commands.
	 */
	अगर (hdev->hci_ver > BLUETOOTH_VER_1_1 &&
	    !test_bit(HCI_QUIRK_BROKEN_LOCAL_COMMANDS, &hdev->quirks))
		hci_req_add(req, HCI_OP_READ_LOCAL_COMMANDS, 0, शून्य);

	अगर (lmp_ssp_capable(hdev)) अणु
		/* When SSP is available, then the host features page
		 * should also be available as well. However some
		 * controllers list the max_page as 0 as दीर्घ as SSP
		 * has not been enabled. To achieve proper debugging
		 * output, क्रमce the minimum max_page to 1 at least.
		 */
		hdev->max_page = 0x01;

		अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
			u8 mode = 0x01;

			hci_req_add(req, HCI_OP_WRITE_SSP_MODE,
				    माप(mode), &mode);
		पूर्ण अन्यथा अणु
			काष्ठा hci_cp_ग_लिखो_eir cp;

			स_रखो(hdev->eir, 0, माप(hdev->eir));
			स_रखो(&cp, 0, माप(cp));

			hci_req_add(req, HCI_OP_WRITE_EIR, माप(cp), &cp);
		पूर्ण
	पूर्ण

	अगर (lmp_inq_rssi_capable(hdev) ||
	    test_bit(HCI_QUIRK_FIXUP_INQUIRY_MODE, &hdev->quirks)) अणु
		u8 mode;

		/* If Extended Inquiry Result events are supported, then
		 * they are clearly preferred over Inquiry Result with RSSI
		 * events.
		 */
		mode = lmp_ext_inq_capable(hdev) ? 0x02 : 0x01;

		hci_req_add(req, HCI_OP_WRITE_INQUIRY_MODE, 1, &mode);
	पूर्ण

	अगर (lmp_inq_tx_pwr_capable(hdev))
		hci_req_add(req, HCI_OP_READ_INQ_RSP_TX_POWER, 0, शून्य);

	अगर (lmp_ext_feat_capable(hdev)) अणु
		काष्ठा hci_cp_पढ़ो_local_ext_features cp;

		cp.page = 0x01;
		hci_req_add(req, HCI_OP_READ_LOCAL_EXT_FEATURES,
			    माप(cp), &cp);
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_LINK_SECURITY)) अणु
		u8 enable = 1;
		hci_req_add(req, HCI_OP_WRITE_AUTH_ENABLE, माप(enable),
			    &enable);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hci_setup_link_policy(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_def_link_policy cp;
	u16 link_policy = 0;

	अगर (lmp_rचयन_capable(hdev))
		link_policy |= HCI_LP_RSWITCH;
	अगर (lmp_hold_capable(hdev))
		link_policy |= HCI_LP_HOLD;
	अगर (lmp_snअगरf_capable(hdev))
		link_policy |= HCI_LP_SNIFF;
	अगर (lmp_park_capable(hdev))
		link_policy |= HCI_LP_PARK;

	cp.policy = cpu_to_le16(link_policy);
	hci_req_add(req, HCI_OP_WRITE_DEF_LINK_POLICY, माप(cp), &cp);
पूर्ण

अटल व्योम hci_set_le_support(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_le_host_supported cp;

	/* LE-only devices करो not support explicit enablement */
	अगर (!lmp_bredr_capable(hdev))
		वापस;

	स_रखो(&cp, 0, माप(cp));

	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
		cp.le = 0x01;
		cp.simul = 0x00;
	पूर्ण

	अगर (cp.le != lmp_host_le_capable(hdev))
		hci_req_add(req, HCI_OP_WRITE_LE_HOST_SUPPORTED, माप(cp),
			    &cp);
पूर्ण

अटल व्योम hci_set_event_mask_page_2(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 events[8] = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	bool changed = false;

	/* If Connectionless Slave Broadcast master role is supported
	 * enable all necessary events क्रम it.
	 */
	अगर (lmp_csb_master_capable(hdev)) अणु
		events[1] |= 0x40;	/* Triggered Clock Capture */
		events[1] |= 0x80;	/* Synchronization Train Complete */
		events[2] |= 0x10;	/* Slave Page Response Timeout */
		events[2] |= 0x20;	/* CSB Channel Map Change */
		changed = true;
	पूर्ण

	/* If Connectionless Slave Broadcast slave role is supported
	 * enable all necessary events क्रम it.
	 */
	अगर (lmp_csb_slave_capable(hdev)) अणु
		events[2] |= 0x01;	/* Synchronization Train Received */
		events[2] |= 0x02;	/* CSB Receive */
		events[2] |= 0x04;	/* CSB Timeout */
		events[2] |= 0x08;	/* Truncated Page Complete */
		changed = true;
	पूर्ण

	/* Enable Authenticated Payload Timeout Expired event अगर supported */
	अगर (lmp_ping_capable(hdev) || hdev->le_features[0] & HCI_LE_PING) अणु
		events[2] |= 0x80;
		changed = true;
	पूर्ण

	/* Some Broadcom based controllers indicate support क्रम Set Event
	 * Mask Page 2 command, but then actually करो not support it. Since
	 * the शेष value is all bits set to zero, the command is only
	 * required अगर the event mask has to be changed. In हाल no change
	 * to the event mask is needed, skip this command.
	 */
	अगर (changed)
		hci_req_add(req, HCI_OP_SET_EVENT_MASK_PAGE_2,
			    माप(events), events);
पूर्ण

अटल पूर्णांक hci_init3_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 p;

	hci_setup_event_mask(req);

	अगर (hdev->commands[6] & 0x20 &&
	    !test_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks)) अणु
		काष्ठा hci_cp_पढ़ो_stored_link_key cp;

		bacpy(&cp.bdaddr, BDADDR_ANY);
		cp.पढ़ो_all = 0x01;
		hci_req_add(req, HCI_OP_READ_STORED_LINK_KEY, माप(cp), &cp);
	पूर्ण

	अगर (hdev->commands[5] & 0x10)
		hci_setup_link_policy(req);

	अगर (hdev->commands[8] & 0x01)
		hci_req_add(req, HCI_OP_READ_PAGE_SCAN_ACTIVITY, 0, शून्य);

	अगर (hdev->commands[18] & 0x04 &&
	    !test_bit(HCI_QUIRK_BROKEN_ERR_DATA_REPORTING, &hdev->quirks))
		hci_req_add(req, HCI_OP_READ_DEF_ERR_DATA_REPORTING, 0, शून्य);

	/* Some older Broadcom based Bluetooth 1.2 controllers करो not
	 * support the Read Page Scan Type command. Check support क्रम
	 * this command in the bit mask of supported commands.
	 */
	अगर (hdev->commands[13] & 0x01)
		hci_req_add(req, HCI_OP_READ_PAGE_SCAN_TYPE, 0, शून्य);

	अगर (lmp_le_capable(hdev)) अणु
		u8 events[8];

		स_रखो(events, 0, माप(events));

		अगर (hdev->le_features[0] & HCI_LE_ENCRYPTION)
			events[0] |= 0x10;	/* LE Long Term Key Request */

		/* If controller supports the Connection Parameters Request
		 * Link Layer Procedure, enable the corresponding event.
		 */
		अगर (hdev->le_features[0] & HCI_LE_CONN_PARAM_REQ_PROC)
			events[0] |= 0x20;	/* LE Remote Connection
						 * Parameter Request
						 */

		/* If the controller supports the Data Length Extension
		 * feature, enable the corresponding event.
		 */
		अगर (hdev->le_features[0] & HCI_LE_DATA_LEN_EXT)
			events[0] |= 0x40;	/* LE Data Length Change */

		/* If the controller supports LL Privacy feature, enable
		 * the corresponding event.
		 */
		अगर (hdev->le_features[0] & HCI_LE_LL_PRIVACY)
			events[1] |= 0x02;	/* LE Enhanced Connection
						 * Complete
						 */

		/* If the controller supports Extended Scanner Filter
		 * Policies, enable the correspondig event.
		 */
		अगर (hdev->le_features[0] & HCI_LE_EXT_SCAN_POLICY)
			events[1] |= 0x04;	/* LE Direct Advertising
						 * Report
						 */

		/* If the controller supports Channel Selection Algorithm #2
		 * feature, enable the corresponding event.
		 */
		अगर (hdev->le_features[1] & HCI_LE_CHAN_SEL_ALG2)
			events[2] |= 0x08;	/* LE Channel Selection
						 * Algorithm
						 */

		/* If the controller supports the LE Set Scan Enable command,
		 * enable the corresponding advertising report event.
		 */
		अगर (hdev->commands[26] & 0x08)
			events[0] |= 0x02;	/* LE Advertising Report */

		/* If the controller supports the LE Create Connection
		 * command, enable the corresponding event.
		 */
		अगर (hdev->commands[26] & 0x10)
			events[0] |= 0x01;	/* LE Connection Complete */

		/* If the controller supports the LE Connection Update
		 * command, enable the corresponding event.
		 */
		अगर (hdev->commands[27] & 0x04)
			events[0] |= 0x04;	/* LE Connection Update
						 * Complete
						 */

		/* If the controller supports the LE Read Remote Used Features
		 * command, enable the corresponding event.
		 */
		अगर (hdev->commands[27] & 0x20)
			events[0] |= 0x08;	/* LE Read Remote Used
						 * Features Complete
						 */

		/* If the controller supports the LE Read Local P-256
		 * Public Key command, enable the corresponding event.
		 */
		अगर (hdev->commands[34] & 0x02)
			events[0] |= 0x80;	/* LE Read Local P-256
						 * Public Key Complete
						 */

		/* If the controller supports the LE Generate DHKey
		 * command, enable the corresponding event.
		 */
		अगर (hdev->commands[34] & 0x04)
			events[1] |= 0x01;	/* LE Generate DHKey Complete */

		/* If the controller supports the LE Set Default PHY or
		 * LE Set PHY commands, enable the corresponding event.
		 */
		अगर (hdev->commands[35] & (0x20 | 0x40))
			events[1] |= 0x08;        /* LE PHY Update Complete */

		/* If the controller supports LE Set Extended Scan Parameters
		 * and LE Set Extended Scan Enable commands, enable the
		 * corresponding event.
		 */
		अगर (use_ext_scan(hdev))
			events[1] |= 0x10;	/* LE Extended Advertising
						 * Report
						 */

		/* If the controller supports the LE Extended Advertising
		 * command, enable the corresponding event.
		 */
		अगर (ext_adv_capable(hdev))
			events[2] |= 0x02;	/* LE Advertising Set
						 * Terminated
						 */

		hci_req_add(req, HCI_OP_LE_SET_EVENT_MASK, माप(events),
			    events);

		/* Read LE Advertising Channel TX Power */
		अगर ((hdev->commands[25] & 0x40) && !ext_adv_capable(hdev)) अणु
			/* HCI TS spec क्रमbids mixing of legacy and extended
			 * advertising commands wherein READ_ADV_TX_POWER is
			 * also included. So करो not call it अगर extended adv
			 * is supported otherwise controller will वापस
			 * COMMAND_DISALLOWED क्रम extended commands.
			 */
			hci_req_add(req, HCI_OP_LE_READ_ADV_TX_POWER, 0, शून्य);
		पूर्ण

		अगर (hdev->commands[38] & 0x80) अणु
			/* Read LE Min/Max Tx Power*/
			hci_req_add(req, HCI_OP_LE_READ_TRANSMIT_POWER,
				    0, शून्य);
		पूर्ण

		अगर (hdev->commands[26] & 0x40) अणु
			/* Read LE White List Size */
			hci_req_add(req, HCI_OP_LE_READ_WHITE_LIST_SIZE,
				    0, शून्य);
		पूर्ण

		अगर (hdev->commands[26] & 0x80) अणु
			/* Clear LE White List */
			hci_req_add(req, HCI_OP_LE_CLEAR_WHITE_LIST, 0, शून्य);
		पूर्ण

		अगर (hdev->commands[34] & 0x40) अणु
			/* Read LE Resolving List Size */
			hci_req_add(req, HCI_OP_LE_READ_RESOLV_LIST_SIZE,
				    0, शून्य);
		पूर्ण

		अगर (hdev->commands[34] & 0x20) अणु
			/* Clear LE Resolving List */
			hci_req_add(req, HCI_OP_LE_CLEAR_RESOLV_LIST, 0, शून्य);
		पूर्ण

		अगर (hdev->commands[35] & 0x04) अणु
			__le16 rpa_समयout = cpu_to_le16(hdev->rpa_समयout);

			/* Set RPA समयout */
			hci_req_add(req, HCI_OP_LE_SET_RPA_TIMEOUT, 2,
				    &rpa_समयout);
		पूर्ण

		अगर (hdev->le_features[0] & HCI_LE_DATA_LEN_EXT) अणु
			/* Read LE Maximum Data Length */
			hci_req_add(req, HCI_OP_LE_READ_MAX_DATA_LEN, 0, शून्य);

			/* Read LE Suggested Default Data Length */
			hci_req_add(req, HCI_OP_LE_READ_DEF_DATA_LEN, 0, शून्य);
		पूर्ण

		अगर (ext_adv_capable(hdev)) अणु
			/* Read LE Number of Supported Advertising Sets */
			hci_req_add(req, HCI_OP_LE_READ_NUM_SUPPORTED_ADV_SETS,
				    0, शून्य);
		पूर्ण

		hci_set_le_support(req);
	पूर्ण

	/* Read features beyond page 1 अगर available */
	क्रम (p = 2; p < HCI_MAX_PAGES && p <= hdev->max_page; p++) अणु
		काष्ठा hci_cp_पढ़ो_local_ext_features cp;

		cp.page = p;
		hci_req_add(req, HCI_OP_READ_LOCAL_EXT_FEATURES,
			    माप(cp), &cp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hci_init4_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* Some Broadcom based Bluetooth controllers करो not support the
	 * Delete Stored Link Key command. They are clearly indicating its
	 * असलence in the bit mask of supported commands.
	 *
	 * Check the supported commands and only अगर the command is marked
	 * as supported send it. If not supported assume that the controller
	 * करोes not have actual support क्रम stored link keys which makes this
	 * command redundant anyway.
	 *
	 * Some controllers indicate that they support handling deleting
	 * stored link keys, but they करोn't. The quirk lets a driver
	 * just disable this command.
	 */
	अगर (hdev->commands[6] & 0x80 &&
	    !test_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks)) अणु
		काष्ठा hci_cp_delete_stored_link_key cp;

		bacpy(&cp.bdaddr, BDADDR_ANY);
		cp.delete_all = 0x01;
		hci_req_add(req, HCI_OP_DELETE_STORED_LINK_KEY,
			    माप(cp), &cp);
	पूर्ण

	/* Set event mask page 2 अगर the HCI command क्रम it is supported */
	अगर (hdev->commands[22] & 0x04)
		hci_set_event_mask_page_2(req);

	/* Read local codec list अगर the HCI command is supported */
	अगर (hdev->commands[29] & 0x20)
		hci_req_add(req, HCI_OP_READ_LOCAL_CODECS, 0, शून्य);

	/* Read local pairing options अगर the HCI command is supported */
	अगर (hdev->commands[41] & 0x08)
		hci_req_add(req, HCI_OP_READ_LOCAL_PAIRING_OPTS, 0, शून्य);

	/* Get MWS transport configuration अगर the HCI command is supported */
	अगर (hdev->commands[30] & 0x08)
		hci_req_add(req, HCI_OP_GET_MWS_TRANSPORT_CONFIG, 0, शून्य);

	/* Check क्रम Synchronization Train support */
	अगर (lmp_sync_train_capable(hdev))
		hci_req_add(req, HCI_OP_READ_SYNC_TRAIN_PARAMS, 0, शून्य);

	/* Enable Secure Connections अगर supported and configured */
	अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED) &&
	    bredr_sc_enabled(hdev)) अणु
		u8 support = 0x01;

		hci_req_add(req, HCI_OP_WRITE_SC_SUPPORT,
			    माप(support), &support);
	पूर्ण

	/* Set erroneous data reporting अगर supported to the wideband speech
	 * setting value
	 */
	अगर (hdev->commands[18] & 0x08 &&
	    !test_bit(HCI_QUIRK_BROKEN_ERR_DATA_REPORTING, &hdev->quirks)) अणु
		bool enabled = hci_dev_test_flag(hdev,
						 HCI_WIDEBAND_SPEECH_ENABLED);

		अगर (enabled !=
		    (hdev->err_data_reporting == ERR_DATA_REPORTING_ENABLED)) अणु
			काष्ठा hci_cp_ग_लिखो_def_err_data_reporting cp;

			cp.err_data_reporting = enabled ?
						ERR_DATA_REPORTING_ENABLED :
						ERR_DATA_REPORTING_DISABLED;

			hci_req_add(req, HCI_OP_WRITE_DEF_ERR_DATA_REPORTING,
				    माप(cp), &cp);
		पूर्ण
	पूर्ण

	/* Set Suggested Default Data Length to maximum अगर supported */
	अगर (hdev->le_features[0] & HCI_LE_DATA_LEN_EXT) अणु
		काष्ठा hci_cp_le_ग_लिखो_def_data_len cp;

		cp.tx_len = cpu_to_le16(hdev->le_max_tx_len);
		cp.tx_समय = cpu_to_le16(hdev->le_max_tx_समय);
		hci_req_add(req, HCI_OP_LE_WRITE_DEF_DATA_LEN, माप(cp), &cp);
	पूर्ण

	/* Set Default PHY parameters अगर command is supported */
	अगर (hdev->commands[35] & 0x20) अणु
		काष्ठा hci_cp_le_set_शेष_phy cp;

		cp.all_phys = 0x00;
		cp.tx_phys = hdev->le_tx_def_phys;
		cp.rx_phys = hdev->le_rx_def_phys;

		hci_req_add(req, HCI_OP_LE_SET_DEFAULT_PHY, माप(cp), &cp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __hci_init(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक err;

	err = __hci_req_sync(hdev, hci_init1_req, 0, HCI_INIT_TIMEOUT, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP))
		hci_debugfs_create_basic(hdev);

	err = __hci_req_sync(hdev, hci_init2_req, 0, HCI_INIT_TIMEOUT, शून्य);
	अगर (err < 0)
		वापस err;

	/* HCI_PRIMARY covers both single-mode LE, BR/EDR and dual-mode
	 * BR/EDR/LE type controllers. AMP controllers only need the
	 * first two stages of init.
	 */
	अगर (hdev->dev_type != HCI_PRIMARY)
		वापस 0;

	err = __hci_req_sync(hdev, hci_init3_req, 0, HCI_INIT_TIMEOUT, शून्य);
	अगर (err < 0)
		वापस err;

	err = __hci_req_sync(hdev, hci_init4_req, 0, HCI_INIT_TIMEOUT, शून्य);
	अगर (err < 0)
		वापस err;

	/* This function is only called when the controller is actually in
	 * configured state. When the controller is marked as unconfigured,
	 * this initialization procedure is not run.
	 *
	 * It means that it is possible that a controller runs through its
	 * setup phase and then discovers missing settings. If that is the
	 * हाल, then this function will not be called. It then will only
	 * be called during the config phase.
	 *
	 * So only when in setup phase or config phase, create the debugfs
	 * entries and रेजिस्टर the SMP channels.
	 */
	अगर (!hci_dev_test_flag(hdev, HCI_SETUP) &&
	    !hci_dev_test_flag(hdev, HCI_CONFIG))
		वापस 0;

	hci_debugfs_create_common(hdev);

	अगर (lmp_bredr_capable(hdev))
		hci_debugfs_create_bredr(hdev);

	अगर (lmp_le_capable(hdev))
		hci_debugfs_create_le(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_init0_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	BT_DBG("%s %ld", hdev->name, opt);

	/* Reset */
	अगर (!test_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks))
		hci_reset_req(req, 0);

	/* Read Local Version */
	hci_req_add(req, HCI_OP_READ_LOCAL_VERSION, 0, शून्य);

	/* Read BD Address */
	अगर (hdev->set_bdaddr)
		hci_req_add(req, HCI_OP_READ_BD_ADDR, 0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __hci_unconf_init(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक err;

	अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		वापस 0;

	err = __hci_req_sync(hdev, hci_init0_req, 0, HCI_INIT_TIMEOUT, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP))
		hci_debugfs_create_basic(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_scan_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	__u8 scan = opt;

	BT_DBG("%s %x", req->hdev->name, scan);

	/* Inquiry and Page scans */
	hci_req_add(req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_auth_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	__u8 auth = opt;

	BT_DBG("%s %x", req->hdev->name, auth);

	/* Authentication */
	hci_req_add(req, HCI_OP_WRITE_AUTH_ENABLE, 1, &auth);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_encrypt_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	__u8 encrypt = opt;

	BT_DBG("%s %x", req->hdev->name, encrypt);

	/* Encryption */
	hci_req_add(req, HCI_OP_WRITE_ENCRYPT_MODE, 1, &encrypt);
	वापस 0;
पूर्ण

अटल पूर्णांक hci_linkpol_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	__le16 policy = cpu_to_le16(opt);

	BT_DBG("%s %x", req->hdev->name, policy);

	/* Default link policy */
	hci_req_add(req, HCI_OP_WRITE_DEF_LINK_POLICY, 2, &policy);
	वापस 0;
पूर्ण

/* Get HCI device by index.
 * Device is held on वापस. */
काष्ठा hci_dev *hci_dev_get(पूर्णांक index)
अणु
	काष्ठा hci_dev *hdev = शून्य, *d;

	BT_DBG("%d", index);

	अगर (index < 0)
		वापस शून्य;

	पढ़ो_lock(&hci_dev_list_lock);
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (d->id == index) अणु
			hdev = hci_dev_hold(d);
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&hci_dev_list_lock);
	वापस hdev;
पूर्ण

/* ---- Inquiry support ---- */

bool hci_discovery_active(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *discov = &hdev->discovery;

	चयन (discov->state) अणु
	हाल DISCOVERY_FINDING:
	हाल DISCOVERY_RESOLVING:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम hci_discovery_set_state(काष्ठा hci_dev *hdev, पूर्णांक state)
अणु
	पूर्णांक old_state = hdev->discovery.state;

	BT_DBG("%s state %u -> %u", hdev->name, hdev->discovery.state, state);

	अगर (old_state == state)
		वापस;

	hdev->discovery.state = state;

	चयन (state) अणु
	हाल DISCOVERY_STOPPED:
		hci_update_background_scan(hdev);

		अगर (old_state != DISCOVERY_STARTING)
			mgmt_discovering(hdev, 0);
		अवरोध;
	हाल DISCOVERY_STARTING:
		अवरोध;
	हाल DISCOVERY_FINDING:
		mgmt_discovering(hdev, 1);
		अवरोध;
	हाल DISCOVERY_RESOLVING:
		अवरोध;
	हाल DISCOVERY_STOPPING:
		अवरोध;
	पूर्ण
पूर्ण

व्योम hci_inquiry_cache_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *p, *n;

	list_क्रम_each_entry_safe(p, n, &cache->all, all) अणु
		list_del(&p->all);
		kमुक्त(p);
	पूर्ण

	INIT_LIST_HEAD(&cache->unknown);
	INIT_LIST_HEAD(&cache->resolve);
पूर्ण

काष्ठा inquiry_entry *hci_inquiry_cache_lookup(काष्ठा hci_dev *hdev,
					       bdaddr_t *bdaddr)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	BT_DBG("cache %p, %pMR", cache, bdaddr);

	list_क्रम_each_entry(e, &cache->all, all) अणु
		अगर (!bacmp(&e->data.bdaddr, bdaddr))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा inquiry_entry *hci_inquiry_cache_lookup_unknown(काष्ठा hci_dev *hdev,
						       bdaddr_t *bdaddr)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	BT_DBG("cache %p, %pMR", cache, bdaddr);

	list_क्रम_each_entry(e, &cache->unknown, list) अणु
		अगर (!bacmp(&e->data.bdaddr, bdaddr))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा inquiry_entry *hci_inquiry_cache_lookup_resolve(काष्ठा hci_dev *hdev,
						       bdaddr_t *bdaddr,
						       पूर्णांक state)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	BT_DBG("cache %p bdaddr %pMR state %d", cache, bdaddr, state);

	list_क्रम_each_entry(e, &cache->resolve, list) अणु
		अगर (!bacmp(bdaddr, BDADDR_ANY) && e->name_state == state)
			वापस e;
		अगर (!bacmp(&e->data.bdaddr, bdaddr))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम hci_inquiry_cache_update_resolve(काष्ठा hci_dev *hdev,
				      काष्ठा inquiry_entry *ie)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा list_head *pos = &cache->resolve;
	काष्ठा inquiry_entry *p;

	list_del(&ie->list);

	list_क्रम_each_entry(p, &cache->resolve, list) अणु
		अगर (p->name_state != NAME_PENDING &&
		    असल(p->data.rssi) >= असल(ie->data.rssi))
			अवरोध;
		pos = &p->list;
	पूर्ण

	list_add(&ie->list, pos);
पूर्ण

u32 hci_inquiry_cache_update(काष्ठा hci_dev *hdev, काष्ठा inquiry_data *data,
			     bool name_known)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *ie;
	u32 flags = 0;

	BT_DBG("cache %p, %pMR", cache, &data->bdaddr);

	hci_हटाओ_remote_oob_data(hdev, &data->bdaddr, BDADDR_BREDR);

	अगर (!data->ssp_mode)
		flags |= MGMT_DEV_FOUND_LEGACY_PAIRING;

	ie = hci_inquiry_cache_lookup(hdev, &data->bdaddr);
	अगर (ie) अणु
		अगर (!ie->data.ssp_mode)
			flags |= MGMT_DEV_FOUND_LEGACY_PAIRING;

		अगर (ie->name_state == NAME_NEEDED &&
		    data->rssi != ie->data.rssi) अणु
			ie->data.rssi = data->rssi;
			hci_inquiry_cache_update_resolve(hdev, ie);
		पूर्ण

		जाओ update;
	पूर्ण

	/* Entry not in the cache. Add new one. */
	ie = kzalloc(माप(*ie), GFP_KERNEL);
	अगर (!ie) अणु
		flags |= MGMT_DEV_FOUND_CONFIRM_NAME;
		जाओ करोne;
	पूर्ण

	list_add(&ie->all, &cache->all);

	अगर (name_known) अणु
		ie->name_state = NAME_KNOWN;
	पूर्ण अन्यथा अणु
		ie->name_state = NAME_NOT_KNOWN;
		list_add(&ie->list, &cache->unknown);
	पूर्ण

update:
	अगर (name_known && ie->name_state != NAME_KNOWN &&
	    ie->name_state != NAME_PENDING) अणु
		ie->name_state = NAME_KNOWN;
		list_del(&ie->list);
	पूर्ण

	स_नकल(&ie->data, data, माप(*data));
	ie->बारtamp = jअगरfies;
	cache->बारtamp = jअगरfies;

	अगर (ie->name_state == NAME_NOT_KNOWN)
		flags |= MGMT_DEV_FOUND_CONFIRM_NAME;

करोne:
	वापस flags;
पूर्ण

अटल पूर्णांक inquiry_cache_dump(काष्ठा hci_dev *hdev, पूर्णांक num, __u8 *buf)
अणु
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_info *info = (काष्ठा inquiry_info *) buf;
	काष्ठा inquiry_entry *e;
	पूर्णांक copied = 0;

	list_क्रम_each_entry(e, &cache->all, all) अणु
		काष्ठा inquiry_data *data = &e->data;

		अगर (copied >= num)
			अवरोध;

		bacpy(&info->bdaddr, &data->bdaddr);
		info->pscan_rep_mode	= data->pscan_rep_mode;
		info->pscan_period_mode	= data->pscan_period_mode;
		info->pscan_mode	= data->pscan_mode;
		स_नकल(info->dev_class, data->dev_class, 3);
		info->घड़ी_offset	= data->घड़ी_offset;

		info++;
		copied++;
	पूर्ण

	BT_DBG("cache %p, copied %d", cache, copied);
	वापस copied;
पूर्ण

अटल पूर्णांक hci_inq_req(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_inquiry_req *ir = (काष्ठा hci_inquiry_req *) opt;
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_inquiry cp;

	BT_DBG("%s", hdev->name);

	अगर (test_bit(HCI_INQUIRY, &hdev->flags))
		वापस 0;

	/* Start Inquiry */
	स_नकल(&cp.lap, &ir->lap, 3);
	cp.length  = ir->length;
	cp.num_rsp = ir->num_rsp;
	hci_req_add(req, HCI_OP_INQUIRY, माप(cp), &cp);

	वापस 0;
पूर्ण

पूर्णांक hci_inquiry(व्योम __user *arg)
अणु
	__u8 __user *ptr = arg;
	काष्ठा hci_inquiry_req ir;
	काष्ठा hci_dev *hdev;
	पूर्णांक err = 0, करो_inquiry = 0, max_rsp;
	दीर्घ समयo;
	__u8 *buf;

	अगर (copy_from_user(&ir, ptr, माप(ir)))
		वापस -EFAULT;

	hdev = hci_dev_get(ir.dev_id);
	अगर (!hdev)
		वापस -ENODEV;

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		err = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	अगर (hdev->dev_type != HCI_PRIMARY) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	hci_dev_lock(hdev);
	अगर (inquiry_cache_age(hdev) > INQUIRY_CACHE_AGE_MAX ||
	    inquiry_cache_empty(hdev) || ir.flags & IREQ_CACHE_FLUSH) अणु
		hci_inquiry_cache_flush(hdev);
		करो_inquiry = 1;
	पूर्ण
	hci_dev_unlock(hdev);

	समयo = ir.length * msecs_to_jअगरfies(2000);

	अगर (करो_inquiry) अणु
		err = hci_req_sync(hdev, hci_inq_req, (अचिन्हित दीर्घ) &ir,
				   समयo, शून्य);
		अगर (err < 0)
			जाओ करोne;

		/* Wait until Inquiry procedure finishes (HCI_INQUIRY flag is
		 * cleared). If it is पूर्णांकerrupted by a संकेत, वापस -EINTR.
		 */
		अगर (रुको_on_bit(&hdev->flags, HCI_INQUIRY,
				TASK_INTERRUPTIBLE)) अणु
			err = -EINTR;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* क्रम unlimited number of responses we will use buffer with
	 * 255 entries
	 */
	max_rsp = (ir.num_rsp == 0) ? 255 : ir.num_rsp;

	/* cache_dump can't sleep. Thereक्रमe we allocate temp buffer and then
	 * copy it to the user space.
	 */
	buf = kदो_स्मृति_array(max_rsp, माप(काष्ठा inquiry_info), GFP_KERNEL);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	hci_dev_lock(hdev);
	ir.num_rsp = inquiry_cache_dump(hdev, max_rsp, buf);
	hci_dev_unlock(hdev);

	BT_DBG("num_rsp %d", ir.num_rsp);

	अगर (!copy_to_user(ptr, &ir, माप(ir))) अणु
		ptr += माप(ir);
		अगर (copy_to_user(ptr, buf, माप(काष्ठा inquiry_info) *
				 ir.num_rsp))
			err = -EFAULT;
	पूर्ण अन्यथा
		err = -EFAULT;

	kमुक्त(buf);

करोne:
	hci_dev_put(hdev);
	वापस err;
पूर्ण

/**
 * hci_dev_get_bd_addr_from_property - Get the Bluetooth Device Address
 *				       (BD_ADDR) क्रम a HCI device from
 *				       a firmware node property.
 * @hdev:	The HCI device
 *
 * Search the firmware node क्रम 'local-bd-address'.
 *
 * All-zero BD addresses are rejected, because those could be properties
 * that exist in the firmware tables, but were not updated by the firmware. For
 * example, the DTS could define 'local-bd-address', with zero BD addresses.
 */
अटल व्योम hci_dev_get_bd_addr_from_property(काष्ठा hci_dev *hdev)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(hdev->dev.parent);
	bdaddr_t ba;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u8_array(fwnode, "local-bd-address",
					    (u8 *)&ba, माप(ba));
	अगर (ret < 0 || !bacmp(&ba, BDADDR_ANY))
		वापस;

	bacpy(&hdev->खुला_addr, &ba);
पूर्ण

अटल पूर्णांक hci_dev_करो_खोलो(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक ret = 0;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_req_sync_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_UNREGISTER)) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_SETUP) &&
	    !hci_dev_test_flag(hdev, HCI_CONFIG)) अणु
		/* Check क्रम rfसमाप्त but allow the HCI setup stage to
		 * proceed (which in itself करोesn't cause any RF activity).
		 */
		अगर (hci_dev_test_flag(hdev, HCI_RFKILLED)) अणु
			ret = -ERFKILL;
			जाओ करोne;
		पूर्ण

		/* Check क्रम valid खुला address or a configured अटल
		 * अक्रमom adddress, but let the HCI setup proceed to
		 * be able to determine अगर there is a खुला address
		 * or not.
		 *
		 * In हाल of user channel usage, it is not important
		 * अगर a खुला address or अटल अक्रमom address is
		 * available.
		 *
		 * This check is only valid क्रम BR/EDR controllers
		 * since AMP controllers करो not have an address.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
		    hdev->dev_type == HCI_PRIMARY &&
		    !bacmp(&hdev->bdaddr, BDADDR_ANY) &&
		    !bacmp(&hdev->अटल_addr, BDADDR_ANY)) अणु
			ret = -EADDRNOTAVAIL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (test_bit(HCI_UP, &hdev->flags)) अणु
		ret = -EALREADY;
		जाओ करोne;
	पूर्ण

	अगर (hdev->खोलो(hdev)) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	set_bit(HCI_RUNNING, &hdev->flags);
	hci_sock_dev_event(hdev, HCI_DEV_OPEN);

	atomic_set(&hdev->cmd_cnt, 1);
	set_bit(HCI_INIT, &hdev->flags);

	अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    test_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks)) अणु
		bool invalid_bdaddr;

		hci_sock_dev_event(hdev, HCI_DEV_SETUP);

		अगर (hdev->setup)
			ret = hdev->setup(hdev);

		/* The transport driver can set the quirk to mark the
		 * BD_ADDR invalid beक्रमe creating the HCI device or in
		 * its setup callback.
		 */
		invalid_bdaddr = test_bit(HCI_QUIRK_INVALID_BDADDR,
					  &hdev->quirks);

		अगर (ret)
			जाओ setup_failed;

		अगर (test_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks)) अणु
			अगर (!bacmp(&hdev->खुला_addr, BDADDR_ANY))
				hci_dev_get_bd_addr_from_property(hdev);

			अगर (bacmp(&hdev->खुला_addr, BDADDR_ANY) &&
			    hdev->set_bdaddr) अणु
				ret = hdev->set_bdaddr(hdev,
						       &hdev->खुला_addr);

				/* If setting of the BD_ADDR from the device
				 * property succeeds, then treat the address
				 * as valid even अगर the invalid BD_ADDR
				 * quirk indicates otherwise.
				 */
				अगर (!ret)
					invalid_bdaddr = false;
			पूर्ण
		पूर्ण

setup_failed:
		/* The transport driver can set these quirks beक्रमe
		 * creating the HCI device or in its setup callback.
		 *
		 * For the invalid BD_ADDR quirk it is possible that
		 * it becomes a valid address अगर the bootloader करोes
		 * provide it (see above).
		 *
		 * In हाल any of them is set, the controller has to
		 * start up as unconfigured.
		 */
		अगर (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) ||
		    invalid_bdaddr)
			hci_dev_set_flag(hdev, HCI_UNCONFIGURED);

		/* For an unconfigured controller it is required to
		 * पढ़ो at least the version inक्रमmation provided by
		 * the Read Local Version Inक्रमmation command.
		 *
		 * If the set_bdaddr driver callback is provided, then
		 * also the original Bluetooth खुला device address
		 * will be पढ़ो using the Read BD Address command.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED))
			ret = __hci_unconf_init(hdev);
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_CONFIG)) अणु
		/* If खुला address change is configured, ensure that
		 * the address माला_लो programmed. If the driver करोes not
		 * support changing the खुला address, fail the घातer
		 * on procedure.
		 */
		अगर (bacmp(&hdev->खुला_addr, BDADDR_ANY) &&
		    hdev->set_bdaddr)
			ret = hdev->set_bdaddr(hdev, &hdev->खुला_addr);
		अन्यथा
			ret = -EADDRNOTAVAIL;
	पूर्ण

	अगर (!ret) अणु
		अगर (!hci_dev_test_flag(hdev, HCI_UNCONFIGURED) &&
		    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
			ret = __hci_init(hdev);
			अगर (!ret && hdev->post_init)
				ret = hdev->post_init(hdev);
		पूर्ण
	पूर्ण

	/* If the HCI Reset command is clearing all diagnostic settings,
	 * then they need to be reprogrammed after the init procedure
	 * completed.
	 */
	अगर (test_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks) &&
	    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
	    hci_dev_test_flag(hdev, HCI_VENDOR_DIAG) && hdev->set_diag)
		ret = hdev->set_diag(hdev, true);

	msft_करो_खोलो(hdev);
	aosp_करो_खोलो(hdev);

	clear_bit(HCI_INIT, &hdev->flags);

	अगर (!ret) अणु
		hci_dev_hold(hdev);
		hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);
		hci_adv_instances_set_rpa_expired(hdev, true);
		set_bit(HCI_UP, &hdev->flags);
		hci_sock_dev_event(hdev, HCI_DEV_UP);
		hci_leds_update_घातered(hdev, true);
		अगर (!hci_dev_test_flag(hdev, HCI_SETUP) &&
		    !hci_dev_test_flag(hdev, HCI_CONFIG) &&
		    !hci_dev_test_flag(hdev, HCI_UNCONFIGURED) &&
		    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
		    hci_dev_test_flag(hdev, HCI_MGMT) &&
		    hdev->dev_type == HCI_PRIMARY) अणु
			ret = __hci_req_hci_घातer_on(hdev);
			mgmt_घातer_on(hdev, ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Init failed, cleanup */
		flush_work(&hdev->tx_work);

		/* Since hci_rx_work() is possible to awake new cmd_work
		 * it should be flushed first to aव्योम unexpected call of
		 * hci_cmd_work()
		 */
		flush_work(&hdev->rx_work);
		flush_work(&hdev->cmd_work);

		skb_queue_purge(&hdev->cmd_q);
		skb_queue_purge(&hdev->rx_q);

		अगर (hdev->flush)
			hdev->flush(hdev);

		अगर (hdev->sent_cmd) अणु
			kमुक्त_skb(hdev->sent_cmd);
			hdev->sent_cmd = शून्य;
		पूर्ण

		clear_bit(HCI_RUNNING, &hdev->flags);
		hci_sock_dev_event(hdev, HCI_DEV_CLOSE);

		hdev->बंद(hdev);
		hdev->flags &= BIT(HCI_RAW);
	पूर्ण

करोne:
	hci_req_sync_unlock(hdev);
	वापस ret;
पूर्ण

/* ---- HCI ioctl helpers ---- */

पूर्णांक hci_dev_खोलो(__u16 dev)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	hdev = hci_dev_get(dev);
	अगर (!hdev)
		वापस -ENODEV;

	/* Devices that are marked as unconfigured can only be घातered
	 * up as user channel. Trying to bring them up as normal devices
	 * will result पूर्णांकo a failure. Only user channel operation is
	 * possible.
	 *
	 * When this function is called क्रम a user channel, the flag
	 * HCI_USER_CHANNEL will be set first beक्रमe attempting to
	 * खोलो the device.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED) &&
	    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	/* We need to ensure that no other घातer on/off work is pending
	 * beक्रमe proceeding to call hci_dev_करो_खोलो. This is
	 * particularly important अगर the setup procedure has not yet
	 * completed.
	 */
	अगर (hci_dev_test_and_clear_flag(hdev, HCI_AUTO_OFF))
		cancel_delayed_work(&hdev->घातer_off);

	/* After this call it is guaranteed that the setup procedure
	 * has finished. This means that error conditions like RFKILL
	 * or no valid खुला or अटल अक्रमom address apply.
	 */
	flush_workqueue(hdev->req_workqueue);

	/* For controllers not using the management पूर्णांकerface and that
	 * are brought up using legacy ioctl, set the HCI_BONDABLE bit
	 * so that pairing works क्रम them. Once the management पूर्णांकerface
	 * is in use this bit will be cleared again and userspace has
	 * to explicitly enable it.
	 */
	अगर (!hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
	    !hci_dev_test_flag(hdev, HCI_MGMT))
		hci_dev_set_flag(hdev, HCI_BONDABLE);

	err = hci_dev_करो_खोलो(hdev);

करोne:
	hci_dev_put(hdev);
	वापस err;
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल व्योम hci_pend_le_actions_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_params *p;

	list_क्रम_each_entry(p, &hdev->le_conn_params, list) अणु
		अगर (p->conn) अणु
			hci_conn_drop(p->conn);
			hci_conn_put(p->conn);
			p->conn = शून्य;
		पूर्ण
		list_del_init(&p->action);
	पूर्ण

	BT_DBG("All LE pending actions cleared");
पूर्ण

पूर्णांक hci_dev_करो_बंद(काष्ठा hci_dev *hdev)
अणु
	bool स्वतः_off;

	BT_DBG("%s %p", hdev->name, hdev);

	अगर (!hci_dev_test_flag(hdev, HCI_UNREGISTER) &&
	    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
	    test_bit(HCI_UP, &hdev->flags)) अणु
		/* Execute venकरोr specअगरic shutकरोwn routine */
		अगर (hdev->shutकरोwn)
			hdev->shutकरोwn(hdev);
	पूर्ण

	cancel_delayed_work(&hdev->घातer_off);

	hci_request_cancel_all(hdev);
	hci_req_sync_lock(hdev);

	अगर (!test_and_clear_bit(HCI_UP, &hdev->flags)) अणु
		cancel_delayed_work_sync(&hdev->cmd_समयr);
		hci_req_sync_unlock(hdev);
		वापस 0;
	पूर्ण

	hci_leds_update_घातered(hdev, false);

	/* Flush RX and TX works */
	flush_work(&hdev->tx_work);
	flush_work(&hdev->rx_work);

	अगर (hdev->discov_समयout > 0) अणु
		hdev->discov_समयout = 0;
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);
	पूर्ण

	अगर (hci_dev_test_and_clear_flag(hdev, HCI_SERVICE_CACHE))
		cancel_delayed_work(&hdev->service_cache);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT)) अणु
		काष्ठा adv_info *adv_instance;

		cancel_delayed_work_sync(&hdev->rpa_expired);

		list_क्रम_each_entry(adv_instance, &hdev->adv_instances, list)
			cancel_delayed_work_sync(&adv_instance->rpa_expired_cb);
	पूर्ण

	/* Aव्योम potential lockdep warnings from the *_flush() calls by
	 * ensuring the workqueue is empty up front.
	 */
	drain_workqueue(hdev->workqueue);

	hci_dev_lock(hdev);

	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);

	स्वतः_off = hci_dev_test_and_clear_flag(hdev, HCI_AUTO_OFF);

	अगर (!स्वतः_off && hdev->dev_type == HCI_PRIMARY &&
	    !hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
	    hci_dev_test_flag(hdev, HCI_MGMT))
		__mgmt_घातer_off(hdev);

	hci_inquiry_cache_flush(hdev);
	hci_pend_le_actions_clear(hdev);
	hci_conn_hash_flush(hdev);
	hci_dev_unlock(hdev);

	smp_unरेजिस्टर(hdev);

	hci_sock_dev_event(hdev, HCI_DEV_DOWN);

	aosp_करो_बंद(hdev);
	msft_करो_बंद(hdev);

	अगर (hdev->flush)
		hdev->flush(hdev);

	/* Reset device */
	skb_queue_purge(&hdev->cmd_q);
	atomic_set(&hdev->cmd_cnt, 1);
	अगर (test_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks) &&
	    !स्वतः_off && !hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		set_bit(HCI_INIT, &hdev->flags);
		__hci_req_sync(hdev, hci_reset_req, 0, HCI_CMD_TIMEOUT, शून्य);
		clear_bit(HCI_INIT, &hdev->flags);
	पूर्ण

	/* flush cmd  work */
	flush_work(&hdev->cmd_work);

	/* Drop queues */
	skb_queue_purge(&hdev->rx_q);
	skb_queue_purge(&hdev->cmd_q);
	skb_queue_purge(&hdev->raw_q);

	/* Drop last sent command */
	अगर (hdev->sent_cmd) अणु
		cancel_delayed_work_sync(&hdev->cmd_समयr);
		kमुक्त_skb(hdev->sent_cmd);
		hdev->sent_cmd = शून्य;
	पूर्ण

	clear_bit(HCI_RUNNING, &hdev->flags);
	hci_sock_dev_event(hdev, HCI_DEV_CLOSE);

	अगर (test_and_clear_bit(SUSPEND_POWERING_DOWN, hdev->suspend_tasks))
		wake_up(&hdev->suspend_रुको_q);

	/* After this poपूर्णांक our queues are empty
	 * and no tasks are scheduled. */
	hdev->बंद(hdev);

	/* Clear flags */
	hdev->flags &= BIT(HCI_RAW);
	hci_dev_clear_अस्थिर_flags(hdev);

	/* Controller radio is available but is currently घातered करोwn */
	hdev->amp_status = AMP_STATUS_POWERED_DOWN;

	स_रखो(hdev->eir, 0, माप(hdev->eir));
	स_रखो(hdev->dev_class, 0, माप(hdev->dev_class));
	bacpy(&hdev->अक्रमom_addr, BDADDR_ANY);

	hci_req_sync_unlock(hdev);

	hci_dev_put(hdev);
	वापस 0;
पूर्ण

पूर्णांक hci_dev_बंद(__u16 dev)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	hdev = hci_dev_get(dev);
	अगर (!hdev)
		वापस -ENODEV;

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		err = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_and_clear_flag(hdev, HCI_AUTO_OFF))
		cancel_delayed_work(&hdev->घातer_off);

	err = hci_dev_करो_बंद(hdev);

करोne:
	hci_dev_put(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक hci_dev_करो_reset(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक ret;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_req_sync_lock(hdev);

	/* Drop queues */
	skb_queue_purge(&hdev->rx_q);
	skb_queue_purge(&hdev->cmd_q);

	/* Aव्योम potential lockdep warnings from the *_flush() calls by
	 * ensuring the workqueue is empty up front.
	 */
	drain_workqueue(hdev->workqueue);

	hci_dev_lock(hdev);
	hci_inquiry_cache_flush(hdev);
	hci_conn_hash_flush(hdev);
	hci_dev_unlock(hdev);

	अगर (hdev->flush)
		hdev->flush(hdev);

	atomic_set(&hdev->cmd_cnt, 1);
	hdev->acl_cnt = 0; hdev->sco_cnt = 0; hdev->le_cnt = 0;

	ret = __hci_req_sync(hdev, hci_reset_req, 0, HCI_INIT_TIMEOUT, शून्य);

	hci_req_sync_unlock(hdev);
	वापस ret;
पूर्ण

पूर्णांक hci_dev_reset(__u16 dev)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	hdev = hci_dev_get(dev);
	अगर (!hdev)
		वापस -ENODEV;

	अगर (!test_bit(HCI_UP, &hdev->flags)) अणु
		err = -ENETDOWN;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		err = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	err = hci_dev_करो_reset(hdev);

करोne:
	hci_dev_put(hdev);
	वापस err;
पूर्ण

पूर्णांक hci_dev_reset_stat(__u16 dev)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक ret = 0;

	hdev = hci_dev_get(dev);
	अगर (!hdev)
		वापस -ENODEV;

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		ret = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	स_रखो(&hdev->stat, 0, माप(काष्ठा hci_dev_stats));

करोne:
	hci_dev_put(hdev);
	वापस ret;
पूर्ण

अटल व्योम hci_update_scan_state(काष्ठा hci_dev *hdev, u8 scan)
अणु
	bool conn_changed, discov_changed;

	BT_DBG("%s scan 0x%02x", hdev->name, scan);

	अगर ((scan & SCAN_PAGE))
		conn_changed = !hci_dev_test_and_set_flag(hdev,
							  HCI_CONNECTABLE);
	अन्यथा
		conn_changed = hci_dev_test_and_clear_flag(hdev,
							   HCI_CONNECTABLE);

	अगर ((scan & SCAN_INQUIRY)) अणु
		discov_changed = !hci_dev_test_and_set_flag(hdev,
							    HCI_DISCOVERABLE);
	पूर्ण अन्यथा अणु
		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);
		discov_changed = hci_dev_test_and_clear_flag(hdev,
							     HCI_DISCOVERABLE);
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		वापस;

	अगर (conn_changed || discov_changed) अणु
		/* In हाल this was disabled through mgmt */
		hci_dev_set_flag(hdev, HCI_BREDR_ENABLED);

		अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED))
			hci_req_update_adv_data(hdev, hdev->cur_adv_instance);

		mgmt_new_settings(hdev);
	पूर्ण
पूर्ण

पूर्णांक hci_dev_cmd(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा hci_dev *hdev;
	काष्ठा hci_dev_req dr;
	पूर्णांक err = 0;

	अगर (copy_from_user(&dr, arg, माप(dr)))
		वापस -EFAULT;

	hdev = hci_dev_get(dr.dev_id);
	अगर (!hdev)
		वापस -ENODEV;

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		err = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	अगर (hdev->dev_type != HCI_PRIMARY) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	चयन (cmd) अणु
	हाल HCISETAUTH:
		err = hci_req_sync(hdev, hci_auth_req, dr.dev_opt,
				   HCI_INIT_TIMEOUT, शून्य);
		अवरोध;

	हाल HCISETENCRYPT:
		अगर (!lmp_encrypt_capable(hdev)) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (!test_bit(HCI_AUTH, &hdev->flags)) अणु
			/* Auth must be enabled first */
			err = hci_req_sync(hdev, hci_auth_req, dr.dev_opt,
					   HCI_INIT_TIMEOUT, शून्य);
			अगर (err)
				अवरोध;
		पूर्ण

		err = hci_req_sync(hdev, hci_encrypt_req, dr.dev_opt,
				   HCI_INIT_TIMEOUT, शून्य);
		अवरोध;

	हाल HCISETSCAN:
		err = hci_req_sync(hdev, hci_scan_req, dr.dev_opt,
				   HCI_INIT_TIMEOUT, शून्य);

		/* Ensure that the connectable and discoverable states
		 * get correctly modअगरied as this was a non-mgmt change.
		 */
		अगर (!err)
			hci_update_scan_state(hdev, dr.dev_opt);
		अवरोध;

	हाल HCISETLINKPOL:
		err = hci_req_sync(hdev, hci_linkpol_req, dr.dev_opt,
				   HCI_INIT_TIMEOUT, शून्य);
		अवरोध;

	हाल HCISETLINKMODE:
		hdev->link_mode = ((__u16) dr.dev_opt) &
					(HCI_LM_MASTER | HCI_LM_ACCEPT);
		अवरोध;

	हाल HCISETPTYPE:
		अगर (hdev->pkt_type == (__u16) dr.dev_opt)
			अवरोध;

		hdev->pkt_type = (__u16) dr.dev_opt;
		mgmt_phy_configuration_changed(hdev, शून्य);
		अवरोध;

	हाल HCISETACLMTU:
		hdev->acl_mtu  = *((__u16 *) &dr.dev_opt + 1);
		hdev->acl_pkts = *((__u16 *) &dr.dev_opt + 0);
		अवरोध;

	हाल HCISETSCOMTU:
		hdev->sco_mtu  = *((__u16 *) &dr.dev_opt + 1);
		hdev->sco_pkts = *((__u16 *) &dr.dev_opt + 0);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

करोne:
	hci_dev_put(hdev);
	वापस err;
पूर्ण

पूर्णांक hci_get_dev_list(व्योम __user *arg)
अणु
	काष्ठा hci_dev *hdev;
	काष्ठा hci_dev_list_req *dl;
	काष्ठा hci_dev_req *dr;
	पूर्णांक n = 0, size, err;
	__u16 dev_num;

	अगर (get_user(dev_num, (__u16 __user *) arg))
		वापस -EFAULT;

	अगर (!dev_num || dev_num > (PAGE_SIZE * 2) / माप(*dr))
		वापस -EINVAL;

	size = माप(*dl) + dev_num * माप(*dr);

	dl = kzalloc(size, GFP_KERNEL);
	अगर (!dl)
		वापस -ENOMEM;

	dr = dl->dev_req;

	पढ़ो_lock(&hci_dev_list_lock);
	list_क्रम_each_entry(hdev, &hci_dev_list, list) अणु
		अचिन्हित दीर्घ flags = hdev->flags;

		/* When the स्वतः-off is configured it means the transport
		 * is running, but in that हाल still indicate that the
		 * device is actually करोwn.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_AUTO_OFF))
			flags &= ~BIT(HCI_UP);

		(dr + n)->dev_id  = hdev->id;
		(dr + n)->dev_opt = flags;

		अगर (++n >= dev_num)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&hci_dev_list_lock);

	dl->dev_num = n;
	size = माप(*dl) + n * माप(*dr);

	err = copy_to_user(arg, dl, size);
	kमुक्त(dl);

	वापस err ? -EFAULT : 0;
पूर्ण

पूर्णांक hci_get_dev_info(व्योम __user *arg)
अणु
	काष्ठा hci_dev *hdev;
	काष्ठा hci_dev_info di;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (copy_from_user(&di, arg, माप(di)))
		वापस -EFAULT;

	hdev = hci_dev_get(di.dev_id);
	अगर (!hdev)
		वापस -ENODEV;

	/* When the स्वतः-off is configured it means the transport
	 * is running, but in that हाल still indicate that the
	 * device is actually करोwn.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_AUTO_OFF))
		flags = hdev->flags & ~BIT(HCI_UP);
	अन्यथा
		flags = hdev->flags;

	म_नकल(di.name, hdev->name);
	di.bdaddr   = hdev->bdaddr;
	di.type     = (hdev->bus & 0x0f) | ((hdev->dev_type & 0x03) << 4);
	di.flags    = flags;
	di.pkt_type = hdev->pkt_type;
	अगर (lmp_bredr_capable(hdev)) अणु
		di.acl_mtu  = hdev->acl_mtu;
		di.acl_pkts = hdev->acl_pkts;
		di.sco_mtu  = hdev->sco_mtu;
		di.sco_pkts = hdev->sco_pkts;
	पूर्ण अन्यथा अणु
		di.acl_mtu  = hdev->le_mtu;
		di.acl_pkts = hdev->le_pkts;
		di.sco_mtu  = 0;
		di.sco_pkts = 0;
	पूर्ण
	di.link_policy = hdev->link_policy;
	di.link_mode   = hdev->link_mode;

	स_नकल(&di.stat, &hdev->stat, माप(di.stat));
	स_नकल(&di.features, &hdev->features, माप(di.features));

	अगर (copy_to_user(arg, &di, माप(di)))
		err = -EFAULT;

	hci_dev_put(hdev);

	वापस err;
पूर्ण

/* ---- Interface to HCI drivers ---- */

अटल पूर्णांक hci_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा hci_dev *hdev = data;

	BT_DBG("%p name %s blocked %d", hdev, hdev->name, blocked);

	अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL))
		वापस -EBUSY;

	अगर (blocked) अणु
		hci_dev_set_flag(hdev, HCI_RFKILLED);
		अगर (!hci_dev_test_flag(hdev, HCI_SETUP) &&
		    !hci_dev_test_flag(hdev, HCI_CONFIG))
			hci_dev_करो_बंद(hdev);
	पूर्ण अन्यथा अणु
		hci_dev_clear_flag(hdev, HCI_RFKILLED);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops hci_rfसमाप्त_ops = अणु
	.set_block = hci_rfसमाप्त_set_block,
पूर्ण;

अटल व्योम hci_घातer_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, घातer_on);
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	अगर (test_bit(HCI_UP, &hdev->flags) &&
	    hci_dev_test_flag(hdev, HCI_MGMT) &&
	    hci_dev_test_and_clear_flag(hdev, HCI_AUTO_OFF)) अणु
		cancel_delayed_work(&hdev->घातer_off);
		hci_req_sync_lock(hdev);
		err = __hci_req_hci_घातer_on(hdev);
		hci_req_sync_unlock(hdev);
		mgmt_घातer_on(hdev, err);
		वापस;
	पूर्ण

	err = hci_dev_करो_खोलो(hdev);
	अगर (err < 0) अणु
		hci_dev_lock(hdev);
		mgmt_set_घातered_failed(hdev, err);
		hci_dev_unlock(hdev);
		वापस;
	पूर्ण

	/* During the HCI setup phase, a few error conditions are
	 * ignored and they need to be checked now. If they are still
	 * valid, it is important to turn the device back off.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_RFKILLED) ||
	    hci_dev_test_flag(hdev, HCI_UNCONFIGURED) ||
	    (hdev->dev_type == HCI_PRIMARY &&
	     !bacmp(&hdev->bdaddr, BDADDR_ANY) &&
	     !bacmp(&hdev->अटल_addr, BDADDR_ANY))) अणु
		hci_dev_clear_flag(hdev, HCI_AUTO_OFF);
		hci_dev_करो_बंद(hdev);
	पूर्ण अन्यथा अगर (hci_dev_test_flag(hdev, HCI_AUTO_OFF)) अणु
		queue_delayed_work(hdev->req_workqueue, &hdev->घातer_off,
				   HCI_AUTO_OFF_TIMEOUT);
	पूर्ण

	अगर (hci_dev_test_and_clear_flag(hdev, HCI_SETUP)) अणु
		/* For unconfigured devices, set the HCI_RAW flag
		 * so that userspace can easily identअगरy them.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED))
			set_bit(HCI_RAW, &hdev->flags);

		/* For fully configured devices, this will send
		 * the Index Added event. For unconfigured devices,
		 * it will send Unconfigued Index Added event.
		 *
		 * Devices with HCI_QUIRK_RAW_DEVICE are ignored
		 * and no event will be send.
		 */
		mgmt_index_added(hdev);
	पूर्ण अन्यथा अगर (hci_dev_test_and_clear_flag(hdev, HCI_CONFIG)) अणु
		/* When the controller is now configured, then it
		 * is important to clear the HCI_RAW flag.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_UNCONFIGURED))
			clear_bit(HCI_RAW, &hdev->flags);

		/* Powering on the controller with HCI_CONFIG set only
		 * happens with the transition from unconfigured to
		 * configured. This will send the Index Added event.
		 */
		mgmt_index_added(hdev);
	पूर्ण
पूर्ण

अटल व्योम hci_घातer_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    घातer_off.work);

	BT_DBG("%s", hdev->name);

	hci_dev_करो_बंद(hdev);
पूर्ण

अटल व्योम hci_error_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, error_reset);

	BT_DBG("%s", hdev->name);

	अगर (hdev->hw_error)
		hdev->hw_error(hdev, hdev->hw_error_code);
	अन्यथा
		bt_dev_err(hdev, "hardware error 0x%2.2x", hdev->hw_error_code);

	अगर (hci_dev_करो_बंद(hdev))
		वापस;

	hci_dev_करो_खोलो(hdev);
पूर्ण

व्योम hci_uuids_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bt_uuid *uuid, *पंचांगp;

	list_क्रम_each_entry_safe(uuid, पंचांगp, &hdev->uuids, list) अणु
		list_del(&uuid->list);
		kमुक्त(uuid);
	पूर्ण
पूर्ण

व्योम hci_link_keys_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा link_key *key;

	list_क्रम_each_entry(key, &hdev->link_keys, list) अणु
		list_del_rcu(&key->list);
		kमुक्त_rcu(key, rcu);
	पूर्ण
पूर्ण

व्योम hci_smp_ltks_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा smp_ltk *k;

	list_क्रम_each_entry(k, &hdev->दीर्घ_term_keys, list) अणु
		list_del_rcu(&k->list);
		kमुक्त_rcu(k, rcu);
	पूर्ण
पूर्ण

व्योम hci_smp_irks_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा smp_irk *k;

	list_क्रम_each_entry(k, &hdev->identity_resolving_keys, list) अणु
		list_del_rcu(&k->list);
		kमुक्त_rcu(k, rcu);
	पूर्ण
पूर्ण

व्योम hci_blocked_keys_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा blocked_key *b;

	list_क्रम_each_entry(b, &hdev->blocked_keys, list) अणु
		list_del_rcu(&b->list);
		kमुक्त_rcu(b, rcu);
	पूर्ण
पूर्ण

bool hci_is_blocked_key(काष्ठा hci_dev *hdev, u8 type, u8 val[16])
अणु
	bool blocked = false;
	काष्ठा blocked_key *b;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(b, &hdev->blocked_keys, list) अणु
		अगर (b->type == type && !स_भेद(b->val, val, माप(b->val))) अणु
			blocked = true;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस blocked;
पूर्ण

काष्ठा link_key *hci_find_link_key(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr)
अणु
	काष्ठा link_key *k;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(k, &hdev->link_keys, list) अणु
		अगर (bacmp(bdaddr, &k->bdaddr) == 0) अणु
			rcu_पढ़ो_unlock();

			अगर (hci_is_blocked_key(hdev,
					       HCI_BLOCKED_KEY_TYPE_LINKKEY,
					       k->val)) अणु
				bt_dev_warn_ratelimited(hdev,
							"Link key blocked for %pMR",
							&k->bdaddr);
				वापस शून्य;
			पूर्ण

			वापस k;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल bool hci_persistent_key(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
			       u8 key_type, u8 old_key_type)
अणु
	/* Legacy key */
	अगर (key_type < 0x03)
		वापस true;

	/* Debug keys are insecure so करोn't store them persistently */
	अगर (key_type == HCI_LK_DEBUG_COMBINATION)
		वापस false;

	/* Changed combination key and there's no previous one */
	अगर (key_type == HCI_LK_CHANGED_COMBINATION && old_key_type == 0xff)
		वापस false;

	/* Security mode 3 हाल */
	अगर (!conn)
		वापस true;

	/* BR/EDR key derived using SC from an LE link */
	अगर (conn->type == LE_LINK)
		वापस true;

	/* Neither local nor remote side had no-bonding as requirement */
	अगर (conn->auth_type > 0x01 && conn->remote_auth > 0x01)
		वापस true;

	/* Local side had dedicated bonding as requirement */
	अगर (conn->auth_type == 0x02 || conn->auth_type == 0x03)
		वापस true;

	/* Remote side had dedicated bonding as requirement */
	अगर (conn->remote_auth == 0x02 || conn->remote_auth == 0x03)
		वापस true;

	/* If none of the above criteria match, then करोn't store the key
	 * persistently */
	वापस false;
पूर्ण

अटल u8 ltk_role(u8 type)
अणु
	अगर (type == SMP_LTK)
		वापस HCI_ROLE_MASTER;

	वापस HCI_ROLE_SLAVE;
पूर्ण

काष्ठा smp_ltk *hci_find_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			     u8 addr_type, u8 role)
अणु
	काष्ठा smp_ltk *k;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(k, &hdev->दीर्घ_term_keys, list) अणु
		अगर (addr_type != k->bdaddr_type || bacmp(bdaddr, &k->bdaddr))
			जारी;

		अगर (smp_ltk_is_sc(k) || ltk_role(k->type) == role) अणु
			rcu_पढ़ो_unlock();

			अगर (hci_is_blocked_key(hdev, HCI_BLOCKED_KEY_TYPE_LTK,
					       k->val)) अणु
				bt_dev_warn_ratelimited(hdev,
							"LTK blocked for %pMR",
							&k->bdaddr);
				वापस शून्य;
			पूर्ण

			वापस k;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

काष्ठा smp_irk *hci_find_irk_by_rpa(काष्ठा hci_dev *hdev, bdaddr_t *rpa)
अणु
	काष्ठा smp_irk *irk_to_वापस = शून्य;
	काष्ठा smp_irk *irk;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(irk, &hdev->identity_resolving_keys, list) अणु
		अगर (!bacmp(&irk->rpa, rpa)) अणु
			irk_to_वापस = irk;
			जाओ करोne;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_rcu(irk, &hdev->identity_resolving_keys, list) अणु
		अगर (smp_irk_matches(hdev, irk->val, rpa)) अणु
			bacpy(&irk->rpa, rpa);
			irk_to_वापस = irk;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	अगर (irk_to_वापस && hci_is_blocked_key(hdev, HCI_BLOCKED_KEY_TYPE_IRK,
						irk_to_वापस->val)) अणु
		bt_dev_warn_ratelimited(hdev, "Identity key blocked for %pMR",
					&irk_to_वापस->bdaddr);
		irk_to_वापस = शून्य;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस irk_to_वापस;
पूर्ण

काष्ठा smp_irk *hci_find_irk_by_addr(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 addr_type)
अणु
	काष्ठा smp_irk *irk_to_वापस = शून्य;
	काष्ठा smp_irk *irk;

	/* Identity Address must be खुला or अटल अक्रमom */
	अगर (addr_type == ADDR_LE_DEV_RANDOM && (bdaddr->b[5] & 0xc0) != 0xc0)
		वापस शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(irk, &hdev->identity_resolving_keys, list) अणु
		अगर (addr_type == irk->addr_type &&
		    bacmp(bdaddr, &irk->bdaddr) == 0) अणु
			irk_to_वापस = irk;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:

	अगर (irk_to_वापस && hci_is_blocked_key(hdev, HCI_BLOCKED_KEY_TYPE_IRK,
						irk_to_वापस->val)) अणु
		bt_dev_warn_ratelimited(hdev, "Identity key blocked for %pMR",
					&irk_to_वापस->bdaddr);
		irk_to_वापस = शून्य;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस irk_to_वापस;
पूर्ण

काष्ठा link_key *hci_add_link_key(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
				  bdaddr_t *bdaddr, u8 *val, u8 type,
				  u8 pin_len, bool *persistent)
अणु
	काष्ठा link_key *key, *old_key;
	u8 old_key_type;

	old_key = hci_find_link_key(hdev, bdaddr);
	अगर (old_key) अणु
		old_key_type = old_key->type;
		key = old_key;
	पूर्ण अन्यथा अणु
		old_key_type = conn ? conn->key_type : 0xff;
		key = kzalloc(माप(*key), GFP_KERNEL);
		अगर (!key)
			वापस शून्य;
		list_add_rcu(&key->list, &hdev->link_keys);
	पूर्ण

	BT_DBG("%s key for %pMR type %u", hdev->name, bdaddr, type);

	/* Some buggy controller combinations generate a changed
	 * combination key क्रम legacy pairing even when there's no
	 * previous key */
	अगर (type == HCI_LK_CHANGED_COMBINATION &&
	    (!conn || conn->remote_auth == 0xff) && old_key_type == 0xff) अणु
		type = HCI_LK_COMBINATION;
		अगर (conn)
			conn->key_type = type;
	पूर्ण

	bacpy(&key->bdaddr, bdaddr);
	स_नकल(key->val, val, HCI_LINK_KEY_SIZE);
	key->pin_len = pin_len;

	अगर (type == HCI_LK_CHANGED_COMBINATION)
		key->type = old_key_type;
	अन्यथा
		key->type = type;

	अगर (persistent)
		*persistent = hci_persistent_key(hdev, conn, type,
						 old_key_type);

	वापस key;
पूर्ण

काष्ठा smp_ltk *hci_add_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 addr_type, u8 type, u8 authenticated,
			    u8 tk[16], u8 enc_size, __le16 eभाग, __le64 अक्रम)
अणु
	काष्ठा smp_ltk *key, *old_key;
	u8 role = ltk_role(type);

	old_key = hci_find_ltk(hdev, bdaddr, addr_type, role);
	अगर (old_key)
		key = old_key;
	अन्यथा अणु
		key = kzalloc(माप(*key), GFP_KERNEL);
		अगर (!key)
			वापस शून्य;
		list_add_rcu(&key->list, &hdev->दीर्घ_term_keys);
	पूर्ण

	bacpy(&key->bdaddr, bdaddr);
	key->bdaddr_type = addr_type;
	स_नकल(key->val, tk, माप(key->val));
	key->authenticated = authenticated;
	key->eभाग = eभाग;
	key->अक्रम = अक्रम;
	key->enc_size = enc_size;
	key->type = type;

	वापस key;
पूर्ण

काष्ठा smp_irk *hci_add_irk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 addr_type, u8 val[16], bdaddr_t *rpa)
अणु
	काष्ठा smp_irk *irk;

	irk = hci_find_irk_by_addr(hdev, bdaddr, addr_type);
	अगर (!irk) अणु
		irk = kzalloc(माप(*irk), GFP_KERNEL);
		अगर (!irk)
			वापस शून्य;

		bacpy(&irk->bdaddr, bdaddr);
		irk->addr_type = addr_type;

		list_add_rcu(&irk->list, &hdev->identity_resolving_keys);
	पूर्ण

	स_नकल(irk->val, val, 16);
	bacpy(&irk->rpa, rpa);

	वापस irk;
पूर्ण

पूर्णांक hci_हटाओ_link_key(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr)
अणु
	काष्ठा link_key *key;

	key = hci_find_link_key(hdev, bdaddr);
	अगर (!key)
		वापस -ENOENT;

	BT_DBG("%s removing %pMR", hdev->name, bdaddr);

	list_del_rcu(&key->list);
	kमुक्त_rcu(key, rcu);

	वापस 0;
पूर्ण

पूर्णांक hci_हटाओ_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 bdaddr_type)
अणु
	काष्ठा smp_ltk *k;
	पूर्णांक हटाओd = 0;

	list_क्रम_each_entry_rcu(k, &hdev->दीर्घ_term_keys, list) अणु
		अगर (bacmp(bdaddr, &k->bdaddr) || k->bdaddr_type != bdaddr_type)
			जारी;

		BT_DBG("%s removing %pMR", hdev->name, bdaddr);

		list_del_rcu(&k->list);
		kमुक्त_rcu(k, rcu);
		हटाओd++;
	पूर्ण

	वापस हटाओd ? 0 : -ENOENT;
पूर्ण

व्योम hci_हटाओ_irk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 addr_type)
अणु
	काष्ठा smp_irk *k;

	list_क्रम_each_entry_rcu(k, &hdev->identity_resolving_keys, list) अणु
		अगर (bacmp(bdaddr, &k->bdaddr) || k->addr_type != addr_type)
			जारी;

		BT_DBG("%s removing %pMR", hdev->name, bdaddr);

		list_del_rcu(&k->list);
		kमुक्त_rcu(k, rcu);
	पूर्ण
पूर्ण

bool hci_bdaddr_is_paired(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा smp_ltk *k;
	काष्ठा smp_irk *irk;
	u8 addr_type;

	अगर (type == BDADDR_BREDR) अणु
		अगर (hci_find_link_key(hdev, bdaddr))
			वापस true;
		वापस false;
	पूर्ण

	/* Convert to HCI addr type which काष्ठा smp_ltk uses */
	अगर (type == BDADDR_LE_PUBLIC)
		addr_type = ADDR_LE_DEV_PUBLIC;
	अन्यथा
		addr_type = ADDR_LE_DEV_RANDOM;

	irk = hci_get_irk(hdev, bdaddr, addr_type);
	अगर (irk) अणु
		bdaddr = &irk->bdaddr;
		addr_type = irk->addr_type;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(k, &hdev->दीर्घ_term_keys, list) अणु
		अगर (k->bdaddr_type == addr_type && !bacmp(bdaddr, &k->bdaddr)) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

/* HCI command समयr function */
अटल व्योम hci_cmd_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    cmd_समयr.work);

	अगर (hdev->sent_cmd) अणु
		काष्ठा hci_command_hdr *sent = (व्योम *) hdev->sent_cmd->data;
		u16 opcode = __le16_to_cpu(sent->opcode);

		bt_dev_err(hdev, "command 0x%4.4x tx timeout", opcode);
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "command tx timeout");
	पूर्ण

	अगर (hdev->cmd_समयout)
		hdev->cmd_समयout(hdev);

	atomic_set(&hdev->cmd_cnt, 1);
	queue_work(hdev->workqueue, &hdev->cmd_work);
पूर्ण

काष्ठा oob_data *hci_find_remote_oob_data(काष्ठा hci_dev *hdev,
					  bdaddr_t *bdaddr, u8 bdaddr_type)
अणु
	काष्ठा oob_data *data;

	list_क्रम_each_entry(data, &hdev->remote_oob_data, list) अणु
		अगर (bacmp(bdaddr, &data->bdaddr) != 0)
			जारी;
		अगर (data->bdaddr_type != bdaddr_type)
			जारी;
		वापस data;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक hci_हटाओ_remote_oob_data(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			       u8 bdaddr_type)
अणु
	काष्ठा oob_data *data;

	data = hci_find_remote_oob_data(hdev, bdaddr, bdaddr_type);
	अगर (!data)
		वापस -ENOENT;

	BT_DBG("%s removing %pMR (%u)", hdev->name, bdaddr, bdaddr_type);

	list_del(&data->list);
	kमुक्त(data);

	वापस 0;
पूर्ण

व्योम hci_remote_oob_data_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा oob_data *data, *n;

	list_क्रम_each_entry_safe(data, n, &hdev->remote_oob_data, list) अणु
		list_del(&data->list);
		kमुक्त(data);
	पूर्ण
पूर्ण

पूर्णांक hci_add_remote_oob_data(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 bdaddr_type, u8 *hash192, u8 *अक्रम192,
			    u8 *hash256, u8 *अक्रम256)
अणु
	काष्ठा oob_data *data;

	data = hci_find_remote_oob_data(hdev, bdaddr, bdaddr_type);
	अगर (!data) अणु
		data = kदो_स्मृति(माप(*data), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;

		bacpy(&data->bdaddr, bdaddr);
		data->bdaddr_type = bdaddr_type;
		list_add(&data->list, &hdev->remote_oob_data);
	पूर्ण

	अगर (hash192 && अक्रम192) अणु
		स_नकल(data->hash192, hash192, माप(data->hash192));
		स_नकल(data->अक्रम192, अक्रम192, माप(data->अक्रम192));
		अगर (hash256 && अक्रम256)
			data->present = 0x03;
	पूर्ण अन्यथा अणु
		स_रखो(data->hash192, 0, माप(data->hash192));
		स_रखो(data->अक्रम192, 0, माप(data->अक्रम192));
		अगर (hash256 && अक्रम256)
			data->present = 0x02;
		अन्यथा
			data->present = 0x00;
	पूर्ण

	अगर (hash256 && अक्रम256) अणु
		स_नकल(data->hash256, hash256, माप(data->hash256));
		स_नकल(data->अक्रम256, अक्रम256, माप(data->अक्रम256));
	पूर्ण अन्यथा अणु
		स_रखो(data->hash256, 0, माप(data->hash256));
		स_रखो(data->अक्रम256, 0, माप(data->अक्रम256));
		अगर (hash192 && अक्रम192)
			data->present = 0x01;
	पूर्ण

	BT_DBG("%s for %pMR", hdev->name, bdaddr);

	वापस 0;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा adv_info *hci_find_adv_instance(काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा adv_info *adv_instance;

	list_क्रम_each_entry(adv_instance, &hdev->adv_instances, list) अणु
		अगर (adv_instance->instance == instance)
			वापस adv_instance;
	पूर्ण

	वापस शून्य;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा adv_info *hci_get_next_instance(काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा adv_info *cur_instance;

	cur_instance = hci_find_adv_instance(hdev, instance);
	अगर (!cur_instance)
		वापस शून्य;

	अगर (cur_instance == list_last_entry(&hdev->adv_instances,
					    काष्ठा adv_info, list))
		वापस list_first_entry(&hdev->adv_instances,
						 काष्ठा adv_info, list);
	अन्यथा
		वापस list_next_entry(cur_instance, list);
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक hci_हटाओ_adv_instance(काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);
	अगर (!adv_instance)
		वापस -ENOENT;

	BT_DBG("%s removing %dMR", hdev->name, instance);

	अगर (hdev->cur_adv_instance == instance) अणु
		अगर (hdev->adv_instance_समयout) अणु
			cancel_delayed_work(&hdev->adv_instance_expire);
			hdev->adv_instance_समयout = 0;
		पूर्ण
		hdev->cur_adv_instance = 0x00;
	पूर्ण

	cancel_delayed_work_sync(&adv_instance->rpa_expired_cb);

	list_del(&adv_instance->list);
	kमुक्त(adv_instance);

	hdev->adv_instance_cnt--;

	वापस 0;
पूर्ण

व्योम hci_adv_instances_set_rpa_expired(काष्ठा hci_dev *hdev, bool rpa_expired)
अणु
	काष्ठा adv_info *adv_instance, *n;

	list_क्रम_each_entry_safe(adv_instance, n, &hdev->adv_instances, list)
		adv_instance->rpa_expired = rpa_expired;
पूर्ण

/* This function requires the caller holds hdev->lock */
व्योम hci_adv_instances_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा adv_info *adv_instance, *n;

	अगर (hdev->adv_instance_समयout) अणु
		cancel_delayed_work(&hdev->adv_instance_expire);
		hdev->adv_instance_समयout = 0;
	पूर्ण

	list_क्रम_each_entry_safe(adv_instance, n, &hdev->adv_instances, list) अणु
		cancel_delayed_work_sync(&adv_instance->rpa_expired_cb);
		list_del(&adv_instance->list);
		kमुक्त(adv_instance);
	पूर्ण

	hdev->adv_instance_cnt = 0;
	hdev->cur_adv_instance = 0x00;
पूर्ण

अटल व्योम adv_instance_rpa_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adv_info *adv_instance = container_of(work, काष्ठा adv_info,
						     rpa_expired_cb.work);

	BT_DBG("");

	adv_instance->rpa_expired = true;
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक hci_add_adv_instance(काष्ठा hci_dev *hdev, u8 instance, u32 flags,
			 u16 adv_data_len, u8 *adv_data,
			 u16 scan_rsp_len, u8 *scan_rsp_data,
			 u16 समयout, u16 duration, s8 tx_घातer,
			 u32 min_पूर्णांकerval, u32 max_पूर्णांकerval)
अणु
	काष्ठा adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);
	अगर (adv_instance) अणु
		स_रखो(adv_instance->adv_data, 0,
		       माप(adv_instance->adv_data));
		स_रखो(adv_instance->scan_rsp_data, 0,
		       माप(adv_instance->scan_rsp_data));
	पूर्ण अन्यथा अणु
		अगर (hdev->adv_instance_cnt >= hdev->le_num_of_adv_sets ||
		    instance < 1 || instance > hdev->le_num_of_adv_sets)
			वापस -EOVERFLOW;

		adv_instance = kzalloc(माप(*adv_instance), GFP_KERNEL);
		अगर (!adv_instance)
			वापस -ENOMEM;

		adv_instance->pending = true;
		adv_instance->instance = instance;
		list_add(&adv_instance->list, &hdev->adv_instances);
		hdev->adv_instance_cnt++;
	पूर्ण

	adv_instance->flags = flags;
	adv_instance->adv_data_len = adv_data_len;
	adv_instance->scan_rsp_len = scan_rsp_len;
	adv_instance->min_पूर्णांकerval = min_पूर्णांकerval;
	adv_instance->max_पूर्णांकerval = max_पूर्णांकerval;
	adv_instance->tx_घातer = tx_घातer;

	अगर (adv_data_len)
		स_नकल(adv_instance->adv_data, adv_data, adv_data_len);

	अगर (scan_rsp_len)
		स_नकल(adv_instance->scan_rsp_data,
		       scan_rsp_data, scan_rsp_len);

	adv_instance->समयout = समयout;
	adv_instance->reमुख्यing_समय = समयout;

	अगर (duration == 0)
		adv_instance->duration = hdev->def_multi_adv_rotation_duration;
	अन्यथा
		adv_instance->duration = duration;

	INIT_DELAYED_WORK(&adv_instance->rpa_expired_cb,
			  adv_instance_rpa_expired);

	BT_DBG("%s for %dMR", hdev->name, instance);

	वापस 0;
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक hci_set_adv_instance_data(काष्ठा hci_dev *hdev, u8 instance,
			      u16 adv_data_len, u8 *adv_data,
			      u16 scan_rsp_len, u8 *scan_rsp_data)
अणु
	काष्ठा adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);

	/* If advertisement करोesn't exist, we can't modअगरy its data */
	अगर (!adv_instance)
		वापस -ENOENT;

	अगर (adv_data_len) अणु
		स_रखो(adv_instance->adv_data, 0,
		       माप(adv_instance->adv_data));
		स_नकल(adv_instance->adv_data, adv_data, adv_data_len);
		adv_instance->adv_data_len = adv_data_len;
	पूर्ण

	अगर (scan_rsp_len) अणु
		स_रखो(adv_instance->scan_rsp_data, 0,
		       माप(adv_instance->scan_rsp_data));
		स_नकल(adv_instance->scan_rsp_data,
		       scan_rsp_data, scan_rsp_len);
		adv_instance->scan_rsp_len = scan_rsp_len;
	पूर्ण

	वापस 0;
पूर्ण

/* This function requires the caller holds hdev->lock */
व्योम hci_adv_monitors_clear(काष्ठा hci_dev *hdev)
अणु
	काष्ठा adv_monitor *monitor;
	पूर्णांक handle;

	idr_क्रम_each_entry(&hdev->adv_monitors_idr, monitor, handle)
		hci_मुक्त_adv_monitor(hdev, monitor);

	idr_destroy(&hdev->adv_monitors_idr);
पूर्ण

/* Frees the monitor काष्ठाure and करो some bookkeepings.
 * This function requires the caller holds hdev->lock.
 */
व्योम hci_मुक्त_adv_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor)
अणु
	काष्ठा adv_pattern *pattern;
	काष्ठा adv_pattern *पंचांगp;

	अगर (!monitor)
		वापस;

	list_क्रम_each_entry_safe(pattern, पंचांगp, &monitor->patterns, list) अणु
		list_del(&pattern->list);
		kमुक्त(pattern);
	पूर्ण

	अगर (monitor->handle)
		idr_हटाओ(&hdev->adv_monitors_idr, monitor->handle);

	अगर (monitor->state != ADV_MONITOR_STATE_NOT_REGISTERED) अणु
		hdev->adv_monitors_cnt--;
		mgmt_adv_monitor_हटाओd(hdev, monitor->handle);
	पूर्ण

	kमुक्त(monitor);
पूर्ण

पूर्णांक hci_add_adv_patterns_monitor_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	वापस mgmt_add_adv_patterns_monitor_complete(hdev, status);
पूर्ण

पूर्णांक hci_हटाओ_adv_monitor_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	वापस mgmt_हटाओ_adv_monitor_complete(hdev, status);
पूर्ण

/* Assigns handle to a monitor, and अगर offloading is supported and घातer is on,
 * also attempts to क्रमward the request to the controller.
 * Returns true अगर request is क्रमwarded (result is pending), false otherwise.
 * This function requires the caller holds hdev->lock.
 */
bool hci_add_adv_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor,
			 पूर्णांक *err)
अणु
	पूर्णांक min, max, handle;

	*err = 0;

	अगर (!monitor) अणु
		*err = -EINVAL;
		वापस false;
	पूर्ण

	min = HCI_MIN_ADV_MONITOR_HANDLE;
	max = HCI_MIN_ADV_MONITOR_HANDLE + HCI_MAX_ADV_MONITOR_NUM_HANDLES;
	handle = idr_alloc(&hdev->adv_monitors_idr, monitor, min, max,
			   GFP_KERNEL);
	अगर (handle < 0) अणु
		*err = handle;
		वापस false;
	पूर्ण

	monitor->handle = handle;

	अगर (!hdev_is_घातered(hdev))
		वापस false;

	चयन (hci_get_adv_monitor_offload_ext(hdev)) अणु
	हाल HCI_ADV_MONITOR_EXT_NONE:
		hci_update_background_scan(hdev);
		bt_dev_dbg(hdev, "%s add monitor status %d", hdev->name, *err);
		/* Message was not क्रमwarded to controller - not an error */
		वापस false;
	हाल HCI_ADV_MONITOR_EXT_MSFT:
		*err = msft_add_monitor_pattern(hdev, monitor);
		bt_dev_dbg(hdev, "%s add monitor msft status %d", hdev->name,
			   *err);
		अवरोध;
	पूर्ण

	वापस (*err == 0);
पूर्ण

/* Attempts to tell the controller and मुक्त the monitor. If somehow the
 * controller करोesn't have a corresponding handle, हटाओ anyway.
 * Returns true अगर request is क्रमwarded (result is pending), false otherwise.
 * This function requires the caller holds hdev->lock.
 */
अटल bool hci_हटाओ_adv_monitor(काष्ठा hci_dev *hdev,
				   काष्ठा adv_monitor *monitor,
				   u16 handle, पूर्णांक *err)
अणु
	*err = 0;

	चयन (hci_get_adv_monitor_offload_ext(hdev)) अणु
	हाल HCI_ADV_MONITOR_EXT_NONE: /* also goes here when घातered off */
		जाओ मुक्त_monitor;
	हाल HCI_ADV_MONITOR_EXT_MSFT:
		*err = msft_हटाओ_monitor(hdev, monitor, handle);
		अवरोध;
	पूर्ण

	/* In हाल no matching handle रेजिस्टरed, just मुक्त the monitor */
	अगर (*err == -ENOENT)
		जाओ मुक्त_monitor;

	वापस (*err == 0);

मुक्त_monitor:
	अगर (*err == -ENOENT)
		bt_dev_warn(hdev, "Removing monitor with no matching handle %d",
			    monitor->handle);
	hci_मुक्त_adv_monitor(hdev, monitor);

	*err = 0;
	वापस false;
पूर्ण

/* Returns true अगर request is क्रमwarded (result is pending), false otherwise.
 * This function requires the caller holds hdev->lock.
 */
bool hci_हटाओ_single_adv_monitor(काष्ठा hci_dev *hdev, u16 handle, पूर्णांक *err)
अणु
	काष्ठा adv_monitor *monitor = idr_find(&hdev->adv_monitors_idr, handle);
	bool pending;

	अगर (!monitor) अणु
		*err = -EINVAL;
		वापस false;
	पूर्ण

	pending = hci_हटाओ_adv_monitor(hdev, monitor, handle, err);
	अगर (!*err && !pending)
		hci_update_background_scan(hdev);

	bt_dev_dbg(hdev, "%s remove monitor handle %d, status %d, %spending",
		   hdev->name, handle, *err, pending ? "" : "not ");

	वापस pending;
पूर्ण

/* Returns true अगर request is क्रमwarded (result is pending), false otherwise.
 * This function requires the caller holds hdev->lock.
 */
bool hci_हटाओ_all_adv_monitor(काष्ठा hci_dev *hdev, पूर्णांक *err)
अणु
	काष्ठा adv_monitor *monitor;
	पूर्णांक idr_next_id = 0;
	bool pending = false;
	bool update = false;

	*err = 0;

	जबतक (!*err && !pending) अणु
		monitor = idr_get_next(&hdev->adv_monitors_idr, &idr_next_id);
		अगर (!monitor)
			अवरोध;

		pending = hci_हटाओ_adv_monitor(hdev, monitor, 0, err);

		अगर (!*err && !pending)
			update = true;
	पूर्ण

	अगर (update)
		hci_update_background_scan(hdev);

	bt_dev_dbg(hdev, "%s remove all monitors status %d, %spending",
		   hdev->name, *err, pending ? "" : "not ");

	वापस pending;
पूर्ण

/* This function requires the caller holds hdev->lock */
bool hci_is_adv_monitoring(काष्ठा hci_dev *hdev)
अणु
	वापस !idr_is_empty(&hdev->adv_monitors_idr);
पूर्ण

पूर्णांक hci_get_adv_monitor_offload_ext(काष्ठा hci_dev *hdev)
अणु
	अगर (msft_monitor_supported(hdev))
		वापस HCI_ADV_MONITOR_EXT_MSFT;

	वापस HCI_ADV_MONITOR_EXT_NONE;
पूर्ण

काष्ठा bdaddr_list *hci_bdaddr_list_lookup(काष्ठा list_head *bdaddr_list,
					 bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा bdaddr_list *b;

	list_क्रम_each_entry(b, bdaddr_list, list) अणु
		अगर (!bacmp(&b->bdaddr, bdaddr) && b->bdaddr_type == type)
			वापस b;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा bdaddr_list_with_irk *hci_bdaddr_list_lookup_with_irk(
				काष्ठा list_head *bdaddr_list, bdaddr_t *bdaddr,
				u8 type)
अणु
	काष्ठा bdaddr_list_with_irk *b;

	list_क्रम_each_entry(b, bdaddr_list, list) अणु
		अगर (!bacmp(&b->bdaddr, bdaddr) && b->bdaddr_type == type)
			वापस b;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा bdaddr_list_with_flags *
hci_bdaddr_list_lookup_with_flags(काष्ठा list_head *bdaddr_list,
				  bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा bdaddr_list_with_flags *b;

	list_क्रम_each_entry(b, bdaddr_list, list) अणु
		अगर (!bacmp(&b->bdaddr, bdaddr) && b->bdaddr_type == type)
			वापस b;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम hci_bdaddr_list_clear(काष्ठा list_head *bdaddr_list)
अणु
	काष्ठा bdaddr_list *b, *n;

	list_क्रम_each_entry_safe(b, n, bdaddr_list, list) अणु
		list_del(&b->list);
		kमुक्त(b);
	पूर्ण
पूर्ण

पूर्णांक hci_bdaddr_list_add(काष्ठा list_head *list, bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा bdaddr_list *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY))
		वापस -EBADF;

	अगर (hci_bdaddr_list_lookup(list, bdaddr, type))
		वापस -EEXIST;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	bacpy(&entry->bdaddr, bdaddr);
	entry->bdaddr_type = type;

	list_add(&entry->list, list);

	वापस 0;
पूर्ण

पूर्णांक hci_bdaddr_list_add_with_irk(काष्ठा list_head *list, bdaddr_t *bdaddr,
					u8 type, u8 *peer_irk, u8 *local_irk)
अणु
	काष्ठा bdaddr_list_with_irk *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY))
		वापस -EBADF;

	अगर (hci_bdaddr_list_lookup(list, bdaddr, type))
		वापस -EEXIST;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	bacpy(&entry->bdaddr, bdaddr);
	entry->bdaddr_type = type;

	अगर (peer_irk)
		स_नकल(entry->peer_irk, peer_irk, 16);

	अगर (local_irk)
		स_नकल(entry->local_irk, local_irk, 16);

	list_add(&entry->list, list);

	वापस 0;
पूर्ण

पूर्णांक hci_bdaddr_list_add_with_flags(काष्ठा list_head *list, bdaddr_t *bdaddr,
				   u8 type, u32 flags)
अणु
	काष्ठा bdaddr_list_with_flags *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY))
		वापस -EBADF;

	अगर (hci_bdaddr_list_lookup(list, bdaddr, type))
		वापस -EEXIST;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	bacpy(&entry->bdaddr, bdaddr);
	entry->bdaddr_type = type;
	entry->current_flags = flags;

	list_add(&entry->list, list);

	वापस 0;
पूर्ण

पूर्णांक hci_bdaddr_list_del(काष्ठा list_head *list, bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा bdaddr_list *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY)) अणु
		hci_bdaddr_list_clear(list);
		वापस 0;
	पूर्ण

	entry = hci_bdaddr_list_lookup(list, bdaddr, type);
	अगर (!entry)
		वापस -ENOENT;

	list_del(&entry->list);
	kमुक्त(entry);

	वापस 0;
पूर्ण

पूर्णांक hci_bdaddr_list_del_with_irk(काष्ठा list_head *list, bdaddr_t *bdaddr,
							u8 type)
अणु
	काष्ठा bdaddr_list_with_irk *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY)) अणु
		hci_bdaddr_list_clear(list);
		वापस 0;
	पूर्ण

	entry = hci_bdaddr_list_lookup_with_irk(list, bdaddr, type);
	अगर (!entry)
		वापस -ENOENT;

	list_del(&entry->list);
	kमुक्त(entry);

	वापस 0;
पूर्ण

पूर्णांक hci_bdaddr_list_del_with_flags(काष्ठा list_head *list, bdaddr_t *bdaddr,
				   u8 type)
अणु
	काष्ठा bdaddr_list_with_flags *entry;

	अगर (!bacmp(bdaddr, BDADDR_ANY)) अणु
		hci_bdaddr_list_clear(list);
		वापस 0;
	पूर्ण

	entry = hci_bdaddr_list_lookup_with_flags(list, bdaddr, type);
	अगर (!entry)
		वापस -ENOENT;

	list_del(&entry->list);
	kमुक्त(entry);

	वापस 0;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा hci_conn_params *hci_conn_params_lookup(काष्ठा hci_dev *hdev,
					       bdaddr_t *addr, u8 addr_type)
अणु
	काष्ठा hci_conn_params *params;

	list_क्रम_each_entry(params, &hdev->le_conn_params, list) अणु
		अगर (bacmp(&params->addr, addr) == 0 &&
		    params->addr_type == addr_type) अणु
			वापस params;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा hci_conn_params *hci_pend_le_action_lookup(काष्ठा list_head *list,
						  bdaddr_t *addr, u8 addr_type)
अणु
	काष्ठा hci_conn_params *param;

	चयन (addr_type) अणु
	हाल ADDR_LE_DEV_PUBLIC_RESOLVED:
		addr_type = ADDR_LE_DEV_PUBLIC;
		अवरोध;
	हाल ADDR_LE_DEV_RANDOM_RESOLVED:
		addr_type = ADDR_LE_DEV_RANDOM;
		अवरोध;
	पूर्ण

	list_क्रम_each_entry(param, list, action) अणु
		अगर (bacmp(&param->addr, addr) == 0 &&
		    param->addr_type == addr_type)
			वापस param;
	पूर्ण

	वापस शून्य;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा hci_conn_params *hci_conn_params_add(काष्ठा hci_dev *hdev,
					    bdaddr_t *addr, u8 addr_type)
अणु
	काष्ठा hci_conn_params *params;

	params = hci_conn_params_lookup(hdev, addr, addr_type);
	अगर (params)
		वापस params;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params) अणु
		bt_dev_err(hdev, "out of memory");
		वापस शून्य;
	पूर्ण

	bacpy(&params->addr, addr);
	params->addr_type = addr_type;

	list_add(&params->list, &hdev->le_conn_params);
	INIT_LIST_HEAD(&params->action);

	params->conn_min_पूर्णांकerval = hdev->le_conn_min_पूर्णांकerval;
	params->conn_max_पूर्णांकerval = hdev->le_conn_max_पूर्णांकerval;
	params->conn_latency = hdev->le_conn_latency;
	params->supervision_समयout = hdev->le_supv_समयout;
	params->स्वतः_connect = HCI_AUTO_CONN_DISABLED;

	BT_DBG("addr %pMR (type %u)", addr, addr_type);

	वापस params;
पूर्ण

अटल व्योम hci_conn_params_मुक्त(काष्ठा hci_conn_params *params)
अणु
	अगर (params->conn) अणु
		hci_conn_drop(params->conn);
		hci_conn_put(params->conn);
	पूर्ण

	list_del(&params->action);
	list_del(&params->list);
	kमुक्त(params);
पूर्ण

/* This function requires the caller holds hdev->lock */
व्योम hci_conn_params_del(काष्ठा hci_dev *hdev, bdaddr_t *addr, u8 addr_type)
अणु
	काष्ठा hci_conn_params *params;

	params = hci_conn_params_lookup(hdev, addr, addr_type);
	अगर (!params)
		वापस;

	hci_conn_params_मुक्त(params);

	hci_update_background_scan(hdev);

	BT_DBG("addr %pMR (type %u)", addr, addr_type);
पूर्ण

/* This function requires the caller holds hdev->lock */
व्योम hci_conn_params_clear_disabled(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_params *params, *पंचांगp;

	list_क्रम_each_entry_safe(params, पंचांगp, &hdev->le_conn_params, list) अणु
		अगर (params->स्वतः_connect != HCI_AUTO_CONN_DISABLED)
			जारी;

		/* If trying to estabilish one समय connection to disabled
		 * device, leave the params, but mark them as just once.
		 */
		अगर (params->explicit_connect) अणु
			params->स्वतः_connect = HCI_AUTO_CONN_EXPLICIT;
			जारी;
		पूर्ण

		list_del(&params->list);
		kमुक्त(params);
	पूर्ण

	BT_DBG("All LE disabled connection parameters were removed");
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल व्योम hci_conn_params_clear_all(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_params *params, *पंचांगp;

	list_क्रम_each_entry_safe(params, पंचांगp, &hdev->le_conn_params, list)
		hci_conn_params_मुक्त(params);

	BT_DBG("All LE connection parameters were removed");
पूर्ण

/* Copy the Identity Address of the controller.
 *
 * If the controller has a खुला BD_ADDR, then by शेष use that one.
 * If this is a LE only controller without a खुला address, शेष to
 * the अटल अक्रमom address.
 *
 * For debugging purposes it is possible to क्रमce controllers with a
 * खुला address to use the अटल अक्रमom address instead.
 *
 * In हाल BR/EDR has been disabled on a dual-mode controller and
 * userspace has configured a अटल address, then that address
 * becomes the identity address instead of the खुला BR/EDR address.
 */
व्योम hci_copy_identity_address(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			       u8 *bdaddr_type)
अणु
	अगर (hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ||
	    !bacmp(&hdev->bdaddr, BDADDR_ANY) ||
	    (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
	     bacmp(&hdev->अटल_addr, BDADDR_ANY))) अणु
		bacpy(bdaddr, &hdev->अटल_addr);
		*bdaddr_type = ADDR_LE_DEV_RANDOM;
	पूर्ण अन्यथा अणु
		bacpy(bdaddr, &hdev->bdaddr);
		*bdaddr_type = ADDR_LE_DEV_PUBLIC;
	पूर्ण
पूर्ण

अटल व्योम hci_suspend_clear_tasks(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __SUSPEND_NUM_TASKS; i++)
		clear_bit(i, hdev->suspend_tasks);

	wake_up(&hdev->suspend_रुको_q);
पूर्ण

अटल पूर्णांक hci_suspend_रुको_event(काष्ठा hci_dev *hdev)
अणु
#घोषणा WAKE_COND                                                              \
	(find_first_bit(hdev->suspend_tasks, __SUSPEND_NUM_TASKS) ==           \
	 __SUSPEND_NUM_TASKS)

	पूर्णांक i;
	पूर्णांक ret = रुको_event_समयout(hdev->suspend_रुको_q,
				     WAKE_COND, SUSPEND_NOTIFIER_TIMEOUT);

	अगर (ret == 0) अणु
		bt_dev_err(hdev, "Timed out waiting for suspend events");
		क्रम (i = 0; i < __SUSPEND_NUM_TASKS; ++i) अणु
			अगर (test_bit(i, hdev->suspend_tasks))
				bt_dev_err(hdev, "Suspend timeout bit: %d", i);
			clear_bit(i, hdev->suspend_tasks);
		पूर्ण

		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hci_prepare_suspend(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev =
		container_of(work, काष्ठा hci_dev, suspend_prepare);

	hci_dev_lock(hdev);
	hci_req_prepare_suspend(hdev, hdev->suspend_state_next);
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक hci_change_suspend_state(काष्ठा hci_dev *hdev,
				    क्रमागत suspended_state next)
अणु
	hdev->suspend_state_next = next;
	set_bit(SUSPEND_PREPARE_NOTIFIER, hdev->suspend_tasks);
	queue_work(hdev->req_workqueue, &hdev->suspend_prepare);
	वापस hci_suspend_रुको_event(hdev);
पूर्ण

अटल व्योम hci_clear_wake_reason(काष्ठा hci_dev *hdev)
अणु
	hci_dev_lock(hdev);

	hdev->wake_reason = 0;
	bacpy(&hdev->wake_addr, BDADDR_ANY);
	hdev->wake_addr_type = 0;

	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक hci_suspend_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
				व्योम *data)
अणु
	काष्ठा hci_dev *hdev =
		container_of(nb, काष्ठा hci_dev, suspend_notअगरier);
	पूर्णांक ret = 0;
	u8 state = BT_RUNNING;

	/* If घातering करोwn, रुको क्रम completion. */
	अगर (mgmt_घातering_करोwn(hdev)) अणु
		set_bit(SUSPEND_POWERING_DOWN, hdev->suspend_tasks);
		ret = hci_suspend_रुको_event(hdev);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	/* Suspend notअगरier should only act on events when घातered. */
	अगर (!hdev_is_घातered(hdev) ||
	    hci_dev_test_flag(hdev, HCI_UNREGISTER))
		जाओ करोne;

	अगर (action == PM_SUSPEND_PREPARE) अणु
		/* Suspend consists of two actions:
		 *  - First, disconnect everything and make the controller not
		 *    connectable (disabling scanning)
		 *  - Second, program event filter/whitelist and enable scan
		 */
		ret = hci_change_suspend_state(hdev, BT_SUSPEND_DISCONNECT);
		अगर (!ret)
			state = BT_SUSPEND_DISCONNECT;

		/* Only configure whitelist अगर disconnect succeeded and wake
		 * isn't being prevented.
		 */
		अगर (!ret && !(hdev->prevent_wake && hdev->prevent_wake(hdev))) अणु
			ret = hci_change_suspend_state(hdev,
						BT_SUSPEND_CONFIGURE_WAKE);
			अगर (!ret)
				state = BT_SUSPEND_CONFIGURE_WAKE;
		पूर्ण

		hci_clear_wake_reason(hdev);
		mgmt_suspending(hdev, state);

	पूर्ण अन्यथा अगर (action == PM_POST_SUSPEND) अणु
		ret = hci_change_suspend_state(hdev, BT_RUNNING);

		mgmt_resuming(hdev, hdev->wake_reason, &hdev->wake_addr,
			      hdev->wake_addr_type);
	पूर्ण

करोne:
	/* We always allow suspend even अगर suspend preparation failed and
	 * attempt to recover in resume.
	 */
	अगर (ret)
		bt_dev_err(hdev, "Suspend notifier action (%lu) failed: %d",
			   action, ret);

	वापस NOTIFY_DONE;
पूर्ण

/* Alloc HCI device */
काष्ठा hci_dev *hci_alloc_dev(व्योम)
अणु
	काष्ठा hci_dev *hdev;

	hdev = kzalloc(माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस शून्य;

	hdev->pkt_type  = (HCI_DM1 | HCI_DH1 | HCI_HV1);
	hdev->esco_type = (ESCO_HV1);
	hdev->link_mode = (HCI_LM_ACCEPT);
	hdev->num_iac = 0x01;		/* One IAC support is mandatory */
	hdev->io_capability = 0x03;	/* No Input No Output */
	hdev->manufacturer = 0xffff;	/* Default to पूर्णांकernal use */
	hdev->inq_tx_घातer = HCI_TX_POWER_INVALID;
	hdev->adv_tx_घातer = HCI_TX_POWER_INVALID;
	hdev->adv_instance_cnt = 0;
	hdev->cur_adv_instance = 0x00;
	hdev->adv_instance_समयout = 0;

	hdev->advmon_allowlist_duration = 300;
	hdev->advmon_no_filter_duration = 500;
	hdev->enable_advmon_पूर्णांकerleave_scan = 0x00;	/* Default to disable */

	hdev->snअगरf_max_पूर्णांकerval = 800;
	hdev->snअगरf_min_पूर्णांकerval = 80;

	hdev->le_adv_channel_map = 0x07;
	hdev->le_adv_min_पूर्णांकerval = 0x0800;
	hdev->le_adv_max_पूर्णांकerval = 0x0800;
	hdev->le_scan_पूर्णांकerval = 0x0060;
	hdev->le_scan_winकरोw = 0x0030;
	hdev->le_scan_पूर्णांक_suspend = 0x0400;
	hdev->le_scan_winकरोw_suspend = 0x0012;
	hdev->le_scan_पूर्णांक_discovery = DISCOV_LE_SCAN_INT;
	hdev->le_scan_winकरोw_discovery = DISCOV_LE_SCAN_WIN;
	hdev->le_scan_पूर्णांक_adv_monitor = 0x0060;
	hdev->le_scan_winकरोw_adv_monitor = 0x0030;
	hdev->le_scan_पूर्णांक_connect = 0x0060;
	hdev->le_scan_winकरोw_connect = 0x0060;
	hdev->le_conn_min_पूर्णांकerval = 0x0018;
	hdev->le_conn_max_पूर्णांकerval = 0x0028;
	hdev->le_conn_latency = 0x0000;
	hdev->le_supv_समयout = 0x002a;
	hdev->le_def_tx_len = 0x001b;
	hdev->le_def_tx_समय = 0x0148;
	hdev->le_max_tx_len = 0x001b;
	hdev->le_max_tx_समय = 0x0148;
	hdev->le_max_rx_len = 0x001b;
	hdev->le_max_rx_समय = 0x0148;
	hdev->le_max_key_size = SMP_MAX_ENC_KEY_SIZE;
	hdev->le_min_key_size = SMP_MIN_ENC_KEY_SIZE;
	hdev->le_tx_def_phys = HCI_LE_SET_PHY_1M;
	hdev->le_rx_def_phys = HCI_LE_SET_PHY_1M;
	hdev->le_num_of_adv_sets = HCI_MAX_ADV_INSTANCES;
	hdev->def_multi_adv_rotation_duration = HCI_DEFAULT_ADV_DURATION;
	hdev->def_le_स्वतःconnect_समयout = HCI_LE_AUTOCONN_TIMEOUT;
	hdev->min_le_tx_घातer = HCI_TX_POWER_INVALID;
	hdev->max_le_tx_घातer = HCI_TX_POWER_INVALID;

	hdev->rpa_समयout = HCI_DEFAULT_RPA_TIMEOUT;
	hdev->discov_पूर्णांकerleaved_समयout = DISCOV_INTERLEAVED_TIMEOUT;
	hdev->conn_info_min_age = DEFAULT_CONN_INFO_MIN_AGE;
	hdev->conn_info_max_age = DEFAULT_CONN_INFO_MAX_AGE;
	hdev->auth_payload_समयout = DEFAULT_AUTH_PAYLOAD_TIMEOUT;
	hdev->min_enc_key_size = HCI_MIN_ENC_KEY_SIZE;

	/* शेष 1.28 sec page scan */
	hdev->def_page_scan_type = PAGE_SCAN_TYPE_STANDARD;
	hdev->def_page_scan_पूर्णांक = 0x0800;
	hdev->def_page_scan_winकरोw = 0x0012;

	mutex_init(&hdev->lock);
	mutex_init(&hdev->req_lock);

	INIT_LIST_HEAD(&hdev->mgmt_pending);
	INIT_LIST_HEAD(&hdev->blacklist);
	INIT_LIST_HEAD(&hdev->whitelist);
	INIT_LIST_HEAD(&hdev->uuids);
	INIT_LIST_HEAD(&hdev->link_keys);
	INIT_LIST_HEAD(&hdev->दीर्घ_term_keys);
	INIT_LIST_HEAD(&hdev->identity_resolving_keys);
	INIT_LIST_HEAD(&hdev->remote_oob_data);
	INIT_LIST_HEAD(&hdev->le_white_list);
	INIT_LIST_HEAD(&hdev->le_resolv_list);
	INIT_LIST_HEAD(&hdev->le_conn_params);
	INIT_LIST_HEAD(&hdev->pend_le_conns);
	INIT_LIST_HEAD(&hdev->pend_le_reports);
	INIT_LIST_HEAD(&hdev->conn_hash.list);
	INIT_LIST_HEAD(&hdev->adv_instances);
	INIT_LIST_HEAD(&hdev->blocked_keys);

	INIT_WORK(&hdev->rx_work, hci_rx_work);
	INIT_WORK(&hdev->cmd_work, hci_cmd_work);
	INIT_WORK(&hdev->tx_work, hci_tx_work);
	INIT_WORK(&hdev->घातer_on, hci_घातer_on);
	INIT_WORK(&hdev->error_reset, hci_error_reset);
	INIT_WORK(&hdev->suspend_prepare, hci_prepare_suspend);

	INIT_DELAYED_WORK(&hdev->घातer_off, hci_घातer_off);

	skb_queue_head_init(&hdev->rx_q);
	skb_queue_head_init(&hdev->cmd_q);
	skb_queue_head_init(&hdev->raw_q);

	init_रुकोqueue_head(&hdev->req_रुको_q);
	init_रुकोqueue_head(&hdev->suspend_रुको_q);

	INIT_DELAYED_WORK(&hdev->cmd_समयr, hci_cmd_समयout);

	hci_request_setup(hdev);

	hci_init_sysfs(hdev);
	discovery_init(hdev);

	वापस hdev;
पूर्ण
EXPORT_SYMBOL(hci_alloc_dev);

/* Free HCI device */
व्योम hci_मुक्त_dev(काष्ठा hci_dev *hdev)
अणु
	/* will मुक्त via device release */
	put_device(&hdev->dev);
पूर्ण
EXPORT_SYMBOL(hci_मुक्त_dev);

/* Register HCI device */
पूर्णांक hci_रेजिस्टर_dev(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक id, error;

	अगर (!hdev->खोलो || !hdev->बंद || !hdev->send)
		वापस -EINVAL;

	/* Do not allow HCI_AMP devices to रेजिस्टर at index 0,
	 * so the index can be used as the AMP controller ID.
	 */
	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		id = ida_simple_get(&hci_index_ida, 0, 0, GFP_KERNEL);
		अवरोध;
	हाल HCI_AMP:
		id = ida_simple_get(&hci_index_ida, 1, 0, GFP_KERNEL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (id < 0)
		वापस id;

	प्र_लिखो(hdev->name, "hci%d", id);
	hdev->id = id;

	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	hdev->workqueue = alloc_ordered_workqueue("%s", WQ_HIGHPRI, hdev->name);
	अगर (!hdev->workqueue) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	hdev->req_workqueue = alloc_ordered_workqueue("%s", WQ_HIGHPRI,
						      hdev->name);
	अगर (!hdev->req_workqueue) अणु
		destroy_workqueue(hdev->workqueue);
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(bt_debugfs))
		hdev->debugfs = debugfs_create_dir(hdev->name, bt_debugfs);

	dev_set_name(&hdev->dev, "%s", hdev->name);

	error = device_add(&hdev->dev);
	अगर (error < 0)
		जाओ err_wqueue;

	hci_leds_init(hdev);

	hdev->rfसमाप्त = rfसमाप्त_alloc(hdev->name, &hdev->dev,
				    RFKILL_TYPE_BLUETOOTH, &hci_rfसमाप्त_ops,
				    hdev);
	अगर (hdev->rfसमाप्त) अणु
		अगर (rfसमाप्त_रेजिस्टर(hdev->rfसमाप्त) < 0) अणु
			rfसमाप्त_destroy(hdev->rfसमाप्त);
			hdev->rfसमाप्त = शून्य;
		पूर्ण
	पूर्ण

	अगर (hdev->rfसमाप्त && rfसमाप्त_blocked(hdev->rfसमाप्त))
		hci_dev_set_flag(hdev, HCI_RFKILLED);

	hci_dev_set_flag(hdev, HCI_SETUP);
	hci_dev_set_flag(hdev, HCI_AUTO_OFF);

	अगर (hdev->dev_type == HCI_PRIMARY) अणु
		/* Assume BR/EDR support until proven otherwise (such as
		 * through पढ़ोing supported features during init.
		 */
		hci_dev_set_flag(hdev, HCI_BREDR_ENABLED);
	पूर्ण

	ग_लिखो_lock(&hci_dev_list_lock);
	list_add(&hdev->list, &hci_dev_list);
	ग_लिखो_unlock(&hci_dev_list_lock);

	/* Devices that are marked क्रम raw-only usage are unconfigured
	 * and should not be included in normal operation.
	 */
	अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		hci_dev_set_flag(hdev, HCI_UNCONFIGURED);

	hci_sock_dev_event(hdev, HCI_DEV_REG);
	hci_dev_hold(hdev);

	अगर (!test_bit(HCI_QUIRK_NO_SUSPEND_NOTIFIER, &hdev->quirks)) अणु
		hdev->suspend_notअगरier.notअगरier_call = hci_suspend_notअगरier;
		error = रेजिस्टर_pm_notअगरier(&hdev->suspend_notअगरier);
		अगर (error)
			जाओ err_wqueue;
	पूर्ण

	queue_work(hdev->req_workqueue, &hdev->घातer_on);

	idr_init(&hdev->adv_monitors_idr);

	वापस id;

err_wqueue:
	destroy_workqueue(hdev->workqueue);
	destroy_workqueue(hdev->req_workqueue);
err:
	ida_simple_हटाओ(&hci_index_ida, hdev->id);

	वापस error;
पूर्ण
EXPORT_SYMBOL(hci_रेजिस्टर_dev);

/* Unरेजिस्टर HCI device */
व्योम hci_unरेजिस्टर_dev(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक id;

	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	hci_dev_set_flag(hdev, HCI_UNREGISTER);

	id = hdev->id;

	ग_लिखो_lock(&hci_dev_list_lock);
	list_del(&hdev->list);
	ग_लिखो_unlock(&hci_dev_list_lock);

	cancel_work_sync(&hdev->घातer_on);

	अगर (!test_bit(HCI_QUIRK_NO_SUSPEND_NOTIFIER, &hdev->quirks)) अणु
		hci_suspend_clear_tasks(hdev);
		unरेजिस्टर_pm_notअगरier(&hdev->suspend_notअगरier);
		cancel_work_sync(&hdev->suspend_prepare);
	पूर्ण

	hci_dev_करो_बंद(hdev);

	अगर (!test_bit(HCI_INIT, &hdev->flags) &&
	    !hci_dev_test_flag(hdev, HCI_SETUP) &&
	    !hci_dev_test_flag(hdev, HCI_CONFIG)) अणु
		hci_dev_lock(hdev);
		mgmt_index_हटाओd(hdev);
		hci_dev_unlock(hdev);
	पूर्ण

	/* mgmt_index_हटाओd should take care of emptying the
	 * pending list */
	BUG_ON(!list_empty(&hdev->mgmt_pending));

	hci_sock_dev_event(hdev, HCI_DEV_UNREG);

	अगर (hdev->rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(hdev->rfसमाप्त);
		rfसमाप्त_destroy(hdev->rfसमाप्त);
	पूर्ण

	device_del(&hdev->dev);

	debugfs_हटाओ_recursive(hdev->debugfs);
	kमुक्त_स्थिर(hdev->hw_info);
	kमुक्त_स्थिर(hdev->fw_info);

	destroy_workqueue(hdev->workqueue);
	destroy_workqueue(hdev->req_workqueue);

	hci_dev_lock(hdev);
	hci_bdaddr_list_clear(&hdev->blacklist);
	hci_bdaddr_list_clear(&hdev->whitelist);
	hci_uuids_clear(hdev);
	hci_link_keys_clear(hdev);
	hci_smp_ltks_clear(hdev);
	hci_smp_irks_clear(hdev);
	hci_remote_oob_data_clear(hdev);
	hci_adv_instances_clear(hdev);
	hci_adv_monitors_clear(hdev);
	hci_bdaddr_list_clear(&hdev->le_white_list);
	hci_bdaddr_list_clear(&hdev->le_resolv_list);
	hci_conn_params_clear_all(hdev);
	hci_discovery_filter_clear(hdev);
	hci_blocked_keys_clear(hdev);
	hci_dev_unlock(hdev);

	hci_dev_put(hdev);

	ida_simple_हटाओ(&hci_index_ida, id);
पूर्ण
EXPORT_SYMBOL(hci_unरेजिस्टर_dev);

/* Suspend HCI device */
पूर्णांक hci_suspend_dev(काष्ठा hci_dev *hdev)
अणु
	hci_sock_dev_event(hdev, HCI_DEV_SUSPEND);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_suspend_dev);

/* Resume HCI device */
पूर्णांक hci_resume_dev(काष्ठा hci_dev *hdev)
अणु
	hci_sock_dev_event(hdev, HCI_DEV_RESUME);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_resume_dev);

/* Reset HCI device */
पूर्णांक hci_reset_dev(काष्ठा hci_dev *hdev)
अणु
	अटल स्थिर u8 hw_err[] = अणु HCI_EV_HARDWARE_ERROR, 0x01, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(3, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	skb_put_data(skb, hw_err, 3);

	/* Send Hardware Error to upper stack */
	वापस hci_recv_frame(hdev, skb);
पूर्ण
EXPORT_SYMBOL(hci_reset_dev);

/* Receive frame from HCI drivers */
पूर्णांक hci_recv_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	अगर (!hdev || (!test_bit(HCI_UP, &hdev->flags)
		      && !test_bit(HCI_INIT, &hdev->flags))) अणु
		kमुक्त_skb(skb);
		वापस -ENXIO;
	पूर्ण

	अगर (hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
	    hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
	    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
	    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	/* Incoming skb */
	bt_cb(skb)->incoming = 1;

	/* Time stamp */
	__net_बारtamp(skb);

	skb_queue_tail(&hdev->rx_q, skb);
	queue_work(hdev->workqueue, &hdev->rx_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_recv_frame);

/* Receive diagnostic message from HCI drivers */
पूर्णांक hci_recv_diag(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	/* Mark as diagnostic packet */
	hci_skb_pkt_type(skb) = HCI_DIAG_PKT;

	/* Time stamp */
	__net_बारtamp(skb);

	skb_queue_tail(&hdev->rx_q, skb);
	queue_work(hdev->workqueue, &hdev->rx_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_recv_diag);

व्योम hci_set_hw_info(काष्ठा hci_dev *hdev, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;

	बहु_शुरू(vargs, fmt);
	kमुक्त_स्थिर(hdev->hw_info);
	hdev->hw_info = kvaप्र_लिखो_स्थिर(GFP_KERNEL, fmt, vargs);
	बहु_पूर्ण(vargs);
पूर्ण
EXPORT_SYMBOL(hci_set_hw_info);

व्योम hci_set_fw_info(काष्ठा hci_dev *hdev, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;

	बहु_शुरू(vargs, fmt);
	kमुक्त_स्थिर(hdev->fw_info);
	hdev->fw_info = kvaप्र_लिखो_स्थिर(GFP_KERNEL, fmt, vargs);
	बहु_पूर्ण(vargs);
पूर्ण
EXPORT_SYMBOL(hci_set_fw_info);

/* ---- Interface to upper protocols ---- */

पूर्णांक hci_रेजिस्टर_cb(काष्ठा hci_cb *cb)
अणु
	BT_DBG("%p name %s", cb, cb->name);

	mutex_lock(&hci_cb_list_lock);
	list_add_tail(&cb->list, &hci_cb_list);
	mutex_unlock(&hci_cb_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_रेजिस्टर_cb);

पूर्णांक hci_unरेजिस्टर_cb(काष्ठा hci_cb *cb)
अणु
	BT_DBG("%p name %s", cb, cb->name);

	mutex_lock(&hci_cb_list_lock);
	list_del(&cb->list);
	mutex_unlock(&hci_cb_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_unरेजिस्टर_cb);

अटल व्योम hci_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	BT_DBG("%s type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	/* Time stamp */
	__net_बारtamp(skb);

	/* Send copy to monitor */
	hci_send_to_monitor(hdev, skb);

	अगर (atomic_पढ़ो(&hdev->promisc)) अणु
		/* Send copy to the sockets */
		hci_send_to_sock(hdev, skb);
	पूर्ण

	/* Get rid of skb owner, prior to sending to the driver. */
	skb_orphan(skb);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	err = hdev->send(hdev, skb);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "sending frame failed (%d)", err);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/* Send HCI command */
पूर्णांक hci_send_cmd(काष्ठा hci_dev *hdev, __u16 opcode, __u32 plen,
		 स्थिर व्योम *param)
अणु
	काष्ठा sk_buff *skb;

	BT_DBG("%s opcode 0x%4.4x plen %d", hdev->name, opcode, plen);

	skb = hci_prepare_cmd(hdev, opcode, plen, param);
	अगर (!skb) अणु
		bt_dev_err(hdev, "no memory for command");
		वापस -ENOMEM;
	पूर्ण

	/* Stand-alone HCI commands must be flagged as
	 * single-command requests.
	 */
	bt_cb(skb)->hci.req_flags |= HCI_REQ_START;

	skb_queue_tail(&hdev->cmd_q, skb);
	queue_work(hdev->workqueue, &hdev->cmd_work);

	वापस 0;
पूर्ण

पूर्णांक __hci_cmd_send(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
		   स्थिर व्योम *param)
अणु
	काष्ठा sk_buff *skb;

	अगर (hci_opcode_ogf(opcode) != 0x3f) अणु
		/* A controller receiving a command shall respond with either
		 * a Command Status Event or a Command Complete Event.
		 * Thereक्रमe, all standard HCI commands must be sent via the
		 * standard API, using hci_send_cmd or hci_cmd_sync helpers.
		 * Some venकरोrs करो not comply with this rule क्रम venकरोr-specअगरic
		 * commands and करो not वापस any event. We want to support
		 * unresponded commands क्रम such हालs only.
		 */
		bt_dev_err(hdev, "unresponded command not supported");
		वापस -EINVAL;
	पूर्ण

	skb = hci_prepare_cmd(hdev, opcode, plen, param);
	अगर (!skb) अणु
		bt_dev_err(hdev, "no memory for command (opcode 0x%4.4x)",
			   opcode);
		वापस -ENOMEM;
	पूर्ण

	hci_send_frame(hdev, skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__hci_cmd_send);

/* Get data from the previously sent command */
व्योम *hci_sent_cmd_data(काष्ठा hci_dev *hdev, __u16 opcode)
अणु
	काष्ठा hci_command_hdr *hdr;

	अगर (!hdev->sent_cmd)
		वापस शून्य;

	hdr = (व्योम *) hdev->sent_cmd->data;

	अगर (hdr->opcode != cpu_to_le16(opcode))
		वापस शून्य;

	BT_DBG("%s opcode 0x%4.4x", hdev->name, opcode);

	वापस hdev->sent_cmd->data + HCI_COMMAND_HDR_SIZE;
पूर्ण

/* Send HCI command and रुको क्रम command commplete event */
काष्ठा sk_buff *hci_cmd_sync(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
			     स्थिर व्योम *param, u32 समयout)
अणु
	काष्ठा sk_buff *skb;

	अगर (!test_bit(HCI_UP, &hdev->flags))
		वापस ERR_PTR(-ENETDOWN);

	bt_dev_dbg(hdev, "opcode 0x%4.4x plen %d", opcode, plen);

	hci_req_sync_lock(hdev);
	skb = __hci_cmd_sync(hdev, opcode, plen, param, समयout);
	hci_req_sync_unlock(hdev);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(hci_cmd_sync);

/* Send ACL data */
अटल व्योम hci_add_acl_hdr(काष्ठा sk_buff *skb, __u16 handle, __u16 flags)
अणु
	काष्ठा hci_acl_hdr *hdr;
	पूर्णांक len = skb->len;

	skb_push(skb, HCI_ACL_HDR_SIZE);
	skb_reset_transport_header(skb);
	hdr = (काष्ठा hci_acl_hdr *)skb_transport_header(skb);
	hdr->handle = cpu_to_le16(hci_handle_pack(handle, flags));
	hdr->dlen   = cpu_to_le16(len);
पूर्ण

अटल व्योम hci_queue_acl(काष्ठा hci_chan *chan, काष्ठा sk_buff_head *queue,
			  काष्ठा sk_buff *skb, __u16 flags)
अणु
	काष्ठा hci_conn *conn = chan->conn;
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा sk_buff *list;

	skb->len = skb_headlen(skb);
	skb->data_len = 0;

	hci_skb_pkt_type(skb) = HCI_ACLDATA_PKT;

	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		hci_add_acl_hdr(skb, conn->handle, flags);
		अवरोध;
	हाल HCI_AMP:
		hci_add_acl_hdr(skb, chan->handle, flags);
		अवरोध;
	शेष:
		bt_dev_err(hdev, "unknown dev_type %d", hdev->dev_type);
		वापस;
	पूर्ण

	list = skb_shinfo(skb)->frag_list;
	अगर (!list) अणु
		/* Non fragmented */
		BT_DBG("%s nonfrag skb %p len %d", hdev->name, skb, skb->len);

		skb_queue_tail(queue, skb);
	पूर्ण अन्यथा अणु
		/* Fragmented */
		BT_DBG("%s frag %p len %d", hdev->name, skb, skb->len);

		skb_shinfo(skb)->frag_list = शून्य;

		/* Queue all fragments atomically. We need to use spin_lock_bh
		 * here because of 6LoWPAN links, as there this function is
		 * called from softirq and using normal spin lock could cause
		 * deadlocks.
		 */
		spin_lock_bh(&queue->lock);

		__skb_queue_tail(queue, skb);

		flags &= ~ACL_START;
		flags |= ACL_CONT;
		करो अणु
			skb = list; list = list->next;

			hci_skb_pkt_type(skb) = HCI_ACLDATA_PKT;
			hci_add_acl_hdr(skb, conn->handle, flags);

			BT_DBG("%s frag %p len %d", hdev->name, skb, skb->len);

			__skb_queue_tail(queue, skb);
		पूर्ण जबतक (list);

		spin_unlock_bh(&queue->lock);
	पूर्ण
पूर्ण

व्योम hci_send_acl(काष्ठा hci_chan *chan, काष्ठा sk_buff *skb, __u16 flags)
अणु
	काष्ठा hci_dev *hdev = chan->conn->hdev;

	BT_DBG("%s chan %p flags 0x%4.4x", hdev->name, chan, flags);

	hci_queue_acl(chan, &chan->data_q, skb, flags);

	queue_work(hdev->workqueue, &hdev->tx_work);
पूर्ण

/* Send SCO data */
व्योम hci_send_sco(काष्ठा hci_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_sco_hdr hdr;

	BT_DBG("%s len %d", hdev->name, skb->len);

	hdr.handle = cpu_to_le16(conn->handle);
	hdr.dlen   = skb->len;

	skb_push(skb, HCI_SCO_HDR_SIZE);
	skb_reset_transport_header(skb);
	स_नकल(skb_transport_header(skb), &hdr, HCI_SCO_HDR_SIZE);

	hci_skb_pkt_type(skb) = HCI_SCODATA_PKT;

	skb_queue_tail(&conn->data_q, skb);
	queue_work(hdev->workqueue, &hdev->tx_work);
पूर्ण

/* ---- HCI TX task (outgoing data) ---- */

/* HCI Connection scheduler */
अटल काष्ठा hci_conn *hci_low_sent(काष्ठा hci_dev *hdev, __u8 type,
				     पूर्णांक *quote)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *conn = शून्य, *c;
	अचिन्हित पूर्णांक num = 0, min = ~0;

	/* We करोn't have to lock device here. Connections are always
	 * added and हटाओd with TX task disabled. */

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type != type || skb_queue_empty(&c->data_q))
			जारी;

		अगर (c->state != BT_CONNECTED && c->state != BT_CONFIG)
			जारी;

		num++;

		अगर (c->sent < min) अणु
			min  = c->sent;
			conn = c;
		पूर्ण

		अगर (hci_conn_num(hdev, type) == num)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (conn) अणु
		पूर्णांक cnt, q;

		चयन (conn->type) अणु
		हाल ACL_LINK:
			cnt = hdev->acl_cnt;
			अवरोध;
		हाल SCO_LINK:
		हाल ESCO_LINK:
			cnt = hdev->sco_cnt;
			अवरोध;
		हाल LE_LINK:
			cnt = hdev->le_mtu ? hdev->le_cnt : hdev->acl_cnt;
			अवरोध;
		शेष:
			cnt = 0;
			bt_dev_err(hdev, "unknown link type %d", conn->type);
		पूर्ण

		q = cnt / num;
		*quote = q ? q : 1;
	पूर्ण अन्यथा
		*quote = 0;

	BT_DBG("conn %p quote %d", conn, *quote);
	वापस conn;
पूर्ण

अटल व्योम hci_link_tx_to(काष्ठा hci_dev *hdev, __u8 type)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *c;

	bt_dev_err(hdev, "link tx timeout");

	rcu_पढ़ो_lock();

	/* Kill stalled connections */
	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type == type && c->sent) अणु
			bt_dev_err(hdev, "killing stalled connection %pMR",
				   &c->dst);
			hci_disconnect(c, HCI_ERROR_REMOTE_USER_TERM);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा hci_chan *hci_chan_sent(काष्ठा hci_dev *hdev, __u8 type,
				      पूर्णांक *quote)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_chan *chan = शून्य;
	अचिन्हित पूर्णांक num = 0, min = ~0, cur_prio = 0;
	काष्ठा hci_conn *conn;
	पूर्णांक cnt, q, conn_num = 0;

	BT_DBG("%s", hdev->name);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(conn, &h->list, list) अणु
		काष्ठा hci_chan *पंचांगp;

		अगर (conn->type != type)
			जारी;

		अगर (conn->state != BT_CONNECTED && conn->state != BT_CONFIG)
			जारी;

		conn_num++;

		list_क्रम_each_entry_rcu(पंचांगp, &conn->chan_list, list) अणु
			काष्ठा sk_buff *skb;

			अगर (skb_queue_empty(&पंचांगp->data_q))
				जारी;

			skb = skb_peek(&पंचांगp->data_q);
			अगर (skb->priority < cur_prio)
				जारी;

			अगर (skb->priority > cur_prio) अणु
				num = 0;
				min = ~0;
				cur_prio = skb->priority;
			पूर्ण

			num++;

			अगर (conn->sent < min) अणु
				min  = conn->sent;
				chan = पंचांगp;
			पूर्ण
		पूर्ण

		अगर (hci_conn_num(hdev, type) == conn_num)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (!chan)
		वापस शून्य;

	चयन (chan->conn->type) अणु
	हाल ACL_LINK:
		cnt = hdev->acl_cnt;
		अवरोध;
	हाल AMP_LINK:
		cnt = hdev->block_cnt;
		अवरोध;
	हाल SCO_LINK:
	हाल ESCO_LINK:
		cnt = hdev->sco_cnt;
		अवरोध;
	हाल LE_LINK:
		cnt = hdev->le_mtu ? hdev->le_cnt : hdev->acl_cnt;
		अवरोध;
	शेष:
		cnt = 0;
		bt_dev_err(hdev, "unknown link type %d", chan->conn->type);
	पूर्ण

	q = cnt / num;
	*quote = q ? q : 1;
	BT_DBG("chan %p quote %d", chan, *quote);
	वापस chan;
पूर्ण

अटल व्योम hci_prio_recalculate(काष्ठा hci_dev *hdev, __u8 type)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *conn;
	पूर्णांक num = 0;

	BT_DBG("%s", hdev->name);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(conn, &h->list, list) अणु
		काष्ठा hci_chan *chan;

		अगर (conn->type != type)
			जारी;

		अगर (conn->state != BT_CONNECTED && conn->state != BT_CONFIG)
			जारी;

		num++;

		list_क्रम_each_entry_rcu(chan, &conn->chan_list, list) अणु
			काष्ठा sk_buff *skb;

			अगर (chan->sent) अणु
				chan->sent = 0;
				जारी;
			पूर्ण

			अगर (skb_queue_empty(&chan->data_q))
				जारी;

			skb = skb_peek(&chan->data_q);
			अगर (skb->priority >= HCI_PRIO_MAX - 1)
				जारी;

			skb->priority = HCI_PRIO_MAX - 1;

			BT_DBG("chan %p skb %p promoted to %d", chan, skb,
			       skb->priority);
		पूर्ण

		अगर (hci_conn_num(hdev, type) == num)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

पूर्ण

अटल अंतरभूत पूर्णांक __get_blocks(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	/* Calculate count of blocks used by this packet */
	वापस DIV_ROUND_UP(skb->len - HCI_ACL_HDR_SIZE, hdev->block_len);
पूर्ण

अटल व्योम __check_समयout(काष्ठा hci_dev *hdev, अचिन्हित पूर्णांक cnt)
अणु
	अगर (!hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
		/* ACL tx समयout must be दीर्घer than maximum
		 * link supervision समयout (40.9 seconds) */
		अगर (!cnt && समय_after(jअगरfies, hdev->acl_last_tx +
				       HCI_ACL_TX_TIMEOUT))
			hci_link_tx_to(hdev, ACL_LINK);
	पूर्ण
पूर्ण

/* Schedule SCO */
अटल व्योम hci_sched_sco(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn *conn;
	काष्ठा sk_buff *skb;
	पूर्णांक quote;

	BT_DBG("%s", hdev->name);

	अगर (!hci_conn_num(hdev, SCO_LINK))
		वापस;

	जबतक (hdev->sco_cnt && (conn = hci_low_sent(hdev, SCO_LINK, &quote))) अणु
		जबतक (quote-- && (skb = skb_dequeue(&conn->data_q))) अणु
			BT_DBG("skb %p len %d", skb, skb->len);
			hci_send_frame(hdev, skb);

			conn->sent++;
			अगर (conn->sent == ~0)
				conn->sent = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hci_sched_esco(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn *conn;
	काष्ठा sk_buff *skb;
	पूर्णांक quote;

	BT_DBG("%s", hdev->name);

	अगर (!hci_conn_num(hdev, ESCO_LINK))
		वापस;

	जबतक (hdev->sco_cnt && (conn = hci_low_sent(hdev, ESCO_LINK,
						     &quote))) अणु
		जबतक (quote-- && (skb = skb_dequeue(&conn->data_q))) अणु
			BT_DBG("skb %p len %d", skb, skb->len);
			hci_send_frame(hdev, skb);

			conn->sent++;
			अगर (conn->sent == ~0)
				conn->sent = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hci_sched_acl_pkt(काष्ठा hci_dev *hdev)
अणु
	अचिन्हित पूर्णांक cnt = hdev->acl_cnt;
	काष्ठा hci_chan *chan;
	काष्ठा sk_buff *skb;
	पूर्णांक quote;

	__check_समयout(hdev, cnt);

	जबतक (hdev->acl_cnt &&
	       (chan = hci_chan_sent(hdev, ACL_LINK, &quote))) अणु
		u32 priority = (skb_peek(&chan->data_q))->priority;
		जबतक (quote-- && (skb = skb_peek(&chan->data_q))) अणु
			BT_DBG("chan %p skb %p len %d priority %u", chan, skb,
			       skb->len, skb->priority);

			/* Stop अगर priority has changed */
			अगर (skb->priority < priority)
				अवरोध;

			skb = skb_dequeue(&chan->data_q);

			hci_conn_enter_active_mode(chan->conn,
						   bt_cb(skb)->क्रमce_active);

			hci_send_frame(hdev, skb);
			hdev->acl_last_tx = jअगरfies;

			hdev->acl_cnt--;
			chan->sent++;
			chan->conn->sent++;

			/* Send pending SCO packets right away */
			hci_sched_sco(hdev);
			hci_sched_esco(hdev);
		पूर्ण
	पूर्ण

	अगर (cnt != hdev->acl_cnt)
		hci_prio_recalculate(hdev, ACL_LINK);
पूर्ण

अटल व्योम hci_sched_acl_blk(काष्ठा hci_dev *hdev)
अणु
	अचिन्हित पूर्णांक cnt = hdev->block_cnt;
	काष्ठा hci_chan *chan;
	काष्ठा sk_buff *skb;
	पूर्णांक quote;
	u8 type;

	__check_समयout(hdev, cnt);

	BT_DBG("%s", hdev->name);

	अगर (hdev->dev_type == HCI_AMP)
		type = AMP_LINK;
	अन्यथा
		type = ACL_LINK;

	जबतक (hdev->block_cnt > 0 &&
	       (chan = hci_chan_sent(hdev, type, &quote))) अणु
		u32 priority = (skb_peek(&chan->data_q))->priority;
		जबतक (quote > 0 && (skb = skb_peek(&chan->data_q))) अणु
			पूर्णांक blocks;

			BT_DBG("chan %p skb %p len %d priority %u", chan, skb,
			       skb->len, skb->priority);

			/* Stop अगर priority has changed */
			अगर (skb->priority < priority)
				अवरोध;

			skb = skb_dequeue(&chan->data_q);

			blocks = __get_blocks(hdev, skb);
			अगर (blocks > hdev->block_cnt)
				वापस;

			hci_conn_enter_active_mode(chan->conn,
						   bt_cb(skb)->क्रमce_active);

			hci_send_frame(hdev, skb);
			hdev->acl_last_tx = jअगरfies;

			hdev->block_cnt -= blocks;
			quote -= blocks;

			chan->sent += blocks;
			chan->conn->sent += blocks;
		पूर्ण
	पूर्ण

	अगर (cnt != hdev->block_cnt)
		hci_prio_recalculate(hdev, type);
पूर्ण

अटल व्योम hci_sched_acl(काष्ठा hci_dev *hdev)
अणु
	BT_DBG("%s", hdev->name);

	/* No ACL link over BR/EDR controller */
	अगर (!hci_conn_num(hdev, ACL_LINK) && hdev->dev_type == HCI_PRIMARY)
		वापस;

	/* No AMP link over AMP controller */
	अगर (!hci_conn_num(hdev, AMP_LINK) && hdev->dev_type == HCI_AMP)
		वापस;

	चयन (hdev->flow_ctl_mode) अणु
	हाल HCI_FLOW_CTL_MODE_PACKET_BASED:
		hci_sched_acl_pkt(hdev);
		अवरोध;

	हाल HCI_FLOW_CTL_MODE_BLOCK_BASED:
		hci_sched_acl_blk(hdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hci_sched_le(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_chan *chan;
	काष्ठा sk_buff *skb;
	पूर्णांक quote, cnt, पंचांगp;

	BT_DBG("%s", hdev->name);

	अगर (!hci_conn_num(hdev, LE_LINK))
		वापस;

	cnt = hdev->le_pkts ? hdev->le_cnt : hdev->acl_cnt;

	__check_समयout(hdev, cnt);

	पंचांगp = cnt;
	जबतक (cnt && (chan = hci_chan_sent(hdev, LE_LINK, &quote))) अणु
		u32 priority = (skb_peek(&chan->data_q))->priority;
		जबतक (quote-- && (skb = skb_peek(&chan->data_q))) अणु
			BT_DBG("chan %p skb %p len %d priority %u", chan, skb,
			       skb->len, skb->priority);

			/* Stop अगर priority has changed */
			अगर (skb->priority < priority)
				अवरोध;

			skb = skb_dequeue(&chan->data_q);

			hci_send_frame(hdev, skb);
			hdev->le_last_tx = jअगरfies;

			cnt--;
			chan->sent++;
			chan->conn->sent++;

			/* Send pending SCO packets right away */
			hci_sched_sco(hdev);
			hci_sched_esco(hdev);
		पूर्ण
	पूर्ण

	अगर (hdev->le_pkts)
		hdev->le_cnt = cnt;
	अन्यथा
		hdev->acl_cnt = cnt;

	अगर (cnt != पंचांगp)
		hci_prio_recalculate(hdev, LE_LINK);
पूर्ण

अटल व्योम hci_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, tx_work);
	काष्ठा sk_buff *skb;

	BT_DBG("%s acl %d sco %d le %d", hdev->name, hdev->acl_cnt,
	       hdev->sco_cnt, hdev->le_cnt);

	अगर (!hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) अणु
		/* Schedule queues and send stuff to HCI driver */
		hci_sched_sco(hdev);
		hci_sched_esco(hdev);
		hci_sched_acl(hdev);
		hci_sched_le(hdev);
	पूर्ण

	/* Send next queued raw (unknown type) packet */
	जबतक ((skb = skb_dequeue(&hdev->raw_q)))
		hci_send_frame(hdev, skb);
पूर्ण

/* ----- HCI RX task (incoming data processing) ----- */

/* ACL data packet */
अटल व्योम hci_acldata_packet(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_acl_hdr *hdr = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;
	__u16 handle, flags;

	skb_pull(skb, HCI_ACL_HDR_SIZE);

	handle = __le16_to_cpu(hdr->handle);
	flags  = hci_flags(handle);
	handle = hci_handle(handle);

	BT_DBG("%s len %d handle 0x%4.4x flags 0x%4.4x", hdev->name, skb->len,
	       handle, flags);

	hdev->stat.acl_rx++;

	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_handle(hdev, handle);
	hci_dev_unlock(hdev);

	अगर (conn) अणु
		hci_conn_enter_active_mode(conn, BT_POWER_FORCE_ACTIVE_OFF);

		/* Send to upper protocol */
		l2cap_recv_acldata(conn, skb, flags);
		वापस;
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "ACL packet for unknown connection handle %d",
			   handle);
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

/* SCO data packet */
अटल व्योम hci_scodata_packet(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_sco_hdr *hdr = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;
	__u16 handle, flags;

	skb_pull(skb, HCI_SCO_HDR_SIZE);

	handle = __le16_to_cpu(hdr->handle);
	flags  = hci_flags(handle);
	handle = hci_handle(handle);

	BT_DBG("%s len %d handle 0x%4.4x flags 0x%4.4x", hdev->name, skb->len,
	       handle, flags);

	hdev->stat.sco_rx++;

	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_handle(hdev, handle);
	hci_dev_unlock(hdev);

	अगर (conn) अणु
		/* Send to upper protocol */
		bt_cb(skb)->sco.pkt_status = flags & 0x03;
		sco_recv_scodata(conn, skb);
		वापस;
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "SCO packet for unknown connection handle %d",
			   handle);
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल bool hci_req_is_complete(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = skb_peek(&hdev->cmd_q);
	अगर (!skb)
		वापस true;

	वापस (bt_cb(skb)->hci.req_flags & HCI_REQ_START);
पूर्ण

अटल व्योम hci_resend_last(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_command_hdr *sent;
	काष्ठा sk_buff *skb;
	u16 opcode;

	अगर (!hdev->sent_cmd)
		वापस;

	sent = (व्योम *) hdev->sent_cmd->data;
	opcode = __le16_to_cpu(sent->opcode);
	अगर (opcode == HCI_OP_RESET)
		वापस;

	skb = skb_clone(hdev->sent_cmd, GFP_KERNEL);
	अगर (!skb)
		वापस;

	skb_queue_head(&hdev->cmd_q, skb);
	queue_work(hdev->workqueue, &hdev->cmd_work);
पूर्ण

व्योम hci_req_cmd_complete(काष्ठा hci_dev *hdev, u16 opcode, u8 status,
			  hci_req_complete_t *req_complete,
			  hci_req_complete_skb_t *req_complete_skb)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	BT_DBG("opcode 0x%04x status 0x%02x", opcode, status);

	/* If the completed command करोesn't match the last one that was
	 * sent we need to करो special handling of it.
	 */
	अगर (!hci_sent_cmd_data(hdev, opcode)) अणु
		/* Some CSR based controllers generate a spontaneous
		 * reset complete event during init and any pending
		 * command will never be completed. In such a हाल we
		 * need to resend whatever was the last sent
		 * command.
		 */
		अगर (test_bit(HCI_INIT, &hdev->flags) && opcode == HCI_OP_RESET)
			hci_resend_last(hdev);

		वापस;
	पूर्ण

	/* If we reach this poपूर्णांक this event matches the last command sent */
	hci_dev_clear_flag(hdev, HCI_CMD_PENDING);

	/* If the command succeeded and there's still more commands in
	 * this request the request is not yet complete.
	 */
	अगर (!status && !hci_req_is_complete(hdev))
		वापस;

	/* If this was the last command in a request the complete
	 * callback would be found in hdev->sent_cmd instead of the
	 * command queue (hdev->cmd_q).
	 */
	अगर (bt_cb(hdev->sent_cmd)->hci.req_flags & HCI_REQ_SKB) अणु
		*req_complete_skb = bt_cb(hdev->sent_cmd)->hci.req_complete_skb;
		वापस;
	पूर्ण

	अगर (bt_cb(hdev->sent_cmd)->hci.req_complete) अणु
		*req_complete = bt_cb(hdev->sent_cmd)->hci.req_complete;
		वापस;
	पूर्ण

	/* Remove all pending commands beदीर्घing to this request */
	spin_lock_irqsave(&hdev->cmd_q.lock, flags);
	जबतक ((skb = __skb_dequeue(&hdev->cmd_q))) अणु
		अगर (bt_cb(skb)->hci.req_flags & HCI_REQ_START) अणु
			__skb_queue_head(&hdev->cmd_q, skb);
			अवरोध;
		पूर्ण

		अगर (bt_cb(skb)->hci.req_flags & HCI_REQ_SKB)
			*req_complete_skb = bt_cb(skb)->hci.req_complete_skb;
		अन्यथा
			*req_complete = bt_cb(skb)->hci.req_complete;
		kमुक्त_skb(skb);
	पूर्ण
	spin_unlock_irqrestore(&hdev->cmd_q.lock, flags);
पूर्ण

अटल व्योम hci_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, rx_work);
	काष्ठा sk_buff *skb;

	BT_DBG("%s", hdev->name);

	जबतक ((skb = skb_dequeue(&hdev->rx_q))) अणु
		/* Send copy to monitor */
		hci_send_to_monitor(hdev, skb);

		अगर (atomic_पढ़ो(&hdev->promisc)) अणु
			/* Send copy to the sockets */
			hci_send_to_sock(hdev, skb);
		पूर्ण

		/* If the device has been खोलोed in HCI_USER_CHANNEL,
		 * the userspace has exclusive access to device.
		 * When device is HCI_INIT, we still need to process
		 * the data packets to the driver in order
		 * to complete its setup().
		 */
		अगर (hci_dev_test_flag(hdev, HCI_USER_CHANNEL) &&
		    !test_bit(HCI_INIT, &hdev->flags)) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		अगर (test_bit(HCI_INIT, &hdev->flags)) अणु
			/* Don't process data packets in this states. */
			चयन (hci_skb_pkt_type(skb)) अणु
			हाल HCI_ACLDATA_PKT:
			हाल HCI_SCODATA_PKT:
			हाल HCI_ISODATA_PKT:
				kमुक्त_skb(skb);
				जारी;
			पूर्ण
		पूर्ण

		/* Process frame */
		चयन (hci_skb_pkt_type(skb)) अणु
		हाल HCI_EVENT_PKT:
			BT_DBG("%s Event packet", hdev->name);
			hci_event_packet(hdev, skb);
			अवरोध;

		हाल HCI_ACLDATA_PKT:
			BT_DBG("%s ACL data packet", hdev->name);
			hci_acldata_packet(hdev, skb);
			अवरोध;

		हाल HCI_SCODATA_PKT:
			BT_DBG("%s SCO data packet", hdev->name);
			hci_scodata_packet(hdev, skb);
			अवरोध;

		शेष:
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hci_cmd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, cmd_work);
	काष्ठा sk_buff *skb;

	BT_DBG("%s cmd_cnt %d cmd queued %d", hdev->name,
	       atomic_पढ़ो(&hdev->cmd_cnt), skb_queue_len(&hdev->cmd_q));

	/* Send queued commands */
	अगर (atomic_पढ़ो(&hdev->cmd_cnt)) अणु
		skb = skb_dequeue(&hdev->cmd_q);
		अगर (!skb)
			वापस;

		kमुक्त_skb(hdev->sent_cmd);

		hdev->sent_cmd = skb_clone(skb, GFP_KERNEL);
		अगर (hdev->sent_cmd) अणु
			अगर (hci_req_status_pend(hdev))
				hci_dev_set_flag(hdev, HCI_CMD_PENDING);
			atomic_dec(&hdev->cmd_cnt);
			hci_send_frame(hdev, skb);
			अगर (test_bit(HCI_RESET, &hdev->flags))
				cancel_delayed_work(&hdev->cmd_समयr);
			अन्यथा
				schedule_delayed_work(&hdev->cmd_समयr,
						      HCI_CMD_TIMEOUT);
		पूर्ण अन्यथा अणु
			skb_queue_head(&hdev->cmd_q, skb);
			queue_work(hdev->workqueue, &hdev->cmd_work);
		पूर्ण
	पूर्ण
पूर्ण
