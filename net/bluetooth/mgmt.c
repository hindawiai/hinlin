<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2010  Nokia Corporation
   Copyright (C) 2011-2012 Intel Corporation

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

/* Bluetooth HCI Management पूर्णांकerface */

#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/hci_sock.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "hci_request.h"
#समावेश "smp.h"
#समावेश "mgmt_util.h"
#समावेश "mgmt_config.h"
#समावेश "msft.h"

#घोषणा MGMT_VERSION	1
#घोषणा MGMT_REVISION	20

अटल स्थिर u16 mgmt_commands[] = अणु
	MGMT_OP_READ_INDEX_LIST,
	MGMT_OP_READ_INFO,
	MGMT_OP_SET_POWERED,
	MGMT_OP_SET_DISCOVERABLE,
	MGMT_OP_SET_CONNECTABLE,
	MGMT_OP_SET_FAST_CONNECTABLE,
	MGMT_OP_SET_BONDABLE,
	MGMT_OP_SET_LINK_SECURITY,
	MGMT_OP_SET_SSP,
	MGMT_OP_SET_HS,
	MGMT_OP_SET_LE,
	MGMT_OP_SET_DEV_CLASS,
	MGMT_OP_SET_LOCAL_NAME,
	MGMT_OP_ADD_UUID,
	MGMT_OP_REMOVE_UUID,
	MGMT_OP_LOAD_LINK_KEYS,
	MGMT_OP_LOAD_LONG_TERM_KEYS,
	MGMT_OP_DISCONNECT,
	MGMT_OP_GET_CONNECTIONS,
	MGMT_OP_PIN_CODE_REPLY,
	MGMT_OP_PIN_CODE_NEG_REPLY,
	MGMT_OP_SET_IO_CAPABILITY,
	MGMT_OP_PAIR_DEVICE,
	MGMT_OP_CANCEL_PAIR_DEVICE,
	MGMT_OP_UNPAIR_DEVICE,
	MGMT_OP_USER_CONFIRM_REPLY,
	MGMT_OP_USER_CONFIRM_NEG_REPLY,
	MGMT_OP_USER_PASSKEY_REPLY,
	MGMT_OP_USER_PASSKEY_NEG_REPLY,
	MGMT_OP_READ_LOCAL_OOB_DATA,
	MGMT_OP_ADD_REMOTE_OOB_DATA,
	MGMT_OP_REMOVE_REMOTE_OOB_DATA,
	MGMT_OP_START_DISCOVERY,
	MGMT_OP_STOP_DISCOVERY,
	MGMT_OP_CONFIRM_NAME,
	MGMT_OP_BLOCK_DEVICE,
	MGMT_OP_UNBLOCK_DEVICE,
	MGMT_OP_SET_DEVICE_ID,
	MGMT_OP_SET_ADVERTISING,
	MGMT_OP_SET_BREDR,
	MGMT_OP_SET_STATIC_ADDRESS,
	MGMT_OP_SET_SCAN_PARAMS,
	MGMT_OP_SET_SECURE_CONN,
	MGMT_OP_SET_DEBUG_KEYS,
	MGMT_OP_SET_PRIVACY,
	MGMT_OP_LOAD_IRKS,
	MGMT_OP_GET_CONN_INFO,
	MGMT_OP_GET_CLOCK_INFO,
	MGMT_OP_ADD_DEVICE,
	MGMT_OP_REMOVE_DEVICE,
	MGMT_OP_LOAD_CONN_PARAM,
	MGMT_OP_READ_UNCONF_INDEX_LIST,
	MGMT_OP_READ_CONFIG_INFO,
	MGMT_OP_SET_EXTERNAL_CONFIG,
	MGMT_OP_SET_PUBLIC_ADDRESS,
	MGMT_OP_START_SERVICE_DISCOVERY,
	MGMT_OP_READ_LOCAL_OOB_EXT_DATA,
	MGMT_OP_READ_EXT_INDEX_LIST,
	MGMT_OP_READ_ADV_FEATURES,
	MGMT_OP_ADD_ADVERTISING,
	MGMT_OP_REMOVE_ADVERTISING,
	MGMT_OP_GET_ADV_SIZE_INFO,
	MGMT_OP_START_LIMITED_DISCOVERY,
	MGMT_OP_READ_EXT_INFO,
	MGMT_OP_SET_APPEARANCE,
	MGMT_OP_GET_PHY_CONFIGURATION,
	MGMT_OP_SET_PHY_CONFIGURATION,
	MGMT_OP_SET_BLOCKED_KEYS,
	MGMT_OP_SET_WIDEBAND_SPEECH,
	MGMT_OP_READ_CONTROLLER_CAP,
	MGMT_OP_READ_EXP_FEATURES_INFO,
	MGMT_OP_SET_EXP_FEATURE,
	MGMT_OP_READ_DEF_SYSTEM_CONFIG,
	MGMT_OP_SET_DEF_SYSTEM_CONFIG,
	MGMT_OP_READ_DEF_RUNTIME_CONFIG,
	MGMT_OP_SET_DEF_RUNTIME_CONFIG,
	MGMT_OP_GET_DEVICE_FLAGS,
	MGMT_OP_SET_DEVICE_FLAGS,
	MGMT_OP_READ_ADV_MONITOR_FEATURES,
	MGMT_OP_ADD_ADV_PATTERNS_MONITOR,
	MGMT_OP_REMOVE_ADV_MONITOR,
	MGMT_OP_ADD_EXT_ADV_PARAMS,
	MGMT_OP_ADD_EXT_ADV_DATA,
	MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI,
पूर्ण;

अटल स्थिर u16 mgmt_events[] = अणु
	MGMT_EV_CONTROLLER_ERROR,
	MGMT_EV_INDEX_ADDED,
	MGMT_EV_INDEX_REMOVED,
	MGMT_EV_NEW_SETTINGS,
	MGMT_EV_CLASS_OF_DEV_CHANGED,
	MGMT_EV_LOCAL_NAME_CHANGED,
	MGMT_EV_NEW_LINK_KEY,
	MGMT_EV_NEW_LONG_TERM_KEY,
	MGMT_EV_DEVICE_CONNECTED,
	MGMT_EV_DEVICE_DISCONNECTED,
	MGMT_EV_CONNECT_FAILED,
	MGMT_EV_PIN_CODE_REQUEST,
	MGMT_EV_USER_CONFIRM_REQUEST,
	MGMT_EV_USER_PASSKEY_REQUEST,
	MGMT_EV_AUTH_FAILED,
	MGMT_EV_DEVICE_FOUND,
	MGMT_EV_DISCOVERING,
	MGMT_EV_DEVICE_BLOCKED,
	MGMT_EV_DEVICE_UNBLOCKED,
	MGMT_EV_DEVICE_UNPAIRED,
	MGMT_EV_PASSKEY_NOTIFY,
	MGMT_EV_NEW_IRK,
	MGMT_EV_NEW_CSRK,
	MGMT_EV_DEVICE_ADDED,
	MGMT_EV_DEVICE_REMOVED,
	MGMT_EV_NEW_CONN_PARAM,
	MGMT_EV_UNCONF_INDEX_ADDED,
	MGMT_EV_UNCONF_INDEX_REMOVED,
	MGMT_EV_NEW_CONFIG_OPTIONS,
	MGMT_EV_EXT_INDEX_ADDED,
	MGMT_EV_EXT_INDEX_REMOVED,
	MGMT_EV_LOCAL_OOB_DATA_UPDATED,
	MGMT_EV_ADVERTISING_ADDED,
	MGMT_EV_ADVERTISING_REMOVED,
	MGMT_EV_EXT_INFO_CHANGED,
	MGMT_EV_PHY_CONFIGURATION_CHANGED,
	MGMT_EV_EXP_FEATURE_CHANGED,
	MGMT_EV_DEVICE_FLAGS_CHANGED,
	MGMT_EV_ADV_MONITOR_ADDED,
	MGMT_EV_ADV_MONITOR_REMOVED,
	MGMT_EV_CONTROLLER_SUSPEND,
	MGMT_EV_CONTROLLER_RESUME,
पूर्ण;

अटल स्थिर u16 mgmt_untrusted_commands[] = अणु
	MGMT_OP_READ_INDEX_LIST,
	MGMT_OP_READ_INFO,
	MGMT_OP_READ_UNCONF_INDEX_LIST,
	MGMT_OP_READ_CONFIG_INFO,
	MGMT_OP_READ_EXT_INDEX_LIST,
	MGMT_OP_READ_EXT_INFO,
	MGMT_OP_READ_CONTROLLER_CAP,
	MGMT_OP_READ_EXP_FEATURES_INFO,
	MGMT_OP_READ_DEF_SYSTEM_CONFIG,
	MGMT_OP_READ_DEF_RUNTIME_CONFIG,
पूर्ण;

अटल स्थिर u16 mgmt_untrusted_events[] = अणु
	MGMT_EV_INDEX_ADDED,
	MGMT_EV_INDEX_REMOVED,
	MGMT_EV_NEW_SETTINGS,
	MGMT_EV_CLASS_OF_DEV_CHANGED,
	MGMT_EV_LOCAL_NAME_CHANGED,
	MGMT_EV_UNCONF_INDEX_ADDED,
	MGMT_EV_UNCONF_INDEX_REMOVED,
	MGMT_EV_NEW_CONFIG_OPTIONS,
	MGMT_EV_EXT_INDEX_ADDED,
	MGMT_EV_EXT_INDEX_REMOVED,
	MGMT_EV_EXT_INFO_CHANGED,
	MGMT_EV_EXP_FEATURE_CHANGED,
पूर्ण;

#घोषणा CACHE_TIMEOUT	msecs_to_jअगरfies(2 * 1000)

#घोषणा ZERO_KEY "\x00\x00\x00\x00\x00\x00\x00\x00" \
		 "\x00\x00\x00\x00\x00\x00\x00\x00"

/* HCI to MGMT error code conversion table */
अटल स्थिर u8 mgmt_status_table[] = अणु
	MGMT_STATUS_SUCCESS,
	MGMT_STATUS_UNKNOWN_COMMAND,	/* Unknown Command */
	MGMT_STATUS_NOT_CONNECTED,	/* No Connection */
	MGMT_STATUS_FAILED,		/* Hardware Failure */
	MGMT_STATUS_CONNECT_FAILED,	/* Page Timeout */
	MGMT_STATUS_AUTH_FAILED,	/* Authentication Failed */
	MGMT_STATUS_AUTH_FAILED,	/* PIN or Key Missing */
	MGMT_STATUS_NO_RESOURCES,	/* Memory Full */
	MGMT_STATUS_TIMEOUT,		/* Connection Timeout */
	MGMT_STATUS_NO_RESOURCES,	/* Max Number of Connections */
	MGMT_STATUS_NO_RESOURCES,	/* Max Number of SCO Connections */
	MGMT_STATUS_ALREADY_CONNECTED,	/* ACL Connection Exists */
	MGMT_STATUS_BUSY,		/* Command Disallowed */
	MGMT_STATUS_NO_RESOURCES,	/* Rejected Limited Resources */
	MGMT_STATUS_REJECTED,		/* Rejected Security */
	MGMT_STATUS_REJECTED,		/* Rejected Personal */
	MGMT_STATUS_TIMEOUT,		/* Host Timeout */
	MGMT_STATUS_NOT_SUPPORTED,	/* Unsupported Feature */
	MGMT_STATUS_INVALID_PARAMS,	/* Invalid Parameters */
	MGMT_STATUS_DISCONNECTED,	/* OE User Ended Connection */
	MGMT_STATUS_NO_RESOURCES,	/* OE Low Resources */
	MGMT_STATUS_DISCONNECTED,	/* OE Power Off */
	MGMT_STATUS_DISCONNECTED,	/* Connection Terminated */
	MGMT_STATUS_BUSY,		/* Repeated Attempts */
	MGMT_STATUS_REJECTED,		/* Pairing Not Allowed */
	MGMT_STATUS_FAILED,		/* Unknown LMP PDU */
	MGMT_STATUS_NOT_SUPPORTED,	/* Unsupported Remote Feature */
	MGMT_STATUS_REJECTED,		/* SCO Offset Rejected */
	MGMT_STATUS_REJECTED,		/* SCO Interval Rejected */
	MGMT_STATUS_REJECTED,		/* Air Mode Rejected */
	MGMT_STATUS_INVALID_PARAMS,	/* Invalid LMP Parameters */
	MGMT_STATUS_FAILED,		/* Unspecअगरied Error */
	MGMT_STATUS_NOT_SUPPORTED,	/* Unsupported LMP Parameter Value */
	MGMT_STATUS_FAILED,		/* Role Change Not Allowed */
	MGMT_STATUS_TIMEOUT,		/* LMP Response Timeout */
	MGMT_STATUS_FAILED,		/* LMP Error Transaction Collision */
	MGMT_STATUS_FAILED,		/* LMP PDU Not Allowed */
	MGMT_STATUS_REJECTED,		/* Encryption Mode Not Accepted */
	MGMT_STATUS_FAILED,		/* Unit Link Key Used */
	MGMT_STATUS_NOT_SUPPORTED,	/* QoS Not Supported */
	MGMT_STATUS_TIMEOUT,		/* Instant Passed */
	MGMT_STATUS_NOT_SUPPORTED,	/* Pairing Not Supported */
	MGMT_STATUS_FAILED,		/* Transaction Collision */
	MGMT_STATUS_INVALID_PARAMS,	/* Unacceptable Parameter */
	MGMT_STATUS_REJECTED,		/* QoS Rejected */
	MGMT_STATUS_NOT_SUPPORTED,	/* Classअगरication Not Supported */
	MGMT_STATUS_REJECTED,		/* Insufficient Security */
	MGMT_STATUS_INVALID_PARAMS,	/* Parameter Out Of Range */
	MGMT_STATUS_BUSY,		/* Role Switch Pending */
	MGMT_STATUS_FAILED,		/* Slot Violation */
	MGMT_STATUS_FAILED,		/* Role Switch Failed */
	MGMT_STATUS_INVALID_PARAMS,	/* EIR Too Large */
	MGMT_STATUS_NOT_SUPPORTED,	/* Simple Pairing Not Supported */
	MGMT_STATUS_BUSY,		/* Host Busy Pairing */
	MGMT_STATUS_REJECTED,		/* Rejected, No Suitable Channel */
	MGMT_STATUS_BUSY,		/* Controller Busy */
	MGMT_STATUS_INVALID_PARAMS,	/* Unsuitable Connection Interval */
	MGMT_STATUS_TIMEOUT,		/* Directed Advertising Timeout */
	MGMT_STATUS_AUTH_FAILED,	/* Terminated Due to MIC Failure */
	MGMT_STATUS_CONNECT_FAILED,	/* Connection Establishment Failed */
	MGMT_STATUS_CONNECT_FAILED,	/* MAC Connection Failed */
पूर्ण;

अटल u8 mgmt_status(u8 hci_status)
अणु
	अगर (hci_status < ARRAY_SIZE(mgmt_status_table))
		वापस mgmt_status_table[hci_status];

	वापस MGMT_STATUS_FAILED;
पूर्ण

अटल पूर्णांक mgmt_index_event(u16 event, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 len, पूर्णांक flag)
अणु
	वापस mgmt_send_event(event, hdev, HCI_CHANNEL_CONTROL, data, len,
			       flag, शून्य);
पूर्ण

अटल पूर्णांक mgmt_limited_event(u16 event, काष्ठा hci_dev *hdev, व्योम *data,
			      u16 len, पूर्णांक flag, काष्ठा sock *skip_sk)
अणु
	वापस mgmt_send_event(event, hdev, HCI_CHANNEL_CONTROL, data, len,
			       flag, skip_sk);
पूर्ण

अटल पूर्णांक mgmt_event(u16 event, काष्ठा hci_dev *hdev, व्योम *data, u16 len,
		      काष्ठा sock *skip_sk)
अणु
	वापस mgmt_send_event(event, hdev, HCI_CHANNEL_CONTROL, data, len,
			       HCI_SOCK_TRUSTED, skip_sk);
पूर्ण

अटल u8 le_addr_type(u8 mgmt_addr_type)
अणु
	अगर (mgmt_addr_type == BDADDR_LE_PUBLIC)
		वापस ADDR_LE_DEV_PUBLIC;
	अन्यथा
		वापस ADDR_LE_DEV_RANDOM;
पूर्ण

व्योम mgmt_fill_version_info(व्योम *ver)
अणु
	काष्ठा mgmt_rp_पढ़ो_version *rp = ver;

	rp->version = MGMT_VERSION;
	rp->revision = cpu_to_le16(MGMT_REVISION);
पूर्ण

अटल पूर्णांक पढ़ो_version(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_version rp;

	bt_dev_dbg(hdev, "sock %p", sk);

	mgmt_fill_version_info(&rp);

	वापस mgmt_cmd_complete(sk, MGMT_INDEX_NONE, MGMT_OP_READ_VERSION, 0,
				 &rp, माप(rp));
पूर्ण

अटल पूर्णांक पढ़ो_commands(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_commands *rp;
	u16 num_commands, num_events;
	माप_प्रकार rp_size;
	पूर्णांक i, err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (hci_sock_test_flag(sk, HCI_SOCK_TRUSTED)) अणु
		num_commands = ARRAY_SIZE(mgmt_commands);
		num_events = ARRAY_SIZE(mgmt_events);
	पूर्ण अन्यथा अणु
		num_commands = ARRAY_SIZE(mgmt_untrusted_commands);
		num_events = ARRAY_SIZE(mgmt_untrusted_events);
	पूर्ण

	rp_size = माप(*rp) + ((num_commands + num_events) * माप(u16));

	rp = kदो_स्मृति(rp_size, GFP_KERNEL);
	अगर (!rp)
		वापस -ENOMEM;

	rp->num_commands = cpu_to_le16(num_commands);
	rp->num_events = cpu_to_le16(num_events);

	अगर (hci_sock_test_flag(sk, HCI_SOCK_TRUSTED)) अणु
		__le16 *opcode = rp->opcodes;

		क्रम (i = 0; i < num_commands; i++, opcode++)
			put_unaligned_le16(mgmt_commands[i], opcode);

		क्रम (i = 0; i < num_events; i++, opcode++)
			put_unaligned_le16(mgmt_events[i], opcode);
	पूर्ण अन्यथा अणु
		__le16 *opcode = rp->opcodes;

		क्रम (i = 0; i < num_commands; i++, opcode++)
			put_unaligned_le16(mgmt_untrusted_commands[i], opcode);

		क्रम (i = 0; i < num_events; i++, opcode++)
			put_unaligned_le16(mgmt_untrusted_events[i], opcode);
	पूर्ण

	err = mgmt_cmd_complete(sk, MGMT_INDEX_NONE, MGMT_OP_READ_COMMANDS, 0,
				rp, rp_size);
	kमुक्त(rp);

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_index_list(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_index_list *rp;
	काष्ठा hci_dev *d;
	माप_प्रकार rp_len;
	u16 count;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	पढ़ो_lock(&hci_dev_list_lock);

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (d->dev_type == HCI_PRIMARY &&
		    !hci_dev_test_flag(d, HCI_UNCONFIGURED))
			count++;
	पूर्ण

	rp_len = माप(*rp) + (2 * count);
	rp = kदो_स्मृति(rp_len, GFP_ATOMIC);
	अगर (!rp) अणु
		पढ़ो_unlock(&hci_dev_list_lock);
		वापस -ENOMEM;
	पूर्ण

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (hci_dev_test_flag(d, HCI_SETUP) ||
		    hci_dev_test_flag(d, HCI_CONFIG) ||
		    hci_dev_test_flag(d, HCI_USER_CHANNEL))
			जारी;

		/* Devices marked as raw-only are neither configured
		 * nor unconfigured controllers.
		 */
		अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &d->quirks))
			जारी;

		अगर (d->dev_type == HCI_PRIMARY &&
		    !hci_dev_test_flag(d, HCI_UNCONFIGURED)) अणु
			rp->index[count++] = cpu_to_le16(d->id);
			bt_dev_dbg(hdev, "Added hci%u", d->id);
		पूर्ण
	पूर्ण

	rp->num_controllers = cpu_to_le16(count);
	rp_len = माप(*rp) + (2 * count);

	पढ़ो_unlock(&hci_dev_list_lock);

	err = mgmt_cmd_complete(sk, MGMT_INDEX_NONE, MGMT_OP_READ_INDEX_LIST,
				0, rp, rp_len);

	kमुक्त(rp);

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_unconf_index_list(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				  व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_unconf_index_list *rp;
	काष्ठा hci_dev *d;
	माप_प्रकार rp_len;
	u16 count;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	पढ़ो_lock(&hci_dev_list_lock);

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (d->dev_type == HCI_PRIMARY &&
		    hci_dev_test_flag(d, HCI_UNCONFIGURED))
			count++;
	पूर्ण

	rp_len = माप(*rp) + (2 * count);
	rp = kदो_स्मृति(rp_len, GFP_ATOMIC);
	अगर (!rp) अणु
		पढ़ो_unlock(&hci_dev_list_lock);
		वापस -ENOMEM;
	पूर्ण

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (hci_dev_test_flag(d, HCI_SETUP) ||
		    hci_dev_test_flag(d, HCI_CONFIG) ||
		    hci_dev_test_flag(d, HCI_USER_CHANNEL))
			जारी;

		/* Devices marked as raw-only are neither configured
		 * nor unconfigured controllers.
		 */
		अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &d->quirks))
			जारी;

		अगर (d->dev_type == HCI_PRIMARY &&
		    hci_dev_test_flag(d, HCI_UNCONFIGURED)) अणु
			rp->index[count++] = cpu_to_le16(d->id);
			bt_dev_dbg(hdev, "Added hci%u", d->id);
		पूर्ण
	पूर्ण

	rp->num_controllers = cpu_to_le16(count);
	rp_len = माप(*rp) + (2 * count);

	पढ़ो_unlock(&hci_dev_list_lock);

	err = mgmt_cmd_complete(sk, MGMT_INDEX_NONE,
				MGMT_OP_READ_UNCONF_INDEX_LIST, 0, rp, rp_len);

	kमुक्त(rp);

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_ext_index_list(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_ext_index_list *rp;
	काष्ठा hci_dev *d;
	u16 count;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	पढ़ो_lock(&hci_dev_list_lock);

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (d->dev_type == HCI_PRIMARY || d->dev_type == HCI_AMP)
			count++;
	पूर्ण

	rp = kदो_स्मृति(काष्ठा_size(rp, entry, count), GFP_ATOMIC);
	अगर (!rp) अणु
		पढ़ो_unlock(&hci_dev_list_lock);
		वापस -ENOMEM;
	पूर्ण

	count = 0;
	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (hci_dev_test_flag(d, HCI_SETUP) ||
		    hci_dev_test_flag(d, HCI_CONFIG) ||
		    hci_dev_test_flag(d, HCI_USER_CHANNEL))
			जारी;

		/* Devices marked as raw-only are neither configured
		 * nor unconfigured controllers.
		 */
		अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &d->quirks))
			जारी;

		अगर (d->dev_type == HCI_PRIMARY) अणु
			अगर (hci_dev_test_flag(d, HCI_UNCONFIGURED))
				rp->entry[count].type = 0x01;
			अन्यथा
				rp->entry[count].type = 0x00;
		पूर्ण अन्यथा अगर (d->dev_type == HCI_AMP) अणु
			rp->entry[count].type = 0x02;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		rp->entry[count].bus = d->bus;
		rp->entry[count++].index = cpu_to_le16(d->id);
		bt_dev_dbg(hdev, "Added hci%u", d->id);
	पूर्ण

	rp->num_controllers = cpu_to_le16(count);

	पढ़ो_unlock(&hci_dev_list_lock);

	/* If this command is called at least once, then all the
	 * शेष index and unconfigured index events are disabled
	 * and from now on only extended index events are used.
	 */
	hci_sock_set_flag(sk, HCI_MGMT_EXT_INDEX_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_INDEX_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_UNCONF_INDEX_EVENTS);

	err = mgmt_cmd_complete(sk, MGMT_INDEX_NONE,
				MGMT_OP_READ_EXT_INDEX_LIST, 0, rp,
				काष्ठा_size(rp, entry, count));

	kमुक्त(rp);

	वापस err;
पूर्ण

अटल bool is_configured(काष्ठा hci_dev *hdev)
अणु
	अगर (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) &&
	    !hci_dev_test_flag(hdev, HCI_EXT_CONFIGURED))
		वापस false;

	अगर ((test_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks) ||
	     test_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks)) &&
	    !bacmp(&hdev->खुला_addr, BDADDR_ANY))
		वापस false;

	वापस true;
पूर्ण

अटल __le32 get_missing_options(काष्ठा hci_dev *hdev)
अणु
	u32 options = 0;

	अगर (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) &&
	    !hci_dev_test_flag(hdev, HCI_EXT_CONFIGURED))
		options |= MGMT_OPTION_EXTERNAL_CONFIG;

	अगर ((test_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks) ||
	     test_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks)) &&
	    !bacmp(&hdev->खुला_addr, BDADDR_ANY))
		options |= MGMT_OPTION_PUBLIC_ADDRESS;

	वापस cpu_to_le32(options);
पूर्ण

अटल पूर्णांक new_options(काष्ठा hci_dev *hdev, काष्ठा sock *skip)
अणु
	__le32 options = get_missing_options(hdev);

	वापस mgmt_limited_event(MGMT_EV_NEW_CONFIG_OPTIONS, hdev, &options,
				  माप(options), HCI_MGMT_OPTION_EVENTS, skip);
पूर्ण

अटल पूर्णांक send_options_rsp(काष्ठा sock *sk, u16 opcode, काष्ठा hci_dev *hdev)
अणु
	__le32 options = get_missing_options(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, opcode, 0, &options,
				 माप(options));
पूर्ण

अटल पूर्णांक पढ़ो_config_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			    व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_config_info rp;
	u32 options = 0;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	स_रखो(&rp, 0, माप(rp));
	rp.manufacturer = cpu_to_le16(hdev->manufacturer);

	अगर (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks))
		options |= MGMT_OPTION_EXTERNAL_CONFIG;

	अगर (hdev->set_bdaddr)
		options |= MGMT_OPTION_PUBLIC_ADDRESS;

	rp.supported_options = cpu_to_le32(options);
	rp.missing_options = get_missing_options(hdev);

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_CONFIG_INFO, 0,
				 &rp, माप(rp));
पूर्ण

अटल u32 get_supported_phys(काष्ठा hci_dev *hdev)
अणु
	u32 supported_phys = 0;

	अगर (lmp_bredr_capable(hdev)) अणु
		supported_phys |= MGMT_PHY_BR_1M_1SLOT;

		अगर (hdev->features[0][0] & LMP_3SLOT)
			supported_phys |= MGMT_PHY_BR_1M_3SLOT;

		अगर (hdev->features[0][0] & LMP_5SLOT)
			supported_phys |= MGMT_PHY_BR_1M_5SLOT;

		अगर (lmp_edr_2m_capable(hdev)) अणु
			supported_phys |= MGMT_PHY_EDR_2M_1SLOT;

			अगर (lmp_edr_3slot_capable(hdev))
				supported_phys |= MGMT_PHY_EDR_2M_3SLOT;

			अगर (lmp_edr_5slot_capable(hdev))
				supported_phys |= MGMT_PHY_EDR_2M_5SLOT;

			अगर (lmp_edr_3m_capable(hdev)) अणु
				supported_phys |= MGMT_PHY_EDR_3M_1SLOT;

				अगर (lmp_edr_3slot_capable(hdev))
					supported_phys |= MGMT_PHY_EDR_3M_3SLOT;

				अगर (lmp_edr_5slot_capable(hdev))
					supported_phys |= MGMT_PHY_EDR_3M_5SLOT;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (lmp_le_capable(hdev)) अणु
		supported_phys |= MGMT_PHY_LE_1M_TX;
		supported_phys |= MGMT_PHY_LE_1M_RX;

		अगर (hdev->le_features[1] & HCI_LE_PHY_2M) अणु
			supported_phys |= MGMT_PHY_LE_2M_TX;
			supported_phys |= MGMT_PHY_LE_2M_RX;
		पूर्ण

		अगर (hdev->le_features[1] & HCI_LE_PHY_CODED) अणु
			supported_phys |= MGMT_PHY_LE_CODED_TX;
			supported_phys |= MGMT_PHY_LE_CODED_RX;
		पूर्ण
	पूर्ण

	वापस supported_phys;
पूर्ण

अटल u32 get_selected_phys(काष्ठा hci_dev *hdev)
अणु
	u32 selected_phys = 0;

	अगर (lmp_bredr_capable(hdev)) अणु
		selected_phys |= MGMT_PHY_BR_1M_1SLOT;

		अगर (hdev->pkt_type & (HCI_DM3 | HCI_DH3))
			selected_phys |= MGMT_PHY_BR_1M_3SLOT;

		अगर (hdev->pkt_type & (HCI_DM5 | HCI_DH5))
			selected_phys |= MGMT_PHY_BR_1M_5SLOT;

		अगर (lmp_edr_2m_capable(hdev)) अणु
			अगर (!(hdev->pkt_type & HCI_2DH1))
				selected_phys |= MGMT_PHY_EDR_2M_1SLOT;

			अगर (lmp_edr_3slot_capable(hdev) &&
			    !(hdev->pkt_type & HCI_2DH3))
				selected_phys |= MGMT_PHY_EDR_2M_3SLOT;

			अगर (lmp_edr_5slot_capable(hdev) &&
			    !(hdev->pkt_type & HCI_2DH5))
				selected_phys |= MGMT_PHY_EDR_2M_5SLOT;

			अगर (lmp_edr_3m_capable(hdev)) अणु
				अगर (!(hdev->pkt_type & HCI_3DH1))
					selected_phys |= MGMT_PHY_EDR_3M_1SLOT;

				अगर (lmp_edr_3slot_capable(hdev) &&
				    !(hdev->pkt_type & HCI_3DH3))
					selected_phys |= MGMT_PHY_EDR_3M_3SLOT;

				अगर (lmp_edr_5slot_capable(hdev) &&
				    !(hdev->pkt_type & HCI_3DH5))
					selected_phys |= MGMT_PHY_EDR_3M_5SLOT;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (lmp_le_capable(hdev)) अणु
		अगर (hdev->le_tx_def_phys & HCI_LE_SET_PHY_1M)
			selected_phys |= MGMT_PHY_LE_1M_TX;

		अगर (hdev->le_rx_def_phys & HCI_LE_SET_PHY_1M)
			selected_phys |= MGMT_PHY_LE_1M_RX;

		अगर (hdev->le_tx_def_phys & HCI_LE_SET_PHY_2M)
			selected_phys |= MGMT_PHY_LE_2M_TX;

		अगर (hdev->le_rx_def_phys & HCI_LE_SET_PHY_2M)
			selected_phys |= MGMT_PHY_LE_2M_RX;

		अगर (hdev->le_tx_def_phys & HCI_LE_SET_PHY_CODED)
			selected_phys |= MGMT_PHY_LE_CODED_TX;

		अगर (hdev->le_rx_def_phys & HCI_LE_SET_PHY_CODED)
			selected_phys |= MGMT_PHY_LE_CODED_RX;
	पूर्ण

	वापस selected_phys;
पूर्ण

अटल u32 get_configurable_phys(काष्ठा hci_dev *hdev)
अणु
	वापस (get_supported_phys(hdev) & ~MGMT_PHY_BR_1M_1SLOT &
		~MGMT_PHY_LE_1M_TX & ~MGMT_PHY_LE_1M_RX);
पूर्ण

