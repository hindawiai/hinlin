<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_UCODE_H__
#घोषणा __AMDGPU_UCODE_H__

#समावेश "amdgpu_socbb.h"

काष्ठा common_firmware_header अणु
	uपूर्णांक32_t size_bytes; /* size of the entire header+image(s) in bytes */
	uपूर्णांक32_t header_size_bytes; /* size of just the header in bytes */
	uपूर्णांक16_t header_version_major; /* header version */
	uपूर्णांक16_t header_version_minor; /* header version */
	uपूर्णांक16_t ip_version_major; /* IP version */
	uपूर्णांक16_t ip_version_minor; /* IP version */
	uपूर्णांक32_t ucode_version;
	uपूर्णांक32_t ucode_size_bytes; /* size of ucode in bytes */
	uपूर्णांक32_t ucode_array_offset_bytes; /* payload offset from the start of the header */
	uपूर्णांक32_t crc32;  /* crc32 checksum of the payload */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा mc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t io_debug_size_bytes; /* size of debug array in dwords */
	uपूर्णांक32_t io_debug_array_offset_bytes; /* payload offset from the start of the header */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा smc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_start_addr;
पूर्ण;

/* version_major=2, version_minor=0 */
काष्ठा smc_firmware_header_v2_0 अणु
	काष्ठा smc_firmware_header_v1_0 v1_0;
	uपूर्णांक32_t ppt_offset_bytes; /* soft pptable offset */
	uपूर्णांक32_t ppt_size_bytes; /* soft pptable size */
पूर्ण;

काष्ठा smc_soft_pptable_entry अणु
        uपूर्णांक32_t id;
        uपूर्णांक32_t ppt_offset_bytes;
        uपूर्णांक32_t ppt_size_bytes;
पूर्ण;

/* version_major=2, version_minor=1 */
काष्ठा smc_firmware_header_v2_1 अणु
        काष्ठा smc_firmware_header_v1_0 v1_0;
        uपूर्णांक32_t pptable_count;
        uपूर्णांक32_t pptable_entry_offset;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा psp_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t sos_offset_bytes;
	uपूर्णांक32_t sos_size_bytes;
पूर्ण;

/* version_major=1, version_minor=1 */
काष्ठा psp_firmware_header_v1_1 अणु
	काष्ठा psp_firmware_header_v1_0 v1_0;
	uपूर्णांक32_t toc_header_version;
	uपूर्णांक32_t toc_offset_bytes;
	uपूर्णांक32_t toc_size_bytes;
	uपूर्णांक32_t kdb_header_version;
	uपूर्णांक32_t kdb_offset_bytes;
	uपूर्णांक32_t kdb_size_bytes;
पूर्ण;

/* version_major=1, version_minor=2 */
काष्ठा psp_firmware_header_v1_2 अणु
	काष्ठा psp_firmware_header_v1_0 v1_0;
	uपूर्णांक32_t reserve[3];
	uपूर्णांक32_t kdb_header_version;
	uपूर्णांक32_t kdb_offset_bytes;
	uपूर्णांक32_t kdb_size_bytes;
पूर्ण;

/* version_major=1, version_minor=3 */
काष्ठा psp_firmware_header_v1_3 अणु
	काष्ठा psp_firmware_header_v1_1 v1_1;
	uपूर्णांक32_t spl_header_version;
	uपूर्णांक32_t spl_offset_bytes;
	uपूर्णांक32_t spl_size_bytes;
	uपूर्णांक32_t rl_header_version;
	uपूर्णांक32_t rl_offset_bytes;
	uपूर्णांक32_t rl_size_bytes;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा ta_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ta_xgmi_ucode_version;
	uपूर्णांक32_t ta_xgmi_offset_bytes;
	uपूर्णांक32_t ta_xgmi_size_bytes;
	uपूर्णांक32_t ta_ras_ucode_version;
	uपूर्णांक32_t ta_ras_offset_bytes;
	uपूर्णांक32_t ta_ras_size_bytes;
	uपूर्णांक32_t ta_hdcp_ucode_version;
	uपूर्णांक32_t ta_hdcp_offset_bytes;
	uपूर्णांक32_t ta_hdcp_size_bytes;
	uपूर्णांक32_t ta_dपंचांग_ucode_version;
	uपूर्णांक32_t ta_dपंचांग_offset_bytes;
	uपूर्णांक32_t ta_dपंचांग_size_bytes;
	uपूर्णांक32_t ta_securedisplay_ucode_version;
	uपूर्णांक32_t ta_securedisplay_offset_bytes;
	uपूर्णांक32_t ta_securedisplay_size_bytes;
