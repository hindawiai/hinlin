<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश "amdgpu.h"
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu_uvd.h"
#समावेश "amdgpu_vce.h"
#समावेश "atom.h"

#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_gem.h"
#समावेश "amdgpu_display.h"
#समावेश "amdgpu_ras.h"

व्योम amdgpu_unरेजिस्टर_gpu_instance(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_gpu_instance *gpu_instance;
	पूर्णांक i;

	mutex_lock(&mgpu_info.mutex);

	क्रम (i = 0; i < mgpu_info.num_gpu; i++) अणु
		gpu_instance = &(mgpu_info.gpu_ins[i]);
		अगर (gpu_instance->adev == adev) अणु
			mgpu_info.gpu_ins[i] =
				mgpu_info.gpu_ins[mgpu_info.num_gpu - 1];
			mgpu_info.num_gpu--;
			अगर (adev->flags & AMD_IS_APU)
				mgpu_info.num_apu--;
			अन्यथा
				mgpu_info.num_dgpu--;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&mgpu_info.mutex);
पूर्ण

/**
 * amdgpu_driver_unload_kms - Main unload function क्रम KMS.
 *
 * @dev: drm dev poपूर्णांकer
 *
 * This is the मुख्य unload function क्रम KMS (all asics).
 * Returns 0 on success.
 */
