<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright (C) 2020 Google Corporation
 */

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "mgmt_util.h"
#समावेश "mgmt_config.h"

#घोषणा HDEV_PARAM_U16(_param_name_) \
	काष्ठा अणु\
		काष्ठा mgmt_tlv entry; \
		__le16 value; \
	पूर्ण __packed _param_name_

#घोषणा HDEV_PARAM_U8(_param_name_) \
	काष्ठा अणु\
		काष्ठा mgmt_tlv entry; \
		__u8 value; \
	पूर्ण __packed _param_name_

#घोषणा TLV_SET_U16(_param_code_, _param_name_) \
	अणु \
		अणु cpu_to_le16(_param_code_), माप(__u16) पूर्ण, \
		cpu_to_le16(hdev->_param_name_) \
	पूर्ण

#घोषणा TLV_SET_U8(_param_code_, _param_name_) \
	अणु \
		अणु cpu_to_le16(_param_code_), माप(__u8) पूर्ण, \
		hdev->_param_name_ \
	पूर्ण

#घोषणा TLV_SET_U16_JIFFIES_TO_MSECS(_param_code_, _param_name_) \
	अणु \
		अणु cpu_to_le16(_param_code_), माप(__u16) पूर्ण, \
		cpu_to_le16(jअगरfies_to_msecs(hdev->_param_name_)) \
	पूर्ण

पूर्णांक पढ़ो_def_प्रणाली_config(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 data_len)
अणु
	पूर्णांक ret;
	काष्ठा mgmt_rp_पढ़ो_def_प्रणाली_config अणु
		/* Please see mgmt-api.txt क्रम करोcumentation of these values */
		HDEV_PARAM_U16(def_page_scan_type);
		HDEV_PARAM_U16(def_page_scan_पूर्णांक);
		HDEV_PARAM_U16(def_page_scan_winकरोw);
		HDEV_PARAM_U16(def_inq_scan_type);
		HDEV_PARAM_U16(def_inq_scan_पूर्णांक);
		HDEV_PARAM_U16(def_inq_scan_winकरोw);
		HDEV_PARAM_U16(def_br_lsto);
		HDEV_PARAM_U16(def_page_समयout);
		HDEV_PARAM_U16(snअगरf_min_पूर्णांकerval);
		HDEV_PARAM_U16(snअगरf_max_पूर्णांकerval);
		HDEV_PARAM_U16(le_adv_min_पूर्णांकerval);
		HDEV_PARAM_U16(le_adv_max_पूर्णांकerval);
		HDEV_PARAM_U16(def_multi_adv_rotation_duration);
		HDEV_PARAM_U16(le_scan_पूर्णांकerval);
		HDEV_PARAM_U16(le_scan_winकरोw);
		HDEV_PARAM_U16(le_scan_पूर्णांक_suspend);
		HDEV_PARAM_U16(le_scan_winकरोw_suspend);
		HDEV_PARAM_U16(le_scan_पूर्णांक_discovery);
		HDEV_PARAM_U16(le_scan_winकरोw_discovery);
		HDEV_PARAM_U16(le_scan_पूर्णांक_adv_monitor);
		HDEV_PARAM_U16(le_scan_winकरोw_adv_monitor);
		HDEV_PARAM_U16(le_scan_पूर्णांक_connect);
		HDEV_PARAM_U16(le_scan_winकरोw_connect);
		HDEV_PARAM_U16(le_conn_min_पूर्णांकerval);
		HDEV_PARAM_U16(le_conn_max_पूर्णांकerval);
		HDEV_PARAM_U16(le_conn_latency);
		HDEV_PARAM_U16(le_supv_समयout);
		HDEV_PARAM_U16(def_le_स्वतःconnect_समयout);
		HDEV_PARAM_U16(advmon_allowlist_duration);
		HDEV_PARAM_U16(advmon_no_filter_duration);
		HDEV_PARAM_U8(enable_advmon_पूर्णांकerleave_scan);
	पूर्ण __packed rp = अणु
		TLV_SET_U16(0x0000, def_page_scan_type),
		TLV_SET_U16(0x0001, def_page_scan_पूर्णांक),
		TLV_SET_U16(0x0002, def_page_scan_winकरोw),
		TLV_SET_U16(0x0003, def_inq_scan_type),
		TLV_SET_U16(0x0004, def_inq_scan_पूर्णांक),
		TLV_SET_U16(0x0005, def_inq_scan_winकरोw),
		TLV_SET_U16(0x0006, def_br_lsto),
		TLV_SET_U16(0x0007, def_page_समयout),
		TLV_SET_U16(0x0008, snअगरf_min_पूर्णांकerval),
		TLV_SET_U16(0x0009, snअगरf_max_पूर्णांकerval),
		TLV_SET_U16(0x000a, le_adv_min_पूर्णांकerval),
		TLV_SET_U16(0x000b, le_adv_max_पूर्णांकerval),
		TLV_SET_U16(0x000c, def_multi_adv_rotation_duration),
		TLV_SET_U16(0x000d, le_scan_पूर्णांकerval),
		TLV_SET_U16(0x000e, le_scan_winकरोw),
		TLV_SET_U16(0x000f, le_scan_पूर्णांक_suspend),
		TLV_SET_U16(0x0010, le_scan_winकरोw_suspend),
		TLV_SET_U16(0x0011, le_scan_पूर्णांक_discovery),
		TLV_SET_U16(0x0012, le_scan_winकरोw_discovery),
		TLV_SET_U16(0x0013, le_scan_पूर्णांक_adv_monitor),
		TLV_SET_U16(0x0014, le_scan_winकरोw_adv_monitor),
		TLV_SET_U16(0x0015, le_scan_पूर्णांक_connect),
		TLV_SET_U16(0x0016, le_scan_winकरोw_connect),
		TLV_SET_U16(0x0017, le_conn_min_पूर्णांकerval),
		TLV_SET_U16(0x0018, le_conn_max_पूर्णांकerval),
		TLV_SET_U16(0x0019, le_conn_latency),
		TLV_SET_U16(0x001a, le_supv_समयout),
		TLV_SET_U16_JIFFIES_TO_MSECS(0x001b,
					     def_le_स्वतःconnect_समयout),
		TLV_SET_U16(0x001d, advmon_allowlist_duration),
		TLV_SET_U16(0x001e, advmon_no_filter_duration),
		TLV_SET_U8(0x001f, enable_advmon_पूर्णांकerleave_scan),
	पूर्ण;

	bt_dev_dbg(hdev, "sock %p", sk);

	ret = mgmt_cmd_complete(sk, hdev->id,
				MGMT_OP_READ_DEF_SYSTEM_CONFIG,
				0, &rp, माप(rp));
	वापस ret;
