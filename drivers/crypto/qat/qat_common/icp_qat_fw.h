<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित _ICP_QAT_FW_H_
#घोषणा _ICP_QAT_FW_H_
#समावेश <linux/types.h>
#समावेश "icp_qat_hw.h"

#घोषणा QAT_FIELD_SET(flags, val, bitpos, mask) \
अणु (flags) = (((flags) & (~((mask) << (bitpos)))) | \
		(((val) & (mask)) << (bitpos))) ; पूर्ण

#घोषणा QAT_FIELD_GET(flags, bitpos, mask) \
	(((flags) >> (bitpos)) & (mask))

#घोषणा ICP_QAT_FW_REQ_DEFAULT_SZ 128
#घोषणा ICP_QAT_FW_RESP_DEFAULT_SZ 32
#घोषणा ICP_QAT_FW_COMN_ONE_BYTE_SHIFT 8
#घोषणा ICP_QAT_FW_COMN_SINGLE_BYTE_MASK 0xFF
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_1 1
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_2 2
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_3 3
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_4 4
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_5 5
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_6 6
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_7 7
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_10 10
#घोषणा ICP_QAT_FW_NUM_LONGWORDS_13 13
#घोषणा ICP_QAT_FW_शून्य_REQ_SERV_ID 1

क्रमागत icp_qat_fw_comn_resp_serv_id अणु
	ICP_QAT_FW_COMN_RESP_SERV_शून्य,
	ICP_QAT_FW_COMN_RESP_SERV_CPM_FW,
	ICP_QAT_FW_COMN_RESP_SERV_DELIMITER
पूर्ण;

क्रमागत icp_qat_fw_comn_request_id अणु
	ICP_QAT_FW_COMN_REQ_शून्य = 0,
	ICP_QAT_FW_COMN_REQ_CPM_FW_PKE = 3,
	ICP_QAT_FW_COMN_REQ_CPM_FW_LA = 4,
	ICP_QAT_FW_COMN_REQ_CPM_FW_DMA = 7,
	ICP_QAT_FW_COMN_REQ_CPM_FW_COMP = 9,
	ICP_QAT_FW_COMN_REQ_DELIMITER
पूर्ण;

काष्ठा icp_qat_fw_comn_req_hdr_cd_pars अणु
	जोड़ अणु
		काष्ठा अणु
			__u64 content_desc_addr;
			__u16 content_desc_resrvd1;
			__u8 content_desc_params_sz;
			__u8 content_desc_hdr_resrvd2;
			__u32 content_desc_resrvd3;
		पूर्ण s;
		काष्ठा अणु
			__u32 serv_specअगर_fields[4];
		पूर्ण s1;
	पूर्ण u;
पूर्ण;

काष्ठा icp_qat_fw_comn_req_mid अणु
	__u64 opaque_data;
	__u64 src_data_addr;
	__u64 dest_data_addr;
	__u32 src_length;
	__u32 dst_length;
पूर्ण;

काष्ठा icp_qat_fw_comn_req_cd_ctrl अणु
	__u32 content_desc_ctrl_lw[ICP_QAT_FW_NUM_LONGWORDS_5];
पूर्ण;

काष्ठा icp_qat_fw_comn_req_hdr अणु
	__u8 resrvd1;
	__u8 service_cmd_id;
	__u8 service_type;
	__u8 hdr_flags;
	__u16 serv_specअगर_flags;
	__u16 comn_req_flags;
पूर्ण;

काष्ठा icp_qat_fw_comn_req_rqpars अणु
	__u32 serv_specअगर_rqpars_lw[ICP_QAT_FW_NUM_LONGWORDS_13];
पूर्ण;

काष्ठा icp_qat_fw_comn_req अणु
	काष्ठा icp_qat_fw_comn_req_hdr comn_hdr;
	काष्ठा icp_qat_fw_comn_req_hdr_cd_pars cd_pars;
	काष्ठा icp_qat_fw_comn_req_mid comn_mid;
	काष्ठा icp_qat_fw_comn_req_rqpars serv_specअगर_rqpars;
	काष्ठा icp_qat_fw_comn_req_cd_ctrl cd_ctrl;
पूर्ण;

काष्ठा icp_qat_fw_comn_error अणु
	__u8 xlat_err_code;
	__u8 cmp_err_code;
पूर्ण;