अटल u32 get_supported_settings(काष्ठा hci_dev *hdev)
अणु
	u32 settings = 0;

	settings |= MGMT_SETTING_POWERED;
	settings |= MGMT_SETTING_BONDABLE;
	settings |= MGMT_SETTING_DEBUG_KEYS;
	settings |= MGMT_SETTING_CONNECTABLE;
	settings |= MGMT_SETTING_DISCOVERABLE;

	अगर (lmp_bredr_capable(hdev)) अणु
		अगर (hdev->hci_ver >= BLUETOOTH_VER_1_2)
			settings |= MGMT_SETTING_FAST_CONNECTABLE;
		settings |= MGMT_SETTING_BREDR;
		settings |= MGMT_SETTING_LINK_SECURITY;

		अगर (lmp_ssp_capable(hdev)) अणु
			settings |= MGMT_SETTING_SSP;
			अगर (IS_ENABLED(CONFIG_BT_HS))
				settings |= MGMT_SETTING_HS;
		पूर्ण

		अगर (lmp_sc_capable(hdev))
			settings |= MGMT_SETTING_SECURE_CONN;

		अगर (test_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED,
			     &hdev->quirks))
			settings |= MGMT_SETTING_WIDEBAND_SPEECH;
	पूर्ण

	अगर (lmp_le_capable(hdev)) अणु
		settings |= MGMT_SETTING_LE;
		settings |= MGMT_SETTING_SECURE_CONN;
		settings |= MGMT_SETTING_PRIVACY;
		settings |= MGMT_SETTING_STATIC_ADDRESS;

		/* When the experimental feature क्रम LL Privacy support is
		 * enabled, then advertising is no दीर्घer supported.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
			settings |= MGMT_SETTING_ADVERTISING;
	पूर्ण

	अगर (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) ||
	    hdev->set_bdaddr)
		settings |= MGMT_SETTING_CONFIGURATION;

	settings |= MGMT_SETTING_PHY_CONFIGURATION;

	वापस settings;
पूर्ण

अटल u32 get_current_settings(काष्ठा hci_dev *hdev)
अणु
	u32 settings = 0;

	अगर (hdev_is_घातered(hdev))
		settings |= MGMT_SETTING_POWERED;

	अगर (hci_dev_test_flag(hdev, HCI_CONNECTABLE))
		settings |= MGMT_SETTING_CONNECTABLE;

	अगर (hci_dev_test_flag(hdev, HCI_FAST_CONNECTABLE))
		settings |= MGMT_SETTING_FAST_CONNECTABLE;

	अगर (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
		settings |= MGMT_SETTING_DISCOVERABLE;

	अगर (hci_dev_test_flag(hdev, HCI_BONDABLE))
		settings |= MGMT_SETTING_BONDABLE;

	अगर (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		settings |= MGMT_SETTING_BREDR;

	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		settings |= MGMT_SETTING_LE;

	अगर (hci_dev_test_flag(hdev, HCI_LINK_SECURITY))
		settings |= MGMT_SETTING_LINK_SECURITY;

	अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		settings |= MGMT_SETTING_SSP;

	अगर (hci_dev_test_flag(hdev, HCI_HS_ENABLED))
		settings |= MGMT_SETTING_HS;

	अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING))
		settings |= MGMT_SETTING_ADVERTISING;

	अगर (hci_dev_test_flag(hdev, HCI_SC_ENABLED))
		settings |= MGMT_SETTING_SECURE_CONN;

	अगर (hci_dev_test_flag(hdev, HCI_KEEP_DEBUG_KEYS))
		settings |= MGMT_SETTING_DEBUG_KEYS;

	अगर (hci_dev_test_flag(hdev, HCI_PRIVACY))
		settings |= MGMT_SETTING_PRIVACY;

	/* The current setting क्रम अटल address has two purposes. The
	 * first is to indicate अगर the अटल address will be used and
	 * the second is to indicate अगर it is actually set.
	 *
	 * This means अगर the अटल address is not configured, this flag
	 * will never be set. If the address is configured, then अगर the
	 * address is actually used decides अगर the flag is set or not.
	 *
	 * For single mode LE only controllers and dual-mode controllers
	 * with BR/EDR disabled, the existence of the अटल address will
	 * be evaluated.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ||
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) ||
	    !bacmp(&hdev->bdaddr, BDADDR_ANY)) अणु
		अगर (bacmp(&hdev->अटल_addr, BDADDR_ANY))
			settings |= MGMT_SETTING_STATIC_ADDRESS;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_WIDEBAND_SPEECH_ENABLED))
		settings |= MGMT_SETTING_WIDEBAND_SPEECH;

	वापस settings;
पूर्ण

अटल काष्ठा mgmt_pending_cmd *pending_find(u16 opcode, काष्ठा hci_dev *hdev)
अणु
	वापस mgmt_pending_find(HCI_CHANNEL_CONTROL, opcode, hdev);
पूर्ण

अटल काष्ठा mgmt_pending_cmd *pending_find_data(u16 opcode,
						  काष्ठा hci_dev *hdev,
						  स्थिर व्योम *data)
अणु
	वापस mgmt_pending_find_data(HCI_CHANNEL_CONTROL, opcode, hdev, data);
पूर्ण

u8 mgmt_get_adv_discov_flags(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	/* If there's a pending mgmt command the flags will not yet have
	 * their final values, so check क्रम this first.
	 */
	cmd = pending_find(MGMT_OP_SET_DISCOVERABLE, hdev);
	अगर (cmd) अणु
		काष्ठा mgmt_mode *cp = cmd->param;
		अगर (cp->val == 0x01)
			वापस LE_AD_GENERAL;
		अन्यथा अगर (cp->val == 0x02)
			वापस LE_AD_LIMITED;
	पूर्ण अन्यथा अणु
		अगर (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE))
			वापस LE_AD_LIMITED;
		अन्यथा अगर (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
			वापस LE_AD_GENERAL;
	पूर्ण

	वापस 0;
पूर्ण

bool mgmt_get_connectable(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	/* If there's a pending mgmt command the flag will not yet have
	 * it's final value, so check क्रम this first.
	 */
	cmd = pending_find(MGMT_OP_SET_CONNECTABLE, hdev);
	अगर (cmd) अणु
		काष्ठा mgmt_mode *cp = cmd->param;

		वापस cp->val;
	पूर्ण

	वापस hci_dev_test_flag(hdev, HCI_CONNECTABLE);
पूर्ण

अटल व्योम service_cache_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    service_cache.work);
	काष्ठा hci_request req;

	अगर (!hci_dev_test_and_clear_flag(hdev, HCI_SERVICE_CACHE))
		वापस;

	hci_req_init(&req, hdev);

	hci_dev_lock(hdev);

	__hci_req_update_eir(&req);
	__hci_req_update_class(&req);

	hci_dev_unlock(hdev);

	hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम rpa_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    rpa_expired.work);
	काष्ठा hci_request req;

	bt_dev_dbg(hdev, "");

	hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);

	अगर (!hci_dev_test_flag(hdev, HCI_ADVERTISING))
		वापस;

	/* The generation of a new RPA and programming it पूर्णांकo the
	 * controller happens in the hci_req_enable_advertising()
	 * function.
	 */
	hci_req_init(&req, hdev);
	अगर (ext_adv_capable(hdev))
		__hci_req_start_ext_adv(&req, hdev->cur_adv_instance);
	अन्यथा
		__hci_req_enable_advertising(&req);
	hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम mgmt_init_hdev(काष्ठा sock *sk, काष्ठा hci_dev *hdev)
अणु
	अगर (hci_dev_test_and_set_flag(hdev, HCI_MGMT))
		वापस;

	INIT_DELAYED_WORK(&hdev->service_cache, service_cache_off);
	INIT_DELAYED_WORK(&hdev->rpa_expired, rpa_expired);

	/* Non-mgmt controlled devices get this bit set
	 * implicitly so that pairing works क्रम them, however
	 * क्रम mgmt we require user-space to explicitly enable
	 * it
	 */
	hci_dev_clear_flag(hdev, HCI_BONDABLE);
पूर्ण

अटल पूर्णांक पढ़ो_controller_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_info rp;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	स_रखो(&rp, 0, माप(rp));

	bacpy(&rp.bdaddr, &hdev->bdaddr);

	rp.version = hdev->hci_ver;
	rp.manufacturer = cpu_to_le16(hdev->manufacturer);

	rp.supported_settings = cpu_to_le32(get_supported_settings(hdev));
	rp.current_settings = cpu_to_le32(get_current_settings(hdev));

	स_नकल(rp.dev_class, hdev->dev_class, 3);

	स_नकल(rp.name, hdev->dev_name, माप(hdev->dev_name));
	स_नकल(rp.लघु_name, hdev->लघु_name, माप(hdev->लघु_name));

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_INFO, 0, &rp,
				 माप(rp));
पूर्ण

अटल u16 append_eir_data_to_buf(काष्ठा hci_dev *hdev, u8 *eir)
अणु
	u16 eir_len = 0;
	माप_प्रकार name_len;

	अगर (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		eir_len = eir_append_data(eir, eir_len, EIR_CLASS_OF_DEV,
					  hdev->dev_class, 3);

	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		eir_len = eir_append_le16(eir, eir_len, EIR_APPEARANCE,
					  hdev->appearance);

	name_len = म_माप(hdev->dev_name);
	eir_len = eir_append_data(eir, eir_len, EIR_NAME_COMPLETE,
				  hdev->dev_name, name_len);

	name_len = म_माप(hdev->लघु_name);
	eir_len = eir_append_data(eir, eir_len, EIR_NAME_SHORT,
				  hdev->लघु_name, name_len);

	वापस eir_len;
पूर्ण

अटल पूर्णांक पढ़ो_ext_controller_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				    व्योम *data, u16 data_len)
अणु
	अक्षर buf[512];
	काष्ठा mgmt_rp_पढ़ो_ext_info *rp = (व्योम *)buf;
	u16 eir_len;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&buf, 0, माप(buf));

	hci_dev_lock(hdev);

	bacpy(&rp->bdaddr, &hdev->bdaddr);

	rp->version = hdev->hci_ver;
	rp->manufacturer = cpu_to_le16(hdev->manufacturer);

	rp->supported_settings = cpu_to_le32(get_supported_settings(hdev));
	rp->current_settings = cpu_to_le32(get_current_settings(hdev));


	eir_len = append_eir_data_to_buf(hdev, rp->eir);
	rp->eir_len = cpu_to_le16(eir_len);

	hci_dev_unlock(hdev);

	/* If this command is called at least once, then the events
	 * क्रम class of device and local name changes are disabled
	 * and only the new extended controller inक्रमmation event
	 * is used.
	 */
	hci_sock_set_flag(sk, HCI_MGMT_EXT_INFO_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_DEV_CLASS_EVENTS);
	hci_sock_clear_flag(sk, HCI_MGMT_LOCAL_NAME_EVENTS);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_EXT_INFO, 0, rp,
				 माप(*rp) + eir_len);
पूर्ण

अटल पूर्णांक ext_info_changed(काष्ठा hci_dev *hdev, काष्ठा sock *skip)
अणु
	अक्षर buf[512];
	काष्ठा mgmt_ev_ext_info_changed *ev = (व्योम *)buf;
	u16 eir_len;

	स_रखो(buf, 0, माप(buf));

	eir_len = append_eir_data_to_buf(hdev, ev->eir);
	ev->eir_len = cpu_to_le16(eir_len);

	वापस mgmt_limited_event(MGMT_EV_EXT_INFO_CHANGED, hdev, ev,
				  माप(*ev) + eir_len,
				  HCI_MGMT_EXT_INFO_EVENTS, skip);
पूर्ण

अटल पूर्णांक send_settings_rsp(काष्ठा sock *sk, u16 opcode, काष्ठा hci_dev *hdev)
अणु
	__le32 settings = cpu_to_le32(get_current_settings(hdev));

	वापस mgmt_cmd_complete(sk, hdev->id, opcode, 0, &settings,
				 माप(settings));
पूर्ण

अटल व्योम clean_up_hci_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "status 0x%02x", status);

	अगर (hci_conn_count(hdev) == 0) अणु
		cancel_delayed_work(&hdev->घातer_off);
		queue_work(hdev->req_workqueue, &hdev->घातer_off.work);
	पूर्ण
पूर्ण

व्योम mgmt_advertising_added(काष्ठा sock *sk, काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा mgmt_ev_advertising_added ev;

	ev.instance = instance;

	mgmt_event(MGMT_EV_ADVERTISING_ADDED, hdev, &ev, माप(ev), sk);
पूर्ण

व्योम mgmt_advertising_हटाओd(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      u8 instance)
अणु
	काष्ठा mgmt_ev_advertising_हटाओd ev;

	ev.instance = instance;

	mgmt_event(MGMT_EV_ADVERTISING_REMOVED, hdev, &ev, माप(ev), sk);
पूर्ण

अटल व्योम cancel_adv_समयout(काष्ठा hci_dev *hdev)
अणु
	अगर (hdev->adv_instance_समयout) अणु
		hdev->adv_instance_समयout = 0;
		cancel_delayed_work(&hdev->adv_instance_expire);
	पूर्ण
पूर्ण

अटल पूर्णांक clean_up_hci_state(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_request req;
	काष्ठा hci_conn *conn;
	bool discov_stopped;
	पूर्णांक err;

	hci_req_init(&req, hdev);

	अगर (test_bit(HCI_ISCAN, &hdev->flags) ||
	    test_bit(HCI_PSCAN, &hdev->flags)) अणु
		u8 scan = 0x00;
		hci_req_add(&req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
	पूर्ण

	hci_req_clear_adv_instance(hdev, शून्य, शून्य, 0x00, false);

	अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
		__hci_req_disable_advertising(&req);

	discov_stopped = hci_req_stop_discovery(&req);

	list_क्रम_each_entry(conn, &hdev->conn_hash.list, list) अणु
		/* 0x15 == Terminated due to Power Off */
		__hci_पात_conn(&req, conn, 0x15);
	पूर्ण

	err = hci_req_run(&req, clean_up_hci_complete);
	अगर (!err && discov_stopped)
		hci_discovery_set_state(hdev, DISCOVERY_STOPPING);

	वापस err;
पूर्ण

अटल पूर्णांक set_घातered(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
		       u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_POWERED,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (pending_find(MGMT_OP_SET_POWERED, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_POWERED,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	अगर (!!cp->val == hdev_is_घातered(hdev)) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_POWERED, hdev);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_POWERED, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	अगर (cp->val) अणु
		queue_work(hdev->req_workqueue, &hdev->घातer_on);
		err = 0;
	पूर्ण अन्यथा अणु
		/* Disconnect connections, stop scans, etc */
		err = clean_up_hci_state(hdev);
		अगर (!err)
			queue_delayed_work(hdev->req_workqueue, &hdev->घातer_off,
					   HCI_POWER_OFF_TIMEOUT);

		/* ENODATA means there were no HCI commands queued */
		अगर (err == -ENODATA) अणु
			cancel_delayed_work(&hdev->घातer_off);
			queue_work(hdev->req_workqueue, &hdev->घातer_off.work);
			err = 0;
		पूर्ण
	पूर्ण

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक new_settings(काष्ठा hci_dev *hdev, काष्ठा sock *skip)
अणु
	__le32 ev = cpu_to_le32(get_current_settings(hdev));

	वापस mgmt_limited_event(MGMT_EV_NEW_SETTINGS, hdev, &ev,
				  माप(ev), HCI_MGMT_SETTING_EVENTS, skip);
पूर्ण

पूर्णांक mgmt_new_settings(काष्ठा hci_dev *hdev)
अणु
	वापस new_settings(hdev, शून्य);
पूर्ण

काष्ठा cmd_lookup अणु
	काष्ठा sock *sk;
	काष्ठा hci_dev *hdev;
	u8 mgmt_status;
पूर्ण;

अटल व्योम settings_rsp(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	काष्ठा cmd_lookup *match = data;

	send_settings_rsp(cmd->sk, cmd->opcode, match->hdev);

	list_del(&cmd->list);

	अगर (match->sk == शून्य) अणु
		match->sk = cmd->sk;
		sock_hold(match->sk);
	पूर्ण

	mgmt_pending_मुक्त(cmd);
पूर्ण

अटल व्योम cmd_status_rsp(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	u8 *status = data;

	mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode, *status);
	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल व्योम cmd_complete_rsp(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	अगर (cmd->cmd_complete) अणु
		u8 *status = data;

		cmd->cmd_complete(cmd, *status);
		mgmt_pending_हटाओ(cmd);

		वापस;
	पूर्ण

	cmd_status_rsp(cmd, data);
पूर्ण

अटल पूर्णांक generic_cmd_complete(काष्ठा mgmt_pending_cmd *cmd, u8 status)
अणु
	वापस mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status,
				 cmd->param, cmd->param_len);
पूर्ण

अटल पूर्णांक addr_cmd_complete(काष्ठा mgmt_pending_cmd *cmd, u8 status)
अणु
	वापस mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status,
				 cmd->param, माप(काष्ठा mgmt_addr_info));
पूर्ण

अटल u8 mgmt_bredr_support(काष्ठा hci_dev *hdev)
अणु
	अगर (!lmp_bredr_capable(hdev))
		वापस MGMT_STATUS_NOT_SUPPORTED;
	अन्यथा अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस MGMT_STATUS_REJECTED;
	अन्यथा
		वापस MGMT_STATUS_SUCCESS;
पूर्ण

अटल u8 mgmt_le_support(काष्ठा hci_dev *hdev)
अणु
	अगर (!lmp_le_capable(hdev))
		वापस MGMT_STATUS_NOT_SUPPORTED;
	अन्यथा अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस MGMT_STATUS_REJECTED;
	अन्यथा
		वापस MGMT_STATUS_SUCCESS;
पूर्ण

व्योम mgmt_set_discoverable_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_DISCOVERABLE, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);
		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode, mgmt_err);
		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);
		जाओ हटाओ_cmd;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_DISCOVERABLE) &&
	    hdev->discov_समयout > 0) अणु
		पूर्णांक to = msecs_to_jअगरfies(hdev->discov_समयout * 1000);
		queue_delayed_work(hdev->req_workqueue, &hdev->discov_off, to);
	पूर्ण

	send_settings_rsp(cmd->sk, MGMT_OP_SET_DISCOVERABLE, hdev);
	new_settings(hdev, cmd->sk);

हटाओ_cmd:
	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_discoverable(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 len)
अणु
	काष्ठा mgmt_cp_set_discoverable *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	u16 समयout;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED) &&
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_REJECTED);

	अगर (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	समयout = __le16_to_cpu(cp->समयout);

	/* Disabling discoverable requires that no समयout is set,
	 * and enabling limited discoverable requires a समयout.
	 */
	अगर ((cp->val == 0x00 && समयout > 0) ||
	    (cp->val == 0x02 && समयout == 0))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev) && समयout > 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_NOT_POWERED);
		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_DISCOVERABLE, hdev) ||
	    pending_find(MGMT_OP_SET_CONNECTABLE, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	अगर (!hci_dev_test_flag(hdev, HCI_CONNECTABLE)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_REJECTED);
		जाओ failed;
	पूर्ण

	अगर (hdev->advertising_छोड़ोd) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	अगर (!hdev_is_घातered(hdev)) अणु
		bool changed = false;

		/* Setting limited discoverable when घातered off is
		 * not a valid operation since it requires a समयout
		 * and so no need to check HCI_LIMITED_DISCOVERABLE.
		 */
		अगर (!!cp->val != hci_dev_test_flag(hdev, HCI_DISCOVERABLE)) अणु
			hci_dev_change_flag(hdev, HCI_DISCOVERABLE);
			changed = true;
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_DISCOVERABLE, hdev);
		अगर (err < 0)
			जाओ failed;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ failed;
	पूर्ण

	/* If the current mode is the same, then just update the समयout
	 * value with the new value. And अगर only the समयout माला_लो updated,
	 * then no need क्रम any HCI transactions.
	 */
	अगर (!!cp->val == hci_dev_test_flag(hdev, HCI_DISCOVERABLE) &&
	    (cp->val == 0x02) == hci_dev_test_flag(hdev,
						   HCI_LIMITED_DISCOVERABLE)) अणु
		cancel_delayed_work(&hdev->discov_off);
		hdev->discov_समयout = समयout;

		अगर (cp->val && hdev->discov_समयout > 0) अणु
			पूर्णांक to = msecs_to_jअगरfies(hdev->discov_समयout * 1000);
			queue_delayed_work(hdev->req_workqueue,
					   &hdev->discov_off, to);
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_DISCOVERABLE, hdev);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_DISCOVERABLE, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* Cancel any potential discoverable समयout that might be
	 * still active and store new समयout value. The arming of
	 * the समयout happens in the complete handler.
	 */
	cancel_delayed_work(&hdev->discov_off);
	hdev->discov_समयout = समयout;

	अगर (cp->val)
		hci_dev_set_flag(hdev, HCI_DISCOVERABLE);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);

	/* Limited discoverable mode */
	अगर (cp->val == 0x02)
		hci_dev_set_flag(hdev, HCI_LIMITED_DISCOVERABLE);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);

	queue_work(hdev->req_workqueue, &hdev->discoverable_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

व्योम mgmt_set_connectable_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_CONNECTABLE, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);
		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode, mgmt_err);
		जाओ हटाओ_cmd;
	पूर्ण

	send_settings_rsp(cmd->sk, MGMT_OP_SET_CONNECTABLE, hdev);
	new_settings(hdev, cmd->sk);

हटाओ_cmd:
	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_connectable_update_settings(काष्ठा hci_dev *hdev,
					   काष्ठा sock *sk, u8 val)
अणु
	bool changed = false;
	पूर्णांक err;

	अगर (!!val != hci_dev_test_flag(hdev, HCI_CONNECTABLE))
		changed = true;

	अगर (val) अणु
		hci_dev_set_flag(hdev, HCI_CONNECTABLE);
	पूर्ण अन्यथा अणु
		hci_dev_clear_flag(hdev, HCI_CONNECTABLE);
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
	पूर्ण

	err = send_settings_rsp(sk, MGMT_OP_SET_CONNECTABLE, hdev);
	अगर (err < 0)
		वापस err;

	अगर (changed) अणु
		hci_req_update_scan(hdev);
		hci_update_background_scan(hdev);
		वापस new_settings(hdev, sk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_connectable(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED) &&
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_CONNECTABLE,
				       MGMT_STATUS_REJECTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_CONNECTABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = set_connectable_update_settings(hdev, sk, cp->val);
		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_DISCOVERABLE, hdev) ||
	    pending_find(MGMT_OP_SET_CONNECTABLE, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_CONNECTABLE,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_CONNECTABLE, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	अगर (cp->val) अणु
		hci_dev_set_flag(hdev, HCI_CONNECTABLE);
	पूर्ण अन्यथा अणु
		अगर (hdev->discov_समयout > 0)
			cancel_delayed_work(&hdev->discov_off);

		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
		hci_dev_clear_flag(hdev, HCI_CONNECTABLE);
	पूर्ण

	queue_work(hdev->req_workqueue, &hdev->connectable_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_bondable(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	bool changed;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BONDABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (cp->val)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_BONDABLE);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev, HCI_BONDABLE);

	err = send_settings_rsp(sk, MGMT_OP_SET_BONDABLE, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (changed) अणु
		/* In limited privacy mode the change of bondable mode
		 * may affect the local advertising address.
		 */
		अगर (hdev_is_घातered(hdev) &&
		    hci_dev_test_flag(hdev, HCI_ADVERTISING) &&
		    hci_dev_test_flag(hdev, HCI_DISCOVERABLE) &&
		    hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY))
			queue_work(hdev->req_workqueue,
				   &hdev->discoverable_update);

		err = new_settings(hdev, sk);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_link_security(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			     u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	u8 val, status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	status = mgmt_bredr_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				       status);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		bool changed = false;

		अगर (!!cp->val != hci_dev_test_flag(hdev, HCI_LINK_SECURITY)) अणु
			hci_dev_change_flag(hdev, HCI_LINK_SECURITY);
			changed = true;
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_LINK_SECURITY, hdev);
		अगर (err < 0)
			जाओ failed;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_LINK_SECURITY, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	val = !!cp->val;

	अगर (test_bit(HCI_AUTH, &hdev->flags) == val) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_LINK_SECURITY, hdev);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LINK_SECURITY, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	err = hci_send_cmd(hdev, HCI_OP_WRITE_AUTH_ENABLE, माप(val), &val);
	अगर (err < 0) अणु
		mgmt_pending_हटाओ(cmd);
		जाओ failed;
	पूर्ण

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_ssp(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	status = mgmt_bredr_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SSP, status);

	अगर (!lmp_ssp_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SSP,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SSP,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		bool changed;

		अगर (cp->val) अणु
			changed = !hci_dev_test_and_set_flag(hdev,
							     HCI_SSP_ENABLED);
		पूर्ण अन्यथा अणु
			changed = hci_dev_test_and_clear_flag(hdev,
							      HCI_SSP_ENABLED);
			अगर (!changed)
				changed = hci_dev_test_and_clear_flag(hdev,
								      HCI_HS_ENABLED);
			अन्यथा
				hci_dev_clear_flag(hdev, HCI_HS_ENABLED);
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_SSP, hdev);
		अगर (err < 0)
			जाओ failed;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_SSP, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SSP,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	अगर (!!cp->val == hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_SSP, hdev);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_SSP, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	अगर (!cp->val && hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS))
		hci_send_cmd(hdev, HCI_OP_WRITE_SSP_DEBUG_MODE,
			     माप(cp->val), &cp->val);

	err = hci_send_cmd(hdev, HCI_OP_WRITE_SSP_MODE, 1, &cp->val);
	अगर (err < 0) अणु
		mgmt_pending_हटाओ(cmd);
		जाओ failed;
	पूर्ण

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_hs(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	bool changed;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!IS_ENABLED(CONFIG_BT_HS))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_NOT_SUPPORTED);

	status = mgmt_bredr_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS, status);

	अगर (!lmp_ssp_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (!hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_REJECTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (pending_find(MGMT_OP_SET_SSP, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (cp->val) अणु
		changed = !hci_dev_test_and_set_flag(hdev, HCI_HS_ENABLED);
	पूर्ण अन्यथा अणु
		अगर (hdev_is_घातered(hdev)) अणु
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
					      MGMT_STATUS_REJECTED);
			जाओ unlock;
		पूर्ण

		changed = hci_dev_test_and_clear_flag(hdev, HCI_HS_ENABLED);
	पूर्ण

	err = send_settings_rsp(sk, MGMT_OP_SET_HS, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल व्योम le_enable_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;

	hci_dev_lock(hdev);

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);

		mgmt_pending_क्रमeach(MGMT_OP_SET_LE, hdev, cmd_status_rsp,
				     &mgmt_err);
		जाओ unlock;
	पूर्ण

	mgmt_pending_क्रमeach(MGMT_OP_SET_LE, hdev, settings_rsp, &match);

	new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);

	/* Make sure the controller has a good शेष क्रम
	 * advertising data. Restrict the update to when LE
	 * has actually been enabled. During घातer on, the
	 * update in घातered_update_hci will take care of it.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
		काष्ठा hci_request req;
		hci_req_init(&req, hdev);
		अगर (ext_adv_capable(hdev)) अणु
			पूर्णांक err;

			err = __hci_req_setup_ext_adv_instance(&req, 0x00);
			अगर (!err)
				__hci_req_update_scan_rsp_data(&req, 0x00);
		पूर्ण अन्यथा अणु
			__hci_req_update_adv_data(&req, 0x00);
			__hci_req_update_scan_rsp_data(&req, 0x00);
		पूर्ण
		hci_req_run(&req, शून्य);
		hci_update_background_scan(hdev);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_le(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा hci_cp_ग_लिखो_le_host_supported hci_cp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;
	u8 val, enabled;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_INVALID_PARAMS);

	/* Bluetooth single mode LE only controllers or dual-mode
	 * controllers configured as LE only devices, करो not allow
	 * चयनing LE off. These have either LE enabled explicitly
	 * or BR/EDR has been previously चयनed off.
	 *
	 * When trying to enable an alपढ़ोy enabled LE, then gracefully
	 * send a positive response. Trying to disable it however will
	 * result पूर्णांकo rejection.
	 */
	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		अगर (cp->val == 0x01)
			वापस send_settings_rsp(sk, MGMT_OP_SET_LE, hdev);

		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_REJECTED);
	पूर्ण

	hci_dev_lock(hdev);

	val = !!cp->val;
	enabled = lmp_host_le_capable(hdev);

	अगर (!val)
		hci_req_clear_adv_instance(hdev, शून्य, शून्य, 0x00, true);

	अगर (!hdev_is_घातered(hdev) || val == enabled) अणु
		bool changed = false;

		अगर (val != hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
			hci_dev_change_flag(hdev, HCI_LE_ENABLED);
			changed = true;
		पूर्ण

		अगर (!val && hci_dev_test_flag(hdev, HCI_ADVERTISING)) अणु
			hci_dev_clear_flag(hdev, HCI_ADVERTISING);
			changed = true;
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_LE, hdev);
		अगर (err < 0)
			जाओ unlock;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ unlock;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_LE, hdev) ||
	    pending_find(MGMT_OP_SET_ADVERTISING, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LE, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	स_रखो(&hci_cp, 0, माप(hci_cp));

	अगर (val) अणु
		hci_cp.le = val;
		hci_cp.simul = 0x00;
	पूर्ण अन्यथा अणु
		अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
			__hci_req_disable_advertising(&req);

		अगर (ext_adv_capable(hdev))
			__hci_req_clear_ext_adv_sets(&req);
	पूर्ण

	hci_req_add(&req, HCI_OP_WRITE_LE_HOST_SUPPORTED, माप(hci_cp),
		    &hci_cp);

	err = hci_req_run(&req, le_enable_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

/* This is a helper function to test क्रम pending mgmt commands that can
 * cause CoD or EIR HCI commands. We can only allow one such pending
 * mgmt command at a समय since otherwise we cannot easily track what
 * the current values are, will be, and based on that calculate अगर a new
 * HCI command needs to be sent and अगर yes with what value.
 */
अटल bool pending_eir_or_class(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	list_क्रम_each_entry(cmd, &hdev->mgmt_pending, list) अणु
		चयन (cmd->opcode) अणु
		हाल MGMT_OP_ADD_UUID:
		हाल MGMT_OP_REMOVE_UUID:
		हाल MGMT_OP_SET_DEV_CLASS:
		हाल MGMT_OP_SET_POWERED:
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर u8 bluetooth_base_uuid[] = अणु
			0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
			0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

अटल u8 get_uuid_size(स्थिर u8 *uuid)
अणु
	u32 val;

	अगर (स_भेद(uuid, bluetooth_base_uuid, 12))
		वापस 128;

	val = get_unaligned_le32(&uuid[12]);
	अगर (val > 0xffff)
		वापस 32;

	वापस 16;
पूर्ण

अटल व्योम mgmt_class_complete(काष्ठा hci_dev *hdev, u16 mgmt_op, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	hci_dev_lock(hdev);

	cmd = pending_find(mgmt_op, hdev);
	अगर (!cmd)
		जाओ unlock;

	mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
			  mgmt_status(status), hdev->dev_class, 3);

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल व्योम add_uuid_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "status 0x%02x", status);

	mgmt_class_complete(hdev, MGMT_OP_ADD_UUID, status);
पूर्ण

अटल पूर्णांक add_uuid(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_add_uuid *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	काष्ठा bt_uuid *uuid;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (pending_eir_or_class(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_UUID,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	uuid = kदो_स्मृति(माप(*uuid), GFP_KERNEL);
	अगर (!uuid) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	स_नकल(uuid->uuid, cp->uuid, 16);
	uuid->svc_hपूर्णांक = cp->svc_hपूर्णांक;
	uuid->size = get_uuid_size(cp->uuid);

	list_add_tail(&uuid->list, &hdev->uuids);

	hci_req_init(&req, hdev);

	__hci_req_update_class(&req);
	__hci_req_update_eir(&req);

	err = hci_req_run(&req, add_uuid_complete);
	अगर (err < 0) अणु
		अगर (err != -ENODATA)
			जाओ failed;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_UUID, 0,
					hdev->dev_class, 3);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_ADD_UUID, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	err = 0;

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल bool enable_service_cache(काष्ठा hci_dev *hdev)
अणु
	अगर (!hdev_is_घातered(hdev))
		वापस false;

	अगर (!hci_dev_test_and_set_flag(hdev, HCI_SERVICE_CACHE)) अणु
		queue_delayed_work(hdev->workqueue, &hdev->service_cache,
				   CACHE_TIMEOUT);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम हटाओ_uuid_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "status 0x%02x", status);

	mgmt_class_complete(hdev, MGMT_OP_REMOVE_UUID, status);
पूर्ण

अटल पूर्णांक हटाओ_uuid(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
		       u16 len)
अणु
	काष्ठा mgmt_cp_हटाओ_uuid *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा bt_uuid *match, *पंचांगp;
	u8 bt_uuid_any[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	काष्ठा hci_request req;
	पूर्णांक err, found;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (pending_eir_or_class(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_UUID,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (स_भेद(cp->uuid, bt_uuid_any, 16) == 0) अणु
		hci_uuids_clear(hdev);

		अगर (enable_service_cache(hdev)) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_UUID,
						0, hdev->dev_class, 3);
			जाओ unlock;
		पूर्ण

		जाओ update_class;
	पूर्ण

	found = 0;

	list_क्रम_each_entry_safe(match, पंचांगp, &hdev->uuids, list) अणु
		अगर (स_भेद(match->uuid, cp->uuid, 16) != 0)
			जारी;

		list_del(&match->list);
		kमुक्त(match);
		found++;
	पूर्ण

	अगर (found == 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_UUID,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

update_class:
	hci_req_init(&req, hdev);

	__hci_req_update_class(&req);
	__hci_req_update_eir(&req);

	err = hci_req_run(&req, हटाओ_uuid_complete);
	अगर (err < 0) अणु
		अगर (err != -ENODATA)
			जाओ unlock;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_REMOVE_UUID, 0,
					hdev->dev_class, 3);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_REMOVE_UUID, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	err = 0;

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल व्योम set_class_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "status 0x%02x", status);

	mgmt_class_complete(hdev, MGMT_OP_SET_DEV_CLASS, status);
पूर्ण

अटल पूर्णांक set_dev_class(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 len)
अणु
	काष्ठा mgmt_cp_set_dev_class *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_bredr_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEV_CLASS,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	अगर (pending_eir_or_class(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEV_CLASS,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर ((cp->minor & 0x03) != 0 || (cp->major & 0xe0) != 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEV_CLASS,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	hdev->major_class = cp->major;
	hdev->minor_class = cp->minor;

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_DEV_CLASS, 0,
					hdev->dev_class, 3);
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	अगर (hci_dev_test_and_clear_flag(hdev, HCI_SERVICE_CACHE)) अणु
		hci_dev_unlock(hdev);
		cancel_delayed_work_sync(&hdev->service_cache);
		hci_dev_lock(hdev);
		__hci_req_update_eir(&req);
	पूर्ण

	__hci_req_update_class(&req);

	err = hci_req_run(&req, set_class_complete);
	अगर (err < 0) अणु
		अगर (err != -ENODATA)
			जाओ unlock;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_DEV_CLASS, 0,
					hdev->dev_class, 3);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_DEV_CLASS, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	err = 0;

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक load_link_keys(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा mgmt_cp_load_link_keys *cp = data;
	स्थिर u16 max_key_count = ((U16_MAX - माप(*cp)) /
				   माप(काष्ठा mgmt_link_key_info));
	u16 key_count, expected_len;
	bool changed;
	पूर्णांक i;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_bredr_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LINK_KEYS,
				       MGMT_STATUS_NOT_SUPPORTED);

	key_count = __le16_to_cpu(cp->key_count);
	अगर (key_count > max_key_count) अणु
		bt_dev_err(hdev, "load_link_keys: too big key_count value %u",
			   key_count);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LINK_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	expected_len = काष्ठा_size(cp, keys, key_count);
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "load_link_keys: expected %u bytes, got %u bytes",
			   expected_len, len);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LINK_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	अगर (cp->debug_keys != 0x00 && cp->debug_keys != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LINK_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);

	bt_dev_dbg(hdev, "debug_keys %u key_count %u", cp->debug_keys,
		   key_count);

	क्रम (i = 0; i < key_count; i++) अणु
		काष्ठा mgmt_link_key_info *key = &cp->keys[i];

		अगर (key->addr.type != BDADDR_BREDR || key->type > 0x08)
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_LOAD_LINK_KEYS,
					       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	hci_dev_lock(hdev);

	hci_link_keys_clear(hdev);

	अगर (cp->debug_keys)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_KEEP_DEBUG_KEYS);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev,
						      HCI_KEEP_DEBUG_KEYS);

	अगर (changed)
		new_settings(hdev, शून्य);

	क्रम (i = 0; i < key_count; i++) अणु
		काष्ठा mgmt_link_key_info *key = &cp->keys[i];

		अगर (hci_is_blocked_key(hdev,
				       HCI_BLOCKED_KEY_TYPE_LINKKEY,
				       key->val)) अणु
			bt_dev_warn(hdev, "Skipping blocked link key for %pMR",
				    &key->addr.bdaddr);
			जारी;
		पूर्ण

		/* Always ignore debug keys and require a new pairing अगर
		 * the user wants to use them.
		 */
		अगर (key->type == HCI_LK_DEBUG_COMBINATION)
			जारी;

		hci_add_link_key(hdev, शून्य, &key->addr.bdaddr, key->val,
				 key->type, key->pin_len, शून्य);
	पूर्ण

	mgmt_cmd_complete(sk, hdev->id, MGMT_OP_LOAD_LINK_KEYS, 0, शून्य, 0);

	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक device_unpaired(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			   u8 addr_type, काष्ठा sock *skip_sk)
अणु
	काष्ठा mgmt_ev_device_unpaired ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = addr_type;

	वापस mgmt_event(MGMT_EV_DEVICE_UNPAIRED, hdev, &ev, माप(ev),
			  skip_sk);
पूर्ण

अटल पूर्णांक unpair_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 len)
अणु
	काष्ठा mgmt_cp_unpair_device *cp = data;
	काष्ठा mgmt_rp_unpair_device rp;
	काष्ठा hci_conn_params *params;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;
	u8 addr_type;
	पूर्णांक err;

	स_रखो(&rp, 0, माप(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	अगर (cp->disconnect != 0x00 && cp->disconnect != 0x01)
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					MGMT_STATUS_NOT_POWERED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (cp->addr.type == BDADDR_BREDR) अणु
		/* If disconnection is requested, then look up the
		 * connection. If the remote device is connected, it
		 * will be later used to terminate the link.
		 *
		 * Setting it to शून्य explicitly will cause no
		 * termination of the link.
		 */
		अगर (cp->disconnect)
			conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
						       &cp->addr.bdaddr);
		अन्यथा
			conn = शून्य;

		err = hci_हटाओ_link_key(hdev, &cp->addr.bdaddr);
		अगर (err < 0) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_UNPAIR_DEVICE,
						MGMT_STATUS_NOT_PAIRED, &rp,
						माप(rp));
			जाओ unlock;
		पूर्ण

		जाओ करोne;
	पूर्ण

	/* LE address type */
	addr_type = le_addr_type(cp->addr.type);

	/* Abort any ongoing SMP pairing. Removes ltk and irk अगर they exist. */
	err = smp_cancel_and_हटाओ_pairing(hdev, &cp->addr.bdaddr, addr_type);
	अगर (err < 0) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE,
					MGMT_STATUS_NOT_PAIRED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	conn = hci_conn_hash_lookup_le(hdev, &cp->addr.bdaddr, addr_type);
	अगर (!conn) अणु
		hci_conn_params_del(hdev, &cp->addr.bdaddr, addr_type);
		जाओ करोne;
	पूर्ण


	/* Defer clearing up the connection parameters until closing to
	 * give a chance of keeping them अगर a repairing happens.
	 */
	set_bit(HCI_CONN_PARAM_REMOVAL_PEND, &conn->flags);

	/* Disable स्वतः-connection parameters अगर present */
	params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr, addr_type);
	अगर (params) अणु
		अगर (params->explicit_connect)
			params->स्वतः_connect = HCI_AUTO_CONN_EXPLICIT;
		अन्यथा
			params->स्वतः_connect = HCI_AUTO_CONN_DISABLED;
	पूर्ण

	/* If disconnection is not requested, then clear the connection
	 * variable so that the link is not terminated.
	 */
	अगर (!cp->disconnect)
		conn = शून्य;

