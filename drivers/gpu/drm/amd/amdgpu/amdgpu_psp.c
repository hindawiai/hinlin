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
 * Author: Huang Rui
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/dma-mapping.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_ucode.h"
#समावेश "soc15_common.h"
#समावेश "psp_v3_1.h"
#समावेश "psp_v10_0.h"
#समावेश "psp_v11_0.h"
#समावेश "psp_v12_0.h"
#समावेश "psp_v13_0.h"

#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_securedisplay.h"

अटल पूर्णांक psp_sysfs_init(काष्ठा amdgpu_device *adev);
अटल व्योम psp_sysfs_fini(काष्ठा amdgpu_device *adev);

अटल पूर्णांक psp_load_smu_fw(काष्ठा psp_context *psp);

/*
 * Due to DF Cstate management centralized to PMFW, the firmware
 * loading sequence will be updated as below:
 *   - Load KDB
 *   - Load SYS_DRV
 *   - Load tOS
 *   - Load PMFW
 *   - Setup TMR
 *   - Load other non-psp fw
 *   - Load ASD
 *   - Load XGMI/RAS/HDCP/DTM TA अगर any
 *
 * This new sequence is required क्रम
 *   - Arcturus and onwards
 *   - Navi12 and onwards
 */
अटल व्योम psp_check_pmfw_centralized_cstate_management(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;

	psp->pmfw_centralized_cstate_management = false;

	अगर (amdgpu_sriov_vf(adev))
		वापस;

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	अगर ((adev->asic_type >= CHIP_ARCTURUS) ||
	    (adev->asic_type >= CHIP_NAVI12))
		psp->pmfw_centralized_cstate_management = true;
पूर्ण

अटल पूर्णांक psp_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा psp_context *psp = &adev->psp;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
		psp_v3_1_set_psp_funcs(psp);
		psp->स्वतःload_supported = false;
		अवरोध;
	हाल CHIP_RAVEN:
		psp_v10_0_set_psp_funcs(psp);
		psp->स्वतःload_supported = false;
		अवरोध;
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
		psp_v11_0_set_psp_funcs(psp);
		psp->स्वतःload_supported = false;
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		psp_v11_0_set_psp_funcs(psp);
		psp->स्वतःload_supported = true;
		अवरोध;
	हाल CHIP_RENOIR:
		psp_v12_0_set_psp_funcs(psp);
		अवरोध;
	हाल CHIP_ALDEBARAN:
		psp_v13_0_set_psp_funcs(psp);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	psp->adev = adev;

	psp_check_pmfw_centralized_cstate_management(psp);

	वापस 0;
पूर्ण

अटल व्योम psp_memory_training_fini(काष्ठा psp_context *psp)
अणु
	काष्ठा psp_memory_training_context *ctx = &psp->mem_train_ctx;

	ctx->init = PSP_MEM_TRAIN_NOT_SUPPORT;
	kमुक्त(ctx->sys_cache);
	ctx->sys_cache = शून्य;
पूर्ण

अटल पूर्णांक psp_memory_training_init(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_memory_training_context *ctx = &psp->mem_train_ctx;

	अगर (ctx->init != PSP_MEM_TRAIN_RESERVE_SUCCESS) अणु
		DRM_DEBUG("memory training is not supported!\n");
		वापस 0;
	पूर्ण

	ctx->sys_cache = kzalloc(ctx->train_data_size, GFP_KERNEL);
	अगर (ctx->sys_cache == शून्य) अणु
		DRM_ERROR("alloc mem_train_ctx.sys_cache failed!\n");
		ret = -ENOMEM;
		जाओ Err_out;
	पूर्ण

	DRM_DEBUG("train_data_size:%llx,p2c_train_data_offset:%llx,c2p_train_data_offset:%llx.\n",
		  ctx->train_data_size,
		  ctx->p2c_train_data_offset,
		  ctx->c2p_train_data_offset);
	ctx->init = PSP_MEM_TRAIN_INIT_SUCCESS;
	वापस 0;

Err_out:
	psp_memory_training_fini(psp);
	वापस ret;
पूर्ण

अटल पूर्णांक psp_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा psp_context *psp = &adev->psp;
	पूर्णांक ret;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		ret = psp_init_microcode(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to load psp firmware!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = psp_memory_training_init(psp);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize memory training!\n");
		वापस ret;
	पूर्ण
	ret = psp_mem_training(psp, PSP_MEM_TRAIN_COLD_BOOT);
	अगर (ret) अणु
		DRM_ERROR("Failed to process memory training!\n");
		वापस ret;
	पूर्ण

	अगर (adev->asic_type == CHIP_NAVI10 || adev->asic_type == CHIP_SIENNA_CICHLID) अणु
		ret= psp_sysfs_init(adev);
		अगर (ret) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	psp_memory_training_fini(&adev->psp);
	अगर (adev->psp.sos_fw) अणु
		release_firmware(adev->psp.sos_fw);
		adev->psp.sos_fw = शून्य;
	पूर्ण
	अगर (adev->psp.asd_fw) अणु
		release_firmware(adev->psp.asd_fw);
		adev->psp.asd_fw = शून्य;
	पूर्ण
	अगर (adev->psp.ta_fw) अणु
		release_firmware(adev->psp.ta_fw);
		adev->psp.ta_fw = शून्य;
	पूर्ण

	अगर (adev->asic_type == CHIP_NAVI10 ||
	    adev->asic_type == CHIP_SIENNA_CICHLID)
		psp_sysfs_fini(adev);

	वापस 0;
पूर्ण

पूर्णांक psp_रुको_क्रम(काष्ठा psp_context *psp, uपूर्णांक32_t reg_index,
		 uपूर्णांक32_t reg_val, uपूर्णांक32_t mask, bool check_changed)
अणु
	uपूर्णांक32_t val;
	पूर्णांक i;
	काष्ठा amdgpu_device *adev = psp->adev;

	अगर (psp->adev->in_pci_err_recovery)
		वापस 0;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		val = RREG32(reg_index);
		अगर (check_changed) अणु
			अगर (val != reg_val)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर ((val & mask) == reg_val)
				वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस -ETIME;
पूर्ण

अटल पूर्णांक
psp_cmd_submit_buf(काष्ठा psp_context *psp,
		   काष्ठा amdgpu_firmware_info *ucode,
		   काष्ठा psp_gfx_cmd_resp *cmd, uपूर्णांक64_t fence_mc_addr)
अणु
	पूर्णांक ret;
	पूर्णांक index;
	पूर्णांक समयout = 20000;
	bool ras_पूर्णांकr = false;
	bool skip_unsupport = false;

	अगर (psp->adev->in_pci_err_recovery)
		वापस 0;

	mutex_lock(&psp->mutex);

	स_रखो(psp->cmd_buf_mem, 0, PSP_CMD_BUFFER_SIZE);

	स_नकल(psp->cmd_buf_mem, cmd, माप(काष्ठा psp_gfx_cmd_resp));

	index = atomic_inc_वापस(&psp->fence_value);
	ret = psp_ring_cmd_submit(psp, psp->cmd_buf_mc_addr, fence_mc_addr, index);
	अगर (ret) अणु
		atomic_dec(&psp->fence_value);
		mutex_unlock(&psp->mutex);
		वापस ret;
	पूर्ण

	amdgpu_asic_invalidate_hdp(psp->adev, शून्य);
	जबतक (*((अचिन्हित पूर्णांक *)psp->fence_buf) != index) अणु
		अगर (--समयout == 0)
			अवरोध;
		/*
		 * Shouldn't रुको क्रम समयout when err_event_athub occurs,
		 * because gpu reset thपढ़ो triggered and lock resource should
		 * be released क्रम psp resume sequence.
		 */
		ras_पूर्णांकr = amdgpu_ras_पूर्णांकr_triggered();
		अगर (ras_पूर्णांकr)
			अवरोध;
		usleep_range(10, 100);
		amdgpu_asic_invalidate_hdp(psp->adev, शून्य);
	पूर्ण

	/* We allow TEE_ERROR_NOT_SUPPORTED क्रम VMR command and PSP_ERR_UNKNOWN_COMMAND in SRIOV */
	skip_unsupport = (psp->cmd_buf_mem->resp.status == TEE_ERROR_NOT_SUPPORTED ||
		psp->cmd_buf_mem->resp.status == PSP_ERR_UNKNOWN_COMMAND) && amdgpu_sriov_vf(psp->adev);

	स_नकल((व्योम*)&cmd->resp, (व्योम*)&psp->cmd_buf_mem->resp, माप(काष्ठा psp_gfx_resp));

	/* In some हालs, psp response status is not 0 even there is no
	 * problem जबतक the command is submitted. Some version of PSP FW
	 * करोesn't ग_लिखो 0 to that field.
	 * So here we would like to only prपूर्णांक a warning instead of an error
	 * during psp initialization to aव्योम अवरोधing hw_init and it करोesn't
	 * वापस -EINVAL.
	 */
	अगर (!skip_unsupport && (psp->cmd_buf_mem->resp.status || !समयout) && !ras_पूर्णांकr) अणु
		अगर (ucode)
			DRM_WARN("failed to load ucode id (%d) ",
				  ucode->ucode_id);
		DRM_WARN("psp command (0x%X) failed and response status is (0x%X)\n",
			 psp->cmd_buf_mem->cmd_id,
			 psp->cmd_buf_mem->resp.status);
		अगर (!समयout) अणु
			mutex_unlock(&psp->mutex);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ucode) अणु
		ucode->पंचांगr_mc_addr_lo = psp->cmd_buf_mem->resp.fw_addr_lo;
		ucode->पंचांगr_mc_addr_hi = psp->cmd_buf_mem->resp.fw_addr_hi;
	पूर्ण
	mutex_unlock(&psp->mutex);

	वापस ret;
पूर्ण

अटल व्योम psp_prep_पंचांगr_cmd_buf(काष्ठा psp_context *psp,
				 काष्ठा psp_gfx_cmd_resp *cmd,
				 uपूर्णांक64_t पंचांगr_mc, काष्ठा amdgpu_bo *पंचांगr_bo)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	uपूर्णांक32_t size = amdgpu_bo_size(पंचांगr_bo);
	uपूर्णांक64_t पंचांगr_pa = amdgpu_gmc_vram_pa(adev, पंचांगr_bo);

	अगर (amdgpu_sriov_vf(psp->adev))
		cmd->cmd_id = GFX_CMD_ID_SETUP_VMR;
	अन्यथा
		cmd->cmd_id = GFX_CMD_ID_SETUP_TMR;
	cmd->cmd.cmd_setup_पंचांगr.buf_phy_addr_lo = lower_32_bits(पंचांगr_mc);
	cmd->cmd.cmd_setup_पंचांगr.buf_phy_addr_hi = upper_32_bits(पंचांगr_mc);
	cmd->cmd.cmd_setup_पंचांगr.buf_size = size;
	cmd->cmd.cmd_setup_पंचांगr.bitfield.virt_phy_addr = 1;
	cmd->cmd.cmd_setup_पंचांगr.प्रणाली_phy_addr_lo = lower_32_bits(पंचांगr_pa);
	cmd->cmd.cmd_setup_पंचांगr.प्रणाली_phy_addr_hi = upper_32_bits(पंचांगr_pa);
पूर्ण

अटल व्योम psp_prep_load_toc_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
				      uपूर्णांक64_t pri_buf_mc, uपूर्णांक32_t size)
अणु
	cmd->cmd_id = GFX_CMD_ID_LOAD_TOC;
	cmd->cmd.cmd_load_toc.toc_phy_addr_lo = lower_32_bits(pri_buf_mc);
	cmd->cmd.cmd_load_toc.toc_phy_addr_hi = upper_32_bits(pri_buf_mc);
	cmd->cmd.cmd_load_toc.toc_size = size;
पूर्ण

/* Issue LOAD TOC cmd to PSP to part toc and calculate पंचांगr size needed */
अटल पूर्णांक psp_load_toc(काष्ठा psp_context *psp,
			uपूर्णांक32_t *पंचांगr_size)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;
	/* Copy toc to psp firmware निजी buffer */
	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->toc_start_addr, psp->toc_bin_size);

	psp_prep_load_toc_cmd_buf(cmd, psp->fw_pri_mc_addr, psp->toc_bin_size);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);
	अगर (!ret)
		*पंचांगr_size = psp->cmd_buf_mem->resp.पंचांगr_size;
	kमुक्त(cmd);
	वापस ret;