काष्ठा icp_qat_fw_comn_resp_hdr अणु
	__u8 resrvd1;
	__u8 service_id;
	__u8 response_type;
	__u8 hdr_flags;
	काष्ठा icp_qat_fw_comn_error comn_error;
	__u8 comn_status;
	__u8 cmd_id;
पूर्ण;

काष्ठा icp_qat_fw_comn_resp अणु
	काष्ठा icp_qat_fw_comn_resp_hdr comn_hdr;
	__u64 opaque_data;
	__u32 resrvd[ICP_QAT_FW_NUM_LONGWORDS_4];
पूर्ण;

#घोषणा ICP_QAT_FW_COMN_REQ_FLAG_SET 1
#घोषणा ICP_QAT_FW_COMN_REQ_FLAG_CLR 0
#घोषणा ICP_QAT_FW_COMN_VALID_FLAG_BITPOS 7
#घोषणा ICP_QAT_FW_COMN_VALID_FLAG_MASK 0x1
#घोषणा ICP_QAT_FW_COMN_HDR_RESRVD_FLD_MASK 0x7F

#घोषणा ICP_QAT_FW_COMN_OV_SRV_TYPE_GET(icp_qat_fw_comn_req_hdr_t) \
	icp_qat_fw_comn_req_hdr_t.service_type

#घोषणा ICP_QAT_FW_COMN_OV_SRV_TYPE_SET(icp_qat_fw_comn_req_hdr_t, val) \
	icp_qat_fw_comn_req_hdr_t.service_type = val

#घोषणा ICP_QAT_FW_COMN_OV_SRV_CMD_ID_GET(icp_qat_fw_comn_req_hdr_t) \
	icp_qat_fw_comn_req_hdr_t.service_cmd_id

#घोषणा ICP_QAT_FW_COMN_OV_SRV_CMD_ID_SET(icp_qat_fw_comn_req_hdr_t, val) \
	icp_qat_fw_comn_req_hdr_t.service_cmd_id = val

#घोषणा ICP_QAT_FW_COMN_HDR_VALID_FLAG_GET(hdr_t) \
	ICP_QAT_FW_COMN_VALID_FLAG_GET(hdr_t.hdr_flags)

#घोषणा ICP_QAT_FW_COMN_HDR_VALID_FLAG_SET(hdr_t, val) \
	ICP_QAT_FW_COMN_VALID_FLAG_SET(hdr_t, val)

#घोषणा ICP_QAT_FW_COMN_VALID_FLAG_GET(hdr_flags) \
	QAT_FIELD_GET(hdr_flags, \
	ICP_QAT_FW_COMN_VALID_FLAG_BITPOS, \
	ICP_QAT_FW_COMN_VALID_FLAG_MASK)

#घोषणा ICP_QAT_FW_COMN_HDR_RESRVD_FLD_GET(hdr_flags) \
	(hdr_flags & ICP_QAT_FW_COMN_HDR_RESRVD_FLD_MASK)

#घोषणा ICP_QAT_FW_COMN_VALID_FLAG_SET(hdr_t, val) \
	QAT_FIELD_SET((hdr_t.hdr_flags), (val), \
	ICP_QAT_FW_COMN_VALID_FLAG_BITPOS, \
	ICP_QAT_FW_COMN_VALID_FLAG_MASK)

#घोषणा ICP_QAT_FW_COMN_HDR_FLAGS_BUILD(valid) \
	(((valid) & ICP_QAT_FW_COMN_VALID_FLAG_MASK) << \
	 ICP_QAT_FW_COMN_VALID_FLAG_BITPOS)

#घोषणा QAT_COMN_PTR_TYPE_BITPOS 0
#घोषणा QAT_COMN_PTR_TYPE_MASK 0x1
#घोषणा QAT_COMN_CD_FLD_TYPE_BITPOS 1
#घोषणा QAT_COMN_CD_FLD_TYPE_MASK 0x1
#घोषणा QAT_COMN_PTR_TYPE_FLAT 0x0
#घोषणा QAT_COMN_PTR_TYPE_SGL 0x1
#घोषणा QAT_COMN_CD_FLD_TYPE_64BIT_ADR 0x0
#घोषणा QAT_COMN_CD_FLD_TYPE_16BYTE_DATA 0x1

