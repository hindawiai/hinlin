<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित WCN3990_QMI_SVC_V01_H
#घोषणा WCN3990_QMI_SVC_V01_H

#घोषणा WLFW_SERVICE_ID_V01 0x45
#घोषणा WLFW_SERVICE_VERS_V01 0x01

#घोषणा QMI_WLFW_BDF_DOWNLOAD_REQ_V01 0x0025
#घोषणा QMI_WLFW_MEM_READY_IND_V01 0x0037
#घोषणा QMI_WLFW_DYNAMIC_FEATURE_MASK_RESP_V01 0x003B
#घोषणा QMI_WLFW_INITIATE_CAL_UPDATE_IND_V01 0x002A
#घोषणा QMI_WLFW_HOST_CAP_REQ_V01 0x0034
#घोषणा QMI_WLFW_M3_INFO_REQ_V01 0x003C
#घोषणा QMI_WLFW_CAP_REQ_V01 0x0024
#घोषणा QMI_WLFW_FW_INIT_DONE_IND_V01 0x0038
#घोषणा QMI_WLFW_CAL_REPORT_REQ_V01 0x0026
#घोषणा QMI_WLFW_M3_INFO_RESP_V01 0x003C
#घोषणा QMI_WLFW_CAL_UPDATE_RESP_V01 0x0029
#घोषणा QMI_WLFW_CAL_DOWNLOAD_RESP_V01 0x0027
#घोषणा QMI_WLFW_XO_CAL_IND_V01 0x003D
#घोषणा QMI_WLFW_INI_RESP_V01 0x002F
#घोषणा QMI_WLFW_CAL_REPORT_RESP_V01 0x0026
#घोषणा QMI_WLFW_MAC_ADDR_RESP_V01 0x0033
#घोषणा QMI_WLFW_INITIATE_CAL_DOWNLOAD_IND_V01 0x0028
#घोषणा QMI_WLFW_HOST_CAP_RESP_V01 0x0034
#घोषणा QMI_WLFW_MSA_READY_IND_V01 0x002B
#घोषणा QMI_WLFW_ATHDIAG_WRITE_RESP_V01 0x0031
#घोषणा QMI_WLFW_WLAN_MODE_REQ_V01 0x0022
#घोषणा QMI_WLFW_IND_REGISTER_REQ_V01 0x0020
#घोषणा QMI_WLFW_WLAN_CFG_RESP_V01 0x0023
#घोषणा QMI_WLFW_REQUEST_MEM_IND_V01 0x0035
#घोषणा QMI_WLFW_REJUVENATE_IND_V01 0x0039
#घोषणा QMI_WLFW_DYNAMIC_FEATURE_MASK_REQ_V01 0x003B
#घोषणा QMI_WLFW_ATHDIAG_WRITE_REQ_V01 0x0031
#घोषणा QMI_WLFW_WLAN_MODE_RESP_V01 0x0022
#घोषणा QMI_WLFW_RESPOND_MEM_REQ_V01 0x0036
#घोषणा QMI_WLFW_PIN_CONNECT_RESULT_IND_V01 0x002C
#घोषणा QMI_WLFW_FW_READY_IND_V01 0x0021
#घोषणा QMI_WLFW_MSA_READY_RESP_V01 0x002E
#घोषणा QMI_WLFW_CAL_UPDATE_REQ_V01 0x0029
#घोषणा QMI_WLFW_INI_REQ_V01 0x002F
#घोषणा QMI_WLFW_BDF_DOWNLOAD_RESP_V01 0x0025
#घोषणा QMI_WLFW_REJUVENATE_ACK_RESP_V01 0x003A
#घोषणा QMI_WLFW_MSA_INFO_RESP_V01 0x002D
#घोषणा QMI_WLFW_MSA_READY_REQ_V01 0x002E
#घोषणा QMI_WLFW_CAP_RESP_V01 0x0024
#घोषणा QMI_WLFW_REJUVENATE_ACK_REQ_V01 0x003A
#घोषणा QMI_WLFW_ATHDIAG_READ_RESP_V01 0x0030
#घोषणा QMI_WLFW_VBATT_REQ_V01 0x0032
#घोषणा QMI_WLFW_MAC_ADDR_REQ_V01 0x0033
#घोषणा QMI_WLFW_RESPOND_MEM_RESP_V01 0x0036
#घोषणा QMI_WLFW_VBATT_RESP_V01 0x0032
#घोषणा QMI_WLFW_MSA_INFO_REQ_V01 0x002D
#घोषणा QMI_WLFW_CAL_DOWNLOAD_REQ_V01 0x0027
#घोषणा QMI_WLFW_ATHDIAG_READ_REQ_V01 0x0030
#घोषणा QMI_WLFW_WLAN_CFG_REQ_V01 0x0023
#घोषणा QMI_WLFW_IND_REGISTER_RESP_V01 0x0020

