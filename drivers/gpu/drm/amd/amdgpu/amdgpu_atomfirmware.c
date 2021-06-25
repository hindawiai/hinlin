<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atomfirmware.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "atom.h"
#समावेश "atombios.h"
#समावेश "soc15_hw_ip.h"

bool amdgpu_atomfirmware_gpu_supports_भवization(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						firmwareinfo);
	uपूर्णांक16_t data_offset;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, शून्य,
					  शून्य, शून्य, &data_offset)) अणु
		काष्ठा atom_firmware_info_v3_1 *firmware_info =
			(काष्ठा atom_firmware_info_v3_1 *)(adev->mode_info.atom_context->bios +
							   data_offset);

		अगर (le32_to_cpu(firmware_info->firmware_capability) &
		    ATOM_FIRMWARE_CAP_GPU_VIRTUALIZATION)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम amdgpu_atomfirmware_scratch_regs_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						firmwareinfo);
	uपूर्णांक16_t data_offset;

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, शून्य,
					  शून्य, शून्य, &data_offset)) अणु
		काष्ठा atom_firmware_info_v3_1 *firmware_info =
			(काष्ठा atom_firmware_info_v3_1 *)(adev->mode_info.atom_context->bios +
							   data_offset);

		adev->bios_scratch_reg_offset =
			le32_to_cpu(firmware_info->bios_scratch_reg_startaddr);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_atomfirmware_allocate_fb_scratch(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	पूर्णांक index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						vram_usagebyfirmware);
	काष्ठा vram_usagebyfirmware_v2_1 *firmware_usage;
	uपूर्णांक32_t start_addr, size;
	uपूर्णांक16_t data_offset;
	पूर्णांक usage_bytes = 0;

	अगर (amdgpu_atom_parse_data_header(ctx, index, शून्य, शून्य, शून्य, &data_offset)) अणु
		firmware_usage = (काष्ठा vram_usagebyfirmware_v2_1 *)(ctx->bios + data_offset);
		DRM_DEBUG("atom firmware requested %08x %dkb fw %dkb drv\n",
			  le32_to_cpu(firmware_usage->start_address_in_kb),
			  le16_to_cpu(firmware_usage->used_by_firmware_in_kb),
			  le16_to_cpu(firmware_usage->used_by_driver_in_kb));

		start_addr = le32_to_cpu(firmware_usage->start_address_in_kb);
		size = le16_to_cpu(firmware_usage->used_by_firmware_in_kb);

		अगर ((uपूर्णांक32_t)(start_addr & ATOM_VRAM_OPERATION_FLAGS_MASK) ==
			(uपूर्णांक32_t)(ATOM_VRAM_BLOCK_SRIOV_MSG_SHARE_RESERVATION <<
			ATOM_VRAM_OPERATION_FLAGS_SHIFT)) अणु
			/* Firmware request VRAM reservation क्रम SR-IOV */
			adev->mman.fw_vram_usage_start_offset = (start_addr &
				(~ATOM_VRAM_OPERATION_FLAGS_MASK)) << 10;
			adev->mman.fw_vram_usage_size = size << 10;
			/* Use the शेष scratch size */
			usage_bytes = 0;
		पूर्ण अन्यथा अणु
			usage_bytes = le16_to_cpu(firmware_usage->used_by_driver_in_kb) << 10;
		पूर्ण
	पूर्ण
	ctx->scratch_size_bytes = 0;
	अगर (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* allocate some scratch memory */
	ctx->scratch = kzalloc(usage_bytes, GFP_KERNEL);
	अगर (!ctx->scratch)
		वापस -ENOMEM;
	ctx->scratch_size_bytes = usage_bytes;
	वापस 0;
पूर्ण

जोड़ igp_info अणु
	काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_11 v11;
	काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_12 v12;
	काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v2_1 v21;
पूर्ण;

जोड़ umc_info अणु
	काष्ठा atom_umc_info_v3_1 v31;
	काष्ठा atom_umc_info_v3_2 v32;
	काष्ठा atom_umc_info_v3_3 v33;
पूर्ण;

जोड़ vram_info अणु
	काष्ठा atom_vram_info_header_v2_3 v23;
	काष्ठा atom_vram_info_header_v2_4 v24;
	काष्ठा atom_vram_info_header_v2_5 v25;
	काष्ठा atom_vram_info_header_v2_6 v26;
पूर्ण;

जोड़ vram_module अणु
	काष्ठा atom_vram_module_v9 v9;
	काष्ठा atom_vram_module_v10 v10;
	काष्ठा atom_vram_module_v11 v11;
पूर्ण;

अटल पूर्णांक convert_atom_mem_type_to_vram_type(काष्ठा amdgpu_device *adev,
					      पूर्णांक atom_mem_type)
अणु
	पूर्णांक vram_type;

	अगर (adev->flags & AMD_IS_APU) अणु
		चयन (atom_mem_type) अणु
		हाल Ddr2MemType:
		हाल LpDdr2MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR2;
			अवरोध;
		हाल Ddr3MemType:
		हाल LpDdr3MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR3;
			अवरोध;
		हाल Ddr4MemType:
		हाल LpDdr4MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR4;
			अवरोध;
		हाल Ddr5MemType:
		हाल LpDdr5MemType:
			vram_type = AMDGPU_VRAM_TYPE_DDR5;
			अवरोध;
		शेष:
			vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (atom_mem_type) अणु
		हाल ATOM_DGPU_VRAM_TYPE_GDDR5:
			vram_type = AMDGPU_VRAM_TYPE_GDDR5;
			अवरोध;
		हाल ATOM_DGPU_VRAM_TYPE_HBM2:
		हाल ATOM_DGPU_VRAM_TYPE_HBM2E:
			vram_type = AMDGPU_VRAM_TYPE_HBM;
			अवरोध;
		हाल ATOM_DGPU_VRAM_TYPE_GDDR6:
			vram_type = AMDGPU_VRAM_TYPE_GDDR6;
			अवरोध;
		शेष:
			vram_type = AMDGPU_VRAM_TYPE_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस vram_type;
पूर्ण


पूर्णांक
amdgpu_atomfirmware_get_vram_info(काष्ठा amdgpu_device *adev,
				  पूर्णांक *vram_width, पूर्णांक *vram_type,
				  पूर्णांक *vram_venकरोr)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index, i = 0;
	u16 data_offset, size;
	जोड़ igp_info *igp_info;
	जोड़ vram_info *vram_info;
	जोड़ vram_module *vram_module;
	u8 frev, crev;
	u8 mem_type;
	u8 mem_venकरोr;
	u32 mem_channel_number;
	u32 mem_channel_width;
	u32 module_id;

	अगर (adev->flags & AMD_IS_APU)
		index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						    पूर्णांकegratedप्रणालीinfo);
	अन्यथा
		index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						    vram_info);

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context,
					  index, &size,
					  &frev, &crev, &data_offset)) अणु
		अगर (adev->flags & AMD_IS_APU) अणु
			igp_info = (जोड़ igp_info *)
				(mode_info->atom_context->bios + data_offset);
			चयन (frev) अणु
			हाल 1:
				चयन (crev) अणु
				हाल 11:
				हाल 12:
					mem_channel_number = igp_info->v11.umachannelnumber;
					अगर (!mem_channel_number)
						mem_channel_number = 1;
					/* channel width is 64 */
					अगर (vram_width)
						*vram_width = mem_channel_number * 64;
					mem_type = igp_info->v11.memorytype;
					अगर (vram_type)
						*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			हाल 2:
				चयन (crev) अणु
				हाल 1:
				हाल 2:
					mem_channel_number = igp_info->v21.umachannelnumber;
					अगर (!mem_channel_number)
						mem_channel_number = 1;
					/* channel width is 64 */
					अगर (vram_width)
						*vram_width = mem_channel_number * 64;
					mem_type = igp_info->v21.memorytype;
					अगर (vram_type)
						*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			vram_info = (जोड़ vram_info *)
				(mode_info->atom_context->bios + data_offset);
			module_id = (RREG32(adev->bios_scratch_reg_offset + 4) & 0x00ff0000) >> 16;
			चयन (crev) अणु
			हाल 3:
				अगर (module_id > vram_info->v23.vram_module_num)
					module_id = 0;
				vram_module = (जोड़ vram_module *)vram_info->v23.vram_module;
				जबतक (i < module_id) अणु
					vram_module = (जोड़ vram_module *)
						((u8 *)vram_module + vram_module->v9.vram_module_size);
					i++;
				पूर्ण
				mem_type = vram_module->v9.memory_type;
				अगर (vram_type)
					*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
				mem_channel_number = vram_module->v9.channel_num;
				mem_channel_width = vram_module->v9.channel_width;
				अगर (vram_width)
					*vram_width = mem_channel_number * (1 << mem_channel_width);
				mem_venकरोr = (vram_module->v9.vender_rev_id) & 0xF;
				अगर (vram_venकरोr)
					*vram_venकरोr = mem_venकरोr;
				अवरोध;
			हाल 4:
				अगर (module_id > vram_info->v24.vram_module_num)
					module_id = 0;
				vram_module = (जोड़ vram_module *)vram_info->v24.vram_module;
				जबतक (i < module_id) अणु
					vram_module = (जोड़ vram_module *)
						((u8 *)vram_module + vram_module->v10.vram_module_size);
					i++;
				पूर्ण
				mem_type = vram_module->v10.memory_type;
				अगर (vram_type)
					*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
				mem_channel_number = vram_module->v10.channel_num;
				mem_channel_width = vram_module->v10.channel_width;
				अगर (vram_width)
					*vram_width = mem_channel_number * (1 << mem_channel_width);
				mem_venकरोr = (vram_module->v10.vender_rev_id) & 0xF;
				अगर (vram_venकरोr)
					*vram_venकरोr = mem_venकरोr;
				अवरोध;
			हाल 5:
				अगर (module_id > vram_info->v25.vram_module_num)
					module_id = 0;
				vram_module = (जोड़ vram_module *)vram_info->v25.vram_module;
				जबतक (i < module_id) अणु
					vram_module = (जोड़ vram_module *)
						((u8 *)vram_module + vram_module->v11.vram_module_size);
					i++;
				पूर्ण
				mem_type = vram_module->v11.memory_type;
				अगर (vram_type)
					*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
				mem_channel_number = vram_module->v11.channel_num;
				mem_channel_width = vram_module->v11.channel_width;
				अगर (vram_width)
					*vram_width = mem_channel_number * (1 << mem_channel_width);
				mem_venकरोr = (vram_module->v11.vender_rev_id) & 0xF;
				अगर (vram_venकरोr)
					*vram_venकरोr = mem_venकरोr;
				अवरोध;
			हाल 6:
				अगर (module_id > vram_info->v26.vram_module_num)
					module_id = 0;
				vram_module = (जोड़ vram_module *)vram_info->v26.vram_module;
				जबतक (i < module_id) अणु
					vram_module = (जोड़ vram_module *)
						((u8 *)vram_module + vram_module->v9.vram_module_size);
					i++;
				पूर्ण
				mem_type = vram_module->v9.memory_type;
				अगर (vram_type)
					*vram_type = convert_atom_mem_type_to_vram_type(adev, mem_type);
				mem_channel_number = vram_module->v9.channel_num;
				mem_channel_width = vram_module->v9.channel_width;
				अगर (vram_width)
					*vram_width = mem_channel_number * (1 << mem_channel_width);
				mem_venकरोr = (vram_module->v9.vender_rev_id) & 0xF;
				अगर (vram_venकरोr)
					*vram_venकरोr = mem_venकरोr;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