पूर्ण

/* Set up Trusted Memory Region */
अटल पूर्णांक psp_पंचांगr_init(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	पूर्णांक पंचांगr_size;
	व्योम *पंचांगr_buf;
	व्योम **pptr;

	/*
	 * According to HW engineer, they prefer the TMR address be "naturally
	 * aligned" , e.g. the start address be an पूर्णांकeger भागide of TMR size.
	 *
	 * Note: this memory need be reserved till the driver
	 * uninitializes.
	 */
	पंचांगr_size = PSP_TMR_SIZE(psp->adev);

	/* For ASICs support RLC स्वतःload, psp will parse the toc
	 * and calculate the total size of TMR needed */
	अगर (!amdgpu_sriov_vf(psp->adev) &&
	    psp->toc_start_addr &&
	    psp->toc_bin_size &&
	    psp->fw_pri_buf) अणु
		ret = psp_load_toc(psp, &पंचांगr_size);
		अगर (ret) अणु
			DRM_ERROR("Failed to load toc\n");
			वापस ret;
		पूर्ण
	पूर्ण

	pptr = amdgpu_sriov_vf(psp->adev) ? &पंचांगr_buf : शून्य;
	ret = amdgpu_bo_create_kernel(psp->adev, पंचांगr_size, PSP_TMR_SIZE(psp->adev),
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->पंचांगr_bo, &psp->पंचांगr_mc_addr, pptr);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_clear_vf_fw(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	अगर (!amdgpu_sriov_vf(psp->adev) || psp->adev->asic_type != CHIP_NAVI12)
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->cmd_id = GFX_CMD_ID_CLEAR_VF_FW;

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);
	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल bool psp_skip_पंचांगr(काष्ठा psp_context *psp)
अणु
	चयन (psp->adev->asic_type) अणु
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक psp_पंचांगr_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/* For Navi12 and CHIP_SIENNA_CICHLID SRIOV, करो not set up TMR.
	 * Alपढ़ोy set up by host driver.
	 */
	अगर (amdgpu_sriov_vf(psp->adev) && psp_skip_पंचांगr(psp))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_पंचांगr_cmd_buf(psp, cmd, psp->पंचांगr_mc_addr, psp->पंचांगr_bo);
	DRM_INFO("reserve 0x%lx from 0x%llx for PSP TMR\n",
		 amdgpu_bo_size(psp->पंचांगr_bo), psp->पंचांगr_mc_addr);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल व्योम psp_prep_पंचांगr_unload_cmd_buf(काष्ठा psp_context *psp,
					काष्ठा psp_gfx_cmd_resp *cmd)
अणु
	अगर (amdgpu_sriov_vf(psp->adev))
		cmd->cmd_id = GFX_CMD_ID_DESTROY_VMR;
	अन्यथा
		cmd->cmd_id = GFX_CMD_ID_DESTROY_TMR;
पूर्ण

अटल पूर्णांक psp_पंचांगr_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_पंचांगr_unload_cmd_buf(psp, cmd);
	DRM_INFO("free PSP TMR buffer\n");

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_पंचांगr_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	व्योम *पंचांगr_buf;
	व्योम **pptr;

	ret = psp_पंचांगr_unload(psp);
	अगर (ret)
		वापस ret;

	/* मुक्त TMR memory buffer */
	pptr = amdgpu_sriov_vf(psp->adev) ? &पंचांगr_buf : शून्य;
	amdgpu_bo_मुक्त_kernel(&psp->पंचांगr_bo, &psp->पंचांगr_mc_addr, pptr);

	वापस 0;
पूर्ण

पूर्णांक psp_get_fw_attestation_records_addr(काष्ठा psp_context *psp,
					uपूर्णांक64_t *output_ptr)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	अगर (!output_ptr)
		वापस -EINVAL;

	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->cmd_id = GFX_CMD_ID_GET_FW_ATTESTATION;

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	अगर (!ret) अणु
		*output_ptr = ((uपूर्णांक64_t)cmd->resp.uresp.fwar_db_info.fwar_db_addr_lo) +
			      ((uपूर्णांक64_t)cmd->resp.uresp.fwar_db_info.fwar_db_addr_hi << 32);
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_boot_config_set(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा psp_context *psp = &adev->psp;
	काष्ठा psp_gfx_cmd_resp *cmd = psp->cmd;

	अगर (adev->asic_type != CHIP_SIENNA_CICHLID || amdgpu_sriov_vf(adev))
		वापस 0;

	स_रखो(cmd, 0, माप(काष्ठा psp_gfx_cmd_resp));

	cmd->cmd_id = GFX_CMD_ID_BOOT_CFG;
	cmd->cmd.boot_cfg.sub_cmd = BOOTCFG_CMD_SET;
	cmd->cmd.boot_cfg.boot_config = BOOT_CONFIG_GECC;
	cmd->cmd.boot_cfg.boot_config_valid = BOOT_CONFIG_GECC;

	वापस psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);
पूर्ण

अटल पूर्णांक psp_rl_load(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा psp_context *psp = &adev->psp;
	काष्ठा psp_gfx_cmd_resp *cmd = psp->cmd;

	अगर (psp->rl_bin_size == 0)
		वापस 0;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->rl_start_addr, psp->rl_bin_size);

	स_रखो(cmd, 0, माप(काष्ठा psp_gfx_cmd_resp));

	cmd->cmd_id = GFX_CMD_ID_LOAD_IP_FW;
	cmd->cmd.cmd_load_ip_fw.fw_phy_addr_lo = lower_32_bits(psp->fw_pri_mc_addr);
	cmd->cmd.cmd_load_ip_fw.fw_phy_addr_hi = upper_32_bits(psp->fw_pri_mc_addr);
	cmd->cmd.cmd_load_ip_fw.fw_size = psp->rl_bin_size;
	cmd->cmd.cmd_load_ip_fw.fw_type = GFX_FW_TYPE_REG_LIST;

	वापस psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);
पूर्ण

अटल व्योम psp_prep_asd_load_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
				uपूर्णांक64_t asd_mc, uपूर्णांक32_t size)
अणु
	cmd->cmd_id = GFX_CMD_ID_LOAD_ASD;
	cmd->cmd.cmd_load_ta.app_phy_addr_lo = lower_32_bits(asd_mc);
	cmd->cmd.cmd_load_ta.app_phy_addr_hi = upper_32_bits(asd_mc);
	cmd->cmd.cmd_load_ta.app_len = size;

	cmd->cmd.cmd_load_ta.cmd_buf_phy_addr_lo = 0;
	cmd->cmd.cmd_load_ta.cmd_buf_phy_addr_hi = 0;
	cmd->cmd.cmd_load_ta.cmd_buf_len = 0;
पूर्ण

अटल पूर्णांक psp_asd_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/* If PSP version करोesn't match ASD version, asd loading will be failed.
	 * add workaround to bypass it क्रम sriov now.
	 * TODO: add version check to make it common
	 */
	अगर (amdgpu_sriov_vf(psp->adev) || !psp->asd_ucode_size)
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->asd_start_addr, psp->asd_ucode_size);

	psp_prep_asd_load_cmd_buf(cmd, psp->fw_pri_mc_addr,
				  psp->asd_ucode_size);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);
	अगर (!ret) अणु
		psp->asd_context.asd_initialized = true;
		psp->asd_context.session_id = cmd->resp.session_id;
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल व्योम psp_prep_ta_unload_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
				       uपूर्णांक32_t session_id)
अणु
	cmd->cmd_id = GFX_CMD_ID_UNLOAD_TA;
	cmd->cmd.cmd_unload_ta.session_id = session_id;
पूर्ण

अटल पूर्णांक psp_asd_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->asd_context.asd_initialized)
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->asd_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);
	अगर (!ret)
		psp->asd_context.asd_initialized = false;

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल व्योम psp_prep_reg_prog_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
		uपूर्णांक32_t id, uपूर्णांक32_t value)
अणु
	cmd->cmd_id = GFX_CMD_ID_PROG_REG;
	cmd->cmd.cmd_setup_reg_prog.reg_value = value;
	cmd->cmd.cmd_setup_reg_prog.reg_id = id;
पूर्ण

पूर्णांक psp_reg_program(काष्ठा psp_context *psp, क्रमागत psp_reg_prog_id reg,
		uपूर्णांक32_t value)
अणु
	काष्ठा psp_gfx_cmd_resp *cmd = शून्य;
	पूर्णांक ret = 0;

	अगर (reg >= PSP_REG_LAST)
		वापस -EINVAL;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_reg_prog_cmd_buf(cmd, reg, value);
	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	kमुक्त(cmd);
	वापस ret;
पूर्ण

अटल व्योम psp_prep_ta_load_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
				     uपूर्णांक64_t ta_bin_mc,
				     uपूर्णांक32_t ta_bin_size,
				     uपूर्णांक64_t ta_shared_mc,
				     uपूर्णांक32_t ta_shared_size)
अणु
	cmd->cmd_id				= GFX_CMD_ID_LOAD_TA;
	cmd->cmd.cmd_load_ta.app_phy_addr_lo 	= lower_32_bits(ta_bin_mc);
	cmd->cmd.cmd_load_ta.app_phy_addr_hi	= upper_32_bits(ta_bin_mc);
	cmd->cmd.cmd_load_ta.app_len		= ta_bin_size;

	cmd->cmd.cmd_load_ta.cmd_buf_phy_addr_lo = lower_32_bits(ta_shared_mc);
	cmd->cmd.cmd_load_ta.cmd_buf_phy_addr_hi = upper_32_bits(ta_shared_mc);
	cmd->cmd.cmd_load_ta.cmd_buf_len	 = ta_shared_size;
पूर्ण

अटल पूर्णांक psp_xgmi_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम xgmi ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_XGMI_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->xgmi_context.xgmi_shared_bo,
				      &psp->xgmi_context.xgmi_shared_mc_addr,
				      &psp->xgmi_context.xgmi_shared_buf);

	वापस ret;
पूर्ण

अटल व्योम psp_prep_ta_invoke_cmd_buf(काष्ठा psp_gfx_cmd_resp *cmd,
				       uपूर्णांक32_t ta_cmd_id,
				       uपूर्णांक32_t session_id)