पूर्ण;

क्रमागत ta_fw_type अणु
	TA_FW_TYPE_UNKOWN,
	TA_FW_TYPE_PSP_ASD,
	TA_FW_TYPE_PSP_XGMI,
	TA_FW_TYPE_PSP_RAS,
	TA_FW_TYPE_PSP_HDCP,
	TA_FW_TYPE_PSP_DTM,
	TA_FW_TYPE_PSP_RAP,
	TA_FW_TYPE_PSP_SECUREDISPLAY,
	TA_FW_TYPE_MAX_INDEX,
पूर्ण;

काष्ठा ta_fw_bin_desc अणु
	uपूर्णांक32_t fw_type;
	uपूर्णांक32_t fw_version;
	uपूर्णांक32_t offset_bytes;
	uपूर्णांक32_t size_bytes;
पूर्ण;

/* version_major=2, version_minor=0 */
काष्ठा ta_firmware_header_v2_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ta_fw_bin_count;
	काष्ठा ta_fw_bin_desc ta_fw_bin[];
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा gfx_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t jt_offset; /* jt location */
	uपूर्णांक32_t jt_size;  /* size of jt */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा mes_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t mes_ucode_version;
	uपूर्णांक32_t mes_ucode_size_bytes;
	uपूर्णांक32_t mes_ucode_offset_bytes;
	uपूर्णांक32_t mes_ucode_data_version;
	uपूर्णांक32_t mes_ucode_data_size_bytes;
	uपूर्णांक32_t mes_ucode_data_offset_bytes;
	uपूर्णांक32_t mes_uc_start_addr_lo;
	uपूर्णांक32_t mes_uc_start_addr_hi;
	uपूर्णांक32_t mes_data_start_addr_lo;
	uपूर्णांक32_t mes_data_start_addr_hi;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा rlc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t save_and_restore_offset;
	uपूर्णांक32_t clear_state_descriptor_offset;
	uपूर्णांक32_t avail_scratch_ram_locations;
	uपूर्णांक32_t master_pkt_description_offset;
पूर्ण;

/* version_major=2, version_minor=0 */
काष्ठा rlc_firmware_header_v2_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t jt_offset; /* jt location */
	uपूर्णांक32_t jt_size;  /* size of jt */
	uपूर्णांक32_t save_and_restore_offset;
	uपूर्णांक32_t clear_state_descriptor_offset;
	uपूर्णांक32_t avail_scratch_ram_locations;
	uपूर्णांक32_t reg_restore_list_size;
	uपूर्णांक32_t reg_list_क्रमmat_start;
	uपूर्णांक32_t reg_list_क्रमmat_separate_start;
	uपूर्णांक32_t starting_offsets_start;
	uपूर्णांक32_t reg_list_क्रमmat_size_bytes; /* size of reg list क्रमmat array in bytes */
	uपूर्णांक32_t reg_list_क्रमmat_array_offset_bytes; /* payload offset from the start of the header */
	uपूर्णांक32_t reg_list_size_bytes; /* size of reg list array in bytes */
	uपूर्णांक32_t reg_list_array_offset_bytes; /* payload offset from the start of the header */
	uपूर्णांक32_t reg_list_क्रमmat_separate_size_bytes; /* size of reg list क्रमmat array in bytes */
	uपूर्णांक32_t reg_list_क्रमmat_separate_array_offset_bytes; /* payload offset from the start of the header */
	uपूर्णांक32_t reg_list_separate_size_bytes; /* size of reg list array in bytes */
	uपूर्णांक32_t reg_list_separate_array_offset_bytes; /* payload offset from the start of the header */
