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

#घोषणा SWSMU_CODE_LAYER_L3

#समावेश <linux/firmware.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "atomfirmware.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_atombios.h"
#समावेश "smu_v12_0.h"
#समावेश "soc15_common.h"
#समावेश "atom.h"
#समावेश "smu_cmn.h"

#समावेश "asic_reg/mp/mp_12_0_0_offset.h"
#समावेश "asic_reg/mp/mp_12_0_0_sh_mask.h"
#समावेश "asic_reg/smuio/smuio_12_0_0_offset.h"
#समावेश "asic_reg/smuio/smuio_12_0_0_sh_mask.h"

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

// because some SMU12 based ASICs use older ip offset tables
// we should undefine this रेजिस्टर from the smuio12 header
// to prevent confusion करोwn the road
#अघोषित mmPWR_MISC_CNTL_STATUS

#घोषणा smnMP1_FIRMWARE_FLAGS                                0x3010024

पूर्णांक smu_v12_0_check_fw_status(काष्ठा smu_context *smu)
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

पूर्णांक smu_v12_0_check_fw_version(काष्ठा smu_context *smu)
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

पूर्णांक smu_v12_0_घातergate_sdma(काष्ठा smu_context *smu, bool gate)
अणु
	अगर (!smu->is_apu)
		वापस 0;

	अगर (gate)
		वापस smu_cmn_send_smc_msg(smu, SMU_MSG_PowerDownSdma, शून्य);
	अन्यथा
		वापस smu_cmn_send_smc_msg(smu, SMU_MSG_PowerUpSdma, शून्य);
पूर्ण

पूर्णांक smu_v12_0_set_gfx_cgpg(काष्ठा smu_context *smu, bool enable)
अणु
	अगर (!(smu->adev->pg_flags & AMD_PG_SUPPORT_GFX_PG))
		वापस 0;

	वापस smu_cmn_send_smc_msg_with_param(smu,
		SMU_MSG_SetGfxCGPG,
		enable ? 1 : 0,
		शून्य);
पूर्ण

/**
 * smu_v12_0_get_gfxoff_status - get gfxoff status
 *
 * @smu: amdgpu_device poपूर्णांकer
 *
 * This function will be used to get gfxoff status
 *
 * Returns 0=GFXOFF(शेष).
 * Returns 1=Transition out of GFX State.
 * Returns 2=Not in GFXOFF.
 * Returns 3=Transition पूर्णांकo GFXOFF.
 */
uपूर्णांक32_t smu_v12_0_get_gfxoff_status(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t reg;
	uपूर्णांक32_t gfxOff_Status = 0;
	काष्ठा amdgpu_device *adev = smu->adev;

	reg = RREG32_SOC15(SMUIO, 0, mmSMUIO_GFX_MISC_CNTL);
	gfxOff_Status = (reg & SMUIO_GFX_MISC_CNTL__PWR_GFXOFF_STATUS_MASK)
		>> SMUIO_GFX_MISC_CNTL__PWR_GFXOFF_STATUS__SHIFT;

	वापस gfxOff_Status;
पूर्ण

पूर्णांक smu_v12_0_gfx_off_control(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0, समयout = 500;

	अगर (enable) अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_AllowGfxOff, शून्य);

	पूर्ण अन्यथा अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_DisallowGfxOff, शून्य);

		/* confirm gfx is back to "on" state, समयout is 0.5 second */
		जबतक (!(smu_v12_0_get_gfxoff_status(smu) == 2)) अणु
			msleep(1);
			समयout--;
			अगर (समयout == 0) अणु
				DRM_ERROR("disable gfxoff timeout and failed!\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v12_0_fini_smc_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;

	kमुक्त(smu_table->घड़ीs_table);
	smu_table->घड़ीs_table = शून्य;

	kमुक्त(smu_table->metrics_table);
	smu_table->metrics_table = शून्य;

	kमुक्त(smu_table->watermarks_table);
	smu_table->watermarks_table = शून्य;

	वापस 0;
पूर्ण

पूर्णांक smu_v12_0_set_शेष_dpm_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;

	वापस smu_cmn_update_table(smu, SMU_TABLE_DPMCLOCKS, 0, smu_table->घड़ीs_table, false);
पूर्ण

पूर्णांक smu_v12_0_mode2_reset(काष्ठा smu_context *smu)अणु
	वापस smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GfxDeviceDriverReset, SMU_RESET_MODE_2, शून्य);
पूर्ण

पूर्णांक smu_v12_0_set_soft_freq_limited_range(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
			    uपूर्णांक32_t min, uपूर्णांक32_t max)
अणु
	पूर्णांक ret = 0;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type))
		वापस 0;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinGfxClk, min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxGfxClk, max, शून्य);
		अगर (ret)
			वापस ret;
	अवरोध;
	हाल SMU_FCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinFclkByFreq, min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxFclkByFreq, max, शून्य);
		अगर (ret)
			वापस ret;
	अवरोध;
	हाल SMU_SOCCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinSocclkByFreq, min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxSocclkByFreq, max, शून्य);
		अगर (ret)
			वापस ret;
	अवरोध;
	हाल SMU_VCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinVcn, min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxVcn, max, शून्य);
		अगर (ret)
			वापस ret;
	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_v12_0_set_driver_table_location(काष्ठा smu_context *smu)
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

अटल पूर्णांक smu_v12_0_atom_get_smu_घड़ीinfo(काष्ठा amdgpu_device *adev,
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

पूर्णांक smu_v12_0_get_vbios_bootup_values(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret, index;
	uपूर्णांक16_t size;
	uपूर्णांक8_t frev, crev;
	काष्ठा atom_common_table_header *header;
	काष्ठा atom_firmware_info_v3_1 *v_3_1;
	काष्ठा atom_firmware_info_v3_3 *v_3_3;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    firmwareinfo);

	ret = amdgpu_atombios_get_data_table(smu->adev, index, &size, &frev, &crev,
				      (uपूर्णांक8_t **)&header);
	अगर (ret)
		वापस ret;

	अगर (header->क्रमmat_revision != 3) अणु
		dev_err(smu->adev->dev, "unknown atom_firmware_info version! for smu12\n");
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

	smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_SOCCLK_ID,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_ID,
					 &smu->smu_table.boot_values.socclk);

	smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU12_SYSPLL1_DCFCLK_ID,
					 (uपूर्णांक8_t)SMU12_SYSPLL1_ID,
					 &smu->smu_table.boot_values.dcefclk);

	smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_VCLK_ID,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_ID,
					 &smu->smu_table.boot_values.vclk);

	smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_DCLK_ID,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_ID,
					 &smu->smu_table.boot_values.dclk);

	अगर ((smu->smu_table.boot_values.क्रमmat_revision == 3) &&
	    (smu->smu_table.boot_values.content_revision >= 2))
		smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
						 (uपूर्णांक8_t)SMU12_SYSPLL3_0_FCLK_ID,
						 (uपूर्णांक8_t)SMU12_SYSPLL3_0_ID,
						 &smu->smu_table.boot_values.fclk);

	smu_v12_0_atom_get_smu_घड़ीinfo(smu->adev,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_LCLK_ID,
					 (uपूर्णांक8_t)SMU12_SYSPLL0_ID,
					 &smu->smu_table.boot_values.lclk);

	वापस 0;
पूर्ण
