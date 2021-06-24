<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/reboot.h>

#घोषणा SMU_11_0_PARTIAL_PPTABLE
#घोषणा SWSMU_CODE_LAYER_L3

#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "atomfirmware.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_atombios.h"
#समावेश "smu_v11_0.h"
#समावेश "soc15_common.h"
#समावेश "atom.h"
#समावेश "amdgpu_ras.h"
#समावेश "smu_cmn.h"

#समावेश "asic_reg/thm/thm_11_0_2_offset.h"
#समावेश "asic_reg/thm/thm_11_0_2_sh_mask.h"
#समावेश "asic_reg/mp/mp_11_0_offset.h"
#समावेश "asic_reg/mp/mp_11_0_sh_mask.h"
#समावेश "asic_reg/smuio/smuio_11_0_0_offset.h"
#समावेश "asic_reg/smuio/smuio_11_0_0_sh_mask.h"

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

MODULE_FIRMWARE("amdgpu/arcturus_smc.bin");
MODULE_FIRMWARE("amdgpu/navi10_smc.bin");
MODULE_FIRMWARE("amdgpu/navi14_smc.bin");
MODULE_FIRMWARE("amdgpu/navi12_smc.bin");
MODULE_FIRMWARE("amdgpu/sienna_cichlid_smc.bin");
MODULE_FIRMWARE("amdgpu/navy_flounder_smc.bin");
MODULE_FIRMWARE("amdgpu/dimgrey_cavefish_smc.bin");

#घोषणा SMU11_VOLTAGE_SCALE 4

#घोषणा SMU11_MODE1_RESET_WAIT_TIME_IN_MS 500  //500ms

#घोषणा smnPCIE_LC_LINK_WIDTH_CNTL		0x11140288
#घोषणा PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK 0x00000070L
#घोषणा PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT 0x4
#घोषणा smnPCIE_LC_SPEED_CNTL			0x11140290
#घोषणा PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK 0xC000
#घोषणा PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT 0xE

#घोषणा mmTHM_BACO_CNTL_ARCT			0xA7
#घोषणा mmTHM_BACO_CNTL_ARCT_BASE_IDX		0