करोne:
	/* If the connection variable is set, then termination of the
	 * link is requested.
	 */
	अगर (!conn) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNPAIR_DEVICE, 0,
					&rp, माप(rp));
		device_unpaired(hdev, &cp->addr.bdaddr, cp->addr.type, sk);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_UNPAIR_DEVICE, hdev, cp,
			       माप(*cp));
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	cmd->cmd_complete = addr_cmd_complete;

	err = hci_पात_conn(conn, HCI_ERROR_REMOTE_USER_TERM);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक disconnect(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
		      u16 len)
अणु
	काष्ठा mgmt_cp_disconnect *cp = data;
	काष्ठा mgmt_rp_disconnect rp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&rp, 0, माप(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	hci_dev_lock(hdev);

	अगर (!test_bit(HCI_UP, &hdev->flags)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_NOT_POWERED, &rp,
					माप(rp));
		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_DISCONNECT, hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_BUSY, &rp, माप(rp));
		जाओ failed;
	पूर्ण

	अगर (cp->addr.type == BDADDR_BREDR)
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
					       &cp->addr.bdaddr);
	अन्यथा
		conn = hci_conn_hash_lookup_le(hdev, &cp->addr.bdaddr,
					       le_addr_type(cp->addr.type));

	अगर (!conn || conn->state == BT_OPEN || conn->state == BT_CLOSED) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_NOT_CONNECTED, &rp,
					माप(rp));
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_DISCONNECT, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	cmd->cmd_complete = generic_cmd_complete;

	err = hci_disconnect(conn, HCI_ERROR_REMOTE_USER_TERM);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल u8 link_to_bdaddr(u8 link_type, u8 addr_type)
अणु
	चयन (link_type) अणु
	हाल LE_LINK:
		चयन (addr_type) अणु
		हाल ADDR_LE_DEV_PUBLIC:
			वापस BDADDR_LE_PUBLIC;

		शेष:
			/* Fallback to LE Ranकरोm address type */
			वापस BDADDR_LE_RANDOM;
		पूर्ण

	शेष:
		/* Fallback to BR/EDR type */
		वापस BDADDR_BREDR;
	पूर्ण
पूर्ण

अटल पूर्णांक get_connections(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 data_len)
अणु
	काष्ठा mgmt_rp_get_connections *rp;
	काष्ठा hci_conn *c;
	पूर्णांक err;
	u16 i;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_CONNECTIONS,
				      MGMT_STATUS_NOT_POWERED);
		जाओ unlock;
	पूर्ण

	i = 0;
	list_क्रम_each_entry(c, &hdev->conn_hash.list, list) अणु
		अगर (test_bit(HCI_CONN_MGMT_CONNECTED, &c->flags))
			i++;
	पूर्ण

	rp = kदो_स्मृति(काष्ठा_size(rp, addr, i), GFP_KERNEL);
	अगर (!rp) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	i = 0;
	list_क्रम_each_entry(c, &hdev->conn_hash.list, list) अणु
		अगर (!test_bit(HCI_CONN_MGMT_CONNECTED, &c->flags))
			जारी;
		bacpy(&rp->addr[i].bdaddr, &c->dst);
		rp->addr[i].type = link_to_bdaddr(c->type, c->dst_type);
		अगर (c->type == SCO_LINK || c->type == ESCO_LINK)
			जारी;
		i++;
	पूर्ण

	rp->conn_count = cpu_to_le16(i);

	/* Recalculate length in हाल of filtered SCO connections, etc */
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONNECTIONS, 0, rp,
				काष्ठा_size(rp, addr, i));

	kमुक्त(rp);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक send_pin_code_neg_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				   काष्ठा mgmt_cp_pin_code_neg_reply *cp)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;

	cmd = mgmt_pending_add(sk, MGMT_OP_PIN_CODE_NEG_REPLY, hdev, cp,
			       माप(*cp));
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->cmd_complete = addr_cmd_complete;

	err = hci_send_cmd(hdev, HCI_OP_PIN_CODE_NEG_REPLY,
			   माप(cp->addr.bdaddr), &cp->addr.bdaddr);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

	वापस err;
पूर्ण

अटल पूर्णांक pin_code_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा hci_conn *conn;
	काष्ठा mgmt_cp_pin_code_reply *cp = data;
	काष्ठा hci_cp_pin_code_reply reply;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
				      MGMT_STATUS_NOT_POWERED);
		जाओ failed;
	पूर्ण

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->addr.bdaddr);
	अगर (!conn) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
				      MGMT_STATUS_NOT_CONNECTED);
		जाओ failed;
	पूर्ण

	अगर (conn->pending_sec_level == BT_SECURITY_HIGH && cp->pin_len != 16) अणु
		काष्ठा mgmt_cp_pin_code_neg_reply ncp;

		स_नकल(&ncp.addr, &cp->addr, माप(ncp.addr));

		bt_dev_err(hdev, "PIN code is not 16 bytes long");

		err = send_pin_code_neg_reply(sk, hdev, &ncp);
		अगर (err >= 0)
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
					      MGMT_STATUS_INVALID_PARAMS);

		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_PIN_CODE_REPLY, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	cmd->cmd_complete = addr_cmd_complete;

	bacpy(&reply.bdaddr, &cp->addr.bdaddr);
	reply.pin_len = cp->pin_len;
	स_नकल(reply.pin_code, cp->pin_code, माप(reply.pin_code));

	err = hci_send_cmd(hdev, HCI_OP_PIN_CODE_REPLY, माप(reply), &reply);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_io_capability(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			     u16 len)
अणु
	काष्ठा mgmt_cp_set_io_capability *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (cp->io_capability > SMP_IO_KEYBOARD_DISPLAY)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_IO_CAPABILITY,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	hdev->io_capability = cp->io_capability;

	bt_dev_dbg(hdev, "IO capability set to 0x%02x", hdev->io_capability);

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_IO_CAPABILITY, 0,
				 शून्य, 0);
पूर्ण

अटल काष्ठा mgmt_pending_cmd *find_pairing(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा mgmt_pending_cmd *cmd;

	list_क्रम_each_entry(cmd, &hdev->mgmt_pending, list) अणु
		अगर (cmd->opcode != MGMT_OP_PAIR_DEVICE)
			जारी;

		अगर (cmd->user_data != conn)
			जारी;

		वापस cmd;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक pairing_complete(काष्ठा mgmt_pending_cmd *cmd, u8 status)
अणु
	काष्ठा mgmt_rp_pair_device rp;
	काष्ठा hci_conn *conn = cmd->user_data;
	पूर्णांक err;

	bacpy(&rp.addr.bdaddr, &conn->dst);
	rp.addr.type = link_to_bdaddr(conn->type, conn->dst_type);

	err = mgmt_cmd_complete(cmd->sk, cmd->index, MGMT_OP_PAIR_DEVICE,
				status, &rp, माप(rp));

	/* So we करोn't get further callbacks क्रम this connection */
	conn->connect_cfm_cb = शून्य;
	conn->security_cfm_cb = शून्य;
	conn->disconn_cfm_cb = शून्य;

	hci_conn_drop(conn);

	/* The device is paired so there is no need to हटाओ
	 * its connection parameters anymore.
	 */
	clear_bit(HCI_CONN_PARAM_REMOVAL_PEND, &conn->flags);

	hci_conn_put(conn);

	वापस err;
पूर्ण

व्योम mgmt_smp_complete(काष्ठा hci_conn *conn, bool complete)
अणु
	u8 status = complete ? MGMT_STATUS_SUCCESS : MGMT_STATUS_FAILED;
	काष्ठा mgmt_pending_cmd *cmd;

	cmd = find_pairing(conn);
	अगर (cmd) अणु
		cmd->cmd_complete(cmd, status);
		mgmt_pending_हटाओ(cmd);
	पूर्ण
पूर्ण

अटल व्योम pairing_complete_cb(काष्ठा hci_conn *conn, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	BT_DBG("status %u", status);

	cmd = find_pairing(conn);
	अगर (!cmd) अणु
		BT_DBG("Unable to find a pending command");
		वापस;
	पूर्ण

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल व्योम le_pairing_complete_cb(काष्ठा hci_conn *conn, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	BT_DBG("status %u", status);

	अगर (!status)
		वापस;

	cmd = find_pairing(conn);
	अगर (!cmd) अणु
		BT_DBG("Unable to find a pending command");
		वापस;
	पूर्ण

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल पूर्णांक pair_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
		       u16 len)
अणु
	काष्ठा mgmt_cp_pair_device *cp = data;
	काष्ठा mgmt_rp_pair_device rp;
	काष्ठा mgmt_pending_cmd *cmd;
	u8 sec_level, auth_type;
	काष्ठा hci_conn *conn;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&rp, 0, माप(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	अगर (cp->io_cap > SMP_IO_KEYBOARD_DISPLAY)
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					MGMT_STATUS_NOT_POWERED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (hci_bdaddr_is_paired(hdev, &cp->addr.bdaddr, cp->addr.type)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					MGMT_STATUS_ALREADY_PAIRED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	sec_level = BT_SECURITY_MEDIUM;
	auth_type = HCI_AT_DEDICATED_BONDING;

	अगर (cp->addr.type == BDADDR_BREDR) अणु
		conn = hci_connect_acl(hdev, &cp->addr.bdaddr, sec_level,
				       auth_type, CONN_REASON_PAIR_DEVICE);
	पूर्ण अन्यथा अणु
		u8 addr_type = le_addr_type(cp->addr.type);
		काष्ठा hci_conn_params *p;

		/* When pairing a new device, it is expected to remember
		 * this device क्रम future connections. Adding the connection
		 * parameter inक्रमmation ahead of समय allows tracking
		 * of the slave preferred values and will speed up any
		 * further connection establishment.
		 *
		 * If connection parameters alपढ़ोy exist, then they
		 * will be kept and this function करोes nothing.
		 */
		p = hci_conn_params_add(hdev, &cp->addr.bdaddr, addr_type);

		अगर (p->स्वतः_connect == HCI_AUTO_CONN_EXPLICIT)
			p->स्वतः_connect = HCI_AUTO_CONN_DISABLED;

		conn = hci_connect_le_scan(hdev, &cp->addr.bdaddr, addr_type,
					   sec_level, HCI_LE_CONN_TIMEOUT,
					   CONN_REASON_PAIR_DEVICE);
	पूर्ण

	अगर (IS_ERR(conn)) अणु
		पूर्णांक status;

		अगर (PTR_ERR(conn) == -EBUSY)
			status = MGMT_STATUS_BUSY;
		अन्यथा अगर (PTR_ERR(conn) == -EOPNOTSUPP)
			status = MGMT_STATUS_NOT_SUPPORTED;
		अन्यथा अगर (PTR_ERR(conn) == -ECONNREFUSED)
			status = MGMT_STATUS_REJECTED;
		अन्यथा
			status = MGMT_STATUS_CONNECT_FAILED;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					status, &rp, माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (conn->connect_cfm_cb) अणु
		hci_conn_drop(conn);
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_PAIR_DEVICE,
					MGMT_STATUS_BUSY, &rp, माप(rp));
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_PAIR_DEVICE, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		hci_conn_drop(conn);
		जाओ unlock;
	पूर्ण

	cmd->cmd_complete = pairing_complete;

	/* For LE, just connecting isn't a proof that the pairing finished */
	अगर (cp->addr.type == BDADDR_BREDR) अणु
		conn->connect_cfm_cb = pairing_complete_cb;
		conn->security_cfm_cb = pairing_complete_cb;
		conn->disconn_cfm_cb = pairing_complete_cb;
	पूर्ण अन्यथा अणु
		conn->connect_cfm_cb = le_pairing_complete_cb;
		conn->security_cfm_cb = le_pairing_complete_cb;
		conn->disconn_cfm_cb = le_pairing_complete_cb;
	पूर्ण

	conn->io_capability = cp->io_cap;
	cmd->user_data = hci_conn_get(conn);

	अगर ((conn->state == BT_CONNECTED || conn->state == BT_CONFIG) &&
	    hci_conn_security(conn, sec_level, auth_type, true)) अणु
		cmd->cmd_complete(cmd, 0);
		mgmt_pending_हटाओ(cmd);
	पूर्ण

	err = 0;

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक cancel_pair_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			      u16 len)
अणु
	काष्ठा mgmt_addr_info *addr = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_NOT_POWERED);
		जाओ unlock;
	पूर्ण

	cmd = pending_find(MGMT_OP_PAIR_DEVICE, hdev);
	अगर (!cmd) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	conn = cmd->user_data;

	अगर (bacmp(&addr->bdaddr, &conn->dst) != 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	cmd->cmd_complete(cmd, MGMT_STATUS_CANCELLED);
	mgmt_pending_हटाओ(cmd);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE, 0,
				addr, माप(*addr));

	/* Since user करोesn't want to proceed with the connection, पात any
	 * ongoing pairing and then terminate the link अगर it was created
	 * because of the pair device action.
	 */
	अगर (addr->type == BDADDR_BREDR)
		hci_हटाओ_link_key(hdev, &addr->bdaddr);
	अन्यथा
		smp_cancel_and_हटाओ_pairing(hdev, &addr->bdaddr,
					      le_addr_type(addr->type));

	अगर (conn->conn_reason == CONN_REASON_PAIR_DEVICE)
		hci_पात_conn(conn, HCI_ERROR_REMOTE_USER_TERM);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक user_pairing_resp(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			     काष्ठा mgmt_addr_info *addr, u16 mgmt_op,
			     u16 hci_op, __le32 passkey)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;
	पूर्णांक err;

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
					MGMT_STATUS_NOT_POWERED, addr,
					माप(*addr));
		जाओ करोne;
	पूर्ण

	अगर (addr->type == BDADDR_BREDR)
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &addr->bdaddr);
	अन्यथा
		conn = hci_conn_hash_lookup_le(hdev, &addr->bdaddr,
					       le_addr_type(addr->type));

	अगर (!conn) अणु
		err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
					MGMT_STATUS_NOT_CONNECTED, addr,
					माप(*addr));
		जाओ करोne;
	पूर्ण

	अगर (addr->type == BDADDR_LE_PUBLIC || addr->type == BDADDR_LE_RANDOM) अणु
		err = smp_user_confirm_reply(conn, mgmt_op, passkey);
		अगर (!err)
			err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
						MGMT_STATUS_SUCCESS, addr,
						माप(*addr));
		अन्यथा
			err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
						MGMT_STATUS_FAILED, addr,
						माप(*addr));

		जाओ करोne;
	पूर्ण

	cmd = mgmt_pending_add(sk, mgmt_op, hdev, addr, माप(*addr));
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	cmd->cmd_complete = addr_cmd_complete;

	/* Continue with pairing via HCI */
	अगर (hci_op == HCI_OP_USER_PASSKEY_REPLY) अणु
		काष्ठा hci_cp_user_passkey_reply cp;

		bacpy(&cp.bdaddr, &addr->bdaddr);
		cp.passkey = passkey;
		err = hci_send_cmd(hdev, hci_op, माप(cp), &cp);
	पूर्ण अन्यथा
		err = hci_send_cmd(hdev, hci_op, माप(addr->bdaddr),
				   &addr->bdaddr);

	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

करोne:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक pin_code_neg_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_pin_code_neg_reply *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	वापस user_pairing_resp(sk, hdev, &cp->addr,
				MGMT_OP_PIN_CODE_NEG_REPLY,
				HCI_OP_PIN_CODE_NEG_REPLY, 0);
पूर्ण

अटल पूर्णांक user_confirm_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			      u16 len)
अणु
	काष्ठा mgmt_cp_user_confirm_reply *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (len != माप(*cp))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_USER_CONFIRM_REPLY,
				       MGMT_STATUS_INVALID_PARAMS);

	वापस user_pairing_resp(sk, hdev, &cp->addr,
				 MGMT_OP_USER_CONFIRM_REPLY,
				 HCI_OP_USER_CONFIRM_REPLY, 0);
पूर्ण

अटल पूर्णांक user_confirm_neg_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				  व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_user_confirm_neg_reply *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	वापस user_pairing_resp(sk, hdev, &cp->addr,
				 MGMT_OP_USER_CONFIRM_NEG_REPLY,
				 HCI_OP_USER_CONFIRM_NEG_REPLY, 0);
पूर्ण

अटल पूर्णांक user_passkey_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			      u16 len)
अणु
	काष्ठा mgmt_cp_user_passkey_reply *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	वापस user_pairing_resp(sk, hdev, &cp->addr,
				 MGMT_OP_USER_PASSKEY_REPLY,
				 HCI_OP_USER_PASSKEY_REPLY, cp->passkey);
पूर्ण

अटल पूर्णांक user_passkey_neg_reply(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				  व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_user_passkey_neg_reply *cp = data;

	bt_dev_dbg(hdev, "sock %p", sk);

	वापस user_pairing_resp(sk, hdev, &cp->addr,
				 MGMT_OP_USER_PASSKEY_NEG_REPLY,
				 HCI_OP_USER_PASSKEY_NEG_REPLY, 0);
पूर्ण

अटल व्योम adv_expire(काष्ठा hci_dev *hdev, u32 flags)
अणु
	काष्ठा adv_info *adv_instance;
	काष्ठा hci_request req;
	पूर्णांक err;

	adv_instance = hci_find_adv_instance(hdev, hdev->cur_adv_instance);
	अगर (!adv_instance)
		वापस;

	/* stop अगर current instance करोesn't need to be changed */
	अगर (!(adv_instance->flags & flags))
		वापस;

	cancel_adv_समयout(hdev);

	adv_instance = hci_get_next_instance(hdev, adv_instance->instance);
	अगर (!adv_instance)
		वापस;

	hci_req_init(&req, hdev);
	err = __hci_req_schedule_adv_instance(&req, adv_instance->instance,
					      true);
	अगर (err)
		वापस;

	hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम set_name_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा mgmt_cp_set_local_name *cp;
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_LOCAL_NAME, hdev);
	अगर (!cmd)
		जाओ unlock;

	cp = cmd->param;

	अगर (status) अणु
		mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_SET_LOCAL_NAME,
			        mgmt_status(status));
	पूर्ण अन्यथा अणु
		mgmt_cmd_complete(cmd->sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
				  cp, माप(*cp));

		अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
			adv_expire(hdev, MGMT_ADV_FLAG_LOCAL_NAME);
	पूर्ण

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_local_name(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा mgmt_cp_set_local_name *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	/* If the old values are the same as the new ones just वापस a
	 * direct command complete event.
	 */
	अगर (!स_भेद(hdev->dev_name, cp->name, माप(hdev->dev_name)) &&
	    !स_भेद(hdev->लघु_name, cp->लघु_name,
		    माप(hdev->लघु_name))) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
					data, len);
		जाओ failed;
	पूर्ण

	स_नकल(hdev->लघु_name, cp->लघु_name, माप(hdev->लघु_name));

	अगर (!hdev_is_घातered(hdev)) अणु
		स_नकल(hdev->dev_name, cp->name, माप(hdev->dev_name));

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
					data, len);
		अगर (err < 0)
			जाओ failed;

		err = mgmt_limited_event(MGMT_EV_LOCAL_NAME_CHANGED, hdev, data,
					 len, HCI_MGMT_LOCAL_NAME_EVENTS, sk);
		ext_info_changed(hdev, sk);

		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LOCAL_NAME, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	स_नकल(hdev->dev_name, cp->name, माप(hdev->dev_name));

	hci_req_init(&req, hdev);

	अगर (lmp_bredr_capable(hdev)) अणु
		__hci_req_update_name(&req);
		__hci_req_update_eir(&req);
	पूर्ण

	/* The name is stored in the scan response data and so
	 * no need to udpate the advertising data here.
	 */
	अगर (lmp_le_capable(hdev) && hci_dev_test_flag(hdev, HCI_ADVERTISING))
		__hci_req_update_scan_rsp_data(&req, hdev->cur_adv_instance);

	err = hci_req_run(&req, set_name_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_appearance(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा mgmt_cp_set_appearance *cp = data;
	u16 appearance;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_APPEARANCE,
				       MGMT_STATUS_NOT_SUPPORTED);

	appearance = le16_to_cpu(cp->appearance);

	hci_dev_lock(hdev);

	अगर (hdev->appearance != appearance) अणु
		hdev->appearance = appearance;

		अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
			adv_expire(hdev, MGMT_ADV_FLAG_APPEARANCE);

		ext_info_changed(hdev, sk);
	पूर्ण

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_APPEARANCE, 0, शून्य,
				0);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक get_phy_configuration(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				 व्योम *data, u16 len)
अणु
	काष्ठा mgmt_rp_get_phy_configuration rp;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	स_रखो(&rp, 0, माप(rp));

	rp.supported_phys = cpu_to_le32(get_supported_phys(hdev));
	rp.selected_phys = cpu_to_le32(get_selected_phys(hdev));
	rp.configurable_phys = cpu_to_le32(get_configurable_phys(hdev));

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_PHY_CONFIGURATION, 0,
				 &rp, माप(rp));
पूर्ण

पूर्णांक mgmt_phy_configuration_changed(काष्ठा hci_dev *hdev, काष्ठा sock *skip)
अणु
	काष्ठा mgmt_ev_phy_configuration_changed ev;

	स_रखो(&ev, 0, माप(ev));

	ev.selected_phys = cpu_to_le32(get_selected_phys(hdev));

	वापस mgmt_event(MGMT_EV_PHY_CONFIGURATION_CHANGED, hdev, &ev,
			  माप(ev), skip);
पूर्ण

अटल व्योम set_शेष_phy_complete(काष्ठा hci_dev *hdev, u8 status,
				     u16 opcode, काष्ठा sk_buff *skb)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_PHY_CONFIGURATION, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		mgmt_cmd_status(cmd->sk, hdev->id,
				MGMT_OP_SET_PHY_CONFIGURATION,
				mgmt_status(status));
	पूर्ण अन्यथा अणु
		mgmt_cmd_complete(cmd->sk, hdev->id,
				  MGMT_OP_SET_PHY_CONFIGURATION, 0,
				  शून्य, 0);

		mgmt_phy_configuration_changed(hdev, cmd->sk);
	पूर्ण

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_phy_configuration(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				 व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_set_phy_configuration *cp = data;
	काष्ठा hci_cp_le_set_शेष_phy cp_phy;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	u32 selected_phys, configurable_phys, supported_phys, unconfigure_phys;
	u16 pkt_type = (HCI_DH1 | HCI_DM1);
	bool changed = false;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	configurable_phys = get_configurable_phys(hdev);
	supported_phys = get_supported_phys(hdev);
	selected_phys = __le32_to_cpu(cp->selected_phys);

	अगर (selected_phys & ~supported_phys)
		वापस mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_PHY_CONFIGURATION,
				       MGMT_STATUS_INVALID_PARAMS);

	unconfigure_phys = supported_phys & ~configurable_phys;

	अगर ((selected_phys & unconfigure_phys) != unconfigure_phys)
		वापस mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_PHY_CONFIGURATION,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (selected_phys == get_selected_phys(hdev))
		वापस mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_SET_PHY_CONFIGURATION,
					 0, शून्य, 0);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_PHY_CONFIGURATION,
				      MGMT_STATUS_REJECTED);
		जाओ unlock;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_PHY_CONFIGURATION, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_PHY_CONFIGURATION,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (selected_phys & MGMT_PHY_BR_1M_3SLOT)
		pkt_type |= (HCI_DH3 | HCI_DM3);
	अन्यथा
		pkt_type &= ~(HCI_DH3 | HCI_DM3);

	अगर (selected_phys & MGMT_PHY_BR_1M_5SLOT)
		pkt_type |= (HCI_DH5 | HCI_DM5);
	अन्यथा
		pkt_type &= ~(HCI_DH5 | HCI_DM5);

	अगर (selected_phys & MGMT_PHY_EDR_2M_1SLOT)
		pkt_type &= ~HCI_2DH1;
	अन्यथा
		pkt_type |= HCI_2DH1;

	अगर (selected_phys & MGMT_PHY_EDR_2M_3SLOT)
		pkt_type &= ~HCI_2DH3;
	अन्यथा
		pkt_type |= HCI_2DH3;

	अगर (selected_phys & MGMT_PHY_EDR_2M_5SLOT)
		pkt_type &= ~HCI_2DH5;
	अन्यथा
		pkt_type |= HCI_2DH5;

	अगर (selected_phys & MGMT_PHY_EDR_3M_1SLOT)
		pkt_type &= ~HCI_3DH1;
	अन्यथा
		pkt_type |= HCI_3DH1;

	अगर (selected_phys & MGMT_PHY_EDR_3M_3SLOT)
		pkt_type &= ~HCI_3DH3;
	अन्यथा
		pkt_type |= HCI_3DH3;

	अगर (selected_phys & MGMT_PHY_EDR_3M_5SLOT)
		pkt_type &= ~HCI_3DH5;
	अन्यथा
		pkt_type |= HCI_3DH5;

	अगर (pkt_type != hdev->pkt_type) अणु
		hdev->pkt_type = pkt_type;
		changed = true;
	पूर्ण

	अगर ((selected_phys & MGMT_PHY_LE_MASK) ==
	    (get_selected_phys(hdev) & MGMT_PHY_LE_MASK)) अणु
		अगर (changed)
			mgmt_phy_configuration_changed(hdev, sk);

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_SET_PHY_CONFIGURATION,
					0, शून्य, 0);

		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_PHY_CONFIGURATION, hdev, data,
			       len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	स_रखो(&cp_phy, 0, माप(cp_phy));

	अगर (!(selected_phys & MGMT_PHY_LE_TX_MASK))
		cp_phy.all_phys |= 0x01;

	अगर (!(selected_phys & MGMT_PHY_LE_RX_MASK))
		cp_phy.all_phys |= 0x02;

	अगर (selected_phys & MGMT_PHY_LE_1M_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_1M;

	अगर (selected_phys & MGMT_PHY_LE_2M_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_2M;

	अगर (selected_phys & MGMT_PHY_LE_CODED_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_CODED;

	अगर (selected_phys & MGMT_PHY_LE_1M_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_1M;

	अगर (selected_phys & MGMT_PHY_LE_2M_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_2M;

	अगर (selected_phys & MGMT_PHY_LE_CODED_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_CODED;

	hci_req_add(&req, HCI_OP_LE_SET_DEFAULT_PHY, माप(cp_phy), &cp_phy);

	err = hci_req_run_skb(&req, set_शेष_phy_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक set_blocked_keys(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 len)
अणु
	पूर्णांक err = MGMT_STATUS_SUCCESS;
	काष्ठा mgmt_cp_set_blocked_keys *keys = data;
	स्थिर u16 max_key_count = ((U16_MAX - माप(*keys)) /
				   माप(काष्ठा mgmt_blocked_key_info));
	u16 key_count, expected_len;
	पूर्णांक i;

	bt_dev_dbg(hdev, "sock %p", sk);

	key_count = __le16_to_cpu(keys->key_count);
	अगर (key_count > max_key_count) अणु
		bt_dev_err(hdev, "too big key_count value %u", key_count);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BLOCKED_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	expected_len = काष्ठा_size(keys, keys, key_count);
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "expected %u bytes, got %u bytes",
			   expected_len, len);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BLOCKED_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	hci_dev_lock(hdev);

	hci_blocked_keys_clear(hdev);

	क्रम (i = 0; i < keys->key_count; ++i) अणु
		काष्ठा blocked_key *b = kzalloc(माप(*b), GFP_KERNEL);

		अगर (!b) अणु
			err = MGMT_STATUS_NO_RESOURCES;
			अवरोध;
		पूर्ण

		b->type = keys->keys[i].type;
		स_नकल(b->val, keys->keys[i].val, माप(b->val));
		list_add_rcu(&b->list, &hdev->blocked_keys);
	पूर्ण
	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_BLOCKED_KEYS,
				err, शून्य, 0);
पूर्ण

अटल पूर्णांक set_wideband_speech(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	पूर्णांक err;
	bool changed = false;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!test_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED, &hdev->quirks))
		वापस mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_WIDEBAND_SPEECH,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_WIDEBAND_SPEECH,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (pending_find(MGMT_OP_SET_WIDEBAND_SPEECH, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_WIDEBAND_SPEECH,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (hdev_is_घातered(hdev) &&
	    !!cp->val != hci_dev_test_flag(hdev,
					   HCI_WIDEBAND_SPEECH_ENABLED)) अणु
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_WIDEBAND_SPEECH,
				      MGMT_STATUS_REJECTED);
		जाओ unlock;
	पूर्ण

	अगर (cp->val)
		changed = !hci_dev_test_and_set_flag(hdev,
						   HCI_WIDEBAND_SPEECH_ENABLED);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev,
						   HCI_WIDEBAND_SPEECH_ENABLED);

	err = send_settings_rsp(sk, MGMT_OP_SET_WIDEBAND_SPEECH, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_controller_cap(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 data_len)
अणु
	अक्षर buf[20];
	काष्ठा mgmt_rp_पढ़ो_controller_cap *rp = (व्योम *)buf;
	u16 cap_len = 0;
	u8 flags = 0;
	u8 tx_घातer_range[2];

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&buf, 0, माप(buf));

	hci_dev_lock(hdev);

	/* When the Read Simple Pairing Options command is supported, then
	 * the remote खुला key validation is supported.
	 *
	 * Alternatively, when Microsoft extensions are available, they can
	 * indicate support क्रम खुला key validation as well.
	 */
	अगर ((hdev->commands[41] & 0x08) || msft_curve_validity(hdev))
		flags |= 0x01;	/* Remote खुला key validation (BR/EDR) */

	flags |= 0x02;		/* Remote खुला key validation (LE) */

	/* When the Read Encryption Key Size command is supported, then the
	 * encryption key size is enक्रमced.
	 */
	अगर (hdev->commands[20] & 0x10)
		flags |= 0x04;	/* Encryption key size enक्रमcement (BR/EDR) */

	flags |= 0x08;		/* Encryption key size enक्रमcement (LE) */

	cap_len = eir_append_data(rp->cap, cap_len, MGMT_CAP_SEC_FLAGS,
				  &flags, 1);

	/* When the Read Simple Pairing Options command is supported, then
	 * also max encryption key size inक्रमmation is provided.
	 */
	अगर (hdev->commands[41] & 0x08)
		cap_len = eir_append_le16(rp->cap, cap_len,
					  MGMT_CAP_MAX_ENC_KEY_SIZE,
					  hdev->max_enc_key_size);

	cap_len = eir_append_le16(rp->cap, cap_len,
				  MGMT_CAP_SMP_MAX_ENC_KEY_SIZE,
				  SMP_MAX_ENC_KEY_SIZE);

	/* Append the min/max LE tx घातer parameters अगर we were able to fetch
	 * it from the controller
	 */
	अगर (hdev->commands[38] & 0x80) अणु
		स_नकल(&tx_घातer_range[0], &hdev->min_le_tx_घातer, 1);
		स_नकल(&tx_घातer_range[1], &hdev->max_le_tx_घातer, 1);
		cap_len = eir_append_data(rp->cap, cap_len, MGMT_CAP_LE_TX_PWR,
					  tx_घातer_range, 2);
	पूर्ण

	rp->cap_len = cpu_to_le16(cap_len);

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_CONTROLLER_CAP, 0,
				 rp, माप(*rp) + cap_len);
पूर्ण

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
/* d4992530-b9ec-469f-ab01-6c481c47da1c */
अटल स्थिर u8 debug_uuid[16] = अणु
	0x1c, 0xda, 0x47, 0x1c, 0x48, 0x6c, 0x01, 0xab,
	0x9f, 0x46, 0xec, 0xb9, 0x30, 0x25, 0x99, 0xd4,
पूर्ण;
#पूर्ण_अगर

/* 671b10b5-42c0-4696-9227-eb28d1b049d6 */
अटल स्थिर u8 simult_central_periph_uuid[16] = अणु
	0xd6, 0x49, 0xb0, 0xd1, 0x28, 0xeb, 0x27, 0x92,
	0x96, 0x46, 0xc0, 0x42, 0xb5, 0x10, 0x1b, 0x67,
पूर्ण;

/* 15c0a148-c273-11ea-b3de-0242ac130004 */
अटल स्थिर u8 rpa_resolution_uuid[16] = अणु
	0x04, 0x00, 0x13, 0xac, 0x42, 0x02, 0xde, 0xb3,
	0xea, 0x11, 0x73, 0xc2, 0x48, 0xa1, 0xc0, 0x15,
पूर्ण;

अटल पूर्णांक पढ़ो_exp_features_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				  व्योम *data, u16 data_len)
अणु
	अक्षर buf[62];	/* Enough space क्रम 3 features */
	काष्ठा mgmt_rp_पढ़ो_exp_features_info *rp = (व्योम *)buf;
	u16 idx = 0;
	u32 flags;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&buf, 0, माप(buf));

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
	अगर (!hdev) अणु
		flags = bt_dbg_get() ? BIT(0) : 0;

		स_नकल(rp->features[idx].uuid, debug_uuid, 16);
		rp->features[idx].flags = cpu_to_le32(flags);
		idx++;
	पूर्ण
#पूर्ण_अगर

	अगर (hdev) अणु
		अगर (test_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks) &&
		    (hdev->le_states[4] & 0x08) &&	/* Central */
		    (hdev->le_states[4] & 0x40) &&	/* Peripheral */
		    (hdev->le_states[3] & 0x10))	/* Simultaneous */
			flags = BIT(0);
		अन्यथा
			flags = 0;

		स_नकल(rp->features[idx].uuid, simult_central_periph_uuid, 16);
		rp->features[idx].flags = cpu_to_le32(flags);
		idx++;
	पूर्ण

	अगर (hdev && use_ll_privacy(hdev)) अणु
		अगर (hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
			flags = BIT(0) | BIT(1);
		अन्यथा
			flags = BIT(1);

		स_नकल(rp->features[idx].uuid, rpa_resolution_uuid, 16);
		rp->features[idx].flags = cpu_to_le32(flags);
		idx++;
	पूर्ण

	rp->feature_count = cpu_to_le16(idx);

	/* After पढ़ोing the experimental features inक्रमmation, enable
	 * the events to update client on any future change.
	 */
	hci_sock_set_flag(sk, HCI_MGMT_EXP_FEATURE_EVENTS);

	वापस mgmt_cmd_complete(sk, hdev ? hdev->id : MGMT_INDEX_NONE,
				 MGMT_OP_READ_EXP_FEATURES_INFO,
				 0, rp, माप(*rp) + (20 * idx));
पूर्ण

अटल पूर्णांक exp_ll_privacy_feature_changed(bool enabled, काष्ठा hci_dev *hdev,
					  काष्ठा sock *skip)
अणु
	काष्ठा mgmt_ev_exp_feature_changed ev;

	स_रखो(&ev, 0, माप(ev));
	स_नकल(ev.uuid, rpa_resolution_uuid, 16);
	ev.flags = cpu_to_le32((enabled ? BIT(0) : 0) | BIT(1));

	वापस mgmt_limited_event(MGMT_EV_EXP_FEATURE_CHANGED, hdev,
				  &ev, माप(ev),
				  HCI_MGMT_EXP_FEATURE_EVENTS, skip);

पूर्ण

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
अटल पूर्णांक exp_debug_feature_changed(bool enabled, काष्ठा sock *skip)
अणु
	काष्ठा mgmt_ev_exp_feature_changed ev;

	स_रखो(&ev, 0, माप(ev));
	स_नकल(ev.uuid, debug_uuid, 16);
	ev.flags = cpu_to_le32(enabled ? BIT(0) : 0);

	वापस mgmt_limited_event(MGMT_EV_EXP_FEATURE_CHANGED, शून्य,
				  &ev, माप(ev),
				  HCI_MGMT_EXP_FEATURE_EVENTS, skip);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक set_exp_feature(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_set_exp_feature *cp = data;
	काष्ठा mgmt_rp_set_exp_feature rp;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!स_भेद(cp->uuid, ZERO_KEY, 16)) अणु
		स_रखो(rp.uuid, 0, 16);
		rp.flags = cpu_to_le32(0);

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
		अगर (!hdev) अणु
			bool changed = bt_dbg_get();

			bt_dbg_set(false);

			अगर (changed)
				exp_debug_feature_changed(false, sk);
		पूर्ण
#पूर्ण_अगर

		अगर (hdev && use_ll_privacy(hdev) && !hdev_is_घातered(hdev)) अणु
			bool changed = hci_dev_test_flag(hdev,
							 HCI_ENABLE_LL_PRIVACY);

			hci_dev_clear_flag(hdev, HCI_ENABLE_LL_PRIVACY);

			अगर (changed)
				exp_ll_privacy_feature_changed(false, hdev, sk);
		पूर्ण

		hci_sock_set_flag(sk, HCI_MGMT_EXP_FEATURE_EVENTS);

		वापस mgmt_cmd_complete(sk, hdev ? hdev->id : MGMT_INDEX_NONE,
					 MGMT_OP_SET_EXP_FEATURE, 0,
					 &rp, माप(rp));
	पूर्ण

#अगर_घोषित CONFIG_BT_FEATURE_DEBUG
	अगर (!स_भेद(cp->uuid, debug_uuid, 16)) अणु
		bool val, changed;
		पूर्णांक err;

		/* Command requires to use the non-controller index */
		अगर (hdev)
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_INDEX);

		/* Parameters are limited to a single octet */
		अगर (data_len != MGMT_SET_EXP_FEATURE_SIZE + 1)
			वापस mgmt_cmd_status(sk, MGMT_INDEX_NONE,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_PARAMS);

		/* Only boolean on/off is supported */
		अगर (cp->param[0] != 0x00 && cp->param[0] != 0x01)
			वापस mgmt_cmd_status(sk, MGMT_INDEX_NONE,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_PARAMS);

		val = !!cp->param[0];
		changed = val ? !bt_dbg_get() : bt_dbg_get();
		bt_dbg_set(val);

		स_नकल(rp.uuid, debug_uuid, 16);
		rp.flags = cpu_to_le32(val ? BIT(0) : 0);

		hci_sock_set_flag(sk, HCI_MGMT_EXP_FEATURE_EVENTS);

		err = mgmt_cmd_complete(sk, MGMT_INDEX_NONE,
					MGMT_OP_SET_EXP_FEATURE, 0,
					&rp, माप(rp));

		अगर (changed)
			exp_debug_feature_changed(val, sk);

		वापस err;
	पूर्ण