व्योम amdgpu_driver_unload_kms(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर (adev == शून्य)
		वापस;

	amdgpu_unरेजिस्टर_gpu_instance(adev);

	अगर (adev->rmmio == शून्य)
		वापस;

	अगर (adev->runpm) अणु
		pm_runसमय_get_sync(dev->dev);
		pm_runसमय_क्रमbid(dev->dev);
	पूर्ण

	amdgpu_acpi_fini(adev);
	amdgpu_device_fini(adev);
पूर्ण

व्योम amdgpu_रेजिस्टर_gpu_instance(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_gpu_instance *gpu_instance;

	mutex_lock(&mgpu_info.mutex);

	अगर (mgpu_info.num_gpu >= MAX_GPU_INSTANCE) अणु
		DRM_ERROR("Cannot register more gpu instance\n");
		mutex_unlock(&mgpu_info.mutex);
		वापस;
	पूर्ण

	gpu_instance = &(mgpu_info.gpu_ins[mgpu_info.num_gpu]);
	gpu_instance->adev = adev;
	gpu_instance->mgpu_fan_enabled = 0;

	mgpu_info.num_gpu++;
	अगर (adev->flags & AMD_IS_APU)
		mgpu_info.num_apu++;
	अन्यथा
		mgpu_info.num_dgpu++;

	mutex_unlock(&mgpu_info.mutex);
पूर्ण

/**
 * amdgpu_driver_load_kms - Main load function क्रम KMS.
 *
 * @adev: poपूर्णांकer to काष्ठा amdgpu_device
 * @flags: device flags
 *
 * This is the मुख्य load function क्रम KMS (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_driver_load_kms(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_device *dev;
	काष्ठा pci_dev *parent;
	पूर्णांक r, acpi_status;

	dev = adev_to_drm(adev);

	अगर (amdgpu_has_atpx() &&
	    (amdgpu_is_atpx_hybrid() ||
	     amdgpu_has_atpx_dgpu_घातer_cntl()) &&
	    ((flags & AMD_IS_APU) == 0) &&
	    !pci_is_thunderbolt_attached(to_pci_dev(dev->dev)))
		flags |= AMD_IS_PX;

	parent = pci_upstream_bridge(adev->pdev);
	adev->has_pr3 = parent ? pci_pr3_present(parent) : false;

	/* amdgpu_device_init should report only fatal error
	 * like memory allocation failure or iomapping failure,
	 * or memory manager initialization failure, it must
	 * properly initialize the GPU MC controller and permit
	 * VRAM allocation
	 */
	r = amdgpu_device_init(adev, flags);
	अगर (r) अणु
		dev_err(dev->dev, "Fatal error during GPU init\n");
		जाओ out;
	पूर्ण

	अगर (amdgpu_device_supports_px(dev) &&
	    (amdgpu_runसमय_pm != 0)) अणु /* enable runpm by शेष क्रम atpx */
		adev->runpm = true;
		dev_info(adev->dev, "Using ATPX for runtime pm\n");
	पूर्ण अन्यथा अगर (amdgpu_device_supports_boco(dev) &&
		   (amdgpu_runसमय_pm != 0)) अणु /* enable runpm by शेष क्रम boco */
		adev->runpm = true;
		dev_info(adev->dev, "Using BOCO for runtime pm\n");
	पूर्ण अन्यथा अगर (amdgpu_device_supports_baco(dev) &&
		   (amdgpu_runसमय_pm != 0)) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_VEGA20:
		हाल CHIP_ARCTURUS:
			/* enable runpm अगर runpm=1 */
			अगर (amdgpu_runसमय_pm > 0)
				adev->runpm = true;
			अवरोध;
		हाल CHIP_VEGA10:
			/* turn runpm on अगर noretry=0 */
			अगर (!adev->gmc.noretry)
				adev->runpm = true;
			अवरोध;
		शेष:
			/* enable runpm on CI+ */
			adev->runpm = true;
			अवरोध;
		पूर्ण
		अगर (adev->runpm)
			dev_info(adev->dev, "Using BACO for runtime pm\n");
	पूर्ण

	/* Call ACPI methods: require modeset init
	 * but failure is not fatal
	 */

	acpi_status = amdgpu_acpi_init(adev);
	अगर (acpi_status)
		dev_dbg(dev->dev, "Error during ACPI methods call\n");

	अगर (adev->runpm) अणु
		/* only need to skip on ATPX */
		अगर (amdgpu_device_supports_px(dev))
			dev_pm_set_driver_flags(dev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);
		/* we want direct complete क्रम BOCO */
		अगर (amdgpu_device_supports_boco(dev))
			dev_pm_set_driver_flags(dev->dev, DPM_FLAG_SMART_PREPARE |
						DPM_FLAG_SMART_SUSPEND |
						DPM_FLAG_MAY_SKIP_RESUME);
		pm_runसमय_use_स्वतःsuspend(dev->dev);
		pm_runसमय_set_स्वतःsuspend_delay(dev->dev, 5000);
		pm_runसमय_allow(dev->dev);
		pm_runसमय_mark_last_busy(dev->dev);
		pm_runसमय_put_स्वतःsuspend(dev->dev);
	पूर्ण

out:
	अगर (r) अणु
		/* balance pm_runसमय_get_sync in amdgpu_driver_unload_kms */
		अगर (adev->rmmio && adev->runpm)
			pm_runसमय_put_noidle(dev->dev);
		amdgpu_driver_unload_kms(dev);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_firmware_info(काष्ठा drm_amdgpu_info_firmware *fw_info,
				काष्ठा drm_amdgpu_query_fw *query_fw,
				काष्ठा amdgpu_device *adev)
अणु
	चयन (query_fw->fw_type) अणु
	हाल AMDGPU_INFO_FW_VCE:
		fw_info->ver = adev->vce.fw_version;
		fw_info->feature = adev->vce.fb_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_UVD:
		fw_info->ver = adev->uvd.fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_VCN:
		fw_info->ver = adev->vcn.fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_GMC:
		fw_info->ver = adev->gmc.fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_ME:
		fw_info->ver = adev->gfx.me_fw_version;
		fw_info->feature = adev->gfx.me_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_PFP:
		fw_info->ver = adev->gfx.pfp_fw_version;
		fw_info->feature = adev->gfx.pfp_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_CE:
		fw_info->ver = adev->gfx.ce_fw_version;
		fw_info->feature = adev->gfx.ce_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_RLC:
		fw_info->ver = adev->gfx.rlc_fw_version;
		fw_info->feature = adev->gfx.rlc_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_CNTL:
		fw_info->ver = adev->gfx.rlc_srlc_fw_version;
		fw_info->feature = adev->gfx.rlc_srlc_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_GPM_MEM:
		fw_info->ver = adev->gfx.rlc_srlg_fw_version;
		fw_info->feature = adev->gfx.rlc_srlg_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_SRM_MEM:
		fw_info->ver = adev->gfx.rlc_srls_fw_version;
		fw_info->feature = adev->gfx.rlc_srls_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_GFX_MEC:
		अगर (query_fw->index == 0) अणु
			fw_info->ver = adev->gfx.mec_fw_version;
			fw_info->feature = adev->gfx.mec_feature_version;
		पूर्ण अन्यथा अगर (query_fw->index == 1) अणु
			fw_info->ver = adev->gfx.mec2_fw_version;
			fw_info->feature = adev->gfx.mec2_feature_version;
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल AMDGPU_INFO_FW_SMC:
		fw_info->ver = adev->pm.fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_TA:
		चयन (query_fw->index) अणु
		हाल TA_FW_TYPE_PSP_XGMI:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_xgmi_ucode_version;
			अवरोध;
		हाल TA_FW_TYPE_PSP_RAS:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_ras_ucode_version;
			अवरोध;
		हाल TA_FW_TYPE_PSP_HDCP:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_hdcp_ucode_version;
			अवरोध;
		हाल TA_FW_TYPE_PSP_DTM:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_dपंचांग_ucode_version;
			अवरोध;
		हाल TA_FW_TYPE_PSP_RAP:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_rap_ucode_version;
			अवरोध;
		हाल TA_FW_TYPE_PSP_SECUREDISPLAY:
			fw_info->ver = adev->psp.ta_fw_version;
			fw_info->feature = adev->psp.ta_securedisplay_ucode_version;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AMDGPU_INFO_FW_SDMA:
		अगर (query_fw->index >= adev->sdma.num_instances)
			वापस -EINVAL;
		fw_info->ver = adev->sdma.instance[query_fw->index].fw_version;
		fw_info->feature = adev->sdma.instance[query_fw->index].feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_SOS:
		fw_info->ver = adev->psp.sos_fw_version;
		fw_info->feature = adev->psp.sos_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_ASD:
		fw_info->ver = adev->psp.asd_fw_version;
		fw_info->feature = adev->psp.asd_feature_version;
		अवरोध;
	हाल AMDGPU_INFO_FW_DMCU:
		fw_info->ver = adev->dm.dmcu_fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_DMCUB:
		fw_info->ver = adev->dm.dmcub_fw_version;
		fw_info->feature = 0;
		अवरोध;
	हाल AMDGPU_INFO_FW_TOC:
		fw_info->ver = adev->psp.toc_fw_version;
		fw_info->feature = adev->psp.toc_feature_version;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_hw_ip_info(काष्ठा amdgpu_device *adev,
			     काष्ठा drm_amdgpu_info *info,
			     काष्ठा drm_amdgpu_info_hw_ip *result)
अणु
	uपूर्णांक32_t ib_start_alignment = 0;
	uपूर्णांक32_t ib_size_alignment = 0;
	क्रमागत amd_ip_block_type type;
	अचिन्हित पूर्णांक num_rings = 0;
	अचिन्हित पूर्णांक i, j;

	अगर (info->query_hw_ip.ip_instance >= AMDGPU_HW_IP_INSTANCE_MAX_COUNT)
		वापस -EINVAL;

	चयन (info->query_hw_ip.type) अणु
	हाल AMDGPU_HW_IP_GFX:
		type = AMD_IP_BLOCK_TYPE_GFX;
		क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++)
			अगर (adev->gfx.gfx_ring[i].sched.पढ़ोy)
				++num_rings;
		ib_start_alignment = 32;
		ib_size_alignment = 32;
		अवरोध;
	हाल AMDGPU_HW_IP_COMPUTE:
		type = AMD_IP_BLOCK_TYPE_GFX;
		क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
			अगर (adev->gfx.compute_ring[i].sched.पढ़ोy)
				++num_rings;
		ib_start_alignment = 32;
		ib_size_alignment = 32;
		अवरोध;
	हाल AMDGPU_HW_IP_DMA:
		type = AMD_IP_BLOCK_TYPE_SDMA;
		क्रम (i = 0; i < adev->sdma.num_instances; i++)
			अगर (adev->sdma.instance[i].ring.sched.पढ़ोy)
				++num_rings;
		ib_start_alignment = 256;
		ib_size_alignment = 4;
		अवरोध;
	हाल AMDGPU_HW_IP_UVD:
		type = AMD_IP_BLOCK_TYPE_UVD;
		क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
			अगर (adev->uvd.harvest_config & (1 << i))
				जारी;

			अगर (adev->uvd.inst[i].ring.sched.पढ़ोy)
				++num_rings;
		पूर्ण
		ib_start_alignment = 64;
		ib_size_alignment = 64;
		अवरोध;
	हाल AMDGPU_HW_IP_VCE:
		type = AMD_IP_BLOCK_TYPE_VCE;
		क्रम (i = 0; i < adev->vce.num_rings; i++)
			अगर (adev->vce.ring[i].sched.पढ़ोy)
				++num_rings;
		ib_start_alignment = 4;
		ib_size_alignment = 1;
		अवरोध;
	हाल AMDGPU_HW_IP_UVD_ENC:
		type = AMD_IP_BLOCK_TYPE_UVD;
		क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
			अगर (adev->uvd.harvest_config & (1 << i))
				जारी;

			क्रम (j = 0; j < adev->uvd.num_enc_rings; j++)
				अगर (adev->uvd.inst[i].ring_enc[j].sched.पढ़ोy)
					++num_rings;
		पूर्ण
		ib_start_alignment = 64;
		ib_size_alignment = 64;
		अवरोध;
	हाल AMDGPU_HW_IP_VCN_DEC:
		type = AMD_IP_BLOCK_TYPE_VCN;
		क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
			अगर (adev->uvd.harvest_config & (1 << i))
				जारी;

			अगर (adev->vcn.inst[i].ring_dec.sched.पढ़ोy)
				++num_rings;
		पूर्ण
		ib_start_alignment = 16;
		ib_size_alignment = 16;
		अवरोध;
	हाल AMDGPU_HW_IP_VCN_ENC:
		type = AMD_IP_BLOCK_TYPE_VCN;
		क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
			अगर (adev->uvd.harvest_config & (1 << i))
				जारी;

			क्रम (j = 0; j < adev->vcn.num_enc_rings; j++)
				अगर (adev->vcn.inst[i].ring_enc[j].sched.पढ़ोy)
					++num_rings;
		पूर्ण
		ib_start_alignment = 64;
		ib_size_alignment = 1;
		अवरोध;
	हाल AMDGPU_HW_IP_VCN_JPEG:
		type = (amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_JPEG)) ?
			AMD_IP_BLOCK_TYPE_JPEG : AMD_IP_BLOCK_TYPE_VCN;

		क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; i++) अणु
			अगर (adev->jpeg.harvest_config & (1 << i))
				जारी;

			अगर (adev->jpeg.inst[i].ring_dec.sched.पढ़ोy)
				++num_rings;
		पूर्ण
		ib_start_alignment = 16;
		ib_size_alignment = 16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < adev->num_ip_blocks; i++)
		अगर (adev->ip_blocks[i].version->type == type &&
		    adev->ip_blocks[i].status.valid)
			अवरोध;

	अगर (i == adev->num_ip_blocks)
		वापस 0;

	num_rings = min(amdgpu_ctx_num_entities[info->query_hw_ip.type],
			num_rings);

	result->hw_ip_version_major = adev->ip_blocks[i].version->major;
	result->hw_ip_version_minor = adev->ip_blocks[i].version->minor;
	result->capabilities_flags = 0;
	result->available_rings = (1 << num_rings) - 1;
	result->ib_start_alignment = ib_start_alignment;
	result->ib_size_alignment = ib_size_alignment;
	वापस 0;