पूर्णांक smu_v11_0_init_microcode(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[SMU_FW_NAME_LEN];
	पूर्णांक err = 0;
	स्थिर काष्ठा smc_firmware_header_v1_0 *hdr;
	स्थिर काष्ठा common_firmware_header *header;
	काष्ठा amdgpu_firmware_info *ucode = शून्य;

	अगर (amdgpu_sriov_vf(adev) &&
			((adev->asic_type == CHIP_NAVI12) ||
			 (adev->asic_type == CHIP_SIENNA_CICHLID)))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		chip_name = "arcturus";
		अवरोध;
	हाल CHIP_NAVI10:
		chip_name = "navi10";
		अवरोध;
	हाल CHIP_NAVI14:
		chip_name = "navi14";
		अवरोध;
	हाल CHIP_NAVI12:
		chip_name = "navi12";
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		chip_name = "sienna_cichlid";
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		chip_name = "navy_flounder";
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		chip_name = "dimgrey_cavefish";
		अवरोध;
	शेष:
		dev_err(adev->dev, "Unsupported ASIC type %d\n", adev->asic_type);
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_smc.bin", chip_name);

	err = request_firmware(&adev->pm.fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;
	err = amdgpu_ucode_validate(adev->pm.fw);
	अगर (err)
		जाओ out;

	hdr = (स्थिर काष्ठा smc_firmware_header_v1_0 *) adev->pm.fw->data;
	amdgpu_ucode_prपूर्णांक_smc_hdr(&hdr->header);
	adev->pm.fw_version = le32_to_cpu(hdr->header.ucode_version);

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		ucode = &adev->firmware.ucode[AMDGPU_UCODE_ID_SMC];
		ucode->ucode_id = AMDGPU_UCODE_ID_SMC;
		ucode->fw = adev->pm.fw;
		header = (स्थिर काष्ठा common_firmware_header *)ucode->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
	पूर्ण

out:
	अगर (err) अणु
		DRM_ERROR("smu_v11_0: Failed to load firmware \"%s\"\n",
			  fw_name);
		release_firmware(adev->pm.fw);
		adev->pm.fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

व्योम smu_v11_0_fini_microcode(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	release_firmware(adev->pm.fw);
	adev->pm.fw = शून्य;
	adev->pm.fw_version = 0;
पूर्ण

पूर्णांक smu_v11_0_load_microcode(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	स्थिर uपूर्णांक32_t *src;
	स्थिर काष्ठा smc_firmware_header_v1_0 *hdr;
	uपूर्णांक32_t addr_start = MP1_SRAM;
	uपूर्णांक32_t i;
	uपूर्णांक32_t smc_fw_size;
	uपूर्णांक32_t mp1_fw_flags;

	hdr = (स्थिर काष्ठा smc_firmware_header_v1_0 *) adev->pm.fw->data;
	src = (स्थिर uपूर्णांक32_t *)(adev->pm.fw->data +
		le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	smc_fw_size = hdr->header.ucode_size_bytes;

	क्रम (i = 1; i < smc_fw_size/4 - 1; i++) अणु
		WREG32_PCIE(addr_start, src[i]);
		addr_start += 4;
	पूर्ण

	WREG32_PCIE(MP1_Public | (smnMP1_PUB_CTRL & 0xffffffff),
		1 & MP1_SMN_PUB_CTRL__RESET_MASK);
	WREG32_PCIE(MP1_Public | (smnMP1_PUB_CTRL & 0xffffffff),
		1 & ~MP1_SMN_PUB_CTRL__RESET_MASK);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		mp1_fw_flags = RREG32_PCIE(MP1_Public |
			(smnMP1_FIRMWARE_FLAGS & 0xffffffff));
		अगर ((mp1_fw_flags & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK) >>
			MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED__SHIFT)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i == adev->usec_समयout)
		वापस -ETIME;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_check_fw_status(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t mp1_fw_flags;

	mp1_fw_flags = RREG32_PCIE(MP1_Public |
				   (smnMP1_FIRMWARE_FLAGS & 0xffffffff));

	अगर ((mp1_fw_flags & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK) >>
	    MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED__SHIFT)
		वापस 0;

	वापस -EIO;
पूर्ण

पूर्णांक smu_v11_0_check_fw_version(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t अगर_version = 0xff, smu_version = 0xff;
	uपूर्णांक16_t smu_major;
	uपूर्णांक8_t smu_minor, smu_debug;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, &अगर_version, &smu_version);
	अगर (ret)
		वापस ret;

	smu_major = (smu_version >> 16) & 0xffff;
	smu_minor = (smu_version >> 8) & 0xff;
	smu_debug = (smu_version >> 0) & 0xff;
	अगर (smu->is_apu)
		adev->pm.fw_version = smu_version;

	चयन (smu->adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_ARCT;
		अवरोध;
	हाल CHIP_NAVI10:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_NV10;
		अवरोध;
	हाल CHIP_NAVI12:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_NV12;
		अवरोध;
	हाल CHIP_NAVI14:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_NV14;
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_Sienna_Cichlid;
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_Navy_Flounder;
		अवरोध;
	हाल CHIP_VANGOGH:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_VANGOGH;
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_Dimgrey_Cavefish;
		अवरोध;
	शेष:
		dev_err(smu->adev->dev, "smu unsupported asic type:%d.\n", smu->adev->asic_type);
		smu->smc_driver_अगर_version = SMU11_DRIVER_IF_VERSION_INV;
		अवरोध;
	पूर्ण

	/*
	 * 1. अगर_version mismatch is not critical as our fw is deचिन्हित
	 * to be backward compatible.
	 * 2. New fw usually brings some optimizations. But that's visible
	 * only on the paired driver.
	 * Considering above, we just leave user a warning message instead
	 * of halt driver loading.
	 */
	अगर (अगर_version != smu->smc_driver_अगर_version) अणु
		dev_info(smu->adev->dev, "smu driver if version = 0x%08x, smu fw if version = 0x%08x, "
			"smu fw version = 0x%08x (%d.%d.%d)\n",
			smu->smc_driver_अगर_version, अगर_version,
			smu_version, smu_major, smu_minor, smu_debug);
		dev_warn(smu->adev->dev, "SMU driver if version not matched\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_v11_0_set_pptable_v2_0(काष्ठा smu_context *smu, व्योम **table, uपूर्णांक32_t *size)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t ppt_offset_bytes;
	स्थिर काष्ठा smc_firmware_header_v2_0 *v2;

	v2 = (स्थिर काष्ठा smc_firmware_header_v2_0 *) adev->pm.fw->data;

	ppt_offset_bytes = le32_to_cpu(v2->ppt_offset_bytes);
	*size = le32_to_cpu(v2->ppt_size_bytes);
	*table = (uपूर्णांक8_t *)v2 + ppt_offset_bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_v11_0_set_pptable_v2_1(काष्ठा smu_context *smu, व्योम **table,
				      uपूर्णांक32_t *size, uपूर्णांक32_t pptable_id)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	स्थिर काष्ठा smc_firmware_header_v2_1 *v2_1;
	काष्ठा smc_soft_pptable_entry *entries;
	uपूर्णांक32_t pptable_count = 0;
	पूर्णांक i = 0;

	v2_1 = (स्थिर काष्ठा smc_firmware_header_v2_1 *) adev->pm.fw->data;
	entries = (काष्ठा smc_soft_pptable_entry *)
		((uपूर्णांक8_t *)v2_1 + le32_to_cpu(v2_1->pptable_entry_offset));
	pptable_count = le32_to_cpu(v2_1->pptable_count);
	क्रम (i = 0; i < pptable_count; i++) अणु
		अगर (le32_to_cpu(entries[i].id) == pptable_id) अणु
			*table = ((uपूर्णांक8_t *)v2_1 + le32_to_cpu(entries[i].ppt_offset_bytes));
			*size = le32_to_cpu(entries[i].ppt_size_bytes);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == pptable_count)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_setup_pptable(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	स्थिर काष्ठा smc_firmware_header_v1_0 *hdr;
	पूर्णांक ret, index;
	uपूर्णांक32_t size = 0;
	uपूर्णांक16_t atom_table_size;
	uपूर्णांक8_t frev, crev;
	व्योम *table;
	uपूर्णांक16_t version_major, version_minor;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		hdr = (स्थिर काष्ठा smc_firmware_header_v1_0 *) adev->pm.fw->data;
		version_major = le16_to_cpu(hdr->header.header_version_major);
		version_minor = le16_to_cpu(hdr->header.header_version_minor);
		अगर (version_major == 2 && smu->smu_table.boot_values.pp_table_id > 0) अणु
			dev_info(adev->dev, "use driver provided pptable %d\n", smu->smu_table.boot_values.pp_table_id);
			चयन (version_minor) अणु
			हाल 0:
				ret = smu_v11_0_set_pptable_v2_0(smu, &table, &size);
				अवरोध;
			हाल 1:
				ret = smu_v11_0_set_pptable_v2_1(smu, &table, &size,
								smu->smu_table.boot_values.pp_table_id);
				अवरोध;
			शेष:
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (ret)
				वापस ret;
			जाओ out;
		पूर्ण
	पूर्ण

	dev_info(adev->dev, "use vbios provided pptable\n");
	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
						घातerplayinfo);

	ret = amdgpu_atombios_get_data_table(adev, index, &atom_table_size, &frev, &crev,
						(uपूर्णांक8_t **)&table);
	अगर (ret)
		वापस ret;
	size = atom_table_size;

out:
	अगर (!smu->smu_table.घातer_play_table)
		smu->smu_table.घातer_play_table = table;
	अगर (!smu->smu_table.घातer_play_table_size)
		smu->smu_table.घातer_play_table_size = size;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_init_smc_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;
	पूर्णांक ret = 0;

	smu_table->driver_pptable =
		kzalloc(tables[SMU_TABLE_PPTABLE].size, GFP_KERNEL);
	अगर (!smu_table->driver_pptable) अणु
		ret = -ENOMEM;
		जाओ err0_out;
	पूर्ण

	smu_table->max_sustainable_घड़ीs =
		kzalloc(माप(काष्ठा smu_11_0_max_sustainable_घड़ीs), GFP_KERNEL);
	अगर (!smu_table->max_sustainable_घड़ीs) अणु
		ret = -ENOMEM;
		जाओ err1_out;
	पूर्ण

	/* Arcturus करोes not support OVERDRIVE */
	अगर (tables[SMU_TABLE_OVERDRIVE].size) अणु
		smu_table->overdrive_table =
			kzalloc(tables[SMU_TABLE_OVERDRIVE].size, GFP_KERNEL);
		अगर (!smu_table->overdrive_table) अणु
			ret = -ENOMEM;
			जाओ err2_out;
		पूर्ण

		smu_table->boot_overdrive_table =
			kzalloc(tables[SMU_TABLE_OVERDRIVE].size, GFP_KERNEL);
		अगर (!smu_table->boot_overdrive_table) अणु
			ret = -ENOMEM;
			जाओ err3_out;
		पूर्ण
	पूर्ण

	वापस 0;

err3_out:
	kमुक्त(smu_table->overdrive_table);
err2_out:
	kमुक्त(smu_table->max_sustainable_घड़ीs);
err1_out:
	kमुक्त(smu_table->driver_pptable);
err0_out:
	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_fini_smc_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	kमुक्त(smu_table->gpu_metrics_table);
	kमुक्त(smu_table->boot_overdrive_table);
	kमुक्त(smu_table->overdrive_table);
	kमुक्त(smu_table->max_sustainable_घड़ीs);
	kमुक्त(smu_table->driver_pptable);
	kमुक्त(smu_table->घड़ीs_table);
	smu_table->gpu_metrics_table = शून्य;
	smu_table->boot_overdrive_table = शून्य;
	smu_table->overdrive_table = शून्य;
	smu_table->max_sustainable_घड़ीs = शून्य;
	smu_table->driver_pptable = शून्य;
	smu_table->घड़ीs_table = शून्य;
	kमुक्त(smu_table->hardcode_pptable);
	smu_table->hardcode_pptable = शून्य;

	kमुक्त(smu_table->metrics_table);
	kमुक्त(smu_table->watermarks_table);
	smu_table->metrics_table = शून्य;
	smu_table->watermarks_table = शून्य;
	smu_table->metrics_समय = 0;

	kमुक्त(smu_dpm->dpm_context);
	kमुक्त(smu_dpm->golden_dpm_context);
	kमुक्त(smu_dpm->dpm_current_घातer_state);
	kमुक्त(smu_dpm->dpm_request_घातer_state);
	smu_dpm->dpm_context = शून्य;
	smu_dpm->golden_dpm_context = शून्य;
	smu_dpm->dpm_context_size = 0;
	smu_dpm->dpm_current_घातer_state = शून्य;
	smu_dpm->dpm_request_घातer_state = शून्य;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_init_घातer(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	माप_प्रकार size = smu->adev->asic_type == CHIP_VANGOGH ?
			माप(काष्ठा smu_11_5_घातer_context) :
			माप(काष्ठा smu_11_0_घातer_context);

	smu_घातer->घातer_context = kzalloc(size, GFP_KERNEL);
	अगर (!smu_घातer->घातer_context)
		वापस -ENOMEM;
	smu_घातer->घातer_context_size = size;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_fini_घातer(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;

	kमुक्त(smu_घातer->घातer_context);
	smu_घातer->घातer_context = शून्य;
	smu_घातer->घातer_context_size = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_v11_0_atom_get_smu_घड़ीinfo(काष्ठा amdgpu_device *adev,
					    uपूर्णांक8_t clk_id,
					    uपूर्णांक8_t syspll_id,
					    uपूर्णांक32_t *clk_freq)
अणु
	काष्ठा atom_get_smu_घड़ी_info_parameters_v3_1 input = अणु0पूर्ण;
	काष्ठा atom_get_smu_घड़ी_info_output_parameters_v3_1 *output;
	पूर्णांक ret, index;

	input.clk_id = clk_id;
	input.syspll_id = syspll_id;
	input.command = GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ;
	index = get_index_पूर्णांकo_master_table(atom_master_list_of_command_functions_v2_1,
					    माला_लोmuघड़ीinfo);

	ret = amdgpu_atom_execute_table(adev->mode_info.atom_context, index,
					(uपूर्णांक32_t *)&input);
	अगर (ret)
		वापस -EINVAL;

	output = (काष्ठा atom_get_smu_घड़ी_info_output_parameters_v3_1 *)&input;
	*clk_freq = le32_to_cpu(output->atom_smu_outअ_दोlkfreq.smu_घड़ी_freq_hz) / 10000;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_get_vbios_bootup_values(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret, index;
	uपूर्णांक16_t size;
	uपूर्णांक8_t frev, crev;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_firmware_info_v3_3 *v_3_3;
	काष्ठा atom_firmware_info_v3_1 *v_3_1;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);

	ret = amdgpu_atombios_get_data_table(smu->adev, index, &size, &frev, &crev,
				      (uपूर्णांक8_t **)&header);
	अगर (ret)
		वापस ret;

	अगर (header->क्रमmat_revision != 3) अणु
		dev_err(smu->adev->dev, "unknown atom_firmware_info version! for smu11\n");
		वापस -EINVAL;
	पूर्ण

	चयन (header->content_revision) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		v_3_1 = (काष्ठा atom_firmware_info_v3_1 *)header;
		smu->smu_table.boot_values.revision = v_3_1->firmware_revision;
		smu->smu_table.boot_values.gfxclk = v_3_1->bootup_sclk_in10khz;
		smu->smu_table.boot_values.uclk = v_3_1->bootup_mclk_in10khz;
		smu->smu_table.boot_values.socclk = 0;
		smu->smu_table.boot_values.dcefclk = 0;
		smu->smu_table.boot_values.vddc = v_3_1->bootup_vddc_mv;
		smu->smu_table.boot_values.vddci = v_3_1->bootup_vddci_mv;
		smu->smu_table.boot_values.mvddc = v_3_1->bootup_mvddc_mv;
		smu->smu_table.boot_values.vdd_gfx = v_3_1->bootup_vddgfx_mv;
		smu->smu_table.boot_values.cooling_id = v_3_1->coolingsolution_id;
		smu->smu_table.boot_values.pp_table_id = 0;
		smu->smu_table.boot_values.firmware_caps = v_3_1->firmware_capability;
		अवरोध;
	हाल 3:
	हाल 4:
	शेष:
		v_3_3 = (काष्ठा atom_firmware_info_v3_3 *)header;
		smu->smu_table.boot_values.revision = v_3_3->firmware_revision;
		smu->smu_table.boot_values.gfxclk = v_3_3->bootup_sclk_in10khz;
		smu->smu_table.boot_values.uclk = v_3_3->bootup_mclk_in10khz;
		smu->smu_table.boot_values.socclk = 0;
		smu->smu_table.boot_values.dcefclk = 0;
		smu->smu_table.boot_values.vddc = v_3_3->bootup_vddc_mv;
		smu->smu_table.boot_values.vddci = v_3_3->bootup_vddci_mv;
		smu->smu_table.boot_values.mvddc = v_3_3->bootup_mvddc_mv;
		smu->smu_table.boot_values.vdd_gfx = v_3_3->bootup_vddgfx_mv;
		smu->smu_table.boot_values.cooling_id = v_3_3->coolingsolution_id;
		smu->smu_table.boot_values.pp_table_id = v_3_3->pplib_pptable_id;
		smu->smu_table.boot_values.firmware_caps = v_3_3->firmware_capability;
	पूर्ण

	smu->smu_table.boot_values.क्रमmat_revision = header->क्रमmat_revision;
	smu->smu_table.boot_values.content_revision = header->content_revision;

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL0_SOCCLK_ID,
					 (uपूर्णांक8_t)0,
					 &smu->smu_table.boot_values.socclk);

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL0_DCEFCLK_ID,
					 (uपूर्णांक8_t)0,
					 &smu->smu_table.boot_values.dcefclk);

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL0_ECLK_ID,
					 (uपूर्णांक8_t)0,
					 &smu->smu_table.boot_values.eclk);

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL0_VCLK_ID,
					 (uपूर्णांक8_t)0,
					 &smu->smu_table.boot_values.vclk);

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL0_DCLK_ID,
					 (uपूर्णांक8_t)0,
					 &smu->smu_table.boot_values.dclk);

	अगर ((smu->smu_table.boot_values.क्रमmat_revision == 3) &&
	    (smu->smu_table.boot_values.content_revision >= 2))
		smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
						 (uपूर्णांक8_t)SMU11_SYSPLL1_0_FCLK_ID,
						 (uपूर्णांक8_t)SMU11_SYSPLL1_2_ID,
						 &smu->smu_table.boot_values.fclk);

	smu_v11_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU11_SYSPLL3_1_LCLK_ID,
					 (uपूर्णांक8_t)SMU11_SYSPLL3_1_ID,
					 &smu->smu_table.boot_values.lclk);

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_notअगरy_memory_pool_location(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *memory_pool = &smu_table->memory_pool;
	पूर्णांक ret = 0;
	uपूर्णांक64_t address;
	uपूर्णांक32_t address_low, address_high;

	अगर (memory_pool->size == 0 || memory_pool->cpu_addr == शून्य)
		वापस ret;

	address = (uपूर्णांकptr_t)memory_pool->cpu_addr;
	address_high = (uपूर्णांक32_t)upper_32_bits(address);
	address_low  = (uपूर्णांक32_t)lower_32_bits(address);

	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_SetSystemVirtualDramAddrHigh,
					  address_high,
					  शून्य);
	अगर (ret)
		वापस ret;
	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_SetSystemVirtualDramAddrLow,
					  address_low,
					  शून्य);
	अगर (ret)
		वापस ret;

	address = memory_pool->mc_address;
	address_high = (uपूर्णांक32_t)upper_32_bits(address);
	address_low  = (uपूर्णांक32_t)lower_32_bits(address);

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_DramLogSetDramAddrHigh,
					  address_high, शून्य);
	अगर (ret)
		वापस ret;
	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_DramLogSetDramAddrLow,
					  address_low, शून्य);
	अगर (ret)
		वापस ret;
	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_DramLogSetDramSize,
					  (uपूर्णांक32_t)memory_pool->size, शून्य);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_min_deep_sleep_dcefclk(काष्ठा smu_context *smu, uपूर्णांक32_t clk)