#घोषणा QMI_WLFW_MAX_MEM_REG_V01 2
#घोषणा QMI_WLFW_MAX_NUM_MEM_SEG_V01 16
#घोषणा QMI_WLFW_MAX_NUM_CAL_V01 5
#घोषणा QMI_WLFW_MAX_DATA_SIZE_V01 6144
#घोषणा QMI_WLFW_FUNCTION_NAME_LEN_V01 128
#घोषणा QMI_WLFW_MAX_NUM_CE_V01 12
#घोषणा QMI_WLFW_MAX_TIMESTAMP_LEN_V01 32
#घोषणा QMI_WLFW_MAX_ATHDIAG_DATA_SIZE_V01 6144
#घोषणा QMI_WLFW_MAX_NUM_GPIO_V01 32
#घोषणा QMI_WLFW_MAX_BUILD_ID_LEN_V01 128
#घोषणा QMI_WLFW_MAX_NUM_MEM_CFG_V01 2
#घोषणा QMI_WLFW_MAX_STR_LEN_V01 16
#घोषणा QMI_WLFW_MAX_NUM_SHADOW_REG_V01 24
#घोषणा QMI_WLFW_MAC_ADDR_SIZE_V01 6
#घोषणा QMI_WLFW_MAX_SHADOW_REG_V2 36
#घोषणा QMI_WLFW_MAX_NUM_SVC_V01 24

क्रमागत wlfw_driver_mode_क्रमागत_v01 अणु
	QMI_WLFW_MISSION_V01 = 0,
	QMI_WLFW_FTM_V01 = 1,
	QMI_WLFW_EPPING_V01 = 2,
	QMI_WLFW_WALTEST_V01 = 3,
	QMI_WLFW_OFF_V01 = 4,
	QMI_WLFW_CCPM_V01 = 5,
	QMI_WLFW_QVIT_V01 = 6,
	QMI_WLFW_CALIBRATION_V01 = 7,
पूर्ण;

क्रमागत wlfw_cal_temp_id_क्रमागत_v01 अणु
	QMI_WLFW_CAL_TEMP_IDX_0_V01 = 0,
	QMI_WLFW_CAL_TEMP_IDX_1_V01 = 1,
	QMI_WLFW_CAL_TEMP_IDX_2_V01 = 2,
	QMI_WLFW_CAL_TEMP_IDX_3_V01 = 3,
	QMI_WLFW_CAL_TEMP_IDX_4_V01 = 4,
पूर्ण;

क्रमागत wlfw_pipedir_क्रमागत_v01 अणु
	QMI_WLFW_PIPEसूची_NONE_V01 = 0,
	QMI_WLFW_PIPEसूची_IN_V01 = 1,
	QMI_WLFW_PIPEसूची_OUT_V01 = 2,
	QMI_WLFW_PIPEसूची_INOUT_V01 = 3,
पूर्ण;

