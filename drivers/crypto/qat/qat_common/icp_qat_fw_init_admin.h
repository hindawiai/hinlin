<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित _ICP_QAT_FW_INIT_ADMIN_H_
#घोषणा _ICP_QAT_FW_INIT_ADMIN_H_

#समावेश "icp_qat_fw.h"

क्रमागत icp_qat_fw_init_admin_cmd_id अणु
	ICP_QAT_FW_INIT_AE = 0,
	ICP_QAT_FW_TRNG_ENABLE = 1,
	ICP_QAT_FW_TRNG_DISABLE = 2,
	ICP_QAT_FW_CONSTANTS_CFG = 3,
	ICP_QAT_FW_STATUS_GET = 4,
	ICP_QAT_FW_COUNTERS_GET = 5,
	ICP_QAT_FW_LOOPBACK = 6,
	ICP_QAT_FW_HEARTBEAT_SYNC = 7,
	ICP_QAT_FW_HEARTBEAT_GET = 8
पूर्ण;

क्रमागत icp_qat_fw_init_admin_resp_status अणु
	ICP_QAT_FW_INIT_RESP_STATUS_SUCCESS = 0,
	ICP_QAT_FW_INIT_RESP_STATUS_FAIL
पूर्ण;

काष्ठा icp_qat_fw_init_admin_req अणु
	__u16 init_cfg_sz;
	__u8 resrvd1;
	__u8 cmd_id;
	__u32 resrvd2;
	__u64 opaque_data;
	__u64 init_cfg_ptr;

	जोड़ अणु
		काष्ठा अणु
			__u16 ibuf_size_in_kb;
			__u16 resrvd3;
		पूर्ण;
		__u32 idle_filter;
	पूर्ण;

	__u32 resrvd4;
पूर्ण __packed;

काष्ठा icp_qat_fw_init_admin_resp अणु
	__u8 flags;
	__u8 resrvd1;
	__u8 status;
	__u8 cmd_id;
	जोड़ अणु
		__u32 resrvd2;
		काष्ठा अणु
			__u16 version_minor_num;
			__u16 version_major_num;
		पूर्ण;
	पूर्ण;
	__u64 opaque_data;
	जोड़ अणु
		__u32 resrvd3[ICP_QAT_FW_NUM_LONGWORDS_4];
		काष्ठा अणु
			__u32 version_patch_num;
			__u8 context_id;
			__u8 ae_id;
			__u16 resrvd4;
			__u64 resrvd5;
		पूर्ण;
		काष्ठा अणु
			__u64 req_rec_count;
			__u64 resp_sent_count;
		पूर्ण;
		काष्ठा अणु
			__u16 compression_algos;
			__u16 checksum_algos;
			__u32 deflate_capabilities;
			__u32 resrvd6;
			__u32 lzs_capabilities;
		पूर्ण;
		काष्ठा अणु
			__u32 cipher_algos;
			__u32 hash_algos;
			__u16 keygen_algos;
			__u16 other;
			__u16 खुला_key_algos;
			__u16 prime_algos;
		पूर्ण;
		काष्ठा अणु
			__u64 बारtamp;
			__u64 resrvd7;
		पूर्ण;
		काष्ठा अणु
			__u32 successful_count;
			__u32 unsuccessful_count;
			__u64 resrvd8;
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_OK 0
#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_BLOCKED 1
#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_FLAG_BITPOS 0
#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_FLAG_MASK 0x1
#घोषणा ICP_QAT_FW_COMN_STATUS_RESRVD_FLD_MASK 0xFE
#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_HDR_FLAG_GET(hdr_t) \
	ICP_QAT_FW_COMN_HEARTBEAT_FLAG_GET(hdr_t.flags)

#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_HDR_FLAG_SET(hdr_t, val) \
	ICP_QAT_FW_COMN_HEARTBEAT_FLAG_SET(hdr_t, val)

#घोषणा ICP_QAT_FW_COMN_HEARTBEAT_FLAG_GET(flags) \
	QAT_FIELD_GET(flags, \
		 ICP_QAT_FW_COMN_HEARTBEAT_FLAG_BITPOS, \
		 ICP_QAT_FW_COMN_HEARTBEAT_FLAG_MASK)
#पूर्ण_अगर