अणु
	पूर्णांक ret;

	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_SetMinDeepSleepDcefclk, clk, शून्य);
	अगर (ret)
		dev_err(smu->adev->dev, "SMU11 attempt to set divider for DCEFCLK Failed!");

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_driver_table_location(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table *driver_table = &smu->smu_table.driver_table;
	पूर्णांक ret = 0;

	अगर (driver_table->mc_address) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetDriverDramAddrHigh,
				upper_32_bits(driver_table->mc_address),
				शून्य);
		अगर (!ret)
			ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetDriverDramAddrLow,
				lower_32_bits(driver_table->mc_address),
				शून्य);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_tool_table_location(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu_table *tool_table = &smu->smu_table.tables[SMU_TABLE_PMSTATUSLOG];

	अगर (tool_table->mc_address) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetToolsDramAddrHigh,
				upper_32_bits(tool_table->mc_address),
				शून्य);
		अगर (!ret)
			ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetToolsDramAddrLow,
				lower_32_bits(tool_table->mc_address),
				शून्य);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_init_display_count(काष्ठा smu_context *smu, uपूर्णांक32_t count)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	/* Navy_Flounder/Dimgrey_Cavefish करो not support to change
	 * display num currently
	 */
	अगर (adev->asic_type >= CHIP_NAVY_FLOUNDER &&
	    adev->asic_type <= CHIP_DIMGREY_CAVEFISH)
		वापस 0;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_NumOfDisplays,
					       count,
					       शून्य);
