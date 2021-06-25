<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_QMI_MSG_H_
#घोषणा _IPA_QMI_MSG_H_

/* === Only "ipa_qmi" and "ipa_qmi_msg.c" should include this file === */

#समावेश <linux/types.h>
#समावेश <linux/soc/qcom/qmi.h>

/* Request/response/indication QMI message ids used क्रम IPA.  Receiving
 * end issues a response क्रम requests; indications require no response.
 */
#घोषणा IPA_QMI_INDICATION_REGISTER	0x20	/* modem -> AP request */
#घोषणा IPA_QMI_INIT_DRIVER		0x21	/* AP -> modem request */
#घोषणा IPA_QMI_INIT_COMPLETE		0x22	/* AP -> modem indication */
#घोषणा IPA_QMI_DRIVER_INIT_COMPLETE	0x35	/* modem -> AP request */

/* The maximum size required क्रम message types.  These sizes include
 * the message data, aदीर्घ with type (1 byte) and length (2 byte)
 * inक्रमmation क्रम each field.  The qmi_send_*() पूर्णांकerfaces require
 * the message size to be provided.
 */
#घोषणा IPA_QMI_INDICATION_REGISTER_REQ_SZ	20	/* -> server handle */
#घोषणा IPA_QMI_INDICATION_REGISTER_RSP_SZ	7	/* <- server handle */
#घोषणा IPA_QMI_INIT_DRIVER_REQ_SZ		162	/* client handle -> */
#घोषणा IPA_QMI_INIT_DRIVER_RSP_SZ		25	/* client handle <- */
#घोषणा IPA_QMI_INIT_COMPLETE_IND_SZ		7	/* <- server handle */
#घोषणा IPA_QMI_DRIVER_INIT_COMPLETE_REQ_SZ	4	/* -> server handle */
#घोषणा IPA_QMI_DRIVER_INIT_COMPLETE_RSP_SZ	7	/* <- server handle */

/* Maximum size of messages we expect the AP to receive (max of above) */
#घोषणा IPA_QMI_SERVER_MAX_RCV_SZ		8
#घोषणा IPA_QMI_CLIENT_MAX_RCV_SZ		25

/* Request message क्रम the IPA_QMI_INDICATION_REGISTER request */
काष्ठा ipa_indication_रेजिस्टर_req अणु
	u8 master_driver_init_complete_valid;
	u8 master_driver_init_complete;
	u8 data_usage_quota_reached_valid;
	u8 data_usage_quota_reached;
	u8 ipa_mhi_पढ़ोy_ind_valid;
	u8 ipa_mhi_पढ़ोy_ind;
	u8 endpoपूर्णांक_desc_ind_valid;
	u8 endpoपूर्णांक_desc_ind;
	u8 bw_change_ind_valid;
	u8 bw_change_ind;
पूर्ण;

/* The response to a IPA_QMI_INDICATION_REGISTER request consists only of
 * a standard QMI response.
 */
काष्ठा ipa_indication_रेजिस्टर_rsp अणु
	काष्ठा qmi_response_type_v01 rsp;
पूर्ण;

/* Request message क्रम the IPA_QMI_DRIVER_INIT_COMPLETE request */
काष्ठा ipa_driver_init_complete_req अणु
	u8 status;
पूर्ण;

/* The response to a IPA_QMI_DRIVER_INIT_COMPLETE request consists only
 * of a standard QMI response.
 */
काष्ठा ipa_driver_init_complete_rsp अणु
	काष्ठा qmi_response_type_v01 rsp;
पूर्ण;

/* The message क्रम the IPA_QMI_INIT_COMPLETE_IND indication consists
 * only of a standard QMI response.
 */
काष्ठा ipa_init_complete_ind अणु
	काष्ठा qmi_response_type_v01 status;
पूर्ण;

