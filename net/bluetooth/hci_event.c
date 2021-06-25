<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (c) 2000-2001, 2010, Code Aurora Forum. All rights reserved.

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

/* Bluetooth HCI event handling. */

#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "hci_request.h"
#समावेश "hci_debugfs.h"
#समावेश "a2mp.h"
#समावेश "amp.h"
#समावेश "smp.h"
#समावेश "msft.h"

#घोषणा ZERO_KEY "\x00\x00\x00\x00\x00\x00\x00\x00" \
		 "\x00\x00\x00\x00\x00\x00\x00\x00"

/* Handle HCI Event packets */

अटल व्योम hci_cc_inquiry_cancel(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb,
				  u8 *new_status)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* It is possible that we receive Inquiry Complete event right
	 * beक्रमe we receive Inquiry Cancel Command Complete event, in
	 * which हाल the latter event should have status of Command
	 * Disallowed (0x0c). This should not be treated as error, since
	 * we actually achieve what Inquiry Cancel wants to achieve,
	 * which is to end the last Inquiry session.
	 */
	अगर (status == 0x0c && !test_bit(HCI_INQUIRY, &hdev->flags)) अणु
		bt_dev_warn(hdev, "Ignoring error of Inquiry Cancel command");
		status = 0x00;
	पूर्ण

	*new_status = status;

	अगर (status)
		वापस;

	clear_bit(HCI_INQUIRY, &hdev->flags);
	smp_mb__after_atomic(); /* wake_up_bit advises about this barrier */
	wake_up_bit(&hdev->flags, HCI_INQUIRY);

	hci_dev_lock(hdev);
	/* Set discovery state to stopped अगर we're not करोing LE active
	 * scanning.
	 */
	अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
	    hdev->le_scan_type != LE_SCAN_ACTIVE)
		hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
	hci_dev_unlock(hdev);

	hci_conn_check_pending(hdev);
पूर्ण

