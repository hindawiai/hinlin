<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 *
 */
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/firmware.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "amdgpu_ucode.h"

काष्ठा amdgpu_cgs_device अणु
	काष्ठा cgs_device base;
	काष्ठा amdgpu_device *adev;
पूर्ण;

#घोषणा CGS_FUNC_ADEV							\
	काष्ठा amdgpu_device *adev =					\
		((काष्ठा amdgpu_cgs_device *)cgs_device)->adev


अटल uपूर्णांक32_t amdgpu_cgs_पढ़ो_रेजिस्टर(काष्ठा cgs_device *cgs_device, अचिन्हित offset)
अणु
	CGS_FUNC_ADEV;
	वापस RREG32(offset);
पूर्ण

अटल व्योम amdgpu_cgs_ग_लिखो_रेजिस्टर(काष्ठा cgs_device *cgs_device, अचिन्हित offset,
				      uपूर्णांक32_t value)
अणु
	CGS_FUNC_ADEV;
	WREG32(offset, value);
पूर्ण

अटल uपूर्णांक32_t amdgpu_cgs_पढ़ो_ind_रेजिस्टर(काष्ठा cgs_device *cgs_device,
					     क्रमागत cgs_ind_reg space,
					     अचिन्हित index)
अणु
	CGS_FUNC_ADEV;
	चयन (space) अणु
	हाल CGS_IND_REG__PCIE:
		वापस RREG32_PCIE(index);
	हाल CGS_IND_REG__SMC:
		वापस RREG32_SMC(index);
	हाल CGS_IND_REG__UVD_CTX:
		वापस RREG32_UVD_CTX(index);
	हाल CGS_IND_REG__DIDT:
		वापस RREG32_DIDT(index);
	हाल CGS_IND_REG_GC_CAC:
		वापस RREG32_GC_CAC(index);
	हाल CGS_IND_REG_SE_CAC:
		वापस RREG32_SE_CAC(index);
	हाल CGS_IND_REG__AUDIO_ENDPT:
		DRM_ERROR("audio endpt register access not implemented.\n");
		वापस 0;
	शेष:
		BUG();
	पूर्ण
	WARN(1, "Invalid indirect register space");
	वापस 0;
पूर्ण

अटल व्योम amdgpu_cgs_ग_लिखो_ind_रेजिस्टर(काष्ठा cgs_device *cgs_device,
					  क्रमागत cgs_ind_reg space,
					  अचिन्हित index, uपूर्णांक32_t value)
अणु
	CGS_FUNC_ADEV;
	चयन (space) अणु
	हाल CGS_IND_REG__PCIE:
		वापस WREG32_PCIE(index, value);
	हाल CGS_IND_REG__SMC:
		वापस WREG32_SMC(index, value);
	हाल CGS_IND_REG__UVD_CTX:
		वापस WREG32_UVD_CTX(index, value);
	हाल CGS_IND_REG__DIDT:
		वापस WREG32_DIDT(index, value);
	हाल CGS_IND_REG_GC_CAC:
		वापस WREG32_GC_CAC(index, value);
	हाल CGS_IND_REG_SE_CAC:
		वापस WREG32_SE_CAC(index, value);
	हाल CGS_IND_REG__AUDIO_ENDPT:
		DRM_ERROR("audio endpt register access not implemented.\n");
		वापस;
	शेष:
		BUG();
	पूर्ण
	WARN(1, "Invalid indirect register space");
पूर्ण

अटल uपूर्णांक32_t fw_type_convert(काष्ठा cgs_device *cgs_device, uपूर्णांक32_t fw_type)
अणु
	CGS_FUNC_ADEV;
	क्रमागत AMDGPU_UCODE_ID result = AMDGPU_UCODE_ID_MAXIMUM;

	चयन (fw_type) अणु
	हाल CGS_UCODE_ID_SDMA0:
		result = AMDGPU_UCODE_ID_SDMA0;
		अवरोध;
	हाल CGS_UCODE_ID_SDMA1:
		result = AMDGPU_UCODE_ID_SDMA1;
		अवरोध;
	हाल CGS_UCODE_ID_CP_CE:
		result = AMDGPU_UCODE_ID_CP_CE;
		अवरोध;
	हाल CGS_UCODE_ID_CP_PFP:
		result = AMDGPU_UCODE_ID_CP_PFP;
		अवरोध;
	हाल CGS_UCODE_ID_CP_ME:
		result = AMDGPU_UCODE_ID_CP_ME;
		अवरोध;
	हाल CGS_UCODE_ID_CP_MEC:
	हाल CGS_UCODE_ID_CP_MEC_JT1:
		result = AMDGPU_UCODE_ID_CP_MEC1;
		अवरोध;
	हाल CGS_UCODE_ID_CP_MEC_JT2:
		/* क्रम VI. JT2 should be the same as JT1, because:
			1, MEC2 and MEC1 use exactly same FW.
			2, JT2 is not pached but JT1 is.
		*/
		अगर (adev->asic_type >= CHIP_TOPAZ)
			result = AMDGPU_UCODE_ID_CP_MEC1;
		अन्यथा
			result = AMDGPU_UCODE_ID_CP_MEC2;
		अवरोध;
	हाल CGS_UCODE_ID_RLC_G:
		result = AMDGPU_UCODE_ID_RLC_G;
		अवरोध;
	हाल CGS_UCODE_ID_STORAGE:
		result = AMDGPU_UCODE_ID_STORAGE;
		अवरोध;
	शेष:
		DRM_ERROR("Firmware type not supported\n");
	पूर्ण
	वापस result;