/* The AP tells the modem its platक्रमm type.  We assume Android. */
क्रमागत ipa_platक्रमm_type अणु
	IPA_QMI_PLATFORM_TYPE_INVALID		= 0x0,	/* Invalid */
	IPA_QMI_PLATFORM_TYPE_TN		= 0x1,	/* Data card */
	IPA_QMI_PLATFORM_TYPE_LE		= 0x2,	/* Data router */
	IPA_QMI_PLATFORM_TYPE_MSM_ANDROID	= 0x3,	/* Android MSM */
	IPA_QMI_PLATFORM_TYPE_MSM_WINDOWS	= 0x4,	/* Winकरोws MSM */
	IPA_QMI_PLATFORM_TYPE_MSM_QNX_V01	= 0x5,	/* QNX MSM */
पूर्ण;

/* This defines the start and end offset of a range of memory.  Both
 * fields are offsets relative to the start of IPA shared memory.
 * The end value is the last addressable byte *within* the range.
 */
काष्ठा ipa_mem_bounds अणु
	u32 start;
	u32 end;
पूर्ण;

/* This defines the location and size of an array.  The start value
 * is an offset relative to the start of IPA shared memory.  The
 * size of the array is implied by the number of entries (the entry
 * size is assumed to be known).
 */
काष्ठा ipa_mem_array अणु
	u32 start;
	u32 count;
पूर्ण;

/* This defines the location and size of a range of memory.  The
 * start is an offset relative to the start of IPA shared memory.
 * This dअगरfers from the ipa_mem_bounds काष्ठाure in that the size
 * (in bytes) of the memory region is specअगरied rather than the
 * offset of its last byte.
 */
काष्ठा ipa_mem_range अणु
	u32 start;
	u32 size;
पूर्ण;

/* The message क्रम the IPA_QMI_INIT_DRIVER request contains inक्रमmation
 * from the AP that affects modem initialization.
 */
काष्ठा ipa_init_modem_driver_req अणु
	u8			platक्रमm_type_valid;
	u32			platक्रमm_type;	/* क्रमागत ipa_platक्रमm_type */

	/* Modem header table inक्रमmation.  This defines the IPA shared
	 * memory in which the modem may insert header table entries.
	 */
	u8			hdr_tbl_info_valid;
	काष्ठा ipa_mem_bounds	hdr_tbl_info;

	/* Routing table inक्रमmation.  These define the location and size of
	 * non-hashable IPv4 and IPv6 filter tables.  The start values are
	 * offsets relative to the start of IPA shared memory.
	 */
	u8			v4_route_tbl_info_valid;
	काष्ठा ipa_mem_array	v4_route_tbl_info;
	u8			v6_route_tbl_info_valid;
	काष्ठा ipa_mem_array	v6_route_tbl_info;

	/* Filter table inक्रमmation.  These define the location of the
	 * non-hashable IPv4 and IPv6 filter tables.  The start values are
	 * offsets relative to the start of IPA shared memory.
	 */
	u8			v4_filter_tbl_start_valid;
	u32			v4_filter_tbl_start;
	u8			v6_filter_tbl_start_valid;
	u32			v6_filter_tbl_start;

	/* Modem memory inक्रमmation.  This defines the location and
	 * size of memory available क्रम the modem to use.
	 */
	u8			modem_mem_info_valid;
	काष्ठा ipa_mem_range	modem_mem_info;

	/* This defines the destination endpoपूर्णांक on the AP to which
	 * the modem driver can send control commands.  Must be less
	 * than ipa_endpoपूर्णांक_max().
	 */
	u8			ctrl_comm_dest_end_pt_valid;
	u32			ctrl_comm_dest_end_pt;

	/* This defines whether the modem should load the microcontroller
	 * or not.  It is unnecessary to reload it अगर the modem is being
	 * restarted.
	 *
	 * NOTE: this field is named "is_ssr_bootup" अन्यथाwhere.
	 */
	u8			skip_uc_load_valid;
	u8			skip_uc_load;

	/* Processing context memory inक्रमmation.  This defines the memory in
	 * which the modem may insert header processing context table entries.
	 */
	u8			hdr_proc_ctx_tbl_info_valid;
	काष्ठा ipa_mem_bounds	hdr_proc_ctx_tbl_info;

	/* Compression command memory inक्रमmation.  This defines the memory
	 * in which the modem may insert compression/decompression commands.
	 */
	u8			zip_tbl_info_valid;
	काष्ठा ipa_mem_bounds	zip_tbl_info;

	/* Routing table inक्रमmation.  These define the location and size
	 * of hashable IPv4 and IPv6 filter tables.  The start values are
	 * offsets relative to the start of IPA shared memory.
	 */
	u8			v4_hash_route_tbl_info_valid;
	काष्ठा ipa_mem_array	v4_hash_route_tbl_info;
	u8			v6_hash_route_tbl_info_valid;
	काष्ठा ipa_mem_array	v6_hash_route_tbl_info;

	/* Filter table inक्रमmation.  These define the location and size
	 * of hashable IPv4 and IPv6 filter tables.  The start values are
	 * offsets relative to the start of IPA shared memory.
	 */
	u8			v4_hash_filter_tbl_start_valid;
	u32			v4_hash_filter_tbl_start;
	u8			v6_hash_filter_tbl_start_valid;
	u32			v6_hash_filter_tbl_start;

	/* Statistics inक्रमmation.  These define the locations of the
	 * first and last statistics sub-regions.  (IPA v4.0 and above)
	 */
	u8			hw_stats_quota_base_addr_valid;
	u32			hw_stats_quota_base_addr;
	u8			hw_stats_quota_size_valid;
	u32			hw_stats_quota_size;
	u8			hw_stats_drop_base_addr_valid;
	u32			hw_stats_drop_base_addr;
	u8			hw_stats_drop_size_valid;
	u32			hw_stats_drop_size;
