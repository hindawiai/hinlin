<शैली गुरु>
/*
 * Copyright 2018-2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित AMDGV_SRIOV_MSG__H_
#घोषणा AMDGV_SRIOV_MSG__H_

/* unit in kilobytes */
#घोषणा AMD_SRIOV_MSG_VBIOS_OFFSET              0
#घोषणा AMD_SRIOV_MSG_VBIOS_SIZE_KB             64
#घोषणा AMD_SRIOV_MSG_DATAEXCHANGE_OFFSET_KB    AMD_SRIOV_MSG_VBIOS_SIZE_KB
#घोषणा AMD_SRIOV_MSG_DATAEXCHANGE_SIZE_KB      4

/*
 * layout
 * 0           64KB        65KB        66KB
 * |   VBIOS   |   PF2VF   |   VF2PF   |   Bad Page   | ...
 * |   64KB    |   1KB     |   1KB     |
 */
#घोषणा AMD_SRIOV_MSG_SIZE_KB                   1
#घोषणा AMD_SRIOV_MSG_PF2VF_OFFSET_KB           AMD_SRIOV_MSG_DATAEXCHANGE_OFFSET_KB
#घोषणा AMD_SRIOV_MSG_VF2PF_OFFSET_KB           (AMD_SRIOV_MSG_PF2VF_OFFSET_KB + AMD_SRIOV_MSG_SIZE_KB)
#घोषणा AMD_SRIOV_MSG_BAD_PAGE_OFFSET_KB        (AMD_SRIOV_MSG_VF2PF_OFFSET_KB + AMD_SRIOV_MSG_SIZE_KB)

/*
 * PF2VF history log:
 * v1 defined in amdgim
 * v2 current
 *
 * VF2PF history log:
 * v1 defined in amdgim
 * v2 defined in amdgim
 * v3 current
 */
#घोषणा AMD_SRIOV_MSG_FW_VRAM_PF2VF_VER			2
#घोषणा AMD_SRIOV_MSG_FW_VRAM_VF2PF_VER			3

#घोषणा AMD_SRIOV_MSG_RESERVE_UCODE		24

क्रमागत amd_sriov_ucode_engine_id अणु
	AMD_SRIOV_UCODE_ID_VCE = 0,
	AMD_SRIOV_UCODE_ID_UVD,
	AMD_SRIOV_UCODE_ID_MC,
	AMD_SRIOV_UCODE_ID_ME,
	AMD_SRIOV_UCODE_ID_PFP,
	AMD_SRIOV_UCODE_ID_CE,
	AMD_SRIOV_UCODE_ID_RLC,
	AMD_SRIOV_UCODE_ID_RLC_SRLC,
	AMD_SRIOV_UCODE_ID_RLC_SRLG,
	AMD_SRIOV_UCODE_ID_RLC_SRLS,
	AMD_SRIOV_UCODE_ID_MEC,
	AMD_SRIOV_UCODE_ID_MEC2,
	AMD_SRIOV_UCODE_ID_SOS,
	AMD_SRIOV_UCODE_ID_ASD,
	AMD_SRIOV_UCODE_ID_TA_RAS,
	AMD_SRIOV_UCODE_ID_TA_XGMI,
	AMD_SRIOV_UCODE_ID_SMC,
	AMD_SRIOV_UCODE_ID_SDMA,
	AMD_SRIOV_UCODE_ID_SDMA2,
	AMD_SRIOV_UCODE_ID_VCN,
	AMD_SRIOV_UCODE_ID_DMCU,
	AMD_SRIOV_UCODE_ID__MAX
पूर्ण;

#आशय pack(push, 1) 	// PF2VF / VF2PF data areas are byte packed

जोड़ amd_sriov_msg_feature_flags अणु
	काष्ठा अणु
		uपूर्णांक32_t  error_log_collect  : 1;
		uपूर्णांक32_t  host_load_ucodes   : 1;
		uपूर्णांक32_t  host_flr_vramlost  : 1;
		uपूर्णांक32_t  mm_bw_management   : 1;
		uपूर्णांक32_t  pp_one_vf_mode     : 1;
		uपूर्णांक32_t  reg_indirect_acc   : 1;
		uपूर्णांक32_t  reserved           : 26;
	पूर्ण flags;
	uपूर्णांक32_t      all;
पूर्ण;

जोड़ amd_sriov_reg_access_flags अणु
	काष्ठा अणु
		uपूर्णांक32_t vf_reg_access_ih    : 1;
		uपूर्णांक32_t vf_reg_access_mmhub : 1;
		uपूर्णांक32_t vf_reg_access_gc    : 1;
		uपूर्णांक32_t reserved            : 29;
	पूर्ण flags;
	uपूर्णांक32_t all;