/*
 * Return true अगर vbios enabled ecc by शेष, अगर umc info table is available
 * or false अगर ecc is not enabled or umc info table is not available
 */
bool amdgpu_atomfirmware_mem_ecc_supported(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index;
	u16 data_offset, size;
	जोड़ umc_info *umc_info;
	u8 frev, crev;
	bool ecc_शेष_enabled = false;
	u8 umc_config;
	u32 umc_config1;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
			umc_info);

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context,
				index, &size, &frev, &crev, &data_offset)) अणु
		अगर (frev == 3) अणु
			umc_info = (जोड़ umc_info *)
				(mode_info->atom_context->bios + data_offset);
			चयन (crev) अणु
			हाल 1:
				umc_config = le32_to_cpu(umc_info->v31.umc_config);
				ecc_शेष_enabled =
					(umc_config & UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE) ? true : false;
				अवरोध;
			हाल 2:
				umc_config = le32_to_cpu(umc_info->v32.umc_config);
				ecc_शेष_enabled =
					(umc_config & UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE) ? true : false;
				अवरोध;
			हाल 3:
				umc_config = le32_to_cpu(umc_info->v33.umc_config);
				umc_config1 = le32_to_cpu(umc_info->v33.umc_config1);
				ecc_शेष_enabled =
					((umc_config & UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE) ||
					 (umc_config1 & UMC_CONFIG1__ENABLE_ECC_CAPABLE)) ? true : false;
				अवरोध;
			शेष:
				/* unsupported crev */
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ecc_शेष_enabled;
पूर्ण