क्रमागत wlfw_mem_type_क्रमागत_v01 अणु
	QMI_WLFW_MEM_TYPE_MSA_V01 = 0,
	QMI_WLFW_MEM_TYPE_DDR_V01 = 1,
पूर्ण;

#घोषणा QMI_WLFW_CE_ATTR_FLAGS_V01 ((u32)0x00)
#घोषणा QMI_WLFW_CE_ATTR_NO_SNOOP_V01 ((u32)0x01)
#घोषणा QMI_WLFW_CE_ATTR_BYTE_SWAP_DATA_V01 ((u32)0x02)
#घोषणा QMI_WLFW_CE_ATTR_SWIZZLE_DESCRIPTORS_V01 ((u32)0x04)
#घोषणा QMI_WLFW_CE_ATTR_DISABLE_INTR_V01 ((u32)0x08)
#घोषणा QMI_WLFW_CE_ATTR_ENABLE_POLL_V01 ((u32)0x10)

#घोषणा QMI_WLFW_ALREADY_REGISTERED_V01 ((u64)0x01ULL)
#घोषणा QMI_WLFW_FW_READY_V01 ((u64)0x02ULL)
#घोषणा QMI_WLFW_MSA_READY_V01 ((u64)0x04ULL)
#घोषणा QMI_WLFW_MEM_READY_V01 ((u64)0x08ULL)
#घोषणा QMI_WLFW_FW_INIT_DONE_V01 ((u64)0x10ULL)

#घोषणा QMI_WLFW_FW_REJUVENATE_V01 ((u64)0x01ULL)

काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01 अणु
	__le32 pipe_num;
	__le32 pipe_dir;
	__le32 nentries;
	__le32 nbytes_max;
	__le32 flags;
पूर्ण;

काष्ठा wlfw_ce_svc_pipe_cfg_s_v01 अणु
	__le32 service_id;
	__le32 pipe_dir;
	__le32 pipe_num;
पूर्ण;

काष्ठा wlfw_shaकरोw_reg_cfg_s_v01 अणु
	u16 id;
	u16 offset;
पूर्ण;

काष्ठा wlfw_shaकरोw_reg_v2_cfg_s_v01 अणु
	u32 addr;
पूर्ण;

काष्ठा wlfw_memory_region_info_s_v01 अणु
	u64 region_addr;
	u32 size;
	u8 secure_flag;
पूर्ण;

काष्ठा wlfw_mem_cfg_s_v01 अणु
	u64 offset;
	u32 size;
	u8 secure_flag;
पूर्ण;

काष्ठा wlfw_mem_seg_s_v01 अणु
	u32 size;
	क्रमागत wlfw_mem_type_क्रमागत_v01 type;
	u32 mem_cfg_len;
	काष्ठा wlfw_mem_cfg_s_v01 mem_cfg[QMI_WLFW_MAX_NUM_MEM_CFG_V01];
पूर्ण;

काष्ठा wlfw_mem_seg_resp_s_v01 अणु
	u64 addr;
	u32 size;
	क्रमागत wlfw_mem_type_क्रमागत_v01 type;
पूर्ण;

काष्ठा wlfw_rf_chip_info_s_v01 अणु
	u32 chip_id;
	u32 chip_family;
पूर्ण;

काष्ठा wlfw_rf_board_info_s_v01 अणु
	u32 board_id;
पूर्ण;

काष्ठा wlfw_soc_info_s_v01 अणु
	u32 soc_id;
पूर्ण;

काष्ठा wlfw_fw_version_info_s_v01 अणु
	u32 fw_version;
	अक्षर fw_build_बारtamp[QMI_WLFW_MAX_TIMESTAMP_LEN_V01 + 1];
पूर्ण;

