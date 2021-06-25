<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#समावेश <linux/मानकघोष.स>
#समावेश <linux/soc/qcom/qmi.h>

#समावेश "ipa_qmi_msg.h"

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_indication_रेजिस्टर_req */
काष्ठा qmi_elem_info ipa_indication_रेजिस्टर_req_ei[] = अणु
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     master_driver_init_complete_valid),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   master_driver_init_complete_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     master_driver_init_complete),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   master_driver_init_complete),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     data_usage_quota_reached_valid),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   data_usage_quota_reached_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     data_usage_quota_reached),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   data_usage_quota_reached),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     ipa_mhi_पढ़ोy_ind_valid),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   ipa_mhi_पढ़ोy_ind_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     ipa_mhi_पढ़ोy_ind),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   ipa_mhi_पढ़ोy_ind),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     endpoपूर्णांक_desc_ind_valid),
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   endpoपूर्णांक_desc_ind_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     endpoपूर्णांक_desc_ind),
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   endpoपूर्णांक_desc_ind),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     bw_change_ind_valid),
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   bw_change_ind_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_req,
				     bw_change_ind),
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_req,
					   bw_change_ind),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_indication_रेजिस्टर_rsp */
काष्ठा qmi_elem_info ipa_indication_रेजिस्टर_rsp_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_indication_रेजिस्टर_rsp,
				     rsp),
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ipa_indication_रेजिस्टर_rsp,
					   rsp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_driver_init_complete_req */
काष्ठा qmi_elem_info ipa_driver_init_complete_req_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_driver_init_complete_req,
				     status),
		.tlv_type	= 0x01,
		.offset		= दुरत्व(काष्ठा ipa_driver_init_complete_req,
					   status),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_driver_init_complete_rsp */
काष्ठा qmi_elem_info ipa_driver_init_complete_rsp_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_driver_init_complete_rsp,
				     rsp),
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ipa_driver_init_complete_rsp,
					   rsp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_init_complete_ind */
काष्ठा qmi_elem_info ipa_init_complete_ind_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_complete_ind,
				     status),
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ipa_init_complete_ind,
					   status),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_mem_bounds */
काष्ठा qmi_elem_info ipa_mem_bounds_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_bounds, start),
		.offset		= दुरत्व(काष्ठा ipa_mem_bounds, start),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_bounds, end),
		.offset		= दुरत्व(काष्ठा ipa_mem_bounds, end),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_mem_array */
काष्ठा qmi_elem_info ipa_mem_array_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_array, start),
		.offset		= दुरत्व(काष्ठा ipa_mem_array, start),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_array, count),
		.offset		= दुरत्व(काष्ठा ipa_mem_array, count),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_mem_range */
काष्ठा qmi_elem_info ipa_mem_range_ei[] = अणु
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_range, start),
		.offset		= दुरत्व(काष्ठा ipa_mem_range, start),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_mem_range, size),
		.offset		= दुरत्व(काष्ठा ipa_mem_range, size),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_init_modem_driver_req */