#घोषणा ICP_QAT_FW_COMN_FLAGS_BUILD(cdt, ptr) \
	((((cdt) & QAT_COMN_CD_FLD_TYPE_MASK) << QAT_COMN_CD_FLD_TYPE_BITPOS) \
	 | (((ptr) & QAT_COMN_PTR_TYPE_MASK) << QAT_COMN_PTR_TYPE_BITPOS))

#घोषणा ICP_QAT_FW_COMN_PTR_TYPE_GET(flags) \
	QAT_FIELD_GET(flags, QAT_COMN_PTR_TYPE_BITPOS, QAT_COMN_PTR_TYPE_MASK)

#घोषणा ICP_QAT_FW_COMN_CD_FLD_TYPE_GET(flags) \
	QAT_FIELD_GET(flags, QAT_COMN_CD_FLD_TYPE_BITPOS, \
			QAT_COMN_CD_FLD_TYPE_MASK)

#घोषणा ICP_QAT_FW_COMN_PTR_TYPE_SET(flags, val) \
	QAT_FIELD_SET(flags, val, QAT_COMN_PTR_TYPE_BITPOS, \
			QAT_COMN_PTR_TYPE_MASK)

#घोषणा ICP_QAT_FW_COMN_CD_FLD_TYPE_SET(flags, val) \
	QAT_FIELD_SET(flags, val, QAT_COMN_CD_FLD_TYPE_BITPOS, \
			QAT_COMN_CD_FLD_TYPE_MASK)

#घोषणा ICP_QAT_FW_COMN_NEXT_ID_BITPOS 4
#घोषणा ICP_QAT_FW_COMN_NEXT_ID_MASK 0xF0
#घोषणा ICP_QAT_FW_COMN_CURR_ID_BITPOS 0
#घोषणा ICP_QAT_FW_COMN_CURR_ID_MASK 0x0F

#घोषणा ICP_QAT_FW_COMN_NEXT_ID_GET(cd_ctrl_hdr_t) \
	((((cd_ctrl_hdr_t)->next_curr_id) & ICP_QAT_FW_COMN_NEXT_ID_MASK) \
	>> (ICP_QAT_FW_COMN_NEXT_ID_BITPOS))

#घोषणा ICP_QAT_FW_COMN_NEXT_ID_SET(cd_ctrl_hdr_t, val) \
	अणु ((cd_ctrl_hdr_t)->next_curr_id) = ((((cd_ctrl_hdr_t)->next_curr_id) \
	& ICP_QAT_FW_COMN_CURR_ID_MASK) | \
	((val << ICP_QAT_FW_COMN_NEXT_ID_BITPOS) \
	 & ICP_QAT_FW_COMN_NEXT_ID_MASK)); पूर्ण

#घोषणा ICP_QAT_FW_COMN_CURR_ID_GET(cd_ctrl_hdr_t) \
	(((cd_ctrl_hdr_t)->next_curr_id) & ICP_QAT_FW_COMN_CURR_ID_MASK)

#घोषणा ICP_QAT_FW_COMN_CURR_ID_SET(cd_ctrl_hdr_t, val) \
	अणु ((cd_ctrl_hdr_t)->next_curr_id) = ((((cd_ctrl_hdr_t)->next_curr_id) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK) | \
	((val) & ICP_QAT_FW_COMN_CURR_ID_MASK)); पूर्ण

#घोषणा QAT_COMN_RESP_CRYPTO_STATUS_BITPOS 7
#घोषणा QAT_COMN_RESP_CRYPTO_STATUS_MASK 0x1
#घोषणा QAT_COMN_RESP_PKE_STATUS_BITPOS 6
#घोषणा QAT_COMN_RESP_PKE_STATUS_MASK 0x1
#घोषणा QAT_COMN_RESP_CMP_STATUS_BITPOS 5
#घोषणा QAT_COMN_RESP_CMP_STATUS_MASK 0x1
#घोषणा QAT_COMN_RESP_XLAT_STATUS_BITPOS 4
#घोषणा QAT_COMN_RESP_XLAT_STATUS_MASK 0x1
#घोषणा QAT_COMN_RESP_CMP_END_OF_LAST_BLK_BITPOS 3
#घोषणा QAT_COMN_RESP_CMP_END_OF_LAST_BLK_MASK 0x1