अणु
	cmd->cmd_id				= GFX_CMD_ID_INVOKE_CMD;
	cmd->cmd.cmd_invoke_cmd.session_id	= session_id;
	cmd->cmd.cmd_invoke_cmd.ta_cmd_id	= ta_cmd_id;
पूर्ण

अटल पूर्णांक psp_ta_invoke(काष्ठा psp_context *psp,
		  uपूर्णांक32_t ta_cmd_id,
		  uपूर्णांक32_t session_id)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_invoke_cmd_buf(cmd, ta_cmd_id, session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_xgmi_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_xgmi_start_addr, psp->ta_xgmi_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_xgmi_ucode_size,
				 psp->xgmi_context.xgmi_shared_mc_addr,
				 PSP_XGMI_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	अगर (!ret) अणु
		psp->xgmi_context.initialized = 1;
		psp->xgmi_context.session_id = cmd->resp.session_id;
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_xgmi_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* XGMI TA unload currently is not supported on Arcturus/Aldebaran A+A */
	अगर (adev->asic_type == CHIP_ARCTURUS ||
		(adev->asic_type == CHIP_ALDEBARAN && adev->gmc.xgmi.connected_to_cpu))
		वापस 0;

	/*
	 * TODO: bypass the unloading in sriov क्रम now
	 */

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->xgmi_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक psp_xgmi_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id)
अणु
	वापस psp_ta_invoke(psp, ta_cmd_id, psp->xgmi_context.session_id);
पूर्ण

पूर्णांक psp_xgmi_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	अगर (!psp->xgmi_context.initialized)
		वापस 0;

	ret = psp_xgmi_unload(psp);
	अगर (ret)
		वापस ret;

	psp->xgmi_context.initialized = 0;

	/* मुक्त xgmi shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->xgmi_context.xgmi_shared_bo,
			&psp->xgmi_context.xgmi_shared_mc_addr,
			&psp->xgmi_context.xgmi_shared_buf);

	वापस 0;
पूर्ण

पूर्णांक psp_xgmi_initialize(काष्ठा psp_context *psp)
अणु
	काष्ठा ta_xgmi_shared_memory *xgmi_cmd;
	पूर्णांक ret;

	अगर (!psp->adev->psp.ta_fw ||
	    !psp->adev->psp.ta_xgmi_ucode_size ||
	    !psp->adev->psp.ta_xgmi_start_addr)
		वापस -ENOENT;

	अगर (!psp->xgmi_context.initialized) अणु
		ret = psp_xgmi_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Load XGMI TA */
	ret = psp_xgmi_load(psp);
	अगर (ret)
		वापस ret;

	/* Initialize XGMI session */
	xgmi_cmd = (काष्ठा ta_xgmi_shared_memory *)(psp->xgmi_context.xgmi_shared_buf);
	स_रखो(xgmi_cmd, 0, माप(काष्ठा ta_xgmi_shared_memory));
	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__INITIALIZE;

	ret = psp_xgmi_invoke(psp, xgmi_cmd->cmd_id);

	वापस ret;
पूर्ण

पूर्णांक psp_xgmi_get_hive_id(काष्ठा psp_context *psp, uपूर्णांक64_t *hive_id)
अणु
	काष्ठा ta_xgmi_shared_memory *xgmi_cmd;
	पूर्णांक ret;

	xgmi_cmd = (काष्ठा ta_xgmi_shared_memory *)psp->xgmi_context.xgmi_shared_buf;
	स_रखो(xgmi_cmd, 0, माप(काष्ठा ta_xgmi_shared_memory));

	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__GET_HIVE_ID;

	/* Invoke xgmi ta to get hive id */
	ret = psp_xgmi_invoke(psp, xgmi_cmd->cmd_id);
	अगर (ret)
		वापस ret;

	*hive_id = xgmi_cmd->xgmi_out_message.get_hive_id.hive_id;

	वापस 0;
पूर्ण

पूर्णांक psp_xgmi_get_node_id(काष्ठा psp_context *psp, uपूर्णांक64_t *node_id)
अणु
	काष्ठा ta_xgmi_shared_memory *xgmi_cmd;
	पूर्णांक ret;

	xgmi_cmd = (काष्ठा ta_xgmi_shared_memory *)psp->xgmi_context.xgmi_shared_buf;
	स_रखो(xgmi_cmd, 0, माप(काष्ठा ta_xgmi_shared_memory));

	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__GET_NODE_ID;

	/* Invoke xgmi ta to get the node id */
	ret = psp_xgmi_invoke(psp, xgmi_cmd->cmd_id);
	अगर (ret)
		वापस ret;

	*node_id = xgmi_cmd->xgmi_out_message.get_node_id.node_id;

	वापस 0;
पूर्ण

पूर्णांक psp_xgmi_get_topology_info(काष्ठा psp_context *psp,
			       पूर्णांक number_devices,
			       काष्ठा psp_xgmi_topology_info *topology)
अणु
	काष्ठा ta_xgmi_shared_memory *xgmi_cmd;
	काष्ठा ta_xgmi_cmd_get_topology_info_input *topology_info_input;
	काष्ठा ta_xgmi_cmd_get_topology_info_output *topology_info_output;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!topology || topology->num_nodes > TA_XGMI__MAX_CONNECTED_NODES)
		वापस -EINVAL;

	xgmi_cmd = (काष्ठा ta_xgmi_shared_memory *)psp->xgmi_context.xgmi_shared_buf;
	स_रखो(xgmi_cmd, 0, माप(काष्ठा ta_xgmi_shared_memory));

	/* Fill in the shared memory with topology inक्रमmation as input */
	topology_info_input = &xgmi_cmd->xgmi_in_message.get_topology_info;
	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__GET_GET_TOPOLOGY_INFO;
	topology_info_input->num_nodes = number_devices;

	क्रम (i = 0; i < topology_info_input->num_nodes; i++) अणु
		topology_info_input->nodes[i].node_id = topology->nodes[i].node_id;
		topology_info_input->nodes[i].num_hops = topology->nodes[i].num_hops;
		topology_info_input->nodes[i].is_sharing_enabled = topology->nodes[i].is_sharing_enabled;
		topology_info_input->nodes[i].sdma_engine = topology->nodes[i].sdma_engine;
	पूर्ण

	/* Invoke xgmi ta to get the topology inक्रमmation */
	ret = psp_xgmi_invoke(psp, TA_COMMAND_XGMI__GET_GET_TOPOLOGY_INFO);
	अगर (ret)
		वापस ret;

	/* Read the output topology inक्रमmation from the shared memory */
	topology_info_output = &xgmi_cmd->xgmi_out_message.get_topology_info;
	topology->num_nodes = xgmi_cmd->xgmi_out_message.get_topology_info.num_nodes;
	क्रम (i = 0; i < topology->num_nodes; i++) अणु
		topology->nodes[i].node_id = topology_info_output->nodes[i].node_id;
		topology->nodes[i].num_hops = topology_info_output->nodes[i].num_hops;
		topology->nodes[i].is_sharing_enabled = topology_info_output->nodes[i].is_sharing_enabled;
		topology->nodes[i].sdma_engine = topology_info_output->nodes[i].sdma_engine;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक psp_xgmi_set_topology_info(काष्ठा psp_context *psp,
			       पूर्णांक number_devices,
			       काष्ठा psp_xgmi_topology_info *topology)
अणु
	काष्ठा ta_xgmi_shared_memory *xgmi_cmd;
	काष्ठा ta_xgmi_cmd_get_topology_info_input *topology_info_input;
	पूर्णांक i;

	अगर (!topology || topology->num_nodes > TA_XGMI__MAX_CONNECTED_NODES)
		वापस -EINVAL;

	xgmi_cmd = (काष्ठा ta_xgmi_shared_memory *)psp->xgmi_context.xgmi_shared_buf;
	स_रखो(xgmi_cmd, 0, माप(काष्ठा ta_xgmi_shared_memory));

	topology_info_input = &xgmi_cmd->xgmi_in_message.get_topology_info;
	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__SET_TOPOLOGY_INFO;
	topology_info_input->num_nodes = number_devices;

	क्रम (i = 0; i < topology_info_input->num_nodes; i++) अणु
		topology_info_input->nodes[i].node_id = topology->nodes[i].node_id;
		topology_info_input->nodes[i].num_hops = topology->nodes[i].num_hops;
		topology_info_input->nodes[i].is_sharing_enabled = 1;
		topology_info_input->nodes[i].sdma_engine = topology->nodes[i].sdma_engine;
	पूर्ण

	/* Invoke xgmi ta to set topology inक्रमmation */
	वापस psp_xgmi_invoke(psp, TA_COMMAND_XGMI__SET_TOPOLOGY_INFO);
पूर्ण

// ras begin
अटल पूर्णांक psp_ras_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम ras ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_RAS_SHARED_MEM_SIZE,
			PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
			&psp->ras.ras_shared_bo,
			&psp->ras.ras_shared_mc_addr,
			&psp->ras.ras_shared_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_ras_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;
	काष्ठा ta_ras_shared_memory *ras_cmd;

	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_ras_start_addr, psp->ta_ras_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_ras_ucode_size,
				 psp->ras.ras_shared_mc_addr,
				 PSP_RAS_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
			psp->fence_buf_mc_addr);

	ras_cmd = (काष्ठा ta_ras_shared_memory *)psp->ras.ras_shared_buf;

	अगर (!ret) अणु
		psp->ras.session_id = cmd->resp.session_id;

		अगर (!ras_cmd->ras_status)
			psp->ras.ras_initialized = true;
		अन्यथा
			dev_warn(psp->adev->dev, "RAS Init Status: 0x%X\n", ras_cmd->ras_status);
	पूर्ण

	अगर (ret || ras_cmd->ras_status)
		amdgpu_ras_fini(psp->adev);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_ras_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the unloading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->ras.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
			psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक psp_ras_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id)
अणु
	काष्ठा ta_ras_shared_memory *ras_cmd;
	पूर्णांक ret;

	ras_cmd = (काष्ठा ta_ras_shared_memory *)psp->ras.ras_shared_buf;

	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	ret = psp_ta_invoke(psp, ta_cmd_id, psp->ras.session_id);

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस ret;

	अगर (ras_cmd->अगर_version > RAS_TA_HOST_IF_VER)
	अणु
		DRM_WARN("RAS: Unsupported Interface");
		वापस -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		अगर (ras_cmd->ras_out_message.flags.err_inject_चयन_disable_flag) अणु
			dev_warn(psp->adev->dev, "ECC switch disabled\n");

			ras_cmd->ras_status = TA_RAS_STATUS__ERROR_RAS_NOT_AVAILABLE;
		पूर्ण
		अन्यथा अगर (ras_cmd->ras_out_message.flags.reg_access_failure_flag)
			dev_warn(psp->adev->dev,
				 "RAS internal register access blocked\n");
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक psp_ras_enable_features(काष्ठा psp_context *psp,
		जोड़ ta_ras_cmd_input *info, bool enable)