पूर्ण


पूर्णांक smu_v11_0_set_allowed_mask(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक ret = 0;
	uपूर्णांक32_t feature_mask[2];

	अगर (biपंचांगap_empty(feature->allowed, SMU_FEATURE_MAX) || feature->feature_num < 64) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	biपंचांगap_copy((अचिन्हित दीर्घ *)feature_mask, feature->allowed, 64);

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetAllowedFeaturesMaskHigh,
					  feature_mask[1], शून्य);
	अगर (ret)
		जाओ failed;

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetAllowedFeaturesMaskLow,
					  feature_mask[0], शून्य);
	अगर (ret)
		जाओ failed;

failed:
	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_प्रणाली_features_control(काष्ठा smu_context *smu,
					     bool en)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	uपूर्णांक32_t feature_mask[2];
	पूर्णांक ret = 0;

	ret = smu_cmn_send_smc_msg(smu, (en ? SMU_MSG_EnableAllSmuFeatures :
				     SMU_MSG_DisableAllSmuFeatures), शून्य);
	अगर (ret)
		वापस ret;

	biपंचांगap_zero(feature->enabled, feature->feature_num);
	biपंचांगap_zero(feature->supported, feature->feature_num);

	अगर (en) अणु
		ret = smu_cmn_get_enabled_mask(smu, feature_mask, 2);
		अगर (ret)
			वापस ret;

		biपंचांगap_copy(feature->enabled, (अचिन्हित दीर्घ *)&feature_mask,
			    feature->feature_num);
		biपंचांगap_copy(feature->supported, (अचिन्हित दीर्घ *)&feature_mask,
			    feature->feature_num);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_notअगरy_display_change(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT) &&
	    smu->adev->gmc.vram_type == AMDGPU_VRAM_TYPE_HBM)
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetUclkFastSwitch, 1, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक
smu_v11_0_get_max_sustainable_घड़ी(काष्ठा smu_context *smu, uपूर्णांक32_t *घड़ी,
				    क्रमागत smu_clk_type घड़ी_select)
अणु
	पूर्णांक ret = 0;
	पूर्णांक clk_id;

	अगर ((smu_cmn_to_asic_specअगरic_index(smu, CMN2ASIC_MAPPING_MSG, SMU_MSG_GetDcModeMaxDpmFreq) < 0) ||
	    (smu_cmn_to_asic_specअगरic_index(smu, CMN2ASIC_MAPPING_MSG, SMU_MSG_GetMaxDpmFreq) < 0))
		वापस 0;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						घड़ी_select);
	अगर (clk_id < 0)
		वापस -EINVAL;

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetDcModeMaxDpmFreq,
					  clk_id << 16, घड़ी);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "[GetMaxSustainableClock] Failed to get max DC clock from SMC!");
		वापस ret;
	पूर्ण

	अगर (*घड़ी != 0)
		वापस 0;

	/* अगर DC limit is zero, वापस AC limit */
	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetMaxDpmFreq,
					  clk_id << 16, घड़ी);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "[GetMaxSustainableClock] failed to get max AC clock from SMC!");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_init_max_sustainable_घड़ीs(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_max_sustainable_घड़ीs *max_sustainable_घड़ीs =
			smu->smu_table.max_sustainable_घड़ीs;
	पूर्णांक ret = 0;

	max_sustainable_घड़ीs->uघड़ी = smu->smu_table.boot_values.uclk / 100;
	max_sustainable_घड़ीs->soc_घड़ी = smu->smu_table.boot_values.socclk / 100;
	max_sustainable_घड़ीs->dcef_घड़ी = smu->smu_table.boot_values.dcefclk / 100;
	max_sustainable_घड़ीs->display_घड़ी = 0xFFFFFFFF;
	max_sustainable_घड़ीs->phy_घड़ी = 0xFFFFFFFF;
	max_sustainable_घड़ीs->pixel_घड़ी = 0xFFFFFFFF;

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) अणु
		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->uघड़ी),
							  SMU_UCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max UCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) अणु
		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->soc_घड़ी),
							  SMU_SOCCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max SOCCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->dcef_घड़ी),
							  SMU_DCEFCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max DCEFCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण

		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->display_घड़ी),
							  SMU_DISPCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max DISPCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण
		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->phy_घड़ी),
							  SMU_PHYCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max PHYCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण
		ret = smu_v11_0_get_max_sustainable_घड़ी(smu,
							  &(max_sustainable_घड़ीs->pixel_घड़ी),
							  SMU_PIXCLK);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get max PIXCLK from SMC!",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (max_sustainable_घड़ीs->soc_घड़ी < max_sustainable_घड़ीs->uघड़ी)
		max_sustainable_घड़ीs->uघड़ी = max_sustainable_घड़ीs->soc_घड़ी;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_get_current_घातer_limit(काष्ठा smu_context *smu,
				      uपूर्णांक32_t *घातer_limit)
अणु
	पूर्णांक घातer_src;
	पूर्णांक ret = 0;

	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_PPT_BIT))
		वापस -EINVAL;

	घातer_src = smu_cmn_to_asic_specअगरic_index(smu,
					CMN2ASIC_MAPPING_PWR,
					smu->adev->pm.ac_घातer ?
					SMU_POWER_SOURCE_AC :
					SMU_POWER_SOURCE_DC);
	अगर (घातer_src < 0)
		वापस -EINVAL;

	/*
	 * BIT 24-31: ControllerId (only PPT0 is supported क्रम now)
	 * BIT 16-23: PowerSource
	 */
	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_GetPptLimit,
					  (0 << 24) | (घातer_src << 16),
					  घातer_limit);
	अगर (ret)
		dev_err(smu->adev->dev, "[%s] get PPT limit failed!", __func__);

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_घातer_limit(काष्ठा smu_context *smu, uपूर्णांक32_t n)
अणु
	पूर्णांक घातer_src;
	पूर्णांक ret = 0;

	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_PPT_BIT)) अणु
		dev_err(smu->adev->dev, "Setting new power limit is not supported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	घातer_src = smu_cmn_to_asic_specअगरic_index(smu,
					CMN2ASIC_MAPPING_PWR,
					smu->adev->pm.ac_घातer ?
					SMU_POWER_SOURCE_AC :
					SMU_POWER_SOURCE_DC);
	अगर (घातer_src < 0)
		वापस -EINVAL;

	/*
	 * BIT 24-31: ControllerId (only PPT0 is supported क्रम now)
	 * BIT 16-23: PowerSource
	 * BIT 0-15: PowerLimit
	 */
	n &= 0xFFFF;
	n |= 0 << 24;
	n |= (घातer_src) << 16;
	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetPptLimit, n, शून्य);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "[%s] Set power limit Failed!\n", __func__);
		वापस ret;
	पूर्ण

	smu->current_घातer_limit = n;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_v11_0_ack_ac_dc_पूर्णांकerrupt(काष्ठा smu_context *smu)