पूर्ण;

जोड़ amd_sriov_msg_os_info अणु
	काष्ठा अणु
		uपूर्णांक32_t  winकरोws            : 1;
		uपूर्णांक32_t  reserved           : 31;
	पूर्ण info;
	uपूर्णांक32_t      all;
पूर्ण;

काष्ठा amd_sriov_msg_pf2vf_info_header अणु
	/* the total काष्ठाure size in byte */
	uपूर्णांक32_t size;
	/* version of this काष्ठाure, written by the HOST */
	uपूर्णांक32_t version;
	/* reserved */
	uपूर्णांक32_t reserved[2];
पूर्ण;

काष्ठा amd_sriov_msg_pf2vf_info अणु
	/* header contains size and version */
	काष्ठा amd_sriov_msg_pf2vf_info_header header;
	/* use निजी key from mailbox 2 to create checksum */
	uपूर्णांक32_t checksum;
	/* The features flags of the HOST driver supports */
	जोड़ amd_sriov_msg_feature_flags feature_flags;
	/* (max_width * max_height * fps) / (16 * 16) */
	uपूर्णांक32_t hevc_enc_max_mb_per_second;
	/* (max_width * max_height) / (16 * 16) */
	uपूर्णांक32_t hevc_enc_max_mb_per_frame;
	/* (max_width * max_height * fps) / (16 * 16) */
	uपूर्णांक32_t avc_enc_max_mb_per_second;
	/* (max_width * max_height) / (16 * 16) */
	uपूर्णांक32_t avc_enc_max_mb_per_frame;
	/* MEC FW position in BYTE from the start of VF visible frame buffer */
	uपूर्णांक64_t mecfw_offset;
	/* MEC FW size in BYTE */
	uपूर्णांक32_t mecfw_size;
	/* UVD FW position in BYTE from the start of VF visible frame buffer */
	uपूर्णांक64_t uvdfw_offset;
	/* UVD FW size in BYTE */
	uपूर्णांक32_t uvdfw_size;
	/* VCE FW position in BYTE from the start of VF visible frame buffer */
	uपूर्णांक64_t vcefw_offset;
	/* VCE FW size in BYTE */
	uपूर्णांक32_t vcefw_size;
	/* Bad pages block position in BYTE */
	uपूर्णांक32_t bp_block_offset_low;
	uपूर्णांक32_t bp_block_offset_high;
	/* Bad pages block size in BYTE */
	uपूर्णांक32_t bp_block_size;
	/* frequency क्रम VF to update the VF2PF area in msec, 0 = manual */
	uपूर्णांक32_t vf2pf_update_पूर्णांकerval_ms;
	/* identअगरication in ROCm SMI */
	uपूर्णांक64_t uuid;
	uपूर्णांक32_t fcn_idx;
	/* flags which indicate the रेजिस्टर access method VF should use */
	जोड़ amd_sriov_reg_access_flags reg_access_flags;
	/* reserved */
	uपूर्णांक32_t reserved[256-27];
पूर्ण;

काष्ठा amd_sriov_msg_vf2pf_info_header अणु
	/* the total काष्ठाure size in byte */
	uपूर्णांक32_t size;
	/* version of this काष्ठाure, written by the guest */
	uपूर्णांक32_t version;
	/* reserved */
	uपूर्णांक32_t reserved[2];
पूर्ण;