काष्ठा wlfw_ind_रेजिस्टर_req_msg_v01 अणु
	u8 fw_पढ़ोy_enable_valid;
	u8 fw_पढ़ोy_enable;
	u8 initiate_cal_करोwnload_enable_valid;
	u8 initiate_cal_करोwnload_enable;
	u8 initiate_cal_update_enable_valid;
	u8 initiate_cal_update_enable;
	u8 msa_पढ़ोy_enable_valid;
	u8 msa_पढ़ोy_enable;
	u8 pin_connect_result_enable_valid;
	u8 pin_connect_result_enable;
	u8 client_id_valid;
	u32 client_id;
	u8 request_mem_enable_valid;
	u8 request_mem_enable;
	u8 mem_पढ़ोy_enable_valid;
	u8 mem_पढ़ोy_enable;
	u8 fw_init_करोne_enable_valid;
	u8 fw_init_करोne_enable;
	u8 rejuvenate_enable_valid;
	u32 rejuvenate_enable;
	u8 xo_cal_enable_valid;
	u8 xo_cal_enable;
पूर्ण;

#घोषणा WLFW_IND_REGISTER_REQ_MSG_V01_MAX_MSG_LEN 50
बाह्य काष्ठा qmi_elem_info wlfw_ind_रेजिस्टर_req_msg_v01_ei[];

काष्ठा wlfw_ind_रेजिस्टर_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 fw_status_valid;
	u64 fw_status;
पूर्ण;

#घोषणा WLFW_IND_REGISTER_RESP_MSG_V01_MAX_MSG_LEN 18
बाह्य काष्ठा qmi_elem_info wlfw_ind_रेजिस्टर_resp_msg_v01_ei[];

काष्ठा wlfw_fw_पढ़ोy_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_FW_READY_IND_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_fw_पढ़ोy_ind_msg_v01_ei[];

काष्ठा wlfw_msa_पढ़ोy_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_MSA_READY_IND_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_ind_msg_v01_ei[];

काष्ठा wlfw_pin_connect_result_ind_msg_v01 अणु
	u8 pwr_pin_result_valid;
	u32 pwr_pin_result;
	u8 phy_io_pin_result_valid;
	u32 phy_io_pin_result;
	u8 rf_pin_result_valid;
	u32 rf_pin_result;
पूर्ण;

#घोषणा WLFW_PIN_CONNECT_RESULT_IND_MSG_V01_MAX_MSG_LEN 21
बाह्य काष्ठा qmi_elem_info wlfw_pin_connect_result_ind_msg_v01_ei[];

काष्ठा wlfw_wlan_mode_req_msg_v01 अणु
	क्रमागत wlfw_driver_mode_क्रमागत_v01 mode;
	u8 hw_debug_valid;
	u8 hw_debug;
पूर्ण;

#घोषणा WLFW_WLAN_MODE_REQ_MSG_V01_MAX_MSG_LEN 11
बाह्य काष्ठा qmi_elem_info wlfw_wlan_mode_req_msg_v01_ei[];

काष्ठा wlfw_wlan_mode_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_WLAN_MODE_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_wlan_mode_resp_msg_v01_ei[];

काष्ठा wlfw_wlan_cfg_req_msg_v01 अणु
	u8 host_version_valid;
	अक्षर host_version[QMI_WLFW_MAX_STR_LEN_V01 + 1];
	u8 tgt_cfg_valid;
	u32 tgt_cfg_len;
	काष्ठा wlfw_ce_tgt_pipe_cfg_s_v01 tgt_cfg[QMI_WLFW_MAX_NUM_CE_V01];
	u8 svc_cfg_valid;
	u32 svc_cfg_len;
	काष्ठा wlfw_ce_svc_pipe_cfg_s_v01 svc_cfg[QMI_WLFW_MAX_NUM_SVC_V01];
	u8 shaकरोw_reg_valid;
	u32 shaकरोw_reg_len;
	काष्ठा wlfw_shaकरोw_reg_cfg_s_v01 shaकरोw_reg[QMI_WLFW_MAX_NUM_SHADOW_REG_V01];
	u8 shaकरोw_reg_v2_valid;
	u32 shaकरोw_reg_v2_len;
	काष्ठा wlfw_shaकरोw_reg_v2_cfg_s_v01 shaकरोw_reg_v2[QMI_WLFW_MAX_SHADOW_REG_V2];