अणु
	वापस smu_cmn_send_smc_msg(smu,
				SMU_MSG_ReenableAcDcInterrupt,
				शून्य);
पूर्ण

अटल पूर्णांक smu_v11_0_process_pending_पूर्णांकerrupt(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (smu->dc_controlled_by_gpio &&
	    smu_cmn_feature_is_enabled(smu, SMU_FEATURE_ACDC_BIT))
		ret = smu_v11_0_ack_ac_dc_पूर्णांकerrupt(smu);

	वापस ret;
पूर्ण

व्योम smu_v11_0_पूर्णांकerrupt_work(काष्ठा smu_context *smu)
अणु
	अगर (smu_v11_0_ack_ac_dc_पूर्णांकerrupt(smu))
		dev_err(smu->adev->dev, "Ack AC/DC interrupt Failed!\n");
पूर्ण

पूर्णांक smu_v11_0_enable_thermal_alert(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (smu->smu_table.thermal_controller_type) अणु
		ret = amdgpu_irq_get(smu->adev, &smu->irq_source, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * After init there might have been missed पूर्णांकerrupts triggered
	 * beक्रमe driver रेजिस्टरs क्रम पूर्णांकerrupt (Ex. AC/DC).
	 */
	वापस smu_v11_0_process_pending_पूर्णांकerrupt(smu);
पूर्ण

पूर्णांक smu_v11_0_disable_thermal_alert(काष्ठा smu_context *smu)
अणु
	वापस amdgpu_irq_put(smu->adev, &smu->irq_source, 0);
पूर्ण

अटल uपूर्णांक16_t convert_to_vddc(uपूर्णांक8_t vid)
अणु
	वापस (uपूर्णांक16_t) ((6200 - (vid * 25)) / SMU11_VOLTAGE_SCALE);
पूर्ण

पूर्णांक smu_v11_0_get_gfx_vdd(काष्ठा smu_context *smu, uपूर्णांक32_t *value)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t vdd = 0, val_vid = 0;

	अगर (!value)
		वापस -EINVAL;
	val_vid = (RREG32_SOC15(SMUIO, 0, mmSMUSVI0_TEL_PLANE0) &
		SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR_MASK) >>
		SMUSVI0_TEL_PLANE0__SVI0_PLANE0_VDDCOR__SHIFT;

	vdd = (uपूर्णांक32_t)convert_to_vddc((uपूर्णांक8_t)val_vid);

	*value = vdd;

	वापस 0;

पूर्ण

पूर्णांक
smu_v11_0_display_घड़ी_voltage_request(काष्ठा smu_context *smu,
					काष्ठा pp_display_घड़ी_request
					*घड़ी_req)
अणु
	क्रमागत amd_pp_घड़ी_प्रकारype clk_type = घड़ी_req->घड़ी_प्रकारype;
	पूर्णांक ret = 0;
	क्रमागत smu_clk_type clk_select = 0;
	uपूर्णांक32_t clk_freq = घड़ी_req->घड़ी_freq_in_khz / 1000;

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT) ||
		smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) अणु
		चयन (clk_type) अणु
		हाल amd_pp_dcef_घड़ी:
			clk_select = SMU_DCEFCLK;
			अवरोध;
		हाल amd_pp_disp_घड़ी:
			clk_select = SMU_DISPCLK;
			अवरोध;
		हाल amd_pp_pixel_घड़ी:
			clk_select = SMU_PIXCLK;
			अवरोध;
		हाल amd_pp_phy_घड़ी:
			clk_select = SMU_PHYCLK;
			अवरोध;
		हाल amd_pp_mem_घड़ी:
			clk_select = SMU_UCLK;
			अवरोध;
		शेष:
			dev_info(smu->adev->dev, "[%s] Invalid Clock Type!", __func__);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (ret)
			जाओ failed;

		अगर (clk_select == SMU_UCLK && smu->disable_uclk_चयन)
			वापस 0;

		ret = smu_v11_0_set_hard_freq_limited_range(smu, clk_select, clk_freq, 0);

		अगर(clk_select == SMU_UCLK)
			smu->hard_min_uclk_req_from_dal = clk_freq;
	पूर्ण

failed:
	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_gfx_off_control(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;
	काष्ठा amdgpu_device *adev = smu->adev;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
		अगर (!(adev->pm.pp_feature & PP_GFXOFF_MASK))
			वापस 0;
		अगर (enable)
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_AllowGfxOff, शून्य);
		अन्यथा
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_DisallowGfxOff, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

uपूर्णांक32_t
smu_v11_0_get_fan_control_mode(काष्ठा smu_context *smu)
अणु
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_FAN_CONTROL_BIT))
		वापस AMD_FAN_CTRL_AUTO;
	अन्यथा
		वापस smu->user_dpm_profile.fan_mode;
पूर्ण

अटल पूर्णांक
smu_v11_0_स्वतः_fan_control(काष्ठा smu_context *smu, bool स्वतः_fan_control)
अणु
	पूर्णांक ret = 0;

	अगर (!smu_cmn_feature_is_supported(smu, SMU_FEATURE_FAN_CONTROL_BIT))
		वापस 0;

	ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_FAN_CONTROL_BIT, स्वतः_fan_control);
	अगर (ret)
		dev_err(smu->adev->dev, "[%s]%s smc FAN CONTROL feature failed!",
		       __func__, (स्वतः_fan_control ? "Start" : "Stop"));

	वापस ret;
पूर्ण

अटल पूर्णांक
smu_v11_0_set_fan_अटल_mode(काष्ठा smu_context *smu, uपूर्णांक32_t mode)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
		     REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				   CG_FDO_CTRL2, TMIN, 0));
	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
		     REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				   CG_FDO_CTRL2, FDO_PWM_MODE, mode));

	वापस 0;
पूर्ण

पूर्णांक
smu_v11_0_set_fan_speed_percent(काष्ठा smu_context *smu, uपूर्णांक32_t speed)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t duty100, duty;
	uपूर्णांक64_t पंचांगp64;

	अगर (speed > 100)
		speed = 100;

	अगर (smu_v11_0_स्वतः_fan_control(smu, 0))
		वापस -EINVAL;

	duty100 = REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL1),
				CG_FDO_CTRL1, FMAX_DUTY100);
	अगर (!duty100)
		वापस -EINVAL;

	पंचांगp64 = (uपूर्णांक64_t)speed * duty100;
	करो_भाग(पंचांगp64, 100);
	duty = (uपूर्णांक32_t)पंचांगp64;

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL0,
		     REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL0),
				   CG_FDO_CTRL0, FDO_STATIC_DUTY, duty));

	वापस smu_v11_0_set_fan_अटल_mode(smu, FDO_PWM_MODE_STATIC);
पूर्ण

पूर्णांक
smu_v11_0_set_fan_control_mode(काष्ठा smu_context *smu,
			       uपूर्णांक32_t mode)
