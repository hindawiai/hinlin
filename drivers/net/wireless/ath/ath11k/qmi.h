<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_QMI_H
#घोषणा ATH11K_QMI_H

#समावेश <linux/mutex.h>
#समावेश <linux/soc/qcom/qmi.h>

#घोषणा ATH11K_HOST_VERSION_STRING		"WIN"
#घोषणा ATH11K_QMI_WLANFW_TIMEOUT_MS		5000
#घोषणा ATH11K_QMI_MAX_BDF_खाता_NAME_SIZE	64
#घोषणा ATH11K_QMI_CALDB_ADDRESS		0x4BA00000
#घोषणा ATH11K_QMI_BDF_MAX_SIZE			(256 * 1024)
#घोषणा ATH11K_QMI_CALDATA_OFFSET		(128 * 1024)
#घोषणा ATH11K_QMI_WLANFW_MAX_BUILD_ID_LEN_V01	128
#घोषणा ATH11K_QMI_WLFW_SERVICE_ID_V01		0x45
#घोषणा ATH11K_QMI_WLFW_SERVICE_VERS_V01	0x01
#घोषणा ATH11K_QMI_WLFW_SERVICE_INS_ID_V01	0x02
#घोषणा ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_QCA6390	0x01
#घोषणा ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_IPQ8074	0x02
#घोषणा ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_QCN9074	0x07
#घोषणा ATH11K_QMI_WLANFW_MAX_TIMESTAMP_LEN_V01	32
#घोषणा ATH11K_QMI_RESP_LEN_MAX			8192
#घोषणा ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01	52
#घोषणा ATH11K_QMI_CALDB_SIZE			0x480000
#घोषणा ATH11K_QMI_BDF_EXT_STR_LENGTH		0x20
#घोषणा ATH11K_QMI_FW_MEM_REQ_SEGMENT_CNT	3

#घोषणा QMI_WLFW_REQUEST_MEM_IND_V01		0x0035
#घोषणा QMI_WLFW_FW_MEM_READY_IND_V01		0x0037
#घोषणा QMI_WLFW_COLD_BOOT_CAL_DONE_IND_V01	0x0021
#घोषणा QMI_WLFW_FW_READY_IND_V01		0x0038

#घोषणा QMI_WLANFW_MAX_DATA_SIZE_V01		6144
#घोषणा ATH11K_FIRMWARE_MODE_OFF		4
#घोषणा ATH11K_QMI_TARGET_MEM_MODE_DEFAULT	0
#घोषणा ATH11K_COLD_BOOT_FW_RESET_DELAY		(40 * HZ)

काष्ठा ath11k_base;

क्रमागत ath11k_qmi_file_type अणु
	ATH11K_QMI_खाता_TYPE_BDF_GOLDEN,
	ATH11K_QMI_खाता_TYPE_CALDATA,
	ATH11K_QMI_MAX_खाता_TYPE,
पूर्ण;

क्रमागत ath11k_qmi_bdf_type अणु
	ATH11K_QMI_BDF_TYPE_BIN			= 0,
	ATH11K_QMI_BDF_TYPE_ELF			= 1,
पूर्ण;

क्रमागत ath11k_qmi_event_type अणु
	ATH11K_QMI_EVENT_SERVER_ARRIVE,
	ATH11K_QMI_EVENT_SERVER_EXIT,
	ATH11K_QMI_EVENT_REQUEST_MEM,
	ATH11K_QMI_EVENT_FW_MEM_READY,
	ATH11K_QMI_EVENT_FW_READY,
	ATH11K_QMI_EVENT_COLD_BOOT_CAL_START,
	ATH11K_QMI_EVENT_COLD_BOOT_CAL_DONE,
	ATH11K_QMI_EVENT_REGISTER_DRIVER,
	ATH11K_QMI_EVENT_UNREGISTER_DRIVER,
	ATH11K_QMI_EVENT_RECOVERY,
	ATH11K_QMI_EVENT_FORCE_FW_ASSERT,
	ATH11K_QMI_EVENT_POWER_UP,
	ATH11K_QMI_EVENT_POWER_DOWN,
	ATH11K_QMI_EVENT_MAX,
