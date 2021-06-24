<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2010  Nokia Corporation
   Copyright (C) 2011-2012  Intel Corporation

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

#घोषणा MGMT_INDEX_NONE			0xFFFF

#घोषणा MGMT_STATUS_SUCCESS		0x00
#घोषणा MGMT_STATUS_UNKNOWN_COMMAND	0x01
#घोषणा MGMT_STATUS_NOT_CONNECTED	0x02
#घोषणा MGMT_STATUS_FAILED		0x03
#घोषणा MGMT_STATUS_CONNECT_FAILED	0x04
#घोषणा MGMT_STATUS_AUTH_FAILED		0x05
#घोषणा MGMT_STATUS_NOT_PAIRED		0x06
#घोषणा MGMT_STATUS_NO_RESOURCES	0x07
#घोषणा MGMT_STATUS_TIMEOUT		0x08
#घोषणा MGMT_STATUS_ALREADY_CONNECTED	0x09
#घोषणा MGMT_STATUS_BUSY		0x0a
#घोषणा MGMT_STATUS_REJECTED		0x0b
#घोषणा MGMT_STATUS_NOT_SUPPORTED	0x0c
#घोषणा MGMT_STATUS_INVALID_PARAMS	0x0d
#घोषणा MGMT_STATUS_DISCONNECTED	0x0e
#घोषणा MGMT_STATUS_NOT_POWERED		0x0f
#घोषणा MGMT_STATUS_CANCELLED		0x10
#घोषणा MGMT_STATUS_INVALID_INDEX	0x11
#घोषणा MGMT_STATUS_RFKILLED		0x12
#घोषणा MGMT_STATUS_ALREADY_PAIRED	0x13
#घोषणा MGMT_STATUS_PERMISSION_DENIED	0x14

काष्ठा mgmt_hdr अणु
	__le16	opcode;
	__le16	index;
	__le16	len;
पूर्ण __packed;

काष्ठा mgmt_tlv अणु
	__le16 type;
	__u8   length;
	__u8   value[];
पूर्ण __packed;

काष्ठा mgmt_addr_info अणु
	bdaddr_t	bdaddr;
	__u8		type;
पूर्ण __packed;
#घोषणा MGMT_ADDR_INFO_SIZE		7

#घोषणा MGMT_OP_READ_VERSION		0x0001
#घोषणा MGMT_READ_VERSION_SIZE		0
काष्ठा mgmt_rp_पढ़ो_version अणु
	__u8	version;
	__le16	revision;
पूर्ण __packed;

#घोषणा MGMT_OP_READ_COMMANDS		0x0002
#घोषणा MGMT_READ_COMMANDS_SIZE		0
काष्ठा mgmt_rp_पढ़ो_commands अणु
	__le16	num_commands;
	__le16	num_events;
	__le16	opcodes[];
पूर्ण __packed;

#घोषणा MGMT_OP_READ_INDEX_LIST		0x0003
#घोषणा MGMT_READ_INDEX_LIST_SIZE	0
काष्ठा mgmt_rp_पढ़ो_index_list अणु
	__le16	num_controllers;
	__le16	index[];
पूर्ण __packed;

/* Reserve one extra byte क्रम names in management messages so that they
 * are always guaranteed to be nul-terminated */
#घोषणा MGMT_MAX_NAME_LENGTH		(HCI_MAX_NAME_LENGTH + 1)
#घोषणा MGMT_MAX_SHORT_NAME_LENGTH	(HCI_MAX_SHORT_NAME_LENGTH + 1)

#घोषणा MGMT_SETTING_POWERED		0x00000001
#घोषणा MGMT_SETTING_CONNECTABLE	0x00000002
#घोषणा MGMT_SETTING_FAST_CONNECTABLE	0x00000004
#घोषणा MGMT_SETTING_DISCOVERABLE	0x00000008
#घोषणा MGMT_SETTING_BONDABLE		0x00000010
#घोषणा MGMT_SETTING_LINK_SECURITY	0x00000020
#घोषणा MGMT_SETTING_SSP		0x00000040
#घोषणा MGMT_SETTING_BREDR		0x00000080
#घोषणा MGMT_SETTING_HS			0x00000100
#घोषणा MGMT_SETTING_LE			0x00000200
#घोषणा MGMT_SETTING_ADVERTISING	0x00000400
#घोषणा MGMT_SETTING_SECURE_CONN	0x00000800
#घोषणा MGMT_SETTING_DEBUG_KEYS		0x00001000
#घोषणा MGMT_SETTING_PRIVACY		0x00002000
#घोषणा MGMT_SETTING_CONFIGURATION	0x00004000
#घोषणा MGMT_SETTING_STATIC_ADDRESS	0x00008000
#घोषणा MGMT_SETTING_PHY_CONFIGURATION	0x00010000
#घोषणा MGMT_SETTING_WIDEBAND_SPEECH	0x00020000

#घोषणा MGMT_OP_READ_INFO		0x0004
#घोषणा MGMT_READ_INFO_SIZE		0
काष्ठा mgmt_rp_पढ़ो_info अणु
	bdaddr_t	bdaddr;
	__u8		version;
	__le16		manufacturer;
	__le32		supported_settings;
	__le32		current_settings;
	__u8		dev_class[3];
	__u8		name[MGMT_MAX_NAME_LENGTH];
	__u8		लघु_name[MGMT_MAX_SHORT_NAME_LENGTH];
पूर्ण __packed;

काष्ठा mgmt_mode अणु
	__u8 val;
पूर्ण __packed;

#घोषणा MGMT_SETTING_SIZE		1

#घोषणा MGMT_OP_SET_POWERED		0x0005

#घोषणा MGMT_OP_SET_DISCOVERABLE	0x0006
काष्ठा mgmt_cp_set_discoverable अणु
	__u8	val;
	__le16	समयout;
पूर्ण __packed;
#घोषणा MGMT_SET_DISCOVERABLE_SIZE	3