पूर्ण;

/* version_major=2, version_minor=1 */
काष्ठा rlc_firmware_header_v2_1 अणु
	काष्ठा rlc_firmware_header_v2_0 v2_0;
	uपूर्णांक32_t reg_list_क्रमmat_direct_reg_list_length; /* length of direct reg list क्रमmat array */
	uपूर्णांक32_t save_restore_list_cntl_ucode_ver;
	uपूर्णांक32_t save_restore_list_cntl_feature_ver;
	uपूर्णांक32_t save_restore_list_cntl_size_bytes;
	uपूर्णांक32_t save_restore_list_cntl_offset_bytes;
	uपूर्णांक32_t save_restore_list_gpm_ucode_ver;
	uपूर्णांक32_t save_restore_list_gpm_feature_ver;
	uपूर्णांक32_t save_restore_list_gpm_size_bytes;
	uपूर्णांक32_t save_restore_list_gpm_offset_bytes;
	uपूर्णांक32_t save_restore_list_srm_ucode_ver;
	uपूर्णांक32_t save_restore_list_srm_feature_ver;
	uपूर्णांक32_t save_restore_list_srm_size_bytes;
	uपूर्णांक32_t save_restore_list_srm_offset_bytes;
पूर्ण;

/* version_major=2, version_minor=1 */
काष्ठा rlc_firmware_header_v2_2 अणु
	काष्ठा rlc_firmware_header_v2_1 v2_1;
	uपूर्णांक32_t rlc_iram_ucode_size_bytes;
	uपूर्णांक32_t rlc_iram_ucode_offset_bytes;
	uपूर्णांक32_t rlc_dram_ucode_size_bytes;
	uपूर्णांक32_t rlc_dram_ucode_offset_bytes;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा sdma_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t ucode_change_version;
	uपूर्णांक32_t jt_offset; /* jt location */
	uपूर्णांक32_t jt_size; /* size of jt */
पूर्ण;

/* version_major=1, version_minor=1 */
काष्ठा sdma_firmware_header_v1_1 अणु
	काष्ठा sdma_firmware_header_v1_0 v1_0;
	uपूर्णांक32_t digest_size;
पूर्ण;

/* gpu info payload */
काष्ठा gpu_info_firmware_v1_0 अणु
	uपूर्णांक32_t gc_num_se;
	uपूर्णांक32_t gc_num_cu_per_sh;
	uपूर्णांक32_t gc_num_sh_per_se;
	uपूर्णांक32_t gc_num_rb_per_se;
	uपूर्णांक32_t gc_num_tccs;
	uपूर्णांक32_t gc_num_gprs;
	uपूर्णांक32_t gc_num_max_gs_thds;
	uपूर्णांक32_t gc_gs_table_depth;
	uपूर्णांक32_t gc_gsprim_buff_depth;
	uपूर्णांक32_t gc_parameter_cache_depth;
	uपूर्णांक32_t gc_द्विगुन_offchip_lds_buffer;
	uपूर्णांक32_t gc_wave_size;
	uपूर्णांक32_t gc_max_waves_per_simd;
	uपूर्णांक32_t gc_max_scratch_slots_per_cu;
	uपूर्णांक32_t gc_lds_size;
पूर्ण;

काष्ठा gpu_info_firmware_v1_1 अणु
	काष्ठा gpu_info_firmware_v1_0 v1_0;
	uपूर्णांक32_t num_sc_per_sh;
	uपूर्णांक32_t num_packer_per_sc;
पूर्ण;

/* gpu info payload
 * version_major=1, version_minor=1 */
काष्ठा gpu_info_firmware_v1_2 अणु
	काष्ठा gpu_info_firmware_v1_1 v1_1;
	काष्ठा gpu_info_soc_bounding_box_v1_0 soc_bounding_box;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा gpu_info_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक16_t version_major; /* version */
	uपूर्णांक16_t version_minor; /* version */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा dmcu_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t पूर्णांकv_offset_bytes; /* पूर्णांकerrupt vectors offset from end of header, in bytes */
	uपूर्णांक32_t पूर्णांकv_size_bytes;  /* size of पूर्णांकerrupt vectors, in bytes */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा dmcub_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t inst_स्थिर_bytes; /* size of inकाष्ठाion region, in bytes */
	uपूर्णांक32_t bss_data_bytes; /* size of bss/data region, in bytes */