पूर्ण

अटल uपूर्णांक16_t amdgpu_get_firmware_version(काष्ठा cgs_device *cgs_device,
					क्रमागत cgs_ucode_id type)
अणु
	CGS_FUNC_ADEV;
	uपूर्णांक16_t fw_version = 0;

	चयन (type) अणु
		हाल CGS_UCODE_ID_SDMA0:
			fw_version = adev->sdma.instance[0].fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_SDMA1:
			fw_version = adev->sdma.instance[1].fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_CE:
			fw_version = adev->gfx.ce_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_PFP:
			fw_version = adev->gfx.pfp_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_ME:
			fw_version = adev->gfx.me_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_MEC:
			fw_version = adev->gfx.mec_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_MEC_JT1:
			fw_version = adev->gfx.mec_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_CP_MEC_JT2:
			fw_version = adev->gfx.mec_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_RLC_G:
			fw_version = adev->gfx.rlc_fw_version;
			अवरोध;
		हाल CGS_UCODE_ID_STORAGE:
			अवरोध;
		शेष:
			DRM_ERROR("firmware type %d do not have version\n", type);
			अवरोध;
	पूर्ण
	वापस fw_version;
पूर्ण

अटल पूर्णांक amdgpu_cgs_get_firmware_info(काष्ठा cgs_device *cgs_device,
					क्रमागत cgs_ucode_id type,
					काष्ठा cgs_firmware_info *info)