#घोषणा MGMT_OP_SET_CONNECTABLE		0x0007

#घोषणा MGMT_OP_SET_FAST_CONNECTABLE	0x0008

#घोषणा MGMT_OP_SET_BONDABLE		0x0009

#घोषणा MGMT_OP_SET_LINK_SECURITY	0x000A

#घोषणा MGMT_OP_SET_SSP			0x000B

#घोषणा MGMT_OP_SET_HS			0x000C

#घोषणा MGMT_OP_SET_LE			0x000D
#घोषणा MGMT_OP_SET_DEV_CLASS		0x000E
काष्ठा mgmt_cp_set_dev_class अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;
#घोषणा MGMT_SET_DEV_CLASS_SIZE		2

#घोषणा MGMT_OP_SET_LOCAL_NAME		0x000F
काष्ठा mgmt_cp_set_local_name अणु
	__u8	name[MGMT_MAX_NAME_LENGTH];
	__u8	लघु_name[MGMT_MAX_SHORT_NAME_LENGTH];
पूर्ण __packed;
#घोषणा MGMT_SET_LOCAL_NAME_SIZE	260

#घोषणा MGMT_OP_ADD_UUID		0x0010
काष्ठा mgmt_cp_add_uuid अणु
	__u8	uuid[16];
	__u8	svc_hपूर्णांक;
पूर्ण __packed;
#घोषणा MGMT_ADD_UUID_SIZE		17

#घोषणा MGMT_OP_REMOVE_UUID		0x0011
काष्ठा mgmt_cp_हटाओ_uuid अणु
	__u8	uuid[16];
पूर्ण __packed;
#घोषणा MGMT_REMOVE_UUID_SIZE		16

काष्ठा mgmt_link_key_info अणु
	काष्ठा mgmt_addr_info addr;
	__u8	type;
	__u8	val[16];
	__u8	pin_len;
पूर्ण __packed;

#घोषणा MGMT_OP_LOAD_LINK_KEYS		0x0012
काष्ठा mgmt_cp_load_link_keys अणु
	__u8	debug_keys;
	__le16	key_count;
	काष्ठा	mgmt_link_key_info keys[];
पूर्ण __packed;
#घोषणा MGMT_LOAD_LINK_KEYS_SIZE	3

#घोषणा MGMT_LTK_UNAUTHENTICATED	0x00
#घोषणा MGMT_LTK_AUTHENTICATED		0x01
#घोषणा MGMT_LTK_P256_UNAUTH		0x02
#घोषणा MGMT_LTK_P256_AUTH		0x03
#घोषणा MGMT_LTK_P256_DEBUG		0x04

काष्ठा mgmt_ltk_info अणु
	काष्ठा mgmt_addr_info addr;
	__u8	type;
	__u8	master;
	__u8	enc_size;
	__le16	eभाग;
	__le64	अक्रम;
	__u8	val[16];
पूर्ण __packed;

#घोषणा MGMT_OP_LOAD_LONG_TERM_KEYS	0x0013
काष्ठा mgmt_cp_load_दीर्घ_term_keys अणु
	__le16	key_count;
	काष्ठा	mgmt_ltk_info keys[];
पूर्ण __packed;
#घोषणा MGMT_LOAD_LONG_TERM_KEYS_SIZE	2

#घोषणा MGMT_OP_DISCONNECT		0x0014
काष्ठा mgmt_cp_disconnect अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_DISCONNECT_SIZE		MGMT_ADDR_INFO_SIZE
काष्ठा mgmt_rp_disconnect अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_GET_CONNECTIONS		0x0015
#घोषणा MGMT_GET_CONNECTIONS_SIZE	0
काष्ठा mgmt_rp_get_connections अणु
	__le16 conn_count;
	काष्ठा mgmt_addr_info addr[];
पूर्ण __packed;

#घोषणा MGMT_OP_PIN_CODE_REPLY		0x0016
काष्ठा mgmt_cp_pin_code_reply अणु
	काष्ठा mgmt_addr_info addr;
	__u8	pin_len;
	__u8	pin_code[16];
पूर्ण __packed;
#घोषणा MGMT_PIN_CODE_REPLY_SIZE	(MGMT_ADDR_INFO_SIZE + 17)
काष्ठा mgmt_rp_pin_code_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_PIN_CODE_NEG_REPLY	0x0017
काष्ठा mgmt_cp_pin_code_neg_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_PIN_CODE_NEG_REPLY_SIZE	MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_SET_IO_CAPABILITY	0x0018
काष्ठा mgmt_cp_set_io_capability अणु
	__u8	io_capability;
पूर्ण __packed;
#घोषणा MGMT_SET_IO_CAPABILITY_SIZE	1

#घोषणा MGMT_OP_PAIR_DEVICE		0x0019
काष्ठा mgmt_cp_pair_device अणु
	काष्ठा mgmt_addr_info addr;
	__u8	io_cap;
पूर्ण __packed;
#घोषणा MGMT_PAIR_DEVICE_SIZE		(MGMT_ADDR_INFO_SIZE + 1)
काष्ठा mgmt_rp_pair_device अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_CANCEL_PAIR_DEVICE	0x001A
#घोषणा MGMT_CANCEL_PAIR_DEVICE_SIZE	MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_UNPAIR_DEVICE		0x001B
काष्ठा mgmt_cp_unpair_device अणु
	काष्ठा mgmt_addr_info addr;
	__u8 disconnect;
पूर्ण __packed;
#घोषणा MGMT_UNPAIR_DEVICE_SIZE		(MGMT_ADDR_INFO_SIZE + 1)
काष्ठा mgmt_rp_unpair_device अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण;