#पूर्ण_अगर

	अगर (!स_भेद(cp->uuid, rpa_resolution_uuid, 16)) अणु
		bool val, changed;
		पूर्णांक err;
		u32 flags;

		/* Command requires to use the controller index */
		अगर (!hdev)
			वापस mgmt_cmd_status(sk, MGMT_INDEX_NONE,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_INDEX);

		/* Changes can only be made when controller is घातered करोwn */
		अगर (hdev_is_घातered(hdev))
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_REJECTED);

		/* Parameters are limited to a single octet */
		अगर (data_len != MGMT_SET_EXP_FEATURE_SIZE + 1)
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_PARAMS);

		/* Only boolean on/off is supported */
		अगर (cp->param[0] != 0x00 && cp->param[0] != 0x01)
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_EXP_FEATURE,
					       MGMT_STATUS_INVALID_PARAMS);

		val = !!cp->param[0];

		अगर (val) अणु
			changed = !hci_dev_test_flag(hdev,
						     HCI_ENABLE_LL_PRIVACY);
			hci_dev_set_flag(hdev, HCI_ENABLE_LL_PRIVACY);
			hci_dev_clear_flag(hdev, HCI_ADVERTISING);

			/* Enable LL privacy + supported settings changed */
			flags = BIT(0) | BIT(1);
		पूर्ण अन्यथा अणु
			changed = hci_dev_test_flag(hdev,
						    HCI_ENABLE_LL_PRIVACY);
			hci_dev_clear_flag(hdev, HCI_ENABLE_LL_PRIVACY);

			/* Disable LL privacy + supported settings changed */
			flags = BIT(1);
		पूर्ण

		स_नकल(rp.uuid, rpa_resolution_uuid, 16);
		rp.flags = cpu_to_le32(flags);

		hci_sock_set_flag(sk, HCI_MGMT_EXP_FEATURE_EVENTS);

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_SET_EXP_FEATURE, 0,
					&rp, माप(rp));

		अगर (changed)
			exp_ll_privacy_feature_changed(val, hdev, sk);

		वापस err;
	पूर्ण

	वापस mgmt_cmd_status(sk, hdev ? hdev->id : MGMT_INDEX_NONE,
			       MGMT_OP_SET_EXP_FEATURE,
			       MGMT_STATUS_NOT_SUPPORTED);
पूर्ण

#घोषणा SUPPORTED_DEVICE_FLAGS() ((1U << HCI_CONN_FLAG_MAX) - 1)

अटल पूर्णांक get_device_flags(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 data_len)
अणु
	काष्ठा mgmt_cp_get_device_flags *cp = data;
	काष्ठा mgmt_rp_get_device_flags rp;
	काष्ठा bdaddr_list_with_flags *br_params;
	काष्ठा hci_conn_params *params;
	u32 supported_flags = SUPPORTED_DEVICE_FLAGS();
	u32 current_flags = 0;
	u8 status = MGMT_STATUS_INVALID_PARAMS;

	bt_dev_dbg(hdev, "Get device flags %pMR (type 0x%x)\n",
		   &cp->addr.bdaddr, cp->addr.type);

	hci_dev_lock(hdev);

	अगर (cp->addr.type == BDADDR_BREDR) अणु
		br_params = hci_bdaddr_list_lookup_with_flags(&hdev->whitelist,
							      &cp->addr.bdaddr,
							      cp->addr.type);
		अगर (!br_params)
			जाओ करोne;

		current_flags = br_params->current_flags;
	पूर्ण अन्यथा अणु
		params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr,
						le_addr_type(cp->addr.type));

		अगर (!params)
			जाओ करोne;

		current_flags = params->current_flags;
	पूर्ण

	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;
	rp.supported_flags = cpu_to_le32(supported_flags);
	rp.current_flags = cpu_to_le32(current_flags);

	status = MGMT_STATUS_SUCCESS;

करोne:
	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_DEVICE_FLAGS, status,
				&rp, माप(rp));
पूर्ण

अटल व्योम device_flags_changed(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				 bdaddr_t *bdaddr, u8 bdaddr_type,
				 u32 supported_flags, u32 current_flags)
अणु
	काष्ठा mgmt_ev_device_flags_changed ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = bdaddr_type;
	ev.supported_flags = cpu_to_le32(supported_flags);
	ev.current_flags = cpu_to_le32(current_flags);

	mgmt_event(MGMT_EV_DEVICE_FLAGS_CHANGED, hdev, &ev, माप(ev), sk);
पूर्ण

अटल पूर्णांक set_device_flags(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 len)
अणु
	काष्ठा mgmt_cp_set_device_flags *cp = data;
	काष्ठा bdaddr_list_with_flags *br_params;
	काष्ठा hci_conn_params *params;
	u8 status = MGMT_STATUS_INVALID_PARAMS;
	u32 supported_flags = SUPPORTED_DEVICE_FLAGS();
	u32 current_flags = __le32_to_cpu(cp->current_flags);

	bt_dev_dbg(hdev, "Set device flags %pMR (type 0x%x) = 0x%x",
		   &cp->addr.bdaddr, cp->addr.type,
		   __le32_to_cpu(current_flags));

	अगर ((supported_flags | current_flags) != supported_flags) अणु
		bt_dev_warn(hdev, "Bad flag given (0x%x) vs supported (0x%0x)",
			    current_flags, supported_flags);
		जाओ करोne;
	पूर्ण

	hci_dev_lock(hdev);

	अगर (cp->addr.type == BDADDR_BREDR) अणु
		br_params = hci_bdaddr_list_lookup_with_flags(&hdev->whitelist,
							      &cp->addr.bdaddr,
							      cp->addr.type);

		अगर (br_params) अणु
			br_params->current_flags = current_flags;
			status = MGMT_STATUS_SUCCESS;
		पूर्ण अन्यथा अणु
			bt_dev_warn(hdev, "No such BR/EDR device %pMR (0x%x)",
				    &cp->addr.bdaddr, cp->addr.type);
		पूर्ण
	पूर्ण अन्यथा अणु
		params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr,
						le_addr_type(cp->addr.type));
		अगर (params) अणु
			params->current_flags = current_flags;
			status = MGMT_STATUS_SUCCESS;
		पूर्ण अन्यथा अणु
			bt_dev_warn(hdev, "No such LE device %pMR (0x%x)",
				    &cp->addr.bdaddr,
				    le_addr_type(cp->addr.type));
		पूर्ण
	पूर्ण

करोne:
	hci_dev_unlock(hdev);

	अगर (status == MGMT_STATUS_SUCCESS)
		device_flags_changed(sk, hdev, &cp->addr.bdaddr, cp->addr.type,
				     supported_flags, current_flags);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_DEVICE_FLAGS, status,
				 &cp->addr, माप(cp->addr));
पूर्ण

अटल व्योम mgmt_adv_monitor_added(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				   u16 handle)
अणु
	काष्ठा mgmt_ev_adv_monitor_added ev;

	ev.monitor_handle = cpu_to_le16(handle);

	mgmt_event(MGMT_EV_ADV_MONITOR_ADDED, hdev, &ev, माप(ev), sk);
पूर्ण

व्योम mgmt_adv_monitor_हटाओd(काष्ठा hci_dev *hdev, u16 handle)
अणु
	काष्ठा mgmt_ev_adv_monitor_हटाओd ev;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा sock *sk_skip = शून्य;
	काष्ठा mgmt_cp_हटाओ_adv_monitor *cp;

	cmd = pending_find(MGMT_OP_REMOVE_ADV_MONITOR, hdev);
	अगर (cmd) अणु
		cp = cmd->param;

		अगर (cp->monitor_handle)
			sk_skip = cmd->sk;
	पूर्ण

	ev.monitor_handle = cpu_to_le16(handle);

	mgmt_event(MGMT_EV_ADV_MONITOR_REMOVED, hdev, &ev, माप(ev), sk_skip);
पूर्ण

अटल पूर्णांक पढ़ो_adv_mon_features(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				 व्योम *data, u16 len)
अणु
	काष्ठा adv_monitor *monitor = शून्य;
	काष्ठा mgmt_rp_पढ़ो_adv_monitor_features *rp = शून्य;
	पूर्णांक handle, err;
	माप_प्रकार rp_size = 0;
	__u32 supported = 0;
	__u32 enabled = 0;
	__u16 num_handles = 0;
	__u16 handles[HCI_MAX_ADV_MONITOR_NUM_HANDLES];

	BT_DBG("request for %s", hdev->name);

	hci_dev_lock(hdev);

	अगर (msft_monitor_supported(hdev))
		supported |= MGMT_ADV_MONITOR_FEATURE_MASK_OR_PATTERNS;

	idr_क्रम_each_entry(&hdev->adv_monitors_idr, monitor, handle)
		handles[num_handles++] = monitor->handle;

	hci_dev_unlock(hdev);

	rp_size = माप(*rp) + (num_handles * माप(u16));
	rp = kदो_स्मृति(rp_size, GFP_KERNEL);
	अगर (!rp)
		वापस -ENOMEM;

	/* All supported features are currently enabled */
	enabled = supported;

	rp->supported_features = cpu_to_le32(supported);
	rp->enabled_features = cpu_to_le32(enabled);
	rp->max_num_handles = cpu_to_le16(HCI_MAX_ADV_MONITOR_NUM_HANDLES);
	rp->max_num_patterns = HCI_MAX_ADV_MONITOR_NUM_PATTERNS;
	rp->num_handles = cpu_to_le16(num_handles);
	अगर (num_handles)
		स_नकल(&rp->handles, &handles, (num_handles * माप(u16)));

	err = mgmt_cmd_complete(sk, hdev->id,
				MGMT_OP_READ_ADV_MONITOR_FEATURES,
				MGMT_STATUS_SUCCESS, rp, rp_size);

	kमुक्त(rp);

	वापस err;
पूर्ण

पूर्णांक mgmt_add_adv_patterns_monitor_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_rp_add_adv_patterns_monitor rp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा adv_monitor *monitor;
	पूर्णांक err = 0;

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI, hdev);
	अगर (!cmd) अणु
		cmd = pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR, hdev);
		अगर (!cmd)
			जाओ करोne;
	पूर्ण

	monitor = cmd->user_data;
	rp.monitor_handle = cpu_to_le16(monitor->handle);

	अगर (!status) अणु
		mgmt_adv_monitor_added(cmd->sk, hdev, monitor->handle);
		hdev->adv_monitors_cnt++;
		अगर (monitor->state == ADV_MONITOR_STATE_NOT_REGISTERED)
			monitor->state = ADV_MONITOR_STATE_REGISTERED;
		hci_update_background_scan(hdev);
	पूर्ण

	err = mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
				mgmt_status(status), &rp, माप(rp));
	mgmt_pending_हटाओ(cmd);

करोne:
	hci_dev_unlock(hdev);
	bt_dev_dbg(hdev, "add monitor %d complete, status %d",
		   rp.monitor_handle, status);

	वापस err;
पूर्ण

अटल पूर्णांक __add_adv_patterns_monitor(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				      काष्ठा adv_monitor *m, u8 status,
				      व्योम *data, u16 len, u16 op)
अणु
	काष्ठा mgmt_rp_add_adv_patterns_monitor rp;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;
	bool pending;

	hci_dev_lock(hdev);

	अगर (status)
		जाओ unlock;

	अगर (pending_find(MGMT_OP_SET_LE, hdev) ||
	    pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR, hdev) ||
	    pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI, hdev) ||
	    pending_find(MGMT_OP_REMOVE_ADV_MONITOR, hdev)) अणु
		status = MGMT_STATUS_BUSY;
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, op, hdev, data, len);
	अगर (!cmd) अणु
		status = MGMT_STATUS_NO_RESOURCES;
		जाओ unlock;
	पूर्ण

	cmd->user_data = m;
	pending = hci_add_adv_monitor(hdev, m, &err);
	अगर (err) अणु
		अगर (err == -ENOSPC || err == -ENOMEM)
			status = MGMT_STATUS_NO_RESOURCES;
		अन्यथा अगर (err == -EINVAL)
			status = MGMT_STATUS_INVALID_PARAMS;
		अन्यथा
			status = MGMT_STATUS_FAILED;

		mgmt_pending_हटाओ(cmd);
		जाओ unlock;
	पूर्ण

	अगर (!pending) अणु
		mgmt_pending_हटाओ(cmd);
		rp.monitor_handle = cpu_to_le16(m->handle);
		mgmt_adv_monitor_added(sk, hdev, m->handle);
		m->state = ADV_MONITOR_STATE_REGISTERED;
		hdev->adv_monitors_cnt++;

		hci_dev_unlock(hdev);
		वापस mgmt_cmd_complete(sk, hdev->id, op, MGMT_STATUS_SUCCESS,
					 &rp, माप(rp));
	पूर्ण

	hci_dev_unlock(hdev);

	वापस 0;

unlock:
	hci_मुक्त_adv_monitor(hdev, m);
	hci_dev_unlock(hdev);
	वापस mgmt_cmd_status(sk, hdev->id, op, status);
पूर्ण

अटल व्योम parse_adv_monitor_rssi(काष्ठा adv_monitor *m,
				   काष्ठा mgmt_adv_rssi_thresholds *rssi)
अणु
	अगर (rssi) अणु
		m->rssi.low_threshold = rssi->low_threshold;
		m->rssi.low_threshold_समयout =
		    __le16_to_cpu(rssi->low_threshold_समयout);
		m->rssi.high_threshold = rssi->high_threshold;
		m->rssi.high_threshold_समयout =
		    __le16_to_cpu(rssi->high_threshold_समयout);
		m->rssi.sampling_period = rssi->sampling_period;
	पूर्ण अन्यथा अणु
		/* Default values. These numbers are the least स्थिरricting
		 * parameters क्रम MSFT API to work, so it behaves as अगर there
		 * are no rssi parameter to consider. May need to be changed
		 * अगर other API are to be supported.
		 */
		m->rssi.low_threshold = -127;
		m->rssi.low_threshold_समयout = 60;
		m->rssi.high_threshold = -127;
		m->rssi.high_threshold_समयout = 0;
		m->rssi.sampling_period = 0;
	पूर्ण
पूर्ण

अटल u8 parse_adv_monitor_pattern(काष्ठा adv_monitor *m, u8 pattern_count,
				    काष्ठा mgmt_adv_pattern *patterns)
अणु
	u8 offset = 0, length = 0;
	काष्ठा adv_pattern *p = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < pattern_count; i++) अणु
		offset = patterns[i].offset;
		length = patterns[i].length;
		अगर (offset >= HCI_MAX_AD_LENGTH ||
		    length > HCI_MAX_AD_LENGTH ||
		    (offset + length) > HCI_MAX_AD_LENGTH)
			वापस MGMT_STATUS_INVALID_PARAMS;

		p = kदो_स्मृति(माप(*p), GFP_KERNEL);
		अगर (!p)
			वापस MGMT_STATUS_NO_RESOURCES;

		p->ad_type = patterns[i].ad_type;
		p->offset = patterns[i].offset;
		p->length = patterns[i].length;
		स_नकल(p->value, patterns[i].value, p->length);

		INIT_LIST_HEAD(&p->list);
		list_add(&p->list, &m->patterns);
	पूर्ण

	वापस MGMT_STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक add_adv_patterns_monitor(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				    व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_add_adv_patterns_monitor *cp = data;
	काष्ठा adv_monitor *m = शून्य;
	u8 status = MGMT_STATUS_SUCCESS;
	माप_प्रकार expected_size = माप(*cp);

	BT_DBG("request for %s", hdev->name);

	अगर (len <= माप(*cp)) अणु
		status = MGMT_STATUS_INVALID_PARAMS;
		जाओ करोne;
	पूर्ण

	expected_size += cp->pattern_count * माप(काष्ठा mgmt_adv_pattern);
	अगर (len != expected_size) अणु
		status = MGMT_STATUS_INVALID_PARAMS;
		जाओ करोne;
	पूर्ण

	m = kzalloc(माप(*m), GFP_KERNEL);
	अगर (!m) अणु
		status = MGMT_STATUS_NO_RESOURCES;
		जाओ करोne;
	पूर्ण

	INIT_LIST_HEAD(&m->patterns);

	parse_adv_monitor_rssi(m, शून्य);
	status = parse_adv_monitor_pattern(m, cp->pattern_count, cp->patterns);

करोne:
	वापस __add_adv_patterns_monitor(sk, hdev, m, status, data, len,
					  MGMT_OP_ADD_ADV_PATTERNS_MONITOR);
पूर्ण

अटल पूर्णांक add_adv_patterns_monitor_rssi(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
					 व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_add_adv_patterns_monitor_rssi *cp = data;
	काष्ठा adv_monitor *m = शून्य;
	u8 status = MGMT_STATUS_SUCCESS;
	माप_प्रकार expected_size = माप(*cp);

	BT_DBG("request for %s", hdev->name);

	अगर (len <= माप(*cp)) अणु
		status = MGMT_STATUS_INVALID_PARAMS;
		जाओ करोne;
	पूर्ण

	expected_size += cp->pattern_count * माप(काष्ठा mgmt_adv_pattern);
	अगर (len != expected_size) अणु
		status = MGMT_STATUS_INVALID_PARAMS;
		जाओ करोne;
	पूर्ण

	m = kzalloc(माप(*m), GFP_KERNEL);
	अगर (!m) अणु
		status = MGMT_STATUS_NO_RESOURCES;
		जाओ करोne;
	पूर्ण

	INIT_LIST_HEAD(&m->patterns);

	parse_adv_monitor_rssi(m, &cp->rssi);
	status = parse_adv_monitor_pattern(m, cp->pattern_count, cp->patterns);

करोne:
	वापस __add_adv_patterns_monitor(sk, hdev, m, status, data, len,
					 MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI);
पूर्ण

पूर्णांक mgmt_हटाओ_adv_monitor_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_rp_हटाओ_adv_monitor rp;
	काष्ठा mgmt_cp_हटाओ_adv_monitor *cp;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err = 0;

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_REMOVE_ADV_MONITOR, hdev);
	अगर (!cmd)
		जाओ करोne;

	cp = cmd->param;
	rp.monitor_handle = cp->monitor_handle;

	अगर (!status)
		hci_update_background_scan(hdev);

	err = mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
				mgmt_status(status), &rp, माप(rp));
	mgmt_pending_हटाओ(cmd);

करोne:
	hci_dev_unlock(hdev);
	bt_dev_dbg(hdev, "remove monitor %d complete, status %d",
		   rp.monitor_handle, status);

	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_adv_monitor(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_हटाओ_adv_monitor *cp = data;
	काष्ठा mgmt_rp_हटाओ_adv_monitor rp;
	काष्ठा mgmt_pending_cmd *cmd;
	u16 handle = __le16_to_cpu(cp->monitor_handle);
	पूर्णांक err, status;
	bool pending;

	BT_DBG("request for %s", hdev->name);
	rp.monitor_handle = cp->monitor_handle;

	hci_dev_lock(hdev);

	अगर (pending_find(MGMT_OP_SET_LE, hdev) ||
	    pending_find(MGMT_OP_REMOVE_ADV_MONITOR, hdev) ||
	    pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR, hdev) ||
	    pending_find(MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI, hdev)) अणु
		status = MGMT_STATUS_BUSY;
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_REMOVE_ADV_MONITOR, hdev, data, len);
	अगर (!cmd) अणु
		status = MGMT_STATUS_NO_RESOURCES;
		जाओ unlock;
	पूर्ण

	अगर (handle)
		pending = hci_हटाओ_single_adv_monitor(hdev, handle, &err);
	अन्यथा
		pending = hci_हटाओ_all_adv_monitor(hdev, &err);

	अगर (err) अणु
		mgmt_pending_हटाओ(cmd);

		अगर (err == -ENOENT)
			status = MGMT_STATUS_INVALID_INDEX;
		अन्यथा
			status = MGMT_STATUS_FAILED;

		जाओ unlock;
	पूर्ण

	/* monitor can be हटाओd without क्रमwarding request to controller */
	अगर (!pending) अणु
		mgmt_pending_हटाओ(cmd);
		hci_dev_unlock(hdev);

		वापस mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_REMOVE_ADV_MONITOR,
					 MGMT_STATUS_SUCCESS,
					 &rp, माप(rp));
	पूर्ण

	hci_dev_unlock(hdev);
	वापस 0;

unlock:
	hci_dev_unlock(hdev);
	वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_ADV_MONITOR,
			       status);
पूर्ण

अटल व्योम पढ़ो_local_oob_data_complete(काष्ठा hci_dev *hdev, u8 status,
				         u16 opcode, काष्ठा sk_buff *skb)
अणु
	काष्ठा mgmt_rp_पढ़ो_local_oob_data mgmt_rp;
	माप_प्रकार rp_size = माप(mgmt_rp);
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status %u", status);

	cmd = pending_find(MGMT_OP_READ_LOCAL_OOB_DATA, hdev);
	अगर (!cmd)
		वापस;

	अगर (status || !skb) अणु
		mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
				status ? mgmt_status(status) : MGMT_STATUS_FAILED);
		जाओ हटाओ;
	पूर्ण

	स_रखो(&mgmt_rp, 0, माप(mgmt_rp));

	अगर (opcode == HCI_OP_READ_LOCAL_OOB_DATA) अणु
		काष्ठा hci_rp_पढ़ो_local_oob_data *rp = (व्योम *) skb->data;

		अगर (skb->len < माप(*rp)) अणु
			mgmt_cmd_status(cmd->sk, hdev->id,
					MGMT_OP_READ_LOCAL_OOB_DATA,
					MGMT_STATUS_FAILED);
			जाओ हटाओ;
		पूर्ण

		स_नकल(mgmt_rp.hash192, rp->hash, माप(rp->hash));
		स_नकल(mgmt_rp.अक्रम192, rp->अक्रम, माप(rp->अक्रम));

		rp_size -= माप(mgmt_rp.hash256) + माप(mgmt_rp.अक्रम256);
	पूर्ण अन्यथा अणु
		काष्ठा hci_rp_पढ़ो_local_oob_ext_data *rp = (व्योम *) skb->data;

		अगर (skb->len < माप(*rp)) अणु
			mgmt_cmd_status(cmd->sk, hdev->id,
					MGMT_OP_READ_LOCAL_OOB_DATA,
					MGMT_STATUS_FAILED);
			जाओ हटाओ;
		पूर्ण

		स_नकल(mgmt_rp.hash192, rp->hash192, माप(rp->hash192));
		स_नकल(mgmt_rp.अक्रम192, rp->अक्रम192, माप(rp->अक्रम192));

		स_नकल(mgmt_rp.hash256, rp->hash256, माप(rp->hash256));
		स_नकल(mgmt_rp.अक्रम256, rp->अक्रम256, माप(rp->अक्रम256));
	पूर्ण

	mgmt_cmd_complete(cmd->sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
			  MGMT_STATUS_SUCCESS, &mgmt_rp, rp_size);

हटाओ:
	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल पूर्णांक पढ़ो_local_oob_data(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
				      MGMT_STATUS_NOT_POWERED);
		जाओ unlock;
	पूर्ण

	अगर (!lmp_ssp_capable(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
				      MGMT_STATUS_NOT_SUPPORTED);
		जाओ unlock;
	पूर्ण

	अगर (pending_find(MGMT_OP_READ_LOCAL_OOB_DATA, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_DATA,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_READ_LOCAL_OOB_DATA, hdev, शून्य, 0);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	अगर (bredr_sc_enabled(hdev))
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_EXT_DATA, 0, शून्य);
	अन्यथा
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_DATA, 0, शून्य);

	err = hci_req_run_skb(&req, पढ़ो_local_oob_data_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक add_remote_oob_data(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 len)
अणु
	काष्ठा mgmt_addr_info *addr = data;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!bdaddr_type_is_valid(addr->type))
		वापस mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_ADD_REMOTE_OOB_DATA,
					 MGMT_STATUS_INVALID_PARAMS,
					 addr, माप(*addr));

	hci_dev_lock(hdev);

	अगर (len == MGMT_ADD_REMOTE_OOB_DATA_SIZE) अणु
		काष्ठा mgmt_cp_add_remote_oob_data *cp = data;
		u8 status;

		अगर (cp->addr.type != BDADDR_BREDR) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_ADD_REMOTE_OOB_DATA,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		err = hci_add_remote_oob_data(hdev, &cp->addr.bdaddr,
					      cp->addr.type, cp->hash,
					      cp->अक्रम, शून्य, शून्य);
		अगर (err < 0)
			status = MGMT_STATUS_FAILED;
		अन्यथा
			status = MGMT_STATUS_SUCCESS;

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_ADD_REMOTE_OOB_DATA, status,
					&cp->addr, माप(cp->addr));
	पूर्ण अन्यथा अगर (len == MGMT_ADD_REMOTE_OOB_EXT_DATA_SIZE) अणु
		काष्ठा mgmt_cp_add_remote_oob_ext_data *cp = data;
		u8 *अक्रम192, *hash192, *अक्रम256, *hash256;
		u8 status;

		अगर (bdaddr_type_is_le(cp->addr.type)) अणु
			/* Enक्रमce zero-valued 192-bit parameters as
			 * दीर्घ as legacy SMP OOB isn't implemented.
			 */
			अगर (स_भेद(cp->अक्रम192, ZERO_KEY, 16) ||
			    स_भेद(cp->hash192, ZERO_KEY, 16)) अणु
				err = mgmt_cmd_complete(sk, hdev->id,
							MGMT_OP_ADD_REMOTE_OOB_DATA,
							MGMT_STATUS_INVALID_PARAMS,
							addr, माप(*addr));
				जाओ unlock;
			पूर्ण

			अक्रम192 = शून्य;
			hash192 = शून्य;
		पूर्ण अन्यथा अणु
			/* In हाल one of the P-192 values is set to zero,
			 * then just disable OOB data क्रम P-192.
			 */
			अगर (!स_भेद(cp->अक्रम192, ZERO_KEY, 16) ||
			    !स_भेद(cp->hash192, ZERO_KEY, 16)) अणु
				अक्रम192 = शून्य;
				hash192 = शून्य;
			पूर्ण अन्यथा अणु
				अक्रम192 = cp->अक्रम192;
				hash192 = cp->hash192;
			पूर्ण
		पूर्ण

		/* In हाल one of the P-256 values is set to zero, then just
		 * disable OOB data क्रम P-256.
		 */
		अगर (!स_भेद(cp->अक्रम256, ZERO_KEY, 16) ||
		    !स_भेद(cp->hash256, ZERO_KEY, 16)) अणु
			अक्रम256 = शून्य;
			hash256 = शून्य;
		पूर्ण अन्यथा अणु
			अक्रम256 = cp->अक्रम256;
			hash256 = cp->hash256;
		पूर्ण

		err = hci_add_remote_oob_data(hdev, &cp->addr.bdaddr,
					      cp->addr.type, hash192, अक्रम192,
					      hash256, अक्रम256);
		अगर (err < 0)
			status = MGMT_STATUS_FAILED;
		अन्यथा
			status = MGMT_STATUS_SUCCESS;

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_ADD_REMOTE_OOB_DATA,
					status, &cp->addr, माप(cp->addr));
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "add_remote_oob_data: invalid len of %u bytes",
			   len);
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_REMOTE_OOB_DATA,
				      MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_remote_oob_data(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				  व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_हटाओ_remote_oob_data *cp = data;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (cp->addr.type != BDADDR_BREDR)
		वापस mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_REMOVE_REMOTE_OOB_DATA,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, माप(cp->addr));

	hci_dev_lock(hdev);

	अगर (!bacmp(&cp->addr.bdaddr, BDADDR_ANY)) अणु
		hci_remote_oob_data_clear(hdev);
		status = MGMT_STATUS_SUCCESS;
		जाओ करोne;
	पूर्ण

	err = hci_हटाओ_remote_oob_data(hdev, &cp->addr.bdaddr, cp->addr.type);
	अगर (err < 0)
		status = MGMT_STATUS_INVALID_PARAMS;
	अन्यथा
		status = MGMT_STATUS_SUCCESS;

करोne:
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_REMOVE_REMOTE_OOB_DATA,
				status, &cp->addr, माप(cp->addr));

	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

व्योम mgmt_start_discovery_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status %d", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_START_DISCOVERY, hdev);
	अगर (!cmd)
		cmd = pending_find(MGMT_OP_START_SERVICE_DISCOVERY, hdev);

	अगर (!cmd)
		cmd = pending_find(MGMT_OP_START_LIMITED_DISCOVERY, hdev);

	अगर (cmd) अणु
		cmd->cmd_complete(cmd, mgmt_status(status));
		mgmt_pending_हटाओ(cmd);
	पूर्ण

	hci_dev_unlock(hdev);

	/* Handle suspend notअगरier */
	अगर (test_and_clear_bit(SUSPEND_UNPAUSE_DISCOVERY,
			       hdev->suspend_tasks)) अणु
		bt_dev_dbg(hdev, "Unpaused discovery");
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण
पूर्ण

अटल bool discovery_type_is_valid(काष्ठा hci_dev *hdev, uपूर्णांक8_t type,
				    uपूर्णांक8_t *mgmt_status)
