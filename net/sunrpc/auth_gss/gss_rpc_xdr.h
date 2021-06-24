<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * GSS Proxy upcall module
 *
 *  Copyright (C) 2012 Simo Sorce <simo@redhat.com>
 */

#अगर_अघोषित _LINUX_GSS_RPC_XDR_H
#घोषणा _LINUX_GSS_RPC_XDR_H

#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/xprtsock.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

#घोषणा LUCID_OPTION "exported_context_type"
#घोषणा LUCID_VALUE  "linux_lucid_v1"
#घोषणा CREDS_OPTION "exported_creds_type"
#घोषणा CREDS_VALUE  "linux_creds_v1"

प्रकार काष्ठा xdr_netobj gssx_buffer;
प्रकार काष्ठा xdr_netobj utf8string;
प्रकार काष्ठा xdr_netobj gssx_OID;

क्रमागत gssx_cred_usage अणु
	GSSX_C_INITIATE = 1,
	GSSX_C_ACCEPT = 2,
	GSSX_C_BOTH = 3,
पूर्ण;

काष्ठा gssx_option अणु
	gssx_buffer option;
	gssx_buffer value;
पूर्ण;

काष्ठा gssx_option_array अणु
	u32 count;
	काष्ठा gssx_option *data;
पूर्ण;

काष्ठा gssx_status अणु
	u64 major_status;
	gssx_OID mech;
	u64 minor_status;
	utf8string major_status_string;
	utf8string minor_status_string;
	gssx_buffer server_ctx;
	काष्ठा gssx_option_array options;
पूर्ण;

काष्ठा gssx_call_ctx अणु
	utf8string locale;
	gssx_buffer server_ctx;
	काष्ठा gssx_option_array options;
पूर्ण;

काष्ठा gssx_name_attr अणु
	gssx_buffer attr;
	gssx_buffer value;
	काष्ठा gssx_option_array extensions;
पूर्ण;

काष्ठा gssx_name_attr_array अणु
	u32 count;
	काष्ठा gssx_name_attr *data;
पूर्ण;

काष्ठा gssx_name अणु
	gssx_buffer display_name;
पूर्ण;
प्रकार काष्ठा gssx_name gssx_name;

काष्ठा gssx_cred_element अणु
	gssx_name MN;
	gssx_OID mech;
	u32 cred_usage;
	u64 initiator_समय_rec;
	u64 acceptor_समय_rec;
	काष्ठा gssx_option_array options;
पूर्ण;

काष्ठा gssx_cred_element_array अणु
	u32 count;
	काष्ठा gssx_cred_element *data;
पूर्ण;

काष्ठा gssx_cred अणु
	gssx_name desired_name;
	काष्ठा gssx_cred_element_array elements;
	gssx_buffer cred_handle_reference;
	u32 needs_release;
पूर्ण;

काष्ठा gssx_ctx अणु
	gssx_buffer exported_context_token;
	gssx_buffer state;
	u32 need_release;
	gssx_OID mech;
	gssx_name src_name;
	gssx_name targ_name;
	u64 lअगरeसमय;
	u64 ctx_flags;
	u32 locally_initiated;
	u32 खोलो;
	काष्ठा gssx_option_array options;
पूर्ण;

काष्ठा gssx_cb अणु
	u64 initiator_addrtype;
	gssx_buffer initiator_address;
	u64 acceptor_addrtype;
	gssx_buffer acceptor_address;
	gssx_buffer application_data;
पूर्ण;


/* This काष्ठाure is not defined in the protocol.
 * It is used in the kernel to carry around a big buffer
 * as a set of pages */
काष्ठा gssp_in_token अणु
	काष्ठा page **pages;	/* Array of contiguous pages */
	अचिन्हित पूर्णांक page_base;	/* Start of page data */
	अचिन्हित पूर्णांक page_len;	/* Length of page data */
पूर्ण;

काष्ठा gssx_arg_accept_sec_context अणु
	काष्ठा gssx_call_ctx call_ctx;
	काष्ठा gssx_ctx *context_handle;
	काष्ठा gssx_cred *cred_handle;
	काष्ठा gssp_in_token input_token;
	काष्ठा gssx_cb *input_cb;
	u32 ret_deleg_cred;
	काष्ठा gssx_option_array options;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक npages;
पूर्ण;

काष्ठा gssx_res_accept_sec_context अणु
	काष्ठा gssx_status status;
	काष्ठा gssx_ctx *context_handle;
	gssx_buffer *output_token;
	/* काष्ठा gssx_cred *delegated_cred_handle; not used in kernel */
	काष्ठा gssx_option_array options;
पूर्ण;



#घोषणा gssx_enc_indicate_mechs शून्य
#घोषणा gssx_dec_indicate_mechs शून्य
#घोषणा gssx_enc_get_call_context शून्य
#घोषणा gssx_dec_get_call_context शून्य
#घोषणा gssx_enc_import_and_canon_name शून्य
#घोषणा gssx_dec_import_and_canon_name शून्य
#घोषणा gssx_enc_export_cred शून्य
#घोषणा gssx_dec_export_cred शून्य
#घोषणा gssx_enc_import_cred शून्य
#घोषणा gssx_dec_import_cred शून्य
#घोषणा gssx_enc_acquire_cred शून्य
#घोषणा gssx_dec_acquire_cred शून्य
#घोषणा gssx_enc_store_cred शून्य
#घोषणा gssx_dec_store_cred शून्य
#घोषणा gssx_enc_init_sec_context शून्य
#घोषणा gssx_dec_init_sec_context शून्य
व्योम gssx_enc_accept_sec_context(काष्ठा rpc_rqst *req,
				 काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data);