#घोषणा ICP_QAT_FW_COMN_RESP_STATUS_BUILD(crypto, comp, xlat, eolb) \
	((((crypto) & QAT_COMN_RESP_CRYPTO_STATUS_MASK) << \
	QAT_COMN_RESP_CRYPTO_STATUS_BITPOS) | \
	(((comp) & QAT_COMN_RESP_CMP_STATUS_MASK) << \
	QAT_COMN_RESP_CMP_STATUS_BITPOS) | \
	(((xlat) & QAT_COMN_RESP_XLAT_STATUS_MASK) << \
	QAT_COMN_RESP_XLAT_STATUS_BITPOS) | \
	(((eolb) & QAT_COMN_RESP_CMP_END_OF_LAST_BLK_MASK) << \
	QAT_COMN_RESP_CMP_END_OF_LAST_BLK_BITPOS))

#घोषणा ICP_QAT_FW_COMN_RESP_CRYPTO_STAT_GET(status) \
	QAT_FIELD_GET(status, QAT_COMN_RESP_CRYPTO_STATUS_BITPOS, \
	QAT_COMN_RESP_CRYPTO_STATUS_MASK)

#घोषणा ICP_QAT_FW_COMN_RESP_CMP_STAT_GET(status) \
	QAT_FIELD_GET(status, QAT_COMN_RESP_CMP_STATUS_BITPOS, \
	QAT_COMN_RESP_CMP_STATUS_MASK)

#घोषणा ICP_QAT_FW_COMN_RESP_XLAT_STAT_GET(status) \
	QAT_FIELD_GET(status, QAT_COMN_RESP_XLAT_STATUS_BITPOS, \
	QAT_COMN_RESP_XLAT_STATUS_MASK)

#घोषणा ICP_QAT_FW_COMN_RESP_CMP_END_OF_LAST_BLK_FLAG_GET(status) \
	QAT_FIELD_GET(status, QAT_COMN_RESP_CMP_END_OF_LAST_BLK_BITPOS, \
	QAT_COMN_RESP_CMP_END_OF_LAST_BLK_MASK)

#घोषणा ICP_QAT_FW_COMN_STATUS_FLAG_OK 0
#घोषणा ICP_QAT_FW_COMN_STATUS_FLAG_ERROR 1
#घोषणा ICP_QAT_FW_COMN_STATUS_CMP_END_OF_LAST_BLK_FLAG_CLR 0
#घोषणा ICP_QAT_FW_COMN_STATUS_CMP_END_OF_LAST_BLK_FLAG_SET 1
#घोषणा ERR_CODE_NO_ERROR 0
#घोषणा ERR_CODE_INVALID_BLOCK_TYPE -1
#घोषणा ERR_CODE_NO_MATCH_ONES_COMP -2
#घोषणा ERR_CODE_TOO_MANY_LEN_OR_DIS -3
#घोषणा ERR_CODE_INCOMPLETE_LEN -4
#घोषणा ERR_CODE_RPT_LEN_NO_FIRST_LEN -5
#घोषणा ERR_CODE_RPT_GT_SPEC_LEN -6
#घोषणा ERR_CODE_INV_LIT_LEN_CODE_LEN -7
#घोषणा ERR_CODE_INV_DIS_CODE_LEN -8
#घोषणा ERR_CODE_INV_LIT_LEN_DIS_IN_BLK -9
#घोषणा ERR_CODE_DIS_TOO_FAR_BACK -10
#घोषणा ERR_CODE_OVERFLOW_ERROR -11
#घोषणा ERR_CODE_SOFT_ERROR -12
#घोषणा ERR_CODE_FATAL_ERROR -13
#घोषणा ERR_CODE_SSM_ERROR -14
#घोषणा ERR_CODE_ENDPOINT_ERROR -15

क्रमागत icp_qat_fw_slice अणु
	ICP_QAT_FW_SLICE_शून्य = 0,
	ICP_QAT_FW_SLICE_CIPHER = 1,
	ICP_QAT_FW_SLICE_AUTH = 2,
	ICP_QAT_FW_SLICE_DRAM_RD = 3,
	ICP_QAT_FW_SLICE_DRAM_WR = 4,
	ICP_QAT_FW_SLICE_COMP = 5,
	ICP_QAT_FW_SLICE_XLAT = 6,
	ICP_QAT_FW_SLICE_DELIMITER
पूर्ण;
#पूर्ण_अगर