अणु
	काष्ठा ta_ras_shared_memory *ras_cmd;
	पूर्णांक ret;

	अगर (!psp->ras.ras_initialized)
		वापस -EINVAL;

	ras_cmd = (काष्ठा ta_ras_shared_memory *)psp->ras.ras_shared_buf;
	स_रखो(ras_cmd, 0, माप(काष्ठा ta_ras_shared_memory));

	अगर (enable)
		ras_cmd->cmd_id = TA_RAS_COMMAND__ENABLE_FEATURES;
	अन्यथा
		ras_cmd->cmd_id = TA_RAS_COMMAND__DISABLE_FEATURES;

	ras_cmd->ras_in_message = *info;

	ret = psp_ras_invoke(psp, ras_cmd->cmd_id);
	अगर (ret)
		वापस -EINVAL;

	वापस ras_cmd->ras_status;
पूर्ण

अटल पूर्णांक psp_ras_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the terminate in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->ras.ras_initialized)
		वापस 0;

	ret = psp_ras_unload(psp);
	अगर (ret)
		वापस ret;

	psp->ras.ras_initialized = false;

	/* मुक्त ras shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->ras.ras_shared_bo,
			&psp->ras.ras_shared_mc_addr,
			&psp->ras.ras_shared_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक psp_ras_initialize(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the initialize in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->adev->psp.ta_ras_ucode_size ||
	    !psp->adev->psp.ta_ras_start_addr) अणु
		dev_info(psp->adev->dev, "RAS: optional ras ta ucode is not available\n");
		वापस 0;
	पूर्ण

	अगर (!psp->ras.ras_initialized) अणु
		ret = psp_ras_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_ras_load(psp);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक psp_ras_trigger_error(काष्ठा psp_context *psp,
			  काष्ठा ta_ras_trigger_error_input *info)
अणु
	काष्ठा ta_ras_shared_memory *ras_cmd;
	पूर्णांक ret;

	अगर (!psp->ras.ras_initialized)
		वापस -EINVAL;

	ras_cmd = (काष्ठा ta_ras_shared_memory *)psp->ras.ras_shared_buf;
	स_रखो(ras_cmd, 0, माप(काष्ठा ta_ras_shared_memory));

	ras_cmd->cmd_id = TA_RAS_COMMAND__TRIGGER_ERROR;
	ras_cmd->ras_in_message.trigger_error = *info;

	ret = psp_ras_invoke(psp, ras_cmd->cmd_id);
	अगर (ret)
		वापस -EINVAL;

	/* If err_event_athub occurs error inject was successful, however
	   वापस status from TA is no दीर्घ reliable */
	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस 0;

	वापस ras_cmd->ras_status;
पूर्ण
// ras end

// HDCP start
अटल पूर्णांक psp_hdcp_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम hdcp ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_HDCP_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->hdcp_context.hdcp_shared_bo,
				      &psp->hdcp_context.hdcp_shared_mc_addr,
				      &psp->hdcp_context.hdcp_shared_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_hdcp_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_hdcp_start_addr,
	       psp->ta_hdcp_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_hdcp_ucode_size,
				 psp->hdcp_context.hdcp_shared_mc_addr,
				 PSP_HDCP_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	अगर (!ret) अणु
		psp->hdcp_context.hdcp_initialized = true;
		psp->hdcp_context.session_id = cmd->resp.session_id;
		mutex_init(&psp->hdcp_context.mutex);
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण
अटल पूर्णांक psp_hdcp_initialize(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the initialize in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->adev->psp.ta_hdcp_ucode_size ||
	    !psp->adev->psp.ta_hdcp_start_addr) अणु
		dev_info(psp->adev->dev, "HDCP: optional hdcp ta ucode is not available\n");
		वापस 0;
	पूर्ण

	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		ret = psp_hdcp_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_hdcp_load(psp);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक psp_hdcp_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the unloading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->hdcp_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक psp_hdcp_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id)
अणु
	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	वापस psp_ta_invoke(psp, ta_cmd_id, psp->hdcp_context.session_id);
पूर्ण

अटल पूर्णांक psp_hdcp_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the terminate in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		अगर (psp->hdcp_context.hdcp_shared_buf)
			जाओ out;
		अन्यथा
			वापस 0;
	पूर्ण

	ret = psp_hdcp_unload(psp);
	अगर (ret)
		वापस ret;

	psp->hdcp_context.hdcp_initialized = false;