#घोषणा MGMT_OP_USER_CONFIRM_REPLY	0x001C
काष्ठा mgmt_cp_user_confirm_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_USER_CONFIRM_REPLY_SIZE	MGMT_ADDR_INFO_SIZE
काष्ठा mgmt_rp_user_confirm_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_USER_CONFIRM_NEG_REPLY	0x001D
काष्ठा mgmt_cp_user_confirm_neg_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_USER_CONFIRM_NEG_REPLY_SIZE MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_USER_PASSKEY_REPLY	0x001E
काष्ठा mgmt_cp_user_passkey_reply अणु
	काष्ठा mgmt_addr_info addr;
	__le32	passkey;
पूर्ण __packed;
#घोषणा MGMT_USER_PASSKEY_REPLY_SIZE	(MGMT_ADDR_INFO_SIZE + 4)
काष्ठा mgmt_rp_user_passkey_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_USER_PASSKEY_NEG_REPLY	0x001F
काष्ठा mgmt_cp_user_passkey_neg_reply अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_USER_PASSKEY_NEG_REPLY_SIZE MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_READ_LOCAL_OOB_DATA	0x0020
#घोषणा MGMT_READ_LOCAL_OOB_DATA_SIZE	0
काष्ठा mgmt_rp_पढ़ो_local_oob_data अणु
	__u8	hash192[16];
	__u8	अक्रम192[16];
	__u8	hash256[16];
	__u8	अक्रम256[16];
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_REMOTE_OOB_DATA	0x0021
काष्ठा mgmt_cp_add_remote_oob_data अणु
	काष्ठा mgmt_addr_info addr;
	__u8	hash[16];
	__u8	अक्रम[16];
पूर्ण __packed;
#घोषणा MGMT_ADD_REMOTE_OOB_DATA_SIZE	(MGMT_ADDR_INFO_SIZE + 32)
काष्ठा mgmt_cp_add_remote_oob_ext_data अणु
	काष्ठा mgmt_addr_info addr;
	__u8	hash192[16];
	__u8	अक्रम192[16];
	__u8	hash256[16];
	__u8	अक्रम256[16];
पूर्ण __packed;
#घोषणा MGMT_ADD_REMOTE_OOB_EXT_DATA_SIZE (MGMT_ADDR_INFO_SIZE + 64)

#घोषणा MGMT_OP_REMOVE_REMOTE_OOB_DATA	0x0022
काष्ठा mgmt_cp_हटाओ_remote_oob_data अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_REMOVE_REMOTE_OOB_DATA_SIZE MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_START_DISCOVERY		0x0023
काष्ठा mgmt_cp_start_discovery अणु
	__u8 type;
पूर्ण __packed;
#घोषणा MGMT_START_DISCOVERY_SIZE	1

#घोषणा MGMT_OP_STOP_DISCOVERY		0x0024
काष्ठा mgmt_cp_stop_discovery अणु
	__u8 type;
पूर्ण __packed;
#घोषणा MGMT_STOP_DISCOVERY_SIZE	1

#घोषणा MGMT_OP_CONFIRM_NAME		0x0025
काष्ठा mgmt_cp_confirm_name अणु
	काष्ठा mgmt_addr_info addr;
	__u8	name_known;
पूर्ण __packed;
#घोषणा MGMT_CONFIRM_NAME_SIZE		(MGMT_ADDR_INFO_SIZE + 1)
काष्ठा mgmt_rp_confirm_name अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_OP_BLOCK_DEVICE		0x0026
काष्ठा mgmt_cp_block_device अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_BLOCK_DEVICE_SIZE		MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_UNBLOCK_DEVICE		0x0027
काष्ठा mgmt_cp_unblock_device अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_UNBLOCK_DEVICE_SIZE	MGMT_ADDR_INFO_SIZE

#घोषणा MGMT_OP_SET_DEVICE_ID		0x0028
काष्ठा mgmt_cp_set_device_id अणु
	__le16	source;
	__le16	venकरोr;
	__le16	product;
	__le16	version;
पूर्ण __packed;
#घोषणा MGMT_SET_DEVICE_ID_SIZE		8

#घोषणा MGMT_OP_SET_ADVERTISING		0x0029

#घोषणा MGMT_OP_SET_BREDR		0x002A

#घोषणा MGMT_OP_SET_STATIC_ADDRESS	0x002B
काष्ठा mgmt_cp_set_अटल_address अणु
	bdaddr_t bdaddr;
पूर्ण __packed;
#घोषणा MGMT_SET_STATIC_ADDRESS_SIZE	6

#घोषणा MGMT_OP_SET_SCAN_PARAMS		0x002C
काष्ठा mgmt_cp_set_scan_params अणु
	__le16	पूर्णांकerval;
	__le16	winकरोw;
पूर्ण __packed;
#घोषणा MGMT_SET_SCAN_PARAMS_SIZE	4

#घोषणा MGMT_OP_SET_SECURE_CONN		0x002D

#घोषणा MGMT_OP_SET_DEBUG_KEYS		0x002E

#घोषणा MGMT_OP_SET_PRIVACY		0x002F
काष्ठा mgmt_cp_set_privacy अणु
	__u8 privacy;
	__u8 irk[16];
पूर्ण __packed;
#घोषणा MGMT_SET_PRIVACY_SIZE		17

काष्ठा mgmt_irk_info अणु
	काष्ठा mgmt_addr_info addr;
	__u8 val[16];
पूर्ण __packed;

#घोषणा MGMT_OP_LOAD_IRKS		0x0030
काष्ठा mgmt_cp_load_irks अणु
	__le16 irk_count;
	काष्ठा mgmt_irk_info irks[];
पूर्ण __packed;
#घोषणा MGMT_LOAD_IRKS_SIZE		2

#घोषणा MGMT_OP_GET_CONN_INFO		0x0031
काष्ठा mgmt_cp_get_conn_info अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_GET_CONN_INFO_SIZE		MGMT_ADDR_INFO_SIZE
काष्ठा mgmt_rp_get_conn_info अणु
	काष्ठा mgmt_addr_info addr;
	__s8	rssi;
	__s8	tx_घातer;
	__s8	max_tx_घातer;
पूर्ण __packed;