अणु
	चयन (type) अणु
	हाल DISCOV_TYPE_LE:
		*mgmt_status = mgmt_le_support(hdev);
		अगर (*mgmt_status)
			वापस false;
		अवरोध;
	हाल DISCOV_TYPE_INTERLEAVED:
		*mgmt_status = mgmt_le_support(hdev);
		अगर (*mgmt_status)
			वापस false;
		fallthrough;
	हाल DISCOV_TYPE_BREDR:
		*mgmt_status = mgmt_bredr_support(hdev);
		अगर (*mgmt_status)
			वापस false;
		अवरोध;
	शेष:
		*mgmt_status = MGMT_STATUS_INVALID_PARAMS;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक start_discovery_पूर्णांकernal(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				    u16 op, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_start_discovery *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, op,
					MGMT_STATUS_NOT_POWERED,
					&cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	अगर (hdev->discovery.state != DISCOVERY_STOPPED ||
	    hci_dev_test_flag(hdev, HCI_PERIODIC_INQ)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, op, MGMT_STATUS_BUSY,
					&cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	अगर (!discovery_type_is_valid(hdev, cp->type, &status)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, op, status,
					&cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	/* Can't start discovery when it is छोड़ोd */
	अगर (hdev->discovery_छोड़ोd) अणु
		err = mgmt_cmd_complete(sk, hdev->id, op, MGMT_STATUS_BUSY,
					&cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	/* Clear the discovery filter first to मुक्त any previously
	 * allocated memory क्रम the UUID list.
	 */
	hci_discovery_filter_clear(hdev);

	hdev->discovery.type = cp->type;
	hdev->discovery.report_invalid_rssi = false;
	अगर (op == MGMT_OP_START_LIMITED_DISCOVERY)
		hdev->discovery.limited = true;
	अन्यथा
		hdev->discovery.limited = false;

	cmd = mgmt_pending_add(sk, op, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	cmd->cmd_complete = generic_cmd_complete;

	hci_discovery_set_state(hdev, DISCOVERY_STARTING);
	queue_work(hdev->req_workqueue, &hdev->discov_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक start_discovery(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   व्योम *data, u16 len)
अणु
	वापस start_discovery_पूर्णांकernal(sk, hdev, MGMT_OP_START_DISCOVERY,
					data, len);
पूर्ण

अटल पूर्णांक start_limited_discovery(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				   व्योम *data, u16 len)
अणु
	वापस start_discovery_पूर्णांकernal(sk, hdev,
					MGMT_OP_START_LIMITED_DISCOVERY,
					data, len);
पूर्ण

अटल पूर्णांक service_discovery_cmd_complete(काष्ठा mgmt_pending_cmd *cmd,
					  u8 status)
अणु
	वापस mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status,
				 cmd->param, 1);
पूर्ण

अटल पूर्णांक start_service_discovery(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				   व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_start_service_discovery *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	स्थिर u16 max_uuid_count = ((U16_MAX - माप(*cp)) / 16);
	u16 uuid_count, expected_len;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					MGMT_STATUS_NOT_POWERED,
					&cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	अगर (hdev->discovery.state != DISCOVERY_STOPPED ||
	    hci_dev_test_flag(hdev, HCI_PERIODIC_INQ)) अणु
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					MGMT_STATUS_BUSY, &cp->type,
					माप(cp->type));
		जाओ failed;
	पूर्ण

	अगर (hdev->discovery_छोड़ोd) अणु
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					MGMT_STATUS_BUSY, &cp->type,
					माप(cp->type));
		जाओ failed;
	पूर्ण

	uuid_count = __le16_to_cpu(cp->uuid_count);
	अगर (uuid_count > max_uuid_count) अणु
		bt_dev_err(hdev, "service_discovery: too big uuid_count value %u",
			   uuid_count);
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					MGMT_STATUS_INVALID_PARAMS, &cp->type,
					माप(cp->type));
		जाओ failed;
	पूर्ण

	expected_len = माप(*cp) + uuid_count * 16;
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "service_discovery: expected %u bytes, got %u bytes",
			   expected_len, len);
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					MGMT_STATUS_INVALID_PARAMS, &cp->type,
					माप(cp->type));
		जाओ failed;
	पूर्ण

	अगर (!discovery_type_is_valid(hdev, cp->type, &status)) अणु
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_START_SERVICE_DISCOVERY,
					status, &cp->type, माप(cp->type));
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_START_SERVICE_DISCOVERY,
			       hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	cmd->cmd_complete = service_discovery_cmd_complete;

	/* Clear the discovery filter first to मुक्त any previously
	 * allocated memory क्रम the UUID list.
	 */
	hci_discovery_filter_clear(hdev);

	hdev->discovery.result_filtering = true;
	hdev->discovery.type = cp->type;
	hdev->discovery.rssi = cp->rssi;
	hdev->discovery.uuid_count = uuid_count;

	अगर (uuid_count > 0) अणु
		hdev->discovery.uuids = kmemdup(cp->uuids, uuid_count * 16,
						GFP_KERNEL);
		अगर (!hdev->discovery.uuids) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_START_SERVICE_DISCOVERY,
						MGMT_STATUS_FAILED,
						&cp->type, माप(cp->type));
			mgmt_pending_हटाओ(cmd);
			जाओ failed;
		पूर्ण
	पूर्ण

	hci_discovery_set_state(hdev, DISCOVERY_STARTING);
	queue_work(hdev->req_workqueue, &hdev->discov_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

व्योम mgmt_stop_discovery_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status %d", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_STOP_DISCOVERY, hdev);
	अगर (cmd) अणु
		cmd->cmd_complete(cmd, mgmt_status(status));
		mgmt_pending_हटाओ(cmd);
	पूर्ण

	hci_dev_unlock(hdev);

	/* Handle suspend notअगरier */
	अगर (test_and_clear_bit(SUSPEND_PAUSE_DISCOVERY, hdev->suspend_tasks)) अणु
		bt_dev_dbg(hdev, "Paused discovery");
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण
पूर्ण

अटल पूर्णांक stop_discovery(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा mgmt_cp_stop_discovery *mgmt_cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hci_discovery_active(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_STOP_DISCOVERY,
					MGMT_STATUS_REJECTED, &mgmt_cp->type,
					माप(mgmt_cp->type));
		जाओ unlock;
	पूर्ण

	अगर (hdev->discovery.type != mgmt_cp->type) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_STOP_DISCOVERY,
					MGMT_STATUS_INVALID_PARAMS,
					&mgmt_cp->type, माप(mgmt_cp->type));
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_STOP_DISCOVERY, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	cmd->cmd_complete = generic_cmd_complete;

	hci_discovery_set_state(hdev, DISCOVERY_STOPPING);
	queue_work(hdev->req_workqueue, &hdev->discov_update);
	err = 0;

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक confirm_name(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			u16 len)
अणु
	काष्ठा mgmt_cp_confirm_name *cp = data;
	काष्ठा inquiry_entry *e;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (!hci_discovery_active(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME,
					MGMT_STATUS_FAILED, &cp->addr,
					माप(cp->addr));
		जाओ failed;
	पूर्ण

	e = hci_inquiry_cache_lookup_unknown(hdev, &cp->addr.bdaddr);
	अगर (!e) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME,
					MGMT_STATUS_INVALID_PARAMS, &cp->addr,
					माप(cp->addr));
		जाओ failed;
	पूर्ण

	अगर (cp->name_known) अणु
		e->name_state = NAME_KNOWN;
		list_del(&e->list);
	पूर्ण अन्यथा अणु
		e->name_state = NAME_NEEDED;
		hci_inquiry_cache_update_resolve(hdev, e);
	पूर्ण

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME, 0,
				&cp->addr, माप(cp->addr));

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक block_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			u16 len)
अणु
	काष्ठा mgmt_cp_block_device *cp = data;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_BLOCK_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, माप(cp->addr));

	hci_dev_lock(hdev);

	err = hci_bdaddr_list_add(&hdev->blacklist, &cp->addr.bdaddr,
				  cp->addr.type);
	अगर (err < 0) अणु
		status = MGMT_STATUS_FAILED;
		जाओ करोne;
	पूर्ण

	mgmt_event(MGMT_EV_DEVICE_BLOCKED, hdev, &cp->addr, माप(cp->addr),
		   sk);
	status = MGMT_STATUS_SUCCESS;

करोne:
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_BLOCK_DEVICE, status,
				&cp->addr, माप(cp->addr));

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक unblock_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 len)
अणु
	काष्ठा mgmt_cp_unblock_device *cp = data;
	u8 status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNBLOCK_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, माप(cp->addr));

	hci_dev_lock(hdev);

	err = hci_bdaddr_list_del(&hdev->blacklist, &cp->addr.bdaddr,
				  cp->addr.type);
	अगर (err < 0) अणु
		status = MGMT_STATUS_INVALID_PARAMS;
		जाओ करोne;
	पूर्ण

	mgmt_event(MGMT_EV_DEVICE_UNBLOCKED, hdev, &cp->addr, माप(cp->addr),
		   sk);
	status = MGMT_STATUS_SUCCESS;

करोne:
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNBLOCK_DEVICE, status,
				&cp->addr, माप(cp->addr));

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक set_device_id(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 len)
अणु
	काष्ठा mgmt_cp_set_device_id *cp = data;
	काष्ठा hci_request req;
	पूर्णांक err;
	__u16 source;

	bt_dev_dbg(hdev, "sock %p", sk);

	source = __le16_to_cpu(cp->source);

	अगर (source > 0x0002)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEVICE_ID,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	hdev->devid_source = source;
	hdev->devid_venकरोr = __le16_to_cpu(cp->venकरोr);
	hdev->devid_product = __le16_to_cpu(cp->product);
	hdev->devid_version = __le16_to_cpu(cp->version);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_DEVICE_ID, 0,
				शून्य, 0);

	hci_req_init(&req, hdev);
	__hci_req_update_eir(&req);
	hci_req_run(&req, शून्य);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल व्योम enable_advertising_instance(काष्ठा hci_dev *hdev, u8 status,
					u16 opcode)
अणु
	bt_dev_dbg(hdev, "status %d", status);
पूर्ण

अटल व्योम set_advertising_complete(काष्ठा hci_dev *hdev, u8 status,
				     u16 opcode)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;
	काष्ठा hci_request req;
	u8 instance;
	काष्ठा adv_info *adv_instance;
	पूर्णांक err;

	hci_dev_lock(hdev);

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);

		mgmt_pending_क्रमeach(MGMT_OP_SET_ADVERTISING, hdev,
				     cmd_status_rsp, &mgmt_err);
		जाओ unlock;
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
		hci_dev_set_flag(hdev, HCI_ADVERTISING);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_ADVERTISING);

	mgmt_pending_क्रमeach(MGMT_OP_SET_ADVERTISING, hdev, settings_rsp,
			     &match);

	new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);

	/* Handle suspend notअगरier */
	अगर (test_and_clear_bit(SUSPEND_PAUSE_ADVERTISING,
			       hdev->suspend_tasks)) अणु
		bt_dev_dbg(hdev, "Paused advertising");
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण अन्यथा अगर (test_and_clear_bit(SUSPEND_UNPAUSE_ADVERTISING,
				      hdev->suspend_tasks)) अणु
		bt_dev_dbg(hdev, "Unpaused advertising");
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण

	/* If "Set Advertising" was just disabled and instance advertising was
	 * set up earlier, then re-enable multi-instance advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    list_empty(&hdev->adv_instances))
		जाओ unlock;

	instance = hdev->cur_adv_instance;
	अगर (!instance) अणु
		adv_instance = list_first_entry_or_null(&hdev->adv_instances,
							काष्ठा adv_info, list);
		अगर (!adv_instance)
			जाओ unlock;

		instance = adv_instance->instance;
	पूर्ण

	hci_req_init(&req, hdev);

	err = __hci_req_schedule_adv_instance(&req, instance, true);

	अगर (!err)
		err = hci_req_run(&req, enable_advertising_instance);

	अगर (err)
		bt_dev_err(hdev, "failed to re-configure advertising");

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_advertising(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	u8 val, status;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	status = mgmt_le_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       status);

	/* Enabling the experimental LL Privay support disables support क्रम
	 * advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (hdev->advertising_छोड़ोd)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       MGMT_STATUS_BUSY);

	hci_dev_lock(hdev);

	val = !!cp->val;

	/* The following conditions are ones which mean that we should
	 * not करो any HCI communication but directly send a mgmt
	 * response to user space (after toggling the flag अगर
	 * necessary).
	 */
	अगर (!hdev_is_घातered(hdev) ||
	    (val == hci_dev_test_flag(hdev, HCI_ADVERTISING) &&
	     (cp->val == 0x02) == hci_dev_test_flag(hdev, HCI_ADVERTISING_CONNECTABLE)) ||
	    hci_conn_num(hdev, LE_LINK) > 0 ||
	    (hci_dev_test_flag(hdev, HCI_LE_SCAN) &&
	     hdev->le_scan_type == LE_SCAN_ACTIVE)) अणु
		bool changed;

		अगर (cp->val) अणु
			hdev->cur_adv_instance = 0x00;
			changed = !hci_dev_test_and_set_flag(hdev, HCI_ADVERTISING);
			अगर (cp->val == 0x02)
				hci_dev_set_flag(hdev, HCI_ADVERTISING_CONNECTABLE);
			अन्यथा
				hci_dev_clear_flag(hdev, HCI_ADVERTISING_CONNECTABLE);
		पूर्ण अन्यथा अणु
			changed = hci_dev_test_and_clear_flag(hdev, HCI_ADVERTISING);
			hci_dev_clear_flag(hdev, HCI_ADVERTISING_CONNECTABLE);
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_ADVERTISING, hdev);
		अगर (err < 0)
			जाओ unlock;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ unlock;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_ADVERTISING, hdev) ||
	    pending_find(MGMT_OP_SET_LE, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_ADVERTISING, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	अगर (cp->val == 0x02)
		hci_dev_set_flag(hdev, HCI_ADVERTISING_CONNECTABLE);
	अन्यथा
		hci_dev_clear_flag(hdev, HCI_ADVERTISING_CONNECTABLE);

	cancel_adv_समयout(hdev);

	अगर (val) अणु
		/* Switch to instance "0" क्रम the Set Advertising setting.
		 * We cannot use update_[adv|scan_rsp]_data() here as the
		 * HCI_ADVERTISING flag is not yet set.
		 */
		hdev->cur_adv_instance = 0x00;

		अगर (ext_adv_capable(hdev)) अणु
			__hci_req_start_ext_adv(&req, 0x00);
		पूर्ण अन्यथा अणु
			__hci_req_update_adv_data(&req, 0x00);
			__hci_req_update_scan_rsp_data(&req, 0x00);
			__hci_req_enable_advertising(&req);
		पूर्ण
	पूर्ण अन्यथा अणु
		__hci_req_disable_advertising(&req);
	पूर्ण

	err = hci_req_run(&req, set_advertising_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_अटल_address(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_set_अटल_address *cp = data;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_STATIC_ADDRESS,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (hdev_is_घातered(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_STATIC_ADDRESS,
				       MGMT_STATUS_REJECTED);

	अगर (bacmp(&cp->bdaddr, BDADDR_ANY)) अणु
		अगर (!bacmp(&cp->bdaddr, BDADDR_NONE))
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_STATIC_ADDRESS,
					       MGMT_STATUS_INVALID_PARAMS);

		/* Two most signअगरicant bits shall be set */
		अगर ((cp->bdaddr.b[5] & 0xc0) != 0xc0)
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_STATIC_ADDRESS,
					       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	hci_dev_lock(hdev);

	bacpy(&hdev->अटल_addr, &cp->bdaddr);

	err = send_settings_rsp(sk, MGMT_OP_SET_STATIC_ADDRESS, hdev);
	अगर (err < 0)
		जाओ unlock;

	err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_scan_params(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_set_scan_params *cp = data;
	__u16 पूर्णांकerval, winकरोw;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_NOT_SUPPORTED);

	पूर्णांकerval = __le16_to_cpu(cp->पूर्णांकerval);

	अगर (पूर्णांकerval < 0x0004 || पूर्णांकerval > 0x4000)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	winकरोw = __le16_to_cpu(cp->winकरोw);

	अगर (winकरोw < 0x0004 || winकरोw > 0x4000)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (winकरोw > पूर्णांकerval)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	hdev->le_scan_पूर्णांकerval = पूर्णांकerval;
	hdev->le_scan_winकरोw = winकरोw;

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS, 0,
				शून्य, 0);

	/* If background scan is running, restart it so new parameters are
	 * loaded.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN) &&
	    hdev->discovery.state == DISCOVERY_STOPPED) अणु
		काष्ठा hci_request req;

		hci_req_init(&req, hdev);

		hci_req_add_le_scan_disable(&req, false);
		hci_req_add_le_passive_scan(&req);

		hci_req_run(&req, शून्य);
	पूर्ण

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल व्योम fast_connectable_complete(काष्ठा hci_dev *hdev, u8 status,
				      u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_FAST_CONNECTABLE, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_SET_FAST_CONNECTABLE,
			        mgmt_status(status));
	पूर्ण अन्यथा अणु
		काष्ठा mgmt_mode *cp = cmd->param;

		अगर (cp->val)
			hci_dev_set_flag(hdev, HCI_FAST_CONNECTABLE);
		अन्यथा
			hci_dev_clear_flag(hdev, HCI_FAST_CONNECTABLE);

		send_settings_rsp(cmd->sk, MGMT_OP_SET_FAST_CONNECTABLE, hdev);
		new_settings(hdev, cmd->sk);
	पूर्ण

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_fast_connectable(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) ||
	    hdev->hci_ver < BLUETOOTH_VER_1_2)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_FAST_CONNECTABLE,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_FAST_CONNECTABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (pending_find(MGMT_OP_SET_FAST_CONNECTABLE, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_FAST_CONNECTABLE,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (!!cp->val == hci_dev_test_flag(hdev, HCI_FAST_CONNECTABLE)) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_FAST_CONNECTABLE,
					hdev);
		जाओ unlock;
	पूर्ण

	अगर (!hdev_is_घातered(hdev)) अणु
		hci_dev_change_flag(hdev, HCI_FAST_CONNECTABLE);
		err = send_settings_rsp(sk, MGMT_OP_SET_FAST_CONNECTABLE,
					hdev);
		new_settings(hdev, sk);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_FAST_CONNECTABLE, hdev,
			       data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	__hci_req_ग_लिखो_fast_connectable(&req, cp->val);

	err = hci_req_run(&req, fast_connectable_complete);
	अगर (err < 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_FAST_CONNECTABLE,
				      MGMT_STATUS_FAILED);
		mgmt_pending_हटाओ(cmd);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल व्योम set_bredr_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	bt_dev_dbg(hdev, "status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_BREDR, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);

		/* We need to restore the flag अगर related HCI commands
		 * failed.
		 */
		hci_dev_clear_flag(hdev, HCI_BREDR_ENABLED);

		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode, mgmt_err);
	पूर्ण अन्यथा अणु
		send_settings_rsp(cmd->sk, MGMT_OP_SET_BREDR, hdev);
		new_settings(hdev, cmd->sk);
	पूर्ण

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_bredr(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_bredr_capable(hdev) || !lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_REJECTED);

	अगर (cp->val != 0x00 && cp->val != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (cp->val == hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_BREDR, hdev);
		जाओ unlock;
	पूर्ण

	अगर (!hdev_is_घातered(hdev)) अणु
		अगर (!cp->val) अणु
			hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
			hci_dev_clear_flag(hdev, HCI_SSP_ENABLED);
			hci_dev_clear_flag(hdev, HCI_LINK_SECURITY);
			hci_dev_clear_flag(hdev, HCI_FAST_CONNECTABLE);
			hci_dev_clear_flag(hdev, HCI_HS_ENABLED);
		पूर्ण

		hci_dev_change_flag(hdev, HCI_BREDR_ENABLED);

		err = send_settings_rsp(sk, MGMT_OP_SET_BREDR, hdev);
		अगर (err < 0)
			जाओ unlock;

		err = new_settings(hdev, sk);
		जाओ unlock;
	पूर्ण

	/* Reject disabling when घातered on */
	अगर (!cp->val) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				      MGMT_STATUS_REJECTED);
		जाओ unlock;
	पूर्ण अन्यथा अणु
		/* When configuring a dual-mode controller to operate
		 * with LE only and using a अटल address, then चयनing
		 * BR/EDR back on is not allowed.
		 *
		 * Dual-mode controllers shall operate with the खुला
		 * address as its identity address क्रम BR/EDR and LE. So
		 * reject the attempt to create an invalid configuration.
		 *
		 * The same restrictions applies when secure connections
		 * has been enabled. For BR/EDR this is a controller feature
		 * जबतक क्रम LE it is a host stack feature. This means that
		 * चयनing BR/EDR back on when secure connections has been
		 * enabled is not a supported transaction.
		 */
		अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
		    (bacmp(&hdev->अटल_addr, BDADDR_ANY) ||
		     hci_dev_test_flag(hdev, HCI_SC_ENABLED))) अणु
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
					      MGMT_STATUS_REJECTED);
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_BREDR, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_BREDR, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	/* We need to flip the bit alपढ़ोy here so that
	 * hci_req_update_adv_data generates the correct flags.
	 */
	hci_dev_set_flag(hdev, HCI_BREDR_ENABLED);

	hci_req_init(&req, hdev);

	__hci_req_ग_लिखो_fast_connectable(&req, false);
	__hci_req_update_scan(&req);

	/* Since only the advertising data flags will change, there
	 * is no need to update the scan response data.
	 */
	__hci_req_update_adv_data(&req, hdev->cur_adv_instance);

	err = hci_req_run(&req, set_bredr_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल व्योम sc_enable_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा mgmt_mode *cp;

	bt_dev_dbg(hdev, "status %u", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_SECURE_CONN, hdev);
	अगर (!cmd)
		जाओ unlock;

	अगर (status) अणु
		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode,
			        mgmt_status(status));
		जाओ हटाओ;
	पूर्ण

	cp = cmd->param;

	चयन (cp->val) अणु
	हाल 0x00:
		hci_dev_clear_flag(hdev, HCI_SC_ENABLED);
		hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		अवरोध;
	हाल 0x01:
		hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		अवरोध;
	हाल 0x02:
		hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		hci_dev_set_flag(hdev, HCI_SC_ONLY);
		अवरोध;
	पूर्ण

	send_settings_rsp(cmd->sk, MGMT_OP_SET_SECURE_CONN, hdev);
	new_settings(hdev, cmd->sk);

हटाओ:
	mgmt_pending_हटाओ(cmd);
unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक set_secure_conn(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	u8 val;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_sc_capable(hdev) &&
	    !hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
	    lmp_sc_capable(hdev) &&
	    !hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				       MGMT_STATUS_REJECTED);

	अगर (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				  MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev) || !lmp_sc_capable(hdev) ||
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		bool changed;

		अगर (cp->val) अणु
			changed = !hci_dev_test_and_set_flag(hdev,
							     HCI_SC_ENABLED);
			अगर (cp->val == 0x02)
				hci_dev_set_flag(hdev, HCI_SC_ONLY);
			अन्यथा
				hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		पूर्ण अन्यथा अणु
			changed = hci_dev_test_and_clear_flag(hdev,
							      HCI_SC_ENABLED);
			hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		पूर्ण

		err = send_settings_rsp(sk, MGMT_OP_SET_SECURE_CONN, hdev);
		अगर (err < 0)
			जाओ failed;

		अगर (changed)
			err = new_settings(hdev, sk);

		जाओ failed;
	पूर्ण

	अगर (pending_find(MGMT_OP_SET_SECURE_CONN, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				      MGMT_STATUS_BUSY);
		जाओ failed;
	पूर्ण

	val = !!cp->val;

	अगर (val == hci_dev_test_flag(hdev, HCI_SC_ENABLED) &&
	    (cp->val == 0x02) == hci_dev_test_flag(hdev, HCI_SC_ONLY)) अणु
		err = send_settings_rsp(sk, MGMT_OP_SET_SECURE_CONN, hdev);
		जाओ failed;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_SECURE_CONN, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_WRITE_SC_SUPPORT, 1, &val);
	err = hci_req_run(&req, sc_enable_complete);
	अगर (err < 0) अणु
		mgmt_pending_हटाओ(cmd);
		जाओ failed;
	पूर्ण

failed:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_debug_keys(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			  व्योम *data, u16 len)
अणु
	काष्ठा mgmt_mode *cp = data;
	bool changed, use_changed;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEBUG_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (cp->val)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_KEEP_DEBUG_KEYS);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev,
						      HCI_KEEP_DEBUG_KEYS);

	अगर (cp->val == 0x02)
		use_changed = !hci_dev_test_and_set_flag(hdev,
							 HCI_USE_DEBUG_KEYS);
	अन्यथा
		use_changed = hci_dev_test_and_clear_flag(hdev,
							  HCI_USE_DEBUG_KEYS);

	अगर (hdev_is_घातered(hdev) && use_changed &&
	    hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
		u8 mode = (cp->val == 0x02) ? 0x01 : 0x00;
		hci_send_cmd(hdev, HCI_OP_WRITE_SSP_DEBUG_MODE,
			     माप(mode), &mode);
	पूर्ण

	err = send_settings_rsp(sk, MGMT_OP_SET_DEBUG_KEYS, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_privacy(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *cp_data,
		       u16 len)
अणु
	काष्ठा mgmt_cp_set_privacy *cp = cp_data;
	bool changed;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PRIVACY,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->privacy != 0x00 && cp->privacy != 0x01 && cp->privacy != 0x02)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PRIVACY,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (hdev_is_घातered(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PRIVACY,
				       MGMT_STATUS_REJECTED);

	hci_dev_lock(hdev);

	/* If user space supports this command it is also expected to
	 * handle IRKs. Thereक्रमe, set the HCI_RPA_RESOLVING flag.
	 */
	hci_dev_set_flag(hdev, HCI_RPA_RESOLVING);

	अगर (cp->privacy) अणु
		changed = !hci_dev_test_and_set_flag(hdev, HCI_PRIVACY);
		स_नकल(hdev->irk, cp->irk, माप(hdev->irk));
		hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);
		hci_adv_instances_set_rpa_expired(hdev, true);
		अगर (cp->privacy == 0x02)
			hci_dev_set_flag(hdev, HCI_LIMITED_PRIVACY);
		अन्यथा
			hci_dev_clear_flag(hdev, HCI_LIMITED_PRIVACY);
	पूर्ण अन्यथा अणु
		changed = hci_dev_test_and_clear_flag(hdev, HCI_PRIVACY);
		स_रखो(hdev->irk, 0, माप(hdev->irk));
		hci_dev_clear_flag(hdev, HCI_RPA_EXPIRED);
		hci_adv_instances_set_rpa_expired(hdev, false);
		hci_dev_clear_flag(hdev, HCI_LIMITED_PRIVACY);
	पूर्ण

	err = send_settings_rsp(sk, MGMT_OP_SET_PRIVACY, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल bool irk_is_valid(काष्ठा mgmt_irk_info *irk)
अणु
	चयन (irk->addr.type) अणु
	हाल BDADDR_LE_PUBLIC:
		वापस true;

	हाल BDADDR_LE_RANDOM:
		/* Two most signअगरicant bits shall be set */
		अगर ((irk->addr.bdaddr.b[5] & 0xc0) != 0xc0)
			वापस false;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक load_irks(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *cp_data,
		     u16 len)
अणु
	काष्ठा mgmt_cp_load_irks *cp = cp_data;
	स्थिर u16 max_irk_count = ((U16_MAX - माप(*cp)) /
				   माप(काष्ठा mgmt_irk_info));
	u16 irk_count, expected_len;
	पूर्णांक i, err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_IRKS,
				       MGMT_STATUS_NOT_SUPPORTED);

	irk_count = __le16_to_cpu(cp->irk_count);
	अगर (irk_count > max_irk_count) अणु
		bt_dev_err(hdev, "load_irks: too big irk_count value %u",
			   irk_count);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_IRKS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	expected_len = काष्ठा_size(cp, irks, irk_count);
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "load_irks: expected %u bytes, got %u bytes",
			   expected_len, len);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_IRKS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	bt_dev_dbg(hdev, "irk_count %u", irk_count);

	क्रम (i = 0; i < irk_count; i++) अणु
		काष्ठा mgmt_irk_info *key = &cp->irks[i];

		अगर (!irk_is_valid(key))
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_LOAD_IRKS,
					       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	hci_dev_lock(hdev);

	hci_smp_irks_clear(hdev);

	क्रम (i = 0; i < irk_count; i++) अणु
		काष्ठा mgmt_irk_info *irk = &cp->irks[i];

		अगर (hci_is_blocked_key(hdev,
				       HCI_BLOCKED_KEY_TYPE_IRK,
				       irk->val)) अणु
			bt_dev_warn(hdev, "Skipping blocked IRK for %pMR",
				    &irk->addr.bdaddr);
			जारी;
		पूर्ण

		hci_add_irk(hdev, &irk->addr.bdaddr,
			    le_addr_type(irk->addr.type), irk->val,
			    BDADDR_ANY);
	पूर्ण

	hci_dev_set_flag(hdev, HCI_RPA_RESOLVING);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_LOAD_IRKS, 0, शून्य, 0);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल bool ltk_is_valid(काष्ठा mgmt_ltk_info *key)
अणु
	अगर (key->master != 0x00 && key->master != 0x01)
		वापस false;

	चयन (key->addr.type) अणु
	हाल BDADDR_LE_PUBLIC:
		वापस true;

	हाल BDADDR_LE_RANDOM:
		/* Two most signअगरicant bits shall be set */
		अगर ((key->addr.bdaddr.b[5] & 0xc0) != 0xc0)
			वापस false;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक load_दीर्घ_term_keys(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *cp_data, u16 len)
अणु
	काष्ठा mgmt_cp_load_दीर्घ_term_keys *cp = cp_data;
	स्थिर u16 max_key_count = ((U16_MAX - माप(*cp)) /
				   माप(काष्ठा mgmt_ltk_info));
	u16 key_count, expected_len;
	पूर्णांक i, err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LONG_TERM_KEYS,
				       MGMT_STATUS_NOT_SUPPORTED);

	key_count = __le16_to_cpu(cp->key_count);
	अगर (key_count > max_key_count) अणु
		bt_dev_err(hdev, "load_ltks: too big key_count value %u",
			   key_count);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LONG_TERM_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	expected_len = काष्ठा_size(cp, keys, key_count);
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "load_keys: expected %u bytes, got %u bytes",
			   expected_len, len);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_LONG_TERM_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	bt_dev_dbg(hdev, "key_count %u", key_count);

	क्रम (i = 0; i < key_count; i++) अणु
		काष्ठा mgmt_ltk_info *key = &cp->keys[i];

		अगर (!ltk_is_valid(key))
			वापस mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_LOAD_LONG_TERM_KEYS,
					       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	hci_dev_lock(hdev);

	hci_smp_ltks_clear(hdev);

	क्रम (i = 0; i < key_count; i++) अणु
		काष्ठा mgmt_ltk_info *key = &cp->keys[i];
		u8 type, authenticated;

		अगर (hci_is_blocked_key(hdev,
				       HCI_BLOCKED_KEY_TYPE_LTK,
				       key->val)) अणु
			bt_dev_warn(hdev, "Skipping blocked LTK for %pMR",
				    &key->addr.bdaddr);
			जारी;
		पूर्ण

		चयन (key->type) अणु
		हाल MGMT_LTK_UNAUTHENTICATED:
			authenticated = 0x00;
			type = key->master ? SMP_LTK : SMP_LTK_SLAVE;
			अवरोध;
		हाल MGMT_LTK_AUTHENTICATED:
			authenticated = 0x01;
			type = key->master ? SMP_LTK : SMP_LTK_SLAVE;
			अवरोध;
		हाल MGMT_LTK_P256_UNAUTH:
			authenticated = 0x00;
			type = SMP_LTK_P256;
			अवरोध;
		हाल MGMT_LTK_P256_AUTH:
			authenticated = 0x01;
			type = SMP_LTK_P256;
			अवरोध;
		हाल MGMT_LTK_P256_DEBUG:
			authenticated = 0x00;
			type = SMP_LTK_P256_DEBUG;
			fallthrough;
		शेष:
			जारी;
		पूर्ण

		hci_add_ltk(hdev, &key->addr.bdaddr,
			    le_addr_type(key->addr.type), type, authenticated,
			    key->val, key->enc_size, key->eभाग, key->अक्रम);
	पूर्ण

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_LOAD_LONG_TERM_KEYS, 0,
			   शून्य, 0);

	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक conn_info_cmd_complete(काष्ठा mgmt_pending_cmd *cmd, u8 status)
अणु
	काष्ठा hci_conn *conn = cmd->user_data;
	काष्ठा mgmt_rp_get_conn_info rp;
	पूर्णांक err;

	स_नकल(&rp.addr, cmd->param, माप(rp.addr));

	अगर (status == MGMT_STATUS_SUCCESS) अणु
		rp.rssi = conn->rssi;
		rp.tx_घातer = conn->tx_घातer;
		rp.max_tx_घातer = conn->max_tx_घातer;
	पूर्ण अन्यथा अणु
		rp.rssi = HCI_RSSI_INVALID;
		rp.tx_घातer = HCI_TX_POWER_INVALID;
		rp.max_tx_घातer = HCI_TX_POWER_INVALID;
	पूर्ण

	err = mgmt_cmd_complete(cmd->sk, cmd->index, MGMT_OP_GET_CONN_INFO,
				status, &rp, माप(rp));

	hci_conn_drop(conn);
	hci_conn_put(conn);

	वापस err;
पूर्ण

अटल व्योम conn_info_refresh_complete(काष्ठा hci_dev *hdev, u8 hci_status,
				       u16 opcode)
अणु
	काष्ठा hci_cp_पढ़ो_rssi *cp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;
	u16 handle;
	u8 status;

	bt_dev_dbg(hdev, "status 0x%02x", hci_status);

	hci_dev_lock(hdev);

	/* Commands sent in request are either Read RSSI or Read Transmit Power
	 * Level so we check which one was last sent to retrieve connection
	 * handle.  Both commands have handle as first parameter so it's safe to
	 * cast data on the same command काष्ठा.
	 *
	 * First command sent is always Read RSSI and we fail only अगर it fails.
	 * In other हाल we simply override error to indicate success as we
	 * alपढ़ोy remembered अगर TX घातer value is actually valid.
	 */
	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_RSSI);
	अगर (!cp) अणु
		cp = hci_sent_cmd_data(hdev, HCI_OP_READ_TX_POWER);
		status = MGMT_STATUS_SUCCESS;
	पूर्ण अन्यथा अणु
		status = mgmt_status(hci_status);
	पूर्ण

	अगर (!cp) अणु
		bt_dev_err(hdev, "invalid sent_cmd in conn_info response");
		जाओ unlock;
	पूर्ण

	handle = __le16_to_cpu(cp->handle);
	conn = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (!conn) अणु
		bt_dev_err(hdev, "unknown handle (%d) in conn_info response",
			   handle);
		जाओ unlock;
	पूर्ण

	cmd = pending_find_data(MGMT_OP_GET_CONN_INFO, hdev, conn);
	अगर (!cmd)
		जाओ unlock;

	cmd->cmd_complete(cmd, status);
	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक get_conn_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 len)