जोड़ firmware_info अणु
	काष्ठा atom_firmware_info_v3_1 v31;
	काष्ठा atom_firmware_info_v3_2 v32;
	काष्ठा atom_firmware_info_v3_3 v33;
	काष्ठा atom_firmware_info_v3_4 v34;
पूर्ण;

/*
 * Return true अगर vbios supports sram ecc or false अगर not
 */
bool amdgpu_atomfirmware_sram_ecc_supported(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index;
	u16 data_offset, size;
	जोड़ firmware_info *firmware_info;
	u8 frev, crev;
	bool sram_ecc_supported = false;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
			firmwareinfo);

	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context,
				index, &size, &frev, &crev, &data_offset)) अणु
		/* support firmware_info 3.1 + */
		अगर ((frev == 3 && crev >=1) || (frev > 3)) अणु
			firmware_info = (जोड़ firmware_info *)
				(mode_info->atom_context->bios + data_offset);
			sram_ecc_supported =
				(le32_to_cpu(firmware_info->v31.firmware_capability) &
				 ATOM_FIRMWARE_CAP_SRAM_ECC) ? true : false;
		पूर्ण
	पूर्ण

	वापस sram_ecc_supported;
पूर्ण

जोड़ smu_info अणु
	काष्ठा atom_smu_info_v3_1 v31;