पूर्ण

/*
 * Userspace get inक्रमmation ioctl
 */
/**
 * amdgpu_info_ioctl - answer a device specअगरic request.
 *
 * @dev: drm device poपूर्णांकer
 * @data: request object
 * @filp: drm filp
 *
 * This function is used to pass device specअगरic parameters to the userspace
 * drivers.  Examples include: pci device id, pipeline parms, tiling params,
 * etc. (all asics).
 * Returns 0 on success, -EINVAL on failure.
 */
पूर्णांक amdgpu_info_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_amdgpu_info *info = data;
	काष्ठा amdgpu_mode_info *minfo = &adev->mode_info;
	व्योम __user *out = (व्योम __user *)(uपूर्णांकptr_t)info->वापस_poपूर्णांकer;
	uपूर्णांक32_t size = info->वापस_size;
	काष्ठा drm_crtc *crtc;
	uपूर्णांक32_t ui32 = 0;
	uपूर्णांक64_t ui64 = 0;
	पूर्णांक i, found;
	पूर्णांक ui32_size = माप(ui32);

	अगर (!info->वापस_size || !info->वापस_poपूर्णांकer)
		वापस -EINVAL;

	चयन (info->query) अणु
	हाल AMDGPU_INFO_ACCEL_WORKING:
		ui32 = adev->accel_working;
		वापस copy_to_user(out, &ui32, min(size, 4u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_CRTC_FROM_ID:
		क्रम (i = 0, found = 0; i < adev->mode_info.num_crtc; i++) अणु
			crtc = (काष्ठा drm_crtc *)minfo->crtcs[i];
			अगर (crtc && crtc->base.id == info->mode_crtc.id) अणु
				काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
				ui32 = amdgpu_crtc->crtc_id;
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found) अणु
			DRM_DEBUG_KMS("unknown crtc id %d\n", info->mode_crtc.id);
			वापस -EINVAL;
		पूर्ण
		वापस copy_to_user(out, &ui32, min(size, 4u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_HW_IP_INFO: अणु
		काष्ठा drm_amdgpu_info_hw_ip ip = अणुपूर्ण;
		पूर्णांक ret;

		ret = amdgpu_hw_ip_info(adev, info, &ip);
		अगर (ret)
			वापस ret;

		ret = copy_to_user(out, &ip, min((माप_प्रकार)size, माप(ip)));
		वापस ret ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_HW_IP_COUNT: अणु
		क्रमागत amd_ip_block_type type;
		uपूर्णांक32_t count = 0;

		चयन (info->query_hw_ip.type) अणु
		हाल AMDGPU_HW_IP_GFX:
			type = AMD_IP_BLOCK_TYPE_GFX;
			अवरोध;
		हाल AMDGPU_HW_IP_COMPUTE:
			type = AMD_IP_BLOCK_TYPE_GFX;
			अवरोध;
		हाल AMDGPU_HW_IP_DMA:
			type = AMD_IP_BLOCK_TYPE_SDMA;
			अवरोध;
		हाल AMDGPU_HW_IP_UVD:
			type = AMD_IP_BLOCK_TYPE_UVD;
			अवरोध;
		हाल AMDGPU_HW_IP_VCE:
			type = AMD_IP_BLOCK_TYPE_VCE;
			अवरोध;
		हाल AMDGPU_HW_IP_UVD_ENC:
			type = AMD_IP_BLOCK_TYPE_UVD;
			अवरोध;
		हाल AMDGPU_HW_IP_VCN_DEC:
		हाल AMDGPU_HW_IP_VCN_ENC:
			type = AMD_IP_BLOCK_TYPE_VCN;
			अवरोध;
		हाल AMDGPU_HW_IP_VCN_JPEG:
			type = (amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_JPEG)) ?
				AMD_IP_BLOCK_TYPE_JPEG : AMD_IP_BLOCK_TYPE_VCN;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < adev->num_ip_blocks; i++)
			अगर (adev->ip_blocks[i].version->type == type &&
			    adev->ip_blocks[i].status.valid &&
			    count < AMDGPU_HW_IP_INSTANCE_MAX_COUNT)
				count++;

		वापस copy_to_user(out, &count, min(size, 4u)) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_TIMESTAMP:
		ui64 = amdgpu_gfx_get_gpu_घड़ी_counter(adev);
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_FW_VERSION: अणु
		काष्ठा drm_amdgpu_info_firmware fw_info;
		पूर्णांक ret;

		/* We only support one instance of each IP block right now. */
		अगर (info->query_fw.ip_instance != 0)
			वापस -EINVAL;

		ret = amdgpu_firmware_info(&fw_info, &info->query_fw, adev);
		अगर (ret)
			वापस ret;

		वापस copy_to_user(out, &fw_info,
				    min((माप_प्रकार)size, माप(fw_info))) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_NUM_BYTES_MOVED:
		ui64 = atomic64_पढ़ो(&adev->num_bytes_moved);
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_NUM_EVICTIONS:
		ui64 = atomic64_पढ़ो(&adev->num_evictions);
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_NUM_VRAM_CPU_PAGE_FAULTS:
		ui64 = atomic64_पढ़ो(&adev->num_vram_cpu_page_faults);
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_VRAM_USAGE:
		ui64 = amdgpu_vram_mgr_usage(tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM));
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_VIS_VRAM_USAGE:
		ui64 = amdgpu_vram_mgr_vis_usage(tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM));
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_GTT_USAGE:
		ui64 = amdgpu_gtt_mgr_usage(tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT));
		वापस copy_to_user(out, &ui64, min(size, 8u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_GDS_CONFIG: अणु
		काष्ठा drm_amdgpu_info_gds gds_info;

		स_रखो(&gds_info, 0, माप(gds_info));
		gds_info.compute_partition_size = adev->gds.gds_size;
		gds_info.gds_total_size = adev->gds.gds_size;
		gds_info.gws_per_compute_partition = adev->gds.gws_size;
		gds_info.oa_per_compute_partition = adev->gds.oa_size;
		वापस copy_to_user(out, &gds_info,
				    min((माप_प्रकार)size, माप(gds_info))) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_VRAM_GTT: अणु
		काष्ठा drm_amdgpu_info_vram_gtt vram_gtt;

		vram_gtt.vram_size = adev->gmc.real_vram_size -
			atomic64_पढ़ो(&adev->vram_pin_size) -
			AMDGPU_VM_RESERVED_VRAM;
		vram_gtt.vram_cpu_accessible_size =
			min(adev->gmc.visible_vram_size -
			    atomic64_पढ़ो(&adev->visible_pin_size),
			    vram_gtt.vram_size);
		vram_gtt.gtt_size = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT)->size;
		vram_gtt.gtt_size *= PAGE_SIZE;
		vram_gtt.gtt_size -= atomic64_पढ़ो(&adev->gart_pin_size);
		वापस copy_to_user(out, &vram_gtt,
				    min((माप_प्रकार)size, माप(vram_gtt))) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_MEMORY: अणु
		काष्ठा drm_amdgpu_memory_info mem;
		काष्ठा tपंचांग_resource_manager *vram_man =
			tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);
		काष्ठा tपंचांग_resource_manager *gtt_man =
			tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT);
		स_रखो(&mem, 0, माप(mem));
		mem.vram.total_heap_size = adev->gmc.real_vram_size;
		mem.vram.usable_heap_size = adev->gmc.real_vram_size -
			atomic64_पढ़ो(&adev->vram_pin_size) -
			AMDGPU_VM_RESERVED_VRAM;
		mem.vram.heap_usage =
			amdgpu_vram_mgr_usage(vram_man);
		mem.vram.max_allocation = mem.vram.usable_heap_size * 3 / 4;

		mem.cpu_accessible_vram.total_heap_size =
			adev->gmc.visible_vram_size;
		mem.cpu_accessible_vram.usable_heap_size =
			min(adev->gmc.visible_vram_size -
			    atomic64_पढ़ो(&adev->visible_pin_size),
			    mem.vram.usable_heap_size);
		mem.cpu_accessible_vram.heap_usage =
			amdgpu_vram_mgr_vis_usage(vram_man);
		mem.cpu_accessible_vram.max_allocation =
			mem.cpu_accessible_vram.usable_heap_size * 3 / 4;

		mem.gtt.total_heap_size = gtt_man->size;
		mem.gtt.total_heap_size *= PAGE_SIZE;
		mem.gtt.usable_heap_size = mem.gtt.total_heap_size -
			atomic64_पढ़ो(&adev->gart_pin_size);
		mem.gtt.heap_usage =
			amdgpu_gtt_mgr_usage(gtt_man);
		mem.gtt.max_allocation = mem.gtt.usable_heap_size * 3 / 4;

		वापस copy_to_user(out, &mem,
				    min((माप_प्रकार)size, माप(mem)))
				    ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_READ_MMR_REG: अणु
		अचिन्हित n, alloc_size;
		uपूर्णांक32_t *regs;
		अचिन्हित se_num = (info->पढ़ो_mmr_reg.instance >>
				   AMDGPU_INFO_MMR_SE_INDEX_SHIFT) &
				  AMDGPU_INFO_MMR_SE_INDEX_MASK;
		अचिन्हित sh_num = (info->पढ़ो_mmr_reg.instance >>
				   AMDGPU_INFO_MMR_SH_INDEX_SHIFT) &
				  AMDGPU_INFO_MMR_SH_INDEX_MASK;

		/* set full masks अगर the userspace set all bits
		 * in the bitfields */
		अगर (se_num == AMDGPU_INFO_MMR_SE_INDEX_MASK)
			se_num = 0xffffffff;
		अन्यथा अगर (se_num >= AMDGPU_GFX_MAX_SE)
			वापस -EINVAL;
		अगर (sh_num == AMDGPU_INFO_MMR_SH_INDEX_MASK)
			sh_num = 0xffffffff;
		अन्यथा अगर (sh_num >= AMDGPU_GFX_MAX_SH_PER_SE)
			वापस -EINVAL;

		अगर (info->पढ़ो_mmr_reg.count > 128)
			वापस -EINVAL;

		regs = kदो_स्मृति_array(info->पढ़ो_mmr_reg.count, माप(*regs), GFP_KERNEL);
		अगर (!regs)
			वापस -ENOMEM;
		alloc_size = info->पढ़ो_mmr_reg.count * माप(*regs);

		amdgpu_gfx_off_ctrl(adev, false);
		क्रम (i = 0; i < info->पढ़ो_mmr_reg.count; i++) अणु
			अगर (amdgpu_asic_पढ़ो_रेजिस्टर(adev, se_num, sh_num,
						      info->पढ़ो_mmr_reg.dword_offset + i,
						      &regs[i])) अणु
				DRM_DEBUG_KMS("unallowed offset %#x\n",
					      info->पढ़ो_mmr_reg.dword_offset + i);
				kमुक्त(regs);
				amdgpu_gfx_off_ctrl(adev, true);
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		amdgpu_gfx_off_ctrl(adev, true);
		n = copy_to_user(out, regs, min(size, alloc_size));
		kमुक्त(regs);
		वापस n ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_DEV_INFO: अणु
		काष्ठा drm_amdgpu_info_device *dev_info;
		uपूर्णांक64_t vm_size;
		पूर्णांक ret;

		dev_info = kzalloc(माप(*dev_info), GFP_KERNEL);
		अगर (!dev_info)
			वापस -ENOMEM;

		dev_info->device_id = adev->pdev->device;
		dev_info->chip_rev = adev->rev_id;
		dev_info->बाह्यal_rev = adev->बाह्यal_rev_id;
		dev_info->pci_rev = adev->pdev->revision;
		dev_info->family = adev->family;
		dev_info->num_shader_engines = adev->gfx.config.max_shader_engines;
		dev_info->num_shader_arrays_per_engine = adev->gfx.config.max_sh_per_se;
		/* वापस all घड़ीs in KHz */
		dev_info->gpu_counter_freq = amdgpu_asic_get_xclk(adev) * 10;
		अगर (adev->pm.dpm_enabled) अणु
			dev_info->max_engine_घड़ी = amdgpu_dpm_get_sclk(adev, false) * 10;
			dev_info->max_memory_घड़ी = amdgpu_dpm_get_mclk(adev, false) * 10;
		पूर्ण अन्यथा अणु
			dev_info->max_engine_घड़ी = adev->घड़ी.शेष_sclk * 10;
			dev_info->max_memory_घड़ी = adev->घड़ी.शेष_mclk * 10;
		पूर्ण
		dev_info->enabled_rb_pipes_mask = adev->gfx.config.backend_enable_mask;
		dev_info->num_rb_pipes = adev->gfx.config.max_backends_per_se *
			adev->gfx.config.max_shader_engines;
		dev_info->num_hw_gfx_contexts = adev->gfx.config.max_hw_contexts;
		dev_info->_pad = 0;
		dev_info->ids_flags = 0;
		अगर (adev->flags & AMD_IS_APU)
			dev_info->ids_flags |= AMDGPU_IDS_FLAGS_FUSION;
		अगर (amdgpu_mcbp || amdgpu_sriov_vf(adev))
			dev_info->ids_flags |= AMDGPU_IDS_FLAGS_PREEMPTION;
		अगर (amdgpu_is_पंचांगz(adev))
			dev_info->ids_flags |= AMDGPU_IDS_FLAGS_TMZ;

		vm_size = adev->vm_manager.max_pfn * AMDGPU_GPU_PAGE_SIZE;
		vm_size -= AMDGPU_VA_RESERVED_SIZE;

		/* Older VCE FW versions are buggy and can handle only 40bits */
		अगर (adev->vce.fw_version &&
		    adev->vce.fw_version < AMDGPU_VCE_FW_53_45)
			vm_size = min(vm_size, 1ULL << 40);

		dev_info->भव_address_offset = AMDGPU_VA_RESERVED_SIZE;
		dev_info->भव_address_max =
			min(vm_size, AMDGPU_GMC_HOLE_START);

		अगर (vm_size > AMDGPU_GMC_HOLE_START) अणु
			dev_info->high_va_offset = AMDGPU_GMC_HOLE_END;
			dev_info->high_va_max = AMDGPU_GMC_HOLE_END | vm_size;
		पूर्ण
		dev_info->भव_address_alignment = max_t(u32, PAGE_SIZE, AMDGPU_GPU_PAGE_SIZE);
		dev_info->pte_fragment_size = (1 << adev->vm_manager.fragment_size) * AMDGPU_GPU_PAGE_SIZE;
		dev_info->gart_page_size = max_t(u32, PAGE_SIZE, AMDGPU_GPU_PAGE_SIZE);
		dev_info->cu_active_number = adev->gfx.cu_info.number;
		dev_info->cu_ao_mask = adev->gfx.cu_info.ao_cu_mask;
		dev_info->ce_ram_size = adev->gfx.ce_ram_size;
		स_नकल(&dev_info->cu_ao_biपंचांगap[0], &adev->gfx.cu_info.ao_cu_biपंचांगap[0],
		       माप(adev->gfx.cu_info.ao_cu_biपंचांगap));
		स_नकल(&dev_info->cu_biपंचांगap[0], &adev->gfx.cu_info.biपंचांगap[0],
		       माप(adev->gfx.cu_info.biपंचांगap));
		dev_info->vram_type = adev->gmc.vram_type;
		dev_info->vram_bit_width = adev->gmc.vram_width;
		dev_info->vce_harvest_config = adev->vce.harvest_config;
		dev_info->gc_द्विगुन_offchip_lds_buf =
			adev->gfx.config.द्विगुन_offchip_lds_buf;
		dev_info->wave_front_size = adev->gfx.cu_info.wave_front_size;
		dev_info->num_shader_visible_vgprs = adev->gfx.config.max_gprs;
		dev_info->num_cu_per_sh = adev->gfx.config.max_cu_per_sh;
		dev_info->num_tcc_blocks = adev->gfx.config.max_texture_channel_caches;
		dev_info->gs_vgt_table_depth = adev->gfx.config.gs_vgt_table_depth;
		dev_info->gs_prim_buffer_depth = adev->gfx.config.gs_prim_buffer_depth;
		dev_info->max_gs_waves_per_vgt = adev->gfx.config.max_gs_thपढ़ोs;

		अगर (adev->family >= AMDGPU_FAMILY_NV)
			dev_info->pa_sc_tile_steering_override =
				adev->gfx.config.pa_sc_tile_steering_override;

		dev_info->tcc_disabled_mask = adev->gfx.config.tcc_disabled_mask;

		ret = copy_to_user(out, dev_info,
				   min((माप_प्रकार)size, माप(*dev_info))) ? -EFAULT : 0;
		kमुक्त(dev_info);
		वापस ret;
	पूर्ण
	हाल AMDGPU_INFO_VCE_CLOCK_TABLE: अणु
		अचिन्हित i;
		काष्ठा drm_amdgpu_info_vce_घड़ी_प्रकारable vce_clk_table = अणुपूर्ण;
		काष्ठा amd_vce_state *vce_state;

		क्रम (i = 0; i < AMDGPU_VCE_CLOCK_TABLE_ENTRIES; i++) अणु
			vce_state = amdgpu_dpm_get_vce_घड़ी_state(adev, i);
			अगर (vce_state) अणु
				vce_clk_table.entries[i].sclk = vce_state->sclk;
				vce_clk_table.entries[i].mclk = vce_state->mclk;
				vce_clk_table.entries[i].eclk = vce_state->evclk;
				vce_clk_table.num_valid_entries++;
			पूर्ण
		पूर्ण

		वापस copy_to_user(out, &vce_clk_table,
				    min((माप_प्रकार)size, माप(vce_clk_table))) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_VBIOS: अणु
		uपूर्णांक32_t bios_size = adev->bios_size;

		चयन (info->vbios_info.type) अणु
		हाल AMDGPU_INFO_VBIOS_SIZE:
			वापस copy_to_user(out, &bios_size,
					min((माप_प्रकार)size, माप(bios_size)))
					? -EFAULT : 0;
		हाल AMDGPU_INFO_VBIOS_IMAGE: अणु
			uपूर्णांक8_t *bios;
			uपूर्णांक32_t bios_offset = info->vbios_info.offset;

			अगर (bios_offset >= bios_size)
				वापस -EINVAL;

			bios = adev->bios + bios_offset;
			वापस copy_to_user(out, bios,
					    min((माप_प्रकार)size, (माप_प्रकार)(bios_size - bios_offset)))
					? -EFAULT : 0;
		पूर्ण
		शेष:
			DRM_DEBUG_KMS("Invalid request %d\n",
					info->vbios_info.type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	हाल AMDGPU_INFO_NUM_HANDLES: अणु
		काष्ठा drm_amdgpu_info_num_handles handle;

		चयन (info->query_hw_ip.type) अणु
		हाल AMDGPU_HW_IP_UVD:
			/* Starting Polaris, we support unlimited UVD handles */
			अगर (adev->asic_type < CHIP_POLARIS10) अणु
				handle.uvd_max_handles = adev->uvd.max_handles;
				handle.uvd_used_handles = amdgpu_uvd_used_handles(adev);

				वापस copy_to_user(out, &handle,
					min((माप_प्रकार)size, माप(handle))) ? -EFAULT : 0;
			पूर्ण अन्यथा अणु
				वापस -ENODATA;
			पूर्ण

			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	हाल AMDGPU_INFO_SENSOR: अणु
		अगर (!adev->pm.dpm_enabled)
			वापस -ENOENT;

		चयन (info->sensor_info.type) अणु
		हाल AMDGPU_INFO_SENSOR_GFX_SCLK:
			/* get sclk in Mhz */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_GFX_SCLK,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			ui32 /= 100;
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_GFX_MCLK:
			/* get mclk in Mhz */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_GFX_MCLK,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			ui32 /= 100;
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_GPU_TEMP:
			/* get temperature in millidegrees C */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_GPU_TEMP,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_GPU_LOAD:
			/* get GPU load */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_GPU_LOAD,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_GPU_AVG_POWER:
			/* get average GPU घातer */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_GPU_POWER,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			ui32 >>= 8;
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_VDDNB:
			/* get VDDNB in millivolts */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_VDDNB,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_VDDGFX:
			/* get VDDGFX in millivolts */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_VDDGFX,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK:
			/* get stable pstate sclk in Mhz */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			ui32 /= 100;
			अवरोध;
		हाल AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_MCLK:
			/* get stable pstate mclk in Mhz */
			अगर (amdgpu_dpm_पढ़ो_sensor(adev,
						   AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK,
						   (व्योम *)&ui32, &ui32_size)) अणु
				वापस -EINVAL;
			पूर्ण
			ui32 /= 100;
			अवरोध;
		शेष:
			DRM_DEBUG_KMS("Invalid request %d\n",
				      info->sensor_info.type);
			वापस -EINVAL;
		पूर्ण
		वापस copy_to_user(out, &ui32, min(size, 4u)) ? -EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_VRAM_LOST_COUNTER:
		ui32 = atomic_पढ़ो(&adev->vram_lost_counter);
		वापस copy_to_user(out, &ui32, min(size, 4u)) ? -EFAULT : 0;
	हाल AMDGPU_INFO_RAS_ENABLED_FEATURES: अणु
		काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);
		uपूर्णांक64_t ras_mask;

		अगर (!ras)
			वापस -EINVAL;
		ras_mask = (uपूर्णांक64_t)ras->supported << 32 | ras->features;

		वापस copy_to_user(out, &ras_mask,
				min_t(u64, size, माप(ras_mask))) ?
			-EFAULT : 0;
	पूर्ण
	हाल AMDGPU_INFO_VIDEO_CAPS: अणु
		स्थिर काष्ठा amdgpu_video_codecs *codecs;
		काष्ठा drm_amdgpu_info_video_caps *caps;
		पूर्णांक r;

		चयन (info->video_cap.type) अणु
		हाल AMDGPU_INFO_VIDEO_CAPS_DECODE:
			r = amdgpu_asic_query_video_codecs(adev, false, &codecs);
			अगर (r)
				वापस -EINVAL;
			अवरोध;
		हाल AMDGPU_INFO_VIDEO_CAPS_ENCODE:
			r = amdgpu_asic_query_video_codecs(adev, true, &codecs);
			अगर (r)
				वापस -EINVAL;
			अवरोध;
		शेष:
			DRM_DEBUG_KMS("Invalid request %d\n",
				      info->video_cap.type);
			वापस -EINVAL;
		पूर्ण

		caps = kzalloc(माप(*caps), GFP_KERNEL);
		अगर (!caps)
			वापस -ENOMEM;

		क्रम (i = 0; i < codecs->codec_count; i++) अणु
			पूर्णांक idx = codecs->codec_array[i].codec_type;

			चयन (idx) अणु
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9:
			हाल AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1:
				caps->codec_info[idx].valid = 1;
				caps->codec_info[idx].max_width =
					codecs->codec_array[i].max_width;
				caps->codec_info[idx].max_height =
					codecs->codec_array[i].max_height;
				caps->codec_info[idx].max_pixels_per_frame =
					codecs->codec_array[i].max_pixels_per_frame;
				caps->codec_info[idx].max_level =
					codecs->codec_array[i].max_level;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		r = copy_to_user(out, caps,
				 min((माप_प्रकार)size, माप(*caps))) ? -EFAULT : 0;
		kमुक्त(caps);
		वापस r;
	पूर्ण
	शेष:
		DRM_DEBUG_KMS("Invalid request %d\n", info->query);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Outdated mess क्रम old drm with Xorg being in अक्षरge (व्योम function now).
 */