#घोषणा MGMT_OP_GET_CLOCK_INFO		0x0032
काष्ठा mgmt_cp_get_घड़ी_info अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_GET_CLOCK_INFO_SIZE	MGMT_ADDR_INFO_SIZE
काष्ठा mgmt_rp_get_घड़ी_info अणु
	काष्ठा mgmt_addr_info addr;
	__le32  local_घड़ी;
	__le32  piconet_घड़ी;
	__le16  accuracy;
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_DEVICE		0x0033
काष्ठा mgmt_cp_add_device अणु
	काष्ठा mgmt_addr_info addr;
	__u8	action;
पूर्ण __packed;
#घोषणा MGMT_ADD_DEVICE_SIZE		(MGMT_ADDR_INFO_SIZE + 1)

#घोषणा MGMT_OP_REMOVE_DEVICE		0x0034
काष्ठा mgmt_cp_हटाओ_device अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
#घोषणा MGMT_REMOVE_DEVICE_SIZE		MGMT_ADDR_INFO_SIZE

काष्ठा mgmt_conn_param अणु
	काष्ठा mgmt_addr_info addr;
	__le16 min_पूर्णांकerval;
	__le16 max_पूर्णांकerval;
	__le16 latency;
	__le16 समयout;
पूर्ण __packed;

#घोषणा MGMT_OP_LOAD_CONN_PARAM		0x0035
काष्ठा mgmt_cp_load_conn_param अणु
	__le16 param_count;
	काष्ठा mgmt_conn_param params[];
पूर्ण __packed;
#घोषणा MGMT_LOAD_CONN_PARAM_SIZE	2

#घोषणा MGMT_OP_READ_UNCONF_INDEX_LIST	0x0036
#घोषणा MGMT_READ_UNCONF_INDEX_LIST_SIZE 0
काष्ठा mgmt_rp_पढ़ो_unconf_index_list अणु
	__le16	num_controllers;
	__le16	index[];
पूर्ण __packed;

#घोषणा MGMT_OPTION_EXTERNAL_CONFIG	0x00000001
#घोषणा MGMT_OPTION_PUBLIC_ADDRESS	0x00000002

#घोषणा MGMT_OP_READ_CONFIG_INFO	0x0037
#घोषणा MGMT_READ_CONFIG_INFO_SIZE	0
काष्ठा mgmt_rp_पढ़ो_config_info अणु
	__le16	manufacturer;
	__le32	supported_options;
	__le32	missing_options;
पूर्ण __packed;

#घोषणा MGMT_OP_SET_EXTERNAL_CONFIG	0x0038
काष्ठा mgmt_cp_set_बाह्यal_config अणु
	__u8 config;
पूर्ण __packed;
#घोषणा MGMT_SET_EXTERNAL_CONFIG_SIZE	1

#घोषणा MGMT_OP_SET_PUBLIC_ADDRESS	0x0039
काष्ठा mgmt_cp_set_खुला_address अणु
	bdaddr_t bdaddr;
पूर्ण __packed;
#घोषणा MGMT_SET_PUBLIC_ADDRESS_SIZE	6

#घोषणा MGMT_OP_START_SERVICE_DISCOVERY	0x003A
काष्ठा mgmt_cp_start_service_discovery अणु
	__u8 type;
	__s8 rssi;
	__le16 uuid_count;
	__u8 uuids[][16];
पूर्ण __packed;
#घोषणा MGMT_START_SERVICE_DISCOVERY_SIZE 4

#घोषणा MGMT_OP_READ_LOCAL_OOB_EXT_DATA	0x003B
काष्ठा mgmt_cp_पढ़ो_local_oob_ext_data अणु
	__u8 type;
पूर्ण __packed;
#घोषणा MGMT_READ_LOCAL_OOB_EXT_DATA_SIZE 1
काष्ठा mgmt_rp_पढ़ो_local_oob_ext_data अणु
	__u8    type;
	__le16	eir_len;
	__u8	eir[];
पूर्ण __packed;

#घोषणा MGMT_OP_READ_EXT_INDEX_LIST	0x003C
#घोषणा MGMT_READ_EXT_INDEX_LIST_SIZE	0
काष्ठा mgmt_rp_पढ़ो_ext_index_list अणु
	__le16	num_controllers;
	काष्ठा अणु
		__le16 index;
		__u8   type;
		__u8   bus;
	पूर्ण entry[];
पूर्ण __packed;

#घोषणा MGMT_OP_READ_ADV_FEATURES	0x0003D
#घोषणा MGMT_READ_ADV_FEATURES_SIZE	0
काष्ठा mgmt_rp_पढ़ो_adv_features अणु
	__le32 supported_flags;
	__u8   max_adv_data_len;
	__u8   max_scan_rsp_len;
	__u8   max_instances;
	__u8   num_instances;
	__u8   instance[];
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_ADVERTISING		0x003E
काष्ठा mgmt_cp_add_advertising अणु
	__u8	instance;
	__le32	flags;
	__le16	duration;
	__le16	समयout;
	__u8	adv_data_len;
	__u8	scan_rsp_len;
	__u8	data[];
पूर्ण __packed;
#घोषणा MGMT_ADD_ADVERTISING_SIZE	11
काष्ठा mgmt_rp_add_advertising अणु
	__u8	instance;
पूर्ण __packed;