पूर्ण

#घोषणा TO_TLV(x)		((काष्ठा mgmt_tlv *)(x))
#घोषणा TLV_GET_LE16(tlv)	le16_to_cpu(*((__le16 *)(TO_TLV(tlv)->value)))
#घोषणा TLV_GET_U8(tlv)		(*((__u8 *)(TO_TLV(tlv)->value)))

पूर्णांक set_def_प्रणाली_config(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			  u16 data_len)
अणु
	u16 buffer_left = data_len;
	u8 *buffer = data;

	अगर (buffer_left < माप(काष्ठा mgmt_tlv)) अणु
		वापस mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_DEF_SYSTEM_CONFIG,
				       MGMT_STATUS_INVALID_PARAMS);
	पूर्ण

	/* First pass to validate the tlv */
	जबतक (buffer_left >= माप(काष्ठा mgmt_tlv)) अणु
		स्थिर u8 len = TO_TLV(buffer)->length;
		माप_प्रकार exp_type_len;
		स्थिर u16 exp_len = माप(काष्ठा mgmt_tlv) +
				    len;
		स्थिर u16 type = le16_to_cpu(TO_TLV(buffer)->type);

		अगर (buffer_left < exp_len) अणु
			bt_dev_warn(hdev, "invalid len left %d, exp >= %d",
				    buffer_left, exp_len);

			वापस mgmt_cmd_status(sk, hdev->id,
					MGMT_OP_SET_DEF_SYSTEM_CONFIG,
					MGMT_STATUS_INVALID_PARAMS);
		पूर्ण

		/* Please see mgmt-api.txt क्रम करोcumentation of these values */
		चयन (type) अणु
		हाल 0x0000:
		हाल 0x0001:
		हाल 0x0002:
		हाल 0x0003:
		हाल 0x0004:
		हाल 0x0005:
		हाल 0x0006:
		हाल 0x0007:
		हाल 0x0008:
		हाल 0x0009:
		हाल 0x000a:
		हाल 0x000b:
		हाल 0x000c:
		हाल 0x000d:
		हाल 0x000e:
		हाल 0x000f:
		हाल 0x0010:
		हाल 0x0011:
		हाल 0x0012:
		हाल 0x0013:
		हाल 0x0014:
		हाल 0x0015:
		हाल 0x0016:
		हाल 0x0017:
		हाल 0x0018:
		हाल 0x0019:
		हाल 0x001a:
		हाल 0x001b:
		हाल 0x001d:
		हाल 0x001e:
			exp_type_len = माप(u16);
			अवरोध;
		हाल 0x001f:
			exp_type_len = माप(u8);
			अवरोध;
		शेष:
			exp_type_len = 0;
			bt_dev_warn(hdev, "unsupported parameter %u", type);
			अवरोध;
		पूर्ण

		अगर (exp_type_len && len != exp_type_len) अणु
			bt_dev_warn(hdev, "invalid length %d, exp %zu for type %d",
				    len, exp_type_len, type);

			वापस mgmt_cmd_status(sk, hdev->id,
				MGMT_OP_SET_DEF_SYSTEM_CONFIG,
				MGMT_STATUS_INVALID_PARAMS);
		पूर्ण

		buffer_left -= exp_len;
		buffer += exp_len;
	पूर्ण

	buffer_left = data_len;
	buffer = data;
	जबतक (buffer_left >= माप(काष्ठा mgmt_tlv)) अणु
		स्थिर u8 len = TO_TLV(buffer)->length;
		स्थिर u16 exp_len = माप(काष्ठा mgmt_tlv) +
				    len;
		स्थिर u16 type = le16_to_cpu(TO_TLV(buffer)->type);

		चयन (type) अणु
		हाल 0x0000:
			hdev->def_page_scan_type = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0001:
			hdev->def_page_scan_पूर्णांक = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0002:
			hdev->def_page_scan_winकरोw = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0003:
			hdev->def_inq_scan_type = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0004:
			hdev->def_inq_scan_पूर्णांक = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0005:
			hdev->def_inq_scan_winकरोw = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0006:
			hdev->def_br_lsto = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0007:
			hdev->def_page_समयout = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0008:
			hdev->snअगरf_min_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0009:
			hdev->snअगरf_max_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000a:
			hdev->le_adv_min_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000b:
			hdev->le_adv_max_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000c:
			hdev->def_multi_adv_rotation_duration =
							   TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000d:
			hdev->le_scan_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000e:
			hdev->le_scan_winकरोw = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x000f:
			hdev->le_scan_पूर्णांक_suspend = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0010:
			hdev->le_scan_winकरोw_suspend = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0011:
			hdev->le_scan_पूर्णांक_discovery = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00012:
			hdev->le_scan_winकरोw_discovery = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00013:
			hdev->le_scan_पूर्णांक_adv_monitor = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00014:
			hdev->le_scan_winकरोw_adv_monitor = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00015:
			hdev->le_scan_पूर्णांक_connect = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00016:
			hdev->le_scan_winकरोw_connect = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00017:
			hdev->le_conn_min_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00018:
			hdev->le_conn_max_पूर्णांकerval = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x00019:
			hdev->le_conn_latency = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0001a:
			hdev->le_supv_समयout = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0001b:
			hdev->def_le_स्वतःconnect_समयout =
					msecs_to_jअगरfies(TLV_GET_LE16(buffer));
			अवरोध;
		हाल 0x0001d:
			hdev->advmon_allowlist_duration = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0001e:
			hdev->advmon_no_filter_duration = TLV_GET_LE16(buffer);
			अवरोध;
		हाल 0x0001f:
			hdev->enable_advmon_पूर्णांकerleave_scan = TLV_GET_U8(buffer);
			अवरोध;
		शेष:
			bt_dev_warn(hdev, "unsupported parameter %u", type);
			अवरोध;
		पूर्ण

		buffer_left -= exp_len;
		buffer += exp_len;
	पूर्ण

	वापस mgmt_cmd_complete(sk, hdev->id,
				 MGMT_OP_SET_DEF_SYSTEM_CONFIG, 0, शून्य, 0);
पूर्ण

पूर्णांक पढ़ो_def_runसमय_config(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			    u16 data_len)
अणु
	bt_dev_dbg(hdev, "sock %p", sk);

	वापस mgmt_cmd_complete(sk, hdev->id,
				 MGMT_OP_READ_DEF_RUNTIME_CONFIG, 0, शून्य, 0);
पूर्ण

पूर्णांक set_def_runसमय_config(काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
			   u16 data_len)
अणु
	bt_dev_dbg(hdev, "sock %p", sk);

	वापस mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEF_SYSTEM_CONFIG,
			       MGMT_STATUS_INVALID_PARAMS);
पूर्ण