/**
 * amdgpu_driver_lastबंद_kms - drm callback क्रम last बंद
 *
 * @dev: drm dev poपूर्णांकer
 *
 * Switch vga_चयनeroo state after last बंद (all asics).
 */
व्योम amdgpu_driver_lastबंद_kms(काष्ठा drm_device *dev)
अणु
	drm_fb_helper_lastबंद(dev);
	vga_चयनeroo_process_delayed_चयन();
पूर्ण

/**
 * amdgpu_driver_खोलो_kms - drm callback क्रम खोलो
 *
 * @dev: drm dev poपूर्णांकer
 * @file_priv: drm file
 *
 * On device खोलो, init vm on cayman+ (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_driver_खोलो_kms(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv;
	पूर्णांक r, pasid;

	/* Ensure IB tests are run on ring */
	flush_delayed_work(&adev->delayed_init_work);


	अगर (amdgpu_ras_पूर्णांकr_triggered()) अणु
		DRM_ERROR("RAS Intr triggered, device disabled!!");
		वापस -EHWPOISON;
	पूर्ण

	file_priv->driver_priv = शून्य;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0)
		जाओ pm_put;

	fpriv = kzalloc(माप(*fpriv), GFP_KERNEL);
	अगर (unlikely(!fpriv)) अणु
		r = -ENOMEM;
		जाओ out_suspend;
	पूर्ण

	pasid = amdgpu_pasid_alloc(16);
	अगर (pasid < 0) अणु
		dev_warn(adev->dev, "No more PASIDs available!");
		pasid = 0;
	पूर्ण
	r = amdgpu_vm_init(adev, &fpriv->vm, AMDGPU_VM_CONTEXT_GFX, pasid);
	अगर (r)
		जाओ error_pasid;

	fpriv->prt_va = amdgpu_vm_bo_add(adev, &fpriv->vm, शून्य);
	अगर (!fpriv->prt_va) अणु
		r = -ENOMEM;
		जाओ error_vm;
	पूर्ण

	अगर (amdgpu_mcbp || amdgpu_sriov_vf(adev)) अणु
		uपूर्णांक64_t csa_addr = amdgpu_csa_vaddr(adev) & AMDGPU_GMC_HOLE_MASK;

		r = amdgpu_map_अटल_csa(adev, &fpriv->vm, adev->virt.csa_obj,
						&fpriv->csa_va, csa_addr, AMDGPU_CSA_SIZE);
		अगर (r)
			जाओ error_vm;
	पूर्ण

	mutex_init(&fpriv->bo_list_lock);
	idr_init(&fpriv->bo_list_handles);

	amdgpu_ctx_mgr_init(&fpriv->ctx_mgr);

	file_priv->driver_priv = fpriv;
	जाओ out_suspend;