out:
	/* मुक्त hdcp shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->hdcp_context.hdcp_shared_bo,
			      &psp->hdcp_context.hdcp_shared_mc_addr,
			      &psp->hdcp_context.hdcp_shared_buf);

	वापस 0;
पूर्ण
// HDCP end

// DTM start
अटल पूर्णांक psp_dपंचांग_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम dपंचांग ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_DTM_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->dपंचांग_context.dपंचांग_shared_bo,
				      &psp->dपंचांग_context.dपंचांग_shared_mc_addr,
				      &psp->dपंचांग_context.dपंचांग_shared_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_dपंचांग_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_dपंचांग_start_addr, psp->ta_dपंचांग_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_dपंचांग_ucode_size,
				 psp->dपंचांग_context.dपंचांग_shared_mc_addr,
				 PSP_DTM_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	अगर (!ret) अणु
		psp->dपंचांग_context.dपंचांग_initialized = true;
		psp->dपंचांग_context.session_id = cmd->resp.session_id;
		mutex_init(&psp->dपंचांग_context.mutex);
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_dपंचांग_initialize(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the initialize in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->adev->psp.ta_dपंचांग_ucode_size ||
	    !psp->adev->psp.ta_dपंचांग_start_addr) अणु
		dev_info(psp->adev->dev, "DTM: optional dtm ta ucode is not available\n");
		वापस 0;
	पूर्ण

	अगर (!psp->dपंचांग_context.dपंचांग_initialized) अणु
		ret = psp_dपंचांग_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_dपंचांग_load(psp);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक psp_dपंचांग_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the unloading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->dपंचांग_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

पूर्णांक psp_dपंचांग_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id)
अणु
	/*
	 * TODO: bypass the loading in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	वापस psp_ta_invoke(psp, ta_cmd_id, psp->dपंचांग_context.session_id);
पूर्ण

अटल पूर्णांक psp_dपंचांग_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO: bypass the terminate in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->dपंचांग_context.dपंचांग_initialized) अणु
		अगर (psp->dपंचांग_context.dपंचांग_shared_buf)
			जाओ out;
		अन्यथा
			वापस 0;
	पूर्ण

	ret = psp_dपंचांग_unload(psp);
	अगर (ret)
		वापस ret;

	psp->dपंचांग_context.dपंचांग_initialized = false;

out:
	/* मुक्त hdcp shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->dपंचांग_context.dपंचांग_shared_bo,
			      &psp->dपंचांग_context.dपंचांग_shared_mc_addr,
			      &psp->dपंचांग_context.dपंचांग_shared_buf);

	वापस 0;
पूर्ण
// DTM end

// RAP start
अटल पूर्णांक psp_rap_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम rap ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_RAP_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->rap_context.rap_shared_bo,
				      &psp->rap_context.rap_shared_mc_addr,
				      &psp->rap_context.rap_shared_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_rap_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_rap_start_addr, psp->ta_rap_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_rap_ucode_size,
				 psp->rap_context.rap_shared_mc_addr,
				 PSP_RAP_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	अगर (!ret) अणु
		psp->rap_context.rap_initialized = true;
		psp->rap_context.session_id = cmd->resp.session_id;
		mutex_init(&psp->rap_context.mutex);
	पूर्ण

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_rap_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->rap_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_rap_initialize(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	क्रमागत ta_rap_status status = TA_RAP_STATUS__SUCCESS;

	/*
	 * TODO: bypass the initialize in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->adev->psp.ta_rap_ucode_size ||
	    !psp->adev->psp.ta_rap_start_addr) अणु
		dev_info(psp->adev->dev, "RAP: optional rap ta ucode is not available\n");
		वापस 0;
	पूर्ण

	अगर (!psp->rap_context.rap_initialized) अणु
		ret = psp_rap_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_rap_load(psp);
	अगर (ret)
		वापस ret;

	ret = psp_rap_invoke(psp, TA_CMD_RAP__INITIALIZE, &status);
	अगर (ret || status != TA_RAP_STATUS__SUCCESS) अणु
		psp_rap_unload(psp);

		amdgpu_bo_मुक्त_kernel(&psp->rap_context.rap_shared_bo,
			      &psp->rap_context.rap_shared_mc_addr,
			      &psp->rap_context.rap_shared_buf);

		psp->rap_context.rap_initialized = false;

		dev_warn(psp->adev->dev, "RAP TA initialize fail (%d) status %d.\n",
			 ret, status);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_rap_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	अगर (!psp->rap_context.rap_initialized)
		वापस 0;

	ret = psp_rap_unload(psp);

	psp->rap_context.rap_initialized = false;

	/* मुक्त rap shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->rap_context.rap_shared_bo,
			      &psp->rap_context.rap_shared_mc_addr,
			      &psp->rap_context.rap_shared_buf);

	वापस ret;
पूर्ण

पूर्णांक psp_rap_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id, क्रमागत ta_rap_status *status)
अणु
	काष्ठा ta_rap_shared_memory *rap_cmd;
	पूर्णांक ret = 0;

	अगर (!psp->rap_context.rap_initialized)
		वापस 0;

	अगर (ta_cmd_id != TA_CMD_RAP__INITIALIZE &&
	    ta_cmd_id != TA_CMD_RAP__VALIDATE_L0)
		वापस -EINVAL;

	mutex_lock(&psp->rap_context.mutex);

	rap_cmd = (काष्ठा ta_rap_shared_memory *)
		  psp->rap_context.rap_shared_buf;
	स_रखो(rap_cmd, 0, माप(काष्ठा ta_rap_shared_memory));

	rap_cmd->cmd_id = ta_cmd_id;
	rap_cmd->validation_method_id = METHOD_A;

	ret = psp_ta_invoke(psp, rap_cmd->cmd_id, psp->rap_context.session_id);
	अगर (ret)
		जाओ out_unlock;

	अगर (status)
		*status = rap_cmd->rap_status;

out_unlock:
	mutex_unlock(&psp->rap_context.mutex);

	वापस ret;
पूर्ण
// RAP end

/* securedisplay start */
अटल पूर्णांक psp_securedisplay_init_shared_buf(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) क्रम sa ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_SECUREDISPLAY_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->securedisplay_context.securedisplay_shared_bo,
				      &psp->securedisplay_context.securedisplay_shared_mc_addr,
				      &psp->securedisplay_context.securedisplay_shared_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_securedisplay_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);
	स_नकल(psp->fw_pri_buf, psp->ta_securedisplay_start_addr, psp->ta_securedisplay_ucode_size);

	psp_prep_ta_load_cmd_buf(cmd,
				 psp->fw_pri_mc_addr,
				 psp->ta_securedisplay_ucode_size,
				 psp->securedisplay_context.securedisplay_shared_mc_addr,
				 PSP_SECUREDISPLAY_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	अगर (ret)
		जाओ failed;

	psp->securedisplay_context.securedisplay_initialized = true;
	psp->securedisplay_context.session_id = cmd->resp.session_id;
	mutex_init(&psp->securedisplay_context.mutex);

failed:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक psp_securedisplay_unload(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	psp_prep_ta_unload_cmd_buf(cmd, psp->securedisplay_context.session_id);

	ret = psp_cmd_submit_buf(psp, शून्य, cmd, psp->fence_buf_mc_addr);

	kमुक्त(cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_securedisplay_initialize(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा securedisplay_cmd *securedisplay_cmd;

	/*
	 * TODO: bypass the initialize in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->adev->psp.ta_securedisplay_ucode_size ||
	    !psp->adev->psp.ta_securedisplay_start_addr) अणु
		dev_info(psp->adev->dev, "SECUREDISPLAY: securedisplay ta ucode is not available\n");
		वापस 0;
	पूर्ण

	अगर (!psp->securedisplay_context.securedisplay_initialized) अणु
		ret = psp_securedisplay_init_shared_buf(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_securedisplay_load(psp);
	अगर (ret)
		वापस ret;

	psp_prep_securedisplay_cmd_buf(psp, &securedisplay_cmd,
			TA_SECUREDISPLAY_COMMAND__QUERY_TA);

	ret = psp_securedisplay_invoke(psp, TA_SECUREDISPLAY_COMMAND__QUERY_TA);
	अगर (ret) अणु
		psp_securedisplay_unload(psp);

		amdgpu_bo_मुक्त_kernel(&psp->securedisplay_context.securedisplay_shared_bo,
			      &psp->securedisplay_context.securedisplay_shared_mc_addr,
			      &psp->securedisplay_context.securedisplay_shared_buf);

		psp->securedisplay_context.securedisplay_initialized = false;

		dev_err(psp->adev->dev, "SECUREDISPLAY TA initialize fail.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (securedisplay_cmd->status != TA_SECUREDISPLAY_STATUS__SUCCESS) अणु
		psp_securedisplay_parse_resp_status(psp, securedisplay_cmd->status);
		dev_err(psp->adev->dev, "SECUREDISPLAY: query securedisplay TA failed. ret 0x%x\n",
			securedisplay_cmd->securedisplay_out_message.query_ta.query_cmd_ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_securedisplay_terminate(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;

	/*
	 * TODO:bypass the terminate in sriov क्रम now
	 */
	अगर (amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर (!psp->securedisplay_context.securedisplay_initialized)
		वापस 0;

	ret = psp_securedisplay_unload(psp);
	अगर (ret)
		वापस ret;

	psp->securedisplay_context.securedisplay_initialized = false;

	/* मुक्त securedisplay shared memory */
	amdgpu_bo_मुक्त_kernel(&psp->securedisplay_context.securedisplay_shared_bo,
			      &psp->securedisplay_context.securedisplay_shared_mc_addr,
			      &psp->securedisplay_context.securedisplay_shared_buf);

	वापस ret;
पूर्ण

पूर्णांक psp_securedisplay_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id)
अणु
	पूर्णांक ret;

	अगर (!psp->securedisplay_context.securedisplay_initialized)
		वापस -EINVAL;

	अगर (ta_cmd_id != TA_SECUREDISPLAY_COMMAND__QUERY_TA &&
	    ta_cmd_id != TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC)
		वापस -EINVAL;

	mutex_lock(&psp->securedisplay_context.mutex);

	ret = psp_ta_invoke(psp, ta_cmd_id, psp->securedisplay_context.session_id);

	mutex_unlock(&psp->securedisplay_context.mutex);

	वापस ret;
पूर्ण
/* SECUREDISPLAY end */

अटल पूर्णांक psp_hw_start(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	पूर्णांक ret;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		अगर (psp->kdb_bin_size &&
		    (psp->funcs->bootloader_load_kdb != शून्य)) अणु
			ret = psp_bootloader_load_kdb(psp);
			अगर (ret) अणु
				DRM_ERROR("PSP load kdb failed!\n");
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (psp->spl_bin_size) अणु
			ret = psp_bootloader_load_spl(psp);
			अगर (ret) अणु
				DRM_ERROR("PSP load spl failed!\n");
				वापस ret;
			पूर्ण
		पूर्ण

		ret = psp_bootloader_load_sysdrv(psp);
		अगर (ret) अणु
			DRM_ERROR("PSP load sysdrv failed!\n");
			वापस ret;
		पूर्ण

		ret = psp_bootloader_load_sos(psp);
		अगर (ret) अणु
			DRM_ERROR("PSP load sos failed!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = psp_ring_create(psp, PSP_RING_TYPE__KM);
	अगर (ret) अणु
		DRM_ERROR("PSP create ring failed!\n");
		वापस ret;
	पूर्ण

	ret = psp_clear_vf_fw(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP clear vf fw!\n");
		वापस ret;
	पूर्ण

	ret = psp_boot_config_set(adev);
	अगर (ret) अणु
		DRM_WARN("PSP set boot config@\n");
	पूर्ण

	ret = psp_पंचांगr_init(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP tmr init failed!\n");
		वापस ret;
	पूर्ण

	/*
	 * For ASICs with DF Cstate management centralized
	 * to PMFW, TMR setup should be perक्रमmed after PMFW
	 * loaded and beक्रमe other non-psp firmware loaded.
	 */
	अगर (psp->pmfw_centralized_cstate_management) अणु
		ret = psp_load_smu_fw(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = psp_पंचांगr_load(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP load tmr failed!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_get_fw_type(काष्ठा amdgpu_firmware_info *ucode,
			   क्रमागत psp_gfx_fw_type *type)
अणु
	चयन (ucode->ucode_id) अणु
	हाल AMDGPU_UCODE_ID_SDMA0:
		*type = GFX_FW_TYPE_SDMA0;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA1:
		*type = GFX_FW_TYPE_SDMA1;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA2:
		*type = GFX_FW_TYPE_SDMA2;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA3:
		*type = GFX_FW_TYPE_SDMA3;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA4:
		*type = GFX_FW_TYPE_SDMA4;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA5:
		*type = GFX_FW_TYPE_SDMA5;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA6:
		*type = GFX_FW_TYPE_SDMA6;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SDMA7:
		*type = GFX_FW_TYPE_SDMA7;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MES:
		*type = GFX_FW_TYPE_CP_MES;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MES_DATA:
		*type = GFX_FW_TYPE_MES_STACK;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_CE:
		*type = GFX_FW_TYPE_CP_CE;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_PFP:
		*type = GFX_FW_TYPE_CP_PFP;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_ME:
		*type = GFX_FW_TYPE_CP_ME;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MEC1:
		*type = GFX_FW_TYPE_CP_MEC;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MEC1_JT:
		*type = GFX_FW_TYPE_CP_MEC_ME1;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MEC2:
		*type = GFX_FW_TYPE_CP_MEC;
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MEC2_JT:
		*type = GFX_FW_TYPE_CP_MEC_ME2;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_G:
		*type = GFX_FW_TYPE_RLC_G;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_CNTL;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_GPM_MEM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_MEM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_IRAM:
		*type = GFX_FW_TYPE_RLC_IRAM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_DRAM:
		*type = GFX_FW_TYPE_RLC_DRAM_BOOT;
		अवरोध;
	हाल AMDGPU_UCODE_ID_SMC:
		*type = GFX_FW_TYPE_SMU;
		अवरोध;
	हाल AMDGPU_UCODE_ID_UVD:
		*type = GFX_FW_TYPE_UVD;
		अवरोध;
	हाल AMDGPU_UCODE_ID_UVD1:
		*type = GFX_FW_TYPE_UVD1;
		अवरोध;
	हाल AMDGPU_UCODE_ID_VCE:
		*type = GFX_FW_TYPE_VCE;
		अवरोध;
	हाल AMDGPU_UCODE_ID_VCN:
		*type = GFX_FW_TYPE_VCN;
		अवरोध;
	हाल AMDGPU_UCODE_ID_VCN1:
		*type = GFX_FW_TYPE_VCN1;
		अवरोध;
	हाल AMDGPU_UCODE_ID_DMCU_ERAM:
		*type = GFX_FW_TYPE_DMCU_ERAM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_DMCU_INTV:
		*type = GFX_FW_TYPE_DMCU_ISR;
		अवरोध;
	हाल AMDGPU_UCODE_ID_VCN0_RAM:
		*type = GFX_FW_TYPE_VCN0_RAM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_VCN1_RAM:
		*type = GFX_FW_TYPE_VCN1_RAM;
		अवरोध;
	हाल AMDGPU_UCODE_ID_DMCUB:
		*type = GFX_FW_TYPE_DMUB;
		अवरोध;
	हाल AMDGPU_UCODE_ID_MAXIMUM:
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम psp_prपूर्णांक_fw_hdr(काष्ठा psp_context *psp,
			     काष्ठा amdgpu_firmware_info *ucode)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	काष्ठा common_firmware_header *hdr;

	चयन (ucode->ucode_id) अणु
	हाल AMDGPU_UCODE_ID_SDMA0:
	हाल AMDGPU_UCODE_ID_SDMA1:
	हाल AMDGPU_UCODE_ID_SDMA2:
	हाल AMDGPU_UCODE_ID_SDMA3:
	हाल AMDGPU_UCODE_ID_SDMA4:
	हाल AMDGPU_UCODE_ID_SDMA5:
	हाल AMDGPU_UCODE_ID_SDMA6:
	हाल AMDGPU_UCODE_ID_SDMA7:
		hdr = (काष्ठा common_firmware_header *)
			adev->sdma.instance[ucode->ucode_id - AMDGPU_UCODE_ID_SDMA0].fw->data;
		amdgpu_ucode_prपूर्णांक_sdma_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_CE:
		hdr = (काष्ठा common_firmware_header *)adev->gfx.ce_fw->data;
		amdgpu_ucode_prपूर्णांक_gfx_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_PFP:
		hdr = (काष्ठा common_firmware_header *)adev->gfx.pfp_fw->data;
		amdgpu_ucode_prपूर्णांक_gfx_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_ME:
		hdr = (काष्ठा common_firmware_header *)adev->gfx.me_fw->data;
		amdgpu_ucode_prपूर्णांक_gfx_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_CP_MEC1:
		hdr = (काष्ठा common_firmware_header *)adev->gfx.mec_fw->data;
		amdgpu_ucode_prपूर्णांक_gfx_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_RLC_G:
		hdr = (काष्ठा common_firmware_header *)adev->gfx.rlc_fw->data;
		amdgpu_ucode_prपूर्णांक_rlc_hdr(hdr);
		अवरोध;
	हाल AMDGPU_UCODE_ID_SMC:
		hdr = (काष्ठा common_firmware_header *)adev->pm.fw->data;
		amdgpu_ucode_prपूर्णांक_smc_hdr(hdr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक psp_prep_load_ip_fw_cmd_buf(काष्ठा amdgpu_firmware_info *ucode,
				       काष्ठा psp_gfx_cmd_resp *cmd)
अणु
	पूर्णांक ret;
	uपूर्णांक64_t fw_mem_mc_addr = ucode->mc_addr;

	स_रखो(cmd, 0, माप(काष्ठा psp_gfx_cmd_resp));

	cmd->cmd_id = GFX_CMD_ID_LOAD_IP_FW;
	cmd->cmd.cmd_load_ip_fw.fw_phy_addr_lo = lower_32_bits(fw_mem_mc_addr);
	cmd->cmd.cmd_load_ip_fw.fw_phy_addr_hi = upper_32_bits(fw_mem_mc_addr);
	cmd->cmd.cmd_load_ip_fw.fw_size = ucode->ucode_size;

	ret = psp_get_fw_type(ucode, &cmd->cmd.cmd_load_ip_fw.fw_type);
	अगर (ret)
		DRM_ERROR("Unknown firmware type\n");

	वापस ret;
पूर्ण

अटल पूर्णांक psp_execute_np_fw_load(काष्ठा psp_context *psp,
			          काष्ठा amdgpu_firmware_info *ucode)
अणु
	पूर्णांक ret = 0;

	ret = psp_prep_load_ip_fw_cmd_buf(ucode, psp->cmd);
	अगर (ret)
		वापस ret;

	ret = psp_cmd_submit_buf(psp, ucode, psp->cmd,
				 psp->fence_buf_mc_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_load_smu_fw(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = psp->adev;
	काष्ठा amdgpu_firmware_info *ucode =
			&adev->firmware.ucode[AMDGPU_UCODE_ID_SMC];
	काष्ठा amdgpu_ras *ras = psp->ras.ras;

	अगर (!ucode->fw || amdgpu_sriov_vf(psp->adev))
		वापस 0;

	अगर ((amdgpu_in_reset(adev) &&
	     ras && ras->supported &&
	     (adev->asic_type == CHIP_ARCTURUS ||
	      adev->asic_type == CHIP_VEGA20)) ||
	     (adev->in_runpm &&
	      adev->asic_type >= CHIP_NAVI10 &&
	      adev->asic_type <= CHIP_NAVI12)) अणु
		ret = amdgpu_dpm_set_mp1_state(adev, PP_MP1_STATE_UNLOAD);
		अगर (ret) अणु
			DRM_WARN("Failed to set MP1 state prepare for reload\n");
		पूर्ण
	पूर्ण

	ret = psp_execute_np_fw_load(psp, ucode);

	अगर (ret)
		DRM_ERROR("PSP load smu failed!\n");

	वापस ret;
पूर्ण

अटल bool fw_load_skip_check(काष्ठा psp_context *psp,
			       काष्ठा amdgpu_firmware_info *ucode)
अणु
	अगर (!ucode->fw)
		वापस true;

	अगर (ucode->ucode_id == AMDGPU_UCODE_ID_SMC &&
	    (psp_smu_reload_quirk(psp) ||
	     psp->स्वतःload_supported ||
	     psp->pmfw_centralized_cstate_management))
		वापस true;

	अगर (amdgpu_sriov_vf(psp->adev) &&
	   (ucode->ucode_id == AMDGPU_UCODE_ID_SDMA0
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA1
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA2
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA3
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA4
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA5
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA6
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA7
	    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_G
	    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL
	    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM
	    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM
	    || ucode->ucode_id == AMDGPU_UCODE_ID_SMC))
		/*skip ucode loading in SRIOV VF */
		वापस true;

	अगर (psp->स्वतःload_supported &&
	    (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1_JT ||
	     ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2_JT))
		/* skip mec JT when स्वतःload is enabled */
		वापस true;

	वापस false;
पूर्ण

पूर्णांक psp_load_fw_list(काष्ठा psp_context *psp,
		     काष्ठा amdgpu_firmware_info **ucode_list, पूर्णांक ucode_count)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा amdgpu_firmware_info *ucode;

	क्रम (i = 0; i < ucode_count; ++i) अणु
		ucode = ucode_list[i];
		psp_prपूर्णांक_fw_hdr(psp, ucode);
		ret = psp_execute_np_fw_load(psp, ucode);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक psp_np_fw_load(काष्ठा psp_context *psp)
अणु
	पूर्णांक i, ret;
	काष्ठा amdgpu_firmware_info *ucode;
	काष्ठा amdgpu_device *adev = psp->adev;

	अगर (psp->स्वतःload_supported &&
	    !psp->pmfw_centralized_cstate_management) अणु
		ret = psp_load_smu_fw(psp);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < adev->firmware.max_ucodes; i++) अणु
		ucode = &adev->firmware.ucode[i];

		अगर (ucode->ucode_id == AMDGPU_UCODE_ID_SMC &&
		    !fw_load_skip_check(psp, ucode)) अणु
			ret = psp_load_smu_fw(psp);
			अगर (ret)
				वापस ret;
			जारी;
		पूर्ण

		अगर (fw_load_skip_check(psp, ucode))
			जारी;

		अगर (psp->स्वतःload_supported &&
		    (adev->asic_type >= CHIP_SIENNA_CICHLID &&
		     adev->asic_type <= CHIP_DIMGREY_CAVEFISH) &&
		    (ucode->ucode_id == AMDGPU_UCODE_ID_SDMA1 ||
		     ucode->ucode_id == AMDGPU_UCODE_ID_SDMA2 ||
		     ucode->ucode_id == AMDGPU_UCODE_ID_SDMA3))
			/* PSP only receive one SDMA fw क्रम sienna_cichlid,
			 * as all four sdma fw are same */
			जारी;

		psp_prपूर्णांक_fw_hdr(psp, ucode);

		ret = psp_execute_np_fw_load(psp, ucode);
		अगर (ret)
			वापस ret;

		/* Start rlc स्वतःload after psp recieved all the gfx firmware */
		अगर (psp->स्वतःload_supported && ucode->ucode_id == (amdgpu_sriov_vf(adev) ?
		    AMDGPU_UCODE_ID_CP_MEC2 : AMDGPU_UCODE_ID_RLC_G)) अणु
			ret = psp_rlc_स्वतःload_start(psp);
			अगर (ret) अणु
				DRM_ERROR("Failed to start rlc autoload\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_load_fw(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	काष्ठा psp_context *psp = &adev->psp;

	अगर (amdgpu_sriov_vf(adev) && amdgpu_in_reset(adev)) अणु
		psp_ring_stop(psp, PSP_RING_TYPE__KM); /* should not destroy ring, only stop */
		जाओ skip_meदो_स्मृति;
	पूर्ण

	psp->cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!psp->cmd)
		वापस -ENOMEM;

	ret = amdgpu_bo_create_kernel(adev, PSP_1_MEG, PSP_1_MEG,
					AMDGPU_GEM_DOMAIN_GTT,
					&psp->fw_pri_bo,
					&psp->fw_pri_mc_addr,
					&psp->fw_pri_buf);
	अगर (ret)
		जाओ failed;

	ret = amdgpu_bo_create_kernel(adev, PSP_FENCE_BUFFER_SIZE, PAGE_SIZE,
					AMDGPU_GEM_DOMAIN_VRAM,
					&psp->fence_buf_bo,
					&psp->fence_buf_mc_addr,
					&psp->fence_buf);
	अगर (ret)
		जाओ failed;

	ret = amdgpu_bo_create_kernel(adev, PSP_CMD_BUFFER_SIZE, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->cmd_buf_bo, &psp->cmd_buf_mc_addr,
				      (व्योम **)&psp->cmd_buf_mem);
	अगर (ret)
		जाओ failed;

	स_रखो(psp->fence_buf, 0, PSP_FENCE_BUFFER_SIZE);

	ret = psp_ring_init(psp, PSP_RING_TYPE__KM);
	अगर (ret) अणु
		DRM_ERROR("PSP ring init failed!\n");
		जाओ failed;
	पूर्ण

skip_meदो_स्मृति:
	ret = psp_hw_start(psp);
	अगर (ret)
		जाओ failed;

	ret = psp_np_fw_load(psp);
	अगर (ret)
		जाओ failed;

	ret = psp_asd_load(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP load asd failed!\n");
		वापस ret;
	पूर्ण

	ret = psp_rl_load(adev);
	अगर (ret) अणु
		DRM_ERROR("PSP load RL failed!\n");
		वापस ret;
	पूर्ण

	अगर (psp->adev->psp.ta_fw) अणु
		ret = psp_ras_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
					"RAS: Failed to initialize RAS\n");

		ret = psp_hdcp_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"HDCP: Failed to initialize HDCP\n");

		ret = psp_dपंचांग_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"DTM: Failed to initialize DTM\n");

		ret = psp_rap_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"RAP: Failed to initialize RAP\n");

		ret = psp_securedisplay_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"SECUREDISPLAY: Failed to initialize SECUREDISPLAY\n");
	पूर्ण

	वापस 0;

failed:
	/*
	 * all cleanup jobs (xgmi terminate, ras terminate,
	 * ring destroy, cmd/fence/fw buffers destory,
	 * psp->cmd destory) are delayed to psp_hw_fini
	 */
	वापस ret;
पूर्ण

अटल पूर्णांक psp_hw_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	mutex_lock(&adev->firmware.mutex);
	/*
	 * This sequence is just used on hw_init only once, no need on
	 * resume.
	 */
	ret = amdgpu_ucode_init_bo(adev);
	अगर (ret)
		जाओ failed;

	ret = psp_load_fw(adev);
	अगर (ret) अणु
		DRM_ERROR("PSP firmware loading failed\n");
		जाओ failed;
	पूर्ण

	mutex_unlock(&adev->firmware.mutex);
	वापस 0;

failed:
	adev->firmware.load_type = AMDGPU_FW_LOAD_सूचीECT;
	mutex_unlock(&adev->firmware.mutex);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक psp_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा psp_context *psp = &adev->psp;
	पूर्णांक ret;

	अगर (psp->adev->psp.ta_fw) अणु
		psp_ras_terminate(psp);
		psp_securedisplay_terminate(psp);
		psp_rap_terminate(psp);
		psp_dपंचांग_terminate(psp);
		psp_hdcp_terminate(psp);
	पूर्ण

	psp_asd_unload(psp);
	ret = psp_clear_vf_fw(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP clear vf fw!\n");
		वापस ret;
	पूर्ण

	psp_पंचांगr_terminate(psp);
	psp_ring_destroy(psp, PSP_RING_TYPE__KM);

	amdgpu_bo_मुक्त_kernel(&psp->fw_pri_bo,
			      &psp->fw_pri_mc_addr, &psp->fw_pri_buf);
	amdgpu_bo_मुक्त_kernel(&psp->fence_buf_bo,
			      &psp->fence_buf_mc_addr, &psp->fence_buf);
	amdgpu_bo_मुक्त_kernel(&psp->cmd_buf_bo, &psp->cmd_buf_mc_addr,
			      (व्योम **)&psp->cmd_buf_mem);

	kमुक्त(psp->cmd);
	psp->cmd = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक psp_suspend(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा psp_context *psp = &adev->psp;

	अगर (adev->gmc.xgmi.num_physical_nodes > 1 &&
	    psp->xgmi_context.initialized == 1) अणु
		ret = psp_xgmi_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate xgmi ta\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (psp->adev->psp.ta_fw) अणु
		ret = psp_ras_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate ras ta\n");
			वापस ret;
		पूर्ण
		ret = psp_hdcp_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate hdcp ta\n");
			वापस ret;
		पूर्ण
		ret = psp_dपंचांग_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate dtm ta\n");
			वापस ret;
		पूर्ण
		ret = psp_rap_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate rap ta\n");
			वापस ret;
		पूर्ण
		ret = psp_securedisplay_terminate(psp);
		अगर (ret) अणु
			DRM_ERROR("Failed to terminate securedisplay ta\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = psp_asd_unload(psp);
	अगर (ret) अणु
		DRM_ERROR("Failed to unload asd\n");
		वापस ret;
	पूर्ण

	ret = psp_पंचांगr_terminate(psp);
	अगर (ret) अणु
		DRM_ERROR("Failed to terminate tmr\n");
		वापस ret;
	पूर्ण

	ret = psp_ring_stop(psp, PSP_RING_TYPE__KM);
	अगर (ret) अणु
		DRM_ERROR("PSP ring stop failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_resume(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा psp_context *psp = &adev->psp;

	DRM_INFO("PSP is resuming...\n");

	ret = psp_mem_training(psp, PSP_MEM_TRAIN_RESUME);
	अगर (ret) अणु
		DRM_ERROR("Failed to process memory training!\n");
		वापस ret;
	पूर्ण

	mutex_lock(&adev->firmware.mutex);

	ret = psp_hw_start(psp);
	अगर (ret)
		जाओ failed;

	ret = psp_np_fw_load(psp);
	अगर (ret)
		जाओ failed;

	ret = psp_asd_load(psp);
	अगर (ret) अणु
		DRM_ERROR("PSP load asd failed!\n");
		जाओ failed;
	पूर्ण

	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		ret = psp_xgmi_initialize(psp);
		/* Warning the XGMI seesion initialize failure
		 * Instead of stop driver initialization
		 */
		अगर (ret)
			dev_err(psp->adev->dev,
				"XGMI: Failed to initialize XGMI session\n");
	पूर्ण

	अगर (psp->adev->psp.ta_fw) अणु
		ret = psp_ras_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
					"RAS: Failed to initialize RAS\n");

		ret = psp_hdcp_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"HDCP: Failed to initialize HDCP\n");

		ret = psp_dपंचांग_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"DTM: Failed to initialize DTM\n");

		ret = psp_rap_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"RAP: Failed to initialize RAP\n");

		ret = psp_securedisplay_initialize(psp);
		अगर (ret)
			dev_err(psp->adev->dev,
				"SECUREDISPLAY: Failed to initialize SECUREDISPLAY\n");
	पूर्ण

	mutex_unlock(&adev->firmware.mutex);

	वापस 0;

failed:
	DRM_ERROR("PSP resume failed\n");
	mutex_unlock(&adev->firmware.mutex);
	वापस ret;
पूर्ण

पूर्णांक psp_gpu_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;

	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		वापस 0;

	mutex_lock(&adev->psp.mutex);
	ret = psp_mode1_reset(&adev->psp);
	mutex_unlock(&adev->psp.mutex);

	वापस ret;
पूर्ण

पूर्णांक psp_rlc_स्वतःload_start(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	काष्ठा psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(माप(काष्ठा psp_gfx_cmd_resp), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->cmd_id = GFX_CMD_ID_AUTOLOAD_RLC;

	ret = psp_cmd_submit_buf(psp, शून्य, cmd,
				 psp->fence_buf_mc_addr);
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक psp_update_vcn_sram(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx,
			uपूर्णांक64_t cmd_gpu_addr, पूर्णांक cmd_size)
अणु
	काष्ठा amdgpu_firmware_info ucode = अणु0पूर्ण;

	ucode.ucode_id = inst_idx ? AMDGPU_UCODE_ID_VCN1_RAM :
		AMDGPU_UCODE_ID_VCN0_RAM;
	ucode.mc_addr = cmd_gpu_addr;
	ucode.ucode_size = cmd_size;

	वापस psp_execute_np_fw_load(&adev->psp, &ucode);
पूर्ण

पूर्णांक psp_ring_cmd_submit(काष्ठा psp_context *psp,
			uपूर्णांक64_t cmd_buf_mc_addr,
			uपूर्णांक64_t fence_mc_addr,
			पूर्णांक index)
अणु
	अचिन्हित पूर्णांक psp_ग_लिखो_ptr_reg = 0;
	काष्ठा psp_gfx_rb_frame *ग_लिखो_frame;
	काष्ठा psp_ring *ring = &psp->km_ring;
	काष्ठा psp_gfx_rb_frame *ring_buffer_start = ring->ring_mem;
	काष्ठा psp_gfx_rb_frame *ring_buffer_end = ring_buffer_start +
		ring->ring_size / माप(काष्ठा psp_gfx_rb_frame) - 1;
	काष्ठा amdgpu_device *adev = psp->adev;
	uपूर्णांक32_t ring_size_dw = ring->ring_size / 4;
	uपूर्णांक32_t rb_frame_size_dw = माप(काष्ठा psp_gfx_rb_frame) / 4;

	/* KM (GPCOM) prepare ग_लिखो poपूर्णांकer */
	psp_ग_लिखो_ptr_reg = psp_ring_get_wptr(psp);

	/* Update KM RB frame poपूर्णांकer to new frame */
	/* ग_लिखो_frame ptr increments by size of rb_frame in bytes */
	/* psp_ग_लिखो_ptr_reg increments by size of rb_frame in DWORDs */
	अगर ((psp_ग_लिखो_ptr_reg % ring_size_dw) == 0)
		ग_लिखो_frame = ring_buffer_start;
	अन्यथा
		ग_लिखो_frame = ring_buffer_start + (psp_ग_लिखो_ptr_reg / rb_frame_size_dw);
	/* Check invalid ग_लिखो_frame ptr address */
	अगर ((ग_लिखो_frame < ring_buffer_start) || (ring_buffer_end < ग_लिखो_frame)) अणु
		DRM_ERROR("ring_buffer_start = %p; ring_buffer_end = %p; write_frame = %p\n",
			  ring_buffer_start, ring_buffer_end, ग_लिखो_frame);
		DRM_ERROR("write_frame is pointing to address out of bounds\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize KM RB frame */
	स_रखो(ग_लिखो_frame, 0, माप(काष्ठा psp_gfx_rb_frame));

	/* Update KM RB frame */
	ग_लिखो_frame->cmd_buf_addr_hi = upper_32_bits(cmd_buf_mc_addr);
	ग_लिखो_frame->cmd_buf_addr_lo = lower_32_bits(cmd_buf_mc_addr);
	ग_लिखो_frame->fence_addr_hi = upper_32_bits(fence_mc_addr);
	ग_लिखो_frame->fence_addr_lo = lower_32_bits(fence_mc_addr);
	ग_लिखो_frame->fence_value = index;
	amdgpu_asic_flush_hdp(adev, शून्य);

	/* Update the ग_लिखो Poपूर्णांकer in DWORDs */
	psp_ग_लिखो_ptr_reg = (psp_ग_लिखो_ptr_reg + rb_frame_size_dw) % ring_size_dw;
	psp_ring_set_wptr(psp, psp_ग_लिखो_ptr_reg);
	वापस 0;
पूर्ण

पूर्णांक psp_init_asd_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	अक्षर fw_name[PSP_FW_NAME_LEN];
	स्थिर काष्ठा psp_firmware_header_v1_0 *asd_hdr;
	पूर्णांक err = 0;

	अगर (!chip_name) अणु
		dev_err(adev->dev, "invalid chip name for asd microcode\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_asd.bin", chip_name);
	err = request_firmware(&adev->psp.asd_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = amdgpu_ucode_validate(adev->psp.asd_fw);
	अगर (err)
		जाओ out;

	asd_hdr = (स्थिर काष्ठा psp_firmware_header_v1_0 *)adev->psp.asd_fw->data;
	adev->psp.asd_fw_version = le32_to_cpu(asd_hdr->header.ucode_version);
	adev->psp.asd_feature_version = le32_to_cpu(asd_hdr->ucode_feature_version);
	adev->psp.asd_ucode_size = le32_to_cpu(asd_hdr->header.ucode_size_bytes);
	adev->psp.asd_start_addr = (uपूर्णांक8_t *)asd_hdr +
				le32_to_cpu(asd_hdr->header.ucode_array_offset_bytes);
	वापस 0;
out:
	dev_err(adev->dev, "fail to initialize asd microcode\n");
	release_firmware(adev->psp.asd_fw);
	adev->psp.asd_fw = शून्य;
	वापस err;
पूर्ण

पूर्णांक psp_init_toc_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	अक्षर fw_name[30];
	स्थिर काष्ठा psp_firmware_header_v1_0 *toc_hdr;
	पूर्णांक err = 0;

	अगर (!chip_name) अणु
		dev_err(adev->dev, "invalid chip name for toc microcode\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_toc.bin", chip_name);
	err = request_firmware(&adev->psp.toc_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = amdgpu_ucode_validate(adev->psp.toc_fw);
	अगर (err)
		जाओ out;

	toc_hdr = (स्थिर काष्ठा psp_firmware_header_v1_0 *)adev->psp.toc_fw->data;
	adev->psp.toc_fw_version = le32_to_cpu(toc_hdr->header.ucode_version);
	adev->psp.toc_feature_version = le32_to_cpu(toc_hdr->ucode_feature_version);
	adev->psp.toc_bin_size = le32_to_cpu(toc_hdr->header.ucode_size_bytes);
	adev->psp.toc_start_addr = (uपूर्णांक8_t *)toc_hdr +
				le32_to_cpu(toc_hdr->header.ucode_array_offset_bytes);
	वापस 0;
out:
	dev_err(adev->dev, "fail to request/validate toc microcode\n");
	release_firmware(adev->psp.toc_fw);
	adev->psp.toc_fw = शून्य;
	वापस err;
पूर्ण

पूर्णांक psp_init_sos_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	अक्षर fw_name[PSP_FW_NAME_LEN];
	स्थिर काष्ठा psp_firmware_header_v1_0 *sos_hdr;
	स्थिर काष्ठा psp_firmware_header_v1_1 *sos_hdr_v1_1;
	स्थिर काष्ठा psp_firmware_header_v1_2 *sos_hdr_v1_2;
	स्थिर काष्ठा psp_firmware_header_v1_3 *sos_hdr_v1_3;
	पूर्णांक err = 0;

	अगर (!chip_name) अणु
		dev_err(adev->dev, "invalid chip name for sos microcode\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_sos.bin", chip_name);
	err = request_firmware(&adev->psp.sos_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = amdgpu_ucode_validate(adev->psp.sos_fw);
	अगर (err)
		जाओ out;

	sos_hdr = (स्थिर काष्ठा psp_firmware_header_v1_0 *)adev->psp.sos_fw->data;
	amdgpu_ucode_prपूर्णांक_psp_hdr(&sos_hdr->header);

	चयन (sos_hdr->header.header_version_major) अणु
	हाल 1:
		adev->psp.sos_fw_version = le32_to_cpu(sos_hdr->header.ucode_version);
		adev->psp.sos_feature_version = le32_to_cpu(sos_hdr->ucode_feature_version);
		adev->psp.sos_bin_size = le32_to_cpu(sos_hdr->sos_size_bytes);
		adev->psp.sys_bin_size = le32_to_cpu(sos_hdr->sos_offset_bytes);
		adev->psp.sys_start_addr = (uपूर्णांक8_t *)sos_hdr +
				le32_to_cpu(sos_hdr->header.ucode_array_offset_bytes);
		adev->psp.sos_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(sos_hdr->sos_offset_bytes);
		अगर (sos_hdr->header.header_version_minor == 1) अणु
			sos_hdr_v1_1 = (स्थिर काष्ठा psp_firmware_header_v1_1 *)adev->psp.sos_fw->data;
			adev->psp.toc_bin_size = le32_to_cpu(sos_hdr_v1_1->toc_size_bytes);
			adev->psp.toc_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
					le32_to_cpu(sos_hdr_v1_1->toc_offset_bytes);
			adev->psp.kdb_bin_size = le32_to_cpu(sos_hdr_v1_1->kdb_size_bytes);
			adev->psp.kdb_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
					le32_to_cpu(sos_hdr_v1_1->kdb_offset_bytes);
		पूर्ण
		अगर (sos_hdr->header.header_version_minor == 2) अणु
			sos_hdr_v1_2 = (स्थिर काष्ठा psp_firmware_header_v1_2 *)adev->psp.sos_fw->data;
			adev->psp.kdb_bin_size = le32_to_cpu(sos_hdr_v1_2->kdb_size_bytes);
			adev->psp.kdb_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
						    le32_to_cpu(sos_hdr_v1_2->kdb_offset_bytes);
		पूर्ण
		अगर (sos_hdr->header.header_version_minor == 3) अणु
			sos_hdr_v1_3 = (स्थिर काष्ठा psp_firmware_header_v1_3 *)adev->psp.sos_fw->data;
			adev->psp.toc_bin_size = le32_to_cpu(sos_hdr_v1_3->v1_1.toc_size_bytes);
			adev->psp.toc_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(sos_hdr_v1_3->v1_1.toc_offset_bytes);
			adev->psp.kdb_bin_size = le32_to_cpu(sos_hdr_v1_3->v1_1.kdb_size_bytes);
			adev->psp.kdb_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(sos_hdr_v1_3->v1_1.kdb_offset_bytes);
			adev->psp.spl_bin_size = le32_to_cpu(sos_hdr_v1_3->spl_size_bytes);
			adev->psp.spl_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(sos_hdr_v1_3->spl_offset_bytes);
			adev->psp.rl_bin_size = le32_to_cpu(sos_hdr_v1_3->rl_size_bytes);
			adev->psp.rl_start_addr = (uपूर्णांक8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(sos_hdr_v1_3->rl_offset_bytes);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(adev->dev,
			"unsupported psp sos firmware\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(adev->dev,
		"failed to init sos firmware\n");
	release_firmware(adev->psp.sos_fw);
	adev->psp.sos_fw = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक parse_ta_bin_descriptor(काष्ठा psp_context *psp,
				   स्थिर काष्ठा ta_fw_bin_desc *desc,
				   स्थिर काष्ठा ta_firmware_header_v2_0 *ta_hdr)
अणु
	uपूर्णांक8_t *ucode_start_addr  = शून्य;

	अगर (!psp || !desc || !ta_hdr)
		वापस -EINVAL;

	ucode_start_addr  = (uपूर्णांक8_t *)ta_hdr +
			    le32_to_cpu(desc->offset_bytes) +
			    le32_to_cpu(ta_hdr->header.ucode_array_offset_bytes);

	चयन (desc->fw_type) अणु
	हाल TA_FW_TYPE_PSP_ASD:
		psp->asd_fw_version        = le32_to_cpu(desc->fw_version);
		psp->asd_feature_version   = le32_to_cpu(desc->fw_version);
		psp->asd_ucode_size        = le32_to_cpu(desc->size_bytes);
		psp->asd_start_addr 	   = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_XGMI:
		psp->ta_xgmi_ucode_version = le32_to_cpu(desc->fw_version);
		psp->ta_xgmi_ucode_size    = le32_to_cpu(desc->size_bytes);
		psp->ta_xgmi_start_addr    = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_RAS:
		psp->ta_ras_ucode_version  = le32_to_cpu(desc->fw_version);
		psp->ta_ras_ucode_size     = le32_to_cpu(desc->size_bytes);
		psp->ta_ras_start_addr     = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_HDCP:
		psp->ta_hdcp_ucode_version = le32_to_cpu(desc->fw_version);
		psp->ta_hdcp_ucode_size    = le32_to_cpu(desc->size_bytes);
		psp->ta_hdcp_start_addr    = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_DTM:
		psp->ta_dपंचांग_ucode_version  = le32_to_cpu(desc->fw_version);
		psp->ta_dपंचांग_ucode_size     = le32_to_cpu(desc->size_bytes);
		psp->ta_dपंचांग_start_addr     = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_RAP:
		psp->ta_rap_ucode_version  = le32_to_cpu(desc->fw_version);
		psp->ta_rap_ucode_size     = le32_to_cpu(desc->size_bytes);
		psp->ta_rap_start_addr     = ucode_start_addr;
		अवरोध;
	हाल TA_FW_TYPE_PSP_SECUREDISPLAY:
		psp->ta_securedisplay_ucode_version  = le32_to_cpu(desc->fw_version);
		psp->ta_securedisplay_ucode_size     = le32_to_cpu(desc->size_bytes);
		psp->ta_securedisplay_start_addr     = ucode_start_addr;
		अवरोध;
	शेष:
		dev_warn(psp->adev->dev, "Unsupported TA type: %d\n", desc->fw_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक psp_init_ta_microcode(काष्ठा psp_context *psp,
			  स्थिर अक्षर *chip_name)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	अक्षर fw_name[PSP_FW_NAME_LEN];
	स्थिर काष्ठा ta_firmware_header_v2_0 *ta_hdr;
	पूर्णांक err = 0;
	पूर्णांक ta_index = 0;

	अगर (!chip_name) अणु
		dev_err(adev->dev, "invalid chip name for ta microcode\n");
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ta.bin", chip_name);
	err = request_firmware(&adev->psp.ta_fw, fw_name, adev->dev);
	अगर (err)
		जाओ out;

	err = amdgpu_ucode_validate(adev->psp.ta_fw);
	अगर (err)
		जाओ out;

	ta_hdr = (स्थिर काष्ठा ta_firmware_header_v2_0 *)adev->psp.ta_fw->data;

	अगर (le16_to_cpu(ta_hdr->header.header_version_major) != 2) अणु
		dev_err(adev->dev, "unsupported TA header version\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (le32_to_cpu(ta_hdr->ta_fw_bin_count) >= UCODE_MAX_TA_PACKAGING) अणु
		dev_err(adev->dev, "packed TA count exceeds maximum limit\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (ta_index = 0; ta_index < le32_to_cpu(ta_hdr->ta_fw_bin_count); ta_index++) अणु
		err = parse_ta_bin_descriptor(psp,
					      &ta_hdr->ta_fw_bin[ta_index],
					      ta_hdr);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(adev->dev, "fail to initialize ta microcode\n");
	release_firmware(adev->psp.ta_fw);
	adev->psp.ta_fw = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक psp_set_घड़ीgating_state(व्योम *handle,
				     क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक psp_set_घातergating_state(व्योम *handle,
				     क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार psp_usbc_pd_fw_sysfs_पढ़ो(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक32_t fw_ver;
	पूर्णांक ret;

	अगर (!adev->ip_blocks[AMD_IP_BLOCK_TYPE_PSP].status.late_initialized) अणु
		DRM_INFO("PSP block is not ready yet.");
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&adev->psp.mutex);
	ret = psp_पढ़ो_usbc_pd_fw(&adev->psp, &fw_ver);
	mutex_unlock(&adev->psp.mutex);

	अगर (ret) अणु
		DRM_ERROR("Failed to read USBC PD FW, err = %d", ret);
		वापस ret;
	पूर्ण

	वापस sysfs_emit(buf, "%x\n", fw_ver);
पूर्ण

अटल sमाप_प्रकार psp_usbc_pd_fw_sysfs_ग_लिखो(काष्ठा device *dev,
						       काष्ठा device_attribute *attr,
						       स्थिर अक्षर *buf,
						       माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	व्योम *cpu_addr;
	dma_addr_t dma_addr;
	पूर्णांक ret;
	अक्षर fw_name[100];
	स्थिर काष्ठा firmware *usbc_pd_fw;

	अगर (!adev->ip_blocks[AMD_IP_BLOCK_TYPE_PSP].status.late_initialized) अणु
		DRM_INFO("PSP block is not ready yet.");
		वापस -EBUSY;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s", buf);
	ret = request_firmware(&usbc_pd_fw, fw_name, adev->dev);
	अगर (ret)
		जाओ fail;

	/* We need contiguous physical mem to place the FW  क्रम psp to access */
	cpu_addr = dma_alloc_coherent(adev->dev, usbc_pd_fw->size, &dma_addr, GFP_KERNEL);

	ret = dma_mapping_error(adev->dev, dma_addr);
	अगर (ret)
		जाओ rel_buf;

	स_नकल_toio(cpu_addr, usbc_pd_fw->data, usbc_pd_fw->size);

	/*
	 * x86 specअगरic workaround.
	 * Without it the buffer is invisible in PSP.
	 *
	 * TODO Remove once PSP starts snooping CPU cache
	 */
#अगर_घोषित CONFIG_X86
	clflush_cache_range(cpu_addr, (usbc_pd_fw->size & ~(L1_CACHE_BYTES - 1)));
#पूर्ण_अगर

	mutex_lock(&adev->psp.mutex);
	ret = psp_load_usbc_pd_fw(&adev->psp, dma_addr);
	mutex_unlock(&adev->psp.mutex);

rel_buf:
	dma_मुक्त_coherent(adev->dev, usbc_pd_fw->size, cpu_addr, dma_addr);
	release_firmware(usbc_pd_fw);

fail:
	अगर (ret) अणु
		DRM_ERROR("Failed to load USBC PD FW, err = %d", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(usbc_pd_fw, S_IRUGO | S_IWUSR,
		   psp_usbc_pd_fw_sysfs_पढ़ो,
		   psp_usbc_pd_fw_sysfs_ग_लिखो);



स्थिर काष्ठा amd_ip_funcs psp_ip_funcs = अणु
	.name = "psp",
	.early_init = psp_early_init,
	.late_init = शून्य,
	.sw_init = psp_sw_init,
	.sw_fini = psp_sw_fini,
	.hw_init = psp_hw_init,
	.hw_fini = psp_hw_fini,
	.suspend = psp_suspend,
	.resume = psp_resume,
	.is_idle = शून्य,
	.check_soft_reset = शून्य,
	.रुको_क्रम_idle = शून्य,
	.soft_reset = शून्य,
	.set_घड़ीgating_state = psp_set_घड़ीgating_state,
	.set_घातergating_state = psp_set_घातergating_state,
पूर्ण;

अटल पूर्णांक psp_sysfs_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = device_create_file(adev->dev, &dev_attr_usbc_pd_fw);

	अगर (ret)
		DRM_ERROR("Failed to create USBC PD FW control file!");

	वापस ret;
पूर्ण

अटल व्योम psp_sysfs_fini(काष्ठा amdgpu_device *adev)
अणु
	device_हटाओ_file(adev->dev, &dev_attr_usbc_pd_fw);
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version psp_v3_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_PSP,
	.major = 3,
	.minor = 1,
	.rev = 0,
	.funcs = &psp_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version psp_v10_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_PSP,
	.major = 10,
	.minor = 0,
	.rev = 0,
	.funcs = &psp_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version psp_v11_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_PSP,
	.major = 11,
	.minor = 0,
	.rev = 0,
	.funcs = &psp_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version psp_v12_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_PSP,
	.major = 12,
	.minor = 0,
	.rev = 0,
	.funcs = &psp_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version psp_v13_0_ip_block = अणु
	.type = AMD_IP_BLOCK_TYPE_PSP,
	.major = 13,
	.minor = 0,
	.rev = 0,
	.funcs = &psp_ip_funcs,
पूर्ण;