पूर्णांक gssx_dec_accept_sec_context(काष्ठा rpc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *data);
#घोषणा gssx_enc_release_handle शून्य
#घोषणा gssx_dec_release_handle शून्य
#घोषणा gssx_enc_get_mic शून्य
#घोषणा gssx_dec_get_mic शून्य
#घोषणा gssx_enc_verअगरy शून्य
#घोषणा gssx_dec_verअगरy शून्य
#घोषणा gssx_enc_wrap शून्य
#घोषणा gssx_dec_wrap शून्य
#घोषणा gssx_enc_unwrap शून्य
#घोषणा gssx_dec_unwrap शून्य
#घोषणा gssx_enc_wrap_size_limit शून्य
#घोषणा gssx_dec_wrap_size_limit शून्य

/* non implemented calls are set to 0 size */
#घोषणा GSSX_ARG_indicate_mechs_sz 0
#घोषणा GSSX_RES_indicate_mechs_sz 0
#घोषणा GSSX_ARG_get_call_context_sz 0
#घोषणा GSSX_RES_get_call_context_sz 0
#घोषणा GSSX_ARG_import_and_canon_name_sz 0
#घोषणा GSSX_RES_import_and_canon_name_sz 0
#घोषणा GSSX_ARG_export_cred_sz 0
#घोषणा GSSX_RES_export_cred_sz 0
#घोषणा GSSX_ARG_import_cred_sz 0
#घोषणा GSSX_RES_import_cred_sz 0
#घोषणा GSSX_ARG_acquire_cred_sz 0
#घोषणा GSSX_RES_acquire_cred_sz 0
#घोषणा GSSX_ARG_store_cred_sz 0
#घोषणा GSSX_RES_store_cred_sz 0
#घोषणा GSSX_ARG_init_sec_context_sz 0
#घोषणा GSSX_RES_init_sec_context_sz 0

#घोषणा GSSX_शेष_in_call_ctx_sz (4 + 4 + 4 + \
			8 + माप(LUCID_OPTION) + माप(LUCID_VALUE) + \
			8 + माप(CREDS_OPTION) + माप(CREDS_VALUE))
#घोषणा GSSX_शेष_in_ctx_hndl_sz (4 + 4+8 + 4 + 4 + 6*4 + 6*4 + 8 + 8 + \
					4 + 4 + 4)
#घोषणा GSSX_शेष_in_cred_sz 4 /* we send in no cred_handle */
#घोषणा GSSX_शेष_in_token_sz 4 /* करोes *not* include token data */
#घोषणा GSSX_शेष_in_cb_sz 4 /* we करो not use channel bindings */
#घोषणा GSSX_ARG_accept_sec_context_sz (GSSX_शेष_in_call_ctx_sz + \
					GSSX_शेष_in_ctx_hndl_sz + \
					GSSX_शेष_in_cred_sz + \
					GSSX_शेष_in_token_sz + \
					GSSX_शेष_in_cb_sz + \
					4 /* no deleg creds boolean */ + \
					4) /* empty options */

/* somewhat arbitrary numbers but large enough (we ignore some of the data
 * sent करोwn, but it is part of the protocol so we need enough space to take
 * it in) */
#घोषणा GSSX_शेष_status_sz 8 + 24 + 8 + 256 + 256 + 16 + 4
#घोषणा GSSX_max_output_handle_sz 128
#घोषणा GSSX_max_oid_sz 16
#घोषणा GSSX_max_princ_sz 256
#घोषणा GSSX_शेष_ctx_sz (GSSX_max_output_handle_sz + \
			     16 + 4 + GSSX_max_oid_sz + \
			     2 * GSSX_max_princ_sz + \
			     8 + 8 + 4 + 4 + 4)
#घोषणा GSSX_max_output_token_sz 1024
/* grouplist not included; we allocate separate pages क्रम that: */
#घोषणा GSSX_max_creds_sz (4 + 4 + 4 /* + NGROUPS_MAX*4 */)
#घोषणा GSSX_RES_accept_sec_context_sz (GSSX_शेष_status_sz + \
					GSSX_शेष_ctx_sz + \
					GSSX_max_output_token_sz + \
					4 + GSSX_max_creds_sz)

#घोषणा GSSX_ARG_release_handle_sz 0
#घोषणा GSSX_RES_release_handle_sz 0
#घोषणा GSSX_ARG_get_mic_sz 0
#घोषणा GSSX_RES_get_mic_sz 0
#घोषणा GSSX_ARG_verअगरy_sz 0
#घोषणा GSSX_RES_verअगरy_sz 0
#घोषणा GSSX_ARG_wrap_sz 0
#घोषणा GSSX_RES_wrap_sz 0
#घोषणा GSSX_ARG_unwrap_sz 0
#घोषणा GSSX_RES_unwrap_sz 0
#घोषणा GSSX_ARG_wrap_size_limit_sz 0
#घोषणा GSSX_RES_wrap_size_limit_sz 0

#पूर्ण_अगर /* _LINUX_GSS_RPC_XDR_H */