error_vm:
	amdgpu_vm_fini(adev, &fpriv->vm);

error_pasid:
	अगर (pasid)
		amdgpu_pasid_मुक्त(pasid);

	kमुक्त(fpriv);

out_suspend:
	pm_runसमय_mark_last_busy(dev->dev);
pm_put:
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस r;
पूर्ण

/**
 * amdgpu_driver_postबंद_kms - drm callback क्रम post बंद
 *
 * @dev: drm dev poपूर्णांकer
 * @file_priv: drm file
 *
 * On device post बंद, tear करोwn vm on cayman+ (all asics).
 */
व्योम amdgpu_driver_postबंद_kms(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = file_priv->driver_priv;
	काष्ठा amdgpu_bo_list *list;
	काष्ठा amdgpu_bo *pd;
	u32 pasid;
	पूर्णांक handle;

	अगर (!fpriv)
		वापस;

	pm_runसमय_get_sync(dev->dev);

	अगर (amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_UVD) != शून्य)
		amdgpu_uvd_मुक्त_handles(adev, file_priv);
	अगर (amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_VCE) != शून्य)
		amdgpu_vce_मुक्त_handles(adev, file_priv);

	amdgpu_vm_bo_rmv(adev, fpriv->prt_va);

	अगर (amdgpu_mcbp || amdgpu_sriov_vf(adev)) अणु
		/* TODO: how to handle reserve failure */
		BUG_ON(amdgpu_bo_reserve(adev->virt.csa_obj, true));
		amdgpu_vm_bo_rmv(adev, fpriv->csa_va);
		fpriv->csa_va = शून्य;
		amdgpu_bo_unreserve(adev->virt.csa_obj);
	पूर्ण

	pasid = fpriv->vm.pasid;
	pd = amdgpu_bo_ref(fpriv->vm.root.base.bo);

	amdgpu_ctx_mgr_fini(&fpriv->ctx_mgr);
	amdgpu_vm_fini(adev, &fpriv->vm);

	अगर (pasid)
		amdgpu_pasid_मुक्त_delayed(pd->tbo.base.resv, pasid);
	amdgpu_bo_unref(&pd);

	idr_क्रम_each_entry(&fpriv->bo_list_handles, list, handle)
		amdgpu_bo_list_put(list);

	idr_destroy(&fpriv->bo_list_handles);
	mutex_destroy(&fpriv->bo_list_lock);

	kमुक्त(fpriv);
	file_priv->driver_priv = शून्य;

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
पूर्ण