पूर्ण;

काष्ठा ath11k_qmi_driver_event अणु
	काष्ठा list_head list;
	क्रमागत ath11k_qmi_event_type type;
	व्योम *data;
पूर्ण;

काष्ठा ath11k_qmi_ce_cfg अणु
	स्थिर काष्ठा ce_pipe_config *tgt_ce;
	पूर्णांक tgt_ce_len;
	स्थिर काष्ठा service_to_pipe *svc_to_ce_map;
	पूर्णांक svc_to_ce_map_len;
	स्थिर u8 *shaकरोw_reg;
	पूर्णांक shaकरोw_reg_len;
	u32 *shaकरोw_reg_v2;
	पूर्णांक shaकरोw_reg_v2_len;
पूर्ण;

काष्ठा ath11k_qmi_event_msg अणु
	काष्ठा list_head list;
	क्रमागत ath11k_qmi_event_type type;
पूर्ण;

काष्ठा target_mem_chunk अणु
	u32 size;
	u32 type;
	dma_addr_t paddr;
	u32 *vaddr;
पूर्ण;

काष्ठा target_info अणु
	u32 chip_id;
	u32 chip_family;
	u32 board_id;
	u32 soc_id;
	u32 fw_version;
	अक्षर fw_build_बारtamp[ATH11K_QMI_WLANFW_MAX_TIMESTAMP_LEN_V01 + 1];
	अक्षर fw_build_id[ATH11K_QMI_WLANFW_MAX_BUILD_ID_LEN_V01 + 1];
	अक्षर bdf_ext[ATH11K_QMI_BDF_EXT_STR_LENGTH];
पूर्ण;

काष्ठा m3_mem_region अणु
	u32 size;
	dma_addr_t paddr;
	व्योम *vaddr;
पूर्ण;

काष्ठा ath11k_qmi अणु
	काष्ठा ath11k_base *ab;
	काष्ठा qmi_handle handle;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा work_काष्ठा event_work;
	काष्ठा workqueue_काष्ठा *event_wq;
	काष्ठा list_head event_list;
	spinlock_t event_lock; /* spinlock क्रम qmi event list */
	काष्ठा ath11k_qmi_ce_cfg ce_cfg;
	काष्ठा target_mem_chunk target_mem[ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01];
	u32 mem_seg_count;
	u32 target_mem_mode;
	bool target_mem_delayed;
	u8 cal_करोne;
	काष्ठा target_info target;
	काष्ठा m3_mem_region m3_mem;
	अचिन्हित पूर्णांक service_ins_id;
	रुको_queue_head_t cold_boot_रुकोq;
पूर्ण;

#घोषणा QMI_WLANFW_HOST_CAP_REQ_MSG_V01_MAX_LEN		189
#घोषणा QMI_WLANFW_HOST_CAP_REQ_V01			0x0034
#घोषणा QMI_WLANFW_HOST_CAP_RESP_MSG_V01_MAX_LEN	7
#घोषणा QMI_WLFW_HOST_CAP_RESP_V01			0x0034
#घोषणा QMI_WLFW_MAX_NUM_GPIO_V01			32
#घोषणा QMI_IPQ8074_FW_MEM_MODE				0xFF
#घोषणा HOST_DDR_REGION_TYPE				0x1
#घोषणा BDF_MEM_REGION_TYPE				0x2
#घोषणा M3_DUMP_REGION_TYPE				0x3
#घोषणा CALDB_MEM_REGION_TYPE				0x4

काष्ठा qmi_wlanfw_host_cap_req_msg_v01 अणु
	u8 num_clients_valid;
	u32 num_clients;
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

काष्ठा qmi_wlanfw_host_cap_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा QMI_WLANFW_IND_REGISTER_REQ_MSG_V01_MAX_LEN		54
#घोषणा QMI_WLANFW_IND_REGISTER_REQ_V01				0x0020
#घोषणा QMI_WLANFW_IND_REGISTER_RESP_MSG_V01_MAX_LEN		18
#घोषणा QMI_WLANFW_IND_REGISTER_RESP_V01			0x0020
#घोषणा QMI_WLANFW_CLIENT_ID					0x4b4e454c

काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01 अणु
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
	u8 fw_mem_पढ़ोy_enable_valid;
	u8 fw_mem_पढ़ोy_enable;
	u8 fw_init_करोne_enable_valid;
	u8 fw_init_करोne_enable;
	u8 rejuvenate_enable_valid;
	u32 rejuvenate_enable;
	u8 xo_cal_enable_valid;
	u8 xo_cal_enable;
	u8 cal_करोne_enable_valid;
	u8 cal_करोne_enable;
पूर्ण;

काष्ठा qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 fw_status_valid;
	u64 fw_status;
पूर्ण;

#घोषणा QMI_WLANFW_REQUEST_MEM_IND_MSG_V01_MAX_LEN	1824
#घोषणा QMI_WLANFW_RESPOND_MEM_REQ_MSG_V01_MAX_LEN	888
#घोषणा QMI_WLANFW_RESPOND_MEM_RESP_MSG_V01_MAX_LEN	7
#घोषणा QMI_WLANFW_REQUEST_MEM_IND_V01			0x0035
#घोषणा QMI_WLANFW_RESPOND_MEM_REQ_V01			0x0036
#घोषणा QMI_WLANFW_RESPOND_MEM_RESP_V01			0x0036
#घोषणा QMI_WLANFW_MAX_NUM_MEM_CFG_V01			2

काष्ठा qmi_wlanfw_mem_cfg_s_v01 अणु
	u64 offset;
	u32 size;
	u8 secure_flag;
पूर्ण;

क्रमागत qmi_wlanfw_mem_type_क्रमागत_v01 अणु
	WLANFW_MEM_TYPE_ENUM_MIN_VAL_V01 = पूर्णांक_न्यून,
	QMI_WLANFW_MEM_TYPE_MSA_V01 = 0,
	QMI_WLANFW_MEM_TYPE_DDR_V01 = 1,
	QMI_WLANFW_MEM_BDF_V01 = 2,
	QMI_WLANFW_MEM_M3_V01 = 3,
	QMI_WLANFW_MEM_CAL_V01 = 4,
	QMI_WLANFW_MEM_DPD_V01 = 5,
	WLANFW_MEM_TYPE_ENUM_MAX_VAL_V01 = पूर्णांक_उच्च,
पूर्ण;

काष्ठा qmi_wlanfw_mem_seg_s_v01 अणु
	u32 size;
	क्रमागत qmi_wlanfw_mem_type_क्रमागत_v01 type;
	u32 mem_cfg_len;
	काष्ठा qmi_wlanfw_mem_cfg_s_v01 mem_cfg[QMI_WLANFW_MAX_NUM_MEM_CFG_V01];
पूर्ण;

काष्ठा qmi_wlanfw_request_mem_ind_msg_v01 अणु
	u32 mem_seg_len;
	काष्ठा qmi_wlanfw_mem_seg_s_v01 mem_seg[ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01];
पूर्ण;

काष्ठा qmi_wlanfw_mem_seg_resp_s_v01 अणु
	u64 addr;
	u32 size;
	क्रमागत qmi_wlanfw_mem_type_क्रमागत_v01 type;
	u8 restore;
पूर्ण;

काष्ठा qmi_wlanfw_respond_mem_req_msg_v01 अणु
	u32 mem_seg_len;
	काष्ठा qmi_wlanfw_mem_seg_resp_s_v01 mem_seg[ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01];
पूर्ण;

काष्ठा qmi_wlanfw_respond_mem_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

काष्ठा qmi_wlanfw_fw_mem_पढ़ोy_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

काष्ठा qmi_wlanfw_fw_पढ़ोy_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

काष्ठा qmi_wlanfw_fw_cold_cal_करोne_ind_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा QMI_WLANFW_CAP_REQ_MSG_V01_MAX_LEN	0
#घोषणा QMI_WLANFW_CAP_RESP_MSG_V01_MAX_LEN	207
#घोषणा QMI_WLANFW_CAP_REQ_V01			0x0024
#घोषणा QMI_WLANFW_CAP_RESP_V01			0x0024