पूर्ण;

/* header is fixed size */
जोड़ amdgpu_firmware_header अणु
	काष्ठा common_firmware_header common;
	काष्ठा mc_firmware_header_v1_0 mc;
	काष्ठा smc_firmware_header_v1_0 smc;
	काष्ठा smc_firmware_header_v2_0 smc_v2_0;
	काष्ठा psp_firmware_header_v1_0 psp;
	काष्ठा psp_firmware_header_v1_1 psp_v1_1;
	काष्ठा psp_firmware_header_v1_3 psp_v1_3;
	काष्ठा ta_firmware_header_v1_0 ta;
	काष्ठा ta_firmware_header_v2_0 ta_v2_0;
	काष्ठा gfx_firmware_header_v1_0 gfx;
	काष्ठा rlc_firmware_header_v1_0 rlc;
	काष्ठा rlc_firmware_header_v2_0 rlc_v2_0;
	काष्ठा rlc_firmware_header_v2_1 rlc_v2_1;
	काष्ठा sdma_firmware_header_v1_0 sdma;
	काष्ठा sdma_firmware_header_v1_1 sdma_v1_1;
	काष्ठा gpu_info_firmware_header_v1_0 gpu_info;
	काष्ठा dmcu_firmware_header_v1_0 dmcu;
	काष्ठा dmcub_firmware_header_v1_0 dmcub;
	uपूर्णांक8_t raw[0x100];
पूर्ण;

#घोषणा UCODE_MAX_TA_PACKAGING ((माप(जोड़ amdgpu_firmware_header) - माप(काष्ठा common_firmware_header) - 4) / माप(काष्ठा ta_fw_bin_desc))

/*
 * fw loading support
 */
क्रमागत AMDGPU_UCODE_ID अणु
	AMDGPU_UCODE_ID_SDMA0 = 0,
	AMDGPU_UCODE_ID_SDMA1,
	AMDGPU_UCODE_ID_SDMA2,
	AMDGPU_UCODE_ID_SDMA3,
	AMDGPU_UCODE_ID_SDMA4,
	AMDGPU_UCODE_ID_SDMA5,
	AMDGPU_UCODE_ID_SDMA6,
	AMDGPU_UCODE_ID_SDMA7,
	AMDGPU_UCODE_ID_CP_CE,
	AMDGPU_UCODE_ID_CP_PFP,
	AMDGPU_UCODE_ID_CP_ME,
	AMDGPU_UCODE_ID_CP_MEC1,
	AMDGPU_UCODE_ID_CP_MEC1_JT,
	AMDGPU_UCODE_ID_CP_MEC2,
	AMDGPU_UCODE_ID_CP_MEC2_JT,
	AMDGPU_UCODE_ID_CP_MES,
	AMDGPU_UCODE_ID_CP_MES_DATA,
	AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL,
	AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM,
	AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM,
	AMDGPU_UCODE_ID_RLC_IRAM,
	AMDGPU_UCODE_ID_RLC_DRAM,
	AMDGPU_UCODE_ID_RLC_G,
	AMDGPU_UCODE_ID_STORAGE,
	AMDGPU_UCODE_ID_SMC,
	AMDGPU_UCODE_ID_UVD,
	AMDGPU_UCODE_ID_UVD1,
	AMDGPU_UCODE_ID_VCE,
	AMDGPU_UCODE_ID_VCN,
	AMDGPU_UCODE_ID_VCN1,
	AMDGPU_UCODE_ID_DMCU_ERAM,
	AMDGPU_UCODE_ID_DMCU_INTV,
	AMDGPU_UCODE_ID_VCN0_RAM,
	AMDGPU_UCODE_ID_VCN1_RAM,
	AMDGPU_UCODE_ID_DMCUB,
	AMDGPU_UCODE_ID_MAXIMUM,