/*
 * VBlank related functions.
 */
/**
 * amdgpu_get_vblank_counter_kms - get frame count
 *
 * @crtc: crtc to get the frame count from
 *
 * Gets the frame count on the requested crtc (all asics).
 * Returns frame count on success, -EINVAL on failure.
 */
u32 amdgpu_get_vblank_counter_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक vpos, hpos, stat;
	u32 count;

	अगर (pipe >= adev->mode_info.num_crtc) अणु
		DRM_ERROR("Invalid crtc %u\n", pipe);
		वापस -EINVAL;
	पूर्ण

	/* The hw increments its frame counter at start of vsync, not at start
	 * of vblank, as is required by DRM core vblank counter handling.
	 * Cook the hw count here to make it appear to the caller as अगर it
	 * incremented at start of vblank. We measure distance to start of
	 * vblank in vpos. vpos thereक्रमe will be >= 0 between start of vblank
	 * and start of vsync, so vpos >= 0 means to bump the hw frame counter
	 * result by 1 to give the proper appearance to caller.
	 */
	अगर (adev->mode_info.crtcs[pipe]) अणु
		/* Repeat पढ़ोout अगर needed to provide stable result अगर
		 * we cross start of vsync during the queries.
		 */
		करो अणु
			count = amdgpu_display_vblank_get_counter(adev, pipe);
			/* Ask amdgpu_display_get_crtc_scanoutpos to वापस
			 * vpos as distance to start of vblank, instead of
			 * regular vertical scanout pos.
			 */
			stat = amdgpu_display_get_crtc_scanoutpos(
				dev, pipe, GET_DISTANCE_TO_VBLANKSTART,
				&vpos, &hpos, शून्य, शून्य,
				&adev->mode_info.crtcs[pipe]->base.hwmode);
		पूर्ण जबतक (count != amdgpu_display_vblank_get_counter(adev, pipe));

		अगर (((stat & (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE)) !=
		    (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE))) अणु
			DRM_DEBUG_VBL("Query failed! stat %d\n", stat);
		पूर्ण अन्यथा अणु
			DRM_DEBUG_VBL("crtc %d: dist from vblank start %d\n",
				      pipe, vpos);

			/* Bump counter अगर we are at >= leading edge of vblank,
			 * but beक्रमe vsync where vpos would turn negative and
			 * the hw counter really increments.
			 */
			अगर (vpos >= 0)
				count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fallback to use value as is. */
		count = amdgpu_display_vblank_get_counter(adev, pipe);
		DRM_DEBUG_VBL("NULL mode info! Returned count may be wrong.\n");
	पूर्ण

	वापस count;