पूर्ण;

#घोषणा WLFW_WLAN_CFG_REQ_MSG_V01_MAX_MSG_LEN 803
बाह्य काष्ठा qmi_elem_info wlfw_wlan_cfg_req_msg_v01_ei[];

काष्ठा wlfw_wlan_cfg_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_WLAN_CFG_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_wlan_cfg_resp_msg_v01_ei[];

काष्ठा wlfw_cap_req_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_CAP_REQ_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_cap_req_msg_v01_ei[];

काष्ठा wlfw_cap_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 chip_info_valid;
	काष्ठा wlfw_rf_chip_info_s_v01 chip_info;
	u8 board_info_valid;
	काष्ठा wlfw_rf_board_info_s_v01 board_info;
	u8 soc_info_valid;
	काष्ठा wlfw_soc_info_s_v01 soc_info;
	u8 fw_version_info_valid;
	काष्ठा wlfw_fw_version_info_s_v01 fw_version_info;
	u8 fw_build_id_valid;
	अक्षर fw_build_id[QMI_WLFW_MAX_BUILD_ID_LEN_V01 + 1];
	u8 num_macs_valid;
	u8 num_macs;
पूर्ण;

#घोषणा WLFW_CAP_RESP_MSG_V01_MAX_MSG_LEN 207
बाह्य काष्ठा qmi_elem_info wlfw_cap_resp_msg_v01_ei[];

काष्ठा wlfw_bdf_करोwnload_req_msg_v01 अणु
	u8 valid;
	u8 file_id_valid;
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 file_id;
	u8 total_size_valid;
	u32 total_size;
	u8 seg_id_valid;
	u32 seg_id;
	u8 data_valid;
	u32 data_len;
	u8 data[QMI_WLFW_MAX_DATA_SIZE_V01];
	u8 end_valid;
	u8 end;
	u8 bdf_type_valid;
	u8 bdf_type;
पूर्ण;

#घोषणा WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN 6182
बाह्य काष्ठा qmi_elem_info wlfw_bdf_करोwnload_req_msg_v01_ei[];

काष्ठा wlfw_bdf_करोwnload_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_BDF_DOWNLOAD_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_bdf_करोwnload_resp_msg_v01_ei[];

काष्ठा wlfw_cal_report_req_msg_v01 अणु
	u32 meta_data_len;
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 meta_data[QMI_WLFW_MAX_NUM_CAL_V01];
	u8 xo_cal_data_valid;
	u8 xo_cal_data;
पूर्ण;

#घोषणा WLFW_CAL_REPORT_REQ_MSG_V01_MAX_MSG_LEN 28
बाह्य काष्ठा qmi_elem_info wlfw_cal_report_req_msg_v01_ei[];

काष्ठा wlfw_cal_report_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_CAL_REPORT_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_cal_report_resp_msg_v01_ei[];

काष्ठा wlfw_initiate_cal_करोwnload_ind_msg_v01 अणु
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 cal_id;
पूर्ण;

#घोषणा WLFW_INITIATE_CAL_DOWNLOAD_IND_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_initiate_cal_करोwnload_ind_msg_v01_ei[];

काष्ठा wlfw_cal_करोwnload_req_msg_v01 अणु
	u8 valid;
	u8 file_id_valid;
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 file_id;
	u8 total_size_valid;
	u32 total_size;
	u8 seg_id_valid;
	u32 seg_id;
	u8 data_valid;
	u32 data_len;
	u8 data[QMI_WLFW_MAX_DATA_SIZE_V01];
	u8 end_valid;
	u8 end;
पूर्ण;

#घोषणा WLFW_CAL_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN 6178
बाह्य काष्ठा qmi_elem_info wlfw_cal_करोwnload_req_msg_v01_ei[];