अणु
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल AMD_FAN_CTRL_NONE:
		ret = smu_v11_0_set_fan_speed_percent(smu, 100);
		अवरोध;
	हाल AMD_FAN_CTRL_MANUAL:
		ret = smu_v11_0_स्वतः_fan_control(smu, 0);
		अवरोध;
	हाल AMD_FAN_CTRL_AUTO:
		ret = smu_v11_0_स्वतः_fan_control(smu, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		dev_err(smu->adev->dev, "[%s]Set fan control mode failed!", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_xgmi_pstate(काष्ठा smu_context *smu,
				     uपूर्णांक32_t pstate)
अणु
	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_SetXgmiMode,
					       pstate ? XGMI_MODE_PSTATE_D0 : XGMI_MODE_PSTATE_D3,
					  शून्य);
पूर्ण

अटल पूर्णांक smu_v11_0_set_irq_state(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_irq_src *source,
				   अचिन्हित tyep,
				   क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	काष्ठा smu_context *smu = &adev->smu;
	uपूर्णांक32_t low, high;
	uपूर्णांक32_t val = 0;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		/* For THM irqs */
		val = RREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_INTH_MASK, 1);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_INTL_MASK, 1);
		WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL, val);

		WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, 0);

		/* For MP1 SW irqs */
		val = RREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL);
		val = REG_SET_FIELD(val, MP1_SMN_IH_SW_INT_CTRL, INT_MASK, 1);
		WREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL, val);

		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		/* For THM irqs */
		low = max(SMU_THERMAL_MINIMUM_ALERT_TEMP,
				smu->thermal_range.min / SMU_TEMPERATURE_UNITS_PER_CENTIGRADES);
		high = min(SMU_THERMAL_MAXIMUM_ALERT_TEMP,
				smu->thermal_range.software_shutकरोwn_temp);

		val = RREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, MAX_IH_CREDIT, 5);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_IH_HW_ENA, 1);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_INTH_MASK, 0);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_INTL_MASK, 0);
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTH, (high & 0xff));
		val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTL, (low & 0xff));
		val = val & (~THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK);
		WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL, val);

		val = (1 << THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT);
		val |= (1 << THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT);
		val |= (1 << THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT);
		WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, val);

		/* For MP1 SW irqs */
		val = RREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT);
		val = REG_SET_FIELD(val, MP1_SMN_IH_SW_INT, ID, 0xFE);
		val = REG_SET_FIELD(val, MP1_SMN_IH_SW_INT, VALID, 0);
		WREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT, val);

		val = RREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL);
		val = REG_SET_FIELD(val, MP1_SMN_IH_SW_INT_CTRL, INT_MASK, 0);
		WREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL, val);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा THM_11_0__SRCID__THM_DIG_THERM_L2H		0		/* ASIC_TEMP > CG_THERMAL_INT.DIG_THERM_INTH  */
#घोषणा THM_11_0__SRCID__THM_DIG_THERM_H2L		1		/* ASIC_TEMP < CG_THERMAL_INT.DIG_THERM_INTL  */

#घोषणा SMUIO_11_0__SRCID__SMUIO_GPIO19			83

अटल पूर्णांक smu_v11_0_irq_process(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_irq_src *source,
				 काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा smu_context *smu = &adev->smu;
	uपूर्णांक32_t client_id = entry->client_id;
	uपूर्णांक32_t src_id = entry->src_id;
	/*
	 * ctxid is used to distinguish dअगरferent
	 * events क्रम SMCToHost पूर्णांकerrupt.
	 */
	uपूर्णांक32_t ctxid = entry->src_data[0];
	uपूर्णांक32_t data;

	अगर (client_id == SOC15_IH_CLIENTID_THM) अणु
		चयन (src_id) अणु
		हाल THM_11_0__SRCID__THM_DIG_THERM_L2H:
			dev_emerg(adev->dev, "ERROR: GPU over temperature range(SW CTF) detected!\n");
			/*
			 * SW CTF just occurred.
			 * Try to करो a graceful shutकरोwn to prevent further damage.
			 */
			dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU SW CTF!\n");
			orderly_घातeroff(true);
		अवरोध;
		हाल THM_11_0__SRCID__THM_DIG_THERM_H2L:
			dev_emerg(adev->dev, "ERROR: GPU under temperature range detected\n");
		अवरोध;
		शेष:
			dev_emerg(adev->dev, "ERROR: GPU under temperature range unknown src id (%d)\n",
				src_id);
		अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_ROM_SMUIO) अणु
		dev_emerg(adev->dev, "ERROR: GPU HW Critical Temperature Fault(aka CTF) detected!\n");
		/*
		 * HW CTF just occurred. Shutकरोwn to prevent further damage.
		 */
		dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU HW CTF!\n");
		orderly_घातeroff(true);
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_MP1) अणु
		अगर (src_id == 0xfe) अणु
			/* ACK SMUToHost पूर्णांकerrupt */
			data = RREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL);
			data = REG_SET_FIELD(data, MP1_SMN_IH_SW_INT_CTRL, INT_ACK, 1);
			WREG32_SOC15(MP1, 0, mmMP1_SMN_IH_SW_INT_CTRL, data);

			चयन (ctxid) अणु
			हाल 0x3:
				dev_dbg(adev->dev, "Switched to AC mode!\n");
				schedule_work(&smu->पूर्णांकerrupt_work);
				अवरोध;
			हाल 0x4:
				dev_dbg(adev->dev, "Switched to DC mode!\n");
				schedule_work(&smu->पूर्णांकerrupt_work);
				अवरोध;
			हाल 0x7:
				/*
				 * Increment the throttle पूर्णांकerrupt counter
				 */
				atomic64_inc(&smu->throttle_पूर्णांक_counter);

				अगर (!atomic_पढ़ो(&adev->throttling_logging_enabled))
					वापस 0;

				अगर (__ratelimit(&adev->throttling_logging_rs))
					schedule_work(&smu->throttling_logging_work);

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs smu_v11_0_irq_funcs =
अणु
	.set = smu_v11_0_set_irq_state,
	.process = smu_v11_0_irq_process,
पूर्ण;

पूर्णांक smu_v11_0_रेजिस्टर_irq_handler(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा amdgpu_irq_src *irq_src = &smu->irq_source;
	पूर्णांक ret = 0;

	irq_src->num_types = 1;
	irq_src->funcs = &smu_v11_0_irq_funcs;

	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_THM,
				THM_11_0__SRCID__THM_DIG_THERM_L2H,
				irq_src);
	अगर (ret)
		वापस ret;

	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_THM,
				THM_11_0__SRCID__THM_DIG_THERM_H2L,
				irq_src);
	अगर (ret)
		वापस ret;

	/* Register CTF(GPIO_19) पूर्णांकerrupt */
	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_ROM_SMUIO,
				SMUIO_11_0__SRCID__SMUIO_GPIO19,
				irq_src);
	अगर (ret)
		वापस ret;

	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_MP1,
				0xfe,
				irq_src);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_get_max_sustainable_घड़ीs_by_dc(काष्ठा smu_context *smu,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_max_sustainable_घड़ीs *sustainable_घड़ीs = शून्य;

	अगर (!max_घड़ीs || !table_context->max_sustainable_घड़ीs)
		वापस -EINVAL;

	sustainable_घड़ीs = table_context->max_sustainable_घड़ीs;

	max_घड़ीs->dcfClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->dcef_घड़ी * 1000;
	max_घड़ीs->displayClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->display_घड़ी * 1000;
	max_घड़ीs->phyClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->phy_घड़ी * 1000;
	max_घड़ीs->pixelClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->pixel_घड़ी * 1000;
	max_घड़ीs->uClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->uघड़ी * 1000;
	max_घड़ीs->socClockInKhz =
			(अचिन्हित पूर्णांक) sustainable_घड़ीs->soc_घड़ी * 1000;
	max_घड़ीs->dscClockInKhz = 0;
	max_घड़ीs->dppClockInKhz = 0;
	max_घड़ीs->fabricClockInKhz = 0;

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_set_azalia_d3_pme(काष्ठा smu_context *smu)
अणु
	वापस smu_cmn_send_smc_msg(smu, SMU_MSG_BacoAudioD3PME, शून्य);
पूर्ण

अटल पूर्णांक smu_v11_0_baco_set_armd3_sequence(काष्ठा smu_context *smu, क्रमागत smu_v11_0_baco_seq baco_seq)
अणु
	वापस smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_ArmD3, baco_seq, शून्य);