#घोषणा MGMT_ADV_FLAG_CONNECTABLE	BIT(0)
#घोषणा MGMT_ADV_FLAG_DISCOV		BIT(1)
#घोषणा MGMT_ADV_FLAG_LIMITED_DISCOV	BIT(2)
#घोषणा MGMT_ADV_FLAG_MANAGED_FLAGS	BIT(3)
#घोषणा MGMT_ADV_FLAG_TX_POWER		BIT(4)
#घोषणा MGMT_ADV_FLAG_APPEARANCE	BIT(5)
#घोषणा MGMT_ADV_FLAG_LOCAL_NAME	BIT(6)
#घोषणा MGMT_ADV_FLAG_SEC_1M 		BIT(7)
#घोषणा MGMT_ADV_FLAG_SEC_2M 		BIT(8)
#घोषणा MGMT_ADV_FLAG_SEC_CODED 	BIT(9)
#घोषणा MGMT_ADV_FLAG_CAN_SET_TX_POWER	BIT(10)
#घोषणा MGMT_ADV_FLAG_HW_OFFLOAD	BIT(11)
#घोषणा MGMT_ADV_PARAM_DURATION		BIT(12)
#घोषणा MGMT_ADV_PARAM_TIMEOUT		BIT(13)
#घोषणा MGMT_ADV_PARAM_INTERVALS	BIT(14)
#घोषणा MGMT_ADV_PARAM_TX_POWER		BIT(15)
#घोषणा MGMT_ADV_PARAM_SCAN_RSP		BIT(16)

#घोषणा MGMT_ADV_FLAG_SEC_MASK	(MGMT_ADV_FLAG_SEC_1M | MGMT_ADV_FLAG_SEC_2M | \
				 MGMT_ADV_FLAG_SEC_CODED)

#घोषणा MGMT_OP_REMOVE_ADVERTISING	0x003F
काष्ठा mgmt_cp_हटाओ_advertising अणु
	__u8	instance;
पूर्ण __packed;
#घोषणा MGMT_REMOVE_ADVERTISING_SIZE	1
काष्ठा mgmt_rp_हटाओ_advertising अणु
	__u8	instance;
पूर्ण __packed;

#घोषणा MGMT_OP_GET_ADV_SIZE_INFO	0x0040
काष्ठा mgmt_cp_get_adv_size_info अणु
	__u8	instance;
	__le32	flags;
पूर्ण __packed;
#घोषणा MGMT_GET_ADV_SIZE_INFO_SIZE	5
काष्ठा mgmt_rp_get_adv_size_info अणु
	__u8	instance;
	__le32	flags;
	__u8	max_adv_data_len;
	__u8	max_scan_rsp_len;
पूर्ण __packed;

#घोषणा MGMT_OP_START_LIMITED_DISCOVERY	0x0041

#घोषणा MGMT_OP_READ_EXT_INFO		0x0042
#घोषणा MGMT_READ_EXT_INFO_SIZE		0
काष्ठा mgmt_rp_पढ़ो_ext_info अणु
	bdaddr_t bdaddr;
	__u8     version;
	__le16   manufacturer;
	__le32   supported_settings;
	__le32   current_settings;
	__le16   eir_len;
	__u8     eir[];
पूर्ण __packed;

#घोषणा MGMT_OP_SET_APPEARANCE		0x0043
काष्ठा mgmt_cp_set_appearance अणु
	__le16	appearance;
पूर्ण __packed;
#घोषणा MGMT_SET_APPEARANCE_SIZE	2

#घोषणा MGMT_OP_GET_PHY_CONFIGURATION	0x0044
काष्ठा mgmt_rp_get_phy_configuration अणु
	__le32	supported_phys;
	__le32	configurable_phys;
	__le32	selected_phys;
पूर्ण __packed;
#घोषणा MGMT_GET_PHY_CONFIGURATION_SIZE	0

#घोषणा MGMT_PHY_BR_1M_1SLOT	0x00000001
#घोषणा MGMT_PHY_BR_1M_3SLOT	0x00000002
#घोषणा MGMT_PHY_BR_1M_5SLOT	0x00000004
#घोषणा MGMT_PHY_EDR_2M_1SLOT	0x00000008
#घोषणा MGMT_PHY_EDR_2M_3SLOT	0x00000010
#घोषणा MGMT_PHY_EDR_2M_5SLOT	0x00000020
#घोषणा MGMT_PHY_EDR_3M_1SLOT	0x00000040
#घोषणा MGMT_PHY_EDR_3M_3SLOT	0x00000080
#घोषणा MGMT_PHY_EDR_3M_5SLOT	0x00000100
#घोषणा MGMT_PHY_LE_1M_TX		0x00000200
#घोषणा MGMT_PHY_LE_1M_RX		0x00000400
#घोषणा MGMT_PHY_LE_2M_TX		0x00000800
#घोषणा MGMT_PHY_LE_2M_RX		0x00001000
#घोषणा MGMT_PHY_LE_CODED_TX	0x00002000
#घोषणा MGMT_PHY_LE_CODED_RX	0x00004000

#घोषणा MGMT_PHY_BREDR_MASK (MGMT_PHY_BR_1M_1SLOT | MGMT_PHY_BR_1M_3SLOT | \
			     MGMT_PHY_BR_1M_5SLOT | MGMT_PHY_EDR_2M_1SLOT | \
			     MGMT_PHY_EDR_2M_3SLOT | MGMT_PHY_EDR_2M_5SLOT | \
			     MGMT_PHY_EDR_3M_1SLOT | MGMT_PHY_EDR_3M_3SLOT | \
			     MGMT_PHY_EDR_3M_5SLOT)
#घोषणा MGMT_PHY_LE_MASK (MGMT_PHY_LE_1M_TX | MGMT_PHY_LE_1M_RX | \
			  MGMT_PHY_LE_2M_TX | MGMT_PHY_LE_2M_RX | \
			  MGMT_PHY_LE_CODED_TX | MGMT_PHY_LE_CODED_RX)
#घोषणा MGMT_PHY_LE_TX_MASK (MGMT_PHY_LE_1M_TX | MGMT_PHY_LE_2M_TX | \
			     MGMT_PHY_LE_CODED_TX)
#घोषणा MGMT_PHY_LE_RX_MASK (MGMT_PHY_LE_1M_RX | MGMT_PHY_LE_2M_RX | \
			     MGMT_PHY_LE_CODED_RX)

#घोषणा MGMT_OP_SET_PHY_CONFIGURATION	0x0045
काष्ठा mgmt_cp_set_phy_configuration अणु
	__le32	selected_phys;