काष्ठा wlfw_cal_करोwnload_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_CAL_DOWNLOAD_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_cal_करोwnload_resp_msg_v01_ei[];

काष्ठा wlfw_initiate_cal_update_ind_msg_v01 अणु
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 cal_id;
	u32 total_size;
पूर्ण;

#घोषणा WLFW_INITIATE_CAL_UPDATE_IND_MSG_V01_MAX_MSG_LEN 14
बाह्य काष्ठा qmi_elem_info wlfw_initiate_cal_update_ind_msg_v01_ei[];

काष्ठा wlfw_cal_update_req_msg_v01 अणु
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 cal_id;
	u32 seg_id;
पूर्ण;

#घोषणा WLFW_CAL_UPDATE_REQ_MSG_V01_MAX_MSG_LEN 14
बाह्य काष्ठा qmi_elem_info wlfw_cal_update_req_msg_v01_ei[];

काष्ठा wlfw_cal_update_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 file_id_valid;
	क्रमागत wlfw_cal_temp_id_क्रमागत_v01 file_id;
	u8 total_size_valid;
	u32 total_size;
	u8 seg_id_valid;
	u32 seg_id;
	u8 data_valid;
	u32 data_len;
	u8 data[QMI_WLFW_MAX_DATA_SIZE_V01];
	u8 end_valid;
	u8 end;
पूर्ण;

#घोषणा WLFW_CAL_UPDATE_RESP_MSG_V01_MAX_MSG_LEN 6181
बाह्य काष्ठा qmi_elem_info wlfw_cal_update_resp_msg_v01_ei[];

काष्ठा wlfw_msa_info_req_msg_v01 अणु
	u64 msa_addr;
	u32 size;
पूर्ण;

#घोषणा WLFW_MSA_INFO_REQ_MSG_V01_MAX_MSG_LEN 18
बाह्य काष्ठा qmi_elem_info wlfw_msa_info_req_msg_v01_ei[];

काष्ठा wlfw_msa_info_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u32 mem_region_info_len;
	काष्ठा wlfw_memory_region_info_s_v01 mem_region_info[QMI_WLFW_MAX_MEM_REG_V01];
पूर्ण;

#घोषणा WLFW_MSA_INFO_RESP_MSG_V01_MAX_MSG_LEN 37
बाह्य काष्ठा qmi_elem_info wlfw_msa_info_resp_msg_v01_ei[];

काष्ठा wlfw_msa_पढ़ोy_req_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_MSA_READY_REQ_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_req_msg_v01_ei[];

काष्ठा wlfw_msa_पढ़ोy_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_MSA_READY_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_msa_पढ़ोy_resp_msg_v01_ei[];

काष्ठा wlfw_ini_req_msg_v01 अणु
	u8 enablefwlog_valid;
	u8 enablefwlog;
पूर्ण;

#घोषणा WLFW_INI_REQ_MSG_V01_MAX_MSG_LEN 4
बाह्य काष्ठा qmi_elem_info wlfw_ini_req_msg_v01_ei[];

काष्ठा wlfw_ini_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_INI_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_ini_resp_msg_v01_ei[];

काष्ठा wlfw_athdiag_पढ़ो_req_msg_v01 अणु
	u32 offset;
	u32 mem_type;
	u32 data_len;
पूर्ण;

#घोषणा WLFW_ATHDIAG_READ_REQ_MSG_V01_MAX_MSG_LEN 21
बाह्य काष्ठा qmi_elem_info wlfw_athdiag_पढ़ो_req_msg_v01_ei[];

काष्ठा wlfw_athdiag_पढ़ो_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 data_valid;
	u32 data_len;
	u8 data[QMI_WLFW_MAX_ATHDIAG_DATA_SIZE_V01];
पूर्ण;

#घोषणा WLFW_ATHDIAG_READ_RESP_MSG_V01_MAX_MSG_LEN 6156
बाह्य काष्ठा qmi_elem_info wlfw_athdiag_पढ़ो_resp_msg_v01_ei[];

