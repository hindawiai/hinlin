<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ucode.h"

अटल व्योम amdgpu_ucode_prपूर्णांक_common_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	DRM_DEBUG("size_bytes: %u\n", le32_to_cpu(hdr->size_bytes));
	DRM_DEBUG("header_size_bytes: %u\n", le32_to_cpu(hdr->header_size_bytes));
	DRM_DEBUG("header_version_major: %u\n", le16_to_cpu(hdr->header_version_major));
	DRM_DEBUG("header_version_minor: %u\n", le16_to_cpu(hdr->header_version_minor));
	DRM_DEBUG("ip_version_major: %u\n", le16_to_cpu(hdr->ip_version_major));
	DRM_DEBUG("ip_version_minor: %u\n", le16_to_cpu(hdr->ip_version_minor));
	DRM_DEBUG("ucode_version: 0x%08x\n", le32_to_cpu(hdr->ucode_version));
	DRM_DEBUG("ucode_size_bytes: %u\n", le32_to_cpu(hdr->ucode_size_bytes));
	DRM_DEBUG("ucode_array_offset_bytes: %u\n",
		  le32_to_cpu(hdr->ucode_array_offset_bytes));
	DRM_DEBUG("crc32: 0x%08x\n", le32_to_cpu(hdr->crc32));
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_mc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("MC\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा mc_firmware_header_v1_0 *mc_hdr =
			container_of(hdr, काष्ठा mc_firmware_header_v1_0, header);

		DRM_DEBUG("io_debug_size_bytes: %u\n",
			  le32_to_cpu(mc_hdr->io_debug_size_bytes));
		DRM_DEBUG("io_debug_array_offset_bytes: %u\n",
			  le32_to_cpu(mc_hdr->io_debug_array_offset_bytes));
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown MC ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_smc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);
	स्थिर काष्ठा smc_firmware_header_v1_0 *v1_0_hdr;
	स्थिर काष्ठा smc_firmware_header_v2_0 *v2_0_hdr;
	स्थिर काष्ठा smc_firmware_header_v2_1 *v2_1_hdr;

	DRM_DEBUG("SMC\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		v1_0_hdr = container_of(hdr, काष्ठा smc_firmware_header_v1_0, header);
		DRM_DEBUG("ucode_start_addr: %u\n", le32_to_cpu(v1_0_hdr->ucode_start_addr));
	पूर्ण अन्यथा अगर (version_major == 2) अणु
		चयन (version_minor) अणु
		हाल 0:
			v2_0_hdr = container_of(hdr, काष्ठा smc_firmware_header_v2_0, v1_0.header);
			DRM_DEBUG("ppt_offset_bytes: %u\n", le32_to_cpu(v2_0_hdr->ppt_offset_bytes));
			DRM_DEBUG("ppt_size_bytes: %u\n", le32_to_cpu(v2_0_hdr->ppt_size_bytes));
			अवरोध;
		हाल 1:
			v2_1_hdr = container_of(hdr, काष्ठा smc_firmware_header_v2_1, v1_0.header);
			DRM_DEBUG("pptable_count: %u\n", le32_to_cpu(v2_1_hdr->pptable_count));
			DRM_DEBUG("pptable_entry_offset: %u\n", le32_to_cpu(v2_1_hdr->pptable_entry_offset));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown SMC ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_gfx_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("GFX\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा gfx_firmware_header_v1_0 *gfx_hdr =
			container_of(hdr, काष्ठा gfx_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(gfx_hdr->ucode_feature_version));
		DRM_DEBUG("jt_offset: %u\n", le32_to_cpu(gfx_hdr->jt_offset));
		DRM_DEBUG("jt_size: %u\n", le32_to_cpu(gfx_hdr->jt_size));
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown GFX ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_rlc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("RLC\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा rlc_firmware_header_v1_0 *rlc_hdr =
			container_of(hdr, काष्ठा rlc_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(rlc_hdr->ucode_feature_version));
		DRM_DEBUG("save_and_restore_offset: %u\n",
			  le32_to_cpu(rlc_hdr->save_and_restore_offset));
		DRM_DEBUG("clear_state_descriptor_offset: %u\n",
			  le32_to_cpu(rlc_hdr->clear_state_descriptor_offset));
		DRM_DEBUG("avail_scratch_ram_locations: %u\n",
			  le32_to_cpu(rlc_hdr->avail_scratch_ram_locations));
		DRM_DEBUG("master_pkt_description_offset: %u\n",
			  le32_to_cpu(rlc_hdr->master_pkt_description_offset));
	पूर्ण अन्यथा अगर (version_major == 2) अणु
		स्थिर काष्ठा rlc_firmware_header_v2_0 *rlc_hdr =
			container_of(hdr, काष्ठा rlc_firmware_header_v2_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(rlc_hdr->ucode_feature_version));
		DRM_DEBUG("jt_offset: %u\n", le32_to_cpu(rlc_hdr->jt_offset));
		DRM_DEBUG("jt_size: %u\n", le32_to_cpu(rlc_hdr->jt_size));
		DRM_DEBUG("save_and_restore_offset: %u\n",
			  le32_to_cpu(rlc_hdr->save_and_restore_offset));
		DRM_DEBUG("clear_state_descriptor_offset: %u\n",
			  le32_to_cpu(rlc_hdr->clear_state_descriptor_offset));
		DRM_DEBUG("avail_scratch_ram_locations: %u\n",
			  le32_to_cpu(rlc_hdr->avail_scratch_ram_locations));
		DRM_DEBUG("reg_restore_list_size: %u\n",
			  le32_to_cpu(rlc_hdr->reg_restore_list_size));
		DRM_DEBUG("reg_list_format_start: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_start));
		DRM_DEBUG("reg_list_format_separate_start: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_separate_start));
		DRM_DEBUG("starting_offsets_start: %u\n",
			  le32_to_cpu(rlc_hdr->starting_offsets_start));
		DRM_DEBUG("reg_list_format_size_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_size_bytes));
		DRM_DEBUG("reg_list_format_array_offset_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_array_offset_bytes));
		DRM_DEBUG("reg_list_size_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_size_bytes));
		DRM_DEBUG("reg_list_array_offset_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_array_offset_bytes));
		DRM_DEBUG("reg_list_format_separate_size_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_separate_size_bytes));
		DRM_DEBUG("reg_list_format_separate_array_offset_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_क्रमmat_separate_array_offset_bytes));
		DRM_DEBUG("reg_list_separate_size_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_separate_size_bytes));
		DRM_DEBUG("reg_list_separate_array_offset_bytes: %u\n",
			  le32_to_cpu(rlc_hdr->reg_list_separate_array_offset_bytes));
		अगर (version_minor == 1) अणु
			स्थिर काष्ठा rlc_firmware_header_v2_1 *v2_1 =
				container_of(rlc_hdr, काष्ठा rlc_firmware_header_v2_1, v2_0);
			DRM_DEBUG("reg_list_format_direct_reg_list_length: %u\n",
				  le32_to_cpu(v2_1->reg_list_क्रमmat_direct_reg_list_length));
			DRM_DEBUG("save_restore_list_cntl_ucode_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_cntl_ucode_ver));
			DRM_DEBUG("save_restore_list_cntl_feature_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_cntl_feature_ver));
			DRM_DEBUG("save_restore_list_cntl_size_bytes %u\n",
				  le32_to_cpu(v2_1->save_restore_list_cntl_size_bytes));
			DRM_DEBUG("save_restore_list_cntl_offset_bytes: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_cntl_offset_bytes));
			DRM_DEBUG("save_restore_list_gpm_ucode_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_gpm_ucode_ver));
			DRM_DEBUG("save_restore_list_gpm_feature_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_gpm_feature_ver));
			DRM_DEBUG("save_restore_list_gpm_size_bytes %u\n",
				  le32_to_cpu(v2_1->save_restore_list_gpm_size_bytes));
			DRM_DEBUG("save_restore_list_gpm_offset_bytes: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_gpm_offset_bytes));
			DRM_DEBUG("save_restore_list_srm_ucode_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_srm_ucode_ver));
			DRM_DEBUG("save_restore_list_srm_feature_ver: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_srm_feature_ver));
			DRM_DEBUG("save_restore_list_srm_size_bytes %u\n",
				  le32_to_cpu(v2_1->save_restore_list_srm_size_bytes));
			DRM_DEBUG("save_restore_list_srm_offset_bytes: %u\n",
				  le32_to_cpu(v2_1->save_restore_list_srm_offset_bytes));
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown RLC ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_sdma_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("SDMA\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा sdma_firmware_header_v1_0 *sdma_hdr =
			container_of(hdr, काष्ठा sdma_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(sdma_hdr->ucode_feature_version));
		DRM_DEBUG("ucode_change_version: %u\n",
			  le32_to_cpu(sdma_hdr->ucode_change_version));
		DRM_DEBUG("jt_offset: %u\n", le32_to_cpu(sdma_hdr->jt_offset));
		DRM_DEBUG("jt_size: %u\n", le32_to_cpu(sdma_hdr->jt_size));
		अगर (version_minor >= 1) अणु
			स्थिर काष्ठा sdma_firmware_header_v1_1 *sdma_v1_1_hdr =
				container_of(sdma_hdr, काष्ठा sdma_firmware_header_v1_1, v1_0);
			DRM_DEBUG("digest_size: %u\n", le32_to_cpu(sdma_v1_1_hdr->digest_size));
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown SDMA ucode version: %u.%u\n",
			  version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_psp_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("PSP\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा psp_firmware_header_v1_0 *psp_hdr =
			container_of(hdr, काष्ठा psp_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(psp_hdr->ucode_feature_version));
		DRM_DEBUG("sos_offset_bytes: %u\n",
			  le32_to_cpu(psp_hdr->sos_offset_bytes));
		DRM_DEBUG("sos_size_bytes: %u\n",
			  le32_to_cpu(psp_hdr->sos_size_bytes));
		अगर (version_minor == 1) अणु
			स्थिर काष्ठा psp_firmware_header_v1_1 *psp_hdr_v1_1 =
				container_of(psp_hdr, काष्ठा psp_firmware_header_v1_1, v1_0);
			DRM_DEBUG("toc_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->toc_header_version));
			DRM_DEBUG("toc_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->toc_offset_bytes));
			DRM_DEBUG("toc_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->toc_size_bytes));
			DRM_DEBUG("kdb_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->kdb_header_version));
			DRM_DEBUG("kdb_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->kdb_offset_bytes));
			DRM_DEBUG("kdb_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_1->kdb_size_bytes));
		पूर्ण
		अगर (version_minor == 2) अणु
			स्थिर काष्ठा psp_firmware_header_v1_2 *psp_hdr_v1_2 =
				container_of(psp_hdr, काष्ठा psp_firmware_header_v1_2, v1_0);
			DRM_DEBUG("kdb_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_2->kdb_header_version));
			DRM_DEBUG("kdb_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_2->kdb_offset_bytes));
			DRM_DEBUG("kdb_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_2->kdb_size_bytes));
		पूर्ण
		अगर (version_minor == 3) अणु
			स्थिर काष्ठा psp_firmware_header_v1_1 *psp_hdr_v1_1 =
				container_of(psp_hdr, काष्ठा psp_firmware_header_v1_1, v1_0);
			स्थिर काष्ठा psp_firmware_header_v1_3 *psp_hdr_v1_3 =
				container_of(psp_hdr_v1_1, काष्ठा psp_firmware_header_v1_3, v1_1);
			DRM_DEBUG("toc_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.toc_header_version));
			DRM_DEBUG("toc_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.toc_offset_bytes));
			DRM_DEBUG("toc_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.toc_size_bytes));
			DRM_DEBUG("kdb_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.kdb_header_version));
			DRM_DEBUG("kdb_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.kdb_offset_bytes));
			DRM_DEBUG("kdb_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->v1_1.kdb_size_bytes));
			DRM_DEBUG("spl_header_version: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->spl_header_version));
			DRM_DEBUG("spl_offset_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->spl_offset_bytes));
			DRM_DEBUG("spl_size_bytes: %u\n",
				  le32_to_cpu(psp_hdr_v1_3->spl_size_bytes));
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown PSP ucode version: %u.%u\n",
			  version_major, version_minor);
	पूर्ण
पूर्ण

व्योम amdgpu_ucode_prपूर्णांक_gpu_info_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("GPU_INFO\n");
	amdgpu_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा gpu_info_firmware_header_v1_0 *gpu_info_hdr =
			container_of(hdr, काष्ठा gpu_info_firmware_header_v1_0, header);

		DRM_DEBUG("version_major: %u\n",
			  le16_to_cpu(gpu_info_hdr->version_major));
		DRM_DEBUG("version_minor: %u\n",
			  le16_to_cpu(gpu_info_hdr->version_minor));
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown gpu_info ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_ucode_validate(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा common_firmware_header *hdr =
		(स्थिर काष्ठा common_firmware_header *)fw->data;

	अगर (fw->size == le32_to_cpu(hdr->size_bytes))
		वापस 0;

	वापस -EINVAL;
पूर्ण

bool amdgpu_ucode_hdr_version(जोड़ amdgpu_firmware_header *hdr,
				uपूर्णांक16_t hdr_major, uपूर्णांक16_t hdr_minor)
अणु
	अगर ((hdr->common.header_version_major == hdr_major) &&
		(hdr->common.header_version_minor == hdr_minor))
		वापस false;
	वापस true;
पूर्ण

क्रमागत amdgpu_firmware_load_type
amdgpu_ucode_get_load_type(काष्ठा amdgpu_device *adev, पूर्णांक load_type)
अणु
	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
	हाल CHIP_HAIन_अंक:
		वापस AMDGPU_FW_LOAD_सूचीECT;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_HAWAII:
	हाल CHIP_MULLINS:
		वापस AMDGPU_FW_LOAD_सूचीECT;
#पूर्ण_अगर
	हाल CHIP_TOPAZ:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		वापस AMDGPU_FW_LOAD_SMU;
	हाल CHIP_VEGA10:
	हाल CHIP_RAVEN:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
	हाल CHIP_RENOIR:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_ALDEBARAN:
		अगर (!load_type)
			वापस AMDGPU_FW_LOAD_सूचीECT;
		अन्यथा
			वापस AMDGPU_FW_LOAD_PSP;
	शेष:
		DRM_ERROR("Unknown firmware load type\n");
	पूर्ण

	वापस AMDGPU_FW_LOAD_सूचीECT;
पूर्ण

#घोषणा FW_VERSION_ATTR(name, mode, field)				\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev,				\
			  काष्ठा device_attribute *attr,		\
			  अक्षर *buf)					\
अणु									\
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);			\
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);			\
									\
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", adev->field);	\
पूर्ण									\
अटल DEVICE_ATTR(name, mode, show_##name, शून्य)

FW_VERSION_ATTR(vce_fw_version, 0444, vce.fw_version);
FW_VERSION_ATTR(uvd_fw_version, 0444, uvd.fw_version);
FW_VERSION_ATTR(mc_fw_version, 0444, gmc.fw_version);
FW_VERSION_ATTR(me_fw_version, 0444, gfx.me_fw_version);
FW_VERSION_ATTR(pfp_fw_version, 0444, gfx.pfp_fw_version);
FW_VERSION_ATTR(ce_fw_version, 0444, gfx.ce_fw_version);
FW_VERSION_ATTR(rlc_fw_version, 0444, gfx.rlc_fw_version);
FW_VERSION_ATTR(rlc_srlc_fw_version, 0444, gfx.rlc_srlc_fw_version);
FW_VERSION_ATTR(rlc_srlg_fw_version, 0444, gfx.rlc_srlg_fw_version);
FW_VERSION_ATTR(rlc_srls_fw_version, 0444, gfx.rlc_srls_fw_version);
FW_VERSION_ATTR(mec_fw_version, 0444, gfx.mec_fw_version);
FW_VERSION_ATTR(mec2_fw_version, 0444, gfx.mec2_fw_version);
FW_VERSION_ATTR(sos_fw_version, 0444, psp.sos_fw_version);
FW_VERSION_ATTR(asd_fw_version, 0444, psp.asd_fw_version);
FW_VERSION_ATTR(ta_ras_fw_version, 0444, psp.ta_ras_ucode_version);
FW_VERSION_ATTR(ta_xgmi_fw_version, 0444, psp.ta_xgmi_ucode_version);
FW_VERSION_ATTR(smc_fw_version, 0444, pm.fw_version);
FW_VERSION_ATTR(sdma_fw_version, 0444, sdma.instance[0].fw_version);
FW_VERSION_ATTR(sdma2_fw_version, 0444, sdma.instance[1].fw_version);
FW_VERSION_ATTR(vcn_fw_version, 0444, vcn.fw_version);
FW_VERSION_ATTR(dmcu_fw_version, 0444, dm.dmcu_fw_version);

अटल काष्ठा attribute *fw_attrs[] = अणु
	&dev_attr_vce_fw_version.attr, &dev_attr_uvd_fw_version.attr,
	&dev_attr_mc_fw_version.attr, &dev_attr_me_fw_version.attr,
	&dev_attr_pfp_fw_version.attr, &dev_attr_ce_fw_version.attr,
	&dev_attr_rlc_fw_version.attr, &dev_attr_rlc_srlc_fw_version.attr,
	&dev_attr_rlc_srlg_fw_version.attr, &dev_attr_rlc_srls_fw_version.attr,
	&dev_attr_mec_fw_version.attr, &dev_attr_mec2_fw_version.attr,
	&dev_attr_sos_fw_version.attr, &dev_attr_asd_fw_version.attr,
	&dev_attr_ta_ras_fw_version.attr, &dev_attr_ta_xgmi_fw_version.attr,
	&dev_attr_smc_fw_version.attr, &dev_attr_sdma_fw_version.attr,
	&dev_attr_sdma2_fw_version.attr, &dev_attr_vcn_fw_version.attr,
	&dev_attr_dmcu_fw_version.attr, शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fw_attr_group = अणु
	.name = "fw_version",
	.attrs = fw_attrs
पूर्ण;

पूर्णांक amdgpu_ucode_sysfs_init(काष्ठा amdgpu_device *adev)
अणु
	वापस sysfs_create_group(&adev->dev->kobj, &fw_attr_group);
पूर्ण

व्योम amdgpu_ucode_sysfs_fini(काष्ठा amdgpu_device *adev)
अणु
	sysfs_हटाओ_group(&adev->dev->kobj, &fw_attr_group);
पूर्ण

अटल पूर्णांक amdgpu_ucode_init_single_fw(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_firmware_info *ucode,
				       uपूर्णांक64_t mc_addr, व्योम *kptr)
अणु
	स्थिर काष्ठा common_firmware_header *header = शून्य;
	स्थिर काष्ठा gfx_firmware_header_v1_0 *cp_hdr = शून्य;
	स्थिर काष्ठा dmcu_firmware_header_v1_0 *dmcu_hdr = शून्य;
	स्थिर काष्ठा dmcub_firmware_header_v1_0 *dmcub_hdr = शून्य;
	स्थिर काष्ठा mes_firmware_header_v1_0 *mes_hdr = शून्य;

	अगर (शून्य == ucode->fw)
		वापस 0;

	ucode->mc_addr = mc_addr;
	ucode->kaddr = kptr;

	अगर (ucode->ucode_id == AMDGPU_UCODE_ID_STORAGE)
		वापस 0;

	header = (स्थिर काष्ठा common_firmware_header *)ucode->fw->data;
	cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)ucode->fw->data;
	dmcu_hdr = (स्थिर काष्ठा dmcu_firmware_header_v1_0 *)ucode->fw->data;
	dmcub_hdr = (स्थिर काष्ठा dmcub_firmware_header_v1_0 *)ucode->fw->data;
	mes_hdr = (स्थिर काष्ठा mes_firmware_header_v1_0 *)ucode->fw->data;

	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP ||
	    (ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC1 &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC2 &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC1_JT &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC2_JT &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MES &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MES_DATA &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_IRAM &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_DRAM &&
		 ucode->ucode_id != AMDGPU_UCODE_ID_DMCU_ERAM &&
		 ucode->ucode_id != AMDGPU_UCODE_ID_DMCU_INTV &&
		 ucode->ucode_id != AMDGPU_UCODE_ID_DMCUB)) अणु
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes);

		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1 ||
		   ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2) अणु
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes) -
			le32_to_cpu(cp_hdr->jt_size) * 4;

		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1_JT ||
		   ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2_JT) अणु
		ucode->ucode_size = le32_to_cpu(cp_hdr->jt_size) * 4;

		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes) +
					      le32_to_cpu(cp_hdr->jt_offset) * 4),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_DMCU_ERAM) अणु
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes) -
				le32_to_cpu(dmcu_hdr->पूर्णांकv_size_bytes);

		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_DMCU_INTV) अणु
		ucode->ucode_size = le32_to_cpu(dmcu_hdr->पूर्णांकv_size_bytes);

		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes) +
					      le32_to_cpu(dmcu_hdr->पूर्णांकv_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_DMCUB) अणु
		ucode->ucode_size = le32_to_cpu(dmcub_hdr->inst_स्थिर_bytes);
		स_नकल(ucode->kaddr,
		       (व्योम *)((uपूर्णांक8_t *)ucode->fw->data +
				le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL) अणु
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_cntl_size_bytes;
		स_नकल(ucode->kaddr, adev->gfx.rlc.save_restore_list_cntl,
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM) अणु
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_gpm_size_bytes;
		स_नकल(ucode->kaddr, adev->gfx.rlc.save_restore_list_gpm,
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM) अणु
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_srm_size_bytes;
		स_नकल(ucode->kaddr, adev->gfx.rlc.save_restore_list_srm,
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_IRAM) अणु
		ucode->ucode_size = adev->gfx.rlc.rlc_iram_ucode_size_bytes;
		स_नकल(ucode->kaddr, adev->gfx.rlc.rlc_iram_ucode,
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_DRAM) अणु
		ucode->ucode_size = adev->gfx.rlc.rlc_dram_ucode_size_bytes;
		स_नकल(ucode->kaddr, adev->gfx.rlc.rlc_dram_ucode,
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MES) अणु
		ucode->ucode_size = le32_to_cpu(mes_hdr->mes_ucode_size_bytes);
		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)adev->mes.fw->data +
			      le32_to_cpu(mes_hdr->mes_ucode_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण अन्यथा अगर (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MES_DATA) अणु
		ucode->ucode_size = le32_to_cpu(mes_hdr->mes_ucode_data_size_bytes);
		स_नकल(ucode->kaddr, (व्योम *)((uपूर्णांक8_t *)adev->mes.fw->data +
			      le32_to_cpu(mes_hdr->mes_ucode_data_offset_bytes)),
		       ucode->ucode_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ucode_patch_jt(काष्ठा amdgpu_firmware_info *ucode,
				uपूर्णांक64_t mc_addr, व्योम *kptr)
अणु
	स्थिर काष्ठा gfx_firmware_header_v1_0 *header = शून्य;
	स्थिर काष्ठा common_firmware_header *comm_hdr = शून्य;
	uपूर्णांक8_t *src_addr = शून्य;
	uपूर्णांक8_t *dst_addr = शून्य;

	अगर (शून्य == ucode->fw)
		वापस 0;

	comm_hdr = (स्थिर काष्ठा common_firmware_header *)ucode->fw->data;
	header = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)ucode->fw->data;
	dst_addr = ucode->kaddr +
			   ALIGN(le32_to_cpu(comm_hdr->ucode_size_bytes),
			   PAGE_SIZE);
	src_addr = (uपूर्णांक8_t *)ucode->fw->data +
			   le32_to_cpu(comm_hdr->ucode_array_offset_bytes) +
			   (le32_to_cpu(header->jt_offset) * 4);
	स_नकल(dst_addr, src_addr, le32_to_cpu(header->jt_size) * 4);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ucode_create_bo(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_सूचीECT) अणु
		amdgpu_bo_create_kernel(adev, adev->firmware.fw_size, PAGE_SIZE,
			amdgpu_sriov_vf(adev) ? AMDGPU_GEM_DOMAIN_VRAM : AMDGPU_GEM_DOMAIN_GTT,
			&adev->firmware.fw_buf,
			&adev->firmware.fw_buf_mc,
			&adev->firmware.fw_buf_ptr);
		अगर (!adev->firmware.fw_buf) अणु
			dev_err(adev->dev, "failed to create kernel buffer for firmware.fw_buf\n");
			वापस -ENOMEM;
		पूर्ण अन्यथा अगर (amdgpu_sriov_vf(adev)) अणु
			स_रखो(adev->firmware.fw_buf_ptr, 0, adev->firmware.fw_size);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम amdgpu_ucode_मुक्त_bo(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_सूचीECT)
		amdgpu_bo_मुक्त_kernel(&adev->firmware.fw_buf,
		&adev->firmware.fw_buf_mc,
		&adev->firmware.fw_buf_ptr);
पूर्ण

पूर्णांक amdgpu_ucode_init_bo(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t fw_offset = 0;
	पूर्णांक i;
	काष्ठा amdgpu_firmware_info *ucode = शून्य;

 /* क्रम baremetal, the ucode is allocated in gtt, so करोn't need to fill the bo when reset/suspend */
	अगर (!amdgpu_sriov_vf(adev) && (amdgpu_in_reset(adev) || adev->in_suspend))
		वापस 0;
	/*
	 * अगर SMU loaded firmware, it needn't add SMC, UVD, and VCE
	 * ucode info here
	 */
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
		अगर (amdgpu_sriov_vf(adev))
			adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 3;
		अन्यथा
			adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 4;
	पूर्ण अन्यथा अणु
		adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM;
	पूर्ण

	क्रम (i = 0; i < adev->firmware.max_ucodes; i++) अणु
		ucode = &adev->firmware.ucode[i];
		अगर (ucode->fw) अणु
			amdgpu_ucode_init_single_fw(adev, ucode, adev->firmware.fw_buf_mc + fw_offset,
						    adev->firmware.fw_buf_ptr + fw_offset);
			अगर (i == AMDGPU_UCODE_ID_CP_MEC1 &&
			    adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
				स्थिर काष्ठा gfx_firmware_header_v1_0 *cp_hdr;
				cp_hdr = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)ucode->fw->data;
				amdgpu_ucode_patch_jt(ucode,  adev->firmware.fw_buf_mc + fw_offset,
						    adev->firmware.fw_buf_ptr + fw_offset);
				fw_offset += ALIGN(le32_to_cpu(cp_hdr->jt_size) << 2, PAGE_SIZE);
			पूर्ण
			fw_offset += ALIGN(ucode->ucode_size, PAGE_SIZE);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