क्रमागत qmi_wlanfw_pipedir_क्रमागत_v01 अणु
	QMI_WLFW_PIPEसूची_NONE_V01 = 0,
	QMI_WLFW_PIPEसूची_IN_V01 = 1,
	QMI_WLFW_PIPEसूची_OUT_V01 = 2,
	QMI_WLFW_PIPEसूची_INOUT_V01 = 3,
पूर्ण;

काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01 अणु
	__le32 pipe_num;
	__le32 pipe_dir;
	__le32 nentries;
	__le32 nbytes_max;
	__le32 flags;
पूर्ण;

काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01 अणु
	__le32 service_id;
	__le32 pipe_dir;
	__le32 pipe_num;
पूर्ण;

काष्ठा qmi_wlanfw_shaकरोw_reg_cfg_s_v01 अणु
	u16 id;
	u16 offset;
पूर्ण;

काष्ठा qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01 अणु
	u32 addr;
पूर्ण;

काष्ठा qmi_wlanfw_memory_region_info_s_v01 अणु
	u64 region_addr;
	u32 size;
	u8 secure_flag;
पूर्ण;

काष्ठा qmi_wlanfw_rf_chip_info_s_v01 अणु
	u32 chip_id;
	u32 chip_family;
पूर्ण;

काष्ठा qmi_wlanfw_rf_board_info_s_v01 अणु
	u32 board_id;
पूर्ण;

काष्ठा qmi_wlanfw_soc_info_s_v01 अणु
	u32 soc_id;
पूर्ण;

काष्ठा qmi_wlanfw_fw_version_info_s_v01 अणु
	u32 fw_version;
	अक्षर fw_build_बारtamp[ATH11K_QMI_WLANFW_MAX_TIMESTAMP_LEN_V01 + 1];
पूर्ण;

क्रमागत qmi_wlanfw_cal_temp_id_क्रमागत_v01 अणु
	QMI_WLANFW_CAL_TEMP_IDX_0_V01 = 0,
	QMI_WLANFW_CAL_TEMP_IDX_1_V01 = 1,
	QMI_WLANFW_CAL_TEMP_IDX_2_V01 = 2,
	QMI_WLANFW_CAL_TEMP_IDX_3_V01 = 3,
	QMI_WLANFW_CAL_TEMP_IDX_4_V01 = 4,
	QMI_WLANFW_CAL_TEMP_ID_MAX_V01 = 0xFF,
पूर्ण;

काष्ठा qmi_wlanfw_cap_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
	u8 chip_info_valid;
	काष्ठा qmi_wlanfw_rf_chip_info_s_v01 chip_info;
	u8 board_info_valid;
	काष्ठा qmi_wlanfw_rf_board_info_s_v01 board_info;
	u8 soc_info_valid;
	काष्ठा qmi_wlanfw_soc_info_s_v01 soc_info;
	u8 fw_version_info_valid;
	काष्ठा qmi_wlanfw_fw_version_info_s_v01 fw_version_info;
	u8 fw_build_id_valid;
	अक्षर fw_build_id[ATH11K_QMI_WLANFW_MAX_BUILD_ID_LEN_V01 + 1];
	u8 num_macs_valid;
	u8 num_macs;
पूर्ण;

काष्ठा qmi_wlanfw_cap_req_msg_v01 अणु
	अक्षर placeholder;
पूर्ण;

#घोषणा QMI_WLANFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_LEN	6182
#घोषणा QMI_WLANFW_BDF_DOWNLOAD_RESP_MSG_V01_MAX_LEN	7
#घोषणा QMI_WLANFW_BDF_DOWNLOAD_RESP_V01		0x0025
#घोषणा QMI_WLANFW_BDF_DOWNLOAD_REQ_V01			0x0025
/* TODO: Need to check with MCL and FW team that data can be poपूर्णांकer and
 * can be last element in काष्ठाure
 */
काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01 अणु
	u8 valid;
	u8 file_id_valid;
	क्रमागत qmi_wlanfw_cal_temp_id_क्रमागत_v01 file_id;
	u8 total_size_valid;
	u32 total_size;
	u8 seg_id_valid;
	u32 seg_id;
	u8 data_valid;
	u32 data_len;
	u8 data[QMI_WLANFW_MAX_DATA_SIZE_V01];
	u8 end_valid;
	u8 end;
	u8 bdf_type_valid;
	u8 bdf_type;