पूर्ण __packed;
#घोषणा MGMT_SET_PHY_CONFIGURATION_SIZE	4

#घोषणा MGMT_OP_SET_BLOCKED_KEYS	0x0046

#घोषणा HCI_BLOCKED_KEY_TYPE_LINKKEY	0x00
#घोषणा HCI_BLOCKED_KEY_TYPE_LTK	0x01
#घोषणा HCI_BLOCKED_KEY_TYPE_IRK	0x02

काष्ठा mgmt_blocked_key_info अणु
	__u8 type;
	__u8 val[16];
पूर्ण __packed;

काष्ठा mgmt_cp_set_blocked_keys अणु
	__le16 key_count;
	काष्ठा mgmt_blocked_key_info keys[];
पूर्ण __packed;
#घोषणा MGMT_OP_SET_BLOCKED_KEYS_SIZE 2

#घोषणा MGMT_OP_SET_WIDEBAND_SPEECH	0x0047

#घोषणा MGMT_CAP_SEC_FLAGS		0x01
#घोषणा MGMT_CAP_MAX_ENC_KEY_SIZE	0x02
#घोषणा MGMT_CAP_SMP_MAX_ENC_KEY_SIZE	0x03
#घोषणा MGMT_CAP_LE_TX_PWR		0x04

#घोषणा MGMT_OP_READ_CONTROLLER_CAP	0x0048
#घोषणा MGMT_READ_CONTROLLER_CAP_SIZE	0
काष्ठा mgmt_rp_पढ़ो_controller_cap अणु
	__le16   cap_len;
	__u8     cap[0];
पूर्ण __packed;

#घोषणा MGMT_OP_READ_EXP_FEATURES_INFO	0x0049
#घोषणा MGMT_READ_EXP_FEATURES_INFO_SIZE 0
काष्ठा mgmt_rp_पढ़ो_exp_features_info अणु
	__le16 feature_count;
	काष्ठा अणु
		__u8   uuid[16];
		__le32 flags;
	पूर्ण features[];
पूर्ण __packed;

#घोषणा MGMT_OP_SET_EXP_FEATURE		0x004a
काष्ठा mgmt_cp_set_exp_feature अणु
	__u8   uuid[16];
	__u8   param[];
पूर्ण __packed;
#घोषणा MGMT_SET_EXP_FEATURE_SIZE	16
काष्ठा mgmt_rp_set_exp_feature अणु
	__u8   uuid[16];
	__le32 flags;
पूर्ण __packed;

#घोषणा MGMT_OP_READ_DEF_SYSTEM_CONFIG	0x004b
#घोषणा MGMT_READ_DEF_SYSTEM_CONFIG_SIZE	0

#घोषणा MGMT_OP_SET_DEF_SYSTEM_CONFIG	0x004c
#घोषणा MGMT_SET_DEF_SYSTEM_CONFIG_SIZE		0

#घोषणा MGMT_OP_READ_DEF_RUNTIME_CONFIG	0x004d
#घोषणा MGMT_READ_DEF_RUNTIME_CONFIG_SIZE	0

#घोषणा MGMT_OP_SET_DEF_RUNTIME_CONFIG	0x004e
#घोषणा MGMT_SET_DEF_RUNTIME_CONFIG_SIZE	0

#घोषणा MGMT_OP_GET_DEVICE_FLAGS	0x004F
#घोषणा MGMT_GET_DEVICE_FLAGS_SIZE	7
काष्ठा mgmt_cp_get_device_flags अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;
काष्ठा mgmt_rp_get_device_flags अणु
	काष्ठा mgmt_addr_info addr;
	__le32 supported_flags;
	__le32 current_flags;
पूर्ण __packed;

#घोषणा MGMT_OP_SET_DEVICE_FLAGS	0x0050
#घोषणा MGMT_SET_DEVICE_FLAGS_SIZE	11
काष्ठा mgmt_cp_set_device_flags अणु
	काष्ठा mgmt_addr_info addr;
	__le32 current_flags;
पूर्ण __packed;
काष्ठा mgmt_rp_set_device_flags अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_ADV_MONITOR_FEATURE_MASK_OR_PATTERNS    BIT(0)

#घोषणा MGMT_OP_READ_ADV_MONITOR_FEATURES	0x0051
#घोषणा MGMT_READ_ADV_MONITOR_FEATURES_SIZE	0
काष्ठा mgmt_rp_पढ़ो_adv_monitor_features अणु
	__le32 supported_features;
	__le32 enabled_features;
	__le16 max_num_handles;
	__u8 max_num_patterns;
	__le16 num_handles;
	__le16 handles[];
पूर्ण  __packed;

काष्ठा mgmt_adv_pattern अणु
	__u8 ad_type;
	__u8 offset;
	__u8 length;
	__u8 value[31];
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_ADV_PATTERNS_MONITOR	0x0052
काष्ठा mgmt_cp_add_adv_patterns_monitor अणु
	__u8 pattern_count;
	काष्ठा mgmt_adv_pattern patterns[];
पूर्ण __packed;
#घोषणा MGMT_ADD_ADV_PATTERNS_MONITOR_SIZE	1
काष्ठा mgmt_rp_add_adv_patterns_monitor अणु
	__le16 monitor_handle;
पूर्ण __packed;

#घोषणा MGMT_OP_REMOVE_ADV_MONITOR		0x0053
काष्ठा mgmt_cp_हटाओ_adv_monitor अणु
	__le16 monitor_handle;
पूर्ण __packed;
#घोषणा MGMT_REMOVE_ADV_MONITOR_SIZE		2
काष्ठा mgmt_rp_हटाओ_adv_monitor अणु
	__le16 monitor_handle;
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_EXT_ADV_PARAMS		0x0054
काष्ठा mgmt_cp_add_ext_adv_params अणु
	__u8	instance;
	__le32	flags;
	__le16	duration;
	__le16	समयout;
	__le32	min_पूर्णांकerval;
	__le32	max_पूर्णांकerval;
	__s8	tx_घातer;