काष्ठा wlfw_athdiag_ग_लिखो_req_msg_v01 अणु
	u32 offset;
	u32 mem_type;
	u32 data_len;
	u8 data[QMI_WLFW_MAX_ATHDIAG_DATA_SIZE_V01];
पूर्ण;

#घोषणा WLFW_ATHDIAG_WRITE_REQ_MSG_V01_MAX_MSG_LEN 6163
बाह्य काष्ठा qmi_elem_info wlfw_athdiag_ग_लिखो_req_msg_v01_ei[];

काष्ठा wlfw_athdiag_ग_लिखो_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_ATHDIAG_WRITE_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_athdiag_ग_लिखो_resp_msg_v01_ei[];

काष्ठा wlfw_vbatt_req_msg_v01 अणु
	u64 voltage_uv;
पूर्ण;

#घोषणा WLFW_VBATT_REQ_MSG_V01_MAX_MSG_LEN 11
बाह्य काष्ठा qmi_elem_info wlfw_vbatt_req_msg_v01_ei[];

काष्ठा wlfw_vbatt_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_VBATT_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_vbatt_resp_msg_v01_ei[];

काष्ठा wlfw_mac_addr_req_msg_v01 अणु
	u8 mac_addr_valid;
	u8 mac_addr[QMI_WLFW_MAC_ADDR_SIZE_V01];
पूर्ण;

#घोषणा WLFW_MAC_ADDR_REQ_MSG_V01_MAX_MSG_LEN 9
बाह्य काष्ठा qmi_elem_info wlfw_mac_addr_req_msg_v01_ei[];

काष्ठा wlfw_mac_addr_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_MAC_ADDR_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_mac_addr_resp_msg_v01_ei[];

#घोषणा QMI_WLFW_MAX_NUM_GPIO_V01 32
काष्ठा wlfw_host_cap_req_msg_v01 अणु
	u8 daemon_support_valid;
	u32 daemon_support;
	u8 wake_msi_valid;
	u32 wake_msi;
	u8 gpios_valid;
	u32 gpios_len;
	u32 gpios[QMI_WLFW_MAX_NUM_GPIO_V01];
	u8 nm_modem_valid;
	u8 nm_modem;
	u8 bdf_support_valid;
	u8 bdf_support;
	u8 bdf_cache_support_valid;
	u8 bdf_cache_support;
	u8 m3_support_valid;
	u8 m3_support;
	u8 m3_cache_support_valid;
	u8 m3_cache_support;
	u8 cal_filesys_support_valid;
	u8 cal_filesys_support;
	u8 cal_cache_support_valid;
	u8 cal_cache_support;
	u8 cal_करोne_valid;
	u8 cal_करोne;
	u8 mem_bucket_valid;
	u32 mem_bucket;
	u8 mem_cfg_mode_valid;
	u8 mem_cfg_mode;
पूर्ण;

#घोषणा WLFW_HOST_CAP_REQ_MSG_V01_MAX_MSG_LEN 189
बाह्य काष्ठा qmi_elem_info wlfw_host_cap_req_msg_v01_ei[];
बाह्य काष्ठा qmi_elem_info wlfw_host_cap_8bit_req_msg_v01_ei[];

काष्ठा wlfw_host_cap_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_HOST_CAP_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_host_cap_resp_msg_v01_ei[];

काष्ठा wlfw_request_mem_ind_msg_v01 अणु
	u32 mem_seg_len;
	काष्ठा wlfw_mem_seg_s_v01 mem_seg[QMI_WLFW_MAX_NUM_MEM_SEG_V01];
पूर्ण;

#घोषणा WLFW_REQUEST_MEM_IND_MSG_V01_MAX_MSG_LEN 564
बाह्य काष्ठा qmi_elem_info wlfw_request_mem_ind_msg_v01_ei[];