अणु
	CGS_FUNC_ADEV;

	अगर ((CGS_UCODE_ID_SMU != type) && (CGS_UCODE_ID_SMU_SK != type)) अणु
		uपूर्णांक64_t gpu_addr;
		uपूर्णांक32_t data_size;
		स्थिर काष्ठा gfx_firmware_header_v1_0 *header;
		क्रमागत AMDGPU_UCODE_ID id;
		काष्ठा amdgpu_firmware_info *ucode;

		id = fw_type_convert(cgs_device, type);
		ucode = &adev->firmware.ucode[id];
		अगर (ucode->fw == शून्य)
			वापस -EINVAL;

		gpu_addr  = ucode->mc_addr;
		header = (स्थिर काष्ठा gfx_firmware_header_v1_0 *)ucode->fw->data;
		data_size = le32_to_cpu(header->header.ucode_size_bytes);

		अगर ((type == CGS_UCODE_ID_CP_MEC_JT1) ||
		    (type == CGS_UCODE_ID_CP_MEC_JT2)) अणु
			gpu_addr += ALIGN(le32_to_cpu(header->header.ucode_size_bytes), PAGE_SIZE);
			data_size = le32_to_cpu(header->jt_size) << 2;
		पूर्ण

		info->kptr = ucode->kaddr;
		info->image_size = data_size;
		info->mc_addr = gpu_addr;
		info->version = (uपूर्णांक16_t)le32_to_cpu(header->header.ucode_version);

		अगर (CGS_UCODE_ID_CP_MEC == type)
			info->image_size = le32_to_cpu(header->jt_offset) << 2;

		info->fw_version = amdgpu_get_firmware_version(cgs_device, type);
		info->feature_version = (uपूर्णांक16_t)le32_to_cpu(header->ucode_feature_version);
	पूर्ण अन्यथा अणु
		अक्षर fw_name[30] = अणु0पूर्ण;
		पूर्णांक err = 0;
		uपूर्णांक32_t ucode_size;
		uपूर्णांक32_t ucode_start_address;
		स्थिर uपूर्णांक8_t *src;
		स्थिर काष्ठा smc_firmware_header_v1_0 *hdr;
		स्थिर काष्ठा common_firmware_header *header;
		काष्ठा amdgpu_firmware_info *ucode = शून्य;

		अगर (!adev->pm.fw) अणु
			चयन (adev->asic_type) अणु
			हाल CHIP_TAHITI:
				म_नकल(fw_name, "radeon/tahiti_smc.bin");
				अवरोध;
			हाल CHIP_PITCAIRN:
				अगर ((adev->pdev->revision == 0x81) &&
				    ((adev->pdev->device == 0x6810) ||
				    (adev->pdev->device == 0x6811))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "radeon/pitcairn_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "radeon/pitcairn_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_VERDE:
				अगर (((adev->pdev->device == 0x6820) &&
					((adev->pdev->revision == 0x81) ||
					(adev->pdev->revision == 0x83))) ||
				    ((adev->pdev->device == 0x6821) &&
					((adev->pdev->revision == 0x83) ||
					(adev->pdev->revision == 0x87))) ||
				    ((adev->pdev->revision == 0x87) &&
					((adev->pdev->device == 0x6823) ||
					(adev->pdev->device == 0x682b)))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "radeon/verde_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "radeon/verde_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_OLAND:
				अगर (((adev->pdev->revision == 0x81) &&
					((adev->pdev->device == 0x6600) ||
					(adev->pdev->device == 0x6604) ||
					(adev->pdev->device == 0x6605) ||
					(adev->pdev->device == 0x6610))) ||
				    ((adev->pdev->revision == 0x83) &&
					(adev->pdev->device == 0x6610))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "radeon/oland_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "radeon/oland_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_HAIन_अंक:
				अगर (((adev->pdev->revision == 0x81) &&
					(adev->pdev->device == 0x6660)) ||
				    ((adev->pdev->revision == 0x83) &&
					((adev->pdev->device == 0x6660) ||
					(adev->pdev->device == 0x6663) ||
					(adev->pdev->device == 0x6665) ||
					 (adev->pdev->device == 0x6667)))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "radeon/hainan_k_smc.bin");
				पूर्ण अन्यथा अगर ((adev->pdev->revision == 0xc3) &&
					 (adev->pdev->device == 0x6665)) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "radeon/banks_k_2_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "radeon/hainan_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_BONAIRE:
				अगर ((adev->pdev->revision == 0x80) ||
					(adev->pdev->revision == 0x81) ||
					(adev->pdev->device == 0x665f)) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "amdgpu/bonaire_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "amdgpu/bonaire_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_HAWAII:
				अगर (adev->pdev->revision == 0x80) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "amdgpu/hawaii_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "amdgpu/hawaii_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_TOPAZ:
				अगर (((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0x81)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0x83)) ||
				    ((adev->pdev->device == 0x6907) && (adev->pdev->revision == 0x87)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0xD1)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0xD3))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "amdgpu/topaz_k_smc.bin");
				पूर्ण अन्यथा
					म_नकल(fw_name, "amdgpu/topaz_smc.bin");
				अवरोध;
			हाल CHIP_TONGA:
				अगर (((adev->pdev->device == 0x6939) && (adev->pdev->revision == 0xf1)) ||
				    ((adev->pdev->device == 0x6938) && (adev->pdev->revision == 0xf1))) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "amdgpu/tonga_k_smc.bin");
				पूर्ण अन्यथा
					म_नकल(fw_name, "amdgpu/tonga_smc.bin");
				अवरोध;
			हाल CHIP_FIJI:
				म_नकल(fw_name, "amdgpu/fiji_smc.bin");
				अवरोध;
			हाल CHIP_POLARIS11:
				अगर (type == CGS_UCODE_ID_SMU) अणु
					अगर (ASICID_IS_P21(adev->pdev->device, adev->pdev->revision)) अणु
						info->is_kicker = true;
						म_नकल(fw_name, "amdgpu/polaris11_k_smc.bin");
					पूर्ण अन्यथा अगर (ASICID_IS_P31(adev->pdev->device, adev->pdev->revision)) अणु
						info->is_kicker = true;
						म_नकल(fw_name, "amdgpu/polaris11_k2_smc.bin");
					पूर्ण अन्यथा अणु
						म_नकल(fw_name, "amdgpu/polaris11_smc.bin");
					पूर्ण
				पूर्ण अन्यथा अगर (type == CGS_UCODE_ID_SMU_SK) अणु
					म_नकल(fw_name, "amdgpu/polaris11_smc_sk.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_POLARIS10:
				अगर (type == CGS_UCODE_ID_SMU) अणु
					अगर (ASICID_IS_P20(adev->pdev->device, adev->pdev->revision)) अणु
						info->is_kicker = true;
						म_नकल(fw_name, "amdgpu/polaris10_k_smc.bin");
					पूर्ण अन्यथा अगर (ASICID_IS_P30(adev->pdev->device, adev->pdev->revision)) अणु
						info->is_kicker = true;
						म_नकल(fw_name, "amdgpu/polaris10_k2_smc.bin");
					पूर्ण अन्यथा अणु
						म_नकल(fw_name, "amdgpu/polaris10_smc.bin");
					पूर्ण
				पूर्ण अन्यथा अगर (type == CGS_UCODE_ID_SMU_SK) अणु
					म_नकल(fw_name, "amdgpu/polaris10_smc_sk.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_POLARIS12:
				अगर (ASICID_IS_P23(adev->pdev->device, adev->pdev->revision)) अणु
					info->is_kicker = true;
					म_नकल(fw_name, "amdgpu/polaris12_k_smc.bin");
				पूर्ण अन्यथा अणु
					म_नकल(fw_name, "amdgpu/polaris12_smc.bin");
				पूर्ण
				अवरोध;
			हाल CHIP_VEGAM:
				म_नकल(fw_name, "amdgpu/vegam_smc.bin");
				अवरोध;
			हाल CHIP_VEGA10:
				अगर ((adev->pdev->device == 0x687f) &&
					((adev->pdev->revision == 0xc0) ||
					(adev->pdev->revision == 0xc1) ||
					(adev->pdev->revision == 0xc3)))
					म_नकल(fw_name, "amdgpu/vega10_acg_smc.bin");
				अन्यथा
					म_नकल(fw_name, "amdgpu/vega10_smc.bin");
				अवरोध;
			हाल CHIP_VEGA12:
				म_नकल(fw_name, "amdgpu/vega12_smc.bin");
				अवरोध;
			हाल CHIP_VEGA20:
				म_नकल(fw_name, "amdgpu/vega20_smc.bin");
				अवरोध;
			शेष:
				DRM_ERROR("SMC firmware not supported\n");
				वापस -EINVAL;
			पूर्ण

			err = request_firmware(&adev->pm.fw, fw_name, adev->dev);
			अगर (err) अणु
				DRM_ERROR("Failed to request firmware\n");
				वापस err;
			पूर्ण

			err = amdgpu_ucode_validate(adev->pm.fw);
			अगर (err) अणु
				DRM_ERROR("Failed to load firmware \"%s\"", fw_name);
				release_firmware(adev->pm.fw);
				adev->pm.fw = शून्य;
				वापस err;
			पूर्ण

			अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
				ucode = &adev->firmware.ucode[AMDGPU_UCODE_ID_SMC];
				ucode->ucode_id = AMDGPU_UCODE_ID_SMC;
				ucode->fw = adev->pm.fw;
				header = (स्थिर काष्ठा common_firmware_header *)ucode->fw->data;
				adev->firmware.fw_size +=
					ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
			पूर्ण
		पूर्ण

		hdr = (स्थिर काष्ठा smc_firmware_header_v1_0 *)	adev->pm.fw->data;
		amdgpu_ucode_prपूर्णांक_smc_hdr(&hdr->header);
		adev->pm.fw_version = le32_to_cpu(hdr->header.ucode_version);
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
		ucode_start_address = le32_to_cpu(hdr->ucode_start_addr);
		src = (स्थिर uपूर्णांक8_t *)(adev->pm.fw->data +
		       le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		info->version = adev->pm.fw_version;
		info->image_size = ucode_size;
		info->ucode_start_address = ucode_start_address;
		info->kptr = (व्योम *)src;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cgs_ops amdgpu_cgs_ops = अणु
	.पढ़ो_रेजिस्टर = amdgpu_cgs_पढ़ो_रेजिस्टर,
	.ग_लिखो_रेजिस्टर = amdgpu_cgs_ग_लिखो_रेजिस्टर,
	.पढ़ो_ind_रेजिस्टर = amdgpu_cgs_पढ़ो_ind_रेजिस्टर,
	.ग_लिखो_ind_रेजिस्टर = amdgpu_cgs_ग_लिखो_ind_रेजिस्टर,
	.get_firmware_info = amdgpu_cgs_get_firmware_info,
पूर्ण;

काष्ठा cgs_device *amdgpu_cgs_create_device(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_cgs_device *cgs_device =
		kदो_स्मृति(माप(*cgs_device), GFP_KERNEL);

	अगर (!cgs_device) अणु
		DRM_ERROR("Couldn't allocate CGS device structure\n");
		वापस शून्य;
	पूर्ण

	cgs_device->base.ops = &amdgpu_cgs_ops;
	cgs_device->adev = adev;

	वापस (काष्ठा cgs_device *)cgs_device;
पूर्ण

व्योम amdgpu_cgs_destroy_device(काष्ठा cgs_device *cgs_device)
अणु
	kमुक्त(cgs_device);
पूर्ण