काष्ठा amd_sriov_msg_vf2pf_info अणु
	/* header contains size and version */
	काष्ठा amd_sriov_msg_vf2pf_info_header header;
	uपूर्णांक32_t checksum;
	/* driver version */
	uपूर्णांक8_t  driver_version[64];
	/* driver certअगरication, 1=WHQL, 0=None */
	uपूर्णांक32_t driver_cert;
	/* guest OS type and version */
	जोड़ amd_sriov_msg_os_info os_info;
	/* guest fb inक्रमmation in the unit of MB */
	uपूर्णांक32_t fb_usage;
	/* guest gfx engine usage percentage */
	uपूर्णांक32_t gfx_usage;
	/* guest gfx engine health percentage */
	uपूर्णांक32_t gfx_health;
	/* guest compute engine usage percentage */
	uपूर्णांक32_t compute_usage;
	/* guest compute engine health percentage */
	uपूर्णांक32_t compute_health;
	/* guest avc engine usage percentage. 0xffff means N/A */
	uपूर्णांक32_t avc_enc_usage;
	/* guest avc engine health percentage. 0xffff means N/A */
	uपूर्णांक32_t avc_enc_health;
	/* guest hevc engine usage percentage. 0xffff means N/A */
	uपूर्णांक32_t hevc_enc_usage;
	/* guest hevc engine usage percentage. 0xffff means N/A */
	uपूर्णांक32_t hevc_enc_health;
	/* combined encode/decode usage */
	uपूर्णांक32_t encode_usage;
	uपूर्णांक32_t decode_usage;
	/* Version of PF2VF that VF understands */
	uपूर्णांक32_t pf2vf_version_required;
	/* additional FB usage */
	uपूर्णांक32_t fb_vis_usage;
	uपूर्णांक32_t fb_vis_size;
	uपूर्णांक32_t fb_size;
	/* guest ucode data, each one is 1.25 Dword */
	काष्ठा अणु
		uपूर्णांक8_t  id;
		uपूर्णांक32_t version;
	पूर्ण ucode_info[AMD_SRIOV_MSG_RESERVE_UCODE];

	/* reserved */
	uपूर्णांक32_t reserved[256-68];
पूर्ण;

/* mailbox message send from guest to host  */
क्रमागत amd_sriov_mailbox_request_message अणु
	MB_REQ_MSG_REQ_GPU_INIT_ACCESS = 1,
	MB_REQ_MSG_REL_GPU_INIT_ACCESS,
	MB_REQ_MSG_REQ_GPU_FINI_ACCESS,
	MB_REQ_MSG_REL_GPU_FINI_ACCESS,
	MB_REQ_MSG_REQ_GPU_RESET_ACCESS,
	MB_REQ_MSG_REQ_GPU_INIT_DATA,

	MB_REQ_MSG_LOG_VF_ERROR       = 200,
पूर्ण;

/* mailbox message send from host to guest  */
क्रमागत amd_sriov_mailbox_response_message अणु
	MB_RES_MSG_CLR_MSG_BUF = 0,
	MB_RES_MSG_READY_TO_ACCESS_GPU = 1,
	MB_RES_MSG_FLR_NOTIFICATION,
	MB_RES_MSG_FLR_NOTIFICATION_COMPLETION,
	MB_RES_MSG_SUCCESS,
	MB_RES_MSG_FAIL,
	MB_RES_MSG_QUERY_ALIVE,
	MB_RES_MSG_GPU_INIT_DATA_READY,

	MB_RES_MSG_TEXT_MESSAGE = 255
पूर्ण;

/* version data stored in MAILBOX_MSGBUF_RCV_DW1 क्रम future expansion */
क्रमागत amd_sriov_gpu_init_data_version अणु
	GPU_INIT_DATA_READY_V1 = 1,
पूर्ण;

#आशय pack(pop)	// Restore previous packing option

/* checksum function between host and guest */
अचिन्हित पूर्णांक amd_sriov_msg_checksum(व्योम *obj,
				अचिन्हित दीर्घ obj_size,
				अचिन्हित पूर्णांक key,
				अचिन्हित पूर्णांक checksum);

/* निश्चितion at compile समय */
#अगर_घोषित __linux__
#घोषणा stringअगरication(s) _stringअगरication(s)
#घोषणा _stringअगरication(s) #s

_Static_निश्चित(
	माप(काष्ठा amd_sriov_msg_vf2pf_info) == AMD_SRIOV_MSG_SIZE_KB << 10,
	"amd_sriov_msg_vf2pf_info must be " stringअगरication(AMD_SRIOV_MSG_SIZE_KB) " KB");

_Static_निश्चित(
	माप(काष्ठा amd_sriov_msg_pf2vf_info) == AMD_SRIOV_MSG_SIZE_KB << 10,
	"amd_sriov_msg_pf2vf_info must be " stringअगरication(AMD_SRIOV_MSG_SIZE_KB) " KB");

_Static_निश्चित(
	AMD_SRIOV_MSG_RESERVE_UCODE % 4 == 0,
	"AMD_SRIOV_MSG_RESERVE_UCODE must be multiple of 4");

_Static_निश्चित(
	AMD_SRIOV_MSG_RESERVE_UCODE > AMD_SRIOV_UCODE_ID__MAX,
	"AMD_SRIOV_MSG_RESERVE_UCODE must be bigger than AMD_SRIOV_UCODE_ID__MAX");

#अघोषित _stringअगरication
#अघोषित stringअगरication
#पूर्ण_अगर

#पूर्ण_अगर /* AMDGV_SRIOV_MSG__H_ */