पूर्ण

/**
 * amdgpu_enable_vblank_kms - enable vblank पूर्णांकerrupt
 *
 * @crtc: crtc to enable vblank पूर्णांकerrupt क्रम
 *
 * Enable the पूर्णांकerrupt on the requested crtc (all asics).
 * Returns 0 on success, -EINVAL on failure.
 */
पूर्णांक amdgpu_enable_vblank_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक idx = amdgpu_display_crtc_idx_to_irq_type(adev, pipe);

	वापस amdgpu_irq_get(adev, &adev->crtc_irq, idx);
पूर्ण

/**
 * amdgpu_disable_vblank_kms - disable vblank पूर्णांकerrupt
 *
 * @crtc: crtc to disable vblank पूर्णांकerrupt क्रम
 *
 * Disable the पूर्णांकerrupt on the requested crtc (all asics).
 */
व्योम amdgpu_disable_vblank_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक idx = amdgpu_display_crtc_idx_to_irq_type(adev, pipe);

	amdgpu_irq_put(adev, &adev->crtc_irq, idx);
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक amdgpu_debugfs_firmware_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_amdgpu_info_firmware fw_info;
	काष्ठा drm_amdgpu_query_fw query_fw;
	काष्ठा atom_context *ctx = adev->mode_info.atom_context;
	पूर्णांक ret, i;

	अटल स्थिर अक्षर *ta_fw_name[TA_FW_TYPE_MAX_INDEX] = अणु