अटल व्योम hci_cc_periodic_inq(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	hci_dev_set_flag(hdev, HCI_PERIODIC_INQ);
पूर्ण

अटल व्योम hci_cc_निकास_periodic_inq(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	hci_dev_clear_flag(hdev, HCI_PERIODIC_INQ);

	hci_conn_check_pending(hdev);
पूर्ण

अटल व्योम hci_cc_remote_name_req_cancel(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	BT_DBG("%s", hdev->name);
पूर्ण

अटल व्योम hci_cc_role_discovery(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_role_discovery *rp = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->role = rp->role;

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_link_policy(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_link_policy *rp = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->link_policy = __le16_to_cpu(rp->policy);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_link_policy(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_ग_लिखो_link_policy *rp = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LINK_POLICY);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->link_policy = get_unaligned_le16(sent + 2);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_def_link_policy(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_def_link_policy *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->link_policy = __le16_to_cpu(rp->policy);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_def_link_policy(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_DEF_LINK_POLICY);
	अगर (!sent)
		वापस;

	hdev->link_policy = get_unaligned_le16(sent);
पूर्ण

अटल व्योम hci_cc_reset(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	clear_bit(HCI_RESET, &hdev->flags);

	अगर (status)
		वापस;

	/* Reset all non-persistent flags */
	hci_dev_clear_अस्थिर_flags(hdev);

	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);

	hdev->inq_tx_घातer = HCI_TX_POWER_INVALID;
	hdev->adv_tx_घातer = HCI_TX_POWER_INVALID;

	स_रखो(hdev->adv_data, 0, माप(hdev->adv_data));
	hdev->adv_data_len = 0;

	स_रखो(hdev->scan_rsp_data, 0, माप(hdev->scan_rsp_data));
	hdev->scan_rsp_data_len = 0;

	hdev->le_scan_type = LE_SCAN_PASSIVE;

	hdev->ssp_debug_mode = 0;

	hci_bdaddr_list_clear(&hdev->le_white_list);
	hci_bdaddr_list_clear(&hdev->le_resolv_list);
पूर्ण

अटल व्योम hci_cc_पढ़ो_stored_link_key(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_stored_link_key *rp = (व्योम *)skb->data;
	काष्ठा hci_cp_पढ़ो_stored_link_key *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_READ_STORED_LINK_KEY);
	अगर (!sent)
		वापस;

	अगर (!rp->status && sent->पढ़ो_all == 0x01) अणु
		hdev->stored_max_keys = rp->max_keys;
		hdev->stored_num_keys = rp->num_keys;
	पूर्ण
पूर्ण

अटल व्योम hci_cc_delete_stored_link_key(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_delete_stored_link_key *rp = (व्योम *)skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (rp->num_keys <= hdev->stored_num_keys)
		hdev->stored_num_keys -= rp->num_keys;
	अन्यथा
		hdev->stored_num_keys = 0;
पूर्ण

अटल व्योम hci_cc_ग_लिखो_local_name(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LOCAL_NAME);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_set_local_name_complete(hdev, sent, status);
	अन्यथा अगर (!status)
		स_नकल(hdev->dev_name, sent, HCI_MAX_NAME_LENGTH);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_name(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_name *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG))
		स_नकल(hdev->dev_name, rp->name, HCI_MAX_NAME_LENGTH);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_auth_enable(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_AUTH_ENABLE);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (!status) अणु
		__u8 param = *((__u8 *) sent);

		अगर (param == AUTH_ENABLED)
			set_bit(HCI_AUTH, &hdev->flags);
		अन्यथा
			clear_bit(HCI_AUTH, &hdev->flags);
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_auth_enable_complete(hdev, status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_encrypt_mode(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	__u8 param;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_ENCRYPT_MODE);
	अगर (!sent)
		वापस;

	param = *((__u8 *) sent);

	अगर (param)
		set_bit(HCI_ENCRYPT, &hdev->flags);
	अन्यथा
		clear_bit(HCI_ENCRYPT, &hdev->flags);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_scan_enable(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	__u8 param;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SCAN_ENABLE);
	अगर (!sent)
		वापस;

	param = *((__u8 *) sent);

	hci_dev_lock(hdev);

	अगर (status) अणु
		hdev->discov_समयout = 0;
		जाओ करोne;
	पूर्ण

	अगर (param & SCAN_INQUIRY)
		set_bit(HCI_ISCAN, &hdev->flags);
	अन्यथा
		clear_bit(HCI_ISCAN, &hdev->flags);

	अगर (param & SCAN_PAGE)
		set_bit(HCI_PSCAN, &hdev->flags);
	अन्यथा
		clear_bit(HCI_PSCAN, &hdev->flags);

करोne:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_set_event_filter(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *)skb->data);
	काष्ठा hci_cp_set_event_filter *cp;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_SET_EVENT_FLT);
	अगर (!sent)
		वापस;

	cp = (काष्ठा hci_cp_set_event_filter *)sent;

	अगर (cp->flt_type == HCI_FLT_CLEAR_ALL)
		hci_dev_clear_flag(hdev, HCI_EVENT_FILTER_CONFIGURED);
	अन्यथा
		hci_dev_set_flag(hdev, HCI_EVENT_FILTER_CONFIGURED);
पूर्ण

अटल व्योम hci_cc_पढ़ो_class_of_dev(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_class_of_dev *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	स_नकल(hdev->dev_class, rp->dev_class, 3);

	BT_DBG("%s class 0x%.2x%.2x%.2x", hdev->name,
	       hdev->dev_class[2], hdev->dev_class[1], hdev->dev_class[0]);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_class_of_dev(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_CLASS_OF_DEV);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (status == 0)
		स_नकल(hdev->dev_class, sent, 3);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_set_class_of_dev_complete(hdev, sent, status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_voice_setting(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_voice_setting *rp = (व्योम *) skb->data;
	__u16 setting;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	setting = __le16_to_cpu(rp->voice_setting);

	अगर (hdev->voice_setting == setting)
		वापस;

	hdev->voice_setting = setting;

	BT_DBG("%s voice setting 0x%4.4x", hdev->name, setting);

	अगर (hdev->notअगरy)
		hdev->notअगरy(hdev, HCI_NOTIFY_VOICE_SETTING);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_voice_setting(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	__u16 setting;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_VOICE_SETTING);
	अगर (!sent)
		वापस;

	setting = get_unaligned_le16(sent);

	अगर (hdev->voice_setting == setting)
		वापस;

	hdev->voice_setting = setting;

	BT_DBG("%s voice setting 0x%4.4x", hdev->name, setting);

	अगर (hdev->notअगरy)
		hdev->notअगरy(hdev, HCI_NOTIFY_VOICE_SETTING);
पूर्ण

अटल व्योम hci_cc_पढ़ो_num_supported_iac(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_num_supported_iac *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->num_iac = rp->num_iac;

	BT_DBG("%s num iac %d", hdev->name, hdev->num_iac);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_ssp_mode(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	काष्ठा hci_cp_ग_लिखो_ssp_mode *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SSP_MODE);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (!status) अणु
		अगर (sent->mode)
			hdev->features[1][0] |= LMP_HOST_SSP;
		अन्यथा
			hdev->features[1][0] &= ~LMP_HOST_SSP;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_ssp_enable_complete(hdev, sent->mode, status);
	अन्यथा अगर (!status) अणु
		अगर (sent->mode)
			hci_dev_set_flag(hdev, HCI_SSP_ENABLED);
		अन्यथा
			hci_dev_clear_flag(hdev, HCI_SSP_ENABLED);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_sc_support(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	u8 status = *((u8 *) skb->data);
	काष्ठा hci_cp_ग_लिखो_sc_support *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SC_SUPPORT);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (!status) अणु
		अगर (sent->support)
			hdev->features[1][0] |= LMP_HOST_SC;
		अन्यथा
			hdev->features[1][0] &= ~LMP_HOST_SC;
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT) && !status) अणु
		अगर (sent->support)
			hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		अन्यथा
			hci_dev_clear_flag(hdev, HCI_SC_ENABLED);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_version(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_version *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG)) अणु
		hdev->hci_ver = rp->hci_ver;
		hdev->hci_rev = __le16_to_cpu(rp->hci_rev);
		hdev->lmp_ver = rp->lmp_ver;
		hdev->manufacturer = __le16_to_cpu(rp->manufacturer);
		hdev->lmp_subver = __le16_to_cpu(rp->lmp_subver);
	पूर्ण
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_commands(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_commands *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG))
		स_नकल(hdev->commands, rp->commands, माप(hdev->commands));
पूर्ण

अटल व्योम hci_cc_पढ़ो_auth_payload_समयout(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_auth_payload_to *rp = (व्योम *)skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->auth_payload_समयout = __le16_to_cpu(rp->समयout);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_auth_payload_समयout(काष्ठा hci_dev *hdev,
					      काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_ग_लिखो_auth_payload_to *rp = (व्योम *)skb->data;
	काष्ठा hci_conn *conn;
	व्योम *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_AUTH_PAYLOAD_TO);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->auth_payload_समयout = get_unaligned_le16(sent + 2);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_features(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_features *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	स_नकल(hdev->features, rp->features, 8);

	/* Adjust शेष settings according to features
	 * supported by device. */

	अगर (hdev->features[0][0] & LMP_3SLOT)
		hdev->pkt_type |= (HCI_DM3 | HCI_DH3);

	अगर (hdev->features[0][0] & LMP_5SLOT)
		hdev->pkt_type |= (HCI_DM5 | HCI_DH5);

	अगर (hdev->features[0][1] & LMP_HV2) अणु
		hdev->pkt_type  |= (HCI_HV2);
		hdev->esco_type |= (ESCO_HV2);
	पूर्ण

	अगर (hdev->features[0][1] & LMP_HV3) अणु
		hdev->pkt_type  |= (HCI_HV3);
		hdev->esco_type |= (ESCO_HV3);
	पूर्ण

	अगर (lmp_esco_capable(hdev))
		hdev->esco_type |= (ESCO_EV3);

	अगर (hdev->features[0][4] & LMP_EV4)
		hdev->esco_type |= (ESCO_EV4);

	अगर (hdev->features[0][4] & LMP_EV5)
		hdev->esco_type |= (ESCO_EV5);

	अगर (hdev->features[0][5] & LMP_EDR_ESCO_2M)
		hdev->esco_type |= (ESCO_2EV3);

	अगर (hdev->features[0][5] & LMP_EDR_ESCO_3M)
		hdev->esco_type |= (ESCO_3EV3);

	अगर (hdev->features[0][5] & LMP_EDR_3S_ESCO)
		hdev->esco_type |= (ESCO_2EV5 | ESCO_3EV5);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_ext_features(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_ext_features *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (hdev->max_page < rp->max_page)
		hdev->max_page = rp->max_page;

	अगर (rp->page < HCI_MAX_PAGES)
		स_नकल(hdev->features[rp->page], rp->features, 8);
पूर्ण

अटल व्योम hci_cc_पढ़ो_flow_control_mode(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_flow_control_mode *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->flow_ctl_mode = rp->mode;
पूर्ण

अटल व्योम hci_cc_पढ़ो_buffer_size(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_buffer_size *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->acl_mtu  = __le16_to_cpu(rp->acl_mtu);
	hdev->sco_mtu  = rp->sco_mtu;
	hdev->acl_pkts = __le16_to_cpu(rp->acl_max_pkt);
	hdev->sco_pkts = __le16_to_cpu(rp->sco_max_pkt);

	अगर (test_bit(HCI_QUIRK_FIXUP_BUFFER_SIZE, &hdev->quirks)) अणु
		hdev->sco_mtu  = 64;
		hdev->sco_pkts = 8;
	पूर्ण

	hdev->acl_cnt = hdev->acl_pkts;
	hdev->sco_cnt = hdev->sco_pkts;

	BT_DBG("%s acl mtu %d:%d sco mtu %d:%d", hdev->name, hdev->acl_mtu,
	       hdev->acl_pkts, hdev->sco_mtu, hdev->sco_pkts);
पूर्ण

अटल व्योम hci_cc_पढ़ो_bd_addr(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_bd_addr *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (test_bit(HCI_INIT, &hdev->flags))
		bacpy(&hdev->bdaddr, &rp->bdaddr);

	अगर (hci_dev_test_flag(hdev, HCI_SETUP))
		bacpy(&hdev->setup_addr, &rp->bdaddr);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_pairing_opts(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_pairing_opts *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG)) अणु
		hdev->pairing_opts = rp->pairing_opts;
		hdev->max_enc_key_size = rp->max_key_size;
	पूर्ण
पूर्ण

अटल व्योम hci_cc_पढ़ो_page_scan_activity(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_page_scan_activity *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (test_bit(HCI_INIT, &hdev->flags)) अणु
		hdev->page_scan_पूर्णांकerval = __le16_to_cpu(rp->पूर्णांकerval);
		hdev->page_scan_winकरोw = __le16_to_cpu(rp->winकरोw);
	पूर्ण
पूर्ण

अटल व्योम hci_cc_ग_लिखो_page_scan_activity(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	u8 status = *((u8 *) skb->data);
	काष्ठा hci_cp_ग_लिखो_page_scan_activity *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_PAGE_SCAN_ACTIVITY);
	अगर (!sent)
		वापस;

	hdev->page_scan_पूर्णांकerval = __le16_to_cpu(sent->पूर्णांकerval);
	hdev->page_scan_winकरोw = __le16_to_cpu(sent->winकरोw);
पूर्ण

अटल व्योम hci_cc_पढ़ो_page_scan_type(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_page_scan_type *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	अगर (test_bit(HCI_INIT, &hdev->flags))
		hdev->page_scan_type = rp->type;
पूर्ण

अटल व्योम hci_cc_ग_लिखो_page_scan_type(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	u8 status = *((u8 *) skb->data);
	u8 *type;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	type = hci_sent_cmd_data(hdev, HCI_OP_WRITE_PAGE_SCAN_TYPE);
	अगर (type)
		hdev->page_scan_type = *type;
पूर्ण

अटल व्योम hci_cc_पढ़ो_data_block_size(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_data_block_size *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->block_mtu = __le16_to_cpu(rp->max_acl_len);
	hdev->block_len = __le16_to_cpu(rp->block_len);
	hdev->num_blocks = __le16_to_cpu(rp->num_blocks);

	hdev->block_cnt = hdev->num_blocks;

	BT_DBG("%s blk mtu %d cnt %d len %d", hdev->name, hdev->block_mtu,
	       hdev->block_cnt, hdev->block_len);
पूर्ण

अटल व्योम hci_cc_पढ़ो_घड़ी(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_घड़ी *rp = (व्योम *) skb->data;
	काष्ठा hci_cp_पढ़ो_घड़ी *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	अगर (skb->len < माप(*rp))
		वापस;

	अगर (rp->status)
		वापस;

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_CLOCK);
	अगर (!cp)
		जाओ unlock;

	अगर (cp->which == 0x00) अणु
		hdev->घड़ी = le32_to_cpu(rp->घड़ी);
		जाओ unlock;
	पूर्ण

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn) अणु
		conn->घड़ी = le32_to_cpu(rp->घड़ी);
		conn->घड़ी_accuracy = le16_to_cpu(rp->accuracy);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_amp_info(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_amp_info *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->amp_status = rp->amp_status;
	hdev->amp_total_bw = __le32_to_cpu(rp->total_bw);
	hdev->amp_max_bw = __le32_to_cpu(rp->max_bw);
	hdev->amp_min_latency = __le32_to_cpu(rp->min_latency);
	hdev->amp_max_pdu = __le32_to_cpu(rp->max_pdu);
	hdev->amp_type = rp->amp_type;
	hdev->amp_pal_cap = __le16_to_cpu(rp->pal_cap);
	hdev->amp_assoc_size = __le16_to_cpu(rp->max_assoc_size);
	hdev->amp_be_flush_to = __le32_to_cpu(rp->be_flush_to);
	hdev->amp_max_flush_to = __le32_to_cpu(rp->max_flush_to);
पूर्ण

अटल व्योम hci_cc_पढ़ो_inq_rsp_tx_घातer(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_inq_rsp_tx_घातer *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->inq_tx_घातer = rp->tx_घातer;
पूर्ण

अटल व्योम hci_cc_पढ़ो_def_err_data_reporting(काष्ठा hci_dev *hdev,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_def_err_data_reporting *rp = (व्योम *)skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->err_data_reporting = rp->err_data_reporting;
पूर्ण

अटल व्योम hci_cc_ग_लिखो_def_err_data_reporting(काष्ठा hci_dev *hdev,
						काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *)skb->data);
	काष्ठा hci_cp_ग_लिखो_def_err_data_reporting *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WRITE_DEF_ERR_DATA_REPORTING);
	अगर (!cp)
		वापस;

	hdev->err_data_reporting = cp->err_data_reporting;
पूर्ण

अटल व्योम hci_cc_pin_code_reply(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_pin_code_reply *rp = (व्योम *) skb->data;
	काष्ठा hci_cp_pin_code_reply *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_pin_code_reply_complete(hdev, &rp->bdaddr, rp->status);

	अगर (rp->status)
		जाओ unlock;

	cp = hci_sent_cmd_data(hdev, HCI_OP_PIN_CODE_REPLY);
	अगर (!cp)
		जाओ unlock;

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);
	अगर (conn)
		conn->pin_length = cp->pin_len;

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_pin_code_neg_reply(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_pin_code_neg_reply *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_pin_code_neg_reply_complete(hdev, &rp->bdaddr,
						 rp->status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_buffer_size(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_buffer_size *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->le_mtu = __le16_to_cpu(rp->le_mtu);
	hdev->le_pkts = rp->le_max_pkt;

	hdev->le_cnt = hdev->le_pkts;

	BT_DBG("%s le mtu %d:%d", hdev->name, hdev->le_mtu, hdev->le_pkts);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_local_features(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_local_features *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	स_नकल(hdev->le_features, rp->features, 8);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_adv_tx_घातer(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_adv_tx_घातer *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->adv_tx_घातer = rp->tx_घातer;
पूर्ण

अटल व्योम hci_cc_user_confirm_reply(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_user_confirm_reply *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_confirm_reply_complete(hdev, &rp->bdaddr, ACL_LINK, 0,
						 rp->status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_user_confirm_neg_reply(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_user_confirm_reply *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_confirm_neg_reply_complete(hdev, &rp->bdaddr,
						     ACL_LINK, 0, rp->status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_user_passkey_reply(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_user_confirm_reply *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_reply_complete(hdev, &rp->bdaddr, ACL_LINK,
						 0, rp->status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_user_passkey_neg_reply(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_user_confirm_reply *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_neg_reply_complete(hdev, &rp->bdaddr,
						     ACL_LINK, 0, rp->status);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_oob_data(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_oob_data *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);
पूर्ण

अटल व्योम hci_cc_पढ़ो_local_oob_ext_data(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_oob_ext_data *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);
पूर्ण

अटल व्योम hci_cc_le_set_अक्रमom_addr(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	bdaddr_t *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_RANDOM_ADDR);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	bacpy(&hdev->अक्रमom_addr, sent);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_शेष_phy(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	काष्ठा hci_cp_le_set_शेष_phy *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_DEFAULT_PHY);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	hdev->le_tx_def_phys = cp->tx_phys;
	hdev->le_rx_def_phys = cp->rx_phys;

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_adv_set_अक्रमom_addr(काष्ठा hci_dev *hdev,
                                              काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	काष्ठा hci_cp_le_set_adv_set_अक्रम_addr *cp;
	काष्ठा adv_info *adv_instance;

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_ADV_SET_RAND_ADDR);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	अगर (!cp->handle) अणु
		/* Store in hdev क्रम instance 0 (Set adv and Directed advs) */
		bacpy(&hdev->अक्रमom_addr, &cp->bdaddr);
	पूर्ण अन्यथा अणु
		adv_instance = hci_find_adv_instance(hdev, cp->handle);
		अगर (adv_instance)
			bacpy(&adv_instance->अक्रमom_addr, &cp->bdaddr);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_transmit_घातer(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_transmit_घातer *rp = (व्योम *)skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->min_le_tx_घातer = rp->min_le_tx_घातer;
	hdev->max_le_tx_घातer = rp->max_le_tx_घातer;
पूर्ण

अटल व्योम hci_cc_le_set_adv_enable(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 *sent, status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_ADV_ENABLE);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	/* If we're करोing connection initiation as peripheral. Set a
	 * समयout in हाल something goes wrong.
	 */
	अगर (*sent) अणु
		काष्ठा hci_conn *conn;

		hci_dev_set_flag(hdev, HCI_LE_ADV);

		conn = hci_lookup_le_connect(hdev);
		अगर (conn)
			queue_delayed_work(hdev->workqueue,
					   &conn->le_conn_समयout,
					   conn->conn_समयout);
	पूर्ण अन्यथा अणु
		hci_dev_clear_flag(hdev, HCI_LE_ADV);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_ext_adv_enable(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_ext_adv_enable *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_ADV_ENABLE);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	अगर (cp->enable) अणु
		काष्ठा hci_conn *conn;

		hci_dev_set_flag(hdev, HCI_LE_ADV);

		conn = hci_lookup_le_connect(hdev);
		अगर (conn)
			queue_delayed_work(hdev->workqueue,
					   &conn->le_conn_समयout,
					   conn->conn_समयout);
	पूर्ण अन्यथा अणु
		hci_dev_clear_flag(hdev, HCI_LE_ADV);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_scan_param(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_scan_param *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_SCAN_PARAM);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	hdev->le_scan_type = cp->type;

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_ext_scan_param(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_ext_scan_params *cp;
	__u8 status = *((__u8 *) skb->data);
	काष्ठा hci_cp_le_scan_phy_params *phy_param;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_SCAN_PARAMS);
	अगर (!cp)
		वापस;

	phy_param = (व्योम *)cp->data;

	hci_dev_lock(hdev);

	hdev->le_scan_type = phy_param->type;

	hci_dev_unlock(hdev);
पूर्ण

अटल bool has_pending_adv_report(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *d = &hdev->discovery;

	वापस bacmp(&d->last_adv_addr, BDADDR_ANY);
पूर्ण

अटल व्योम clear_pending_adv_report(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *d = &hdev->discovery;

	bacpy(&d->last_adv_addr, BDADDR_ANY);
	d->last_adv_data_len = 0;
पूर्ण

अटल व्योम store_pending_adv_report(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 bdaddr_type, s8 rssi, u32 flags,
				     u8 *data, u8 len)
अणु
	काष्ठा discovery_state *d = &hdev->discovery;

	अगर (len > HCI_MAX_AD_LENGTH)
		वापस;

	bacpy(&d->last_adv_addr, bdaddr);
	d->last_adv_addr_type = bdaddr_type;
	d->last_adv_rssi = rssi;
	d->last_adv_flags = flags;
	स_नकल(d->last_adv_data, data, len);
	d->last_adv_data_len = len;
पूर्ण

अटल व्योम le_set_scan_enable_complete(काष्ठा hci_dev *hdev, u8 enable)
अणु
	hci_dev_lock(hdev);

	चयन (enable) अणु
	हाल LE_SCAN_ENABLE:
		hci_dev_set_flag(hdev, HCI_LE_SCAN);
		अगर (hdev->le_scan_type == LE_SCAN_ACTIVE)
			clear_pending_adv_report(hdev);
		अवरोध;

	हाल LE_SCAN_DISABLE:
		/* We करो this here instead of when setting DISCOVERY_STOPPED
		 * since the latter would potentially require रुकोing क्रम
		 * inquiry to stop too.
		 */
		अगर (has_pending_adv_report(hdev)) अणु
			काष्ठा discovery_state *d = &hdev->discovery;

			mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
					  d->last_adv_addr_type, शून्य,
					  d->last_adv_rssi, d->last_adv_flags,
					  d->last_adv_data,
					  d->last_adv_data_len, शून्य, 0);
		पूर्ण

		/* Cancel this समयr so that we करोn't try to disable scanning
		 * when it's alपढ़ोy disabled.
		 */
		cancel_delayed_work(&hdev->le_scan_disable);

		hci_dev_clear_flag(hdev, HCI_LE_SCAN);

		/* The HCI_LE_SCAN_INTERRUPTED flag indicates that we
		 * पूर्णांकerrupted scanning due to a connect request. Mark
		 * thereक्रमe discovery as stopped. If this was not
		 * because of a connect request advertising might have
		 * been disabled because of active scanning, so
		 * re-enable it again अगर necessary.
		 */
		अगर (hci_dev_test_and_clear_flag(hdev, HCI_LE_SCAN_INTERRUPTED))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		अन्यथा अगर (!hci_dev_test_flag(hdev, HCI_LE_ADV) &&
			 hdev->discovery.state == DISCOVERY_FINDING)
			hci_req_reenable_advertising(hdev);

		अवरोध;

	शेष:
		bt_dev_err(hdev, "use of reserved LE_Scan_Enable param %d",
			   enable);
		अवरोध;
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_set_scan_enable(काष्ठा hci_dev *hdev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_scan_enable *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_SCAN_ENABLE);
	अगर (!cp)
		वापस;

	le_set_scan_enable_complete(hdev, cp->enable);
पूर्ण

अटल व्योम hci_cc_le_set_ext_scan_enable(काष्ठा hci_dev *hdev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_ext_scan_enable *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_SCAN_ENABLE);
	अगर (!cp)
		वापस;

	le_set_scan_enable_complete(hdev, cp->enable);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_num_adv_sets(काष्ठा hci_dev *hdev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_num_supported_adv_sets *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x No of Adv sets %u", hdev->name, rp->status,
	       rp->num_of_sets);

	अगर (rp->status)
		वापस;

	hdev->le_num_of_adv_sets = rp->num_of_sets;
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_white_list_size(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_white_list_size *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x size %u", hdev->name, rp->status, rp->size);

	अगर (rp->status)
		वापस;

	hdev->le_white_list_size = rp->size;
पूर्ण

अटल व्योम hci_cc_le_clear_white_list(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	hci_bdaddr_list_clear(&hdev->le_white_list);
पूर्ण

अटल व्योम hci_cc_le_add_to_white_list(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_add_to_white_list *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_ADD_TO_WHITE_LIST);
	अगर (!sent)
		वापस;

	hci_bdaddr_list_add(&hdev->le_white_list, &sent->bdaddr,
			   sent->bdaddr_type);
पूर्ण

अटल व्योम hci_cc_le_del_from_white_list(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_del_from_white_list *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_DEL_FROM_WHITE_LIST);
	अगर (!sent)
		वापस;

	hci_bdaddr_list_del(&hdev->le_white_list, &sent->bdaddr,
			    sent->bdaddr_type);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_supported_states(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_supported_states *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	स_नकल(hdev->le_states, rp->le_states, 8);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_def_data_len(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_def_data_len *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->le_def_tx_len = le16_to_cpu(rp->tx_len);
	hdev->le_def_tx_समय = le16_to_cpu(rp->tx_समय);
पूर्ण

अटल व्योम hci_cc_le_ग_लिखो_def_data_len(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_ग_लिखो_def_data_len *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_WRITE_DEF_DATA_LEN);
	अगर (!sent)
		वापस;

	hdev->le_def_tx_len = le16_to_cpu(sent->tx_len);
	hdev->le_def_tx_समय = le16_to_cpu(sent->tx_समय);
पूर्ण

अटल व्योम hci_cc_le_add_to_resolv_list(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_add_to_resolv_list *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_ADD_TO_RESOLV_LIST);
	अगर (!sent)
		वापस;

	hci_bdaddr_list_add_with_irk(&hdev->le_resolv_list, &sent->bdaddr,
				sent->bdaddr_type, sent->peer_irk,
				sent->local_irk);
पूर्ण

अटल व्योम hci_cc_le_del_from_resolv_list(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_del_from_resolv_list *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_DEL_FROM_RESOLV_LIST);
	अगर (!sent)
		वापस;

	hci_bdaddr_list_del_with_irk(&hdev->le_resolv_list, &sent->bdaddr,
			    sent->bdaddr_type);
पूर्ण

अटल व्योम hci_cc_le_clear_resolv_list(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	hci_bdaddr_list_clear(&hdev->le_resolv_list);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_resolv_list_size(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_resolv_list_size *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x size %u", hdev->name, rp->status, rp->size);

	अगर (rp->status)
		वापस;

	hdev->le_resolv_list_size = rp->size;
पूर्ण

अटल व्योम hci_cc_le_set_addr_resolution_enable(काष्ठा hci_dev *hdev,
						काष्ठा sk_buff *skb)
अणु
	__u8 *sent, status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_ADDR_RESOLV_ENABLE);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (*sent)
		hci_dev_set_flag(hdev, HCI_LL_RPA_RESOLUTION);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_LL_RPA_RESOLUTION);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_le_पढ़ो_max_data_len(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_पढ़ो_max_data_len *rp = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hdev->le_max_tx_len = le16_to_cpu(rp->tx_len);
	hdev->le_max_tx_समय = le16_to_cpu(rp->tx_समय);
	hdev->le_max_rx_len = le16_to_cpu(rp->rx_len);
	hdev->le_max_rx_समय = le16_to_cpu(rp->rx_समय);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_le_host_supported(काष्ठा hci_dev *hdev,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_ग_लिखो_le_host_supported *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LE_HOST_SUPPORTED);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	अगर (sent->le) अणु
		hdev->features[1][0] |= LMP_HOST_LE;
		hci_dev_set_flag(hdev, HCI_LE_ENABLED);
	पूर्ण अन्यथा अणु
		hdev->features[1][0] &= ~LMP_HOST_LE;
		hci_dev_clear_flag(hdev, HCI_LE_ENABLED);
		hci_dev_clear_flag(hdev, HCI_ADVERTISING);
	पूर्ण

	अगर (sent->simul)
		hdev->features[1][0] |= LMP_HOST_LE_BREDR;
	अन्यथा
		hdev->features[1][0] &= ~LMP_HOST_LE_BREDR;

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_set_adv_param(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_le_set_adv_param *cp;
	u8 status = *((u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_ADV_PARAM);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);
	hdev->adv_addr_type = cp->own_address_type;
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_set_ext_adv_param(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_le_set_ext_adv_params *rp = (व्योम *) skb->data;
	काष्ठा hci_cp_le_set_ext_adv_params *cp;
	काष्ठा adv_info *adv_instance;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_ADV_PARAMS);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);
	hdev->adv_addr_type = cp->own_addr_type;
	अगर (!cp->handle) अणु
		/* Store in hdev क्रम instance 0 */
		hdev->adv_tx_घातer = rp->tx_घातer;
	पूर्ण अन्यथा अणु
		adv_instance = hci_find_adv_instance(hdev, cp->handle);
		अगर (adv_instance)
			adv_instance->tx_घातer = rp->tx_घातer;
	पूर्ण
	/* Update adv data as tx घातer is known now */
	hci_req_update_adv_data(hdev, cp->handle);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_rssi(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_rssi *rp = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (conn)
		conn->rssi = rp->rssi;

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_पढ़ो_tx_घातer(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_cp_पढ़ो_tx_घातer *sent;
	काष्ठा hci_rp_पढ़ो_tx_घातer *rp = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		वापस;

	sent = hci_sent_cmd_data(hdev, HCI_OP_READ_TX_POWER);
	अगर (!sent)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	अगर (!conn)
		जाओ unlock;

	चयन (sent->type) अणु
	हाल 0x00:
		conn->tx_घातer = rp->tx_घातer;
		अवरोध;
	हाल 0x01:
		conn->max_tx_घातer = rp->tx_घातer;
		अवरोध;
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cc_ग_लिखो_ssp_debug_mode(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	u8 status = *((u8 *) skb->data);
	u8 *mode;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	mode = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SSP_DEBUG_MODE);
	अगर (mode)
		hdev->ssp_debug_mode = *mode;
पूर्ण

अटल व्योम hci_cs_inquiry(काष्ठा hci_dev *hdev, __u8 status)
अणु
	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status) अणु
		hci_conn_check_pending(hdev);
		वापस;
	पूर्ण

	set_bit(HCI_INQUIRY, &hdev->flags);
पूर्ण

अटल व्योम hci_cs_create_conn(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_create_conn *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_CREATE_CONN);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);

	BT_DBG("%s bdaddr %pMR hcon %p", hdev->name, &cp->bdaddr, conn);

	अगर (status) अणु
		अगर (conn && conn->state == BT_CONNECT) अणु
			अगर (status != 0x0c || conn->attempt > 2) अणु
				conn->state = BT_CLOSED;
				hci_connect_cfm(conn, status);
				hci_conn_del(conn);
			पूर्ण अन्यथा
				conn->state = BT_CONNECT2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!conn) अणु
			conn = hci_conn_add(hdev, ACL_LINK, &cp->bdaddr,
					    HCI_ROLE_MASTER);
			अगर (!conn)
				bt_dev_err(hdev, "no memory for new connection");
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_add_sco(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_add_sco *cp;
	काष्ठा hci_conn *acl, *sco;
	__u16 handle;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ADD_SCO);
	अगर (!cp)
		वापस;

	handle = __le16_to_cpu(cp->handle);

	BT_DBG("%s handle 0x%4.4x", hdev->name, handle);

	hci_dev_lock(hdev);

	acl = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (acl) अणु
		sco = acl->link;
		अगर (sco) अणु
			sco->state = BT_CLOSED;

			hci_connect_cfm(sco, status);
			hci_conn_del(sco);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_auth_requested(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_auth_requested *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_AUTH_REQUESTED);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		अगर (conn->state == BT_CONFIG) अणु
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_set_conn_encrypt(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_set_conn_encrypt *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SET_CONN_ENCRYPT);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		अगर (conn->state == BT_CONFIG) अणु
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक hci_outgoing_auth_needed(काष्ठा hci_dev *hdev,
				    काष्ठा hci_conn *conn)
अणु
	अगर (conn->state != BT_CONFIG || !conn->out)
		वापस 0;

	अगर (conn->pending_sec_level == BT_SECURITY_SDP)
		वापस 0;

	/* Only request authentication क्रम SSP connections or non-SSP
	 * devices with sec_level MEDIUM or HIGH or अगर MITM protection
	 * is requested.
	 */
	अगर (!hci_conn_ssp_enabled(conn) && !(conn->auth_type & 0x01) &&
	    conn->pending_sec_level != BT_SECURITY_FIPS &&
	    conn->pending_sec_level != BT_SECURITY_HIGH &&
	    conn->pending_sec_level != BT_SECURITY_MEDIUM)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक hci_resolve_name(काष्ठा hci_dev *hdev,
				   काष्ठा inquiry_entry *e)
अणु
	काष्ठा hci_cp_remote_name_req cp;

	स_रखो(&cp, 0, माप(cp));

	bacpy(&cp.bdaddr, &e->data.bdaddr);
	cp.pscan_rep_mode = e->data.pscan_rep_mode;
	cp.pscan_mode = e->data.pscan_mode;
	cp.घड़ी_offset = e->data.घड़ी_offset;

	वापस hci_send_cmd(hdev, HCI_OP_REMOTE_NAME_REQ, माप(cp), &cp);
पूर्ण

अटल bool hci_resolve_next_name(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *discov = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	अगर (list_empty(&discov->resolve))
		वापस false;

	e = hci_inquiry_cache_lookup_resolve(hdev, BDADDR_ANY, NAME_NEEDED);
	अगर (!e)
		वापस false;

	अगर (hci_resolve_name(hdev, e) == 0) अणु
		e->name_state = NAME_PENDING;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hci_check_pending_name(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
				   bdaddr_t *bdaddr, u8 *name, u8 name_len)
अणु
	काष्ठा discovery_state *discov = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	/* Update the mgmt connected state अगर necessary. Be careful with
	 * conn objects that exist but are not (yet) connected however.
	 * Only those in BT_CONFIG or BT_CONNECTED states can be
	 * considered connected.
	 */
	अगर (conn &&
	    (conn->state == BT_CONFIG || conn->state == BT_CONNECTED) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, name, name_len);

	अगर (discov->state == DISCOVERY_STOPPED)
		वापस;

	अगर (discov->state == DISCOVERY_STOPPING)
		जाओ discov_complete;

	अगर (discov->state != DISCOVERY_RESOLVING)
		वापस;

	e = hci_inquiry_cache_lookup_resolve(hdev, bdaddr, NAME_PENDING);
	/* If the device was not found in a list of found devices names of which
	 * are pending. there is no need to जारी resolving a next name as it
	 * will be करोne upon receiving another Remote Name Request Complete
	 * Event */
	अगर (!e)
		वापस;

	list_del(&e->list);
	अगर (name) अणु
		e->name_state = NAME_KNOWN;
		mgmt_remote_name(hdev, bdaddr, ACL_LINK, 0x00,
				 e->data.rssi, name, name_len);
	पूर्ण अन्यथा अणु
		e->name_state = NAME_NOT_KNOWN;
	पूर्ण

	अगर (hci_resolve_next_name(hdev))
		वापस;

discov_complete:
	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
पूर्ण

अटल व्योम hci_cs_remote_name_req(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_remote_name_req *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* If successful रुको क्रम the name req complete event beक्रमe
	 * checking क्रम the need to करो authentication */
	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_REMOTE_NAME_REQ);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		hci_check_pending_name(hdev, conn, &cp->bdaddr, शून्य, 0);

	अगर (!conn)
		जाओ unlock;

	अगर (!hci_outgoing_auth_needed(hdev, conn))
		जाओ unlock;

	अगर (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_auth_requested auth_cp;

		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

		auth_cp.handle = __cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_AUTH_REQUESTED,
			     माप(auth_cp), &auth_cp);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_पढ़ो_remote_features(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_पढ़ो_remote_features *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_REMOTE_FEATURES);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		अगर (conn->state == BT_CONFIG) अणु
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_पढ़ो_remote_ext_features(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_पढ़ो_remote_ext_features *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_REMOTE_EXT_FEATURES);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		अगर (conn->state == BT_CONFIG) अणु
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_setup_sync_conn(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_setup_sync_conn *cp;
	काष्ठा hci_conn *acl, *sco;
	__u16 handle;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SETUP_SYNC_CONN);
	अगर (!cp)
		वापस;

	handle = __le16_to_cpu(cp->handle);

	BT_DBG("%s handle 0x%4.4x", hdev->name, handle);

	hci_dev_lock(hdev);

	acl = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (acl) अणु
		sco = acl->link;
		अगर (sco) अणु
			sco->state = BT_CLOSED;

			hci_connect_cfm(sco, status);
			hci_conn_del(sco);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_snअगरf_mode(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_snअगरf_mode *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SNIFF_MODE);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		clear_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags);

		अगर (test_and_clear_bit(HCI_CONN_SCO_SETUP_PEND, &conn->flags))
			hci_sco_setup(conn, status);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_निकास_snअगरf_mode(काष्ठा hci_dev *hdev, __u8 status)
अणु
	काष्ठा hci_cp_निकास_snअगरf_mode *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_EXIT_SNIFF_MODE);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		clear_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags);

		अगर (test_and_clear_bit(HCI_CONN_SCO_SETUP_PEND, &conn->flags))
			hci_sco_setup(conn, status);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_disconnect(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_disconnect *cp;
	काष्ठा hci_conn *conn;

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_DISCONNECT);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		u8 type = conn->type;

		mgmt_disconnect_failed(hdev, &conn->dst, conn->type,
				       conn->dst_type, status);

		/* If the disconnection failed क्रम any reason, the upper layer
		 * करोes not retry to disconnect in current implementation.
		 * Hence, we need to करो some basic cleanup here and re-enable
		 * advertising अगर necessary.
		 */
		hci_conn_del(conn);
		अगर (type == LE_LINK)
			hci_req_reenable_advertising(hdev);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम cs_le_create_conn(काष्ठा hci_dev *hdev, bdaddr_t *peer_addr,
			      u8 peer_addr_type, u8 own_address_type,
			      u8 filter_policy)
अणु
	काष्ठा hci_conn *conn;

	conn = hci_conn_hash_lookup_le(hdev, peer_addr,
				       peer_addr_type);
	अगर (!conn)
		वापस;

	/* When using controller based address resolution, then the new
	 * address types 0x02 and 0x03 are used. These types need to be
	 * converted back पूर्णांकo either खुला address or अक्रमom address type
	 */
	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_LL_RPA_RESOLUTION)) अणु
		चयन (own_address_type) अणु
		हाल ADDR_LE_DEV_PUBLIC_RESOLVED:
			own_address_type = ADDR_LE_DEV_PUBLIC;
			अवरोध;
		हाल ADDR_LE_DEV_RANDOM_RESOLVED:
			own_address_type = ADDR_LE_DEV_RANDOM;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Store the initiator and responder address inक्रमmation which
	 * is needed क्रम SMP. These values will not change during the
	 * lअगरeसमय of the connection.
	 */
	conn->init_addr_type = own_address_type;
	अगर (own_address_type == ADDR_LE_DEV_RANDOM)
		bacpy(&conn->init_addr, &hdev->अक्रमom_addr);
	अन्यथा
		bacpy(&conn->init_addr, &hdev->bdaddr);

	conn->resp_addr_type = peer_addr_type;
	bacpy(&conn->resp_addr, peer_addr);

	/* We करोn't want the connection attempt to stick around
	 * indefinitely since LE करोesn't have a page समयout concept
	 * like BR/EDR. Set a समयr क्रम any connection that करोesn't use
	 * the white list क्रम connecting.
	 */
	अगर (filter_policy == HCI_LE_USE_PEER_ADDR)
		queue_delayed_work(conn->hdev->workqueue,
				   &conn->le_conn_समयout,
				   conn->conn_समयout);
पूर्ण

अटल व्योम hci_cs_le_create_conn(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_le_create_conn *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* All connection failure handling is taken care of by the
	 * hci_le_conn_failed function which is triggered by the HCI
	 * request completion callbacks used क्रम connecting.
	 */
	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_CREATE_CONN);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	cs_le_create_conn(hdev, &cp->peer_addr, cp->peer_addr_type,
			  cp->own_address_type, cp->filter_policy);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_le_ext_create_conn(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_le_ext_create_conn *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* All connection failure handling is taken care of by the
	 * hci_le_conn_failed function which is triggered by the HCI
	 * request completion callbacks used क्रम connecting.
	 */
	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_EXT_CREATE_CONN);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	cs_le_create_conn(hdev, &cp->peer_addr, cp->peer_addr_type,
			  cp->own_addr_type, cp->filter_policy);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_le_पढ़ो_remote_features(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_le_पढ़ो_remote_features *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_READ_REMOTE_FEATURES);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (conn) अणु
		अगर (conn->state == BT_CONFIG) अणु
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_le_start_enc(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_le_start_enc *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_START_ENC);
	अगर (!cp)
		जाओ unlock;

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (conn->state != BT_CONNECTED)
		जाओ unlock;

	hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
	hci_conn_drop(conn);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cs_चयन_role(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा hci_cp_चयन_role *cp;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (!status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SWITCH_ROLE);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);
	अगर (conn)
		clear_bit(HCI_CONN_RSWITCH_PEND, &conn->flags);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_inquiry_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	__u8 status = *((__u8 *) skb->data);
	काष्ठा discovery_state *discov = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	hci_conn_check_pending(hdev);

	अगर (!test_and_clear_bit(HCI_INQUIRY, &hdev->flags))
		वापस;

	smp_mb__after_atomic(); /* wake_up_bit advises about this barrier */
	wake_up_bit(&hdev->flags, HCI_INQUIRY);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		वापस;

	hci_dev_lock(hdev);

	अगर (discov->state != DISCOVERY_FINDING)
		जाओ unlock;

	अगर (list_empty(&discov->resolve)) अणु
		/* When BR/EDR inquiry is active and no LE scanning is in
		 * progress, then change discovery state to indicate completion.
		 *
		 * When running LE scanning and BR/EDR inquiry simultaneously
		 * and the LE scan alपढ़ोy finished, then change the discovery
		 * state to indicate completion.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
		    !test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		जाओ unlock;
	पूर्ण

	e = hci_inquiry_cache_lookup_resolve(hdev, BDADDR_ANY, NAME_NEEDED);
	अगर (e && hci_resolve_name(hdev, e) == 0) अणु
		e->name_state = NAME_PENDING;
		hci_discovery_set_state(hdev, DISCOVERY_RESOLVING);
	पूर्ण अन्यथा अणु
		/* When BR/EDR inquiry is active and no LE scanning is in
		 * progress, then change discovery state to indicate completion.
		 *
		 * When running LE scanning and BR/EDR inquiry simultaneously
		 * and the LE scan alपढ़ोy finished, then change the discovery
		 * state to indicate completion.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
		    !test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_inquiry_result_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा inquiry_data data;
	काष्ठा inquiry_info *info = (व्योम *) (skb->data + 1);
	पूर्णांक num_rsp = *((__u8 *) skb->data);

	BT_DBG("%s num_rsp %d", hdev->name, num_rsp);

	अगर (!num_rsp || skb->len < num_rsp * माप(*info) + 1)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_PERIODIC_INQ))
		वापस;

	hci_dev_lock(hdev);

	क्रम (; num_rsp; num_rsp--, info++) अणु
		u32 flags;

		bacpy(&data.bdaddr, &info->bdaddr);
		data.pscan_rep_mode	= info->pscan_rep_mode;
		data.pscan_period_mode	= info->pscan_period_mode;
		data.pscan_mode		= info->pscan_mode;
		स_नकल(data.dev_class, info->dev_class, 3);
		data.घड़ी_offset	= info->घड़ी_offset;
		data.rssi		= HCI_RSSI_INVALID;
		data.ssp_mode		= 0x00;

		flags = hci_inquiry_cache_update(hdev, &data, false);

		mgmt_device_found(hdev, &info->bdaddr, ACL_LINK, 0x00,
				  info->dev_class, HCI_RSSI_INVALID,
				  flags, शून्य, 0, शून्य, 0);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_conn_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_conn_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
	अगर (!conn) अणु
		/* Connection may not exist अगर स्वतः-connected. Check the bredr
		 * allowlist to see अगर this device is allowed to स्वतः connect.
		 * If link is an ACL type, create a connection class
		 * स्वतःmatically.
		 *
		 * Auto-connect will only occur अगर the event filter is
		 * programmed with a given address. Right now, event filter is
		 * only used during suspend.
		 */
		अगर (ev->link_type == ACL_LINK &&
		    hci_bdaddr_list_lookup_with_flags(&hdev->whitelist,
						      &ev->bdaddr,
						      BDADDR_BREDR)) अणु
			conn = hci_conn_add(hdev, ev->link_type, &ev->bdaddr,
					    HCI_ROLE_SLAVE);
			अगर (!conn) अणु
				bt_dev_err(hdev, "no memory for new conn");
				जाओ unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ev->link_type != SCO_LINK)
				जाओ unlock;

			conn = hci_conn_hash_lookup_ba(hdev, ESCO_LINK,
						       &ev->bdaddr);
			अगर (!conn)
				जाओ unlock;

			conn->type = SCO_LINK;
		पूर्ण
	पूर्ण

	अगर (!ev->status) अणु
		conn->handle = __le16_to_cpu(ev->handle);

		अगर (conn->type == ACL_LINK) अणु
			conn->state = BT_CONFIG;
			hci_conn_hold(conn);

			अगर (!conn->out && !hci_conn_ssp_enabled(conn) &&
			    !hci_find_link_key(hdev, &ev->bdaddr))
				conn->disc_समयout = HCI_PAIRING_TIMEOUT;
			अन्यथा
				conn->disc_समयout = HCI_DISCONN_TIMEOUT;
		पूर्ण अन्यथा
			conn->state = BT_CONNECTED;

		hci_debugfs_create_conn(conn);
		hci_conn_add_sysfs(conn);

		अगर (test_bit(HCI_AUTH, &hdev->flags))
			set_bit(HCI_CONN_AUTH, &conn->flags);

		अगर (test_bit(HCI_ENCRYPT, &hdev->flags))
			set_bit(HCI_CONN_ENCRYPT, &conn->flags);

		/* Get remote features */
		अगर (conn->type == ACL_LINK) अणु
			काष्ठा hci_cp_पढ़ो_remote_features cp;
			cp.handle = ev->handle;
			hci_send_cmd(hdev, HCI_OP_READ_REMOTE_FEATURES,
				     माप(cp), &cp);

			hci_req_update_scan(hdev);
		पूर्ण

		/* Set packet type क्रम incoming connection */
		अगर (!conn->out && hdev->hci_ver < BLUETOOTH_VER_2_0) अणु
			काष्ठा hci_cp_change_conn_ptype cp;
			cp.handle = ev->handle;
			cp.pkt_type = cpu_to_le16(conn->pkt_type);
			hci_send_cmd(hdev, HCI_OP_CHANGE_CONN_PTYPE, माप(cp),
				     &cp);
		पूर्ण
	पूर्ण अन्यथा अणु
		conn->state = BT_CLOSED;
		अगर (conn->type == ACL_LINK)
			mgmt_connect_failed(hdev, &conn->dst, conn->type,
					    conn->dst_type, ev->status);
	पूर्ण

	अगर (conn->type == ACL_LINK)
		hci_sco_setup(conn, ev->status);

	अगर (ev->status) अणु
		hci_connect_cfm(conn, ev->status);
		hci_conn_del(conn);
	पूर्ण अन्यथा अगर (ev->link_type == SCO_LINK) अणु
		चयन (conn->setting & SCO_AIRMODE_MASK) अणु
		हाल SCO_AIRMODE_CVSD:
			अगर (hdev->notअगरy)
				hdev->notअगरy(hdev, HCI_NOTIFY_ENABLE_SCO_CVSD);
			अवरोध;
		पूर्ण

		hci_connect_cfm(conn, ev->status);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);

	hci_conn_check_pending(hdev);
पूर्ण

अटल व्योम hci_reject_conn(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr)
अणु
	काष्ठा hci_cp_reject_conn_req cp;

	bacpy(&cp.bdaddr, bdaddr);
	cp.reason = HCI_ERROR_REJ_BAD_ADDR;
	hci_send_cmd(hdev, HCI_OP_REJECT_CONN_REQ, माप(cp), &cp);
पूर्ण

अटल व्योम hci_conn_request_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_conn_request *ev = (व्योम *) skb->data;
	पूर्णांक mask = hdev->link_mode;
	काष्ठा inquiry_entry *ie;
	काष्ठा hci_conn *conn;
	__u8 flags = 0;

	BT_DBG("%s bdaddr %pMR type 0x%x", hdev->name, &ev->bdaddr,
	       ev->link_type);

	mask |= hci_proto_connect_ind(hdev, &ev->bdaddr, ev->link_type,
				      &flags);

	अगर (!(mask & HCI_LM_ACCEPT)) अणु
		hci_reject_conn(hdev, &ev->bdaddr);
		वापस;
	पूर्ण

	अगर (hci_bdaddr_list_lookup(&hdev->blacklist, &ev->bdaddr,
				   BDADDR_BREDR)) अणु
		hci_reject_conn(hdev, &ev->bdaddr);
		वापस;
	पूर्ण

	/* Require HCI_CONNECTABLE or a whitelist entry to accept the
	 * connection. These features are only touched through mgmt so
	 * only करो the checks अगर HCI_MGMT is set.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_MGMT) &&
	    !hci_dev_test_flag(hdev, HCI_CONNECTABLE) &&
	    !hci_bdaddr_list_lookup_with_flags(&hdev->whitelist, &ev->bdaddr,
					       BDADDR_BREDR)) अणु
		hci_reject_conn(hdev, &ev->bdaddr);
		वापस;
	पूर्ण

	/* Connection accepted */

	hci_dev_lock(hdev);

	ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr);
	अगर (ie)
		स_नकल(ie->data.dev_class, ev->dev_class, 3);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type,
			&ev->bdaddr);
	अगर (!conn) अणु
		conn = hci_conn_add(hdev, ev->link_type, &ev->bdaddr,
				    HCI_ROLE_SLAVE);
		अगर (!conn) अणु
			bt_dev_err(hdev, "no memory for new connection");
			hci_dev_unlock(hdev);
			वापस;
		पूर्ण
	पूर्ण

	स_नकल(conn->dev_class, ev->dev_class, 3);

	hci_dev_unlock(hdev);

	अगर (ev->link_type == ACL_LINK ||
	    (!(flags & HCI_PROTO_DEFER) && !lmp_esco_capable(hdev))) अणु
		काष्ठा hci_cp_accept_conn_req cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddr, &ev->bdaddr);

		अगर (lmp_rचयन_capable(hdev) && (mask & HCI_LM_MASTER))
			cp.role = 0x00; /* Become master */
		अन्यथा
			cp.role = 0x01; /* Reमुख्य slave */

		hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_REQ, माप(cp), &cp);
	पूर्ण अन्यथा अगर (!(flags & HCI_PROTO_DEFER)) अणु
		काष्ठा hci_cp_accept_sync_conn_req cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		cp.pkt_type = cpu_to_le16(conn->pkt_type);

		cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.max_latency    = cpu_to_le16(0xffff);
		cp.content_क्रमmat = cpu_to_le16(hdev->voice_setting);
		cp.retrans_efक्रमt = 0xff;

		hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_REQ, माप(cp),
			     &cp);
	पूर्ण अन्यथा अणु
		conn->state = BT_CONNECT2;
		hci_connect_cfm(conn, 0);
	पूर्ण
पूर्ण

अटल u8 hci_to_mgmt_reason(u8 err)
अणु
	चयन (err) अणु
	हाल HCI_ERROR_CONNECTION_TIMEOUT:
		वापस MGMT_DEV_DISCONN_TIMEOUT;
	हाल HCI_ERROR_REMOTE_USER_TERM:
	हाल HCI_ERROR_REMOTE_LOW_RESOURCES:
	हाल HCI_ERROR_REMOTE_POWER_OFF:
		वापस MGMT_DEV_DISCONN_REMOTE;
	हाल HCI_ERROR_LOCAL_HOST_TERM:
		वापस MGMT_DEV_DISCONN_LOCAL_HOST;
	शेष:
		वापस MGMT_DEV_DISCONN_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम hci_disconn_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_disconn_complete *ev = (व्योम *) skb->data;
	u8 reason;
	काष्ठा hci_conn_params *params;
	काष्ठा hci_conn *conn;
	bool mgmt_connected;
	u8 type;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (ev->status) अणु
		mgmt_disconnect_failed(hdev, &conn->dst, conn->type,
				       conn->dst_type, ev->status);
		जाओ unlock;
	पूर्ण

	conn->state = BT_CLOSED;

	mgmt_connected = test_and_clear_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags);

	अगर (test_bit(HCI_CONN_AUTH_FAILURE, &conn->flags))
		reason = MGMT_DEV_DISCONN_AUTH_FAILURE;
	अन्यथा
		reason = hci_to_mgmt_reason(ev->reason);

	mgmt_device_disconnected(hdev, &conn->dst, conn->type, conn->dst_type,
				reason, mgmt_connected);

	अगर (conn->type == ACL_LINK) अणु
		अगर (test_bit(HCI_CONN_FLUSH_KEY, &conn->flags))
			hci_हटाओ_link_key(hdev, &conn->dst);

		hci_req_update_scan(hdev);
	पूर्ण

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	अगर (params) अणु
		चयन (params->स्वतः_connect) अणु
		हाल HCI_AUTO_CONN_LINK_LOSS:
			अगर (ev->reason != HCI_ERROR_CONNECTION_TIMEOUT)
				अवरोध;
			fallthrough;

		हाल HCI_AUTO_CONN_सूचीECT:
		हाल HCI_AUTO_CONN_ALWAYS:
			list_del_init(&params->action);
			list_add(&params->action, &hdev->pend_le_conns);
			hci_update_background_scan(hdev);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	type = conn->type;

	hci_disconn_cfm(conn, ev->reason);
	hci_conn_del(conn);

	/* The suspend notअगरier is रुकोing क्रम all devices to disconnect so
	 * clear the bit from pending tasks and inक्रमm the रुको queue.
	 */
	अगर (list_empty(&hdev->conn_hash.list) &&
	    test_and_clear_bit(SUSPEND_DISCONNECTING, hdev->suspend_tasks)) अणु
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण

	/* Re-enable advertising अगर necessary, since it might
	 * have been disabled by the connection. From the
	 * HCI_LE_Set_Advertise_Enable command description in
	 * the core specअगरication (v4.0):
	 * "The Controller shall जारी advertising until the Host
	 * issues an LE_Set_Advertise_Enable command with
	 * Advertising_Enable set to 0x00 (Advertising is disabled)
	 * or until a connection is created or until the Advertising
	 * is समयd out due to Directed Advertising."
	 */
	अगर (type == LE_LINK)
		hci_req_reenable_advertising(hdev);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_auth_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_auth_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (!ev->status) अणु
		clear_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		अगर (!hci_conn_ssp_enabled(conn) &&
		    test_bit(HCI_CONN_REAUTH_PEND, &conn->flags)) अणु
			bt_dev_info(hdev, "re-auth of legacy device is not possible.");
		पूर्ण अन्यथा अणु
			set_bit(HCI_CONN_AUTH, &conn->flags);
			conn->sec_level = conn->pending_sec_level;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ev->status == HCI_ERROR_PIN_OR_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		mgmt_auth_failed(conn, ev->status);
	पूर्ण

	clear_bit(HCI_CONN_AUTH_PEND, &conn->flags);
	clear_bit(HCI_CONN_REAUTH_PEND, &conn->flags);

	अगर (conn->state == BT_CONFIG) अणु
		अगर (!ev->status && hci_conn_ssp_enabled(conn)) अणु
			काष्ठा hci_cp_set_conn_encrypt cp;
			cp.handle  = ev->handle;
			cp.encrypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCRYPT, माप(cp),
				     &cp);
		पूर्ण अन्यथा अणु
			conn->state = BT_CONNECTED;
			hci_connect_cfm(conn, ev->status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण अन्यथा अणु
		hci_auth_cfm(conn, ev->status);

		hci_conn_hold(conn);
		conn->disc_समयout = HCI_DISCONN_TIMEOUT;
		hci_conn_drop(conn);
	पूर्ण

	अगर (test_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags)) अणु
		अगर (!ev->status) अणु
			काष्ठा hci_cp_set_conn_encrypt cp;
			cp.handle  = ev->handle;
			cp.encrypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCRYPT, माप(cp),
				     &cp);
		पूर्ण अन्यथा अणु
			clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);
			hci_encrypt_cfm(conn, ev->status);
		पूर्ण
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_remote_name_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_remote_name *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_conn_check_pending(hdev);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		जाओ check_auth;

	अगर (ev->status == 0)
		hci_check_pending_name(hdev, conn, &ev->bdaddr, ev->name,
				       strnlen(ev->name, HCI_MAX_NAME_LENGTH));
	अन्यथा
		hci_check_pending_name(hdev, conn, &ev->bdaddr, शून्य, 0);

check_auth:
	अगर (!conn)
		जाओ unlock;

	अगर (!hci_outgoing_auth_needed(hdev, conn))
		जाओ unlock;

	अगर (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_auth_requested cp;

		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

		cp.handle = __cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_AUTH_REQUESTED, माप(cp), &cp);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम पढ़ो_enc_key_size_complete(काष्ठा hci_dev *hdev, u8 status,
				       u16 opcode, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा hci_rp_पढ़ो_enc_key_size *rp;
	काष्ठा hci_conn *conn;
	u16 handle;

	BT_DBG("%s status 0x%02x", hdev->name, status);

	अगर (!skb || skb->len < माप(*rp)) अणु
		bt_dev_err(hdev, "invalid read key size response");
		वापस;
	पूर्ण

	rp = (व्योम *)skb->data;
	handle = le16_to_cpu(rp->handle);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (!conn)
		जाओ unlock;

	/* While unexpected, the पढ़ो_enc_key_size command may fail. The most
	 * secure approach is to then assume the key size is 0 to क्रमce a
	 * disconnection.
	 */
	अगर (rp->status) अणु
		bt_dev_err(hdev, "failed to read key size for handle %u",
			   handle);
		conn->enc_key_size = 0;
	पूर्ण अन्यथा अणु
		conn->enc_key_size = rp->key_size;
	पूर्ण

	hci_encrypt_cfm(conn, 0);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_encrypt_change_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_encrypt_change *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (!ev->status) अणु
		अगर (ev->encrypt) अणु
			/* Encryption implies authentication */
			set_bit(HCI_CONN_AUTH, &conn->flags);
			set_bit(HCI_CONN_ENCRYPT, &conn->flags);
			conn->sec_level = conn->pending_sec_level;

			/* P-256 authentication key implies FIPS */
			अगर (conn->key_type == HCI_LK_AUTH_COMBINATION_P256)
				set_bit(HCI_CONN_FIPS, &conn->flags);

			अगर ((conn->type == ACL_LINK && ev->encrypt == 0x02) ||
			    conn->type == LE_LINK)
				set_bit(HCI_CONN_AES_CCM, &conn->flags);
		पूर्ण अन्यथा अणु
			clear_bit(HCI_CONN_ENCRYPT, &conn->flags);
			clear_bit(HCI_CONN_AES_CCM, &conn->flags);
		पूर्ण
	पूर्ण

	/* We should disregard the current RPA and generate a new one
	 * whenever the encryption procedure fails.
	 */
	अगर (ev->status && conn->type == LE_LINK) अणु
		hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);
		hci_adv_instances_set_rpa_expired(hdev, true);
	पूर्ण

	clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);

	/* Check link security requirements are met */
	अगर (!hci_conn_check_link_mode(conn))
		ev->status = HCI_ERROR_AUTH_FAILURE;

	अगर (ev->status && conn->state == BT_CONNECTED) अणु
		अगर (ev->status == HCI_ERROR_PIN_OR_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		/* Notअगरy upper layers so they can cleanup beक्रमe
		 * disconnecting.
		 */
		hci_encrypt_cfm(conn, ev->status);
		hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
		hci_conn_drop(conn);
		जाओ unlock;
	पूर्ण

	/* Try पढ़ोing the encryption key size क्रम encrypted ACL links */
	अगर (!ev->status && ev->encrypt && conn->type == ACL_LINK) अणु
		काष्ठा hci_cp_पढ़ो_enc_key_size cp;
		काष्ठा hci_request req;

		/* Only send HCI_Read_Encryption_Key_Size अगर the
		 * controller really supports it. If it करोesn't, assume
		 * the शेष size (16).
		 */
		अगर (!(hdev->commands[20] & 0x10)) अणु
			conn->enc_key_size = HCI_LINK_KEY_SIZE;
			जाओ notअगरy;
		पूर्ण

		hci_req_init(&req, hdev);

		cp.handle = cpu_to_le16(conn->handle);
		hci_req_add(&req, HCI_OP_READ_ENC_KEY_SIZE, माप(cp), &cp);

		अगर (hci_req_run_skb(&req, पढ़ो_enc_key_size_complete)) अणु
			bt_dev_err(hdev, "sending read key size failed");
			conn->enc_key_size = HCI_LINK_KEY_SIZE;
			जाओ notअगरy;
		पूर्ण

		जाओ unlock;
	पूर्ण

	/* Set the शेष Authenticated Payload Timeout after
	 * an LE Link is established. As per Core Spec v5.0, Vol 2, Part B
	 * Section 3.3, the HCI command WRITE_AUTH_PAYLOAD_TIMEOUT should be
	 * sent when the link is active and Encryption is enabled, the conn
	 * type can be either LE or ACL and controller must support LMP Ping.
	 * Ensure क्रम AES-CCM encryption as well.
	 */
	अगर (test_bit(HCI_CONN_ENCRYPT, &conn->flags) &&
	    test_bit(HCI_CONN_AES_CCM, &conn->flags) &&
	    ((conn->type == ACL_LINK && lmp_ping_capable(hdev)) ||
	     (conn->type == LE_LINK && (hdev->le_features[0] & HCI_LE_PING)))) अणु
		काष्ठा hci_cp_ग_लिखो_auth_payload_to cp;

		cp.handle = cpu_to_le16(conn->handle);
		cp.समयout = cpu_to_le16(hdev->auth_payload_समयout);
		hci_send_cmd(conn->hdev, HCI_OP_WRITE_AUTH_PAYLOAD_TO,
			     माप(cp), &cp);
	पूर्ण

notअगरy:
	hci_encrypt_cfm(conn, ev->status);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_change_link_key_complete_evt(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_change_link_key_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn) अणु
		अगर (!ev->status)
			set_bit(HCI_CONN_SECURE, &conn->flags);

		clear_bit(HCI_CONN_AUTH_PEND, &conn->flags);

		hci_key_change_cfm(conn, ev->status);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_remote_features_evt(काष्ठा hci_dev *hdev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_remote_features *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (!ev->status)
		स_नकल(conn->features[0], ev->features, 8);

	अगर (conn->state != BT_CONFIG)
		जाओ unlock;

	अगर (!ev->status && lmp_ext_feat_capable(hdev) &&
	    lmp_ext_feat_capable(conn)) अणु
		काष्ठा hci_cp_पढ़ो_remote_ext_features cp;
		cp.handle = ev->handle;
		cp.page = 0x01;
		hci_send_cmd(hdev, HCI_OP_READ_REMOTE_EXT_FEATURES,
			     माप(cp), &cp);
		जाओ unlock;
	पूर्ण

	अगर (!ev->status && !test_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags)) अणु
		काष्ठा hci_cp_remote_name_req cp;
		स_रखो(&cp, 0, माप(cp));
		bacpy(&cp.bdaddr, &conn->dst);
		cp.pscan_rep_mode = 0x02;
		hci_send_cmd(hdev, HCI_OP_REMOTE_NAME_REQ, माप(cp), &cp);
	पूर्ण अन्यथा अगर (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, शून्य, 0);

	अगर (!hci_outgoing_auth_needed(hdev, conn)) अणु
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_cmd_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb,
				 u16 *opcode, u8 *status,
				 hci_req_complete_t *req_complete,
				 hci_req_complete_skb_t *req_complete_skb)
अणु
	काष्ठा hci_ev_cmd_complete *ev = (व्योम *) skb->data;

	*opcode = __le16_to_cpu(ev->opcode);
	*status = skb->data[माप(*ev)];

	skb_pull(skb, माप(*ev));

	चयन (*opcode) अणु
	हाल HCI_OP_INQUIRY_CANCEL:
		hci_cc_inquiry_cancel(hdev, skb, status);
		अवरोध;

	हाल HCI_OP_PERIODIC_INQ:
		hci_cc_periodic_inq(hdev, skb);
		अवरोध;

	हाल HCI_OP_EXIT_PERIODIC_INQ:
		hci_cc_निकास_periodic_inq(hdev, skb);
		अवरोध;

	हाल HCI_OP_REMOTE_NAME_REQ_CANCEL:
		hci_cc_remote_name_req_cancel(hdev, skb);
		अवरोध;

	हाल HCI_OP_ROLE_DISCOVERY:
		hci_cc_role_discovery(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LINK_POLICY:
		hci_cc_पढ़ो_link_policy(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_LINK_POLICY:
		hci_cc_ग_लिखो_link_policy(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_DEF_LINK_POLICY:
		hci_cc_पढ़ो_def_link_policy(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_DEF_LINK_POLICY:
		hci_cc_ग_लिखो_def_link_policy(hdev, skb);
		अवरोध;

	हाल HCI_OP_RESET:
		hci_cc_reset(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_STORED_LINK_KEY:
		hci_cc_पढ़ो_stored_link_key(hdev, skb);
		अवरोध;

	हाल HCI_OP_DELETE_STORED_LINK_KEY:
		hci_cc_delete_stored_link_key(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_LOCAL_NAME:
		hci_cc_ग_लिखो_local_name(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_NAME:
		hci_cc_पढ़ो_local_name(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_AUTH_ENABLE:
		hci_cc_ग_लिखो_auth_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_ENCRYPT_MODE:
		hci_cc_ग_लिखो_encrypt_mode(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_SCAN_ENABLE:
		hci_cc_ग_लिखो_scan_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_SET_EVENT_FLT:
		hci_cc_set_event_filter(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_CLASS_OF_DEV:
		hci_cc_पढ़ो_class_of_dev(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_CLASS_OF_DEV:
		hci_cc_ग_लिखो_class_of_dev(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_VOICE_SETTING:
		hci_cc_पढ़ो_voice_setting(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_VOICE_SETTING:
		hci_cc_ग_लिखो_voice_setting(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_NUM_SUPPORTED_IAC:
		hci_cc_पढ़ो_num_supported_iac(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_SSP_MODE:
		hci_cc_ग_लिखो_ssp_mode(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_SC_SUPPORT:
		hci_cc_ग_लिखो_sc_support(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_AUTH_PAYLOAD_TO:
		hci_cc_पढ़ो_auth_payload_समयout(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_AUTH_PAYLOAD_TO:
		hci_cc_ग_लिखो_auth_payload_समयout(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_VERSION:
		hci_cc_पढ़ो_local_version(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_COMMANDS:
		hci_cc_पढ़ो_local_commands(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_FEATURES:
		hci_cc_पढ़ो_local_features(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_EXT_FEATURES:
		hci_cc_पढ़ो_local_ext_features(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_BUFFER_SIZE:
		hci_cc_पढ़ो_buffer_size(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_BD_ADDR:
		hci_cc_पढ़ो_bd_addr(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_PAIRING_OPTS:
		hci_cc_पढ़ो_local_pairing_opts(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_PAGE_SCAN_ACTIVITY:
		hci_cc_पढ़ो_page_scan_activity(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_PAGE_SCAN_ACTIVITY:
		hci_cc_ग_लिखो_page_scan_activity(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_PAGE_SCAN_TYPE:
		hci_cc_पढ़ो_page_scan_type(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_PAGE_SCAN_TYPE:
		hci_cc_ग_लिखो_page_scan_type(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_DATA_BLOCK_SIZE:
		hci_cc_पढ़ो_data_block_size(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_FLOW_CONTROL_MODE:
		hci_cc_पढ़ो_flow_control_mode(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_AMP_INFO:
		hci_cc_पढ़ो_local_amp_info(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_CLOCK:
		hci_cc_पढ़ो_घड़ी(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_INQ_RSP_TX_POWER:
		hci_cc_पढ़ो_inq_rsp_tx_घातer(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_DEF_ERR_DATA_REPORTING:
		hci_cc_पढ़ो_def_err_data_reporting(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_DEF_ERR_DATA_REPORTING:
		hci_cc_ग_लिखो_def_err_data_reporting(hdev, skb);
		अवरोध;

	हाल HCI_OP_PIN_CODE_REPLY:
		hci_cc_pin_code_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_PIN_CODE_NEG_REPLY:
		hci_cc_pin_code_neg_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_OOB_DATA:
		hci_cc_पढ़ो_local_oob_data(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_LOCAL_OOB_EXT_DATA:
		hci_cc_पढ़ो_local_oob_ext_data(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_BUFFER_SIZE:
		hci_cc_le_पढ़ो_buffer_size(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_LOCAL_FEATURES:
		hci_cc_le_पढ़ो_local_features(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_ADV_TX_POWER:
		hci_cc_le_पढ़ो_adv_tx_घातer(hdev, skb);
		अवरोध;

	हाल HCI_OP_USER_CONFIRM_REPLY:
		hci_cc_user_confirm_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_USER_CONFIRM_NEG_REPLY:
		hci_cc_user_confirm_neg_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_USER_PASSKEY_REPLY:
		hci_cc_user_passkey_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_USER_PASSKEY_NEG_REPLY:
		hci_cc_user_passkey_neg_reply(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_RANDOM_ADDR:
		hci_cc_le_set_अक्रमom_addr(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_ADV_ENABLE:
		hci_cc_le_set_adv_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_SCAN_PARAM:
		hci_cc_le_set_scan_param(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_SCAN_ENABLE:
		hci_cc_le_set_scan_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_WHITE_LIST_SIZE:
		hci_cc_le_पढ़ो_white_list_size(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_CLEAR_WHITE_LIST:
		hci_cc_le_clear_white_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_ADD_TO_WHITE_LIST:
		hci_cc_le_add_to_white_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_DEL_FROM_WHITE_LIST:
		hci_cc_le_del_from_white_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_SUPPORTED_STATES:
		hci_cc_le_पढ़ो_supported_states(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_DEF_DATA_LEN:
		hci_cc_le_पढ़ो_def_data_len(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_WRITE_DEF_DATA_LEN:
		hci_cc_le_ग_लिखो_def_data_len(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_ADD_TO_RESOLV_LIST:
		hci_cc_le_add_to_resolv_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_DEL_FROM_RESOLV_LIST:
		hci_cc_le_del_from_resolv_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_CLEAR_RESOLV_LIST:
		hci_cc_le_clear_resolv_list(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_RESOLV_LIST_SIZE:
		hci_cc_le_पढ़ो_resolv_list_size(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_ADDR_RESOLV_ENABLE:
		hci_cc_le_set_addr_resolution_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_MAX_DATA_LEN:
		hci_cc_le_पढ़ो_max_data_len(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_LE_HOST_SUPPORTED:
		hci_cc_ग_लिखो_le_host_supported(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_ADV_PARAM:
		hci_cc_set_adv_param(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_RSSI:
		hci_cc_पढ़ो_rssi(hdev, skb);
		अवरोध;

	हाल HCI_OP_READ_TX_POWER:
		hci_cc_पढ़ो_tx_घातer(hdev, skb);
		अवरोध;

	हाल HCI_OP_WRITE_SSP_DEBUG_MODE:
		hci_cc_ग_लिखो_ssp_debug_mode(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_EXT_SCAN_PARAMS:
		hci_cc_le_set_ext_scan_param(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_EXT_SCAN_ENABLE:
		hci_cc_le_set_ext_scan_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_DEFAULT_PHY:
		hci_cc_le_set_शेष_phy(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_NUM_SUPPORTED_ADV_SETS:
		hci_cc_le_पढ़ो_num_adv_sets(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_EXT_ADV_PARAMS:
		hci_cc_set_ext_adv_param(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_EXT_ADV_ENABLE:
		hci_cc_le_set_ext_adv_enable(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_SET_ADV_SET_RAND_ADDR:
		hci_cc_le_set_adv_set_अक्रमom_addr(hdev, skb);
		अवरोध;

	हाल HCI_OP_LE_READ_TRANSMIT_POWER:
		hci_cc_le_पढ़ो_transmit_घातer(hdev, skb);
		अवरोध;

	शेष:
		BT_DBG("%s opcode 0x%4.4x", hdev->name, *opcode);
		अवरोध;
	पूर्ण

	अगर (*opcode != HCI_OP_NOP)
		cancel_delayed_work(&hdev->cmd_समयr);

	अगर (ev->ncmd && !test_bit(HCI_RESET, &hdev->flags))
		atomic_set(&hdev->cmd_cnt, 1);

	hci_req_cmd_complete(hdev, *opcode, *status, req_complete,
			     req_complete_skb);

	अगर (hci_dev_test_flag(hdev, HCI_CMD_PENDING)) अणु
		bt_dev_err(hdev,
			   "unexpected event for opcode 0x%4.4x", *opcode);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_work(hdev->workqueue, &hdev->cmd_work);
पूर्ण

अटल व्योम hci_cmd_status_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb,
			       u16 *opcode, u8 *status,
			       hci_req_complete_t *req_complete,
			       hci_req_complete_skb_t *req_complete_skb)
अणु
	काष्ठा hci_ev_cmd_status *ev = (व्योम *) skb->data;

	skb_pull(skb, माप(*ev));

	*opcode = __le16_to_cpu(ev->opcode);
	*status = ev->status;

	चयन (*opcode) अणु
	हाल HCI_OP_INQUIRY:
		hci_cs_inquiry(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_CREATE_CONN:
		hci_cs_create_conn(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_DISCONNECT:
		hci_cs_disconnect(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_ADD_SCO:
		hci_cs_add_sco(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_AUTH_REQUESTED:
		hci_cs_auth_requested(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_SET_CONN_ENCRYPT:
		hci_cs_set_conn_encrypt(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_REMOTE_NAME_REQ:
		hci_cs_remote_name_req(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_READ_REMOTE_FEATURES:
		hci_cs_पढ़ो_remote_features(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_READ_REMOTE_EXT_FEATURES:
		hci_cs_पढ़ो_remote_ext_features(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_SETUP_SYNC_CONN:
		hci_cs_setup_sync_conn(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_SNIFF_MODE:
		hci_cs_snअगरf_mode(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_EXIT_SNIFF_MODE:
		hci_cs_निकास_snअगरf_mode(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_SWITCH_ROLE:
		hci_cs_चयन_role(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_LE_CREATE_CONN:
		hci_cs_le_create_conn(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_LE_READ_REMOTE_FEATURES:
		hci_cs_le_पढ़ो_remote_features(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_LE_START_ENC:
		hci_cs_le_start_enc(hdev, ev->status);
		अवरोध;

	हाल HCI_OP_LE_EXT_CREATE_CONN:
		hci_cs_le_ext_create_conn(hdev, ev->status);
		अवरोध;

	शेष:
		BT_DBG("%s opcode 0x%4.4x", hdev->name, *opcode);
		अवरोध;
	पूर्ण

	अगर (*opcode != HCI_OP_NOP)
		cancel_delayed_work(&hdev->cmd_समयr);

	अगर (ev->ncmd && !test_bit(HCI_RESET, &hdev->flags))
		atomic_set(&hdev->cmd_cnt, 1);

	/* Indicate request completion अगर the command failed. Also, अगर
	 * we're not रुकोing क्रम a special event and we get a success
	 * command status we should try to flag the request as completed
	 * (since क्रम this kind of commands there will not be a command
	 * complete event).
	 */
	अगर (ev->status ||
	    (hdev->sent_cmd && !bt_cb(hdev->sent_cmd)->hci.req_event))
		hci_req_cmd_complete(hdev, *opcode, ev->status, req_complete,
				     req_complete_skb);

	अगर (hci_dev_test_flag(hdev, HCI_CMD_PENDING)) अणु
		bt_dev_err(hdev,
			   "unexpected event for opcode 0x%4.4x", *opcode);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_work(hdev->workqueue, &hdev->cmd_work);
पूर्ण

अटल व्योम hci_hardware_error_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_hardware_error *ev = (व्योम *) skb->data;

	hdev->hw_error_code = ev->code;

	queue_work(hdev->req_workqueue, &hdev->error_reset);
पूर्ण

अटल व्योम hci_role_change_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_role_change *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (conn) अणु
		अगर (!ev->status)
			conn->role = ev->role;

		clear_bit(HCI_CONN_RSWITCH_PEND, &conn->flags);

		hci_role_चयन_cfm(conn, ev->status, ev->role);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_num_comp_pkts_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_num_comp_pkts *ev = (व्योम *) skb->data;
	पूर्णांक i;

	अगर (hdev->flow_ctl_mode != HCI_FLOW_CTL_MODE_PACKET_BASED) अणु
		bt_dev_err(hdev, "wrong event for mode %d", hdev->flow_ctl_mode);
		वापस;
	पूर्ण

	अगर (skb->len < माप(*ev) ||
	    skb->len < काष्ठा_size(ev, handles, ev->num_hndl)) अणु
		BT_DBG("%s bad parameters", hdev->name);
		वापस;
	पूर्ण

	BT_DBG("%s num_hndl %d", hdev->name, ev->num_hndl);

	क्रम (i = 0; i < ev->num_hndl; i++) अणु
		काष्ठा hci_comp_pkts_info *info = &ev->handles[i];
		काष्ठा hci_conn *conn;
		__u16  handle, count;

		handle = __le16_to_cpu(info->handle);
		count  = __le16_to_cpu(info->count);

		conn = hci_conn_hash_lookup_handle(hdev, handle);
		अगर (!conn)
			जारी;

		conn->sent -= count;

		चयन (conn->type) अणु
		हाल ACL_LINK:
			hdev->acl_cnt += count;
			अगर (hdev->acl_cnt > hdev->acl_pkts)
				hdev->acl_cnt = hdev->acl_pkts;
			अवरोध;

		हाल LE_LINK:
			अगर (hdev->le_pkts) अणु
				hdev->le_cnt += count;
				अगर (hdev->le_cnt > hdev->le_pkts)
					hdev->le_cnt = hdev->le_pkts;
			पूर्ण अन्यथा अणु
				hdev->acl_cnt += count;
				अगर (hdev->acl_cnt > hdev->acl_pkts)
					hdev->acl_cnt = hdev->acl_pkts;
			पूर्ण
			अवरोध;

		हाल SCO_LINK:
			hdev->sco_cnt += count;
			अगर (hdev->sco_cnt > hdev->sco_pkts)
				hdev->sco_cnt = hdev->sco_pkts;
			अवरोध;

		शेष:
			bt_dev_err(hdev, "unknown type %d conn %p",
				   conn->type, conn);
			अवरोध;
		पूर्ण
	पूर्ण

	queue_work(hdev->workqueue, &hdev->tx_work);
पूर्ण

अटल काष्ठा hci_conn *__hci_conn_lookup_handle(काष्ठा hci_dev *hdev,
						 __u16 handle)
अणु
	काष्ठा hci_chan *chan;

	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		वापस hci_conn_hash_lookup_handle(hdev, handle);
	हाल HCI_AMP:
		chan = hci_chan_lookup_handle(hdev, handle);
		अगर (chan)
			वापस chan->conn;
		अवरोध;
	शेष:
		bt_dev_err(hdev, "unknown dev_type %d", hdev->dev_type);
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hci_num_comp_blocks_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_num_comp_blocks *ev = (व्योम *) skb->data;
	पूर्णांक i;

	अगर (hdev->flow_ctl_mode != HCI_FLOW_CTL_MODE_BLOCK_BASED) अणु
		bt_dev_err(hdev, "wrong event for mode %d", hdev->flow_ctl_mode);
		वापस;
	पूर्ण

	अगर (skb->len < माप(*ev) ||
	    skb->len < काष्ठा_size(ev, handles, ev->num_hndl)) अणु
		BT_DBG("%s bad parameters", hdev->name);
		वापस;
	पूर्ण

	BT_DBG("%s num_blocks %d num_hndl %d", hdev->name, ev->num_blocks,
	       ev->num_hndl);

	क्रम (i = 0; i < ev->num_hndl; i++) अणु
		काष्ठा hci_comp_blocks_info *info = &ev->handles[i];
		काष्ठा hci_conn *conn = शून्य;
		__u16  handle, block_count;

		handle = __le16_to_cpu(info->handle);
		block_count = __le16_to_cpu(info->blocks);

		conn = __hci_conn_lookup_handle(hdev, handle);
		अगर (!conn)
			जारी;

		conn->sent -= block_count;

		चयन (conn->type) अणु
		हाल ACL_LINK:
		हाल AMP_LINK:
			hdev->block_cnt += block_count;
			अगर (hdev->block_cnt > hdev->num_blocks)
				hdev->block_cnt = hdev->num_blocks;
			अवरोध;

		शेष:
			bt_dev_err(hdev, "unknown type %d conn %p",
				   conn->type, conn);
			अवरोध;
		पूर्ण
	पूर्ण

	queue_work(hdev->workqueue, &hdev->tx_work);
पूर्ण

अटल व्योम hci_mode_change_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_mode_change *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn) अणु
		conn->mode = ev->mode;

		अगर (!test_and_clear_bit(HCI_CONN_MODE_CHANGE_PEND,
					&conn->flags)) अणु
			अगर (conn->mode == HCI_CM_ACTIVE)
				set_bit(HCI_CONN_POWER_SAVE, &conn->flags);
			अन्यथा
				clear_bit(HCI_CONN_POWER_SAVE, &conn->flags);
		पूर्ण

		अगर (test_and_clear_bit(HCI_CONN_SCO_SETUP_PEND, &conn->flags))
			hci_sco_setup(conn, ev->status);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_pin_code_request_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_pin_code_req *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	अगर (conn->state == BT_CONNECTED) अणु
		hci_conn_hold(conn);
		conn->disc_समयout = HCI_PAIRING_TIMEOUT;
		hci_conn_drop(conn);
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_BONDABLE) &&
	    !test_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags)) अणु
		hci_send_cmd(hdev, HCI_OP_PIN_CODE_NEG_REPLY,
			     माप(ev->bdaddr), &ev->bdaddr);
	पूर्ण अन्यथा अगर (hci_dev_test_flag(hdev, HCI_MGMT)) अणु
		u8 secure;

		अगर (conn->pending_sec_level == BT_SECURITY_HIGH)
			secure = 1;
		अन्यथा
			secure = 0;

		mgmt_pin_code_request(hdev, &ev->bdaddr, secure);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम conn_set_key(काष्ठा hci_conn *conn, u8 key_type, u8 pin_len)
अणु
	अगर (key_type == HCI_LK_CHANGED_COMBINATION)
		वापस;

	conn->pin_length = pin_len;
	conn->key_type = key_type;

	चयन (key_type) अणु
	हाल HCI_LK_LOCAL_UNIT:
	हाल HCI_LK_REMOTE_UNIT:
	हाल HCI_LK_DEBUG_COMBINATION:
		वापस;
	हाल HCI_LK_COMBINATION:
		अगर (pin_len == 16)
			conn->pending_sec_level = BT_SECURITY_HIGH;
		अन्यथा
			conn->pending_sec_level = BT_SECURITY_MEDIUM;
		अवरोध;
	हाल HCI_LK_UNAUTH_COMBINATION_P192:
	हाल HCI_LK_UNAUTH_COMBINATION_P256:
		conn->pending_sec_level = BT_SECURITY_MEDIUM;
		अवरोध;
	हाल HCI_LK_AUTH_COMBINATION_P192:
		conn->pending_sec_level = BT_SECURITY_HIGH;
		अवरोध;
	हाल HCI_LK_AUTH_COMBINATION_P256:
		conn->pending_sec_level = BT_SECURITY_FIPS;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hci_link_key_request_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_link_key_req *ev = (व्योम *) skb->data;
	काष्ठा hci_cp_link_key_reply cp;
	काष्ठा hci_conn *conn;
	काष्ठा link_key *key;

	BT_DBG("%s", hdev->name);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		वापस;

	hci_dev_lock(hdev);

	key = hci_find_link_key(hdev, &ev->bdaddr);
	अगर (!key) अणु
		BT_DBG("%s link key not found for %pMR", hdev->name,
		       &ev->bdaddr);
		जाओ not_found;
	पूर्ण

	BT_DBG("%s found key type %u for %pMR", hdev->name, key->type,
	       &ev->bdaddr);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (conn) अणु
		clear_bit(HCI_CONN_NEW_LINK_KEY, &conn->flags);

		अगर ((key->type == HCI_LK_UNAUTH_COMBINATION_P192 ||
		     key->type == HCI_LK_UNAUTH_COMBINATION_P256) &&
		    conn->auth_type != 0xff && (conn->auth_type & 0x01)) अणु
			BT_DBG("%s ignoring unauthenticated key", hdev->name);
			जाओ not_found;
		पूर्ण

		अगर (key->type == HCI_LK_COMBINATION && key->pin_len < 16 &&
		    (conn->pending_sec_level == BT_SECURITY_HIGH ||
		     conn->pending_sec_level == BT_SECURITY_FIPS)) अणु
			BT_DBG("%s ignoring key unauthenticated for high security",
			       hdev->name);
			जाओ not_found;
		पूर्ण

		conn_set_key(conn, key->type, key->pin_len);
	पूर्ण

	bacpy(&cp.bdaddr, &ev->bdaddr);
	स_नकल(cp.link_key, key->val, HCI_LINK_KEY_SIZE);

	hci_send_cmd(hdev, HCI_OP_LINK_KEY_REPLY, माप(cp), &cp);

	hci_dev_unlock(hdev);

	वापस;

not_found:
	hci_send_cmd(hdev, HCI_OP_LINK_KEY_NEG_REPLY, 6, &ev->bdaddr);
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_link_key_notअगरy_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_link_key_notअगरy *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;
	काष्ठा link_key *key;
	bool persistent;
	u8 pin_len = 0;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	hci_conn_hold(conn);
	conn->disc_समयout = HCI_DISCONN_TIMEOUT;
	hci_conn_drop(conn);

	set_bit(HCI_CONN_NEW_LINK_KEY, &conn->flags);
	conn_set_key(conn, ev->key_type, conn->pin_length);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		जाओ unlock;

	key = hci_add_link_key(hdev, conn, &ev->bdaddr, ev->link_key,
			        ev->key_type, pin_len, &persistent);
	अगर (!key)
		जाओ unlock;

	/* Update connection inक्रमmation since adding the key will have
	 * fixed up the type in the हाल of changed combination keys.
	 */
	अगर (ev->key_type == HCI_LK_CHANGED_COMBINATION)
		conn_set_key(conn, key->type, key->pin_len);

	mgmt_new_link_key(hdev, key, persistent);

	/* Keep debug keys around only अगर the HCI_KEEP_DEBUG_KEYS flag
	 * is set. If it's not set simply हटाओ the key from the kernel
	 * list (we've still notअगरied user space about it but with
	 * store_hपूर्णांक being 0).
	 */
	अगर (key->type == HCI_LK_DEBUG_COMBINATION &&
	    !hci_dev_test_flag(hdev, HCI_KEEP_DEBUG_KEYS)) अणु
		list_del_rcu(&key->list);
		kमुक्त_rcu(key, rcu);
		जाओ unlock;
	पूर्ण

	अगर (persistent)
		clear_bit(HCI_CONN_FLUSH_KEY, &conn->flags);
	अन्यथा
		set_bit(HCI_CONN_FLUSH_KEY, &conn->flags);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_घड़ी_offset_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_घड़ी_offset *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn && !ev->status) अणु
		काष्ठा inquiry_entry *ie;

		ie = hci_inquiry_cache_lookup(hdev, &conn->dst);
		अगर (ie) अणु
			ie->data.घड़ी_offset = ev->घड़ी_offset;
			ie->बारtamp = jअगरfies;
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_pkt_type_change_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_pkt_type_change *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn && !ev->status)
		conn->pkt_type = __le16_to_cpu(ev->pkt_type);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_pscan_rep_mode_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_pscan_rep_mode *ev = (व्योम *) skb->data;
	काष्ठा inquiry_entry *ie;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr);
	अगर (ie) अणु
		ie->data.pscan_rep_mode = ev->pscan_rep_mode;
		ie->बारtamp = jअगरfies;
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_inquiry_result_with_rssi_evt(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा inquiry_data data;
	पूर्णांक num_rsp = *((__u8 *) skb->data);

	BT_DBG("%s num_rsp %d", hdev->name, num_rsp);

	अगर (!num_rsp)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_PERIODIC_INQ))
		वापस;

	hci_dev_lock(hdev);

	अगर ((skb->len - 1) / num_rsp != माप(काष्ठा inquiry_info_with_rssi)) अणु
		काष्ठा inquiry_info_with_rssi_and_pscan_mode *info;
		info = (व्योम *) (skb->data + 1);

		अगर (skb->len < num_rsp * माप(*info) + 1)
			जाओ unlock;

		क्रम (; num_rsp; num_rsp--, info++) अणु
			u32 flags;

			bacpy(&data.bdaddr, &info->bdaddr);
			data.pscan_rep_mode	= info->pscan_rep_mode;
			data.pscan_period_mode	= info->pscan_period_mode;
			data.pscan_mode		= info->pscan_mode;
			स_नकल(data.dev_class, info->dev_class, 3);
			data.घड़ी_offset	= info->घड़ी_offset;
			data.rssi		= info->rssi;
			data.ssp_mode		= 0x00;

			flags = hci_inquiry_cache_update(hdev, &data, false);

			mgmt_device_found(hdev, &info->bdaddr, ACL_LINK, 0x00,
					  info->dev_class, info->rssi,
					  flags, शून्य, 0, शून्य, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा inquiry_info_with_rssi *info = (व्योम *) (skb->data + 1);

		अगर (skb->len < num_rsp * माप(*info) + 1)
			जाओ unlock;

		क्रम (; num_rsp; num_rsp--, info++) अणु
			u32 flags;

			bacpy(&data.bdaddr, &info->bdaddr);
			data.pscan_rep_mode	= info->pscan_rep_mode;
			data.pscan_period_mode	= info->pscan_period_mode;
			data.pscan_mode		= 0x00;
			स_नकल(data.dev_class, info->dev_class, 3);
			data.घड़ी_offset	= info->घड़ी_offset;
			data.rssi		= info->rssi;
			data.ssp_mode		= 0x00;

			flags = hci_inquiry_cache_update(hdev, &data, false);

			mgmt_device_found(hdev, &info->bdaddr, ACL_LINK, 0x00,
					  info->dev_class, info->rssi,
					  flags, शून्य, 0, शून्य, 0);
		पूर्ण
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_remote_ext_features_evt(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_remote_ext_features *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	अगर (ev->page < HCI_MAX_PAGES)
		स_नकल(conn->features[ev->page], ev->features, 8);

	अगर (!ev->status && ev->page == 0x01) अणु
		काष्ठा inquiry_entry *ie;

		ie = hci_inquiry_cache_lookup(hdev, &conn->dst);
		अगर (ie)
			ie->data.ssp_mode = (ev->features[0] & LMP_HOST_SSP);

		अगर (ev->features[0] & LMP_HOST_SSP) अणु
			set_bit(HCI_CONN_SSP_ENABLED, &conn->flags);
		पूर्ण अन्यथा अणु
			/* It is mandatory by the Bluetooth specअगरication that
			 * Extended Inquiry Results are only used when Secure
			 * Simple Pairing is enabled, but some devices violate
			 * this.
			 *
			 * To make these devices work, the पूर्णांकernal SSP
			 * enabled flag needs to be cleared अगर the remote host
			 * features करो not indicate SSP support */
			clear_bit(HCI_CONN_SSP_ENABLED, &conn->flags);
		पूर्ण

		अगर (ev->features[0] & LMP_HOST_SC)
			set_bit(HCI_CONN_SC_ENABLED, &conn->flags);
	पूर्ण

	अगर (conn->state != BT_CONFIG)
		जाओ unlock;

	अगर (!ev->status && !test_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags)) अणु
		काष्ठा hci_cp_remote_name_req cp;
		स_रखो(&cp, 0, माप(cp));
		bacpy(&cp.bdaddr, &conn->dst);
		cp.pscan_rep_mode = 0x02;
		hci_send_cmd(hdev, HCI_OP_REMOTE_NAME_REQ, माप(cp), &cp);
	पूर्ण अन्यथा अगर (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, शून्य, 0);

	अगर (!hci_outgoing_auth_needed(hdev, conn)) अणु
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_sync_conn_complete_evt(काष्ठा hci_dev *hdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_sync_conn_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
	अगर (!conn) अणु
		अगर (ev->link_type == ESCO_LINK)
			जाओ unlock;

		/* When the link type in the event indicates SCO connection
		 * and lookup of the connection object fails, then check
		 * अगर an eSCO connection object exists.
		 *
		 * The core limits the synchronous connections to either
		 * SCO or eSCO. The eSCO connection is preferred and tried
		 * to be setup first and until successfully established,
		 * the link type will be hपूर्णांकed as eSCO.
		 */
		conn = hci_conn_hash_lookup_ba(hdev, ESCO_LINK, &ev->bdaddr);
		अगर (!conn)
			जाओ unlock;
	पूर्ण

	चयन (ev->status) अणु
	हाल 0x00:
		conn->handle = __le16_to_cpu(ev->handle);
		conn->state  = BT_CONNECTED;
		conn->type   = ev->link_type;

		hci_debugfs_create_conn(conn);
		hci_conn_add_sysfs(conn);
		अवरोध;

	हाल 0x10:	/* Connection Accept Timeout */
	हाल 0x0d:	/* Connection Rejected due to Limited Resources */
	हाल 0x11:	/* Unsupported Feature or Parameter Value */
	हाल 0x1c:	/* SCO पूर्णांकerval rejected */
	हाल 0x1a:	/* Unsupported Remote Feature */
	हाल 0x1e:	/* Invalid LMP Parameters */
	हाल 0x1f:	/* Unspecअगरied error */
	हाल 0x20:	/* Unsupported LMP Parameter value */
		अगर (conn->out) अणु
			conn->pkt_type = (hdev->esco_type & SCO_ESCO_MASK) |
					(hdev->esco_type & EDR_ESCO_MASK);
			अगर (hci_setup_sync(conn, conn->link->handle))
				जाओ unlock;
		पूर्ण
		fallthrough;

	शेष:
		conn->state = BT_CLOSED;
		अवरोध;
	पूर्ण

	bt_dev_dbg(hdev, "SCO connected with air mode: %02x", ev->air_mode);

	चयन (conn->setting & SCO_AIRMODE_MASK) अणु
	हाल SCO_AIRMODE_CVSD:
		अगर (hdev->notअगरy)
			hdev->notअगरy(hdev, HCI_NOTIFY_ENABLE_SCO_CVSD);
		अवरोध;
	हाल SCO_AIRMODE_TRANSP:
		अगर (hdev->notअगरy)
			hdev->notअगरy(hdev, HCI_NOTIFY_ENABLE_SCO_TRANSP);
		अवरोध;
	पूर्ण

	hci_connect_cfm(conn, ev->status);
	अगर (ev->status)
		hci_conn_del(conn);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल अंतरभूत माप_प्रकार eir_get_length(u8 *eir, माप_प्रकार eir_len)
अणु
	माप_प्रकार parsed = 0;

	जबतक (parsed < eir_len) अणु
		u8 field_len = eir[0];

		अगर (field_len == 0)
			वापस parsed;

		parsed += field_len + 1;
		eir += field_len + 1;
	पूर्ण

	वापस eir_len;
पूर्ण

अटल व्योम hci_extended_inquiry_result_evt(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा inquiry_data data;
	काष्ठा extended_inquiry_info *info = (व्योम *) (skb->data + 1);
	पूर्णांक num_rsp = *((__u8 *) skb->data);
	माप_प्रकार eir_len;

	BT_DBG("%s num_rsp %d", hdev->name, num_rsp);

	अगर (!num_rsp || skb->len < num_rsp * माप(*info) + 1)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_PERIODIC_INQ))
		वापस;

	hci_dev_lock(hdev);

	क्रम (; num_rsp; num_rsp--, info++) अणु
		u32 flags;
		bool name_known;

		bacpy(&data.bdaddr, &info->bdaddr);
		data.pscan_rep_mode	= info->pscan_rep_mode;
		data.pscan_period_mode	= info->pscan_period_mode;
		data.pscan_mode		= 0x00;
		स_नकल(data.dev_class, info->dev_class, 3);
		data.घड़ी_offset	= info->घड़ी_offset;
		data.rssi		= info->rssi;
		data.ssp_mode		= 0x01;

		अगर (hci_dev_test_flag(hdev, HCI_MGMT))
			name_known = eir_get_data(info->data,
						  माप(info->data),
						  EIR_NAME_COMPLETE, शून्य);
		अन्यथा
			name_known = true;

		flags = hci_inquiry_cache_update(hdev, &data, name_known);

		eir_len = eir_get_length(info->data, माप(info->data));

		mgmt_device_found(hdev, &info->bdaddr, ACL_LINK, 0x00,
				  info->dev_class, info->rssi,
				  flags, info->data, eir_len, शून्य, 0);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_key_refresh_complete_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_key_refresh_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x handle 0x%4.4x", hdev->name, ev->status,
	       __le16_to_cpu(ev->handle));

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	/* For BR/EDR the necessary steps are taken through the
	 * auth_complete event.
	 */
	अगर (conn->type != LE_LINK)
		जाओ unlock;

	अगर (!ev->status)
		conn->sec_level = conn->pending_sec_level;

	clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);

	अगर (ev->status && conn->state == BT_CONNECTED) अणु
		hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
		hci_conn_drop(conn);
		जाओ unlock;
	पूर्ण

	अगर (conn->state == BT_CONFIG) अणु
		अगर (!ev->status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	पूर्ण अन्यथा अणु
		hci_auth_cfm(conn, ev->status);

		hci_conn_hold(conn);
		conn->disc_समयout = HCI_DISCONN_TIMEOUT;
		hci_conn_drop(conn);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल u8 hci_get_auth_req(काष्ठा hci_conn *conn)
अणु
	/* If remote requests no-bonding follow that lead */
	अगर (conn->remote_auth == HCI_AT_NO_BONDING ||
	    conn->remote_auth == HCI_AT_NO_BONDING_MITM)
		वापस conn->remote_auth | (conn->auth_type & 0x01);

	/* If both remote and local have enough IO capabilities, require
	 * MITM protection
	 */
	अगर (conn->remote_cap != HCI_IO_NO_INPUT_OUTPUT &&
	    conn->io_capability != HCI_IO_NO_INPUT_OUTPUT)
		वापस conn->remote_auth | 0x01;

	/* No MITM protection possible so ignore remote requirement */
	वापस (conn->remote_auth & ~0x01) | (conn->auth_type & 0x01);
पूर्ण

अटल u8 bredr_oob_data_present(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा oob_data *data;

	data = hci_find_remote_oob_data(hdev, &conn->dst, BDADDR_BREDR);
	अगर (!data)
		वापस 0x00;

	अगर (bredr_sc_enabled(hdev)) अणु
		/* When Secure Connections is enabled, then just
		 * वापस the present value stored with the OOB
		 * data. The stored value contains the right present
		 * inक्रमmation. However it can only be trusted when
		 * not in Secure Connection Only mode.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_SC_ONLY))
			वापस data->present;

		/* When Secure Connections Only mode is enabled, then
		 * the P-256 values are required. If they are not
		 * available, then करो not declare that OOB data is
		 * present.
		 */
		अगर (!स_भेद(data->अक्रम256, ZERO_KEY, 16) ||
		    !स_भेद(data->hash256, ZERO_KEY, 16))
			वापस 0x00;

		वापस 0x02;
	पूर्ण

	/* When Secure Connections is not enabled or actually
	 * not supported by the hardware, then check that अगर
	 * P-192 data values are present.
	 */
	अगर (!स_भेद(data->अक्रम192, ZERO_KEY, 16) ||
	    !स_भेद(data->hash192, ZERO_KEY, 16))
		वापस 0x00;

	वापस 0x01;
पूर्ण

अटल व्योम hci_io_capa_request_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_io_capa_request *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	hci_conn_hold(conn);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		जाओ unlock;

	/* Allow pairing अगर we're pairable, the initiators of the
	 * pairing or अगर the remote is not requesting bonding.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_BONDABLE) ||
	    test_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags) ||
	    (conn->remote_auth & ~0x01) == HCI_AT_NO_BONDING) अणु
		काष्ठा hci_cp_io_capability_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		/* Change the IO capability from KeyboardDisplay
		 * to DisplayYesNo as it is not supported by BT spec. */
		cp.capability = (conn->io_capability == 0x04) ?
				HCI_IO_DISPLAY_YESNO : conn->io_capability;

		/* If we are initiators, there is no remote inक्रमmation yet */
		अगर (conn->remote_auth == 0xff) अणु
			/* Request MITM protection अगर our IO caps allow it
			 * except क्रम the no-bonding हाल.
			 */
			अगर (conn->io_capability != HCI_IO_NO_INPUT_OUTPUT &&
			    conn->auth_type != HCI_AT_NO_BONDING)
				conn->auth_type |= 0x01;
		पूर्ण अन्यथा अणु
			conn->auth_type = hci_get_auth_req(conn);
		पूर्ण

		/* If we're not bondable, क्रमce one of the non-bondable
		 * authentication requirement values.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_BONDABLE))
			conn->auth_type &= HCI_AT_NO_BONDING_MITM;

		cp.authentication = conn->auth_type;
		cp.oob_data = bredr_oob_data_present(conn);

		hci_send_cmd(hdev, HCI_OP_IO_CAPABILITY_REPLY,
			     माप(cp), &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_io_capability_neg_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		cp.reason = HCI_ERROR_PAIRING_NOT_ALLOWED;

		hci_send_cmd(hdev, HCI_OP_IO_CAPABILITY_NEG_REPLY,
			     माप(cp), &cp);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_io_capa_reply_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_io_capa_reply *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	conn->remote_cap = ev->capability;
	conn->remote_auth = ev->authentication;

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_user_confirm_request_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_user_confirm_req *ev = (व्योम *) skb->data;
	पूर्णांक loc_miपंचांग, rem_miपंचांग, confirm_hपूर्णांक = 0;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		जाओ unlock;

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	loc_miपंचांग = (conn->auth_type & 0x01);
	rem_miपंचांग = (conn->remote_auth & 0x01);

	/* If we require MITM but the remote device can't provide that
	 * (it has NoInputNoOutput) then reject the confirmation
	 * request. We check the security level here since it करोesn't
	 * necessarily match conn->auth_type.
	 */
	अगर (conn->pending_sec_level > BT_SECURITY_MEDIUM &&
	    conn->remote_cap == HCI_IO_NO_INPUT_OUTPUT) अणु
		BT_DBG("Rejecting request: remote device can't provide MITM");
		hci_send_cmd(hdev, HCI_OP_USER_CONFIRM_NEG_REPLY,
			     माप(ev->bdaddr), &ev->bdaddr);
		जाओ unlock;
	पूर्ण

	/* If no side requires MITM protection; स्वतः-accept */
	अगर ((!loc_miपंचांग || conn->remote_cap == HCI_IO_NO_INPUT_OUTPUT) &&
	    (!rem_miपंचांग || conn->io_capability == HCI_IO_NO_INPUT_OUTPUT)) अणु

		/* If we're not the initiators request authorization to
		 * proceed from user space (mgmt_user_confirm with
		 * confirm_hपूर्णांक set to 1). The exception is अगर neither
		 * side had MITM or अगर the local IO capability is
		 * NoInputNoOutput, in which हाल we करो स्वतः-accept
		 */
		अगर (!test_bit(HCI_CONN_AUTH_PEND, &conn->flags) &&
		    conn->io_capability != HCI_IO_NO_INPUT_OUTPUT &&
		    (loc_miपंचांग || rem_miपंचांग)) अणु
			BT_DBG("Confirming auto-accept as acceptor");
			confirm_hपूर्णांक = 1;
			जाओ confirm;
		पूर्ण

		/* If there alपढ़ोy exists link key in local host, leave the
		 * decision to user space since the remote device could be
		 * legitimate or malicious.
		 */
		अगर (hci_find_link_key(hdev, &ev->bdaddr)) अणु
			bt_dev_dbg(hdev, "Local host already has link key");
			confirm_hपूर्णांक = 1;
			जाओ confirm;
		पूर्ण

		BT_DBG("Auto-accept of user confirmation with %ums delay",
		       hdev->स्वतः_accept_delay);

		अगर (hdev->स्वतः_accept_delay > 0) अणु
			पूर्णांक delay = msecs_to_jअगरfies(hdev->स्वतः_accept_delay);
			queue_delayed_work(conn->hdev->workqueue,
					   &conn->स्वतः_accept_work, delay);
			जाओ unlock;
		पूर्ण

		hci_send_cmd(hdev, HCI_OP_USER_CONFIRM_REPLY,
			     माप(ev->bdaddr), &ev->bdaddr);
		जाओ unlock;
	पूर्ण

confirm:
	mgmt_user_confirm_request(hdev, &ev->bdaddr, ACL_LINK, 0,
				  le32_to_cpu(ev->passkey), confirm_hपूर्णांक);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_user_passkey_request_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_user_passkey_req *ev = (व्योम *) skb->data;

	BT_DBG("%s", hdev->name);

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_request(hdev, &ev->bdaddr, ACL_LINK, 0);
पूर्ण

अटल व्योम hci_user_passkey_notअगरy_evt(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_user_passkey_notअगरy *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		वापस;

	conn->passkey_notअगरy = __le32_to_cpu(ev->passkey);
	conn->passkey_entered = 0;

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_notअगरy(hdev, &conn->dst, conn->type,
					 conn->dst_type, conn->passkey_notअगरy,
					 conn->passkey_entered);
पूर्ण

अटल व्योम hci_keypress_notअगरy_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_keypress_notअगरy *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		वापस;

	चयन (ev->type) अणु
	हाल HCI_KEYPRESS_STARTED:
		conn->passkey_entered = 0;
		वापस;

	हाल HCI_KEYPRESS_ENTERED:
		conn->passkey_entered++;
		अवरोध;

	हाल HCI_KEYPRESS_ERASED:
		conn->passkey_entered--;
		अवरोध;

	हाल HCI_KEYPRESS_CLEARED:
		conn->passkey_entered = 0;
		अवरोध;

	हाल HCI_KEYPRESS_COMPLETED:
		वापस;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_notअगरy(hdev, &conn->dst, conn->type,
					 conn->dst_type, conn->passkey_notअगरy,
					 conn->passkey_entered);
पूर्ण

अटल व्योम hci_simple_pair_complete_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_simple_pair_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (!conn)
		जाओ unlock;

	/* Reset the authentication requirement to unknown */
	conn->remote_auth = 0xff;

	/* To aव्योम duplicate auth_failed events to user space we check
	 * the HCI_CONN_AUTH_PEND flag which will be set अगर we
	 * initiated the authentication. A traditional auth_complete
	 * event माला_लो always produced as initiator and is also mapped to
	 * the mgmt_auth_failed event */
	अगर (!test_bit(HCI_CONN_AUTH_PEND, &conn->flags) && ev->status)
		mgmt_auth_failed(conn, ev->status);

	hci_conn_drop(conn);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_remote_host_features_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_remote_host_features *ev = (व्योम *) skb->data;
	काष्ठा inquiry_entry *ie;
	काष्ठा hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	अगर (conn)
		स_नकल(conn->features[1], ev->features, 8);

	ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr);
	अगर (ie)
		ie->data.ssp_mode = (ev->features[0] & LMP_HOST_SSP);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_remote_oob_data_request_evt(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_remote_oob_data_request *ev = (व्योम *) skb->data;
	काष्ठा oob_data *data;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	अगर (!hci_dev_test_flag(hdev, HCI_MGMT))
		जाओ unlock;

	data = hci_find_remote_oob_data(hdev, &ev->bdaddr, BDADDR_BREDR);
	अगर (!data) अणु
		काष्ठा hci_cp_remote_oob_data_neg_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_DATA_NEG_REPLY,
			     माप(cp), &cp);
		जाओ unlock;
	पूर्ण

	अगर (bredr_sc_enabled(hdev)) अणु
		काष्ठा hci_cp_remote_oob_ext_data_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY)) अणु
			स_रखो(cp.hash192, 0, माप(cp.hash192));
			स_रखो(cp.अक्रम192, 0, माप(cp.अक्रम192));
		पूर्ण अन्यथा अणु
			स_नकल(cp.hash192, data->hash192, माप(cp.hash192));
			स_नकल(cp.अक्रम192, data->अक्रम192, माप(cp.अक्रम192));
		पूर्ण
		स_नकल(cp.hash256, data->hash256, माप(cp.hash256));
		स_नकल(cp.अक्रम256, data->अक्रम256, माप(cp.अक्रम256));

		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_EXT_DATA_REPLY,
			     माप(cp), &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_remote_oob_data_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		स_नकल(cp.hash, data->hash192, माप(cp.hash));
		स_नकल(cp.अक्रम, data->अक्रम192, माप(cp.अक्रम));

		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_DATA_REPLY,
			     माप(cp), &cp);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

#अगर IS_ENABLED(CONFIG_BT_HS)
अटल व्योम hci_chan_selected_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_channel_selected *ev = (व्योम *)skb->data;
	काष्ठा hci_conn *hcon;

	BT_DBG("%s handle 0x%2.2x", hdev->name, ev->phy_handle);

	skb_pull(skb, माप(*ev));

	hcon = hci_conn_hash_lookup_handle(hdev, ev->phy_handle);
	अगर (!hcon)
		वापस;

	amp_पढ़ो_loc_assoc_final_data(hdev, hcon);
पूर्ण

अटल व्योम hci_phy_link_complete_evt(काष्ठा hci_dev *hdev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_phy_link_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *hcon, *bredr_hcon;

	BT_DBG("%s handle 0x%2.2x status 0x%2.2x", hdev->name, ev->phy_handle,
	       ev->status);

	hci_dev_lock(hdev);

	hcon = hci_conn_hash_lookup_handle(hdev, ev->phy_handle);
	अगर (!hcon)
		जाओ unlock;

	अगर (!hcon->amp_mgr)
		जाओ unlock;

	अगर (ev->status) अणु
		hci_conn_del(hcon);
		जाओ unlock;
	पूर्ण

	bredr_hcon = hcon->amp_mgr->l2cap_conn->hcon;

	hcon->state = BT_CONNECTED;
	bacpy(&hcon->dst, &bredr_hcon->dst);

	hci_conn_hold(hcon);
	hcon->disc_समयout = HCI_DISCONN_TIMEOUT;
	hci_conn_drop(hcon);

	hci_debugfs_create_conn(hcon);
	hci_conn_add_sysfs(hcon);

	amp_physical_cfm(bredr_hcon, hcon);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_loglink_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_logical_link_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *hcon;
	काष्ठा hci_chan *hchan;
	काष्ठा amp_mgr *mgr;

	BT_DBG("%s log_handle 0x%4.4x phy_handle 0x%2.2x status 0x%2.2x",
	       hdev->name, le16_to_cpu(ev->handle), ev->phy_handle,
	       ev->status);

	hcon = hci_conn_hash_lookup_handle(hdev, ev->phy_handle);
	अगर (!hcon)
		वापस;

	/* Create AMP hchan */
	hchan = hci_chan_create(hcon);
	अगर (!hchan)
		वापस;

	hchan->handle = le16_to_cpu(ev->handle);
	hchan->amp = true;

	BT_DBG("hcon %p mgr %p hchan %p", hcon, hcon->amp_mgr, hchan);

	mgr = hcon->amp_mgr;
	अगर (mgr && mgr->bredr_chan) अणु
		काष्ठा l2cap_chan *bredr_chan = mgr->bredr_chan;

		l2cap_chan_lock(bredr_chan);

		bredr_chan->conn->mtu = hdev->block_mtu;
		l2cap_logical_cfm(bredr_chan, hchan, 0);
		hci_conn_hold(hcon);

		l2cap_chan_unlock(bredr_chan);
	पूर्ण
पूर्ण

अटल व्योम hci_disconn_loglink_complete_evt(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_disconn_logical_link_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_chan *hchan;

	BT_DBG("%s log handle 0x%4.4x status 0x%2.2x", hdev->name,
	       le16_to_cpu(ev->handle), ev->status);

	अगर (ev->status)
		वापस;

	hci_dev_lock(hdev);

	hchan = hci_chan_lookup_handle(hdev, le16_to_cpu(ev->handle));
	अगर (!hchan || !hchan->amp)
		जाओ unlock;

	amp_destroy_logical_link(hchan, ev->reason);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_disconn_phylink_complete_evt(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_disconn_phy_link_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *hcon;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	अगर (ev->status)
		वापस;

	hci_dev_lock(hdev);

	hcon = hci_conn_hash_lookup_handle(hdev, ev->phy_handle);
	अगर (hcon) अणु
		hcon->state = BT_CLOSED;
		hci_conn_del(hcon);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण
#पूर्ण_अगर

अटल व्योम le_conn_complete_evt(काष्ठा hci_dev *hdev, u8 status,
			bdaddr_t *bdaddr, u8 bdaddr_type, u8 role, u16 handle,
			u16 पूर्णांकerval, u16 latency, u16 supervision_समयout)
अणु
	काष्ठा hci_conn_params *params;
	काष्ठा hci_conn *conn;
	काष्ठा smp_irk *irk;
	u8 addr_type;

	hci_dev_lock(hdev);

	/* All controllers implicitly stop advertising in the event of a
	 * connection, so ensure that the state bit is cleared.
	 */
	hci_dev_clear_flag(hdev, HCI_LE_ADV);

	conn = hci_lookup_le_connect(hdev);
	अगर (!conn) अणु
		conn = hci_conn_add(hdev, LE_LINK, bdaddr, role);
		अगर (!conn) अणु
			bt_dev_err(hdev, "no memory for new connection");
			जाओ unlock;
		पूर्ण

		conn->dst_type = bdaddr_type;

		/* If we didn't have a hci_conn object previously
		 * but we're in master role this must be something
		 * initiated using a white list. Since white list based
		 * connections are not "first class citizens" we करोn't
		 * have full tracking of them. Thereक्रमe, we go ahead
		 * with a "best effort" approach of determining the
		 * initiator address based on the HCI_PRIVACY flag.
		 */
		अगर (conn->out) अणु
			conn->resp_addr_type = bdaddr_type;
			bacpy(&conn->resp_addr, bdaddr);
			अगर (hci_dev_test_flag(hdev, HCI_PRIVACY)) अणु
				conn->init_addr_type = ADDR_LE_DEV_RANDOM;
				bacpy(&conn->init_addr, &hdev->rpa);
			पूर्ण अन्यथा अणु
				hci_copy_identity_address(hdev,
							  &conn->init_addr,
							  &conn->init_addr_type);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cancel_delayed_work(&conn->le_conn_समयout);
	पूर्ण

	अगर (!conn->out) अणु
		/* Set the responder (our side) address type based on
		 * the advertising address type.
		 */
		conn->resp_addr_type = hdev->adv_addr_type;
		अगर (hdev->adv_addr_type == ADDR_LE_DEV_RANDOM) अणु
			/* In हाल of ext adv, resp_addr will be updated in
			 * Adv Terminated event.
			 */
			अगर (!ext_adv_capable(hdev))
				bacpy(&conn->resp_addr, &hdev->अक्रमom_addr);
		पूर्ण अन्यथा अणु
			bacpy(&conn->resp_addr, &hdev->bdaddr);
		पूर्ण

		conn->init_addr_type = bdaddr_type;
		bacpy(&conn->init_addr, bdaddr);

		/* For incoming connections, set the शेष minimum
		 * and maximum connection पूर्णांकerval. They will be used
		 * to check अगर the parameters are in range and अगर not
		 * trigger the connection update procedure.
		 */
		conn->le_conn_min_पूर्णांकerval = hdev->le_conn_min_पूर्णांकerval;
		conn->le_conn_max_पूर्णांकerval = hdev->le_conn_max_पूर्णांकerval;
	पूर्ण

	/* Lookup the identity address from the stored connection
	 * address and address type.
	 *
	 * When establishing connections to an identity address, the
	 * connection procedure will store the resolvable अक्रमom
	 * address first. Now अगर it can be converted back पूर्णांकo the
	 * identity address, start using the identity address from
	 * now on.
	 */
	irk = hci_get_irk(hdev, &conn->dst, conn->dst_type);
	अगर (irk) अणु
		bacpy(&conn->dst, &irk->bdaddr);
		conn->dst_type = irk->addr_type;
	पूर्ण

	अगर (status) अणु
		hci_le_conn_failed(conn, status);
		जाओ unlock;
	पूर्ण

	अगर (conn->dst_type == ADDR_LE_DEV_PUBLIC)
		addr_type = BDADDR_LE_PUBLIC;
	अन्यथा
		addr_type = BDADDR_LE_RANDOM;

	/* Drop the connection अगर the device is blocked */
	अगर (hci_bdaddr_list_lookup(&hdev->blacklist, &conn->dst, addr_type)) अणु
		hci_conn_drop(conn);
		जाओ unlock;
	पूर्ण

	अगर (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, शून्य, 0);

	conn->sec_level = BT_SECURITY_LOW;
	conn->handle = handle;
	conn->state = BT_CONFIG;

	conn->le_conn_पूर्णांकerval = पूर्णांकerval;
	conn->le_conn_latency = latency;
	conn->le_supv_समयout = supervision_समयout;

	hci_debugfs_create_conn(conn);
	hci_conn_add_sysfs(conn);

	/* The remote features procedure is defined क्रम master
	 * role only. So only in हाल of an initiated connection
	 * request the remote features.
	 *
	 * If the local controller supports slave-initiated features
	 * exchange, then requesting the remote features in slave
	 * role is possible. Otherwise just transition पूर्णांकo the
	 * connected state without requesting the remote features.
	 */
	अगर (conn->out ||
	    (hdev->le_features[0] & HCI_LE_SLAVE_FEATURES)) अणु
		काष्ठा hci_cp_le_पढ़ो_remote_features cp;

		cp.handle = __cpu_to_le16(conn->handle);

		hci_send_cmd(hdev, HCI_OP_LE_READ_REMOTE_FEATURES,
			     माप(cp), &cp);

		hci_conn_hold(conn);
	पूर्ण अन्यथा अणु
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, status);
	पूर्ण

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, &conn->dst,
					   conn->dst_type);
	अगर (params) अणु
		list_del_init(&params->action);
		अगर (params->conn) अणु
			hci_conn_drop(params->conn);
			hci_conn_put(params->conn);
			params->conn = शून्य;
		पूर्ण
	पूर्ण

unlock:
	hci_update_background_scan(hdev);
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_le_conn_complete_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_conn_complete *ev = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	le_conn_complete_evt(hdev, ev->status, &ev->bdaddr, ev->bdaddr_type,
			     ev->role, le16_to_cpu(ev->handle),
			     le16_to_cpu(ev->पूर्णांकerval),
			     le16_to_cpu(ev->latency),
			     le16_to_cpu(ev->supervision_समयout));
पूर्ण

अटल व्योम hci_le_enh_conn_complete_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_enh_conn_complete *ev = (व्योम *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	le_conn_complete_evt(hdev, ev->status, &ev->bdaddr, ev->bdaddr_type,
			     ev->role, le16_to_cpu(ev->handle),
			     le16_to_cpu(ev->पूर्णांकerval),
			     le16_to_cpu(ev->latency),
			     le16_to_cpu(ev->supervision_समयout));

	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
	    hci_dev_test_flag(hdev, HCI_LL_RPA_RESOLUTION))
		hci_req_disable_address_resolution(hdev);
पूर्ण

अटल व्योम hci_le_ext_adv_term_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_evt_le_ext_adv_set_term *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	अगर (ev->status)
		वापस;

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->conn_handle));
	अगर (conn) अणु
		काष्ठा adv_info *adv_instance;

		अगर (hdev->adv_addr_type != ADDR_LE_DEV_RANDOM)
			वापस;

		अगर (!ev->handle) अणु
			bacpy(&conn->resp_addr, &hdev->अक्रमom_addr);
			वापस;
		पूर्ण

		adv_instance = hci_find_adv_instance(hdev, ev->handle);
		अगर (adv_instance)
			bacpy(&conn->resp_addr, &adv_instance->अक्रमom_addr);
	पूर्ण
पूर्ण

अटल व्योम hci_le_conn_update_complete_evt(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_conn_update_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	अगर (ev->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn) अणु
		conn->le_conn_पूर्णांकerval = le16_to_cpu(ev->पूर्णांकerval);
		conn->le_conn_latency = le16_to_cpu(ev->latency);
		conn->le_supv_समयout = le16_to_cpu(ev->supervision_समयout);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल काष्ठा hci_conn *check_pending_le_conn(काष्ठा hci_dev *hdev,
					      bdaddr_t *addr,
					      u8 addr_type, u8 adv_type,
					      bdaddr_t *direct_rpa)
अणु
	काष्ठा hci_conn *conn;
	काष्ठा hci_conn_params *params;

	/* If the event is not connectable करोn't proceed further */
	अगर (adv_type != LE_ADV_IND && adv_type != LE_ADV_सूचीECT_IND)
		वापस शून्य;

	/* Ignore अगर the device is blocked */
	अगर (hci_bdaddr_list_lookup(&hdev->blacklist, addr, addr_type))
		वापस शून्य;

	/* Most controller will fail अगर we try to create new connections
	 * जबतक we have an existing one in slave role.
	 */
	अगर (hdev->conn_hash.le_num_slave > 0 &&
	    (!test_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks) ||
	     !(hdev->le_states[3] & 0x10)))
		वापस शून्य;

	/* If we're not connectable only connect devices that we have in
	 * our pend_le_conns list.
	 */
	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, addr,
					   addr_type);
	अगर (!params)
		वापस शून्य;

	अगर (!params->explicit_connect) अणु
		चयन (params->स्वतः_connect) अणु
		हाल HCI_AUTO_CONN_सूचीECT:
			/* Only devices advertising with ADV_सूचीECT_IND are
			 * triggering a connection attempt. This is allowing
			 * incoming connections from slave devices.
			 */
			अगर (adv_type != LE_ADV_सूचीECT_IND)
				वापस शून्य;
			अवरोध;
		हाल HCI_AUTO_CONN_ALWAYS:
			/* Devices advertising with ADV_IND or ADV_सूचीECT_IND
			 * are triggering a connection attempt. This means
			 * that incoming connections from slave device are
			 * accepted and also outgoing connections to slave
			 * devices are established when found.
			 */
			अवरोध;
		शेष:
			वापस शून्य;
		पूर्ण
	पूर्ण

	conn = hci_connect_le(hdev, addr, addr_type, BT_SECURITY_LOW,
			      hdev->def_le_स्वतःconnect_समयout, HCI_ROLE_MASTER,
			      direct_rpa);
	अगर (!IS_ERR(conn)) अणु
		/* If HCI_AUTO_CONN_EXPLICIT is set, conn is alपढ़ोy owned
		 * by higher layer that tried to connect, अगर no then
		 * store the poपूर्णांकer since we करोn't really have any
		 * other owner of the object besides the params that
		 * triggered it. This way we can पात the connection अगर
		 * the parameters get हटाओd and keep the reference
		 * count consistent once the connection is established.
		 */

		अगर (!params->explicit_connect)
			params->conn = hci_conn_get(conn);

		वापस conn;
	पूर्ण

	चयन (PTR_ERR(conn)) अणु
	हाल -EBUSY:
		/* If hci_connect() वापसs -EBUSY it means there is alपढ़ोy
		 * an LE connection attempt going on. Since controllers करोn't
		 * support more than one connection attempt at the समय, we
		 * करोn't consider this an error हाल.
		 */
		अवरोध;
	शेष:
		BT_DBG("Failed to connect: err %ld", PTR_ERR(conn));
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम process_adv_report(काष्ठा hci_dev *hdev, u8 type, bdaddr_t *bdaddr,
			       u8 bdaddr_type, bdaddr_t *direct_addr,
			       u8 direct_addr_type, s8 rssi, u8 *data, u8 len,
			       bool ext_adv)
अणु
	काष्ठा discovery_state *d = &hdev->discovery;
	काष्ठा smp_irk *irk;
	काष्ठा hci_conn *conn;
	bool match;
	u32 flags;
	u8 *ptr, real_len;

	चयन (type) अणु
	हाल LE_ADV_IND:
	हाल LE_ADV_सूचीECT_IND:
	हाल LE_ADV_SCAN_IND:
	हाल LE_ADV_NONCONN_IND:
	हाल LE_ADV_SCAN_RSP:
		अवरोध;
	शेष:
		bt_dev_err_ratelimited(hdev, "unknown advertising packet "
				       "type: 0x%02x", type);
		वापस;
	पूर्ण

	अगर (!ext_adv && len > HCI_MAX_AD_LENGTH) अणु
		bt_dev_err_ratelimited(hdev, "legacy adv larger than 31 bytes");
		वापस;
	पूर्ण

	/* Find the end of the data in हाल the report contains padded zero
	 * bytes at the end causing an invalid length value.
	 *
	 * When data is शून्य, len is 0 so there is no need क्रम extra ptr
	 * check as 'ptr < data + 0' is alपढ़ोy false in such हाल.
	 */
	क्रम (ptr = data; ptr < data + len && *ptr; ptr += *ptr + 1) अणु
		अगर (ptr + 1 + *ptr > data + len)
			अवरोध;
	पूर्ण

	real_len = ptr - data;

	/* Adjust क्रम actual length */
	अगर (len != real_len) अणु
		bt_dev_err_ratelimited(hdev, "advertising data len corrected %u -> %u",
				       len, real_len);
		len = real_len;
	पूर्ण

	/* If the direct address is present, then this report is from
	 * a LE Direct Advertising Report event. In that हाल it is
	 * important to see अगर the address is matching the local
	 * controller address.
	 */
	अगर (direct_addr) अणु
		/* Only resolvable अक्रमom addresses are valid क्रम these
		 * kind of reports and others can be ignored.
		 */
		अगर (!hci_bdaddr_is_rpa(direct_addr, direct_addr_type))
			वापस;

		/* If the controller is not using resolvable अक्रमom
		 * addresses, then this report can be ignored.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_PRIVACY))
			वापस;

		/* If the local IRK of the controller करोes not match
		 * with the resolvable अक्रमom address provided, then
		 * this report can be ignored.
		 */
		अगर (!smp_irk_matches(hdev, hdev->irk, direct_addr))
			वापस;
	पूर्ण

	/* Check अगर we need to convert to identity address */
	irk = hci_get_irk(hdev, bdaddr, bdaddr_type);
	अगर (irk) अणु
		bdaddr = &irk->bdaddr;
		bdaddr_type = irk->addr_type;
	पूर्ण

	/* Check अगर we have been requested to connect to this device.
	 *
	 * direct_addr is set only क्रम directed advertising reports (it is शून्य
	 * क्रम advertising reports) and is alपढ़ोy verअगरied to be RPA above.
	 */
	conn = check_pending_le_conn(hdev, bdaddr, bdaddr_type, type,
								direct_addr);
	अगर (!ext_adv && conn && type == LE_ADV_IND && len <= HCI_MAX_AD_LENGTH) अणु
		/* Store report क्रम later inclusion by
		 * mgmt_device_connected
		 */
		स_नकल(conn->le_adv_data, data, len);
		conn->le_adv_data_len = len;
	पूर्ण

	/* Passive scanning shouldn't trigger any device found events,
	 * except क्रम devices marked as CONN_REPORT क्रम which we करो send
	 * device found events, or advertisement monitoring requested.
	 */
	अगर (hdev->le_scan_type == LE_SCAN_PASSIVE) अणु
		अगर (type == LE_ADV_सूचीECT_IND)
			वापस;

		अगर (!hci_pend_le_action_lookup(&hdev->pend_le_reports,
					       bdaddr, bdaddr_type) &&
		    idr_is_empty(&hdev->adv_monitors_idr))
			वापस;

		अगर (type == LE_ADV_NONCONN_IND || type == LE_ADV_SCAN_IND)
			flags = MGMT_DEV_FOUND_NOT_CONNECTABLE;
		अन्यथा
			flags = 0;
		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, शून्य,
				  rssi, flags, data, len, शून्य, 0);
		वापस;
	पूर्ण

	/* When receiving non-connectable or scannable undirected
	 * advertising reports, this means that the remote device is
	 * not connectable and then clearly indicate this in the
	 * device found event.
	 *
	 * When receiving a scan response, then there is no way to
	 * know अगर the remote device is connectable or not. However
	 * since scan responses are merged with a previously seen
	 * advertising report, the flags field from that report
	 * will be used.
	 *
	 * In the really unlikely हाल that a controller get confused
	 * and just sends a scan response event, then it is marked as
	 * not connectable as well.
	 */
	अगर (type == LE_ADV_NONCONN_IND || type == LE_ADV_SCAN_IND ||
	    type == LE_ADV_SCAN_RSP)
		flags = MGMT_DEV_FOUND_NOT_CONNECTABLE;
	अन्यथा
		flags = 0;

	/* If there's nothing pending either store the data from this
	 * event or send an immediate device found event अगर the data
	 * should not be stored क्रम later.
	 */
	अगर (!ext_adv &&	!has_pending_adv_report(hdev)) अणु
		/* If the report will trigger a SCAN_REQ store it क्रम
		 * later merging.
		 */
		अगर (type == LE_ADV_IND || type == LE_ADV_SCAN_IND) अणु
			store_pending_adv_report(hdev, bdaddr, bdaddr_type,
						 rssi, flags, data, len);
			वापस;
		पूर्ण

		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, शून्य,
				  rssi, flags, data, len, शून्य, 0);
		वापस;
	पूर्ण

	/* Check अगर the pending report is क्रम the same device as the new one */
	match = (!bacmp(bdaddr, &d->last_adv_addr) &&
		 bdaddr_type == d->last_adv_addr_type);

	/* If the pending data करोesn't match this report or this isn't a
	 * scan response (e.g. we got a duplicate ADV_IND) then क्रमce
	 * sending of the pending data.
	 */
	अगर (type != LE_ADV_SCAN_RSP || !match) अणु
		/* Send out whatever is in the cache, but skip duplicates */
		अगर (!match)
			mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
					  d->last_adv_addr_type, शून्य,
					  d->last_adv_rssi, d->last_adv_flags,
					  d->last_adv_data,
					  d->last_adv_data_len, शून्य, 0);

		/* If the new report will trigger a SCAN_REQ store it क्रम
		 * later merging.
		 */
		अगर (!ext_adv && (type == LE_ADV_IND ||
				 type == LE_ADV_SCAN_IND)) अणु
			store_pending_adv_report(hdev, bdaddr, bdaddr_type,
						 rssi, flags, data, len);
			वापस;
		पूर्ण

		/* The advertising reports cannot be merged, so clear
		 * the pending report and send out a device found event.
		 */
		clear_pending_adv_report(hdev);
		mgmt_device_found(hdev, bdaddr, LE_LINK, bdaddr_type, शून्य,
				  rssi, flags, data, len, शून्य, 0);
		वापस;
	पूर्ण

	/* If we get here we've got a pending ADV_IND or ADV_SCAN_IND and
	 * the new event is a SCAN_RSP. We can thereक्रमe proceed with
	 * sending a merged device found event.
	 */
	mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
			  d->last_adv_addr_type, शून्य, rssi, d->last_adv_flags,
			  d->last_adv_data, d->last_adv_data_len, data, len);
	clear_pending_adv_report(hdev);
पूर्ण

अटल व्योम hci_le_adv_report_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	u8 num_reports = skb->data[0];
	व्योम *ptr = &skb->data[1];

	hci_dev_lock(hdev);

	जबतक (num_reports--) अणु
		काष्ठा hci_ev_le_advertising_info *ev = ptr;
		s8 rssi;

		अगर (ev->length <= HCI_MAX_AD_LENGTH) अणु
			rssi = ev->data[ev->length];
			process_adv_report(hdev, ev->evt_type, &ev->bdaddr,
					   ev->bdaddr_type, शून्य, 0, rssi,
					   ev->data, ev->length, false);
		पूर्ण अन्यथा अणु
			bt_dev_err(hdev, "Dropping invalid advertising data");
		पूर्ण

		ptr += माप(*ev) + ev->length + 1;
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल u8 ext_evt_type_to_legacy(काष्ठा hci_dev *hdev, u16 evt_type)
अणु
	अगर (evt_type & LE_EXT_ADV_LEGACY_PDU) अणु
		चयन (evt_type) अणु
		हाल LE_LEGACY_ADV_IND:
			वापस LE_ADV_IND;
		हाल LE_LEGACY_ADV_सूचीECT_IND:
			वापस LE_ADV_सूचीECT_IND;
		हाल LE_LEGACY_ADV_SCAN_IND:
			वापस LE_ADV_SCAN_IND;
		हाल LE_LEGACY_NONCONN_IND:
			वापस LE_ADV_NONCONN_IND;
		हाल LE_LEGACY_SCAN_RSP_ADV:
		हाल LE_LEGACY_SCAN_RSP_ADV_SCAN:
			वापस LE_ADV_SCAN_RSP;
		पूर्ण

		जाओ invalid;
	पूर्ण

	अगर (evt_type & LE_EXT_ADV_CONN_IND) अणु
		अगर (evt_type & LE_EXT_ADV_सूचीECT_IND)
			वापस LE_ADV_सूचीECT_IND;

		वापस LE_ADV_IND;
	पूर्ण

	अगर (evt_type & LE_EXT_ADV_SCAN_RSP)
		वापस LE_ADV_SCAN_RSP;

	अगर (evt_type & LE_EXT_ADV_SCAN_IND)
		वापस LE_ADV_SCAN_IND;

	अगर (evt_type == LE_EXT_ADV_NON_CONN_IND ||
	    evt_type & LE_EXT_ADV_सूचीECT_IND)
		वापस LE_ADV_NONCONN_IND;

invalid:
	bt_dev_err_ratelimited(hdev, "Unknown advertising packet type: 0x%02x",
			       evt_type);

	वापस LE_ADV_INVALID;
पूर्ण

अटल व्योम hci_le_ext_adv_report_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	u8 num_reports = skb->data[0];
	व्योम *ptr = &skb->data[1];

	hci_dev_lock(hdev);

	जबतक (num_reports--) अणु
		काष्ठा hci_ev_le_ext_adv_report *ev = ptr;
		u8 legacy_evt_type;
		u16 evt_type;

		evt_type = __le16_to_cpu(ev->evt_type);
		legacy_evt_type = ext_evt_type_to_legacy(hdev, evt_type);
		अगर (legacy_evt_type != LE_ADV_INVALID) अणु
			process_adv_report(hdev, legacy_evt_type, &ev->bdaddr,
					   ev->bdaddr_type, शून्य, 0, ev->rssi,
					   ev->data, ev->length,
					   !(evt_type & LE_EXT_ADV_LEGACY_PDU));
		पूर्ण

		ptr += माप(*ev) + ev->length;
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_le_remote_feat_complete_evt(काष्ठा hci_dev *hdev,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_remote_feat_complete *ev = (व्योम *)skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn) अणु
		अगर (!ev->status)
			स_नकल(conn->features[0], ev->features, 8);

		अगर (conn->state == BT_CONFIG) अणु
			__u8 status;

			/* If the local controller supports slave-initiated
			 * features exchange, but the remote controller करोes
			 * not, then it is possible that the error code 0x1a
			 * क्रम unsupported remote feature माला_लो वापसed.
			 *
			 * In this specअगरic हाल, allow the connection to
			 * transition पूर्णांकo connected state and mark it as
			 * successful.
			 */
			अगर ((hdev->le_features[0] & HCI_LE_SLAVE_FEATURES) &&
			    !conn->out && ev->status == 0x1a)
				status = 0x00;
			अन्यथा
				status = ev->status;

			conn->state = BT_CONNECTED;
			hci_connect_cfm(conn, status);
			hci_conn_drop(conn);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_le_ltk_request_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_ltk_req *ev = (व्योम *) skb->data;
	काष्ठा hci_cp_le_ltk_reply cp;
	काष्ठा hci_cp_le_ltk_neg_reply neg;
	काष्ठा hci_conn *conn;
	काष्ठा smp_ltk *ltk;

	BT_DBG("%s handle 0x%4.4x", hdev->name, __le16_to_cpu(ev->handle));

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (conn == शून्य)
		जाओ not_found;

	ltk = hci_find_ltk(hdev, &conn->dst, conn->dst_type, conn->role);
	अगर (!ltk)
		जाओ not_found;

	अगर (smp_ltk_is_sc(ltk)) अणु
		/* With SC both EDiv and Rand are set to zero */
		अगर (ev->eभाग || ev->अक्रम)
			जाओ not_found;
	पूर्ण अन्यथा अणु
		/* For non-SC keys check that EDiv and Rand match */
		अगर (ev->eभाग != ltk->eभाग || ev->अक्रम != ltk->अक्रम)
			जाओ not_found;
	पूर्ण

	स_नकल(cp.ltk, ltk->val, ltk->enc_size);
	स_रखो(cp.ltk + ltk->enc_size, 0, माप(cp.ltk) - ltk->enc_size);
	cp.handle = cpu_to_le16(conn->handle);

	conn->pending_sec_level = smp_ltk_sec_level(ltk);

	conn->enc_key_size = ltk->enc_size;

	hci_send_cmd(hdev, HCI_OP_LE_LTK_REPLY, माप(cp), &cp);

	/* Ref. Bluetooth Core SPEC pages 1975 and 2004. STK is a
	 * temporary key used to encrypt a connection following
	 * pairing. It is used during the Encrypted Session Setup to
	 * distribute the keys. Later, security can be re-established
	 * using a distributed LTK.
	 */
	अगर (ltk->type == SMP_STK) अणु
		set_bit(HCI_CONN_STK_ENCRYPT, &conn->flags);
		list_del_rcu(&ltk->list);
		kमुक्त_rcu(ltk, rcu);
	पूर्ण अन्यथा अणु
		clear_bit(HCI_CONN_STK_ENCRYPT, &conn->flags);
	पूर्ण

	hci_dev_unlock(hdev);

	वापस;

not_found:
	neg.handle = ev->handle;
	hci_send_cmd(hdev, HCI_OP_LE_LTK_NEG_REPLY, माप(neg), &neg);
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम send_conn_param_neg_reply(काष्ठा hci_dev *hdev, u16 handle,
				      u8 reason)
अणु
	काष्ठा hci_cp_le_conn_param_req_neg_reply cp;

	cp.handle = cpu_to_le16(handle);
	cp.reason = reason;

	hci_send_cmd(hdev, HCI_OP_LE_CONN_PARAM_REQ_NEG_REPLY, माप(cp),
		     &cp);
पूर्ण

अटल व्योम hci_le_remote_conn_param_req_evt(काष्ठा hci_dev *hdev,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_remote_conn_param_req *ev = (व्योम *) skb->data;
	काष्ठा hci_cp_le_conn_param_req_reply cp;
	काष्ठा hci_conn *hcon;
	u16 handle, min, max, latency, समयout;

	handle = le16_to_cpu(ev->handle);
	min = le16_to_cpu(ev->पूर्णांकerval_min);
	max = le16_to_cpu(ev->पूर्णांकerval_max);
	latency = le16_to_cpu(ev->latency);
	समयout = le16_to_cpu(ev->समयout);

	hcon = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (!hcon || hcon->state != BT_CONNECTED)
		वापस send_conn_param_neg_reply(hdev, handle,
						 HCI_ERROR_UNKNOWN_CONN_ID);

	अगर (hci_check_conn_params(min, max, latency, समयout))
		वापस send_conn_param_neg_reply(hdev, handle,
						 HCI_ERROR_INVALID_LL_PARAMS);

	अगर (hcon->role == HCI_ROLE_MASTER) अणु
		काष्ठा hci_conn_params *params;
		u8 store_hपूर्णांक;

		hci_dev_lock(hdev);

		params = hci_conn_params_lookup(hdev, &hcon->dst,
						hcon->dst_type);
		अगर (params) अणु
			params->conn_min_पूर्णांकerval = min;
			params->conn_max_पूर्णांकerval = max;
			params->conn_latency = latency;
			params->supervision_समयout = समयout;
			store_hपूर्णांक = 0x01;
		पूर्ण अन्यथा अणु
			store_hपूर्णांक = 0x00;
		पूर्ण

		hci_dev_unlock(hdev);

		mgmt_new_conn_param(hdev, &hcon->dst, hcon->dst_type,
				    store_hपूर्णांक, min, max, latency, समयout);
	पूर्ण

	cp.handle = ev->handle;
	cp.पूर्णांकerval_min = ev->पूर्णांकerval_min;
	cp.पूर्णांकerval_max = ev->पूर्णांकerval_max;
	cp.latency = ev->latency;
	cp.समयout = ev->समयout;
	cp.min_ce_len = 0;
	cp.max_ce_len = 0;

	hci_send_cmd(hdev, HCI_OP_LE_CONN_PARAM_REQ_REPLY, माप(cp), &cp);
पूर्ण

अटल व्योम hci_le_direct_adv_report_evt(काष्ठा hci_dev *hdev,
					 काष्ठा sk_buff *skb)
अणु
	u8 num_reports = skb->data[0];
	काष्ठा hci_ev_le_direct_adv_info *ev = (व्योम *)&skb->data[1];

	अगर (!num_reports || skb->len < num_reports * माप(*ev) + 1)
		वापस;

	hci_dev_lock(hdev);

	क्रम (; num_reports; num_reports--, ev++)
		process_adv_report(hdev, ev->evt_type, &ev->bdaddr,
				   ev->bdaddr_type, &ev->direct_addr,
				   ev->direct_addr_type, ev->rssi, शून्य, 0,
				   false);

	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_le_phy_update_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_phy_update_complete *ev = (व्योम *) skb->data;
	काष्ठा hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	अगर (ev->status)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	अगर (!conn)
		जाओ unlock;

	conn->le_tx_phy = ev->tx_phy;
	conn->le_rx_phy = ev->rx_phy;

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम hci_le_meta_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_meta *le_ev = (व्योम *) skb->data;

	skb_pull(skb, माप(*le_ev));

	चयन (le_ev->subevent) अणु
	हाल HCI_EV_LE_CONN_COMPLETE:
		hci_le_conn_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_CONN_UPDATE_COMPLETE:
		hci_le_conn_update_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_ADVERTISING_REPORT:
		hci_le_adv_report_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_REMOTE_FEAT_COMPLETE:
		hci_le_remote_feat_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_LTK_REQ:
		hci_le_ltk_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_REMOTE_CONN_PARAM_REQ:
		hci_le_remote_conn_param_req_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_सूचीECT_ADV_REPORT:
		hci_le_direct_adv_report_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_PHY_UPDATE_COMPLETE:
		hci_le_phy_update_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_EXT_ADV_REPORT:
		hci_le_ext_adv_report_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_ENHANCED_CONN_COMPLETE:
		hci_le_enh_conn_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_EXT_ADV_SET_TERM:
		hci_le_ext_adv_term_evt(hdev, skb);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool hci_get_cmd_complete(काष्ठा hci_dev *hdev, u16 opcode,
				 u8 event, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_cmd_complete *ev;
	काष्ठा hci_event_hdr *hdr;

	अगर (!skb)
		वापस false;

	अगर (skb->len < माप(*hdr)) अणु
		bt_dev_err(hdev, "too short HCI event");
		वापस false;
	पूर्ण

	hdr = (व्योम *) skb->data;
	skb_pull(skb, HCI_EVENT_HDR_SIZE);

	अगर (event) अणु
		अगर (hdr->evt != event)
			वापस false;
		वापस true;
	पूर्ण

	/* Check अगर request ended in Command Status - no way to retreive
	 * any extra parameters in this हाल.
	 */
	अगर (hdr->evt == HCI_EV_CMD_STATUS)
		वापस false;

	अगर (hdr->evt != HCI_EV_CMD_COMPLETE) अणु
		bt_dev_err(hdev, "last event is not cmd complete (0x%2.2x)",
			   hdr->evt);
		वापस false;
	पूर्ण

	अगर (skb->len < माप(*ev)) अणु
		bt_dev_err(hdev, "too short cmd_complete event");
		वापस false;
	पूर्ण

	ev = (व्योम *) skb->data;
	skb_pull(skb, माप(*ev));

	अगर (opcode != __le16_to_cpu(ev->opcode)) अणु
		BT_DBG("opcode doesn't match (0x%2.2x != 0x%2.2x)", opcode,
		       __le16_to_cpu(ev->opcode));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम hci_store_wake_reason(काष्ठा hci_dev *hdev, u8 event,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_ev_le_advertising_info *adv;
	काष्ठा hci_ev_le_direct_adv_info *direct_adv;
	काष्ठा hci_ev_le_ext_adv_report *ext_adv;
	स्थिर काष्ठा hci_ev_conn_complete *conn_complete = (व्योम *)skb->data;
	स्थिर काष्ठा hci_ev_conn_request *conn_request = (व्योम *)skb->data;

	hci_dev_lock(hdev);

	/* If we are currently suspended and this is the first BT event seen,
	 * save the wake reason associated with the event.
	 */
	अगर (!hdev->suspended || hdev->wake_reason)
		जाओ unlock;

	/* Default to remote wake. Values क्रम wake_reason are करोcumented in the
	 * Bluez mgmt api करोcs.
	 */
	hdev->wake_reason = MGMT_WAKE_REASON_REMOTE_WAKE;

	/* Once configured क्रम remote wakeup, we should only wake up क्रम
	 * reconnections. It's useful to see which device is waking us up so
	 * keep track of the bdaddr of the connection event that woke us up.
	 */
	अगर (event == HCI_EV_CONN_REQUEST) अणु
		bacpy(&hdev->wake_addr, &conn_complete->bdaddr);
		hdev->wake_addr_type = BDADDR_BREDR;
	पूर्ण अन्यथा अगर (event == HCI_EV_CONN_COMPLETE) अणु
		bacpy(&hdev->wake_addr, &conn_request->bdaddr);
		hdev->wake_addr_type = BDADDR_BREDR;
	पूर्ण अन्यथा अगर (event == HCI_EV_LE_META) अणु
		काष्ठा hci_ev_le_meta *le_ev = (व्योम *)skb->data;
		u8 subevent = le_ev->subevent;
		u8 *ptr = &skb->data[माप(*le_ev)];
		u8 num_reports = *ptr;

		अगर ((subevent == HCI_EV_LE_ADVERTISING_REPORT ||
		     subevent == HCI_EV_LE_सूचीECT_ADV_REPORT ||
		     subevent == HCI_EV_LE_EXT_ADV_REPORT) &&
		    num_reports) अणु
			adv = (व्योम *)(ptr + 1);
			direct_adv = (व्योम *)(ptr + 1);
			ext_adv = (व्योम *)(ptr + 1);

			चयन (subevent) अणु
			हाल HCI_EV_LE_ADVERTISING_REPORT:
				bacpy(&hdev->wake_addr, &adv->bdaddr);
				hdev->wake_addr_type = adv->bdaddr_type;
				अवरोध;
			हाल HCI_EV_LE_सूचीECT_ADV_REPORT:
				bacpy(&hdev->wake_addr, &direct_adv->bdaddr);
				hdev->wake_addr_type = direct_adv->bdaddr_type;
				अवरोध;
			हाल HCI_EV_LE_EXT_ADV_REPORT:
				bacpy(&hdev->wake_addr, &ext_adv->bdaddr);
				hdev->wake_addr_type = ext_adv->bdaddr_type;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hdev->wake_reason = MGMT_WAKE_REASON_UNEXPECTED;
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

व्योम hci_event_packet(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_event_hdr *hdr = (व्योम *) skb->data;
	hci_req_complete_t req_complete = शून्य;
	hci_req_complete_skb_t req_complete_skb = शून्य;
	काष्ठा sk_buff *orig_skb = शून्य;
	u8 status = 0, event = hdr->evt, req_evt = 0;
	u16 opcode = HCI_OP_NOP;

	अगर (!event) अणु
		bt_dev_warn(hdev, "Received unexpected HCI Event 00000000");
		जाओ करोne;
	पूर्ण

	अगर (hdev->sent_cmd && bt_cb(hdev->sent_cmd)->hci.req_event == event) अणु
		काष्ठा hci_command_hdr *cmd_hdr = (व्योम *) hdev->sent_cmd->data;
		opcode = __le16_to_cpu(cmd_hdr->opcode);
		hci_req_cmd_complete(hdev, opcode, status, &req_complete,
				     &req_complete_skb);
		req_evt = event;
	पूर्ण

	/* If it looks like we might end up having to call
	 * req_complete_skb, store a pristine copy of the skb since the
	 * various handlers may modअगरy the original one through
	 * skb_pull() calls, etc.
	 */
	अगर (req_complete_skb || event == HCI_EV_CMD_STATUS ||
	    event == HCI_EV_CMD_COMPLETE)
		orig_skb = skb_clone(skb, GFP_KERNEL);

	skb_pull(skb, HCI_EVENT_HDR_SIZE);

	/* Store wake reason अगर we're suspended */
	hci_store_wake_reason(hdev, event, skb);

	चयन (event) अणु
	हाल HCI_EV_INQUIRY_COMPLETE:
		hci_inquiry_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_INQUIRY_RESULT:
		hci_inquiry_result_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_CONN_COMPLETE:
		hci_conn_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_CONN_REQUEST:
		hci_conn_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_DISCONN_COMPLETE:
		hci_disconn_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_AUTH_COMPLETE:
		hci_auth_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_REMOTE_NAME:
		hci_remote_name_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_ENCRYPT_CHANGE:
		hci_encrypt_change_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_CHANGE_LINK_KEY_COMPLETE:
		hci_change_link_key_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_REMOTE_FEATURES:
		hci_remote_features_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_CMD_COMPLETE:
		hci_cmd_complete_evt(hdev, skb, &opcode, &status,
				     &req_complete, &req_complete_skb);
		अवरोध;

	हाल HCI_EV_CMD_STATUS:
		hci_cmd_status_evt(hdev, skb, &opcode, &status, &req_complete,
				   &req_complete_skb);
		अवरोध;

	हाल HCI_EV_HARDWARE_ERROR:
		hci_hardware_error_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_ROLE_CHANGE:
		hci_role_change_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_NUM_COMP_PKTS:
		hci_num_comp_pkts_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_MODE_CHANGE:
		hci_mode_change_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_PIN_CODE_REQ:
		hci_pin_code_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LINK_KEY_REQ:
		hci_link_key_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LINK_KEY_NOTIFY:
		hci_link_key_notअगरy_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_CLOCK_OFFSET:
		hci_घड़ी_offset_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_PKT_TYPE_CHANGE:
		hci_pkt_type_change_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_PSCAN_REP_MODE:
		hci_pscan_rep_mode_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_INQUIRY_RESULT_WITH_RSSI:
		hci_inquiry_result_with_rssi_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_REMOTE_EXT_FEATURES:
		hci_remote_ext_features_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_SYNC_CONN_COMPLETE:
		hci_sync_conn_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_EXTENDED_INQUIRY_RESULT:
		hci_extended_inquiry_result_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_KEY_REFRESH_COMPLETE:
		hci_key_refresh_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_IO_CAPA_REQUEST:
		hci_io_capa_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_IO_CAPA_REPLY:
		hci_io_capa_reply_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_USER_CONFIRM_REQUEST:
		hci_user_confirm_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_USER_PASSKEY_REQUEST:
		hci_user_passkey_request_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_USER_PASSKEY_NOTIFY:
		hci_user_passkey_notअगरy_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_KEYPRESS_NOTIFY:
		hci_keypress_notअगरy_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_SIMPLE_PAIR_COMPLETE:
		hci_simple_pair_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_REMOTE_HOST_FEATURES:
		hci_remote_host_features_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LE_META:
		hci_le_meta_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_REMOTE_OOB_DATA_REQUEST:
		hci_remote_oob_data_request_evt(hdev, skb);
		अवरोध;

#अगर IS_ENABLED(CONFIG_BT_HS)
	हाल HCI_EV_CHANNEL_SELECTED:
		hci_chan_selected_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_PHY_LINK_COMPLETE:
		hci_phy_link_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_LOGICAL_LINK_COMPLETE:
		hci_loglink_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_DISCONN_LOGICAL_LINK_COMPLETE:
		hci_disconn_loglink_complete_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_DISCONN_PHY_LINK_COMPLETE:
		hci_disconn_phylink_complete_evt(hdev, skb);
		अवरोध;
#पूर्ण_अगर

	हाल HCI_EV_NUM_COMP_BLOCKS:
		hci_num_comp_blocks_evt(hdev, skb);
		अवरोध;

	हाल HCI_EV_VENDOR:
		msft_venकरोr_evt(hdev, skb);
		अवरोध;

	शेष:
		BT_DBG("%s event 0x%2.2x", hdev->name, event);
		अवरोध;
	पूर्ण

	अगर (req_complete) अणु
		req_complete(hdev, status, opcode);
	पूर्ण अन्यथा अगर (req_complete_skb) अणु
		अगर (!hci_get_cmd_complete(hdev, opcode, req_evt, orig_skb)) अणु
			kमुक्त_skb(orig_skb);
			orig_skb = शून्य;
		पूर्ण
		req_complete_skb(hdev, status, opcode, orig_skb);
	पूर्ण

करोne:
	kमुक्त_skb(orig_skb);
	kमुक्त_skb(skb);
	hdev->stat.evt_rx++;
पूर्ण