पूर्ण

bool smu_v11_0_baco_is_support(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;

	अगर (!smu_baco->platक्रमm_support)
		वापस false;

	/* Arcturus करोes not support this bit mask */
	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_BACO_BIT) &&
	   !smu_cmn_feature_is_enabled(smu, SMU_FEATURE_BACO_BIT))
		वापस false;

	वापस true;
पूर्ण

क्रमागत smu_baco_state smu_v11_0_baco_get_state(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;
	क्रमागत smu_baco_state baco_state;

	mutex_lock(&smu_baco->mutex);
	baco_state = smu_baco->state;
	mutex_unlock(&smu_baco->mutex);

	वापस baco_state;
पूर्ण

#घोषणा D3HOT_BACO_SEQUENCE 0
#घोषणा D3HOT_BAMACO_SEQUENCE 2

पूर्णांक smu_v11_0_baco_set_state(काष्ठा smu_context *smu, क्रमागत smu_baco_state state)
अणु
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);
	uपूर्णांक32_t data;
	पूर्णांक ret = 0;

	अगर (smu_v11_0_baco_get_state(smu) == state)
		वापस 0;

	mutex_lock(&smu_baco->mutex);

	अगर (state == SMU_BACO_STATE_ENTER) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_SIENNA_CICHLID:
		हाल CHIP_NAVY_FLOUNDER:
		हाल CHIP_DIMGREY_CAVEFISH:
			अगर (amdgpu_runसमय_pm == 2)
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_EnterBaco,
								      D3HOT_BAMACO_SEQUENCE,
								      शून्य);
			अन्यथा
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_EnterBaco,
								      D3HOT_BACO_SEQUENCE,
								      शून्य);
			अवरोध;
		शेष:
			अगर (!ras || !ras->supported || adev->gmc.xgmi.pending_reset) अणु
				अगर (adev->asic_type == CHIP_ARCTURUS) अणु
					data = RREG32_SOC15(THM, 0, mmTHM_BACO_CNTL_ARCT);
					data |= 0x80000000;
					WREG32_SOC15(THM, 0, mmTHM_BACO_CNTL_ARCT, data);
				पूर्ण अन्यथा अणु
					data = RREG32_SOC15(THM, 0, mmTHM_BACO_CNTL);
					data |= 0x80000000;
					WREG32_SOC15(THM, 0, mmTHM_BACO_CNTL, data);
				पूर्ण

				ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_EnterBaco, 0, शून्य);
			पूर्ण अन्यथा अणु
				ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_EnterBaco, 1, शून्य);
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_ExitBaco, शून्य);
		अगर (ret)
			जाओ out;

		/* clear vbios scratch 6 and 7 क्रम coming asic reinit */
		WREG32(adev->bios_scratch_reg_offset + 6, 0);
		WREG32(adev->bios_scratch_reg_offset + 7, 0);
	पूर्ण
	अगर (ret)
		जाओ out;

	smu_baco->state = state;
out:
	mutex_unlock(&smu_baco->mutex);
	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_baco_enter(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	/* Arcturus करोes not need this audio workaround */
	अगर (adev->asic_type != CHIP_ARCTURUS) अणु
		ret = smu_v11_0_baco_set_armd3_sequence(smu, BACO_SEQ_BACO);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_ENTER);
	अगर (ret)
		वापस ret;

	msleep(10);

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_baco_निकास(काष्ठा smu_context *smu)
अणु
	वापस smu_v11_0_baco_set_state(smu, SMU_BACO_STATE_EXIT);
पूर्ण

पूर्णांक smu_v11_0_mode1_reset(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_Mode1Reset, शून्य);
	अगर (!ret)
		msleep(SMU11_MODE1_RESET_WAIT_TIME_IN_MS);

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_light_sbr(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	ret =  smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_LightSBR, enable ? 1 : 0, शून्य);

	वापस ret;
पूर्ण


पूर्णांक smu_v11_0_get_dpm_ultimate_freq(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
						 uपूर्णांक32_t *min, uपूर्णांक32_t *max)
अणु
	पूर्णांक ret = 0, clk_id = 0;
	uपूर्णांक32_t param = 0;
	uपूर्णांक32_t घड़ी_limit;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type)) अणु
		चयन (clk_type) अणु
		हाल SMU_MCLK:
		हाल SMU_UCLK:
			घड़ी_limit = smu->smu_table.boot_values.uclk;
			अवरोध;
		हाल SMU_GFXCLK:
		हाल SMU_SCLK:
			घड़ी_limit = smu->smu_table.boot_values.gfxclk;
			अवरोध;
		हाल SMU_SOCCLK:
			घड़ी_limit = smu->smu_table.boot_values.socclk;
			अवरोध;
		शेष:
			घड़ी_limit = 0;
			अवरोध;
		पूर्ण

		/* घड़ी in Mhz unit */
		अगर (min)
			*min = घड़ी_limit / 100;
		अगर (max)
			*max = घड़ी_limit / 100;

		वापस 0;
	पूर्ण

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण
	param = (clk_id & 0xffff) << 16;

	अगर (max) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetMaxDpmFreq, param, max);
		अगर (ret)
			जाओ failed;
	पूर्ण

	अगर (min) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetMinDpmFreq, param, min);
		अगर (ret)
			जाओ failed;
	पूर्ण

failed:
	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_soft_freq_limited_range(काष्ठा smu_context *smu,
					  क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min,
					  uपूर्णांक32_t max)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0, clk_id = 0;
	uपूर्णांक32_t param;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type))
		वापस 0;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0)
		वापस clk_id;

	अगर (clk_type == SMU_GFXCLK)
		amdgpu_gfx_off_ctrl(adev, false);

	अगर (max > 0) अणु
		param = (uपूर्णांक32_t)((clk_id << 16) | (max & 0xffff));
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxByFreq,
						  param, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (min > 0) अणु
		param = (uपूर्णांक32_t)((clk_id << 16) | (min & 0xffff));
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMinByFreq,
						  param, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	अगर (clk_type == SMU_GFXCLK)
		amdgpu_gfx_off_ctrl(adev, true);

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_hard_freq_limited_range(काष्ठा smu_context *smu,
					  क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min,
					  uपूर्णांक32_t max)