पूर्ण;

/* engine firmware status */
क्रमागत AMDGPU_UCODE_STATUS अणु
	AMDGPU_UCODE_STATUS_INVALID,
	AMDGPU_UCODE_STATUS_NOT_LOADED,
	AMDGPU_UCODE_STATUS_LOADED,
पूर्ण;

क्रमागत amdgpu_firmware_load_type अणु
	AMDGPU_FW_LOAD_सूचीECT = 0,
	AMDGPU_FW_LOAD_SMU,
	AMDGPU_FW_LOAD_PSP,
	AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO,
पूर्ण;

/* conक्रमm to smu_ucode_xfer_cz.h */
#घोषणा AMDGPU_SDMA0_UCODE_LOADED	0x00000001
#घोषणा AMDGPU_SDMA1_UCODE_LOADED	0x00000002
#घोषणा AMDGPU_CPCE_UCODE_LOADED	0x00000004
#घोषणा AMDGPU_CPPFP_UCODE_LOADED	0x00000008
#घोषणा AMDGPU_CPME_UCODE_LOADED	0x00000010
#घोषणा AMDGPU_CPMEC1_UCODE_LOADED	0x00000020
#घोषणा AMDGPU_CPMEC2_UCODE_LOADED	0x00000040
#घोषणा AMDGPU_CPRLC_UCODE_LOADED	0x00000100

/* amdgpu firmware info */
काष्ठा amdgpu_firmware_info अणु
	/* ucode ID */
	क्रमागत AMDGPU_UCODE_ID ucode_id;
	/* request_firmware */
	स्थिर काष्ठा firmware *fw;
	/* starting mc address */
	uपूर्णांक64_t mc_addr;
	/* kernel linear address */
	व्योम *kaddr;
	/* ucode_size_bytes */
	uपूर्णांक32_t ucode_size;
	/* starting पंचांगr mc address */
	uपूर्णांक32_t पंचांगr_mc_addr_lo;
	uपूर्णांक32_t पंचांगr_mc_addr_hi;
पूर्ण;

काष्ठा amdgpu_firmware अणु
	काष्ठा amdgpu_firmware_info ucode[AMDGPU_UCODE_ID_MAXIMUM];
	क्रमागत amdgpu_firmware_load_type load_type;
	काष्ठा amdgpu_bo *fw_buf;
	अचिन्हित पूर्णांक fw_size;
	अचिन्हित पूर्णांक max_ucodes;
	/* firmwares are loaded by psp instead of smu from vega10 */
	स्थिर काष्ठा amdgpu_psp_funcs *funcs;
	काष्ठा amdgpu_bo *rbuf;
	काष्ठा mutex mutex;

	/* gpu info firmware data poपूर्णांकer */
	स्थिर काष्ठा firmware *gpu_info_fw;

	व्योम *fw_buf_ptr;
	uपूर्णांक64_t fw_buf_mc;
पूर्ण;

व्योम amdgpu_ucode_prपूर्णांक_mc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_smc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_gfx_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_rlc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_sdma_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_psp_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम amdgpu_ucode_prपूर्णांक_gpu_info_hdr(स्थिर काष्ठा common_firmware_header *hdr);
पूर्णांक amdgpu_ucode_validate(स्थिर काष्ठा firmware *fw);
bool amdgpu_ucode_hdr_version(जोड़ amdgpu_firmware_header *hdr,
				uपूर्णांक16_t hdr_major, uपूर्णांक16_t hdr_minor);

पूर्णांक amdgpu_ucode_init_bo(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ucode_create_bo(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ucode_sysfs_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_ucode_मुक्त_bo(काष्ठा amdgpu_device *adev);
व्योम amdgpu_ucode_sysfs_fini(काष्ठा amdgpu_device *adev);

क्रमागत amdgpu_firmware_load_type
amdgpu_ucode_get_load_type(काष्ठा amdgpu_device *adev, पूर्णांक load_type);

#पूर्ण_अगर
