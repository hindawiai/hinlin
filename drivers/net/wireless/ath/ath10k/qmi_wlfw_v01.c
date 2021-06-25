<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/soc/qcom/qmi.h>
#समावेश <linux/types.h>
#समावेश "qmi_wlfw_v01.h"

अटल काष्ठा qmi_elem_info wlfw_ce_tgt_pipe_cfg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_num),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_pipedir_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_dir),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01,
					   nentries),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01,
					   nbytes_max),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01,
					   flags),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_ce_svc_pipe_cfg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_svc_pipe_cfg_s_v01,
					   service_id),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_pipedir_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_svc_pipe_cfg_s_v01,
					   pipe_dir),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_ce_svc_pipe_cfg_s_v01,
					   pipe_num),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_shaकरोw_reg_cfg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_shaकरोw_reg_cfg_s_v01,
					   id),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_shaकरोw_reg_cfg_s_v01,
					   offset),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_shaकरोw_reg_v2_cfg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_shaकरोw_reg_v2_cfg_s_v01,
					   addr),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_memory_region_info_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_memory_region_info_s_v01,
					   region_addr),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_memory_region_info_s_v01,
					   size),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_memory_region_info_s_v01,
					   secure_flag),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_mem_cfg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_cfg_s_v01,
					   offset),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_cfg_s_v01,
					   size),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_cfg_s_v01,
					   secure_flag),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_mem_seg_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_s_v01,
					   size),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_mem_type_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_s_v01,
					   type),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_s_v01,
					   mem_cfg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_MEM_CFG_V01,
		.elem_size      = माप(काष्ठा wlfw_mem_cfg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_s_v01,
					   mem_cfg),
		.ei_array      = wlfw_mem_cfg_s_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_mem_seg_resp_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_resp_s_v01,
					   addr),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_resp_s_v01,
					   size),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_mem_type_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_mem_seg_resp_s_v01,
					   type),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_rf_chip_info_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_rf_chip_info_s_v01,
					   chip_id),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_rf_chip_info_s_v01,
					   chip_family),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_rf_board_info_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_rf_board_info_s_v01,
					   board_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_soc_info_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_soc_info_s_v01,
					   soc_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा qmi_elem_info wlfw_fw_version_info_s_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_fw_version_info_s_v01,
					   fw_version),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = QMI_WLFW_MAX_TIMESTAMP_LEN_V01 + 1,
		.elem_size      = माप(अक्षर),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = दुरत्व(काष्ठा wlfw_fw_version_info_s_v01,
					   fw_build_बारtamp),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_ind_रेजिस्टर_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   fw_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   fw_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_करोwnload_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_करोwnload_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_update_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_update_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   msa_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   msa_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   pin_connect_result_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   pin_connect_result_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   client_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   client_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x16,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   request_mem_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x16,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   request_mem_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x17,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   mem_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x17,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   mem_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x18,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   fw_init_करोne_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x18,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   fw_init_करोne_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x19,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   rejuvenate_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x19,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   rejuvenate_enable),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1A,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   xo_cal_enable_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1A,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01,
					   xo_cal_enable),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_ind_रेजिस्टर_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_resp_msg_v01,
					   fw_status_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ind_रेजिस्टर_resp_msg_v01,
					   fw_status),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_fw_पढ़ोy_ind_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_ind_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_pin_connect_result_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   pwr_pin_result_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   pwr_pin_result),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   phy_io_pin_result_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   phy_io_pin_result),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   rf_pin_result_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_pin_connect_result_ind_msg_v01,
					   rf_pin_result),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_wlan_mode_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_driver_mode_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_mode_req_msg_v01,
					   mode),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_mode_req_msg_v01,
					   hw_debug_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_mode_req_msg_v01,
					   hw_debug),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_wlan_mode_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_mode_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_wlan_cfg_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   host_version_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = QMI_WLFW_MAX_STR_LEN_V01 + 1,
		.elem_size      = माप(अक्षर),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   host_version),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_CE_V01,
		.elem_size      = माप(काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   tgt_cfg),
		.ei_array      = wlfw_ce_tgt_pipe_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   svc_cfg_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   svc_cfg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_SVC_V01,
		.elem_size      = माप(काष्ठा wlfw_ce_svc_pipe_cfg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   svc_cfg),
		.ei_array      = wlfw_ce_svc_pipe_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_SHADOW_REG_V01,
		.elem_size      = माप(काष्ठा wlfw_shaकरोw_reg_cfg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg),
		.ei_array      = wlfw_shaकरोw_reg_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_SHADOW_REG_V2,
		.elem_size      = माप(काष्ठा wlfw_shaकरोw_reg_v2_cfg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2),
		.ei_array      = wlfw_shaकरोw_reg_v2_cfg_s_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_wlan_cfg_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_wlan_cfg_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cap_req_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cap_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   chip_info_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा wlfw_rf_chip_info_s_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   chip_info),
		.ei_array      = wlfw_rf_chip_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   board_info_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा wlfw_rf_board_info_s_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   board_info),
		.ei_array      = wlfw_rf_board_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   soc_info_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा wlfw_soc_info_s_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   soc_info),
		.ei_array      = wlfw_soc_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   fw_version_info_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा wlfw_fw_version_info_s_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   fw_version_info),
		.ei_array      = wlfw_fw_version_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   fw_build_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = QMI_WLFW_MAX_BUILD_ID_LEN_V01 + 1,
		.elem_size      = माप(अक्षर),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   fw_build_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   num_macs_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_cap_resp_msg_v01,
					   num_macs),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_bdf_करोwnload_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   valid),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   file_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   file_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   total_size_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   total_size),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   seg_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   seg_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_DATA_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   end_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   end),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   bdf_type_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_req_msg_v01,
					   bdf_type),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_bdf_करोwnload_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_bdf_करोwnload_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_report_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_cal_report_req_msg_v01,
					   meta_data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = QMI_WLFW_MAX_NUM_CAL_V01,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_cal_report_req_msg_v01,
					   meta_data),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_report_req_msg_v01,
					   xo_cal_data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_report_req_msg_v01,
					   xo_cal_data),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_report_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_cal_report_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_initiate_cal_करोwnload_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_initiate_cal_करोwnload_ind_msg_v01,
					   cal_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_करोwnload_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   valid),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   file_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   file_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   total_size_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   total_size),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   seg_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   seg_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_DATA_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   end_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_req_msg_v01,
					   end),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_करोwnload_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_cal_करोwnload_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_initiate_cal_update_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_initiate_cal_update_ind_msg_v01,
					   cal_id),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_initiate_cal_update_ind_msg_v01,
					   total_size),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_update_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_req_msg_v01,
					   cal_id),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_req_msg_v01,
					   seg_id),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_cal_update_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   file_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = माप(क्रमागत wlfw_cal_temp_id_क्रमागत_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   file_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   total_size_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   total_size),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   seg_id_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   seg_id),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_DATA_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   end_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_cal_update_resp_msg_v01,
					   end),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_msa_info_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_msa_info_req_msg_v01,
					   msa_addr),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_msa_info_req_msg_v01,
					   size),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_msa_info_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_msa_info_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा wlfw_msa_info_resp_msg_v01,
					   mem_region_info_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_MEM_REG_V01,
		.elem_size      = माप(काष्ठा wlfw_memory_region_info_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा wlfw_msa_info_resp_msg_v01,
					   mem_region_info),
		.ei_array      = wlfw_memory_region_info_s_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_req_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_msa_पढ़ोy_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_ini_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ini_req_msg_v01,
					   enablefwlog_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_ini_req_msg_v01,
					   enablefwlog),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_ini_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_ini_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_athdiag_पढ़ो_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_req_msg_v01,
					   offset),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_req_msg_v01,
					   mem_type),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_req_msg_v01,
					   data_len),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_athdiag_पढ़ो_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_resp_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_resp_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_ATHDIAG_DATA_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_पढ़ो_resp_msg_v01,
					   data),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_athdiag_ग_लिखो_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_ग_लिखो_req_msg_v01,
					   offset),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_ग_लिखो_req_msg_v01,
					   mem_type),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_ग_लिखो_req_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_ATHDIAG_DATA_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x03,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_ग_लिखो_req_msg_v01,
					   data),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_athdiag_ग_लिखो_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_athdiag_ग_लिखो_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_vbatt_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_vbatt_req_msg_v01,
					   voltage_uv),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_vbatt_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_vbatt_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_mac_addr_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_mac_addr_req_msg_v01,
					   mac_addr_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAC_ADDR_SIZE_V01,
		.elem_size      = माप(u8),
		.array_type       = STATIC_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_mac_addr_req_msg_v01,
					   mac_addr),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_mac_addr_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_mac_addr_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_host_cap_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   daemon_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   daemon_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   wake_msi_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   wake_msi),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   gpios_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   gpios_len),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = QMI_WLFW_MAX_NUM_GPIO_V01,
		.elem_size      = माप(u32),
		.array_type     = VAR_LEN_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   gpios),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   nm_modem_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   nm_modem),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   bdf_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x14,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   bdf_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   bdf_cache_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x15,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   bdf_cache_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x16,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   m3_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x16,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   m3_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x17,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   m3_cache_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x17,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   m3_cache_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x18,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_filesys_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x18,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_filesys_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x19,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_cache_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x19,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_cache_support),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1A,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_करोne_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1A,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   cal_करोne),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1B,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   mem_bucket_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1B,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   mem_bucket),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1C,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   mem_cfg_mode_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x1C,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   mem_cfg_mode),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_host_cap_8bit_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   daemon_support_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_req_msg_v01,
					   daemon_support),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_host_cap_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_host_cap_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_request_mem_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_request_mem_ind_msg_v01,
					   mem_seg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_MEM_SEG_V01,
		.elem_size      = माप(काष्ठा wlfw_mem_seg_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_request_mem_ind_msg_v01,
					   mem_seg),
		.ei_array      = wlfw_mem_seg_s_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_respond_mem_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_respond_mem_req_msg_v01,
					   mem_seg_len),
	पूर्ण,
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = QMI_WLFW_MAX_NUM_MEM_SEG_V01,
		.elem_size      = माप(काष्ठा wlfw_mem_seg_resp_s_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_respond_mem_req_msg_v01,
					   mem_seg),
		.ei_array      = wlfw_mem_seg_resp_s_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_respond_mem_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_respond_mem_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_mem_पढ़ोy_ind_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_fw_init_करोne_ind_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_rejuvenate_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   cause_क्रम_rejuvenation_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   cause_क्रम_rejuvenation),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   requesting_sub_प्रणाली_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   requesting_sub_प्रणाली),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   line_number_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   line_number),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   function_name_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_STRING,
		.elem_len       = QMI_WLFW_FUNCTION_NAME_LEN_V01 + 1,
		.elem_size      = माप(अक्षर),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ind_msg_v01,
					   function_name),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_rejuvenate_ack_req_msg_v01_ei[] = अणु
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_rejuvenate_ack_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_rejuvenate_ack_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_dynamic_feature_mask_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_req_msg_v01,
					   mask_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_req_msg_v01,
					   mask),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_dynamic_feature_mask_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01,
					   prev_mask_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01,
					   prev_mask),
	पूर्ण,
	अणु
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01,
					   curr_mask_valid),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = दुरत्व(काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01,
					   curr_mask),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_m3_info_req_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_8_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u64),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_m3_info_req_msg_v01,
					   addr),
	पूर्ण,
	अणु
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_m3_info_req_msg_v01,
					   size),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_m3_info_resp_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = माप(काष्ठा qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = दुरत्व(काष्ठा wlfw_m3_info_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा qmi_elem_info wlfw_xo_cal_ind_msg_v01_ei[] = अणु
	अणु
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = माप(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = दुरत्व(काष्ठा wlfw_xo_cal_ind_msg_v01,
					   xo_cal_data),
	पूर्ण,
	अणुपूर्ण
पूर्ण;