#घोषणा TA_FW_NAME(type) [TA_FW_TYPE_PSP_##type] = #type
		TA_FW_NAME(XGMI),
		TA_FW_NAME(RAS),
		TA_FW_NAME(HDCP),
		TA_FW_NAME(DTM),
		TA_FW_NAME(RAP),
		TA_FW_NAME(SECUREDISPLAY),
#अघोषित TA_FW_NAME
	पूर्ण;

	/* VCE */
	query_fw.fw_type = AMDGPU_INFO_FW_VCE;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "VCE feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* UVD */
	query_fw.fw_type = AMDGPU_INFO_FW_UVD;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "UVD feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* GMC */
	query_fw.fw_type = AMDGPU_INFO_FW_GMC;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "MC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* ME */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_ME;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "ME feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* PFP */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_PFP;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "PFP feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* CE */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_CE;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "CE feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* RLC */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_RLC;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "RLC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* RLC SAVE RESTORE LIST CNTL */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_CNTL;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "RLC SRLC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* RLC SAVE RESTORE LIST GPM MEM */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_GPM_MEM;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "RLC SRLG feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* RLC SAVE RESTORE LIST SRM MEM */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_SRM_MEM;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "RLC SRLS feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* MEC */
	query_fw.fw_type = AMDGPU_INFO_FW_GFX_MEC;
	query_fw.index = 0;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "MEC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* MEC2 */
	अगर (adev->gfx.mec2_fw) अणु
		query_fw.index = 1;
		ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
		अगर (ret)
			वापस ret;
		seq_म_लिखो(m, "MEC2 feature version: %u, firmware version: 0x%08x\n",
			   fw_info.feature, fw_info.ver);
	पूर्ण

	/* PSP SOS */
	query_fw.fw_type = AMDGPU_INFO_FW_SOS;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "SOS feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);


	/* PSP ASD */
	query_fw.fw_type = AMDGPU_INFO_FW_ASD;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "ASD feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	query_fw.fw_type = AMDGPU_INFO_FW_TA;
	क्रम (i = TA_FW_TYPE_PSP_XGMI; i < TA_FW_TYPE_MAX_INDEX; i++) अणु
		query_fw.index = i;
		ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
		अगर (ret)
			जारी;

		seq_म_लिखो(m, "TA %s feature version: 0x%08x, firmware version: 0x%08x\n",
			   ta_fw_name[i], fw_info.feature, fw_info.ver);
	पूर्ण

	/* SMC */
	query_fw.fw_type = AMDGPU_INFO_FW_SMC;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "SMC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* SDMA */
	query_fw.fw_type = AMDGPU_INFO_FW_SDMA;
	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		query_fw.index = i;
		ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
		अगर (ret)
			वापस ret;
		seq_म_लिखो(m, "SDMA%d feature version: %u, firmware version: 0x%08x\n",
			   i, fw_info.feature, fw_info.ver);
	पूर्ण

	/* VCN */
	query_fw.fw_type = AMDGPU_INFO_FW_VCN;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "VCN feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* DMCU */
	query_fw.fw_type = AMDGPU_INFO_FW_DMCU;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "DMCU feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* DMCUB */
	query_fw.fw_type = AMDGPU_INFO_FW_DMCUB;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "DMCUB feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	/* TOC */
	query_fw.fw_type = AMDGPU_INFO_FW_TOC;
	ret = amdgpu_firmware_info(&fw_info, &query_fw, adev);
	अगर (ret)
		वापस ret;
	seq_म_लिखो(m, "TOC feature version: %u, firmware version: 0x%08x\n",
		   fw_info.feature, fw_info.ver);

	seq_म_लिखो(m, "VBIOS version: %s\n", ctx->vbios_version);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_firmware_info);

#पूर्ण_अगर

व्योम amdgpu_debugfs_firmware_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_firmware_info", 0444, root,
			    adev, &amdgpu_debugfs_firmware_info_fops);

#पूर्ण_अगर
पूर्ण