पूर्ण __packed;
#घोषणा MGMT_ADD_EXT_ADV_PARAMS_MIN_SIZE	18
काष्ठा mgmt_rp_add_ext_adv_params अणु
	__u8	instance;
	__s8	tx_घातer;
	__u8	max_adv_data_len;
	__u8	max_scan_rsp_len;
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_EXT_ADV_DATA		0x0055
काष्ठा mgmt_cp_add_ext_adv_data अणु
	__u8	instance;
	__u8	adv_data_len;
	__u8	scan_rsp_len;
	__u8	data[];
पूर्ण __packed;
#घोषणा MGMT_ADD_EXT_ADV_DATA_SIZE	3
काष्ठा mgmt_rp_add_ext_adv_data अणु
	__u8	instance;
पूर्ण __packed;

काष्ठा mgmt_adv_rssi_thresholds अणु
	__s8	high_threshold;
	__le16	high_threshold_समयout;
	__s8	low_threshold;
	__le16	low_threshold_समयout;
	__u8	sampling_period;
पूर्ण __packed;

#घोषणा MGMT_OP_ADD_ADV_PATTERNS_MONITOR_RSSI	0x0056
काष्ठा mgmt_cp_add_adv_patterns_monitor_rssi अणु
	काष्ठा mgmt_adv_rssi_thresholds rssi;
	__u8	pattern_count;
	काष्ठा mgmt_adv_pattern patterns[];
पूर्ण __packed;
#घोषणा MGMT_ADD_ADV_PATTERNS_MONITOR_RSSI_SIZE	8

#घोषणा MGMT_EV_CMD_COMPLETE		0x0001
काष्ठा mgmt_ev_cmd_complete अणु
	__le16	opcode;
	__u8	status;
	__u8	data[];
पूर्ण __packed;

#घोषणा MGMT_EV_CMD_STATUS		0x0002
काष्ठा mgmt_ev_cmd_status अणु
	__le16	opcode;
	__u8	status;
पूर्ण __packed;

#घोषणा MGMT_EV_CONTROLLER_ERROR	0x0003
काष्ठा mgmt_ev_controller_error अणु
	__u8	error_code;
पूर्ण __packed;

#घोषणा MGMT_EV_INDEX_ADDED		0x0004

#घोषणा MGMT_EV_INDEX_REMOVED		0x0005

#घोषणा MGMT_EV_NEW_SETTINGS		0x0006

#घोषणा MGMT_EV_CLASS_OF_DEV_CHANGED	0x0007
काष्ठा mgmt_ev_class_of_dev_changed अणु
	__u8	dev_class[3];
पूर्ण;

#घोषणा MGMT_EV_LOCAL_NAME_CHANGED	0x0008
काष्ठा mgmt_ev_local_name_changed अणु
	__u8	name[MGMT_MAX_NAME_LENGTH];
	__u8	लघु_name[MGMT_MAX_SHORT_NAME_LENGTH];
पूर्ण __packed;

#घोषणा MGMT_EV_NEW_LINK_KEY		0x0009
काष्ठा mgmt_ev_new_link_key अणु
	__u8	store_hपूर्णांक;
	काष्ठा mgmt_link_key_info key;
पूर्ण __packed;

#घोषणा MGMT_EV_NEW_LONG_TERM_KEY	0x000A
काष्ठा mgmt_ev_new_दीर्घ_term_key अणु
	__u8	store_hपूर्णांक;
	काष्ठा mgmt_ltk_info key;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_CONNECTED	0x000B
काष्ठा mgmt_ev_device_connected अणु
	काष्ठा mgmt_addr_info addr;
	__le32	flags;
	__le16	eir_len;
	__u8	eir[];
पूर्ण __packed;

#घोषणा MGMT_DEV_DISCONN_UNKNOWN	0x00
#घोषणा MGMT_DEV_DISCONN_TIMEOUT	0x01
#घोषणा MGMT_DEV_DISCONN_LOCAL_HOST	0x02
#घोषणा MGMT_DEV_DISCONN_REMOTE		0x03
#घोषणा MGMT_DEV_DISCONN_AUTH_FAILURE	0x04
#घोषणा MGMT_DEV_DISCONN_LOCAL_HOST_SUSPEND	0x05

#घोषणा MGMT_EV_DEVICE_DISCONNECTED	0x000C
काष्ठा mgmt_ev_device_disconnected अणु
	काष्ठा mgmt_addr_info addr;
	__u8	reason;
पूर्ण __packed;

#घोषणा MGMT_EV_CONNECT_FAILED		0x000D
काष्ठा mgmt_ev_connect_failed अणु
	काष्ठा mgmt_addr_info addr;
	__u8	status;
पूर्ण __packed;

#घोषणा MGMT_EV_PIN_CODE_REQUEST	0x000E
काष्ठा mgmt_ev_pin_code_request अणु
	काष्ठा mgmt_addr_info addr;
	__u8	secure;
पूर्ण __packed;

#घोषणा MGMT_EV_USER_CONFIRM_REQUEST	0x000F
काष्ठा mgmt_ev_user_confirm_request अणु
	काष्ठा mgmt_addr_info addr;
	__u8	confirm_hपूर्णांक;
	__le32	value;
पूर्ण __packed;

#घोषणा MGMT_EV_USER_PASSKEY_REQUEST	0x0010
काष्ठा mgmt_ev_user_passkey_request अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_EV_AUTH_FAILED		0x0011
काष्ठा mgmt_ev_auth_failed अणु
	काष्ठा mgmt_addr_info addr;
	__u8	status;
पूर्ण __packed;

#घोषणा MGMT_DEV_FOUND_CONFIRM_NAME    0x01
#घोषणा MGMT_DEV_FOUND_LEGACY_PAIRING  0x02
#घोषणा MGMT_DEV_FOUND_NOT_CONNECTABLE 0x04

