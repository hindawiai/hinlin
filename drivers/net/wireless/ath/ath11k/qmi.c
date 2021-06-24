<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/elf.h>

#समावेश "qmi.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश <linux/of.h>
#समावेश <linux/firmware.h>

#घोषणा SLEEP_CLOCK_SELECT_INTERNAL_BIT	0x02
#घोषणा HOST_CSTATE_BIT			0x04

bool ath11k_cold_boot_cal = 1;
EXPORT_SYMBOL(ath11k_cold_boot_cal);
module_param_named(cold_boot_cal, ath11k_cold_boot_cal, bool, 0644);
MODULE_PARM_DESC(cold_boot_cal,
		 "Decrease the channel switch time but increase the driver load time (Default: true)");

अटल काष्ठा qmi_elem_info qmi_wlanfw_host_cap_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   num_clients_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   num_clients),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   wake_msi_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   wake_msi),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   gpios_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   gpios_len),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= QMI_WLFW_MAX_NUM_GPIO_V01,
		.elem_size	= माप(u32),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   gpios),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   nm_modem_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   nm_modem),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_cache_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_cache_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   m3_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   m3_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   m3_cache_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   m3_cache_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_filesys_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_filesys_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_cache_support_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_cache_support),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_करोne_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   cal_करोne),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   mem_bucket_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   mem_bucket),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   mem_cfg_mode_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_req_msg_v01,
					   mem_cfg_mode),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_host_cap_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_host_cap_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_ind_रेजिस्टर_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_करोwnload_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_करोwnload_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_update_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   initiate_cal_update_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   msa_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   msa_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   pin_connect_result_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   pin_connect_result_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   client_id_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   client_id),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   request_mem_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   request_mem_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_mem_पढ़ोy_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_mem_पढ़ोy_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_init_करोne_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   fw_init_करोne_enable),
	पूर्ण,

	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   rejuvenate_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   rejuvenate_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   xo_cal_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   xo_cal_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   cal_करोne_enable_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01,
					   cal_करोne_enable),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01,
					   fw_status_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01,
					   fw_status),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_mem_cfg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_cfg_s_v01, offset),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_cfg_s_v01, size),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_cfg_s_v01, secure_flag),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_mem_seg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_s_v01,
				  size),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(क्रमागत qmi_wlanfw_mem_type_क्रमागत_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_s_v01, type),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_s_v01, mem_cfg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_MEM_CFG_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_mem_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_s_v01, mem_cfg),
		.ei_array	= qmi_wlanfw_mem_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_request_mem_ind_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_request_mem_ind_msg_v01,
					   mem_seg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_mem_seg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_request_mem_ind_msg_v01,
					   mem_seg),
		.ei_array	= qmi_wlanfw_mem_seg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_mem_seg_resp_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_resp_s_v01, addr),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_resp_s_v01, size),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(क्रमागत qmi_wlanfw_mem_type_क्रमागत_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_resp_s_v01, type),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_mem_seg_resp_s_v01, restore),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_respond_mem_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_respond_mem_req_msg_v01,
					   mem_seg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_mem_seg_resp_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_respond_mem_req_msg_v01,
					   mem_seg),
		.ei_array	= qmi_wlanfw_mem_seg_resp_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_respond_mem_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_respond_mem_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_cap_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_rf_chip_info_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_rf_chip_info_s_v01,
					   chip_id),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_rf_chip_info_s_v01,
					   chip_family),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_rf_board_info_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_rf_board_info_s_v01,
					   board_id),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_soc_info_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_soc_info_s_v01, soc_id),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_fw_version_info_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_fw_version_info_s_v01,
					   fw_version),
	पूर्ण,
	अणु
		.data_type	= QMI_STRING,
		.elem_len	= ATH11K_QMI_WLANFW_MAX_TIMESTAMP_LEN_V01 + 1,
		.elem_size	= माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_fw_version_info_s_v01,
					   fw_build_बारtamp),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_cap_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   chip_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_wlanfw_rf_chip_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   chip_info),
		.ei_array	= qmi_wlanfw_rf_chip_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   board_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_wlanfw_rf_board_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   board_info),
		.ei_array	= qmi_wlanfw_rf_board_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   soc_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_wlanfw_soc_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   soc_info),
		.ei_array	= qmi_wlanfw_soc_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   fw_version_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_wlanfw_fw_version_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   fw_version_info),
		.ei_array	= qmi_wlanfw_fw_version_info_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   fw_build_id_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRING,
		.elem_len	= ATH11K_QMI_WLANFW_MAX_BUILD_ID_LEN_V01 + 1,
		.elem_size	= माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   fw_build_id),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   num_macs_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_cap_resp_msg_v01,
					   num_macs),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_bdf_करोwnload_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   valid),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   file_id_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(क्रमागत qmi_wlanfw_cal_temp_id_क्रमागत_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   file_id),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   total_size_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   total_size),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   seg_id_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   seg_id),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   data_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   data_len),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= QMI_WLANFW_MAX_DATA_SIZE_V01,
		.elem_size	= माप(u8),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   data),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   end_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   end),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   bdf_type_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01,
					   bdf_type),
	पूर्ण,

	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_bdf_करोwnload_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_bdf_करोwnload_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_m3_info_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_m3_info_req_msg_v01, addr),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_m3_info_req_msg_v01, size),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_m3_info_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_m3_info_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_ce_tgt_pipe_cfg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_num),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(क्रमागत qmi_wlanfw_pipedir_क्रमागत_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_dir),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   nentries),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   nbytes_max),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   flags),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_ce_svc_pipe_cfg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   service_id),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= माप(क्रमागत qmi_wlanfw_pipedir_क्रमागत_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   pipe_dir),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   pipe_num),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_shaकरोw_reg_cfg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_shaकरोw_reg_cfg_s_v01, id),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_shaकरोw_reg_cfg_s_v01,
					   offset),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01,
					   addr),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_wlan_mode_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_mode_req_msg_v01,
					   mode),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_mode_req_msg_v01,
					   hw_debug_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_mode_req_msg_v01,
					   hw_debug),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_wlan_mode_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_mode_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_wlan_cfg_req_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   host_version_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRING,
		.elem_len	= QMI_WLANFW_MAX_STR_LEN_V01 + 1,
		.elem_size	= माप(अक्षर),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   host_version),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_CE_V01,
		.elem_size	= माप(
				काष्ठा qmi_wlanfw_ce_tgt_pipe_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg),
		.ei_array	= qmi_wlanfw_ce_tgt_pipe_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SVC_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_ce_svc_pipe_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg),
		.ei_array	= qmi_wlanfw_ce_svc_pipe_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SHADOW_REG_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_shaकरोw_reg_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg),
		.ei_array	= qmi_wlanfw_shaकरोw_reg_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= माप(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2_len),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SHADOW_REG_V2_V01,
		.elem_size	= माप(काष्ठा qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shaकरोw_reg_v2),
		.ei_array	= qmi_wlanfw_shaकरोw_reg_v2_cfg_s_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_wlan_cfg_resp_msg_v01_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= माप(काष्ठा qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा qmi_wlanfw_wlan_cfg_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_mem_पढ़ोy_ind_msg_v01_ei[] = अणु
	अणु
		.data_type = QMI_EOTI,
		.array_type = NO_ARRAY,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_fw_पढ़ोy_ind_msg_v01_ei[] = अणु
	अणु
		.data_type = QMI_EOTI,
		.array_type = NO_ARRAY,
	पूर्ण,
पूर्ण;

अटल काष्ठा qmi_elem_info qmi_wlanfw_cold_boot_cal_करोne_ind_msg_v01_ei[] = अणु
	अणु
		.data_type = QMI_EOTI,
		.array_type = NO_ARRAY,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ath11k_qmi_host_cap_send(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_host_cap_req_msg_v01 req;
	काष्ठा qmi_wlanfw_host_cap_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	req.num_clients_valid = 1;
	req.num_clients = 1;
	req.mem_cfg_mode = ab->qmi.target_mem_mode;
	req.mem_cfg_mode_valid = 1;
	req.bdf_support_valid = 1;
	req.bdf_support = 1;

	अगर (ab->bus_params.m3_fw_support) अणु
		req.m3_support_valid = 1;
		req.m3_support = 1;
		req.m3_cache_support_valid = 1;
		req.m3_cache_support = 1;
	पूर्ण अन्यथा अणु
		req.m3_support_valid = 0;
		req.m3_support = 0;
		req.m3_cache_support_valid = 0;
		req.m3_cache_support = 0;
	पूर्ण

	req.cal_करोne_valid = 1;
	req.cal_करोne = ab->qmi.cal_करोne;

	अगर (ab->hw_params.पूर्णांकernal_sleep_घड़ी) अणु
		req.nm_modem_valid = 1;

		/* Notअगरy firmware that this is non-qualcomm platक्रमm. */
		req.nm_modem |= HOST_CSTATE_BIT;

		/* Notअगरy firmware about the sleep घड़ी selection,
		 * nm_modem_bit[1] is used क्रम this purpose. Host driver on
		 * non-qualcomm platक्रमms should select पूर्णांकernal sleep
		 * घड़ी.
		 */
		req.nm_modem |= SLEEP_CLOCK_SELECT_INTERNAL_BIT;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi host cap request\n");

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_host_cap_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_HOST_CAP_REQ_V01,
			       QMI_WLANFW_HOST_CAP_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_host_cap_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send host capability request: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0)
		जाओ out;

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "host capability request failed: %d %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_fw_ind_रेजिस्टर_send(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_ind_रेजिस्टर_req_msg_v01 *req;
	काष्ठा qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01 *resp;
	काष्ठा qmi_handle *handle = &ab->qmi.handle;
	काष्ठा qmi_txn txn;
	पूर्णांक ret;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	resp = kzalloc(माप(*resp), GFP_KERNEL);
	अगर (!resp) अणु
		ret = -ENOMEM;
		जाओ resp_out;
	पूर्ण

	req->client_id_valid = 1;
	req->client_id = QMI_WLANFW_CLIENT_ID;
	req->fw_पढ़ोy_enable_valid = 1;
	req->fw_पढ़ोy_enable = 1;
	req->request_mem_enable_valid = 1;
	req->request_mem_enable = 1;
	req->fw_mem_पढ़ोy_enable_valid = 1;
	req->fw_mem_पढ़ोy_enable = 1;
	req->cal_करोne_enable_valid = 1;
	req->cal_करोne_enable = 1;
	req->fw_init_करोne_enable_valid = 1;
	req->fw_init_करोne_enable = 1;

	req->pin_connect_result_enable_valid = 0;
	req->pin_connect_result_enable = 0;

	ret = qmi_txn_init(handle, &txn,
			   qmi_wlanfw_ind_रेजिस्टर_resp_msg_v01_ei, resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi indication register request\n");

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_IND_REGISTER_REQ_V01,
			       QMI_WLANFW_IND_REGISTER_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_ind_रेजिस्टर_req_msg_v01_ei, req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send indication register request: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to register fw indication: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (resp->resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "firmware indication register request failed: %d %d\n",
			    resp->resp.result, resp->resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	kमुक्त(resp);
resp_out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_respond_fw_mem_request(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_respond_mem_req_msg_v01 *req;
	काष्ठा qmi_wlanfw_respond_mem_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0, i;
	bool delayed;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	स_रखो(&resp, 0, माप(resp));

	/* For QCA6390 by शेष FW requests a block of ~4M contiguous
	 * DMA memory, it's hard to allocate from OS. So host वापसs
	 * failure to FW and FW will then request mulitple blocks of small
	 * chunk size memory.
	 */
	अगर (!ab->bus_params.fixed_mem_region && ab->qmi.target_mem_delayed) अणु
		delayed = true;
		ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi delays mem_request %d\n",
			   ab->qmi.mem_seg_count);
		स_रखो(req, 0, माप(*req));
	पूर्ण अन्यथा अणु
		delayed = false;
		req->mem_seg_len = ab->qmi.mem_seg_count;

		क्रम (i = 0; i < req->mem_seg_len ; i++) अणु
			req->mem_seg[i].addr = ab->qmi.target_mem[i].paddr;
			req->mem_seg[i].size = ab->qmi.target_mem[i].size;
			req->mem_seg[i].type = ab->qmi.target_mem[i].type;
			ath11k_dbg(ab, ATH11K_DBG_QMI,
				   "qmi req mem_seg[%d] %pad %u %u\n", i,
				    &ab->qmi.target_mem[i].paddr,
				    ab->qmi.target_mem[i].size,
				    ab->qmi.target_mem[i].type);
		पूर्ण
	पूर्ण

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_respond_mem_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi respond memory request delayed %i\n",
		   delayed);

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_RESPOND_MEM_REQ_V01,
			       QMI_WLANFW_RESPOND_MEM_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_respond_mem_req_msg_v01_ei, req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to respond qmi memory request: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to wait qmi memory request: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		/* the error response is expected when
		 * target_mem_delayed is true.
		 */
		अगर (delayed && resp.resp.error == 0)
			जाओ out;

		ath11k_warn(ab, "qmi respond memory request failed: %d %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल व्योम ath11k_qmi_मुक्त_target_mem_chunk(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	अगर (ab->bus_params.fixed_mem_region)
		वापस;

	क्रम (i = 0; i < ab->qmi.mem_seg_count; i++) अणु
		अगर (!ab->qmi.target_mem[i].vaddr)
			जारी;

		dma_मुक्त_coherent(ab->dev,
				  ab->qmi.target_mem[i].size,
				  ab->qmi.target_mem[i].vaddr,
				  ab->qmi.target_mem[i].paddr);
		ab->qmi.target_mem[i].vaddr = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_qmi_alloc_target_mem_chunk(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;
	काष्ठा target_mem_chunk *chunk;

	ab->qmi.target_mem_delayed = false;

	क्रम (i = 0; i < ab->qmi.mem_seg_count; i++) अणु
		chunk = &ab->qmi.target_mem[i];
		chunk->vaddr = dma_alloc_coherent(ab->dev,
						  chunk->size,
						  &chunk->paddr,
						  GFP_KERNEL);
		अगर (!chunk->vaddr) अणु
			अगर (ab->qmi.mem_seg_count <= ATH11K_QMI_FW_MEM_REQ_SEGMENT_CNT) अणु
				ath11k_dbg(ab, ATH11K_DBG_QMI,
					   "qmi dma allocation failed (%d B type %u), will try later with small size\n",
					    chunk->size,
					    chunk->type);
				ath11k_qmi_मुक्त_target_mem_chunk(ab);
				ab->qmi.target_mem_delayed = true;
				वापस 0;
			पूर्ण

			ath11k_err(ab, "failed to allocate dma memory for qmi (%d B type %u)\n",
				   chunk->size,
				   chunk->type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_qmi_assign_target_mem_chunk(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, idx;

	क्रम (i = 0, idx = 0; i < ab->qmi.mem_seg_count; i++) अणु
		चयन (ab->qmi.target_mem[i].type) अणु
		हाल BDF_MEM_REGION_TYPE:
			ab->qmi.target_mem[idx].paddr = ab->hw_params.bdf_addr;
			ab->qmi.target_mem[idx].vaddr = शून्य;
			ab->qmi.target_mem[idx].size = ab->qmi.target_mem[i].size;
			ab->qmi.target_mem[idx].type = ab->qmi.target_mem[i].type;
			idx++;
			अवरोध;
		हाल CALDB_MEM_REGION_TYPE:
			अगर (ab->qmi.target_mem[i].size > ATH11K_QMI_CALDB_SIZE) अणु
				ath11k_warn(ab, "qmi mem size is low to load caldata\n");
				वापस -EINVAL;
			पूर्ण

			अगर (ath11k_cold_boot_cal && ab->hw_params.cold_boot_calib) अणु
				ab->qmi.target_mem[idx].paddr =
						     ATH11K_QMI_CALDB_ADDRESS;
				ab->qmi.target_mem[idx].vaddr =
						     (व्योम *)ATH11K_QMI_CALDB_ADDRESS;
			पूर्ण अन्यथा अणु
				ab->qmi.target_mem[idx].paddr = 0;
				ab->qmi.target_mem[idx].vaddr = शून्य;
			पूर्ण
			ab->qmi.target_mem[idx].size = ab->qmi.target_mem[i].size;
			ab->qmi.target_mem[idx].type = ab->qmi.target_mem[i].type;
			idx++;
			अवरोध;
		शेष:
			ath11k_warn(ab, "qmi ignore invalid mem req type %d\n",
				    ab->qmi.target_mem[i].type);
			अवरोध;
		पूर्ण
	पूर्ण
	ab->qmi.mem_seg_count = idx;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_qmi_request_target_cap(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_cap_req_msg_v01 req;
	काष्ठा qmi_wlanfw_cap_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0;
	पूर्णांक r;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_cap_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi target cap request\n");

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_CAP_REQ_V01,
			       QMI_WLANFW_CAP_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_cap_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send qmi cap request: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to wait qmi cap request: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "qmi cap request failed: %d %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp.chip_info_valid) अणु
		ab->qmi.target.chip_id = resp.chip_info.chip_id;
		ab->qmi.target.chip_family = resp.chip_info.chip_family;
	पूर्ण

	अगर (resp.board_info_valid)
		ab->qmi.target.board_id = resp.board_info.board_id;
	अन्यथा
		ab->qmi.target.board_id = 0xFF;

	अगर (resp.soc_info_valid)
		ab->qmi.target.soc_id = resp.soc_info.soc_id;

	अगर (resp.fw_version_info_valid) अणु
		ab->qmi.target.fw_version = resp.fw_version_info.fw_version;
		strlcpy(ab->qmi.target.fw_build_बारtamp,
			resp.fw_version_info.fw_build_बारtamp,
			माप(ab->qmi.target.fw_build_बारtamp));
	पूर्ण

	अगर (resp.fw_build_id_valid)
		strlcpy(ab->qmi.target.fw_build_id, resp.fw_build_id,
			माप(ab->qmi.target.fw_build_id));

	ath11k_info(ab, "chip_id 0x%x chip_family 0x%x board_id 0x%x soc_id 0x%x\n",
		    ab->qmi.target.chip_id, ab->qmi.target.chip_family,
		    ab->qmi.target.board_id, ab->qmi.target.soc_id);

	ath11k_info(ab, "fw_version 0x%x fw_build_timestamp %s fw_build_id %s",
		    ab->qmi.target.fw_version,
		    ab->qmi.target.fw_build_बारtamp,
		    ab->qmi.target.fw_build_id);

	r = ath11k_core_check_dt(ab);
	अगर (r)
		ath11k_dbg(ab, ATH11K_DBG_QMI, "DT bdf variant name not set.\n");

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
ath11k_qmi_prepare_bdf_करोwnload(काष्ठा ath11k_base *ab, पूर्णांक type,
				काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01 *req,
				व्योम __iomem *bdf_addr)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा ath11k_board_data bd;
	u32 fw_size;
	पूर्णांक ret;

	चयन (type) अणु
	हाल ATH11K_QMI_खाता_TYPE_BDF_GOLDEN:
		स_रखो(&bd, 0, माप(bd));

		ret = ath11k_core_fetch_bdf(ab, &bd);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to load board file: %d\n", ret);
			वापस ret;
		पूर्ण

		fw_size = min_t(u32, ab->hw_params.fw.board_size, bd.len);
		स_नकल_toio(bdf_addr, bd.data, fw_size);
		ath11k_core_मुक्त_bdf(ab, &bd);
		अवरोध;
	हाल ATH11K_QMI_खाता_TYPE_CALDATA:
		fw_entry = ath11k_core_firmware_request(ab, ATH11K_DEFAULT_CAL_खाता);
		अगर (IS_ERR(fw_entry)) अणु
			ret = PTR_ERR(fw_entry);
			ath11k_warn(ab, "failed to load %s: %d\n",
				    ATH11K_DEFAULT_CAL_खाता, ret);
			वापस ret;
		पूर्ण

		fw_size = min_t(u32, ab->hw_params.fw.board_size,
				fw_entry->size);

		स_नकल_toio(bdf_addr + ATH11K_QMI_CALDATA_OFFSET,
			    fw_entry->data, fw_size);

		release_firmware(fw_entry);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	req->total_size = fw_size;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_qmi_load_bdf_fixed_addr(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01 *req;
	काष्ठा qmi_wlanfw_bdf_करोwnload_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	व्योम __iomem *bdf_addr = शून्य;
	पूर्णांक type, ret;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;
	स_रखो(&resp, 0, माप(resp));

	bdf_addr = ioremap(ab->hw_params.bdf_addr, ATH11K_QMI_BDF_MAX_SIZE);
	अगर (!bdf_addr) अणु
		ath11k_warn(ab, "failed ioremap for board file\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	क्रम (type = 0; type < ATH11K_QMI_MAX_खाता_TYPE; type++) अणु
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = ab->qmi.target.board_id;
		req->total_size_valid = 1;
		req->seg_id_valid = 1;
		req->seg_id = type;
		req->data_valid = 0;
		req->data_len = ATH11K_QMI_MAX_BDF_खाता_NAME_SIZE;
		req->bdf_type = 0;
		req->bdf_type_valid = 0;
		req->end_valid = 1;
		req->end = 1;

		ret = ath11k_qmi_prepare_bdf_करोwnload(ab, type, req, bdf_addr);
		अगर (ret < 0)
			जाओ out_qmi_bdf;

		ret = qmi_txn_init(&ab->qmi.handle, &txn,
				   qmi_wlanfw_bdf_करोwnload_resp_msg_v01_ei,
				   &resp);
		अगर (ret < 0)
			जाओ out_qmi_bdf;

		ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi bdf download req fixed addr type %d\n",
			   type);

		ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_V01,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_LEN,
				       qmi_wlanfw_bdf_करोwnload_req_msg_v01_ei, req);
		अगर (ret < 0) अणु
			qmi_txn_cancel(&txn);
			जाओ out_qmi_bdf;
		पूर्ण

		ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
		अगर (ret < 0)
			जाओ out_qmi_bdf;

		अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
			ath11k_warn(ab, "board file download request failed: %d %d\n",
				    resp.resp.result, resp.resp.error);
			ret = -EINVAL;
			जाओ out_qmi_bdf;
		पूर्ण
	पूर्ण

out_qmi_bdf:
	iounmap(bdf_addr);
out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_load_bdf_qmi(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_bdf_करोwnload_req_msg_v01 *req;
	काष्ठा qmi_wlanfw_bdf_करोwnload_resp_msg_v01 resp;
	काष्ठा ath11k_board_data bd;
	अचिन्हित पूर्णांक reमुख्यing;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret;
	स्थिर u8 *temp;
	पूर्णांक bdf_type;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;
	स_रखो(&resp, 0, माप(resp));

	स_रखो(&bd, 0, माप(bd));
	ret = ath11k_core_fetch_bdf(ab, &bd);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to fetch board file: %d\n", ret);
		जाओ out;
	पूर्ण

	temp = bd.data;
	reमुख्यing = bd.len;

	अगर (bd.len >= SELFMAG && स_भेद(bd.data, ELFMAG, SELFMAG) == 0)
		bdf_type = ATH11K_QMI_BDF_TYPE_ELF;
	अन्यथा
		bdf_type = ATH11K_QMI_BDF_TYPE_BIN;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi bdf_type %d\n", bdf_type);

	जबतक (reमुख्यing) अणु
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = ab->qmi.target.board_id;
		req->total_size_valid = 1;
		req->total_size = bd.len;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->data_len = ATH11K_QMI_MAX_BDF_खाता_NAME_SIZE;
		req->bdf_type = bdf_type;
		req->bdf_type_valid = 1;
		req->end_valid = 1;
		req->end = 0;

		अगर (reमुख्यing > QMI_WLANFW_MAX_DATA_SIZE_V01) अणु
			req->data_len = QMI_WLANFW_MAX_DATA_SIZE_V01;
		पूर्ण अन्यथा अणु
			req->data_len = reमुख्यing;
			req->end = 1;
		पूर्ण

		स_नकल(req->data, temp, req->data_len);

		ret = qmi_txn_init(&ab->qmi.handle, &txn,
				   qmi_wlanfw_bdf_करोwnload_resp_msg_v01_ei,
				   &resp);
		अगर (ret < 0)
			जाओ out_qmi_bdf;

		ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi bdf download request remaining %i\n",
			   reमुख्यing);

		ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_V01,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_LEN,
				       qmi_wlanfw_bdf_करोwnload_req_msg_v01_ei, req);
		अगर (ret < 0) अणु
			qmi_txn_cancel(&txn);
			जाओ out_qmi_bdf;
		पूर्ण

		ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
		अगर (ret < 0)
			जाओ out_qmi_bdf;

		अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
			ath11k_warn(ab, "bdf download request failed: %d %d\n",
				    resp.resp.result, resp.resp.error);
			ret = resp.resp.result;
			जाओ out_qmi_bdf;
		पूर्ण
		reमुख्यing -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
	पूर्ण

out_qmi_bdf:
	ath11k_core_मुक्त_bdf(ab, &bd);

out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_m3_load(काष्ठा ath11k_base *ab)
अणु
	काष्ठा m3_mem_region *m3_mem = &ab->qmi.m3_mem;
	स्थिर काष्ठा firmware *fw;
	अक्षर path[100];
	पूर्णांक ret;

	अगर (m3_mem->vaddr || m3_mem->size)
		वापस 0;

	fw = ath11k_core_firmware_request(ab, ATH11K_M3_खाता);
	अगर (IS_ERR(fw)) अणु
		ret = PTR_ERR(fw);
		ath11k_core_create_firmware_path(ab, ATH11K_M3_खाता,
						 path, माप(path));
		ath11k_err(ab, "failed to load %s: %d\n", path, ret);
		वापस ret;
	पूर्ण

	m3_mem->vaddr = dma_alloc_coherent(ab->dev,
					   fw->size, &m3_mem->paddr,
					   GFP_KERNEL);
	अगर (!m3_mem->vaddr) अणु
		ath11k_err(ab, "failed to allocate memory for M3 with size %zu\n",
			   fw->size);
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(m3_mem->vaddr, fw->data, fw->size);
	m3_mem->size = fw->size;
	release_firmware(fw);

	वापस 0;
पूर्ण

अटल व्योम ath11k_qmi_m3_मुक्त(काष्ठा ath11k_base *ab)
अणु
	काष्ठा m3_mem_region *m3_mem = &ab->qmi.m3_mem;

	अगर (!ab->bus_params.m3_fw_support || !m3_mem->vaddr)
		वापस;

	dma_मुक्त_coherent(ab->dev, m3_mem->size,
			  m3_mem->vaddr, m3_mem->paddr);
	m3_mem->vaddr = शून्य;
पूर्ण

अटल पूर्णांक ath11k_qmi_wlanfw_m3_info_send(काष्ठा ath11k_base *ab)
अणु
	काष्ठा m3_mem_region *m3_mem = &ab->qmi.m3_mem;
	काष्ठा qmi_wlanfw_m3_info_req_msg_v01 req;
	काष्ठा qmi_wlanfw_m3_info_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	अगर (ab->bus_params.m3_fw_support) अणु
		ret = ath11k_qmi_m3_load(ab);
		अगर (ret) अणु
			ath11k_err(ab, "failed to load m3 firmware: %d", ret);
			वापस ret;
		पूर्ण

		req.addr = m3_mem->paddr;
		req.size = m3_mem->size;
	पूर्ण अन्यथा अणु
		req.addr = 0;
		req.size = 0;
	पूर्ण

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_m3_info_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi m3 info req\n");

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_M3_INFO_REQ_V01,
			       QMI_WLANFW_M3_INFO_REQ_MSG_V01_MAX_MSG_LEN,
			       qmi_wlanfw_m3_info_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send m3 information request: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to wait m3 information request: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "m3 info request failed: %d %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_wlanfw_mode_send(काष्ठा ath11k_base *ab,
				       u32 mode)
अणु
	काष्ठा qmi_wlanfw_wlan_mode_req_msg_v01 req;
	काष्ठा qmi_wlanfw_wlan_mode_resp_msg_v01 resp;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	req.mode = mode;
	req.hw_debug_valid = 1;
	req.hw_debug = 0;

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_wlan_mode_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi wlan mode req mode %d\n", mode);

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_WLAN_MODE_REQ_V01,
			       QMI_WLANFW_WLAN_MODE_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_wlan_mode_req_msg_v01_ei, &req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send wlan mode request (mode %d): %d\n",
			    mode, ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		अगर (mode == ATH11K_FIRMWARE_MODE_OFF && ret == -ENETRESET) अणु
			ath11k_warn(ab, "WLFW service is dis-connected\n");
			वापस 0;
		पूर्ण
		ath11k_warn(ab, "failed to wait wlan mode request (mode %d): %d\n",
			    mode, ret);
		जाओ out;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "wlan mode request failed (mode: %d): %d %d\n",
			    mode, resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_wlanfw_wlan_cfg_send(काष्ठा ath11k_base *ab)
अणु
	काष्ठा qmi_wlanfw_wlan_cfg_req_msg_v01 *req;
	काष्ठा qmi_wlanfw_wlan_cfg_resp_msg_v01 resp;
	काष्ठा ce_pipe_config *ce_cfg;
	काष्ठा service_to_pipe *svc_cfg;
	काष्ठा qmi_txn txn = अणुपूर्ण;
	पूर्णांक ret = 0, pipe_num;

	ce_cfg	= (काष्ठा ce_pipe_config *)ab->qmi.ce_cfg.tgt_ce;
	svc_cfg	= (काष्ठा service_to_pipe *)ab->qmi.ce_cfg.svc_to_ce_map;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	स_रखो(&resp, 0, माप(resp));

	req->host_version_valid = 1;
	strlcpy(req->host_version, ATH11K_HOST_VERSION_STRING,
		माप(req->host_version));

	req->tgt_cfg_valid = 1;
	/* This is number of CE configs */
	req->tgt_cfg_len = ab->qmi.ce_cfg.tgt_ce_len;
	क्रम (pipe_num = 0; pipe_num < req->tgt_cfg_len ; pipe_num++) अणु
		req->tgt_cfg[pipe_num].pipe_num = ce_cfg[pipe_num].pipक्रमागत;
		req->tgt_cfg[pipe_num].pipe_dir = ce_cfg[pipe_num].pipedir;
		req->tgt_cfg[pipe_num].nentries = ce_cfg[pipe_num].nentries;
		req->tgt_cfg[pipe_num].nbytes_max = ce_cfg[pipe_num].nbytes_max;
		req->tgt_cfg[pipe_num].flags = ce_cfg[pipe_num].flags;
	पूर्ण

	req->svc_cfg_valid = 1;
	/* This is number of Service/CE configs */
	req->svc_cfg_len = ab->qmi.ce_cfg.svc_to_ce_map_len;
	क्रम (pipe_num = 0; pipe_num < req->svc_cfg_len; pipe_num++) अणु
		req->svc_cfg[pipe_num].service_id = svc_cfg[pipe_num].service_id;
		req->svc_cfg[pipe_num].pipe_dir = svc_cfg[pipe_num].pipedir;
		req->svc_cfg[pipe_num].pipe_num = svc_cfg[pipe_num].pipक्रमागत;
	पूर्ण
	req->shaकरोw_reg_valid = 0;

	/* set shaकरोw v2 configuration */
	अगर (ab->hw_params.supports_shaकरोw_regs) अणु
		req->shaकरोw_reg_v2_valid = 1;
		req->shaकरोw_reg_v2_len = min_t(u32,
					       ab->qmi.ce_cfg.shaकरोw_reg_v2_len,
					       QMI_WLANFW_MAX_NUM_SHADOW_REG_V2_V01);
		स_नकल(&req->shaकरोw_reg_v2, ab->qmi.ce_cfg.shaकरोw_reg_v2,
		       माप(u32) * req->shaकरोw_reg_v2_len);
	पूर्ण अन्यथा अणु
		req->shaकरोw_reg_v2_valid = 0;
	पूर्ण

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_wlan_cfg_resp_msg_v01_ei, &resp);
	अगर (ret < 0)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi wlan cfg req\n");

	ret = qmi_send_request(&ab->qmi.handle, शून्य, &txn,
			       QMI_WLANFW_WLAN_CFG_REQ_V01,
			       QMI_WLANFW_WLAN_CFG_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_wlan_cfg_req_msg_v01_ei, req);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send wlan config request: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = qmi_txn_रुको(&txn, msecs_to_jअगरfies(ATH11K_QMI_WLANFW_TIMEOUT_MS));
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to wait wlan config request: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (resp.resp.result != QMI_RESULT_SUCCESS_V01) अणु
		ath11k_warn(ab, "wlan config request failed: %d %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	kमुक्त(req);
	वापस ret;
पूर्ण

व्योम ath11k_qmi_firmware_stop(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi firmware stop\n");

	ret = ath11k_qmi_wlanfw_mode_send(ab, ATH11K_FIRMWARE_MODE_OFF);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "qmi failed to send wlan mode off: %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

पूर्णांक ath11k_qmi_firmware_start(काष्ठा ath11k_base *ab,
			      u32 mode)
अणु
	पूर्णांक ret;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi firmware start\n");

	ret = ath11k_qmi_wlanfw_wlan_cfg_send(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "qmi failed to send wlan cfg: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_qmi_wlanfw_mode_send(ab, mode);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "qmi failed to send wlan fw mode: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_qmi_process_coldboot_calibration(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक समयout;
	पूर्णांक ret;

	ret = ath11k_qmi_wlanfw_mode_send(ab, ATH11K_FIRMWARE_MODE_COLD_BOOT);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "qmi failed to send wlan fw mode: %d\n", ret);
		वापस ret;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_QMI, "Coldboot calibration wait started\n");

	समयout = रुको_event_समयout(ab->qmi.cold_boot_रुकोq,
				     (ab->qmi.cal_करोne  == 1),
				     ATH11K_COLD_BOOT_FW_RESET_DELAY);
	अगर (समयout <= 0) अणु
		ath11k_warn(ab, "coldboot calibration timed out\n");
		वापस 0;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_QMI, "Coldboot calibration done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_qmi_driver_event_post(काष्ठा ath11k_qmi *qmi,
			     क्रमागत ath11k_qmi_event_type type,
			     व्योम *data)
अणु
	काष्ठा ath11k_qmi_driver_event *event;

	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस -ENOMEM;

	event->type = type;
	event->data = data;

	spin_lock(&qmi->event_lock);
	list_add_tail(&event->list, &qmi->event_list);
	spin_unlock(&qmi->event_lock);

	queue_work(qmi->event_wq, &qmi->event_work);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_qmi_event_server_arrive(काष्ठा ath11k_qmi *qmi)
अणु
	काष्ठा ath11k_base *ab = qmi->ab;
	पूर्णांक ret;

	ret = ath11k_qmi_fw_ind_रेजिस्टर_send(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send qmi firmware indication: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath11k_qmi_host_cap_send(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send qmi host cap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_event_mem_request(काष्ठा ath11k_qmi *qmi)
अणु
	काष्ठा ath11k_base *ab = qmi->ab;
	पूर्णांक ret;

	ret = ath11k_qmi_respond_fw_mem_request(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "qmi failed to respond fw mem req: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_qmi_event_load_bdf(काष्ठा ath11k_qmi *qmi)
अणु
	काष्ठा ath11k_base *ab = qmi->ab;
	पूर्णांक ret;

	ret = ath11k_qmi_request_target_cap(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to request qmi target capabilities: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	अगर (ab->bus_params.fixed_bdf_addr)
		ret = ath11k_qmi_load_bdf_fixed_addr(ab);
	अन्यथा
		ret = ath11k_qmi_load_bdf_qmi(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to load board data file: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_qmi_wlanfw_m3_info_send(ab);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to send qmi m3 info req: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath11k_qmi_msg_mem_request_cb(काष्ठा qmi_handle *qmi_hdl,
					  काष्ठा sockaddr_qrtr *sq,
					  काष्ठा qmi_txn *txn,
					  स्थिर व्योम *data)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;
	स्थिर काष्ठा qmi_wlanfw_request_mem_ind_msg_v01 *msg = data;
	पूर्णांक i, ret;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi firmware request memory request\n");

	अगर (msg->mem_seg_len == 0 ||
	    msg->mem_seg_len > ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01)
		ath11k_warn(ab, "invalid memory segment length: %u\n",
			    msg->mem_seg_len);

	ab->qmi.mem_seg_count = msg->mem_seg_len;

	क्रम (i = 0; i < qmi->mem_seg_count ; i++) अणु
		ab->qmi.target_mem[i].type = msg->mem_seg[i].type;
		ab->qmi.target_mem[i].size = msg->mem_seg[i].size;
		ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi mem seg type %d size %d\n",
			   msg->mem_seg[i].type, msg->mem_seg[i].size);
	पूर्ण

	अगर (ab->bus_params.fixed_mem_region) अणु
		ret = ath11k_qmi_assign_target_mem_chunk(ab);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to assign qmi target memory: %d\n",
				    ret);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ath11k_qmi_alloc_target_mem_chunk(ab);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to allocate qmi target memory: %d\n",
				    ret);
			वापस;
		पूर्ण
	पूर्ण

	ath11k_qmi_driver_event_post(qmi, ATH11K_QMI_EVENT_REQUEST_MEM, शून्य);
पूर्ण

अटल व्योम ath11k_qmi_msg_mem_पढ़ोy_cb(काष्ठा qmi_handle *qmi_hdl,
					काष्ठा sockaddr_qrtr *sq,
					काष्ठा qmi_txn *txn,
					स्थिर व्योम *decoded)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi firmware memory ready indication\n");
	ath11k_qmi_driver_event_post(qmi, ATH11K_QMI_EVENT_FW_MEM_READY, शून्य);
पूर्ण

अटल व्योम ath11k_qmi_msg_fw_पढ़ोy_cb(काष्ठा qmi_handle *qmi_hdl,
				       काष्ठा sockaddr_qrtr *sq,
				       काष्ठा qmi_txn *txn,
				       स्थिर व्योम *decoded)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi firmware ready\n");
	ath11k_qmi_driver_event_post(qmi, ATH11K_QMI_EVENT_FW_READY, शून्य);
पूर्ण

अटल व्योम ath11k_qmi_msg_cold_boot_cal_करोne_cb(काष्ठा qmi_handle *qmi_hdl,
						 काष्ठा sockaddr_qrtr *sq,
						 काष्ठा qmi_txn *txn,
						 स्थिर व्योम *decoded)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl,
					      काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;

	ab->qmi.cal_करोne = 1;
	wake_up(&ab->qmi.cold_boot_रुकोq);
	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi cold boot calibration done\n");
पूर्ण

अटल स्थिर काष्ठा qmi_msg_handler ath11k_qmi_msg_handlers[] = अणु
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_REQUEST_MEM_IND_V01,
		.ei = qmi_wlanfw_request_mem_ind_msg_v01_ei,
		.decoded_size = माप(काष्ठा qmi_wlanfw_request_mem_ind_msg_v01),
		.fn = ath11k_qmi_msg_mem_request_cb,
	पूर्ण,
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_FW_MEM_READY_IND_V01,
		.ei = qmi_wlanfw_mem_पढ़ोy_ind_msg_v01_ei,
		.decoded_size = माप(काष्ठा qmi_wlanfw_fw_mem_पढ़ोy_ind_msg_v01),
		.fn = ath11k_qmi_msg_mem_पढ़ोy_cb,
	पूर्ण,
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_FW_READY_IND_V01,
		.ei = qmi_wlanfw_fw_पढ़ोy_ind_msg_v01_ei,
		.decoded_size = माप(काष्ठा qmi_wlanfw_fw_पढ़ोy_ind_msg_v01),
		.fn = ath11k_qmi_msg_fw_पढ़ोy_cb,
	पूर्ण,
	अणु
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_COLD_BOOT_CAL_DONE_IND_V01,
		.ei = qmi_wlanfw_cold_boot_cal_करोne_ind_msg_v01_ei,
		.decoded_size =
			माप(काष्ठा qmi_wlanfw_fw_cold_cal_करोne_ind_msg_v01),
		.fn = ath11k_qmi_msg_cold_boot_cal_करोne_cb,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ath11k_qmi_ops_new_server(काष्ठा qmi_handle *qmi_hdl,
				     काष्ठा qmi_service *service)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;
	काष्ठा sockaddr_qrtr *sq = &qmi->sq;
	पूर्णांक ret;

	sq->sq_family = AF_QIPCRTR;
	sq->sq_node = service->node;
	sq->sq_port = service->port;

	ret = kernel_connect(qmi_hdl->sock, (काष्ठा sockaddr *)sq,
			     माप(*sq), 0);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to connect to qmi remote service: %d\n", ret);
		वापस ret;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi wifi fw qmi service connected\n");
	ath11k_qmi_driver_event_post(qmi, ATH11K_QMI_EVENT_SERVER_ARRIVE, शून्य);

	वापस ret;
पूर्ण

अटल व्योम ath11k_qmi_ops_del_server(काष्ठा qmi_handle *qmi_hdl,
				      काष्ठा qmi_service *service)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(qmi_hdl, काष्ठा ath11k_qmi, handle);
	काष्ठा ath11k_base *ab = qmi->ab;

	ath11k_dbg(ab, ATH11K_DBG_QMI, "qmi wifi fw del server\n");
	ath11k_qmi_driver_event_post(qmi, ATH11K_QMI_EVENT_SERVER_EXIT, शून्य);
पूर्ण

अटल स्थिर काष्ठा qmi_ops ath11k_qmi_ops = अणु
	.new_server = ath11k_qmi_ops_new_server,
	.del_server = ath11k_qmi_ops_del_server,
पूर्ण;

अटल व्योम ath11k_qmi_driver_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k_qmi *qmi = container_of(work, काष्ठा ath11k_qmi,
					      event_work);
	काष्ठा ath11k_qmi_driver_event *event;
	काष्ठा ath11k_base *ab = qmi->ab;
	पूर्णांक ret;

	spin_lock(&qmi->event_lock);
	जबतक (!list_empty(&qmi->event_list)) अणु
		event = list_first_entry(&qmi->event_list,
					 काष्ठा ath11k_qmi_driver_event, list);
		list_del(&event->list);
		spin_unlock(&qmi->event_lock);

		अगर (test_bit(ATH11K_FLAG_UNREGISTERING, &ab->dev_flags))
			वापस;

		चयन (event->type) अणु
		हाल ATH11K_QMI_EVENT_SERVER_ARRIVE:
			ret = ath11k_qmi_event_server_arrive(qmi);
			अगर (ret < 0)
				set_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags);
			अवरोध;
		हाल ATH11K_QMI_EVENT_SERVER_EXIT:
			set_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags);
			set_bit(ATH11K_FLAG_RECOVERY, &ab->dev_flags);
			अवरोध;
		हाल ATH11K_QMI_EVENT_REQUEST_MEM:
			ret = ath11k_qmi_event_mem_request(qmi);
			अगर (ret < 0)
				set_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags);
			अवरोध;
		हाल ATH11K_QMI_EVENT_FW_MEM_READY:
			ret = ath11k_qmi_event_load_bdf(qmi);
			अगर (ret < 0)
				set_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags);
			अवरोध;
		हाल ATH11K_QMI_EVENT_FW_READY:
			clear_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags);
			अगर (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags)) अणु
				ath11k_hal_dump_srng_stats(ab);
				queue_work(ab->workqueue, &ab->restart_work);
				अवरोध;
			पूर्ण

			अगर (ath11k_cold_boot_cal && ab->qmi.cal_करोne == 0 &&
			    ab->hw_params.cold_boot_calib) अणु
				ath11k_qmi_process_coldboot_calibration(ab);
			पूर्ण अन्यथा अणु
				clear_bit(ATH11K_FLAG_CRASH_FLUSH,
					  &ab->dev_flags);
				clear_bit(ATH11K_FLAG_RECOVERY, &ab->dev_flags);
				ath11k_core_qmi_firmware_पढ़ोy(ab);
				set_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags);
			पूर्ण

			अवरोध;
		हाल ATH11K_QMI_EVENT_COLD_BOOT_CAL_DONE:
			अवरोध;
		शेष:
			ath11k_warn(ab, "invalid qmi event type: %d", event->type);
			अवरोध;
		पूर्ण
		kमुक्त(event);
		spin_lock(&qmi->event_lock);
	पूर्ण
	spin_unlock(&qmi->event_lock);