काष्ठा wlfw_respond_mem_req_msg_v01 अणु
	u32 mem_seg_len;
	काष्ठा wlfw_mem_seg_resp_s_v01 mem_seg[QMI_WLFW_MAX_NUM_MEM_SEG_V01];
पूर्ण;

#घोषणा WLFW_RESPOND_MEM_REQ_MSG_V01_MAX_MSG_LEN 260
बाह्य काष्ठा qmi_elem_info wlfw_respond_mem_req_msg_v01_ei[];

काष्ठा wlfw_respond_mem_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_RESPOND_MEM_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_respond_mem_resp_msg_v01_ei[];

काष्ठा wlfw_mem_पढ़ोy_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_MEM_READY_IND_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_mem_पढ़ोy_ind_msg_v01_ei[];

काष्ठा wlfw_fw_init_करोne_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_FW_INIT_DONE_IND_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_fw_init_करोne_ind_msg_v01_ei[];

काष्ठा wlfw_rejuvenate_ind_msg_v01 अणु
	u8 cause_क्रम_rejuvenation_valid;
	u8 cause_क्रम_rejuvenation;
	u8 requesting_sub_प्रणाली_valid;
	u8 requesting_sub_प्रणाली;
	u8 line_number_valid;
	u16 line_number;
	u8 function_name_valid;
	अक्षर function_name[QMI_WLFW_FUNCTION_NAME_LEN_V01 + 1];
पूर्ण;

#घोषणा WLFW_REJUVENATE_IND_MSG_V01_MAX_MSG_LEN 144
बाह्य काष्ठा qmi_elem_info wlfw_rejuvenate_ind_msg_v01_ei[];

काष्ठा wlfw_rejuvenate_ack_req_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा WLFW_REJUVENATE_ACK_REQ_MSG_V01_MAX_MSG_LEN 0
बाह्य काष्ठा qmi_elem_info wlfw_rejuvenate_ack_req_msg_v01_ei[];

काष्ठा wlfw_rejuvenate_ack_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_REJUVENATE_ACK_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_rejuvenate_ack_resp_msg_v01_ei[];

काष्ठा wlfw_dynamic_feature_mask_req_msg_v01 अणु
	u8 mask_valid;
	u64 mask;
पूर्ण;

#घोषणा WLFW_DYNAMIC_FEATURE_MASK_REQ_MSG_V01_MAX_MSG_LEN 11
बाह्य काष्ठा qmi_elem_info wlfw_dynamic_feature_mask_req_msg_v01_ei[];

काष्ठा wlfw_dynamic_feature_mask_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 prev_mask_valid;
	u64 prev_mask;
	u8 curr_mask_valid;
	u64 curr_mask;
पूर्ण;

#घोषणा WLFW_DYNAMIC_FEATURE_MASK_RESP_MSG_V01_MAX_MSG_LEN 29
बाह्य काष्ठा qmi_elem_info wlfw_dynamic_feature_mask_resp_msg_v01_ei[];

काष्ठा wlfw_m3_info_req_msg_v01 अणु
	u64 addr;
	u32 size;
पूर्ण;

#घोषणा WLFW_M3_INFO_REQ_MSG_V01_MAX_MSG_LEN 18
बाह्य काष्ठा qmi_elem_info wlfw_m3_info_req_msg_v01_ei[];

काष्ठा wlfw_m3_info_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा WLFW_M3_INFO_RESP_MSG_V01_MAX_MSG_LEN 7
बाह्य काष्ठा qmi_elem_info wlfw_m3_info_resp_msg_v01_ei[];

काष्ठा wlfw_xo_cal_ind_msg_v01 अणु
	u8 xo_cal_data;
पूर्ण;

#घोषणा WLFW_XO_CAL_IND_MSG_V01_MAX_MSG_LEN 4
बाह्य काष्ठा qmi_elem_info wlfw_xo_cal_ind_msg_v01_ei[];

#पूर्ण_अगर