अणु
	पूर्णांक ret = 0, clk_id = 0;
	uपूर्णांक32_t param;

	अगर (min <= 0 && max <= 0)
		वापस -EINVAL;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type))
		वापस 0;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0)
		वापस clk_id;

	अगर (max > 0) अणु
		param = (uपूर्णांक32_t)((clk_id << 16) | (max & 0xffff));
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMaxByFreq,
						  param, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (min > 0) अणु
		param = (uपूर्णांक32_t)((clk_id << 16) | (min & 0xffff));
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinByFreq,
						  param, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_perक्रमmance_level(काष्ठा smu_context *smu,
				    क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context =
				smu->smu_dpm.dpm_context;
	काष्ठा smu_11_0_dpm_table *gfx_table =
				&dpm_context->dpm_tables.gfx_table;
	काष्ठा smu_11_0_dpm_table *mem_table =
				&dpm_context->dpm_tables.uclk_table;
	काष्ठा smu_11_0_dpm_table *soc_table =
				&dpm_context->dpm_tables.soc_table;
	काष्ठा smu_umd_pstate_table *pstate_table =
				&smu->pstate_table;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t sclk_min = 0, sclk_max = 0;
	uपूर्णांक32_t mclk_min = 0, mclk_max = 0;
	uपूर्णांक32_t socclk_min = 0, socclk_max = 0;
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		sclk_min = sclk_max = gfx_table->max;
		mclk_min = mclk_max = mem_table->max;
		socclk_min = socclk_max = soc_table->max;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		sclk_min = sclk_max = gfx_table->min;
		mclk_min = mclk_max = mem_table->min;
		socclk_min = socclk_max = soc_table->min;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		sclk_min = gfx_table->min;
		sclk_max = gfx_table->max;
		mclk_min = mem_table->min;
		mclk_max = mem_table->max;
		socclk_min = soc_table->min;
		socclk_max = soc_table->max;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
		sclk_min = sclk_max = pstate_table->gfxclk_pstate.standard;
		mclk_min = mclk_max = pstate_table->uclk_pstate.standard;
		socclk_min = socclk_max = pstate_table->socclk_pstate.standard;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
		sclk_min = sclk_max = pstate_table->gfxclk_pstate.min;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
		mclk_min = mclk_max = pstate_table->uclk_pstate.min;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		sclk_min = sclk_max = pstate_table->gfxclk_pstate.peak;
		mclk_min = mclk_max = pstate_table->uclk_pstate.peak;
		socclk_min = socclk_max = pstate_table->socclk_pstate.peak;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
		वापस 0;
	शेष:
		dev_err(adev->dev, "Invalid performance level %d\n", level);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Separate MCLK and SOCCLK soft min/max settings are not allowed
	 * on Arcturus.
	 */
	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		mclk_min = mclk_max = 0;
		socclk_min = socclk_max = 0;
	पूर्ण

	अगर (sclk_min && sclk_max) अणु
		ret = smu_v11_0_set_soft_freq_limited_range(smu,
							    SMU_GFXCLK,
							    sclk_min,
							    sclk_max);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mclk_min && mclk_max) अणु
		ret = smu_v11_0_set_soft_freq_limited_range(smu,
							    SMU_MCLK,
							    mclk_min,
							    mclk_max);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (socclk_min && socclk_max) अणु
		ret = smu_v11_0_set_soft_freq_limited_range(smu,
							    SMU_SOCCLK,
							    socclk_min,
							    socclk_max);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_set_घातer_source(काष्ठा smu_context *smu,
			       क्रमागत smu_घातer_src_type घातer_src)
अणु
	पूर्णांक pwr_source;

	pwr_source = smu_cmn_to_asic_specअगरic_index(smu,
						    CMN2ASIC_MAPPING_PWR,
						    (uपूर्णांक32_t)घातer_src);
	अगर (pwr_source < 0)
		वापस -EINVAL;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					SMU_MSG_NotअगरyPowerSource,
					pwr_source,
					शून्य);
पूर्ण

पूर्णांक smu_v11_0_get_dpm_freq_by_index(काष्ठा smu_context *smu,
				    क्रमागत smu_clk_type clk_type,
				    uपूर्णांक16_t level,
				    uपूर्णांक32_t *value)
अणु
	पूर्णांक ret = 0, clk_id = 0;
	uपूर्णांक32_t param;

	अगर (!value)
		वापस -EINVAL;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type))
		वापस 0;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0)
		वापस clk_id;

	param = (uपूर्णांक32_t)(((clk_id & 0xffff) << 16) | (level & 0xffff));

	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_GetDpmFreqByIndex,
					  param,
					  value);
	अगर (ret)
		वापस ret;

	/*
	 * BIT31:  0 - Fine grained DPM, 1 - Dicrete DPM
	 * now, we un-support it
	 */
	*value = *value & 0x7fffffff;

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_get_dpm_level_count(काष्ठा smu_context *smu,
				  क्रमागत smu_clk_type clk_type,
				  uपूर्णांक32_t *value)
अणु
	वापस smu_v11_0_get_dpm_freq_by_index(smu,
					       clk_type,
					       0xff,
					       value);
पूर्ण

पूर्णांक smu_v11_0_set_single_dpm_table(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type,
				   काष्ठा smu_11_0_dpm_table *single_dpm_table)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t clk;
	पूर्णांक i;

	ret = smu_v11_0_get_dpm_level_count(smu,
					    clk_type,
					    &single_dpm_table->count);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "[%s] failed to get dpm levels!\n", __func__);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < single_dpm_table->count; i++) अणु
		ret = smu_v11_0_get_dpm_freq_by_index(smu,
						      clk_type,
						      i,
						      &clk);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] failed to get dpm freq by index!\n", __func__);
			वापस ret;
		पूर्ण

		single_dpm_table->dpm_levels[i].value = clk;
		single_dpm_table->dpm_levels[i].enabled = true;

		अगर (i == 0)
			single_dpm_table->min = clk;
		अन्यथा अगर (i == single_dpm_table->count - 1)
			single_dpm_table->max = clk;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu_v11_0_get_dpm_level_range(काष्ठा smu_context *smu,
				  क्रमागत smu_clk_type clk_type,
				  uपूर्णांक32_t *min_value,
				  uपूर्णांक32_t *max_value)
अणु
	uपूर्णांक32_t level_count = 0;
	पूर्णांक ret = 0;

	अगर (!min_value && !max_value)
		वापस -EINVAL;

	अगर (min_value) अणु
		/* by शेष, level 0 घड़ी value as min value */
		ret = smu_v11_0_get_dpm_freq_by_index(smu,
						      clk_type,
						      0,
						      min_value);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (max_value) अणु
		ret = smu_v11_0_get_dpm_level_count(smu,
						    clk_type,
						    &level_count);
		अगर (ret)
			वापस ret;

		ret = smu_v11_0_get_dpm_freq_by_index(smu,
						      clk_type,
						      level_count - 1,
						      max_value);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_get_current_pcie_link_width_level(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_LINK_WIDTH_CNTL) &
		PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK)
		>> PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;
पूर्ण

uपूर्णांक16_t smu_v11_0_get_current_pcie_link_width(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t width_level;

	width_level = smu_v11_0_get_current_pcie_link_width_level(smu);
	अगर (width_level > LINK_WIDTH_MAX)
		width_level = 0;

	वापस link_width[width_level];
पूर्ण

पूर्णांक smu_v11_0_get_current_pcie_link_speed_level(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	वापस (RREG32_PCIE(smnPCIE_LC_SPEED_CNTL) &
		PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK)
		>> PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
पूर्ण

uपूर्णांक16_t smu_v11_0_get_current_pcie_link_speed(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t speed_level;

	speed_level = smu_v11_0_get_current_pcie_link_speed_level(smu);
	अगर (speed_level > LINK_SPEED_MAX)
		speed_level = 0;

	वापस link_speed[speed_level];
पूर्ण

पूर्णांक smu_v11_0_gfx_ulv_control(काष्ठा smu_context *smu,
			      bool enablement)
अणु
	पूर्णांक ret = 0;

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_GFX_ULV_BIT))
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_GFX_ULV_BIT, enablement);

	वापस ret;
पूर्ण

पूर्णांक smu_v11_0_deep_sleep_control(काष्ठा smu_context *smu,
				 bool enablement)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_GFXCLK_BIT)) अणु
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_DS_GFXCLK_BIT, enablement);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to %s GFXCLK DS!\n", enablement ? "enable" : "disable");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_UCLK_BIT)) अणु
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_DS_UCLK_BIT, enablement);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to %s UCLK DS!\n", enablement ? "enable" : "disable");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_FCLK_BIT)) अणु
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_DS_FCLK_BIT, enablement);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to %s FCLK DS!\n", enablement ? "enable" : "disable");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_SOCCLK_BIT)) अणु
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_DS_SOCCLK_BIT, enablement);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to %s SOCCLK DS!\n", enablement ? "enable" : "disable");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_LCLK_BIT)) अणु
		ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_DS_LCLK_BIT, enablement);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to %s LCLK DS!\n", enablement ? "enable" : "disable");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