पूर्ण;

पूर्णांक amdgpu_atomfirmware_get_घड़ी_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	काष्ठा amdgpu_pll *spll = &adev->घड़ी.spll;
	काष्ठा amdgpu_pll *mpll = &adev->घड़ी.mpll;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t data_offset;
	पूर्णांक ret = -EINVAL, index;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		जोड़ firmware_info *firmware_info =
			(जोड़ firmware_info *)(mode_info->atom_context->bios +
						data_offset);

		adev->घड़ी.शेष_sclk =
			le32_to_cpu(firmware_info->v31.bootup_sclk_in10khz);
		adev->घड़ी.शेष_mclk =
			le32_to_cpu(firmware_info->v31.bootup_mclk_in10khz);

		adev->pm.current_sclk = adev->घड़ी.शेष_sclk;
		adev->pm.current_mclk = adev->घड़ी.शेष_mclk;

		/* not technically a घड़ी, but... */
		adev->mode_info.firmware_flags =
			le32_to_cpu(firmware_info->v31.firmware_capability);

		ret = 0;
	पूर्ण

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    smu_info);
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		जोड़ smu_info *smu_info =
			(जोड़ smu_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* प्रणाली घड़ी */
		spll->reference_freq = le32_to_cpu(smu_info->v31.core_refclk_10khz);

		spll->reference_भाग = 0;
		spll->min_post_भाग = 1;
		spll->max_post_भाग = 1;
		spll->min_ref_भाग = 2;
		spll->max_ref_भाग = 0xff;
		spll->min_feedback_भाग = 4;
		spll->max_feedback_भाग = 0xff;
		spll->best_vco = 0;

		ret = 0;
	पूर्ण

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    umc_info);
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		जोड़ umc_info *umc_info =
			(जोड़ umc_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* memory घड़ी */
		mpll->reference_freq = le32_to_cpu(umc_info->v31.mem_refclk_10khz);

		mpll->reference_भाग = 0;
		mpll->min_post_भाग = 1;
		mpll->max_post_भाग = 1;
		mpll->min_ref_भाग = 2;
		mpll->max_ref_भाग = 0xff;
		mpll->min_feedback_भाग = 4;
		mpll->max_feedback_भाग = 0xff;
		mpll->best_vco = 0;

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

जोड़ gfx_info अणु
	काष्ठा atom_gfx_info_v2_4 v24;
	काष्ठा atom_gfx_info_v2_7 v27;
पूर्ण;

पूर्णांक amdgpu_atomfirmware_get_gfx_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t data_offset;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    gfx_info);
	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		जोड़ gfx_info *gfx_info = (जोड़ gfx_info *)
			(mode_info->atom_context->bios + data_offset);
		चयन (crev) अणु
		हाल 4:
			adev->gfx.config.max_shader_engines = gfx_info->v24.max_shader_engines;
			adev->gfx.config.max_cu_per_sh = gfx_info->v24.max_cu_per_sh;
			adev->gfx.config.max_sh_per_se = gfx_info->v24.max_sh_per_se;
			adev->gfx.config.max_backends_per_se = gfx_info->v24.max_backends_per_se;
			adev->gfx.config.max_texture_channel_caches = gfx_info->v24.max_texture_channel_caches;
			adev->gfx.config.max_gprs = le16_to_cpu(gfx_info->v24.gc_num_gprs);
			adev->gfx.config.max_gs_thपढ़ोs = gfx_info->v24.gc_num_max_gs_thds;
			adev->gfx.config.gs_vgt_table_depth = gfx_info->v24.gc_gs_table_depth;
			adev->gfx.config.gs_prim_buffer_depth =
				le16_to_cpu(gfx_info->v24.gc_gsprim_buff_depth);
			adev->gfx.config.द्विगुन_offchip_lds_buf =
				gfx_info->v24.gc_द्विगुन_offchip_lds_buffer;
			adev->gfx.cu_info.wave_front_size = le16_to_cpu(gfx_info->v24.gc_wave_size);
			adev->gfx.cu_info.max_waves_per_simd = le16_to_cpu(gfx_info->v24.gc_max_waves_per_simd);
			adev->gfx.cu_info.max_scratch_slots_per_cu = gfx_info->v24.gc_max_scratch_slots_per_cu;
			adev->gfx.cu_info.lds_size = le16_to_cpu(gfx_info->v24.gc_lds_size);
			वापस 0;
		हाल 7:
			adev->gfx.config.max_shader_engines = gfx_info->v27.max_shader_engines;
			adev->gfx.config.max_cu_per_sh = gfx_info->v27.max_cu_per_sh;
			adev->gfx.config.max_sh_per_se = gfx_info->v27.max_sh_per_se;
			adev->gfx.config.max_backends_per_se = gfx_info->v27.max_backends_per_se;
			adev->gfx.config.max_texture_channel_caches = gfx_info->v27.max_texture_channel_caches;
			adev->gfx.config.max_gprs = le16_to_cpu(gfx_info->v27.gc_num_gprs);
			adev->gfx.config.max_gs_thपढ़ोs = gfx_info->v27.gc_num_max_gs_thds;
			adev->gfx.config.gs_vgt_table_depth = gfx_info->v27.gc_gs_table_depth;
			adev->gfx.config.gs_prim_buffer_depth = le16_to_cpu(gfx_info->v27.gc_gsprim_buff_depth);
			adev->gfx.config.द्विगुन_offchip_lds_buf = gfx_info->v27.gc_द्विगुन_offchip_lds_buffer;
			adev->gfx.cu_info.wave_front_size = le16_to_cpu(gfx_info->v27.gc_wave_size);
			adev->gfx.cu_info.max_waves_per_simd = le16_to_cpu(gfx_info->v27.gc_max_waves_per_simd);
			adev->gfx.cu_info.max_scratch_slots_per_cu = gfx_info->v27.gc_max_scratch_slots_per_cu;
			adev->gfx.cu_info.lds_size = le16_to_cpu(gfx_info->v27.gc_lds_size);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Check अगर VBIOS supports GDDR6 training data save/restore
 */