काष्ठा qmi_elem_info ipa_init_modem_driver_req_ei[] = अणु
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     platक्रमm_type_valid),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   platक्रमm_type_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     platक्रमm_type),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   platक्रमm_type),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hdr_tbl_info_valid),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hdr_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hdr_tbl_info),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hdr_tbl_info),
		.ei_array	= ipa_mem_bounds_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_route_tbl_info_valid),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_route_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_route_tbl_info),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_route_tbl_info),
		.ei_array	= ipa_mem_array_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_route_tbl_info_valid),
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_route_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_route_tbl_info),
		.tlv_type	= 0x13,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_route_tbl_info),
		.ei_array	= ipa_mem_array_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_filter_tbl_start_valid),
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_filter_tbl_start_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_filter_tbl_start),
		.tlv_type	= 0x14,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_filter_tbl_start),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_filter_tbl_start_valid),
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_filter_tbl_start_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_filter_tbl_start),
		.tlv_type	= 0x15,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_filter_tbl_start),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     modem_mem_info_valid),
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   modem_mem_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     modem_mem_info),
		.tlv_type	= 0x16,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   modem_mem_info),
		.ei_array	= ipa_mem_range_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     ctrl_comm_dest_end_pt_valid),
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   ctrl_comm_dest_end_pt_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     ctrl_comm_dest_end_pt),
		.tlv_type	= 0x17,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   ctrl_comm_dest_end_pt),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     skip_uc_load_valid),
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   skip_uc_load_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     skip_uc_load),
		.tlv_type	= 0x18,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   skip_uc_load),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hdr_proc_ctx_tbl_info_valid),
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hdr_proc_ctx_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hdr_proc_ctx_tbl_info),
		.tlv_type	= 0x19,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hdr_proc_ctx_tbl_info),
		.ei_array	= ipa_mem_bounds_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     zip_tbl_info_valid),
		.tlv_type	= 0x1a,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   zip_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     zip_tbl_info),
		.tlv_type	= 0x1a,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   zip_tbl_info),
		.ei_array	= ipa_mem_bounds_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_hash_route_tbl_info_valid),
		.tlv_type	= 0x1b,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_hash_route_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_hash_route_tbl_info),
		.tlv_type	= 0x1b,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_hash_route_tbl_info),
		.ei_array	= ipa_mem_array_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_hash_route_tbl_info_valid),
		.tlv_type	= 0x1c,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_hash_route_tbl_info_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_hash_route_tbl_info),
		.tlv_type	= 0x1c,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_hash_route_tbl_info),
		.ei_array	= ipa_mem_array_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_hash_filter_tbl_start_valid),
		.tlv_type	= 0x1d,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_hash_filter_tbl_start_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v4_hash_filter_tbl_start),
		.tlv_type	= 0x1d,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v4_hash_filter_tbl_start),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_hash_filter_tbl_start_valid),
		.tlv_type	= 0x1e,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_hash_filter_tbl_start_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     v6_hash_filter_tbl_start),
		.tlv_type	= 0x1e,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   v6_hash_filter_tbl_start),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_quota_base_addr_valid),
		.tlv_type	= 0x1f,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_quota_base_addr_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_quota_base_addr),
		.tlv_type	= 0x1f,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_quota_base_addr),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_quota_size_valid),
		.tlv_type	= 0x20,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_quota_size_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_quota_size),
		.tlv_type	= 0x20,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_quota_size),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_drop_base_addr_valid),
		.tlv_type	= 0x21,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_drop_base_addr_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_drop_base_addr),
		.tlv_type	= 0x21,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_drop_base_addr),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_drop_size_valid),
		.tlv_type	= 0x22,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_drop_size_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_req,
				     hw_stats_drop_size),
		.tlv_type	= 0x22,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_req,
					   hw_stats_drop_size),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;

/* QMI message काष्ठाure definition क्रम काष्ठा ipa_init_modem_driver_rsp */
काष्ठा qmi_elem_info ipa_init_modem_driver_rsp_ei[] = अणु
	अणु
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     rsp),
		.tlv_type	= 0x02,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   rsp),
		.ei_array	= qmi_response_type_v01_ei,
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     ctrl_comm_dest_end_pt_valid),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   ctrl_comm_dest_end_pt_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     ctrl_comm_dest_end_pt),
		.tlv_type	= 0x10,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   ctrl_comm_dest_end_pt),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     शेष_end_pt_valid),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   शेष_end_pt_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     शेष_end_pt),
		.tlv_type	= 0x11,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   शेष_end_pt),
	पूर्ण,
	अणु
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     modem_driver_init_pending_valid),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   modem_driver_init_pending_valid),
	पूर्ण,
	अणु
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	=
			माप_field(काष्ठा ipa_init_modem_driver_rsp,
				     modem_driver_init_pending),
		.tlv_type	= 0x12,
		.offset		= दुरत्व(काष्ठा ipa_init_modem_driver_rsp,
					   modem_driver_init_pending),
	पूर्ण,
	अणु
		.data_type	= QMI_EOTI,
	पूर्ण,
पूर्ण;