पूर्ण;

/* The response to a IPA_QMI_INIT_DRIVER request begins with a standard
 * QMI response, but contains other inक्रमmation as well.  Currently we
 * simply रुको क्रम the the INIT_DRIVER transaction to complete and
 * ignore any other data that might be वापसed.
 */
काष्ठा ipa_init_modem_driver_rsp अणु
	काष्ठा qmi_response_type_v01	rsp;

	/* This defines the destination endpoपूर्णांक on the modem to which
	 * the AP driver can send control commands.  Must be less than
	 * ipa_endpoपूर्णांक_max().
	 */
	u8				ctrl_comm_dest_end_pt_valid;
	u32				ctrl_comm_dest_end_pt;

	/* This defines the शेष endpoपूर्णांक.  The AP driver is not
	 * required to configure the hardware with this value.  Must
	 * be less than ipa_endpoपूर्णांक_max().
	 */
	u8				शेष_end_pt_valid;
	u32				शेष_end_pt;

	/* This defines whether a second handshake is required to complete
	 * initialization.
	 */
	u8				modem_driver_init_pending_valid;
	u8				modem_driver_init_pending;
पूर्ण;

/* Message काष्ठाure definitions defined in "ipa_qmi_msg.c" */
बाह्य काष्ठा qmi_elem_info ipa_indication_रेजिस्टर_req_ei[];
बाह्य काष्ठा qmi_elem_info ipa_indication_रेजिस्टर_rsp_ei[];
बाह्य काष्ठा qmi_elem_info ipa_driver_init_complete_req_ei[];
बाह्य काष्ठा qmi_elem_info ipa_driver_init_complete_rsp_ei[];
बाह्य काष्ठा qmi_elem_info ipa_init_complete_ind_ei[];
बाह्य काष्ठा qmi_elem_info ipa_mem_bounds_ei[];
बाह्य काष्ठा qmi_elem_info ipa_mem_array_ei[];
बाह्य काष्ठा qmi_elem_info ipa_mem_range_ei[];
बाह्य काष्ठा qmi_elem_info ipa_init_modem_driver_req_ei[];
बाह्य काष्ठा qmi_elem_info ipa_init_modem_driver_rsp_ei[];

#पूर्ण_अगर /* !_IPA_QMI_MSG_H_ */