#घोषणा MGMT_EV_DEVICE_FOUND		0x0012
काष्ठा mgmt_ev_device_found अणु
	काष्ठा mgmt_addr_info addr;
	__s8	rssi;
	__le32	flags;
	__le16	eir_len;
	__u8	eir[];
पूर्ण __packed;

#घोषणा MGMT_EV_DISCOVERING		0x0013
काष्ठा mgmt_ev_discovering अणु
	__u8	type;
	__u8	discovering;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_BLOCKED		0x0014
काष्ठा mgmt_ev_device_blocked अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_UNBLOCKED	0x0015
काष्ठा mgmt_ev_device_unblocked अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_UNPAIRED		0x0016
काष्ठा mgmt_ev_device_unpaired अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_EV_PASSKEY_NOTIFY		0x0017
काष्ठा mgmt_ev_passkey_notअगरy अणु
	काष्ठा mgmt_addr_info addr;
	__le32	passkey;
	__u8	entered;
पूर्ण __packed;

#घोषणा MGMT_EV_NEW_IRK			0x0018
काष्ठा mgmt_ev_new_irk अणु
	__u8     store_hपूर्णांक;
	bdaddr_t rpa;
	काष्ठा mgmt_irk_info irk;
पूर्ण __packed;

#घोषणा MGMT_CSRK_LOCAL_UNAUTHENTICATED		0x00
#घोषणा MGMT_CSRK_REMOTE_UNAUTHENTICATED	0x01
#घोषणा MGMT_CSRK_LOCAL_AUTHENTICATED		0x02
#घोषणा MGMT_CSRK_REMOTE_AUTHENTICATED		0x03

काष्ठा mgmt_csrk_info अणु
	काष्ठा mgmt_addr_info addr;
	__u8 type;
	__u8 val[16];
पूर्ण __packed;

#घोषणा MGMT_EV_NEW_CSRK		0x0019
काष्ठा mgmt_ev_new_csrk अणु
	__u8 store_hपूर्णांक;
	काष्ठा mgmt_csrk_info key;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_ADDED		0x001a
काष्ठा mgmt_ev_device_added अणु
	काष्ठा mgmt_addr_info addr;
	__u8 action;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_REMOVED		0x001b
काष्ठा mgmt_ev_device_हटाओd अणु
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_EV_NEW_CONN_PARAM		0x001c
काष्ठा mgmt_ev_new_conn_param अणु
	काष्ठा mgmt_addr_info addr;
	__u8 store_hपूर्णांक;
	__le16 min_पूर्णांकerval;
	__le16 max_पूर्णांकerval;
	__le16 latency;
	__le16 समयout;
पूर्ण __packed;

#घोषणा MGMT_EV_UNCONF_INDEX_ADDED	0x001d

#घोषणा MGMT_EV_UNCONF_INDEX_REMOVED	0x001e

#घोषणा MGMT_EV_NEW_CONFIG_OPTIONS	0x001f

काष्ठा mgmt_ev_ext_index अणु
	__u8 type;
	__u8 bus;
पूर्ण __packed;

#घोषणा MGMT_EV_EXT_INDEX_ADDED		0x0020

#घोषणा MGMT_EV_EXT_INDEX_REMOVED	0x0021

#घोषणा MGMT_EV_LOCAL_OOB_DATA_UPDATED	0x0022
काष्ठा mgmt_ev_local_oob_data_updated अणु
	__u8    type;
	__le16	eir_len;
	__u8	eir[];
पूर्ण __packed;

#घोषणा MGMT_EV_ADVERTISING_ADDED	0x0023
काष्ठा mgmt_ev_advertising_added अणु
	__u8    instance;
पूर्ण __packed;

#घोषणा MGMT_EV_ADVERTISING_REMOVED	0x0024
काष्ठा mgmt_ev_advertising_हटाओd अणु
	__u8    instance;
पूर्ण __packed;

#घोषणा MGMT_EV_EXT_INFO_CHANGED	0x0025
काष्ठा mgmt_ev_ext_info_changed अणु
	__le16	eir_len;
	__u8	eir[];
पूर्ण __packed;

#घोषणा MGMT_EV_PHY_CONFIGURATION_CHANGED	0x0026
काष्ठा mgmt_ev_phy_configuration_changed अणु
	__le32	selected_phys;
पूर्ण __packed;

#घोषणा MGMT_EV_EXP_FEATURE_CHANGED	0x0027
काष्ठा mgmt_ev_exp_feature_changed अणु
	__u8	uuid[16];
	__le32	flags;
पूर्ण __packed;

#घोषणा MGMT_EV_DEVICE_FLAGS_CHANGED		0x002a
काष्ठा mgmt_ev_device_flags_changed अणु
	काष्ठा mgmt_addr_info addr;
	__le32 supported_flags;
	__le32 current_flags;
पूर्ण __packed;

#घोषणा MGMT_EV_ADV_MONITOR_ADDED	0x002b
काष्ठा mgmt_ev_adv_monitor_added अणु
	__le16 monitor_handle;
पूर्ण  __packed;

#घोषणा MGMT_EV_ADV_MONITOR_REMOVED	0x002c
काष्ठा mgmt_ev_adv_monitor_हटाओd अणु
	__le16 monitor_handle;
पूर्ण  __packed;

#घोषणा MGMT_EV_CONTROLLER_SUSPEND		0x002d
काष्ठा mgmt_ev_controller_suspend अणु
	__u8	suspend_state;
पूर्ण __packed;

#घोषणा MGMT_EV_CONTROLLER_RESUME		0x002e
काष्ठा mgmt_ev_controller_resume अणु
	__u8	wake_reason;
	काष्ठा mgmt_addr_info addr;
पूर्ण __packed;

#घोषणा MGMT_WAKE_REASON_NON_BT_WAKE		0x0
#घोषणा MGMT_WAKE_REASON_UNEXPECTED		0x1
#घोषणा MGMT_WAKE_REASON_REMOTE_WAKE		0x2