अणु
	काष्ठा mgmt_cp_get_conn_info *cp = data;
	काष्ठा mgmt_rp_get_conn_info rp;
	काष्ठा hci_conn *conn;
	अचिन्हित दीर्घ conn_info_age;
	पूर्णांक err = 0;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&rp, 0, माप(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	अगर (!bdaddr_type_is_valid(cp->addr.type))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONN_INFO,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONN_INFO,
					MGMT_STATUS_NOT_POWERED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (cp->addr.type == BDADDR_BREDR)
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
					       &cp->addr.bdaddr);
	अन्यथा
		conn = hci_conn_hash_lookup_ba(hdev, LE_LINK, &cp->addr.bdaddr);

	अगर (!conn || conn->state != BT_CONNECTED) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONN_INFO,
					MGMT_STATUS_NOT_CONNECTED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (pending_find_data(MGMT_OP_GET_CONN_INFO, hdev, conn)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONN_INFO,
					MGMT_STATUS_BUSY, &rp, माप(rp));
		जाओ unlock;
	पूर्ण

	/* To aव्योम client trying to guess when to poll again क्रम inक्रमmation we
	 * calculate conn info age as अक्रमom value between min/max set in hdev.
	 */
	conn_info_age = hdev->conn_info_min_age +
			pअक्रमom_u32_max(hdev->conn_info_max_age -
					hdev->conn_info_min_age);

	/* Query controller to refresh cached values अगर they are too old or were
	 * never पढ़ो.
	 */
	अगर (समय_after(jअगरfies, conn->conn_info_बारtamp +
		       msecs_to_jअगरfies(conn_info_age)) ||
	    !conn->conn_info_बारtamp) अणु
		काष्ठा hci_request req;
		काष्ठा hci_cp_पढ़ो_tx_घातer req_txp_cp;
		काष्ठा hci_cp_पढ़ो_rssi req_rssi_cp;
		काष्ठा mgmt_pending_cmd *cmd;

		hci_req_init(&req, hdev);
		req_rssi_cp.handle = cpu_to_le16(conn->handle);
		hci_req_add(&req, HCI_OP_READ_RSSI, माप(req_rssi_cp),
			    &req_rssi_cp);

		/* For LE links TX घातer करोes not change thus we करोn't need to
		 * query क्रम it once value is known.
		 */
		अगर (!bdaddr_type_is_le(cp->addr.type) ||
		    conn->tx_घातer == HCI_TX_POWER_INVALID) अणु
			req_txp_cp.handle = cpu_to_le16(conn->handle);
			req_txp_cp.type = 0x00;
			hci_req_add(&req, HCI_OP_READ_TX_POWER,
				    माप(req_txp_cp), &req_txp_cp);
		पूर्ण

		/* Max TX घातer needs to be पढ़ो only once per connection */
		अगर (conn->max_tx_घातer == HCI_TX_POWER_INVALID) अणु
			req_txp_cp.handle = cpu_to_le16(conn->handle);
			req_txp_cp.type = 0x01;
			hci_req_add(&req, HCI_OP_READ_TX_POWER,
				    माप(req_txp_cp), &req_txp_cp);
		पूर्ण

		err = hci_req_run(&req, conn_info_refresh_complete);
		अगर (err < 0)
			जाओ unlock;

		cmd = mgmt_pending_add(sk, MGMT_OP_GET_CONN_INFO, hdev,
				       data, len);
		अगर (!cmd) अणु
			err = -ENOMEM;
			जाओ unlock;
		पूर्ण

		hci_conn_hold(conn);
		cmd->user_data = hci_conn_get(conn);
		cmd->cmd_complete = conn_info_cmd_complete;

		conn->conn_info_बारtamp = jअगरfies;
	पूर्ण अन्यथा अणु
		/* Cache is valid, just reply with values cached in hci_conn */
		rp.rssi = conn->rssi;
		rp.tx_घातer = conn->tx_घातer;
		rp.max_tx_घातer = conn->max_tx_घातer;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CONN_INFO,
					MGMT_STATUS_SUCCESS, &rp, माप(rp));
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक घड़ी_info_cmd_complete(काष्ठा mgmt_pending_cmd *cmd, u8 status)
अणु
	काष्ठा hci_conn *conn = cmd->user_data;
	काष्ठा mgmt_rp_get_घड़ी_info rp;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	स_रखो(&rp, 0, माप(rp));
	स_नकल(&rp.addr, cmd->param, माप(rp.addr));

	अगर (status)
		जाओ complete;

	hdev = hci_dev_get(cmd->index);
	अगर (hdev) अणु
		rp.local_घड़ी = cpu_to_le32(hdev->घड़ी);
		hci_dev_put(hdev);
	पूर्ण

	अगर (conn) अणु
		rp.piconet_घड़ी = cpu_to_le32(conn->घड़ी);
		rp.accuracy = cpu_to_le16(conn->घड़ी_accuracy);
	पूर्ण

complete:
	err = mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status, &rp,
				माप(rp));

	अगर (conn) अणु
		hci_conn_drop(conn);
		hci_conn_put(conn);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम get_घड़ी_info_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा hci_cp_पढ़ो_घड़ी *hci_cp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_conn *conn;

	bt_dev_dbg(hdev, "status %u", status);

	hci_dev_lock(hdev);

	hci_cp = hci_sent_cmd_data(hdev, HCI_OP_READ_CLOCK);
	अगर (!hci_cp)
		जाओ unlock;

	अगर (hci_cp->which) अणु
		u16 handle = __le16_to_cpu(hci_cp->handle);
		conn = hci_conn_hash_lookup_handle(hdev, handle);
	पूर्ण अन्यथा अणु
		conn = शून्य;
	पूर्ण

	cmd = pending_find_data(MGMT_OP_GET_CLOCK_INFO, hdev, conn);
	अगर (!cmd)
		जाओ unlock;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक get_घड़ी_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			 u16 len)
अणु
	काष्ठा mgmt_cp_get_घड़ी_info *cp = data;
	काष्ठा mgmt_rp_get_घड़ी_info rp;
	काष्ठा hci_cp_पढ़ो_घड़ी hci_cp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	काष्ठा hci_conn *conn;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	स_रखो(&rp, 0, माप(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	अगर (cp->addr.type != BDADDR_BREDR)
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CLOCK_INFO,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, माप(rp));

	hci_dev_lock(hdev);

	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CLOCK_INFO,
					MGMT_STATUS_NOT_POWERED, &rp,
					माप(rp));
		जाओ unlock;
	पूर्ण

	अगर (bacmp(&cp->addr.bdaddr, BDADDR_ANY)) अणु
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
					       &cp->addr.bdaddr);
		अगर (!conn || conn->state != BT_CONNECTED) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_GET_CLOCK_INFO,
						MGMT_STATUS_NOT_CONNECTED,
						&rp, माप(rp));
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		conn = शून्य;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_GET_CLOCK_INFO, hdev, data, len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	cmd->cmd_complete = घड़ी_info_cmd_complete;

	hci_req_init(&req, hdev);

	स_रखो(&hci_cp, 0, माप(hci_cp));
	hci_req_add(&req, HCI_OP_READ_CLOCK, माप(hci_cp), &hci_cp);

	अगर (conn) अणु
		hci_conn_hold(conn);
		cmd->user_data = hci_conn_get(conn);

		hci_cp.handle = cpu_to_le16(conn->handle);
		hci_cp.which = 0x01; /* Piconet घड़ी */
		hci_req_add(&req, HCI_OP_READ_CLOCK, माप(hci_cp), &hci_cp);
	पूर्ण

	err = hci_req_run(&req, get_घड़ी_info_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल bool is_connected(काष्ठा hci_dev *hdev, bdaddr_t *addr, u8 type)
अणु
	काष्ठा hci_conn *conn;

	conn = hci_conn_hash_lookup_ba(hdev, LE_LINK, addr);
	अगर (!conn)
		वापस false;

	अगर (conn->dst_type != type)
		वापस false;

	अगर (conn->state != BT_CONNECTED)
		वापस false;

	वापस true;
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल पूर्णांक hci_conn_params_set(काष्ठा hci_dev *hdev, bdaddr_t *addr,
			       u8 addr_type, u8 स्वतः_connect)
अणु
	काष्ठा hci_conn_params *params;

	params = hci_conn_params_add(hdev, addr, addr_type);
	अगर (!params)
		वापस -EIO;

	अगर (params->स्वतः_connect == स्वतः_connect)
		वापस 0;

	list_del_init(&params->action);

	चयन (स्वतः_connect) अणु
	हाल HCI_AUTO_CONN_DISABLED:
	हाल HCI_AUTO_CONN_LINK_LOSS:
		/* If स्वतः connect is being disabled when we're trying to
		 * connect to device, keep connecting.
		 */
		अगर (params->explicit_connect)
			list_add(&params->action, &hdev->pend_le_conns);
		अवरोध;
	हाल HCI_AUTO_CONN_REPORT:
		अगर (params->explicit_connect)
			list_add(&params->action, &hdev->pend_le_conns);
		अन्यथा
			list_add(&params->action, &hdev->pend_le_reports);
		अवरोध;
	हाल HCI_AUTO_CONN_सूचीECT:
	हाल HCI_AUTO_CONN_ALWAYS:
		अगर (!is_connected(hdev, addr, addr_type))
			list_add(&params->action, &hdev->pend_le_conns);
		अवरोध;
	पूर्ण

	params->स्वतः_connect = स्वतः_connect;

	bt_dev_dbg(hdev, "addr %pMR (type %u) auto_connect %u",
		   addr, addr_type, स्वतः_connect);

	वापस 0;
पूर्ण

अटल व्योम device_added(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			 bdaddr_t *bdaddr, u8 type, u8 action)
अणु
	काष्ठा mgmt_ev_device_added ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = type;
	ev.action = action;

	mgmt_event(MGMT_EV_DEVICE_ADDED, hdev, &ev, माप(ev), sk);
पूर्ण

अटल पूर्णांक add_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
		      व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_add_device *cp = data;
	u8 स्वतः_conn, addr_type;
	काष्ठा hci_conn_params *params;
	पूर्णांक err;
	u32 current_flags = 0;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!bdaddr_type_is_valid(cp->addr.type) ||
	    !bacmp(&cp->addr.bdaddr, BDADDR_ANY))
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, माप(cp->addr));

	अगर (cp->action != 0x00 && cp->action != 0x01 && cp->action != 0x02)
		वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, माप(cp->addr));

	hci_dev_lock(hdev);

	अगर (cp->addr.type == BDADDR_BREDR) अणु
		/* Only incoming connections action is supported क्रम now */
		अगर (cp->action != 0x01) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_ADD_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		err = hci_bdaddr_list_add_with_flags(&hdev->whitelist,
						     &cp->addr.bdaddr,
						     cp->addr.type, 0);
		अगर (err)
			जाओ unlock;

		hci_req_update_scan(hdev);

		जाओ added;
	पूर्ण

	addr_type = le_addr_type(cp->addr.type);

	अगर (cp->action == 0x02)
		स्वतः_conn = HCI_AUTO_CONN_ALWAYS;
	अन्यथा अगर (cp->action == 0x01)
		स्वतः_conn = HCI_AUTO_CONN_सूचीECT;
	अन्यथा
		स्वतः_conn = HCI_AUTO_CONN_REPORT;

	/* Kernel पूर्णांकernally uses conn_params with resolvable निजी
	 * address, but Add Device allows only identity addresses.
	 * Make sure it is enक्रमced beक्रमe calling
	 * hci_conn_params_lookup.
	 */
	अगर (!hci_is_identity_address(&cp->addr.bdaddr, addr_type)) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					MGMT_STATUS_INVALID_PARAMS,
					&cp->addr, माप(cp->addr));
		जाओ unlock;
	पूर्ण

	/* If the connection parameters करोn't exist क्रम this device,
	 * they will be created and configured with शेषs.
	 */
	अगर (hci_conn_params_set(hdev, &cp->addr.bdaddr, addr_type,
				स्वतः_conn) < 0) अणु
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					MGMT_STATUS_FAILED, &cp->addr,
					माप(cp->addr));
		जाओ unlock;
	पूर्ण अन्यथा अणु
		params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr,
						addr_type);
		अगर (params)
			current_flags = params->current_flags;
	पूर्ण

	hci_update_background_scan(hdev);

added:
	device_added(sk, hdev, &cp->addr.bdaddr, cp->addr.type, cp->action);
	device_flags_changed(शून्य, hdev, &cp->addr.bdaddr, cp->addr.type,
			     SUPPORTED_DEVICE_FLAGS(), current_flags);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
				MGMT_STATUS_SUCCESS, &cp->addr,
				माप(cp->addr));

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल व्योम device_हटाओd(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   bdaddr_t *bdaddr, u8 type)
अणु
	काष्ठा mgmt_ev_device_हटाओd ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = type;

	mgmt_event(MGMT_EV_DEVICE_REMOVED, hdev, &ev, माप(ev), sk);
पूर्ण

अटल पूर्णांक हटाओ_device(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			 व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_हटाओ_device *cp = data;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	hci_dev_lock(hdev);

	अगर (bacmp(&cp->addr.bdaddr, BDADDR_ANY)) अणु
		काष्ठा hci_conn_params *params;
		u8 addr_type;

		अगर (!bdaddr_type_is_valid(cp->addr.type)) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		अगर (cp->addr.type == BDADDR_BREDR) अणु
			err = hci_bdaddr_list_del(&hdev->whitelist,
						  &cp->addr.bdaddr,
						  cp->addr.type);
			अगर (err) अणु
				err = mgmt_cmd_complete(sk, hdev->id,
							MGMT_OP_REMOVE_DEVICE,
							MGMT_STATUS_INVALID_PARAMS,
							&cp->addr,
							माप(cp->addr));
				जाओ unlock;
			पूर्ण

			hci_req_update_scan(hdev);

			device_हटाओd(sk, hdev, &cp->addr.bdaddr,
				       cp->addr.type);
			जाओ complete;
		पूर्ण

		addr_type = le_addr_type(cp->addr.type);

		/* Kernel पूर्णांकernally uses conn_params with resolvable निजी
		 * address, but Remove Device allows only identity addresses.
		 * Make sure it is enक्रमced beक्रमe calling
		 * hci_conn_params_lookup.
		 */
		अगर (!hci_is_identity_address(&cp->addr.bdaddr, addr_type)) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		params = hci_conn_params_lookup(hdev, &cp->addr.bdaddr,
						addr_type);
		अगर (!params) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		अगर (params->स्वतः_connect == HCI_AUTO_CONN_DISABLED ||
		    params->स्वतः_connect == HCI_AUTO_CONN_EXPLICIT) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		list_del(&params->action);
		list_del(&params->list);
		kमुक्त(params);
		hci_update_background_scan(hdev);

		device_हटाओd(sk, hdev, &cp->addr.bdaddr, cp->addr.type);
	पूर्ण अन्यथा अणु
		काष्ठा hci_conn_params *p, *पंचांगp;
		काष्ठा bdaddr_list *b, *bपंचांगp;

		अगर (cp->addr.type) अणु
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_REMOVE_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, माप(cp->addr));
			जाओ unlock;
		पूर्ण

		list_क्रम_each_entry_safe(b, bपंचांगp, &hdev->whitelist, list) अणु
			device_हटाओd(sk, hdev, &b->bdaddr, b->bdaddr_type);
			list_del(&b->list);
			kमुक्त(b);
		पूर्ण

		hci_req_update_scan(hdev);

		list_क्रम_each_entry_safe(p, पंचांगp, &hdev->le_conn_params, list) अणु
			अगर (p->स्वतः_connect == HCI_AUTO_CONN_DISABLED)
				जारी;
			device_हटाओd(sk, hdev, &p->addr, p->addr_type);
			अगर (p->explicit_connect) अणु
				p->स्वतः_connect = HCI_AUTO_CONN_EXPLICIT;
				जारी;
			पूर्ण
			list_del(&p->action);
			list_del(&p->list);
			kमुक्त(p);
		पूर्ण

		bt_dev_dbg(hdev, "All LE connection parameters were removed");

		hci_update_background_scan(hdev);
	पूर्ण

complete:
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_REMOVE_DEVICE,
				MGMT_STATUS_SUCCESS, &cp->addr,
				माप(cp->addr));
unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक load_conn_param(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 len)
अणु
	काष्ठा mgmt_cp_load_conn_param *cp = data;
	स्थिर u16 max_param_count = ((U16_MAX - माप(*cp)) /
				     माप(काष्ठा mgmt_conn_param));
	u16 param_count, expected_len;
	पूर्णांक i;

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_CONN_PARAM,
				       MGMT_STATUS_NOT_SUPPORTED);

	param_count = __le16_to_cpu(cp->param_count);
	अगर (param_count > max_param_count) अणु
		bt_dev_err(hdev, "load_conn_param: too big param_count value %u",
			   param_count);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_CONN_PARAM,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	expected_len = काष्ठा_size(cp, params, param_count);
	अगर (expected_len != len) अणु
		bt_dev_err(hdev, "load_conn_param: expected %u bytes, got %u bytes",
			   expected_len, len);
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_LOAD_CONN_PARAM,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	bt_dev_dbg(hdev, "param_count %u", param_count);

	hci_dev_lock(hdev);

	hci_conn_params_clear_disabled(hdev);

	क्रम (i = 0; i < param_count; i++) अणु
		काष्ठा mgmt_conn_param *param = &cp->params[i];
		काष्ठा hci_conn_params *hci_param;
		u16 min, max, latency, समयout;
		u8 addr_type;

		bt_dev_dbg(hdev, "Adding %pMR (type %u)", &param->addr.bdaddr,
			   param->addr.type);

		अगर (param->addr.type == BDADDR_LE_PUBLIC) अणु
			addr_type = ADDR_LE_DEV_PUBLIC;
		पूर्ण अन्यथा अगर (param->addr.type == BDADDR_LE_RANDOM) अणु
			addr_type = ADDR_LE_DEV_RANDOM;
		पूर्ण अन्यथा अणु
			bt_dev_err(hdev, "ignoring invalid connection parameters");
			जारी;
		पूर्ण

		min = le16_to_cpu(param->min_पूर्णांकerval);
		max = le16_to_cpu(param->max_पूर्णांकerval);
		latency = le16_to_cpu(param->latency);
		समयout = le16_to_cpu(param->समयout);

		bt_dev_dbg(hdev, "min 0x%04x max 0x%04x latency 0x%04x timeout 0x%04x",
			   min, max, latency, समयout);

		अगर (hci_check_conn_params(min, max, latency, समयout) < 0) अणु
			bt_dev_err(hdev, "ignoring invalid connection parameters");
			जारी;
		पूर्ण

		hci_param = hci_conn_params_add(hdev, &param->addr.bdaddr,
						addr_type);
		अगर (!hci_param) अणु
			bt_dev_err(hdev, "failed to add connection parameters");
			जारी;
		पूर्ण

		hci_param->conn_min_पूर्णांकerval = min;
		hci_param->conn_max_पूर्णांकerval = max;
		hci_param->conn_latency = latency;
		hci_param->supervision_समयout = समयout;
	पूर्ण

	hci_dev_unlock(hdev);

	वापस mgmt_cmd_complete(sk, hdev->id, MGMT_OP_LOAD_CONN_PARAM, 0,
				 शून्य, 0);
पूर्ण

अटल पूर्णांक set_बाह्यal_config(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			       व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_set_बाह्यal_config *cp = data;
	bool changed;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (hdev_is_घातered(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				       MGMT_STATUS_REJECTED);

	अगर (cp->config != 0x00 && cp->config != 0x01)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				         MGMT_STATUS_INVALID_PARAMS);

	अगर (!test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	अगर (cp->config)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_EXT_CONFIGURED);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev, HCI_EXT_CONFIGURED);

	err = send_options_rsp(sk, MGMT_OP_SET_EXTERNAL_CONFIG, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (!changed)
		जाओ unlock;

	err = new_options(hdev, sk);

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED) == is_configured(hdev)) अणु
		mgmt_index_हटाओd(hdev);

		अगर (hci_dev_test_and_change_flag(hdev, HCI_UNCONFIGURED)) अणु
			hci_dev_set_flag(hdev, HCI_CONFIG);
			hci_dev_set_flag(hdev, HCI_AUTO_OFF);

			queue_work(hdev->req_workqueue, &hdev->घातer_on);
		पूर्ण अन्यथा अणु
			set_bit(HCI_RAW, &hdev->flags);
			mgmt_index_added(hdev);
		पूर्ण
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_खुला_address(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 len)
अणु
	काष्ठा mgmt_cp_set_खुला_address *cp = data;
	bool changed;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (hdev_is_घातered(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PUBLIC_ADDRESS,
				       MGMT_STATUS_REJECTED);

	अगर (!bacmp(&cp->bdaddr, BDADDR_ANY))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PUBLIC_ADDRESS,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (!hdev->set_bdaddr)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_PUBLIC_ADDRESS,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	changed = !!bacmp(&hdev->खुला_addr, &cp->bdaddr);
	bacpy(&hdev->खुला_addr, &cp->bdaddr);

	err = send_options_rsp(sk, MGMT_OP_SET_PUBLIC_ADDRESS, hdev);
	अगर (err < 0)
		जाओ unlock;

	अगर (!changed)
		जाओ unlock;

	अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED))
		err = new_options(hdev, sk);

	अगर (is_configured(hdev)) अणु
		mgmt_index_हटाओd(hdev);

		hci_dev_clear_flag(hdev, HCI_UNCONFIGURED);

		hci_dev_set_flag(hdev, HCI_CONFIG);
		hci_dev_set_flag(hdev, HCI_AUTO_OFF);

		queue_work(hdev->req_workqueue, &hdev->घातer_on);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);
	वापस err;
पूर्ण

अटल व्योम पढ़ो_local_oob_ext_data_complete(काष्ठा hci_dev *hdev, u8 status,
					     u16 opcode, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा mgmt_cp_पढ़ो_local_oob_ext_data *mgmt_cp;
	काष्ठा mgmt_rp_पढ़ो_local_oob_ext_data *mgmt_rp;
	u8 *h192, *r192, *h256, *r256;
	काष्ठा mgmt_pending_cmd *cmd;
	u16 eir_len;
	पूर्णांक err;

	bt_dev_dbg(hdev, "status %u", status);

	cmd = pending_find(MGMT_OP_READ_LOCAL_OOB_EXT_DATA, hdev);
	अगर (!cmd)
		वापस;

	mgmt_cp = cmd->param;

	अगर (status) अणु
		status = mgmt_status(status);
		eir_len = 0;

		h192 = शून्य;
		r192 = शून्य;
		h256 = शून्य;
		r256 = शून्य;
	पूर्ण अन्यथा अगर (opcode == HCI_OP_READ_LOCAL_OOB_DATA) अणु
		काष्ठा hci_rp_पढ़ो_local_oob_data *rp;

		अगर (skb->len != माप(*rp)) अणु
			status = MGMT_STATUS_FAILED;
			eir_len = 0;
		पूर्ण अन्यथा अणु
			status = MGMT_STATUS_SUCCESS;
			rp = (व्योम *)skb->data;

			eir_len = 5 + 18 + 18;
			h192 = rp->hash;
			r192 = rp->अक्रम;
			h256 = शून्य;
			r256 = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा hci_rp_पढ़ो_local_oob_ext_data *rp;

		अगर (skb->len != माप(*rp)) अणु
			status = MGMT_STATUS_FAILED;
			eir_len = 0;
		पूर्ण अन्यथा अणु
			status = MGMT_STATUS_SUCCESS;
			rp = (व्योम *)skb->data;

			अगर (hci_dev_test_flag(hdev, HCI_SC_ONLY)) अणु
				eir_len = 5 + 18 + 18;
				h192 = शून्य;
				r192 = शून्य;
			पूर्ण अन्यथा अणु
				eir_len = 5 + 18 + 18 + 18 + 18;
				h192 = rp->hash192;
				r192 = rp->अक्रम192;
			पूर्ण

			h256 = rp->hash256;
			r256 = rp->अक्रम256;
		पूर्ण
	पूर्ण

	mgmt_rp = kदो_स्मृति(माप(*mgmt_rp) + eir_len, GFP_KERNEL);
	अगर (!mgmt_rp)
		जाओ करोne;

	अगर (status)
		जाओ send_rsp;

	eir_len = eir_append_data(mgmt_rp->eir, 0, EIR_CLASS_OF_DEV,
				  hdev->dev_class, 3);

	अगर (h192 && r192) अणु
		eir_len = eir_append_data(mgmt_rp->eir, eir_len,
					  EIR_SSP_HASH_C192, h192, 16);
		eir_len = eir_append_data(mgmt_rp->eir, eir_len,
					  EIR_SSP_RAND_R192, r192, 16);
	पूर्ण

	अगर (h256 && r256) अणु
		eir_len = eir_append_data(mgmt_rp->eir, eir_len,
					  EIR_SSP_HASH_C256, h256, 16);
		eir_len = eir_append_data(mgmt_rp->eir, eir_len,
					  EIR_SSP_RAND_R256, r256, 16);
	पूर्ण

send_rsp:
	mgmt_rp->type = mgmt_cp->type;
	mgmt_rp->eir_len = cpu_to_le16(eir_len);

	err = mgmt_cmd_complete(cmd->sk, hdev->id,
				MGMT_OP_READ_LOCAL_OOB_EXT_DATA, status,
				mgmt_rp, माप(*mgmt_rp) + eir_len);
	अगर (err < 0 || status)
		जाओ करोne;

	hci_sock_set_flag(cmd->sk, HCI_MGMT_OOB_DATA_EVENTS);

	err = mgmt_limited_event(MGMT_EV_LOCAL_OOB_DATA_UPDATED, hdev,
				 mgmt_rp, माप(*mgmt_rp) + eir_len,
				 HCI_MGMT_OOB_DATA_EVENTS, cmd->sk);
करोne:
	kमुक्त(mgmt_rp);
	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल पूर्णांक पढ़ो_local_ssp_oob_req(काष्ठा hci_dev *hdev, काष्ठा sock *sk,
				  काष्ठा mgmt_cp_पढ़ो_local_oob_ext_data *cp)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	cmd = mgmt_pending_add(sk, MGMT_OP_READ_LOCAL_OOB_EXT_DATA, hdev,
			       cp, माप(*cp));
	अगर (!cmd)
		वापस -ENOMEM;

	hci_req_init(&req, hdev);

	अगर (bredr_sc_enabled(hdev))
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_EXT_DATA, 0, शून्य);
	अन्यथा
		hci_req_add(&req, HCI_OP_READ_LOCAL_OOB_DATA, 0, शून्य);

	err = hci_req_run_skb(&req, पढ़ो_local_oob_ext_data_complete);
	अगर (err < 0) अणु
		mgmt_pending_हटाओ(cmd);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_local_oob_ext_data(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
				   व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_पढ़ो_local_oob_ext_data *cp = data;
	काष्ठा mgmt_rp_पढ़ो_local_oob_ext_data *rp;
	माप_प्रकार rp_len;
	u16 eir_len;
	u8 status, flags, role, addr[7], hash[16], अक्रम[16];
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (hdev_is_घातered(hdev)) अणु
		चयन (cp->type) अणु
		हाल BIT(BDADDR_BREDR):
			status = mgmt_bredr_support(hdev);
			अगर (status)
				eir_len = 0;
			अन्यथा
				eir_len = 5;
			अवरोध;
		हाल (BIT(BDADDR_LE_PUBLIC) | BIT(BDADDR_LE_RANDOM)):
			status = mgmt_le_support(hdev);
			अगर (status)
				eir_len = 0;
			अन्यथा
				eir_len = 9 + 3 + 18 + 18 + 3;
			अवरोध;
		शेष:
			status = MGMT_STATUS_INVALID_PARAMS;
			eir_len = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = MGMT_STATUS_NOT_POWERED;
		eir_len = 0;
	पूर्ण

	rp_len = माप(*rp) + eir_len;
	rp = kदो_स्मृति(rp_len, GFP_ATOMIC);
	अगर (!rp)
		वापस -ENOMEM;

	अगर (status)
		जाओ complete;

	hci_dev_lock(hdev);

	eir_len = 0;
	चयन (cp->type) अणु
	हाल BIT(BDADDR_BREDR):
		अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
			err = पढ़ो_local_ssp_oob_req(hdev, sk, cp);
			hci_dev_unlock(hdev);
			अगर (!err)
				जाओ करोne;

			status = MGMT_STATUS_FAILED;
			जाओ complete;
		पूर्ण अन्यथा अणु
			eir_len = eir_append_data(rp->eir, eir_len,
						  EIR_CLASS_OF_DEV,
						  hdev->dev_class, 3);
		पूर्ण
		अवरोध;
	हाल (BIT(BDADDR_LE_PUBLIC) | BIT(BDADDR_LE_RANDOM)):
		अगर (hci_dev_test_flag(hdev, HCI_SC_ENABLED) &&
		    smp_generate_oob(hdev, hash, अक्रम) < 0) अणु
			hci_dev_unlock(hdev);
			status = MGMT_STATUS_FAILED;
			जाओ complete;
		पूर्ण

		/* This should वापस the active RPA, but since the RPA
		 * is only programmed on demand, it is really hard to fill
		 * this in at the moment. For now disallow retrieving
		 * local out-of-band data when privacy is in use.
		 *
		 * Returning the identity address will not help here since
		 * pairing happens beक्रमe the identity resolving key is
		 * known and thus the connection establishment happens
		 * based on the RPA and not the identity address.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_PRIVACY)) अणु
			hci_dev_unlock(hdev);
			status = MGMT_STATUS_REJECTED;
			जाओ complete;
		पूर्ण

		अगर (hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ||
		   !bacmp(&hdev->bdaddr, BDADDR_ANY) ||
		   (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
		    bacmp(&hdev->अटल_addr, BDADDR_ANY))) अणु
			स_नकल(addr, &hdev->अटल_addr, 6);
			addr[6] = 0x01;
		पूर्ण अन्यथा अणु
			स_नकल(addr, &hdev->bdaddr, 6);
			addr[6] = 0x00;
		पूर्ण

		eir_len = eir_append_data(rp->eir, eir_len, EIR_LE_BDADDR,
					  addr, माप(addr));

		अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING))
			role = 0x02;
		अन्यथा
			role = 0x01;

		eir_len = eir_append_data(rp->eir, eir_len, EIR_LE_ROLE,
					  &role, माप(role));

		अगर (hci_dev_test_flag(hdev, HCI_SC_ENABLED)) अणु
			eir_len = eir_append_data(rp->eir, eir_len,
						  EIR_LE_SC_CONFIRM,
						  hash, माप(hash));

			eir_len = eir_append_data(rp->eir, eir_len,
						  EIR_LE_SC_RANDOM,
						  अक्रम, माप(अक्रम));
		पूर्ण

		flags = mgmt_get_adv_discov_flags(hdev);

		अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
			flags |= LE_AD_NO_BREDR;

		eir_len = eir_append_data(rp->eir, eir_len, EIR_FLAGS,
					  &flags, माप(flags));
		अवरोध;
	पूर्ण

	hci_dev_unlock(hdev);

	hci_sock_set_flag(sk, HCI_MGMT_OOB_DATA_EVENTS);

	status = MGMT_STATUS_SUCCESS;

complete:
	rp->type = cp->type;
	rp->eir_len = cpu_to_le16(eir_len);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_LOCAL_OOB_EXT_DATA,
				status, rp, माप(*rp) + eir_len);
	अगर (err < 0 || status)
		जाओ करोne;

	err = mgmt_limited_event(MGMT_EV_LOCAL_OOB_DATA_UPDATED, hdev,
				 rp, माप(*rp) + eir_len,
				 HCI_MGMT_OOB_DATA_EVENTS, sk);

करोne:
	kमुक्त(rp);

	वापस err;
पूर्ण

अटल u32 get_supported_adv_flags(काष्ठा hci_dev *hdev)
अणु
	u32 flags = 0;

	flags |= MGMT_ADV_FLAG_CONNECTABLE;
	flags |= MGMT_ADV_FLAG_DISCOV;
	flags |= MGMT_ADV_FLAG_LIMITED_DISCOV;
	flags |= MGMT_ADV_FLAG_MANAGED_FLAGS;
	flags |= MGMT_ADV_FLAG_APPEARANCE;
	flags |= MGMT_ADV_FLAG_LOCAL_NAME;
	flags |= MGMT_ADV_PARAM_DURATION;
	flags |= MGMT_ADV_PARAM_TIMEOUT;
	flags |= MGMT_ADV_PARAM_INTERVALS;
	flags |= MGMT_ADV_PARAM_TX_POWER;
	flags |= MGMT_ADV_PARAM_SCAN_RSP;

	/* In extended adv TX_POWER वापसed from Set Adv Param
	 * will be always valid.
	 */
	अगर ((hdev->adv_tx_घातer != HCI_TX_POWER_INVALID) ||
	    ext_adv_capable(hdev))
		flags |= MGMT_ADV_FLAG_TX_POWER;

	अगर (ext_adv_capable(hdev)) अणु
		flags |= MGMT_ADV_FLAG_SEC_1M;
		flags |= MGMT_ADV_FLAG_HW_OFFLOAD;
		flags |= MGMT_ADV_FLAG_CAN_SET_TX_POWER;

		अगर (hdev->le_features[1] & HCI_LE_PHY_2M)
			flags |= MGMT_ADV_FLAG_SEC_2M;

		अगर (hdev->le_features[1] & HCI_LE_PHY_CODED)
			flags |= MGMT_ADV_FLAG_SEC_CODED;
	पूर्ण

	वापस flags;
पूर्ण

अटल पूर्णांक पढ़ो_adv_features(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			     व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_rp_पढ़ो_adv_features *rp;
	माप_प्रकार rp_len;
	पूर्णांक err;
	काष्ठा adv_info *adv_instance;
	u32 supported_flags;
	u8 *instance;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_READ_ADV_FEATURES,
				       MGMT_STATUS_REJECTED);

	/* Enabling the experimental LL Privay support disables support क्रम
	 * advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_READ_ADV_FEATURES,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	rp_len = माप(*rp) + hdev->adv_instance_cnt;
	rp = kदो_स्मृति(rp_len, GFP_ATOMIC);
	अगर (!rp) अणु
		hci_dev_unlock(hdev);
		वापस -ENOMEM;
	पूर्ण

	supported_flags = get_supported_adv_flags(hdev);

	rp->supported_flags = cpu_to_le32(supported_flags);
	rp->max_adv_data_len = HCI_MAX_AD_LENGTH;
	rp->max_scan_rsp_len = HCI_MAX_AD_LENGTH;
	rp->max_instances = hdev->le_num_of_adv_sets;
	rp->num_instances = hdev->adv_instance_cnt;

	instance = rp->instance;
	list_क्रम_each_entry(adv_instance, &hdev->adv_instances, list) अणु
		*instance = adv_instance->instance;
		instance++;
	पूर्ण

	hci_dev_unlock(hdev);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_READ_ADV_FEATURES,
				MGMT_STATUS_SUCCESS, rp, rp_len);

	kमुक्त(rp);

	वापस err;
पूर्ण

अटल u8 calculate_name_len(काष्ठा hci_dev *hdev)
अणु
	u8 buf[HCI_MAX_SHORT_NAME_LENGTH + 3];

	वापस append_local_name(hdev, buf, 0);
पूर्ण

अटल u8 tlv_data_max_len(काष्ठा hci_dev *hdev, u32 adv_flags,
			   bool is_adv_data)
अणु
	u8 max_len = HCI_MAX_AD_LENGTH;

	अगर (is_adv_data) अणु
		अगर (adv_flags & (MGMT_ADV_FLAG_DISCOV |
				 MGMT_ADV_FLAG_LIMITED_DISCOV |
				 MGMT_ADV_FLAG_MANAGED_FLAGS))
			max_len -= 3;

		अगर (adv_flags & MGMT_ADV_FLAG_TX_POWER)
			max_len -= 3;
	पूर्ण अन्यथा अणु
		अगर (adv_flags & MGMT_ADV_FLAG_LOCAL_NAME)
			max_len -= calculate_name_len(hdev);

		अगर (adv_flags & (MGMT_ADV_FLAG_APPEARANCE))
			max_len -= 4;
	पूर्ण

	वापस max_len;
पूर्ण

अटल bool flags_managed(u32 adv_flags)
अणु
	वापस adv_flags & (MGMT_ADV_FLAG_DISCOV |
			    MGMT_ADV_FLAG_LIMITED_DISCOV |
			    MGMT_ADV_FLAG_MANAGED_FLAGS);
पूर्ण

अटल bool tx_घातer_managed(u32 adv_flags)
अणु
	वापस adv_flags & MGMT_ADV_FLAG_TX_POWER;
पूर्ण

अटल bool name_managed(u32 adv_flags)
अणु
	वापस adv_flags & MGMT_ADV_FLAG_LOCAL_NAME;
पूर्ण

अटल bool appearance_managed(u32 adv_flags)
अणु
	वापस adv_flags & MGMT_ADV_FLAG_APPEARANCE;
पूर्ण

अटल bool tlv_data_is_valid(काष्ठा hci_dev *hdev, u32 adv_flags, u8 *data,
			      u8 len, bool is_adv_data)
अणु
	पूर्णांक i, cur_len;
	u8 max_len;

	max_len = tlv_data_max_len(hdev, adv_flags, is_adv_data);

	अगर (len > max_len)
		वापस false;

	/* Make sure that the data is correctly क्रमmatted. */
	क्रम (i = 0, cur_len = 0; i < len; i += (cur_len + 1)) अणु
		cur_len = data[i];

		अगर (data[i + 1] == EIR_FLAGS &&
		    (!is_adv_data || flags_managed(adv_flags)))
			वापस false;

		अगर (data[i + 1] == EIR_TX_POWER && tx_घातer_managed(adv_flags))
			वापस false;

		अगर (data[i + 1] == EIR_NAME_COMPLETE && name_managed(adv_flags))
			वापस false;

		अगर (data[i + 1] == EIR_NAME_SHORT && name_managed(adv_flags))
			वापस false;

		अगर (data[i + 1] == EIR_APPEARANCE &&
		    appearance_managed(adv_flags))
			वापस false;

		/* If the current field length would exceed the total data
		 * length, then it's invalid.
		 */
		अगर (i + cur_len >= len)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool requested_adv_flags_are_valid(काष्ठा hci_dev *hdev, u32 adv_flags)
अणु
	u32 supported_flags, phy_flags;

	/* The current implementation only supports a subset of the specअगरied
	 * flags. Also need to check mutual exclusiveness of sec flags.
	 */
	supported_flags = get_supported_adv_flags(hdev);
	phy_flags = adv_flags & MGMT_ADV_FLAG_SEC_MASK;
	अगर (adv_flags & ~supported_flags ||
	    ((phy_flags && (phy_flags ^ (phy_flags & -phy_flags)))))
		वापस false;

	वापस true;
पूर्ण

अटल bool adv_busy(काष्ठा hci_dev *hdev)
अणु
	वापस (pending_find(MGMT_OP_ADD_ADVERTISING, hdev) ||
		pending_find(MGMT_OP_REMOVE_ADVERTISING, hdev) ||
		pending_find(MGMT_OP_SET_LE, hdev) ||
		pending_find(MGMT_OP_ADD_EXT_ADV_PARAMS, hdev) ||
		pending_find(MGMT_OP_ADD_EXT_ADV_DATA, hdev));
पूर्ण

अटल व्योम add_advertising_complete(काष्ठा hci_dev *hdev, u8 status,
				     u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा mgmt_cp_add_advertising *cp;
	काष्ठा mgmt_rp_add_advertising rp;
	काष्ठा adv_info *adv_instance, *n;
	u8 instance;

	bt_dev_dbg(hdev, "status %d", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_ADD_ADVERTISING, hdev);
	अगर (!cmd)
		cmd = pending_find(MGMT_OP_ADD_EXT_ADV_DATA, hdev);

	list_क्रम_each_entry_safe(adv_instance, n, &hdev->adv_instances, list) अणु
		अगर (!adv_instance->pending)
			जारी;

		अगर (!status) अणु
			adv_instance->pending = false;
			जारी;
		पूर्ण

		instance = adv_instance->instance;

		अगर (hdev->cur_adv_instance == instance)
			cancel_adv_समयout(hdev);

		hci_हटाओ_adv_instance(hdev, instance);
		mgmt_advertising_हटाओd(cmd ? cmd->sk : शून्य, hdev, instance);
	पूर्ण

	अगर (!cmd)
		जाओ unlock;

	cp = cmd->param;
	rp.instance = cp->instance;

	अगर (status)
		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode,
				mgmt_status(status));
	अन्यथा
		mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
				  mgmt_status(status), &rp, माप(rp));

	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक add_advertising(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			   व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_add_advertising *cp = data;
	काष्ठा mgmt_rp_add_advertising rp;
	u32 flags;
	u8 status;
	u16 समयout, duration;
	अचिन्हित पूर्णांक prev_instance_cnt = hdev->adv_instance_cnt;
	u8 schedule_instance = 0;
	काष्ठा adv_info *next_instance;
	पूर्णांक err;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;

	bt_dev_dbg(hdev, "sock %p", sk);

	status = mgmt_le_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				       status);

	/* Enabling the experimental LL Privay support disables support क्रम
	 * advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       MGMT_STATUS_NOT_SUPPORTED);

	अगर (cp->instance < 1 || cp->instance > hdev->le_num_of_adv_sets)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				       MGMT_STATUS_INVALID_PARAMS);

	अगर (data_len != माप(*cp) + cp->adv_data_len + cp->scan_rsp_len)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				       MGMT_STATUS_INVALID_PARAMS);

	flags = __le32_to_cpu(cp->flags);
	समयout = __le16_to_cpu(cp->समयout);
	duration = __le16_to_cpu(cp->duration);

	अगर (!requested_adv_flags_are_valid(hdev, flags))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	अगर (समयout && !hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				      MGMT_STATUS_REJECTED);
		जाओ unlock;
	पूर्ण

	अगर (adv_busy(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (!tlv_data_is_valid(hdev, flags, cp->data, cp->adv_data_len, true) ||
	    !tlv_data_is_valid(hdev, flags, cp->data + cp->adv_data_len,
			       cp->scan_rsp_len, false)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	err = hci_add_adv_instance(hdev, cp->instance, flags,
				   cp->adv_data_len, cp->data,
				   cp->scan_rsp_len,
				   cp->data + cp->adv_data_len,
				   समयout, duration,
				   HCI_ADV_TX_POWER_NO_PREFERENCE,
				   hdev->le_adv_min_पूर्णांकerval,
				   hdev->le_adv_max_पूर्णांकerval);
	अगर (err < 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				      MGMT_STATUS_FAILED);
		जाओ unlock;
	पूर्ण

	/* Only trigger an advertising added event अगर a new instance was
	 * actually added.
	 */
	अगर (hdev->adv_instance_cnt > prev_instance_cnt)
		mgmt_advertising_added(sk, hdev, cp->instance);

	अगर (hdev->cur_adv_instance == cp->instance) अणु
		/* If the currently advertised instance is being changed then
		 * cancel the current advertising and schedule the next
		 * instance. If there is only one instance then the overridden
		 * advertising data will be visible right away.
		 */
		cancel_adv_समयout(hdev);

		next_instance = hci_get_next_instance(hdev, cp->instance);
		अगर (next_instance)
			schedule_instance = next_instance->instance;
	पूर्ण अन्यथा अगर (!hdev->adv_instance_समयout) अणु
		/* Immediately advertise the new instance अगर no other
		 * instance is currently being advertised.
		 */
		schedule_instance = cp->instance;
	पूर्ण

	/* If the HCI_ADVERTISING flag is set or the device isn't घातered or
	 * there is no instance to be advertised then we have no HCI
	 * communication to make. Simply वापस.
	 */
	अगर (!hdev_is_घातered(hdev) ||
	    hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    !schedule_instance) अणु
		rp.instance = cp->instance;
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
					MGMT_STATUS_SUCCESS, &rp, माप(rp));
		जाओ unlock;
	पूर्ण

	/* We're good to go, update advertising data, parameters, and start
	 * advertising.
	 */
	cmd = mgmt_pending_add(sk, MGMT_OP_ADD_ADVERTISING, hdev, data,
			       data_len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	err = __hci_req_schedule_adv_instance(&req, schedule_instance, true);

	अगर (!err)
		err = hci_req_run(&req, add_advertising_complete);

	अगर (err < 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				      MGMT_STATUS_FAILED);
		mgmt_pending_हटाओ(cmd);
	पूर्ण

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल व्योम add_ext_adv_params_complete(काष्ठा hci_dev *hdev, u8 status,
					u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा mgmt_cp_add_ext_adv_params *cp;
	काष्ठा mgmt_rp_add_ext_adv_params rp;
	काष्ठा adv_info *adv_instance;
	u32 flags;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_ADD_EXT_ADV_PARAMS, hdev);
	अगर (!cmd)
		जाओ unlock;

	cp = cmd->param;
	adv_instance = hci_find_adv_instance(hdev, cp->instance);
	अगर (!adv_instance)
		जाओ unlock;

	rp.instance = cp->instance;
	rp.tx_घातer = adv_instance->tx_घातer;

	/* While we're at it, inक्रमm userspace of the available space क्रम this
	 * advertisement, given the flags that will be used.
	 */
	flags = __le32_to_cpu(cp->flags);
	rp.max_adv_data_len = tlv_data_max_len(hdev, flags, true);
	rp.max_scan_rsp_len = tlv_data_max_len(hdev, flags, false);

	अगर (status) अणु
		/* If this advertisement was previously advertising and we
		 * failed to update it, we संकेत that it has been हटाओd and
		 * delete its काष्ठाure
		 */
		अगर (!adv_instance->pending)
			mgmt_advertising_हटाओd(cmd->sk, hdev, cp->instance);

		hci_हटाओ_adv_instance(hdev, cp->instance);

		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode,
				mgmt_status(status));

	पूर्ण अन्यथा अणु
		mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
				  mgmt_status(status), &rp, माप(rp));
	पूर्ण