पूर्ण

पूर्णांक ath11k_qmi_init_service(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	स_रखो(&ab->qmi.target, 0, माप(काष्ठा target_info));
	स_रखो(&ab->qmi.target_mem, 0, माप(काष्ठा target_mem_chunk));
	ab->qmi.ab = ab;

	ab->qmi.target_mem_mode = ATH11K_QMI_TARGET_MEM_MODE_DEFAULT;
	ret = qmi_handle_init(&ab->qmi.handle, ATH11K_QMI_RESP_LEN_MAX,
			      &ath11k_qmi_ops, ath11k_qmi_msg_handlers);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to initialize qmi handle: %d\n", ret);
		वापस ret;
	पूर्ण

	ab->qmi.event_wq = alloc_workqueue("ath11k_qmi_driver_event",
					   WQ_UNBOUND, 1);
	अगर (!ab->qmi.event_wq) अणु
		ath11k_err(ab, "failed to allocate workqueue\n");
		वापस -EFAULT;
	पूर्ण

	INIT_LIST_HEAD(&ab->qmi.event_list);
	spin_lock_init(&ab->qmi.event_lock);
	INIT_WORK(&ab->qmi.event_work, ath11k_qmi_driver_event_work);

	ret = qmi_add_lookup(&ab->qmi.handle, ATH11K_QMI_WLFW_SERVICE_ID_V01,
			     ATH11K_QMI_WLFW_SERVICE_VERS_V01,
			     ab->qmi.service_ins_id);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to add qmi lookup: %d\n", ret);
		destroy_workqueue(ab->qmi.event_wq);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम ath11k_qmi_deinit_service(काष्ठा ath11k_base *ab)
अणु
	qmi_handle_release(&ab->qmi.handle);
	cancel_work_sync(&ab->qmi.event_work);
	destroy_workqueue(ab->qmi.event_wq);
	ath11k_qmi_m3_मुक्त(ab);
	ath11k_qmi_मुक्त_target_mem_chunk(ab);
पूर्ण
EXPORT_SYMBOL(ath11k_qmi_deinit_service);