अटल bool gddr6_mem_train_vbios_support(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक16_t data_offset;
	पूर्णांक index;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);
	अगर (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, शून्य,
					  शून्य, शून्य, &data_offset)) अणु
		काष्ठा atom_firmware_info_v3_1 *firmware_info =
			(काष्ठा atom_firmware_info_v3_1 *)(adev->mode_info.atom_context->bios +
							   data_offset);

		DRM_DEBUG("atom firmware capability:0x%08x.\n",
			  le32_to_cpu(firmware_info->firmware_capability));

		अगर (le32_to_cpu(firmware_info->firmware_capability) &
		    ATOM_FIRMWARE_CAP_ENABLE_2STAGE_BIST_TRAINING)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक amdgpu_mem_train_support(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t major, minor, revision, hw_v;

	अगर (gddr6_mem_train_vbios_support(adev)) अणु
		amdgpu_discovery_get_ip_version(adev, MP0_HWID, &major, &minor, &revision);
		hw_v = HW_REV(major, minor, revision);
		/*
		 * treat 0 revision as a special हाल since रेजिस्टर क्रम MP0 and MMHUB is missing
		 * क्रम some Navi10 A0, preventing driver from discovering the hwip inक्रमmation since
		 * none of the functions will be initialized, it should not cause any problems
		 */
		चयन (hw_v) अणु
		हाल HW_REV(11, 0, 0):
		हाल HW_REV(11, 0, 5):
		हाल HW_REV(11, 0, 7):
		हाल HW_REV(11, 0, 11):
		हाल HW_REV(11, 0, 12):
			ret = 1;
			अवरोध;
		शेष:
			DRM_ERROR("memory training vbios supports but psp hw(%08x)"
				  " doesn't support!\n", hw_v);
			ret = -1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
		hw_v = -1;
	पूर्ण


	DRM_DEBUG("mp0 hw_v %08x, ret:%d.\n", hw_v, ret);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_atomfirmware_get_fw_reserved_fb_size(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	जोड़ firmware_info *firmware_info;
	पूर्णांक index;
	u16 data_offset, size;
	u8 frev, crev;
	पूर्णांक fw_reserved_fb_size;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
			firmwareinfo);

	अगर (!amdgpu_atom_parse_data_header(ctx, index, &size,
				&frev, &crev, &data_offset))
		/* fail to parse data_header */
		वापस 0;

	firmware_info = (जोड़ firmware_info *)(ctx->bios + data_offset);

	अगर (frev !=3)
		वापस -EINVAL;

	चयन (crev) अणु
	हाल 4:
		fw_reserved_fb_size =
			(firmware_info->v34.fw_reserved_size_in_kb << 10);
		अवरोध;
	शेष:
		fw_reserved_fb_size = 0;
		अवरोध;
	पूर्ण

	वापस fw_reserved_fb_size;
पूर्ण