unlock:
	अगर (cmd)
		mgmt_pending_हटाओ(cmd);

	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक add_ext_adv_params(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_add_ext_adv_params *cp = data;
	काष्ठा mgmt_rp_add_ext_adv_params rp;
	काष्ठा mgmt_pending_cmd *cmd = शून्य;
	काष्ठा adv_info *adv_instance;
	काष्ठा hci_request req;
	u32 flags, min_पूर्णांकerval, max_पूर्णांकerval;
	u16 समयout, duration;
	u8 status;
	s8 tx_घातer;
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	status = mgmt_le_support(hdev);
	अगर (status)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				       status);

	अगर (cp->instance < 1 || cp->instance > hdev->le_num_of_adv_sets)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	/* The purpose of अवरोधing add_advertising पूर्णांकo two separate MGMT calls
	 * क्रम params and data is to allow more parameters to be added to this
	 * काष्ठाure in the future. For this reason, we verअगरy that we have the
	 * bare minimum काष्ठाure we know of when the पूर्णांकerface was defined. Any
	 * extra parameters we करोn't know about will be ignored in this request.
	 */
	अगर (data_len < MGMT_ADD_EXT_ADV_PARAMS_MIN_SIZE)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_ADVERTISING,
				       MGMT_STATUS_INVALID_PARAMS);

	flags = __le32_to_cpu(cp->flags);

	अगर (!requested_adv_flags_are_valid(hdev, flags))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	/* In new पूर्णांकerface, we require that we are घातered to रेजिस्टर */
	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				      MGMT_STATUS_REJECTED);
		जाओ unlock;
	पूर्ण

	अगर (adv_busy(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	/* Parse defined parameters from request, use शेषs otherwise */
	समयout = (flags & MGMT_ADV_PARAM_TIMEOUT) ?
		  __le16_to_cpu(cp->समयout) : 0;

	duration = (flags & MGMT_ADV_PARAM_DURATION) ?
		   __le16_to_cpu(cp->duration) :
		   hdev->def_multi_adv_rotation_duration;

	min_पूर्णांकerval = (flags & MGMT_ADV_PARAM_INTERVALS) ?
		       __le32_to_cpu(cp->min_पूर्णांकerval) :
		       hdev->le_adv_min_पूर्णांकerval;

	max_पूर्णांकerval = (flags & MGMT_ADV_PARAM_INTERVALS) ?
		       __le32_to_cpu(cp->max_पूर्णांकerval) :
		       hdev->le_adv_max_पूर्णांकerval;

	tx_घातer = (flags & MGMT_ADV_PARAM_TX_POWER) ?
		   cp->tx_घातer :
		   HCI_ADV_TX_POWER_NO_PREFERENCE;

	/* Create advertising instance with no advertising or response data */
	err = hci_add_adv_instance(hdev, cp->instance, flags,
				   0, शून्य, 0, शून्य, समयout, duration,
				   tx_घातer, min_पूर्णांकerval, max_पूर्णांकerval);

	अगर (err < 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_PARAMS,
				      MGMT_STATUS_FAILED);
		जाओ unlock;
	पूर्ण

	/* Submit request क्रम advertising params अगर ext adv available */
	अगर (ext_adv_capable(hdev)) अणु
		hci_req_init(&req, hdev);
		adv_instance = hci_find_adv_instance(hdev, cp->instance);

		/* Updating parameters of an active instance will वापस a
		 * Command Disallowed error, so we must first disable the
		 * instance अगर it is active.
		 */
		अगर (!adv_instance->pending)
			__hci_req_disable_ext_adv_instance(&req, cp->instance);

		__hci_req_setup_ext_adv_instance(&req, cp->instance);

		err = hci_req_run(&req, add_ext_adv_params_complete);

		अगर (!err)
			cmd = mgmt_pending_add(sk, MGMT_OP_ADD_EXT_ADV_PARAMS,
					       hdev, data, data_len);
		अगर (!cmd) अणु
			err = -ENOMEM;
			hci_हटाओ_adv_instance(hdev, cp->instance);
			जाओ unlock;
		पूर्ण

	पूर्ण अन्यथा अणु
		rp.instance = cp->instance;
		rp.tx_घातer = HCI_ADV_TX_POWER_NO_PREFERENCE;
		rp.max_adv_data_len = tlv_data_max_len(hdev, flags, true);
		rp.max_scan_rsp_len = tlv_data_max_len(hdev, flags, false);
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_ADD_EXT_ADV_PARAMS,
					MGMT_STATUS_SUCCESS, &rp, माप(rp));
	पूर्ण

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक add_ext_adv_data(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 data_len)
अणु
	काष्ठा mgmt_cp_add_ext_adv_data *cp = data;
	काष्ठा mgmt_rp_add_ext_adv_data rp;
	u8 schedule_instance = 0;
	काष्ठा adv_info *next_instance;
	काष्ठा adv_info *adv_instance;
	पूर्णांक err = 0;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	adv_instance = hci_find_adv_instance(hdev, cp->instance);

	अगर (!adv_instance) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_DATA,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	/* In new पूर्णांकerface, we require that we are घातered to रेजिस्टर */
	अगर (!hdev_is_घातered(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_DATA,
				      MGMT_STATUS_REJECTED);
		जाओ clear_new_instance;
	पूर्ण

	अगर (adv_busy(hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_DATA,
				      MGMT_STATUS_BUSY);
		जाओ clear_new_instance;
	पूर्ण

	/* Validate new data */
	अगर (!tlv_data_is_valid(hdev, adv_instance->flags, cp->data,
			       cp->adv_data_len, true) ||
	    !tlv_data_is_valid(hdev, adv_instance->flags, cp->data +
			       cp->adv_data_len, cp->scan_rsp_len, false)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_DATA,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ clear_new_instance;
	पूर्ण

	/* Set the data in the advertising instance */
	hci_set_adv_instance_data(hdev, cp->instance, cp->adv_data_len,
				  cp->data, cp->scan_rsp_len,
				  cp->data + cp->adv_data_len);

	/* We're good to go, update advertising data, parameters, and start
	 * advertising.
	 */

	hci_req_init(&req, hdev);

	hci_req_add(&req, HCI_OP_READ_LOCAL_NAME, 0, शून्य);

	अगर (ext_adv_capable(hdev)) अणु
		__hci_req_update_adv_data(&req, cp->instance);
		__hci_req_update_scan_rsp_data(&req, cp->instance);
		__hci_req_enable_ext_advertising(&req, cp->instance);

	पूर्ण अन्यथा अणु
		/* If using software rotation, determine next instance to use */

		अगर (hdev->cur_adv_instance == cp->instance) अणु
			/* If the currently advertised instance is being changed
			 * then cancel the current advertising and schedule the
			 * next instance. If there is only one instance then the
			 * overridden advertising data will be visible right
			 * away
			 */
			cancel_adv_समयout(hdev);

			next_instance = hci_get_next_instance(hdev,
							      cp->instance);
			अगर (next_instance)
				schedule_instance = next_instance->instance;
		पूर्ण अन्यथा अगर (!hdev->adv_instance_समयout) अणु
			/* Immediately advertise the new instance अगर no other
			 * instance is currently being advertised.
			 */
			schedule_instance = cp->instance;
		पूर्ण

		/* If the HCI_ADVERTISING flag is set or there is no instance to
		 * be advertised then we have no HCI communication to make.
		 * Simply वापस.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
		    !schedule_instance) अणु
			अगर (adv_instance->pending) अणु
				mgmt_advertising_added(sk, hdev, cp->instance);
				adv_instance->pending = false;
			पूर्ण
			rp.instance = cp->instance;
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_ADD_EXT_ADV_DATA,
						MGMT_STATUS_SUCCESS, &rp,
						माप(rp));
			जाओ unlock;
		पूर्ण

		err = __hci_req_schedule_adv_instance(&req, schedule_instance,
						      true);
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_ADD_EXT_ADV_DATA, hdev, data,
			       data_len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ clear_new_instance;
	पूर्ण

	अगर (!err)
		err = hci_req_run(&req, add_advertising_complete);

	अगर (err < 0) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_EXT_ADV_DATA,
				      MGMT_STATUS_FAILED);
		mgmt_pending_हटाओ(cmd);
		जाओ clear_new_instance;
	पूर्ण

	/* We were successful in updating data, so trigger advertising_added
	 * event अगर this is an instance that wasn't previously advertising. If
	 * a failure occurs in the requests we initiated, we will हटाओ the
	 * instance again in add_advertising_complete
	 */
	अगर (adv_instance->pending)
		mgmt_advertising_added(sk, hdev, cp->instance);

	जाओ unlock;

clear_new_instance:
	hci_हटाओ_adv_instance(hdev, cp->instance);

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल व्योम हटाओ_advertising_complete(काष्ठा hci_dev *hdev, u8 status,
					u16 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा mgmt_cp_हटाओ_advertising *cp;
	काष्ठा mgmt_rp_हटाओ_advertising rp;

	bt_dev_dbg(hdev, "status %d", status);

	hci_dev_lock(hdev);

	/* A failure status here only means that we failed to disable
	 * advertising. Otherwise, the advertising instance has been हटाओd,
	 * so report success.
	 */
	cmd = pending_find(MGMT_OP_REMOVE_ADVERTISING, hdev);
	अगर (!cmd)
		जाओ unlock;

	cp = cmd->param;
	rp.instance = cp->instance;

	mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, MGMT_STATUS_SUCCESS,
			  &rp, माप(rp));
	mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक हटाओ_advertising(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_हटाओ_advertising *cp = data;
	काष्ठा mgmt_rp_हटाओ_advertising rp;
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा hci_request req;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	/* Enabling the experimental LL Privay support disables support क्रम
	 * advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_ADVERTISING,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	अगर (cp->instance && !hci_find_adv_instance(hdev, cp->instance)) अणु
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	अगर (pending_find(MGMT_OP_ADD_ADVERTISING, hdev) ||
	    pending_find(MGMT_OP_REMOVE_ADVERTISING, hdev) ||
	    pending_find(MGMT_OP_SET_LE, hdev)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_BUSY);
		जाओ unlock;
	पूर्ण

	अगर (list_empty(&hdev->adv_instances)) अणु
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_INVALID_PARAMS);
		जाओ unlock;
	पूर्ण

	hci_req_init(&req, hdev);

	/* If we use extended advertising, instance is disabled and हटाओd */
	अगर (ext_adv_capable(hdev)) अणु
		__hci_req_disable_ext_adv_instance(&req, cp->instance);
		__hci_req_हटाओ_ext_adv_instance(&req, cp->instance);
	पूर्ण

	hci_req_clear_adv_instance(hdev, sk, &req, cp->instance, true);

	अगर (list_empty(&hdev->adv_instances))
		__hci_req_disable_advertising(&req);

	/* If no HCI commands have been collected so far or the HCI_ADVERTISING
	 * flag is set or the device isn't घातered then we have no HCI
	 * communication to make. Simply वापस.
	 */
	अगर (skb_queue_empty(&req.cmd_q) ||
	    !hdev_is_घातered(hdev) ||
	    hci_dev_test_flag(hdev, HCI_ADVERTISING)) अणु
		hci_req_purge(&req);
		rp.instance = cp->instance;
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_REMOVE_ADVERTISING,
					MGMT_STATUS_SUCCESS, &rp, माप(rp));
		जाओ unlock;
	पूर्ण

	cmd = mgmt_pending_add(sk, MGMT_OP_REMOVE_ADVERTISING, hdev, data,
			       data_len);
	अगर (!cmd) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	err = hci_req_run(&req, हटाओ_advertising_complete);
	अगर (err < 0)
		mgmt_pending_हटाओ(cmd);

unlock:
	hci_dev_unlock(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक get_adv_size_info(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			     व्योम *data, u16 data_len)
अणु
	काष्ठा mgmt_cp_get_adv_size_info *cp = data;
	काष्ठा mgmt_rp_get_adv_size_info rp;
	u32 flags, supported_flags;
	पूर्णांक err;

	bt_dev_dbg(hdev, "sock %p", sk);

	अगर (!lmp_le_capable(hdev))
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_REJECTED);

	अगर (cp->instance < 1 || cp->instance > hdev->le_num_of_adv_sets)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_INVALID_PARAMS);

	flags = __le32_to_cpu(cp->flags);

	/* The current implementation only supports a subset of the specअगरied
	 * flags.
	 */
	supported_flags = get_supported_adv_flags(hdev);
	अगर (flags & ~supported_flags)
		वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				       MGMT_STATUS_INVALID_PARAMS);

	rp.instance = cp->instance;
	rp.flags = cp->flags;
	rp.max_adv_data_len = tlv_data_max_len(hdev, flags, true);
	rp.max_scan_rsp_len = tlv_data_max_len(hdev, flags, false);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_ADV_SIZE_INFO,
				MGMT_STATUS_SUCCESS, &rp, माप(rp));

	वापस err;
पूर्ण

अटल स्थिर काष्ठा hci_mgmt_handler mgmt_handlers[] = अणु
	अणु शून्य पूर्ण, /* 0x0000 (no command) */
	अणु पढ़ो_version,            MGMT_READ_VERSION_SIZE,
						HCI_MGMT_NO_HDEV |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_commands,           MGMT_READ_COMMANDS_SIZE,
						HCI_MGMT_NO_HDEV |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_index_list,         MGMT_READ_INDEX_LIST_SIZE,
						HCI_MGMT_NO_HDEV |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_controller_info,    MGMT_READ_INFO_SIZE,
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु set_घातered,             MGMT_SETTING_SIZE पूर्ण,
	अणु set_discoverable,        MGMT_SET_DISCOVERABLE_SIZE पूर्ण,
	अणु set_connectable,         MGMT_SETTING_SIZE पूर्ण,
	अणु set_fast_connectable,    MGMT_SETTING_SIZE पूर्ण,
	अणु set_bondable,            MGMT_SETTING_SIZE पूर्ण,
	अणु set_link_security,       MGMT_SETTING_SIZE पूर्ण,
	अणु set_ssp,                 MGMT_SETTING_SIZE पूर्ण,
	अणु set_hs,                  MGMT_SETTING_SIZE पूर्ण,
	अणु set_le,                  MGMT_SETTING_SIZE पूर्ण,
	अणु set_dev_class,           MGMT_SET_DEV_CLASS_SIZE पूर्ण,
	अणु set_local_name,          MGMT_SET_LOCAL_NAME_SIZE पूर्ण,
	अणु add_uuid,                MGMT_ADD_UUID_SIZE पूर्ण,
	अणु हटाओ_uuid,             MGMT_REMOVE_UUID_SIZE पूर्ण,
	अणु load_link_keys,          MGMT_LOAD_LINK_KEYS_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु load_दीर्घ_term_keys,     MGMT_LOAD_LONG_TERM_KEYS_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु disconnect,              MGMT_DISCONNECT_SIZE पूर्ण,
	अणु get_connections,         MGMT_GET_CONNECTIONS_SIZE पूर्ण,
	अणु pin_code_reply,          MGMT_PIN_CODE_REPLY_SIZE पूर्ण,
	अणु pin_code_neg_reply,      MGMT_PIN_CODE_NEG_REPLY_SIZE पूर्ण,
	अणु set_io_capability,       MGMT_SET_IO_CAPABILITY_SIZE पूर्ण,
	अणु pair_device,             MGMT_PAIR_DEVICE_SIZE पूर्ण,
	अणु cancel_pair_device,      MGMT_CANCEL_PAIR_DEVICE_SIZE पूर्ण,
	अणु unpair_device,           MGMT_UNPAIR_DEVICE_SIZE पूर्ण,
	अणु user_confirm_reply,      MGMT_USER_CONFIRM_REPLY_SIZE पूर्ण,
	अणु user_confirm_neg_reply,  MGMT_USER_CONFIRM_NEG_REPLY_SIZE पूर्ण,
	अणु user_passkey_reply,      MGMT_USER_PASSKEY_REPLY_SIZE पूर्ण,
	अणु user_passkey_neg_reply,  MGMT_USER_PASSKEY_NEG_REPLY_SIZE पूर्ण,
	अणु पढ़ो_local_oob_data,     MGMT_READ_LOCAL_OOB_DATA_SIZE पूर्ण,
	अणु add_remote_oob_data,     MGMT_ADD_REMOTE_OOB_DATA_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु हटाओ_remote_oob_data,  MGMT_REMOVE_REMOTE_OOB_DATA_SIZE पूर्ण,
	अणु start_discovery,         MGMT_START_DISCOVERY_SIZE पूर्ण,
	अणु stop_discovery,          MGMT_STOP_DISCOVERY_SIZE पूर्ण,
	अणु confirm_name,            MGMT_CONFIRM_NAME_SIZE पूर्ण,
	अणु block_device,            MGMT_BLOCK_DEVICE_SIZE पूर्ण,
	अणु unblock_device,          MGMT_UNBLOCK_DEVICE_SIZE पूर्ण,
	अणु set_device_id,           MGMT_SET_DEVICE_ID_SIZE पूर्ण,
	अणु set_advertising,         MGMT_SETTING_SIZE पूर्ण,
	अणु set_bredr,               MGMT_SETTING_SIZE पूर्ण,
	अणु set_अटल_address,      MGMT_SET_STATIC_ADDRESS_SIZE पूर्ण,
	अणु set_scan_params,         MGMT_SET_SCAN_PARAMS_SIZE पूर्ण,
	अणु set_secure_conn,         MGMT_SETTING_SIZE पूर्ण,
	अणु set_debug_keys,          MGMT_SETTING_SIZE पूर्ण,
	अणु set_privacy,             MGMT_SET_PRIVACY_SIZE पूर्ण,
	अणु load_irks,               MGMT_LOAD_IRKS_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु get_conn_info,           MGMT_GET_CONN_INFO_SIZE पूर्ण,
	अणु get_घड़ी_info,          MGMT_GET_CLOCK_INFO_SIZE पूर्ण,
	अणु add_device,              MGMT_ADD_DEVICE_SIZE पूर्ण,
	अणु हटाओ_device,           MGMT_REMOVE_DEVICE_SIZE पूर्ण,
	अणु load_conn_param,         MGMT_LOAD_CONN_PARAM_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु पढ़ो_unconf_index_list,  MGMT_READ_UNCONF_INDEX_LIST_SIZE,
						HCI_MGMT_NO_HDEV |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_config_info,        MGMT_READ_CONFIG_INFO_SIZE,
						HCI_MGMT_UNCONFIGURED |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु set_बाह्यal_config,     MGMT_SET_EXTERNAL_CONFIG_SIZE,
						HCI_MGMT_UNCONFIGURED पूर्ण,
	अणु set_खुला_address,      MGMT_SET_PUBLIC_ADDRESS_SIZE,
						HCI_MGMT_UNCONFIGURED पूर्ण,
	अणु start_service_discovery, MGMT_START_SERVICE_DISCOVERY_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु पढ़ो_local_oob_ext_data, MGMT_READ_LOCAL_OOB_EXT_DATA_SIZE पूर्ण,
	अणु पढ़ो_ext_index_list,     MGMT_READ_EXT_INDEX_LIST_SIZE,
						HCI_MGMT_NO_HDEV |
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_adv_features,       MGMT_READ_ADV_FEATURES_SIZE पूर्ण,
	अणु add_advertising,	   MGMT_ADD_ADVERTISING_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु हटाओ_advertising,	   MGMT_REMOVE_ADVERTISING_SIZE पूर्ण,
	अणु get_adv_size_info,       MGMT_GET_ADV_SIZE_INFO_SIZE पूर्ण,
	अणु start_limited_discovery, MGMT_START_DISCOVERY_SIZE पूर्ण,
	अणु पढ़ो_ext_controller_info,MGMT_READ_EXT_INFO_SIZE,
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु set_appearance,	   MGMT_SET_APPEARANCE_SIZE पूर्ण,
	अणु get_phy_configuration,   MGMT_GET_PHY_CONFIGURATION_SIZE पूर्ण,
	अणु set_phy_configuration,   MGMT_SET_PHY_CONFIGURATION_SIZE पूर्ण,
	अणु set_blocked_keys,	   MGMT_OP_SET_BLOCKED_KEYS_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु set_wideband_speech,	   MGMT_SETTING_SIZE पूर्ण,
	अणु पढ़ो_controller_cap,     MGMT_READ_CONTROLLER_CAP_SIZE,
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु पढ़ो_exp_features_info,  MGMT_READ_EXP_FEATURES_INFO_SIZE,
						HCI_MGMT_UNTRUSTED |
						HCI_MGMT_HDEV_OPTIONAL पूर्ण,
	अणु set_exp_feature,         MGMT_SET_EXP_FEATURE_SIZE,
						HCI_MGMT_VAR_LEN |
						HCI_MGMT_HDEV_OPTIONAL पूर्ण,
	अणु पढ़ो_def_प्रणाली_config,  MGMT_READ_DEF_SYSTEM_CONFIG_SIZE,
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु set_def_प्रणाली_config,   MGMT_SET_DEF_SYSTEM_CONFIG_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु पढ़ो_def_runसमय_config, MGMT_READ_DEF_RUNTIME_CONFIG_SIZE,
						HCI_MGMT_UNTRUSTED पूर्ण,
	अणु set_def_runसमय_config,  MGMT_SET_DEF_RUNTIME_CONFIG_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु get_device_flags,        MGMT_GET_DEVICE_FLAGS_SIZE पूर्ण,
	अणु set_device_flags,        MGMT_SET_DEVICE_FLAGS_SIZE पूर्ण,
	अणु पढ़ो_adv_mon_features,   MGMT_READ_ADV_MONITOR_FEATURES_SIZE पूर्ण,
	अणु add_adv_patterns_monitor,MGMT_ADD_ADV_PATTERNS_MONITOR_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु हटाओ_adv_monitor,      MGMT_REMOVE_ADV_MONITOR_SIZE पूर्ण,
	अणु add_ext_adv_params,      MGMT_ADD_EXT_ADV_PARAMS_MIN_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु add_ext_adv_data,        MGMT_ADD_EXT_ADV_DATA_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
	अणु add_adv_patterns_monitor_rssi,
				   MGMT_ADD_ADV_PATTERNS_MONITOR_RSSI_SIZE,
						HCI_MGMT_VAR_LEN पूर्ण,
पूर्ण;

व्योम mgmt_index_added(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_ev_ext_index ev;

	अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		वापस;

	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
			mgmt_index_event(MGMT_EV_UNCONF_INDEX_ADDED, hdev,
					 शून्य, 0, HCI_MGMT_UNCONF_INDEX_EVENTS);
			ev.type = 0x01;
		पूर्ण अन्यथा अणु
			mgmt_index_event(MGMT_EV_INDEX_ADDED, hdev, शून्य, 0,
					 HCI_MGMT_INDEX_EVENTS);
			ev.type = 0x00;
		पूर्ण
		अवरोध;
	हाल HCI_AMP:
		ev.type = 0x02;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ev.bus = hdev->bus;

	mgmt_index_event(MGMT_EV_EXT_INDEX_ADDED, hdev, &ev, माप(ev),
			 HCI_MGMT_EXT_INDEX_EVENTS);
पूर्ण

व्योम mgmt_index_हटाओd(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_ev_ext_index ev;
	u8 status = MGMT_STATUS_INVALID_INDEX;

	अगर (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		वापस;

	चयन (hdev->dev_type) अणु
	हाल HCI_PRIMARY:
		mgmt_pending_क्रमeach(0, hdev, cmd_complete_rsp, &status);

		अगर (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) अणु
			mgmt_index_event(MGMT_EV_UNCONF_INDEX_REMOVED, hdev,
					 शून्य, 0, HCI_MGMT_UNCONF_INDEX_EVENTS);
			ev.type = 0x01;
		पूर्ण अन्यथा अणु
			mgmt_index_event(MGMT_EV_INDEX_REMOVED, hdev, शून्य, 0,
					 HCI_MGMT_INDEX_EVENTS);
			ev.type = 0x00;
		पूर्ण
		अवरोध;
	हाल HCI_AMP:
		ev.type = 0x02;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ev.bus = hdev->bus;

	mgmt_index_event(MGMT_EV_EXT_INDEX_REMOVED, hdev, &ev, माप(ev),
			 HCI_MGMT_EXT_INDEX_EVENTS);
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल व्योम restart_le_actions(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_params *p;

	list_क्रम_each_entry(p, &hdev->le_conn_params, list) अणु
		/* Needed क्रम AUTO_OFF हाल where might not "really"
		 * have been घातered off.
		 */
		list_del_init(&p->action);

		चयन (p->स्वतः_connect) अणु
		हाल HCI_AUTO_CONN_सूचीECT:
		हाल HCI_AUTO_CONN_ALWAYS:
			list_add(&p->action, &hdev->pend_le_conns);
			अवरोध;
		हाल HCI_AUTO_CONN_REPORT:
			list_add(&p->action, &hdev->pend_le_reports);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम mgmt_घातer_on(काष्ठा hci_dev *hdev, पूर्णांक err)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;

	bt_dev_dbg(hdev, "err %d", err);

	hci_dev_lock(hdev);

	अगर (!err) अणु
		restart_le_actions(hdev);
		hci_update_background_scan(hdev);
	पूर्ण

	mgmt_pending_क्रमeach(MGMT_OP_SET_POWERED, hdev, settings_rsp, &match);

	new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);

	hci_dev_unlock(hdev);
पूर्ण

व्योम __mgmt_घातer_off(काष्ठा hci_dev *hdev)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;
	u8 status, zero_cod[] = अणु 0, 0, 0 पूर्ण;

	mgmt_pending_क्रमeach(MGMT_OP_SET_POWERED, hdev, settings_rsp, &match);

	/* If the घातer off is because of hdev unregistration let
	 * use the appropriate INVALID_INDEX status. Otherwise use
	 * NOT_POWERED. We cover both scenarios here since later in
	 * mgmt_index_हटाओd() any hci_conn callbacks will have alपढ़ोy
	 * been triggered, potentially causing misleading DISCONNECTED
	 * status responses.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_UNREGISTER))
		status = MGMT_STATUS_INVALID_INDEX;
	अन्यथा
		status = MGMT_STATUS_NOT_POWERED;

	mgmt_pending_क्रमeach(0, hdev, cmd_complete_rsp, &status);

	अगर (स_भेद(hdev->dev_class, zero_cod, माप(zero_cod)) != 0) अणु
		mgmt_limited_event(MGMT_EV_CLASS_OF_DEV_CHANGED, hdev,
				   zero_cod, माप(zero_cod),
				   HCI_MGMT_DEV_CLASS_EVENTS, शून्य);
		ext_info_changed(hdev, शून्य);
	पूर्ण

	new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);
पूर्ण

व्योम mgmt_set_घातered_failed(काष्ठा hci_dev *hdev, पूर्णांक err)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	u8 status;

	cmd = pending_find(MGMT_OP_SET_POWERED, hdev);
	अगर (!cmd)
		वापस;

	अगर (err == -ERFKILL)
		status = MGMT_STATUS_RFKILLED;
	अन्यथा
		status = MGMT_STATUS_FAILED;

	mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_SET_POWERED, status);

	mgmt_pending_हटाओ(cmd);
पूर्ण

व्योम mgmt_new_link_key(काष्ठा hci_dev *hdev, काष्ठा link_key *key,
		       bool persistent)
अणु
	काष्ठा mgmt_ev_new_link_key ev;

	स_रखो(&ev, 0, माप(ev));

	ev.store_hपूर्णांक = persistent;
	bacpy(&ev.key.addr.bdaddr, &key->bdaddr);
	ev.key.addr.type = BDADDR_BREDR;
	ev.key.type = key->type;
	स_नकल(ev.key.val, key->val, HCI_LINK_KEY_SIZE);
	ev.key.pin_len = key->pin_len;

	mgmt_event(MGMT_EV_NEW_LINK_KEY, hdev, &ev, माप(ev), शून्य);
पूर्ण

अटल u8 mgmt_ltk_type(काष्ठा smp_ltk *ltk)
अणु
	चयन (ltk->type) अणु
	हाल SMP_LTK:
	हाल SMP_LTK_SLAVE:
		अगर (ltk->authenticated)
			वापस MGMT_LTK_AUTHENTICATED;
		वापस MGMT_LTK_UNAUTHENTICATED;
	हाल SMP_LTK_P256:
		अगर (ltk->authenticated)
			वापस MGMT_LTK_P256_AUTH;
		वापस MGMT_LTK_P256_UNAUTH;
	हाल SMP_LTK_P256_DEBUG:
		वापस MGMT_LTK_P256_DEBUG;
	पूर्ण

	वापस MGMT_LTK_UNAUTHENTICATED;
पूर्ण

व्योम mgmt_new_ltk(काष्ठा hci_dev *hdev, काष्ठा smp_ltk *key, bool persistent)
अणु
	काष्ठा mgmt_ev_new_दीर्घ_term_key ev;

	स_रखो(&ev, 0, माप(ev));

	/* Devices using resolvable or non-resolvable अक्रमom addresses
	 * without providing an identity resolving key करोn't require
	 * to store दीर्घ term keys. Their addresses will change the
	 * next समय around.
	 *
	 * Only when a remote device provides an identity address
	 * make sure the दीर्घ term key is stored. If the remote
	 * identity is known, the दीर्घ term keys are पूर्णांकernally
	 * mapped to the identity address. So allow अटल अक्रमom
	 * and खुला addresses here.
	 */
	अगर (key->bdaddr_type == ADDR_LE_DEV_RANDOM &&
	    (key->bdaddr.b[5] & 0xc0) != 0xc0)
		ev.store_hपूर्णांक = 0x00;
	अन्यथा
		ev.store_hपूर्णांक = persistent;

	bacpy(&ev.key.addr.bdaddr, &key->bdaddr);
	ev.key.addr.type = link_to_bdaddr(LE_LINK, key->bdaddr_type);
	ev.key.type = mgmt_ltk_type(key);
	ev.key.enc_size = key->enc_size;
	ev.key.eभाग = key->eभाग;
	ev.key.अक्रम = key->अक्रम;

	अगर (key->type == SMP_LTK)
		ev.key.master = 1;

	/* Make sure we copy only the signअगरicant bytes based on the
	 * encryption key size, and set the rest of the value to zeroes.
	 */
	स_नकल(ev.key.val, key->val, key->enc_size);
	स_रखो(ev.key.val + key->enc_size, 0,
	       माप(ev.key.val) - key->enc_size);

	mgmt_event(MGMT_EV_NEW_LONG_TERM_KEY, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_new_irk(काष्ठा hci_dev *hdev, काष्ठा smp_irk *irk, bool persistent)
अणु
	काष्ठा mgmt_ev_new_irk ev;

	स_रखो(&ev, 0, माप(ev));

	ev.store_hपूर्णांक = persistent;

	bacpy(&ev.rpa, &irk->rpa);
	bacpy(&ev.irk.addr.bdaddr, &irk->bdaddr);
	ev.irk.addr.type = link_to_bdaddr(LE_LINK, irk->addr_type);
	स_नकल(ev.irk.val, irk->val, माप(irk->val));

	mgmt_event(MGMT_EV_NEW_IRK, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_new_csrk(काष्ठा hci_dev *hdev, काष्ठा smp_csrk *csrk,
		   bool persistent)
अणु
	काष्ठा mgmt_ev_new_csrk ev;

	स_रखो(&ev, 0, माप(ev));

	/* Devices using resolvable or non-resolvable अक्रमom addresses
	 * without providing an identity resolving key करोn't require
	 * to store signature resolving keys. Their addresses will change
	 * the next समय around.
	 *
	 * Only when a remote device provides an identity address
	 * make sure the signature resolving key is stored. So allow
	 * अटल अक्रमom and खुला addresses here.
	 */
	अगर (csrk->bdaddr_type == ADDR_LE_DEV_RANDOM &&
	    (csrk->bdaddr.b[5] & 0xc0) != 0xc0)
		ev.store_hपूर्णांक = 0x00;
	अन्यथा
		ev.store_hपूर्णांक = persistent;

	bacpy(&ev.key.addr.bdaddr, &csrk->bdaddr);
	ev.key.addr.type = link_to_bdaddr(LE_LINK, csrk->bdaddr_type);
	ev.key.type = csrk->type;
	स_नकल(ev.key.val, csrk->val, माप(csrk->val));

	mgmt_event(MGMT_EV_NEW_CSRK, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_new_conn_param(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			 u8 bdaddr_type, u8 store_hपूर्णांक, u16 min_पूर्णांकerval,
			 u16 max_पूर्णांकerval, u16 latency, u16 समयout)
अणु
	काष्ठा mgmt_ev_new_conn_param ev;

	अगर (!hci_is_identity_address(bdaddr, bdaddr_type))
		वापस;

	स_रखो(&ev, 0, माप(ev));
	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(LE_LINK, bdaddr_type);
	ev.store_hपूर्णांक = store_hपूर्णांक;
	ev.min_पूर्णांकerval = cpu_to_le16(min_पूर्णांकerval);
	ev.max_पूर्णांकerval = cpu_to_le16(max_पूर्णांकerval);
	ev.latency = cpu_to_le16(latency);
	ev.समयout = cpu_to_le16(समयout);

	mgmt_event(MGMT_EV_NEW_CONN_PARAM, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_device_connected(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
			   u32 flags, u8 *name, u8 name_len)
अणु
	अक्षर buf[512];
	काष्ठा mgmt_ev_device_connected *ev = (व्योम *) buf;
	u16 eir_len = 0;

	bacpy(&ev->addr.bdaddr, &conn->dst);
	ev->addr.type = link_to_bdaddr(conn->type, conn->dst_type);

	ev->flags = __cpu_to_le32(flags);

	/* We must ensure that the EIR Data fields are ordered and
	 * unique. Keep it simple क्रम now and aव्योम the problem by not
	 * adding any BR/EDR data to the LE adv.
	 */
	अगर (conn->le_adv_data_len > 0) अणु
		स_नकल(&ev->eir[eir_len],
		       conn->le_adv_data, conn->le_adv_data_len);
		eir_len = conn->le_adv_data_len;
	पूर्ण अन्यथा अणु
		अगर (name_len > 0)
			eir_len = eir_append_data(ev->eir, 0, EIR_NAME_COMPLETE,
						  name, name_len);

		अगर (स_भेद(conn->dev_class, "\0\0\0", 3) != 0)
			eir_len = eir_append_data(ev->eir, eir_len,
						  EIR_CLASS_OF_DEV,
						  conn->dev_class, 3);
	पूर्ण

	ev->eir_len = cpu_to_le16(eir_len);

	mgmt_event(MGMT_EV_DEVICE_CONNECTED, hdev, buf,
		    माप(*ev) + eir_len, शून्य);
पूर्ण

अटल व्योम disconnect_rsp(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	काष्ठा sock **sk = data;

	cmd->cmd_complete(cmd, 0);

	*sk = cmd->sk;
	sock_hold(*sk);

	mgmt_pending_हटाओ(cmd);
पूर्ण

अटल व्योम unpair_device_rsp(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	काष्ठा hci_dev *hdev = data;
	काष्ठा mgmt_cp_unpair_device *cp = cmd->param;

	device_unpaired(hdev, &cp->addr.bdaddr, cp->addr.type, cmd->sk);

	cmd->cmd_complete(cmd, 0);
	mgmt_pending_हटाओ(cmd);
पूर्ण

bool mgmt_घातering_करोwn(काष्ठा hci_dev *hdev)
अणु
	काष्ठा mgmt_pending_cmd *cmd;
	काष्ठा mgmt_mode *cp;

	cmd = pending_find(MGMT_OP_SET_POWERED, hdev);
	अगर (!cmd)
		वापस false;

	cp = cmd->param;
	अगर (!cp->val)
		वापस true;

	वापस false;
पूर्ण

व्योम mgmt_device_disconnected(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type, u8 reason,
			      bool mgmt_connected)
अणु
	काष्ठा mgmt_ev_device_disconnected ev;
	काष्ठा sock *sk = शून्य;

	/* The connection is still in hci_conn_hash so test क्रम 1
	 * instead of 0 to know अगर this is the last one.
	 */
	अगर (mgmt_घातering_करोwn(hdev) && hci_conn_count(hdev) == 1) अणु
		cancel_delayed_work(&hdev->घातer_off);
		queue_work(hdev->req_workqueue, &hdev->घातer_off.work);
	पूर्ण

	अगर (!mgmt_connected)
		वापस;

	अगर (link_type != ACL_LINK && link_type != LE_LINK)
		वापस;

	mgmt_pending_क्रमeach(MGMT_OP_DISCONNECT, hdev, disconnect_rsp, &sk);

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(link_type, addr_type);
	ev.reason = reason;

	/* Report disconnects due to suspend */
	अगर (hdev->suspended)
		ev.reason = MGMT_DEV_DISCONN_LOCAL_HOST_SUSPEND;

	mgmt_event(MGMT_EV_DEVICE_DISCONNECTED, hdev, &ev, माप(ev), sk);

	अगर (sk)
		sock_put(sk);

	mgmt_pending_क्रमeach(MGMT_OP_UNPAIR_DEVICE, hdev, unpair_device_rsp,
			     hdev);
पूर्ण

व्योम mgmt_disconnect_failed(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 link_type, u8 addr_type, u8 status)
अणु
	u8 bdaddr_type = link_to_bdaddr(link_type, addr_type);
	काष्ठा mgmt_cp_disconnect *cp;
	काष्ठा mgmt_pending_cmd *cmd;

	mgmt_pending_क्रमeach(MGMT_OP_UNPAIR_DEVICE, hdev, unpair_device_rsp,
			     hdev);

	cmd = pending_find(MGMT_OP_DISCONNECT, hdev);
	अगर (!cmd)
		वापस;

	cp = cmd->param;

	अगर (bacmp(bdaddr, &cp->addr.bdaddr))
		वापस;

	अगर (cp->addr.type != bdaddr_type)
		वापस;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);
पूर्ण

व्योम mgmt_connect_failed(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
			 u8 addr_type, u8 status)
अणु
	काष्ठा mgmt_ev_connect_failed ev;

	/* The connection is still in hci_conn_hash so test क्रम 1
	 * instead of 0 to know अगर this is the last one.
	 */
	अगर (mgmt_घातering_करोwn(hdev) && hci_conn_count(hdev) == 1) अणु
		cancel_delayed_work(&hdev->घातer_off);
		queue_work(hdev->req_workqueue, &hdev->घातer_off.work);
	पूर्ण

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(link_type, addr_type);
	ev.status = mgmt_status(status);

	mgmt_event(MGMT_EV_CONNECT_FAILED, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_pin_code_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 secure)
अणु
	काष्ठा mgmt_ev_pin_code_request ev;

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = BDADDR_BREDR;
	ev.secure = secure;

	mgmt_event(MGMT_EV_PIN_CODE_REQUEST, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_pin_code_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	cmd = pending_find(MGMT_OP_PIN_CODE_REPLY, hdev);
	अगर (!cmd)
		वापस;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);
पूर्ण

व्योम mgmt_pin_code_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				      u8 status)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	cmd = pending_find(MGMT_OP_PIN_CODE_NEG_REPLY, hdev);
	अगर (!cmd)
		वापस;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);
पूर्ण

पूर्णांक mgmt_user_confirm_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type, u32 value,
			      u8 confirm_hपूर्णांक)
अणु
	काष्ठा mgmt_ev_user_confirm_request ev;

	bt_dev_dbg(hdev, "bdaddr %pMR", bdaddr);

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(link_type, addr_type);
	ev.confirm_hपूर्णांक = confirm_hपूर्णांक;
	ev.value = cpu_to_le32(value);

	वापस mgmt_event(MGMT_EV_USER_CONFIRM_REQUEST, hdev, &ev, माप(ev),
			  शून्य);
पूर्ण

पूर्णांक mgmt_user_passkey_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type)
अणु
	काष्ठा mgmt_ev_user_passkey_request ev;

	bt_dev_dbg(hdev, "bdaddr %pMR", bdaddr);

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(link_type, addr_type);

	वापस mgmt_event(MGMT_EV_USER_PASSKEY_REQUEST, hdev, &ev, माप(ev),
			  शून्य);
पूर्ण

अटल पूर्णांक user_pairing_resp_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				      u8 link_type, u8 addr_type, u8 status,
				      u8 opcode)
अणु
	काष्ठा mgmt_pending_cmd *cmd;

	cmd = pending_find(opcode, hdev);
	अगर (!cmd)
		वापस -ENOENT;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_हटाओ(cmd);

	वापस 0;
पूर्ण

पूर्णांक mgmt_user_confirm_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 link_type, u8 addr_type, u8 status)
अणु
	वापस user_pairing_resp_complete(hdev, bdaddr, link_type, addr_type,
					  status, MGMT_OP_USER_CONFIRM_REPLY);
पूर्ण

पूर्णांक mgmt_user_confirm_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
					 u8 link_type, u8 addr_type, u8 status)
अणु
	वापस user_pairing_resp_complete(hdev, bdaddr, link_type, addr_type,
					  status,
					  MGMT_OP_USER_CONFIRM_NEG_REPLY);
पूर्ण

पूर्णांक mgmt_user_passkey_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 link_type, u8 addr_type, u8 status)
अणु
	वापस user_pairing_resp_complete(hdev, bdaddr, link_type, addr_type,
					  status, MGMT_OP_USER_PASSKEY_REPLY);
पूर्ण

पूर्णांक mgmt_user_passkey_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
					 u8 link_type, u8 addr_type, u8 status)
