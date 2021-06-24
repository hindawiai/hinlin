<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_PDR_HELPER_INTERNAL__
#घोषणा __QCOM_PDR_HELPER_INTERNAL__

#समावेश <linux/soc/qcom/pdr.h>

#घोषणा SERVREG_LOCATOR_SERVICE				0x40
#घोषणा SERVREG_NOTIFIER_SERVICE			0x42

#घोषणा SERVREG_REGISTER_LISTENER_REQ			0x20
#घोषणा SERVREG_GET_DOMAIN_LIST_REQ			0x21
#घोषणा SERVREG_STATE_UPDATED_IND_ID			0x22
#घोषणा SERVREG_SET_ACK_REQ				0x23
#घोषणा SERVREG_RESTART_PD_REQ				0x24

#घोषणा SERVREG_DOMAIN_LIST_LENGTH			32
#घोषणा SERVREG_RESTART_PD_REQ_MAX_LEN			67
#घोषणा SERVREG_REGISTER_LISTENER_REQ_LEN		71
#घोषणा SERVREG_SET_ACK_REQ_LEN				72
#घोषणा SERVREG_GET_DOMAIN_LIST_REQ_MAX_LEN		74
#घोषणा SERVREG_STATE_UPDATED_IND_MAX_LEN		79
#घोषणा SERVREG_GET_DOMAIN_LIST_RESP_MAX_LEN		2389

काष्ठा servreg_location_entry अणु
	अक्षर name[SERVREG_NAME_LENGTH + 1];
	u8 service_data_valid;
	u32 service_data;
	u32 instance;
पूर्ण;

काष्ठा qmi_elem_info servreg_location_entry_ei[] = अणु
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा servreg_location_entry,
					   name),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा servreg_location_entry,
					   instance),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा servreg_location_entry,
					   service_data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा servreg_location_entry,
					   service_data),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_get_करोमुख्य_list_req अणु
	अक्षर service_name[SERVREG_NAME_LENGTH + 1];
	u8 करोमुख्य_offset_valid;
	u32 करोमुख्य_offset;
पूर्ण;

काष्ठा qmi_elem_info servreg_get_करोमुख्य_list_req_ei[] = अणु
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_req,
					   service_name),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_req,
					   करोमुख्य_offset_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_req,
					   करोमुख्य_offset),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_get_करोमुख्य_list_resp अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 total_करोमुख्यs_valid;
	u16 total_करोमुख्यs;
	u8 db_rev_count_valid;
	u16 db_rev_count;
	u8 करोमुख्य_list_valid;
	u32 करोमुख्य_list_len;
	काष्ठा servreg_location_entry करोमुख्य_list[SERVREG_DOMAIN_LIST_LENGTH];
पूर्ण;

काष्ठा qmi_elem_info servreg_get_करोमुख्य_list_resp_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   total_करोमुख्यs_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   total_करोमुख्यs),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   db_rev_count_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   db_rev_count),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   करोमुख्य_list_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   करोमुख्य_list_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = SERVREG_DOMAIN_LIST_LENGTH,
		.elem_size      = माप(काष्ठा servreg_location_entry),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा servreg_get_करोमुख्य_list_resp,
					   करोमुख्य_list),
		.ei_array      = servreg_location_entry_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_रेजिस्टर_listener_req अणु
	u8 enable;
	अक्षर service_path[SERVREG_NAME_LENGTH + 1];
पूर्ण;

काष्ठा qmi_elem_info servreg_रेजिस्टर_listener_req_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा servreg_रेजिस्टर_listener_req,
					   enable),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_रेजिस्टर_listener_req,
					   service_path),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_रेजिस्टर_listener_resp अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 curr_state_valid;
	क्रमागत servreg_service_state curr_state;
पूर्ण;

काष्ठा qmi_elem_info servreg_रेजिस्टर_listener_resp_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_रेजिस्टर_listener_resp,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_रेजिस्टर_listener_resp,
					   curr_state_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत servreg_service_state),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा servreg_रेजिस्टर_listener_resp,
					   curr_state),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_restart_pd_req अणु
	अक्षर service_path[SERVREG_NAME_LENGTH + 1];
पूर्ण;

काष्ठा qmi_elem_info servreg_restart_pd_req_ei[] = अणु
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा servreg_restart_pd_req,
					   service_path),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_restart_pd_resp अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

काष्ठा qmi_elem_info servreg_restart_pd_resp_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_restart_pd_resp,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_state_updated_ind अणु
	क्रमागत servreg_service_state curr_state;
	अक्षर service_path[SERVREG_NAME_LENGTH + 1];
	u16 transaction_id;
पूर्ण;

काष्ठा qmi_elem_info servreg_state_updated_ind_ei[] = अणु
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा servreg_state_updated_ind,
					   curr_state),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_state_updated_ind,
					   service_path),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा servreg_state_updated_ind,
					   transaction_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_set_ack_req अणु
	अक्षर service_path[SERVREG_NAME_LENGTH + 1];
	u16 transaction_id;
पूर्ण;

काष्ठा qmi_elem_info servreg_set_ack_req_ei[] = अणु
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = SERVREG_NAME_LENGTH + 1,
		.elem_size      = माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा servreg_set_ack_req,
					   service_path),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_set_ack_req,
					   transaction_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा servreg_set_ack_resp अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

काष्ठा qmi_elem_info servreg_set_ack_resp_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा servreg_set_ack_resp,
					   resp),
		.ei_array       = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#पूर्ण_अगर