पूर्ण;

काष्ठा qmi_wlanfw_bdf_करोwnload_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा QMI_WLANFW_M3_INFO_REQ_MSG_V01_MAX_MSG_LEN	18
#घोषणा QMI_WLANFW_M3_INFO_RESP_MSG_V01_MAX_MSG_LEN	7
#घोषणा QMI_WLANFW_M3_INFO_RESP_V01		0x003C
#घोषणा QMI_WLANFW_M3_INFO_REQ_V01		0x003C

काष्ठा qmi_wlanfw_m3_info_req_msg_v01 अणु
	u64 addr;
	u32 size;
पूर्ण;

काष्ठा qmi_wlanfw_m3_info_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

#घोषणा QMI_WLANFW_WLAN_MODE_REQ_MSG_V01_MAX_LEN	11
#घोषणा QMI_WLANFW_WLAN_MODE_RESP_MSG_V01_MAX_LEN	7
#घोषणा QMI_WLANFW_WLAN_CFG_REQ_MSG_V01_MAX_LEN		803
#घोषणा QMI_WLANFW_WLAN_CFG_RESP_MSG_V01_MAX_LEN	7
#घोषणा QMI_WLANFW_WLAN_MODE_REQ_V01			0x0022
#घोषणा QMI_WLANFW_WLAN_MODE_RESP_V01			0x0022
#घोषणा QMI_WLANFW_WLAN_CFG_REQ_V01			0x0023
#घोषणा QMI_WLANFW_WLAN_CFG_RESP_V01			0x0023
#घोषणा QMI_WLANFW_MAX_STR_LEN_V01			16
#घोषणा QMI_WLANFW_MAX_NUM_CE_V01			12
#घोषणा QMI_WLANFW_MAX_NUM_SVC_V01			24
#घोषणा QMI_WLANFW_MAX_NUM_SHADOW_REG_V01		24
#घोषणा QMI_WLANFW_MAX_NUM_SHADOW_REG_V2_V01		36

काष्ठा qmi_wlanfw_wlan_mode_req_msg_v01 अणु
	u32 mode;
	u8 hw_debug_valid;
	u8 hw_debug;
पूर्ण;

काष्ठा qmi_wlanfw_wlan_mode_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01 अणु
	u8 host_version_valid;
	अक्षर host_version[QMI_WLANFW_MAX_STR_LEN_V01 + 1];
	u8  tgt_cfg_valid;
	u32  tgt_cfg_len;
	काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01
			tgt_cfg[QMI_WLANFW_MAX_NUM_CE_V01];
	u8  svc_cfg_valid;
	u32 svc_cfg_len;
	काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01
			svc_cfg[QMI_WLANFW_MAX_NUM_SVC_V01];
	u8 shaकरोw_reg_valid;
	u32 shaकरोw_reg_len;
	काष्ठा qmi_wlanfw_shaकरोw_reg_cfg_s_v01
		shaकरोw_reg[QMI_WLANFW_MAX_NUM_SHADOW_REG_V01];
	u8 shaकरोw_reg_v2_valid;
	u32 shaकरोw_reg_v2_len;
	काष्ठा qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01
		shaकरोw_reg_v2[QMI_WLANFW_MAX_NUM_SHADOW_REG_V2_V01];
पूर्ण;

काष्ठा qmi_wlanfw_wlan_cfg_resp_msg_v01 अणु
	काष्ठा qmi_response_type_v01 resp;
पूर्ण;

पूर्णांक ath11k_qmi_firmware_start(काष्ठा ath11k_base *ab,
			      u32 mode);
व्योम ath11k_qmi_firmware_stop(काष्ठा ath11k_base *ab);
व्योम ath11k_qmi_event_work(काष्ठा work_काष्ठा *work);
व्योम ath11k_qmi_msg_recv_work(काष्ठा work_काष्ठा *work);
व्योम ath11k_qmi_deinit_service(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_qmi_init_service(काष्ठा ath11k_base *ab);

#पूर्ण_अगर