अणु
	वापस user_pairing_resp_complete(hdev, bdaddr, link_type, addr_type,
					  status,
					  MGMT_OP_USER_PASSKEY_NEG_REPLY);
पूर्ण

पूर्णांक mgmt_user_passkey_notअगरy(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			     u8 link_type, u8 addr_type, u32 passkey,
			     u8 entered)
अणु
	काष्ठा mgmt_ev_passkey_notअगरy ev;

	bt_dev_dbg(hdev, "bdaddr %pMR", bdaddr);

	bacpy(&ev.addr.bdaddr, bdaddr);
	ev.addr.type = link_to_bdaddr(link_type, addr_type);
	ev.passkey = __cpu_to_le32(passkey);
	ev.entered = entered;

	वापस mgmt_event(MGMT_EV_PASSKEY_NOTIFY, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_auth_failed(काष्ठा hci_conn *conn, u8 hci_status)
अणु
	काष्ठा mgmt_ev_auth_failed ev;
	काष्ठा mgmt_pending_cmd *cmd;
	u8 status = mgmt_status(hci_status);

	bacpy(&ev.addr.bdaddr, &conn->dst);
	ev.addr.type = link_to_bdaddr(conn->type, conn->dst_type);
	ev.status = status;

	cmd = find_pairing(conn);

	mgmt_event(MGMT_EV_AUTH_FAILED, conn->hdev, &ev, माप(ev),
		    cmd ? cmd->sk : शून्य);

	अगर (cmd) अणु
		cmd->cmd_complete(cmd, status);
		mgmt_pending_हटाओ(cmd);
	पूर्ण
पूर्ण

व्योम mgmt_auth_enable_complete(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;
	bool changed;

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);
		mgmt_pending_क्रमeach(MGMT_OP_SET_LINK_SECURITY, hdev,
				     cmd_status_rsp, &mgmt_err);
		वापस;
	पूर्ण

	अगर (test_bit(HCI_AUTH, &hdev->flags))
		changed = !hci_dev_test_and_set_flag(hdev, HCI_LINK_SECURITY);
	अन्यथा
		changed = hci_dev_test_and_clear_flag(hdev, HCI_LINK_SECURITY);

	mgmt_pending_क्रमeach(MGMT_OP_SET_LINK_SECURITY, hdev, settings_rsp,
			     &match);

	अगर (changed)
		new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);
पूर्ण

अटल व्योम clear_eir(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_eir cp;

	अगर (!lmp_ext_inq_capable(hdev))
		वापस;

	स_रखो(hdev->eir, 0, माप(hdev->eir));

	स_रखो(&cp, 0, माप(cp));

	hci_req_add(req, HCI_OP_WRITE_EIR, माप(cp), &cp);
पूर्ण

व्योम mgmt_ssp_enable_complete(काष्ठा hci_dev *hdev, u8 enable, u8 status)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev पूर्ण;
	काष्ठा hci_request req;
	bool changed = false;

	अगर (status) अणु
		u8 mgmt_err = mgmt_status(status);

		अगर (enable && hci_dev_test_and_clear_flag(hdev,
							  HCI_SSP_ENABLED)) अणु
			hci_dev_clear_flag(hdev, HCI_HS_ENABLED);
			new_settings(hdev, शून्य);
		पूर्ण

		mgmt_pending_क्रमeach(MGMT_OP_SET_SSP, hdev, cmd_status_rsp,
				     &mgmt_err);
		वापस;
	पूर्ण

	अगर (enable) अणु
		changed = !hci_dev_test_and_set_flag(hdev, HCI_SSP_ENABLED);
	पूर्ण अन्यथा अणु
		changed = hci_dev_test_and_clear_flag(hdev, HCI_SSP_ENABLED);
		अगर (!changed)
			changed = hci_dev_test_and_clear_flag(hdev,
							      HCI_HS_ENABLED);
		अन्यथा
			hci_dev_clear_flag(hdev, HCI_HS_ENABLED);
	पूर्ण

	mgmt_pending_क्रमeach(MGMT_OP_SET_SSP, hdev, settings_rsp, &match);

	अगर (changed)
		new_settings(hdev, match.sk);

	अगर (match.sk)
		sock_put(match.sk);

	hci_req_init(&req, hdev);

	अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) अणु
		अगर (hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS))
			hci_req_add(&req, HCI_OP_WRITE_SSP_DEBUG_MODE,
				    माप(enable), &enable);
		__hci_req_update_eir(&req);
	पूर्ण अन्यथा अणु
		clear_eir(&req);
	पूर्ण

	hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम sk_lookup(काष्ठा mgmt_pending_cmd *cmd, व्योम *data)
अणु
	काष्ठा cmd_lookup *match = data;

	अगर (match->sk == शून्य) अणु
		match->sk = cmd->sk;
		sock_hold(match->sk);
	पूर्ण
पूर्ण

व्योम mgmt_set_class_of_dev_complete(काष्ठा hci_dev *hdev, u8 *dev_class,
				    u8 status)
अणु
	काष्ठा cmd_lookup match = अणु शून्य, hdev, mgmt_status(status) पूर्ण;

	mgmt_pending_क्रमeach(MGMT_OP_SET_DEV_CLASS, hdev, sk_lookup, &match);
	mgmt_pending_क्रमeach(MGMT_OP_ADD_UUID, hdev, sk_lookup, &match);
	mgmt_pending_क्रमeach(MGMT_OP_REMOVE_UUID, hdev, sk_lookup, &match);

	अगर (!status) अणु
		mgmt_limited_event(MGMT_EV_CLASS_OF_DEV_CHANGED, hdev, dev_class,
				   3, HCI_MGMT_DEV_CLASS_EVENTS, शून्य);
		ext_info_changed(hdev, शून्य);
	पूर्ण

	अगर (match.sk)
		sock_put(match.sk);
पूर्ण

व्योम mgmt_set_local_name_complete(काष्ठा hci_dev *hdev, u8 *name, u8 status)
अणु
	काष्ठा mgmt_cp_set_local_name ev;
	काष्ठा mgmt_pending_cmd *cmd;

	अगर (status)
		वापस;

	स_रखो(&ev, 0, माप(ev));
	स_नकल(ev.name, name, HCI_MAX_NAME_LENGTH);
	स_नकल(ev.लघु_name, hdev->लघु_name, HCI_MAX_SHORT_NAME_LENGTH);

	cmd = pending_find(MGMT_OP_SET_LOCAL_NAME, hdev);
	अगर (!cmd) अणु
		स_नकल(hdev->dev_name, name, माप(hdev->dev_name));

		/* If this is a HCI command related to घातering on the
		 * HCI dev करोn't send any mgmt संकेतs.
		 */
		अगर (pending_find(MGMT_OP_SET_POWERED, hdev))
			वापस;
	पूर्ण

	mgmt_limited_event(MGMT_EV_LOCAL_NAME_CHANGED, hdev, &ev, माप(ev),
			   HCI_MGMT_LOCAL_NAME_EVENTS, cmd ? cmd->sk : शून्य);
	ext_info_changed(hdev, cmd ? cmd->sk : शून्य);
पूर्ण

अटल अंतरभूत bool has_uuid(u8 *uuid, u16 uuid_count, u8 (*uuids)[16])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < uuid_count; i++) अणु
		अगर (!स_भेद(uuid, uuids[i], 16))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool eir_has_uuids(u8 *eir, u16 eir_len, u16 uuid_count, u8 (*uuids)[16])
अणु
	u16 parsed = 0;

	जबतक (parsed < eir_len) अणु
		u8 field_len = eir[0];
		u8 uuid[16];
		पूर्णांक i;

		अगर (field_len == 0)
			अवरोध;

		अगर (eir_len - parsed < field_len + 1)
			अवरोध;

		चयन (eir[1]) अणु
		हाल EIR_UUID16_ALL:
		हाल EIR_UUID16_SOME:
			क्रम (i = 0; i + 3 <= field_len; i += 2) अणु
				स_नकल(uuid, bluetooth_base_uuid, 16);
				uuid[13] = eir[i + 3];
				uuid[12] = eir[i + 2];
				अगर (has_uuid(uuid, uuid_count, uuids))
					वापस true;
			पूर्ण
			अवरोध;
		हाल EIR_UUID32_ALL:
		हाल EIR_UUID32_SOME:
			क्रम (i = 0; i + 5 <= field_len; i += 4) अणु
				स_नकल(uuid, bluetooth_base_uuid, 16);
				uuid[15] = eir[i + 5];
				uuid[14] = eir[i + 4];
				uuid[13] = eir[i + 3];
				uuid[12] = eir[i + 2];
				अगर (has_uuid(uuid, uuid_count, uuids))
					वापस true;
			पूर्ण
			अवरोध;
		हाल EIR_UUID128_ALL:
		हाल EIR_UUID128_SOME:
			क्रम (i = 0; i + 17 <= field_len; i += 16) अणु
				स_नकल(uuid, eir + i + 2, 16);
				अगर (has_uuid(uuid, uuid_count, uuids))
					वापस true;
			पूर्ण
			अवरोध;
		पूर्ण

		parsed += field_len + 1;
		eir += field_len + 1;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम restart_le_scan(काष्ठा hci_dev *hdev)
अणु
	/* If controller is not scanning we are करोne. */
	अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
		वापस;

	अगर (समय_after(jअगरfies + DISCOV_LE_RESTART_DELAY,
		       hdev->discovery.scan_start +
		       hdev->discovery.scan_duration))
		वापस;

	queue_delayed_work(hdev->req_workqueue, &hdev->le_scan_restart,
			   DISCOV_LE_RESTART_DELAY);
पूर्ण

अटल bool is_filter_match(काष्ठा hci_dev *hdev, s8 rssi, u8 *eir,
			    u16 eir_len, u8 *scan_rsp, u8 scan_rsp_len)
अणु
	/* If a RSSI threshold has been specअगरied, and
	 * HCI_QUIRK_STRICT_DUPLICATE_FILTER is not set, then all results with
	 * a RSSI smaller than the RSSI threshold will be dropped. If the quirk
	 * is set, let it through क्रम further processing, as we might need to
	 * restart the scan.
	 *
	 * For BR/EDR devices (pre 1.2) providing no RSSI during inquiry,
	 * the results are also dropped.
	 */
	अगर (hdev->discovery.rssi != HCI_RSSI_INVALID &&
	    (rssi == HCI_RSSI_INVALID ||
	    (rssi < hdev->discovery.rssi &&
	     !test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks))))
		वापस  false;

	अगर (hdev->discovery.uuid_count != 0) अणु
		/* If a list of UUIDs is provided in filter, results with no
		 * matching UUID should be dropped.
		 */
		अगर (!eir_has_uuids(eir, eir_len, hdev->discovery.uuid_count,
				   hdev->discovery.uuids) &&
		    !eir_has_uuids(scan_rsp, scan_rsp_len,
				   hdev->discovery.uuid_count,
				   hdev->discovery.uuids))
			वापस false;
	पूर्ण

	/* If duplicate filtering करोes not report RSSI changes, then restart
	 * scanning to ensure updated result with updated RSSI values.
	 */
	अगर (test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks)) अणु
		restart_le_scan(hdev);

		/* Validate RSSI value against the RSSI threshold once more. */
		अगर (hdev->discovery.rssi != HCI_RSSI_INVALID &&
		    rssi < hdev->discovery.rssi)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम mgmt_device_found(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
		       u8 addr_type, u8 *dev_class, s8 rssi, u32 flags,
		       u8 *eir, u16 eir_len, u8 *scan_rsp, u8 scan_rsp_len)
अणु
	अक्षर buf[512];
	काष्ठा mgmt_ev_device_found *ev = (व्योम *)buf;
	माप_प्रकार ev_size;

	/* Don't send events क्रम a non-kernel initiated discovery. With
	 * LE one exception is अगर we have pend_le_reports > 0 in which
	 * हाल we're करोing passive scanning and want these events.
	 */
	अगर (!hci_discovery_active(hdev)) अणु
		अगर (link_type == ACL_LINK)
			वापस;
		अगर (link_type == LE_LINK &&
		    list_empty(&hdev->pend_le_reports) &&
		    !hci_is_adv_monitoring(hdev)) अणु
			वापस;
		पूर्ण
	पूर्ण

	अगर (hdev->discovery.result_filtering) अणु
		/* We are using service discovery */
		अगर (!is_filter_match(hdev, rssi, eir, eir_len, scan_rsp,
				     scan_rsp_len))
			वापस;
	पूर्ण

	अगर (hdev->discovery.limited) अणु
		/* Check क्रम limited discoverable bit */
		अगर (dev_class) अणु
			अगर (!(dev_class[1] & 0x20))
				वापस;
		पूर्ण अन्यथा अणु
			u8 *flags = eir_get_data(eir, eir_len, EIR_FLAGS, शून्य);
			अगर (!flags || !(flags[0] & LE_AD_LIMITED))
				वापस;
		पूर्ण
	पूर्ण

	/* Make sure that the buffer is big enough. The 5 extra bytes
	 * are क्रम the potential CoD field.
	 */
	अगर (माप(*ev) + eir_len + scan_rsp_len + 5 > माप(buf))
		वापस;

	स_रखो(buf, 0, माप(buf));

	/* In हाल of device discovery with BR/EDR devices (pre 1.2), the
	 * RSSI value was reported as 0 when not available. This behavior
	 * is kept when using device discovery. This is required क्रम full
	 * backwards compatibility with the API.
	 *
	 * However when using service discovery, the value 127 will be
	 * वापसed when the RSSI is not available.
	 */
	अगर (rssi == HCI_RSSI_INVALID && !hdev->discovery.report_invalid_rssi &&
	    link_type == ACL_LINK)
		rssi = 0;

	bacpy(&ev->addr.bdaddr, bdaddr);
	ev->addr.type = link_to_bdaddr(link_type, addr_type);
	ev->rssi = rssi;
	ev->flags = cpu_to_le32(flags);

	अगर (eir_len > 0)
		/* Copy EIR or advertising data पूर्णांकo event */
		स_नकल(ev->eir, eir, eir_len);

	अगर (dev_class && !eir_get_data(ev->eir, eir_len, EIR_CLASS_OF_DEV,
				       शून्य))
		eir_len = eir_append_data(ev->eir, eir_len, EIR_CLASS_OF_DEV,
					  dev_class, 3);

	अगर (scan_rsp_len > 0)
		/* Append scan response data to event */
		स_नकल(ev->eir + eir_len, scan_rsp, scan_rsp_len);

	ev->eir_len = cpu_to_le16(eir_len + scan_rsp_len);
	ev_size = माप(*ev) + eir_len + scan_rsp_len;

	mgmt_event(MGMT_EV_DEVICE_FOUND, hdev, ev, ev_size, शून्य);
पूर्ण

व्योम mgmt_remote_name(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
		      u8 addr_type, s8 rssi, u8 *name, u8 name_len)
अणु
	काष्ठा mgmt_ev_device_found *ev;
	अक्षर buf[माप(*ev) + HCI_MAX_NAME_LENGTH + 2];
	u16 eir_len;

	ev = (काष्ठा mgmt_ev_device_found *) buf;

	स_रखो(buf, 0, माप(buf));

	bacpy(&ev->addr.bdaddr, bdaddr);
	ev->addr.type = link_to_bdaddr(link_type, addr_type);
	ev->rssi = rssi;

	eir_len = eir_append_data(ev->eir, 0, EIR_NAME_COMPLETE, name,
				  name_len);

	ev->eir_len = cpu_to_le16(eir_len);

	mgmt_event(MGMT_EV_DEVICE_FOUND, hdev, ev, माप(*ev) + eir_len, शून्य);
पूर्ण

व्योम mgmt_discovering(काष्ठा hci_dev *hdev, u8 discovering)
अणु
	काष्ठा mgmt_ev_discovering ev;

	bt_dev_dbg(hdev, "discovering %u", discovering);

	स_रखो(&ev, 0, माप(ev));
	ev.type = hdev->discovery.type;
	ev.discovering = discovering;

	mgmt_event(MGMT_EV_DISCOVERING, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_suspending(काष्ठा hci_dev *hdev, u8 state)
अणु
	काष्ठा mgmt_ev_controller_suspend ev;

	ev.suspend_state = state;
	mgmt_event(MGMT_EV_CONTROLLER_SUSPEND, hdev, &ev, माप(ev), शून्य);
पूर्ण

व्योम mgmt_resuming(काष्ठा hci_dev *hdev, u8 reason, bdaddr_t *bdaddr,
		   u8 addr_type)
अणु
	काष्ठा mgmt_ev_controller_resume ev;

	ev.wake_reason = reason;
	अगर (bdaddr) अणु
		bacpy(&ev.addr.bdaddr, bdaddr);
		ev.addr.type = addr_type;
	पूर्ण अन्यथा अणु
		स_रखो(&ev.addr, 0, माप(ev.addr));
	पूर्ण

	mgmt_event(MGMT_EV_CONTROLLER_RESUME, hdev, &ev, माप(ev), शून्य);
पूर्ण

अटल काष्ठा hci_mgmt_chan chan = अणु
	.channel	= HCI_CHANNEL_CONTROL,
	.handler_count	= ARRAY_SIZE(mgmt_handlers),
	.handlers	= mgmt_handlers,
	.hdev_init	= mgmt_init_hdev,
पूर्ण;

पूर्णांक mgmt_init(व्योम)
अणु
	वापस hci_mgmt_chan_रेजिस्टर(&chan);
पूर्ण

व्योम mgmt_निकास(व्योम)
अणु
	hci_mgmt_chan_unरेजिस्टर(&chan);
पूर्ण
