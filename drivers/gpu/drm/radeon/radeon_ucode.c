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

#समावेश "radeon.h"
#समावेश "radeon_ucode.h"

अटल व्योम radeon_ucode_prपूर्णांक_common_hdr(स्थिर काष्ठा common_firmware_header *hdr)
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

व्योम radeon_ucode_prपूर्णांक_mc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("MC\n");
	radeon_ucode_prपूर्णांक_common_hdr(hdr);

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

व्योम radeon_ucode_prपूर्णांक_smc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("SMC\n");
	radeon_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा smc_firmware_header_v1_0 *smc_hdr =
			container_of(hdr, काष्ठा smc_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_start_addr: %u\n", le32_to_cpu(smc_hdr->ucode_start_addr));
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown SMC ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम radeon_ucode_prपूर्णांक_gfx_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("GFX\n");
	radeon_ucode_prपूर्णांक_common_hdr(hdr);

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

व्योम radeon_ucode_prपूर्णांक_rlc_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("RLC\n");
	radeon_ucode_prपूर्णांक_common_hdr(hdr);

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
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown RLC ucode version: %u.%u\n", version_major, version_minor);
	पूर्ण
पूर्ण

व्योम radeon_ucode_prपूर्णांक_sdma_hdr(स्थिर काष्ठा common_firmware_header *hdr)
अणु
	uपूर्णांक16_t version_major = le16_to_cpu(hdr->header_version_major);
	uपूर्णांक16_t version_minor = le16_to_cpu(hdr->header_version_minor);

	DRM_DEBUG("SDMA\n");
	radeon_ucode_prपूर्णांक_common_hdr(hdr);

	अगर (version_major == 1) अणु
		स्थिर काष्ठा sdma_firmware_header_v1_0 *sdma_hdr =
			container_of(hdr, काष्ठा sdma_firmware_header_v1_0, header);

		DRM_DEBUG("ucode_feature_version: %u\n",
			  le32_to_cpu(sdma_hdr->ucode_feature_version));
		DRM_DEBUG("ucode_change_version: %u\n",
			  le32_to_cpu(sdma_hdr->ucode_change_version));
		DRM_DEBUG("jt_offset: %u\n", le32_to_cpu(sdma_hdr->jt_offset));
		DRM_DEBUG("jt_size: %u\n", le32_to_cpu(sdma_hdr->jt_size));
	पूर्ण अन्यथा अणु
		DRM_ERROR("Unknown SDMA ucode version: %u.%u\n",
			  version_major, version_minor);
	पूर्ण
पूर्ण

पूर्णांक radeon_ucode_validate(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा common_firmware_header *hdr =
		(स्थिर काष्ठा common_firmware_header *)fw->data;

	अगर (fw->size == le32_to_cpu(hdr->size_bytes))
		वापस 0;

	वापस -EINVAL;
पूर्ण

