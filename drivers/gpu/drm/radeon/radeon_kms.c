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

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_drv.h"
#समावेश "radeon_kms.h"

#अगर defined(CONFIG_VGA_SWITCHEROO)
bool radeon_has_atpx(व्योम);
#अन्यथा
अटल अंतरभूत bool radeon_has_atpx(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

/**
 * radeon_driver_unload_kms - Main unload function क्रम KMS.
 *
 * @dev: drm dev poपूर्णांकer
 *
 * This is the मुख्य unload function क्रम KMS (all asics).
 * It calls radeon_modeset_fini() to tear करोwn the
 * displays, and radeon_device_fini() to tear करोwn
 * the rest of the device (CP, ग_लिखोback, etc.).
 * Returns 0 on success.
 */
व्योम radeon_driver_unload_kms(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (rdev == शून्य)
		वापस;

	अगर (rdev->rmmio == शून्य)
		जाओ करोne_मुक्त;

	अगर (radeon_is_px(dev)) अणु
		pm_runसमय_get_sync(dev->dev);
		pm_runसमय_क्रमbid(dev->dev);
	पूर्ण

	radeon_acpi_fini(rdev);

	radeon_modeset_fini(rdev);
	radeon_device_fini(rdev);

	अगर (dev->agp)
		arch_phys_wc_del(dev->agp->agp_mtrr);
	kमुक्त(dev->agp);
	dev->agp = शून्य;

करोne_मुक्त:
	kमुक्त(rdev);
	dev->dev_निजी = शून्य;
पूर्ण

/**
 * radeon_driver_load_kms - Main load function क्रम KMS.
 *
 * @dev: drm dev poपूर्णांकer
 * @flags: device flags
 *
 * This is the मुख्य load function क्रम KMS (all asics).
 * It calls radeon_device_init() to set up the non-display
 * parts of the chip (asic init, CP, ग_लिखोback, etc.), and
 * radeon_modeset_init() to set up the display parts
 * (crtcs, encoders, hotplug detect, etc.).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_driver_load_kms(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा radeon_device *rdev;
	पूर्णांक r, acpi_status;

	rdev = kzalloc(माप(काष्ठा radeon_device), GFP_KERNEL);
	अगर (rdev == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	dev->dev_निजी = (व्योम *)rdev;

#अगर_घोषित __alpha__
	rdev->hose = pdev->sysdata;
#पूर्ण_अगर

	/* update BUS flag */
	अगर (pci_find_capability(pdev, PCI_CAP_ID_AGP)) अणु
		flags |= RADEON_IS_AGP;
	पूर्ण अन्यथा अगर (pci_is_pcie(pdev)) अणु
		flags |= RADEON_IS_PCIE;
	पूर्ण अन्यथा अणु
		flags |= RADEON_IS_PCI;
	पूर्ण

	अगर ((radeon_runसमय_pm != 0) &&
	    radeon_has_atpx() &&
	    ((flags & RADEON_IS_IGP) == 0) &&
	    !pci_is_thunderbolt_attached(pdev))
		flags |= RADEON_IS_PX;

	/* radeon_device_init should report only fatal error
	 * like memory allocation failure or iomapping failure,
	 * or memory manager initialization failure, it must
	 * properly initialize the GPU MC controller and permit
	 * VRAM allocation
	 */
	r = radeon_device_init(rdev, dev, pdev, flags);
	अगर (r) अणु
		dev_err(dev->dev, "Fatal error during GPU init\n");
		जाओ out;
	पूर्ण

	/* Again modeset_init should fail only on fatal error
	 * otherwise it should provide enough functionalities
	 * क्रम shaकरोwfb to run
	 */
	r = radeon_modeset_init(rdev);
	अगर (r)
		dev_err(dev->dev, "Fatal error during modeset init\n");

	/* Call ACPI methods: require modeset init
	 * but failure is not fatal
	 */
	अगर (!r) अणु
		acpi_status = radeon_acpi_init(rdev);
		अगर (acpi_status)
		dev_dbg(dev->dev, "Error during ACPI methods call\n");
	पूर्ण

	अगर (radeon_is_px(dev)) अणु
		dev_pm_set_driver_flags(dev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);
		pm_runसमय_use_स्वतःsuspend(dev->dev);
		pm_runसमय_set_स्वतःsuspend_delay(dev->dev, 5000);
		pm_runसमय_set_active(dev->dev);
		pm_runसमय_allow(dev->dev);
		pm_runसमय_mark_last_busy(dev->dev);
		pm_runसमय_put_स्वतःsuspend(dev->dev);
	पूर्ण

out:
	अगर (r)
		radeon_driver_unload_kms(dev);


	वापस r;
पूर्ण

/**
 * radeon_set_filp_rights - Set filp right.
 *
 * @dev: drm dev poपूर्णांकer
 * @owner: drm file
 * @applier: drm file
 * @value: value
 *
 * Sets the filp rights क्रम the device (all asics).
 */
अटल व्योम radeon_set_filp_rights(काष्ठा drm_device *dev,
				   काष्ठा drm_file **owner,
				   काष्ठा drm_file *applier,
				   uपूर्णांक32_t *value)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	mutex_lock(&rdev->gem.mutex);
	अगर (*value == 1) अणु
		/* wants rights */
		अगर (!*owner)
			*owner = applier;
	पूर्ण अन्यथा अगर (*value == 0) अणु
		/* revokes rights */
		अगर (*owner == applier)
			*owner = शून्य;
	पूर्ण
	*value = *owner == applier ? 1 : 0;
	mutex_unlock(&rdev->gem.mutex);
पूर्ण

/*
 * Userspace get inक्रमmation ioctl
 */
/**
 * radeon_info_ioctl - answer a device specअगरic request.
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
पूर्णांक radeon_info_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_info *info = data;
	काष्ठा radeon_mode_info *minfo = &rdev->mode_info;
	uपूर्णांक32_t *value, value_पंचांगp, *value_ptr, value_size;
	uपूर्णांक64_t value64;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i, found;

	value_ptr = (uपूर्णांक32_t *)((अचिन्हित दीर्घ)info->value);
	value = &value_पंचांगp;
	value_size = माप(uपूर्णांक32_t);

	चयन (info->request) अणु
	हाल RADEON_INFO_DEVICE_ID:
		*value = to_pci_dev(dev->dev)->device;
		अवरोध;
	हाल RADEON_INFO_NUM_GB_PIPES:
		*value = rdev->num_gb_pipes;
		अवरोध;
	हाल RADEON_INFO_NUM_Z_PIPES:
		*value = rdev->num_z_pipes;
		अवरोध;
	हाल RADEON_INFO_ACCEL_WORKING:
		/* xf86-video-ati 6.13.0 relies on this being false क्रम evergreen */
		अगर ((rdev->family >= CHIP_CEDAR) && (rdev->family <= CHIP_HEMLOCK))
			*value = false;
		अन्यथा
			*value = rdev->accel_working;
		अवरोध;
	हाल RADEON_INFO_CRTC_FROM_ID:
		अगर (copy_from_user(value, value_ptr, माप(uपूर्णांक32_t))) अणु
			DRM_ERROR("copy_from_user %s:%u\n", __func__, __LINE__);
			वापस -EFAULT;
		पूर्ण
		क्रम (i = 0, found = 0; i < rdev->num_crtc; i++) अणु
			crtc = (काष्ठा drm_crtc *)minfo->crtcs[i];
			अगर (crtc && crtc->base.id == *value) अणु
				काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
				*value = radeon_crtc->crtc_id;
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found) अणु
			DRM_DEBUG_KMS("unknown crtc id %d\n", *value);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_ACCEL_WORKING2:
		अगर (rdev->family == CHIP_HAWAII) अणु
			अगर (rdev->accel_working) अणु
				अगर (rdev->new_fw)
					*value = 3;
				अन्यथा
					*value = 2;
			पूर्ण अन्यथा अणु
				*value = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			*value = rdev->accel_working;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_TILING_CONFIG:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.tile_config;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.tile_config;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.tile_config;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.tile_config;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.tile_config;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.tile_config;
		अन्यथा अणु
			DRM_DEBUG_KMS("tiling config is r6xx+ only!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_WANT_HYPERZ:
		/* The "value" here is both an input and output parameter.
		 * If the input value is 1, filp requests hyper-z access.
		 * If the input value is 0, filp revokes its hyper-z access.
		 *
		 * When वापसing, the value is 1 अगर filp owns hyper-z access,
		 * 0 otherwise. */
		अगर (copy_from_user(value, value_ptr, माप(uपूर्णांक32_t))) अणु
			DRM_ERROR("copy_from_user %s:%u\n", __func__, __LINE__);
			वापस -EFAULT;
		पूर्ण
		अगर (*value >= 2) अणु
			DRM_DEBUG_KMS("WANT_HYPERZ: invalid value %d\n", *value);
			वापस -EINVAL;
		पूर्ण
		radeon_set_filp_rights(dev, &rdev->hyperz_filp, filp, value);
		अवरोध;
	हाल RADEON_INFO_WANT_CMASK:
		/* The same logic as Hyper-Z. */
		अगर (copy_from_user(value, value_ptr, माप(uपूर्णांक32_t))) अणु
			DRM_ERROR("copy_from_user %s:%u\n", __func__, __LINE__);
			वापस -EFAULT;
		पूर्ण
		अगर (*value >= 2) अणु
			DRM_DEBUG_KMS("WANT_CMASK: invalid value %d\n", *value);
			वापस -EINVAL;
		पूर्ण
		radeon_set_filp_rights(dev, &rdev->cmask_filp, filp, value);
		अवरोध;
	हाल RADEON_INFO_CLOCK_CRYSTAL_FREQ:
		/* वापस घड़ी value in KHz */
		अगर (rdev->asic->get_xclk)
			*value = radeon_get_xclk(rdev) * 10;
		अन्यथा
			*value = rdev->घड़ी.spll.reference_freq * 10;
		अवरोध;
	हाल RADEON_INFO_NUM_BACKENDS:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.max_backends_per_se *
				rdev->config.cik.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.max_backends_per_se *
				rdev->config.si.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.max_backends_per_se *
				rdev->config.cayman.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.max_backends;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.max_backends;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.max_backends;
		अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_NUM_TILE_PIPES:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.max_tile_pipes;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.max_tile_pipes;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.max_tile_pipes;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.max_tile_pipes;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.max_tile_pipes;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.max_tile_pipes;
		अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_FUSION_GART_WORKING:
		*value = 1;
		अवरोध;
	हाल RADEON_INFO_BACKEND_MAP:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.backend_map;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.backend_map;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.backend_map;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.backend_map;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.backend_map;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.backend_map;
		अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_VA_START:
		/* this is where we report अगर vm is supported or not */
		अगर (rdev->family < CHIP_CAYMAN)
			वापस -EINVAL;
		*value = RADEON_VA_RESERVED_SIZE;
		अवरोध;
	हाल RADEON_INFO_IB_VM_MAX_SIZE:
		/* this is where we report अगर vm is supported or not */
		अगर (rdev->family < CHIP_CAYMAN)
			वापस -EINVAL;
		*value = RADEON_IB_VM_MAX_SIZE;
		अवरोध;
	हाल RADEON_INFO_MAX_PIPES:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.max_cu_per_sh;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.max_cu_per_sh;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.max_pipes_per_simd;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.max_pipes;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.max_pipes;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.max_pipes;
		अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_TIMESTAMP:
		अगर (rdev->family < CHIP_R600) अणु
			DRM_DEBUG_KMS("timestamp is r6xx+ only!\n");
			वापस -EINVAL;
		पूर्ण
		value = (uपूर्णांक32_t*)&value64;
		value_size = माप(uपूर्णांक64_t);
		value64 = radeon_get_gpu_घड़ी_counter(rdev);
		अवरोध;
	हाल RADEON_INFO_MAX_SE:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.max_shader_engines;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.num_ses;
		अन्यथा
			*value = 1;
		अवरोध;
	हाल RADEON_INFO_MAX_SH_PER_SE:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.max_sh_per_se;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.max_sh_per_se;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल RADEON_INFO_FASTFB_WORKING:
		*value = rdev->fastfb_working;
		अवरोध;
	हाल RADEON_INFO_RING_WORKING:
		अगर (copy_from_user(value, value_ptr, माप(uपूर्णांक32_t))) अणु
			DRM_ERROR("copy_from_user %s:%u\n", __func__, __LINE__);
			वापस -EFAULT;
		पूर्ण
		चयन (*value) अणु
		हाल RADEON_CS_RING_GFX:
		हाल RADEON_CS_RING_COMPUTE:
			*value = rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy;
			अवरोध;
		हाल RADEON_CS_RING_DMA:
			*value = rdev->ring[R600_RING_TYPE_DMA_INDEX].पढ़ोy;
			*value |= rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX].पढ़ोy;
			अवरोध;
		हाल RADEON_CS_RING_UVD:
			*value = rdev->ring[R600_RING_TYPE_UVD_INDEX].पढ़ोy;
			अवरोध;
		हाल RADEON_CS_RING_VCE:
			*value = rdev->ring[TN_RING_TYPE_VCE1_INDEX].पढ़ोy;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_SI_TILE_MODE_ARRAY:
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			value = rdev->config.cik.tile_mode_array;
			value_size = माप(uपूर्णांक32_t)*32;
		पूर्ण अन्यथा अगर (rdev->family >= CHIP_TAHITI) अणु
			value = rdev->config.si.tile_mode_array;
			value_size = माप(uपूर्णांक32_t)*32;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("tile mode array is si+ only!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_CIK_MACROTILE_MODE_ARRAY:
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			value = rdev->config.cik.macrotile_mode_array;
			value_size = माप(uपूर्णांक32_t)*16;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("macrotile mode array is cik+ only!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_SI_CP_DMA_COMPUTE:
		*value = 1;
		अवरोध;
	हाल RADEON_INFO_SI_BACKEND_ENABLED_MASK:
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			*value = rdev->config.cik.backend_enable_mask;
		पूर्ण अन्यथा अगर (rdev->family >= CHIP_TAHITI) अणु
			*value = rdev->config.si.backend_enable_mask;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("BACKEND_ENABLED_MASK is si+ only!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RADEON_INFO_MAX_SCLK:
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) &&
		    rdev->pm.dpm_enabled)
			*value = rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.sclk * 10;
		अन्यथा
			*value = rdev->pm.शेष_sclk * 10;
		अवरोध;
	हाल RADEON_INFO_VCE_FW_VERSION:
		*value = rdev->vce.fw_version;
		अवरोध;
	हाल RADEON_INFO_VCE_FB_VERSION:
		*value = rdev->vce.fb_version;
		अवरोध;
	हाल RADEON_INFO_NUM_BYTES_MOVED:
		value = (uपूर्णांक32_t*)&value64;
		value_size = माप(uपूर्णांक64_t);
		value64 = atomic64_पढ़ो(&rdev->num_bytes_moved);
		अवरोध;
	हाल RADEON_INFO_VRAM_USAGE:
		value = (uपूर्णांक32_t*)&value64;
		value_size = माप(uपूर्णांक64_t);
		value64 = atomic64_पढ़ो(&rdev->vram_usage);
		अवरोध;
	हाल RADEON_INFO_GTT_USAGE:
		value = (uपूर्णांक32_t*)&value64;
		value_size = माप(uपूर्णांक64_t);
		value64 = atomic64_पढ़ो(&rdev->gtt_usage);
		अवरोध;
	हाल RADEON_INFO_ACTIVE_CU_COUNT:
		अगर (rdev->family >= CHIP_BONAIRE)
			*value = rdev->config.cik.active_cus;
		अन्यथा अगर (rdev->family >= CHIP_TAHITI)
			*value = rdev->config.si.active_cus;
		अन्यथा अगर (rdev->family >= CHIP_CAYMAN)
			*value = rdev->config.cayman.active_simds;
		अन्यथा अगर (rdev->family >= CHIP_CEDAR)
			*value = rdev->config.evergreen.active_simds;
		अन्यथा अगर (rdev->family >= CHIP_RV770)
			*value = rdev->config.rv770.active_simds;
		अन्यथा अगर (rdev->family >= CHIP_R600)
			*value = rdev->config.r600.active_simds;
		अन्यथा
			*value = 1;
		अवरोध;
	हाल RADEON_INFO_CURRENT_GPU_TEMP:
		/* get temperature in millidegrees C */
		अगर (rdev->asic->pm.get_temperature)
			*value = radeon_get_temperature(rdev);
		अन्यथा
			*value = 0;
		अवरोध;
	हाल RADEON_INFO_CURRENT_GPU_SCLK:
		/* get sclk in Mhz */
		अगर (rdev->pm.dpm_enabled)
			*value = radeon_dpm_get_current_sclk(rdev) / 100;
		अन्यथा
			*value = rdev->pm.current_sclk / 100;
		अवरोध;
	हाल RADEON_INFO_CURRENT_GPU_MCLK:
		/* get mclk in Mhz */
		अगर (rdev->pm.dpm_enabled)
			*value = radeon_dpm_get_current_mclk(rdev) / 100;
		अन्यथा
			*value = rdev->pm.current_mclk / 100;
		अवरोध;
	हाल RADEON_INFO_READ_REG:
		अगर (copy_from_user(value, value_ptr, माप(uपूर्णांक32_t))) अणु
			DRM_ERROR("copy_from_user %s:%u\n", __func__, __LINE__);
			वापस -EFAULT;
		पूर्ण
		अगर (radeon_get_allowed_info_रेजिस्टर(rdev, *value, value))
			वापस -EINVAL;
		अवरोध;
	हाल RADEON_INFO_VA_UNMAP_WORKING:
		*value = true;
		अवरोध;
	हाल RADEON_INFO_GPU_RESET_COUNTER:
		*value = atomic_पढ़ो(&rdev->gpu_reset_counter);
		अवरोध;
	शेष:
		DRM_DEBUG_KMS("Invalid request %d\n", info->request);
		वापस -EINVAL;
	पूर्ण
	अगर (copy_to_user(value_ptr, (अक्षर*)value, value_size)) अणु
		DRM_ERROR("copy_to_user %s:%u\n", __func__, __LINE__);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Outdated mess क्रम old drm with Xorg being in अक्षरge (व्योम function now).
 */
/**
 * radeon_driver_lastबंद_kms - drm callback क्रम last बंद
 *
 * @dev: drm dev poपूर्णांकer
 *
 * Switch vga_चयनeroo state after last बंद (all asics).
 */
व्योम radeon_driver_lastबंद_kms(काष्ठा drm_device *dev)
अणु
	drm_fb_helper_lastबंद(dev);
	vga_चयनeroo_process_delayed_चयन();
पूर्ण

/**
 * radeon_driver_खोलो_kms - drm callback क्रम खोलो
 *
 * @dev: drm dev poपूर्णांकer
 * @file_priv: drm file
 *
 * On device खोलो, init vm on cayman+ (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_driver_खोलो_kms(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक r;

	file_priv->driver_priv = शून्य;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस r;
	पूर्ण

	/* new gpu have भव address space support */
	अगर (rdev->family >= CHIP_CAYMAN) अणु
		काष्ठा radeon_fpriv *fpriv;
		काष्ठा radeon_vm *vm;

		fpriv = kzalloc(माप(*fpriv), GFP_KERNEL);
		अगर (unlikely(!fpriv)) अणु
			r = -ENOMEM;
			जाओ out_suspend;
		पूर्ण

		अगर (rdev->accel_working) अणु
			vm = &fpriv->vm;
			r = radeon_vm_init(rdev, vm);
			अगर (r) अणु
				kमुक्त(fpriv);
				जाओ out_suspend;
			पूर्ण

			r = radeon_bo_reserve(rdev->ring_पंचांगp_bo.bo, false);
			अगर (r) अणु
				radeon_vm_fini(rdev, vm);
				kमुक्त(fpriv);
				जाओ out_suspend;
			पूर्ण

			/* map the ib pool buffer पढ़ो only पूर्णांकo
			 * भव address space */
			vm->ib_bo_va = radeon_vm_bo_add(rdev, vm,
							rdev->ring_पंचांगp_bo.bo);
			r = radeon_vm_bo_set_addr(rdev, vm->ib_bo_va,
						  RADEON_VA_IB_OFFSET,
						  RADEON_VM_PAGE_READABLE |
						  RADEON_VM_PAGE_SNOOPED);
			अगर (r) अणु
				radeon_vm_fini(rdev, vm);
				kमुक्त(fpriv);
				जाओ out_suspend;
			पूर्ण
		पूर्ण
		file_priv->driver_priv = fpriv;
	पूर्ण

out_suspend:
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस r;
पूर्ण

/**
 * radeon_driver_postबंद_kms - drm callback क्रम post बंद
 *
 * @dev: drm dev poपूर्णांकer
 * @file_priv: drm file
 *
 * On device बंद, tear करोwn hyperz and cmask filps on r1xx-r5xx
 * (all asics).  And tear करोwn vm on cayman+ (all asics).
 */
व्योम radeon_driver_postबंद_kms(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	pm_runसमय_get_sync(dev->dev);

	mutex_lock(&rdev->gem.mutex);
	अगर (rdev->hyperz_filp == file_priv)
		rdev->hyperz_filp = शून्य;
	अगर (rdev->cmask_filp == file_priv)
		rdev->cmask_filp = शून्य;
	mutex_unlock(&rdev->gem.mutex);

	radeon_uvd_मुक्त_handles(rdev, file_priv);
	radeon_vce_मुक्त_handles(rdev, file_priv);

	/* new gpu have भव address space support */
	अगर (rdev->family >= CHIP_CAYMAN && file_priv->driver_priv) अणु
		काष्ठा radeon_fpriv *fpriv = file_priv->driver_priv;
		काष्ठा radeon_vm *vm = &fpriv->vm;
		पूर्णांक r;

		अगर (rdev->accel_working) अणु
			r = radeon_bo_reserve(rdev->ring_पंचांगp_bo.bo, false);
			अगर (!r) अणु
				अगर (vm->ib_bo_va)
					radeon_vm_bo_rmv(rdev, vm->ib_bo_va);
				radeon_bo_unreserve(rdev->ring_पंचांगp_bo.bo);
			पूर्ण
			radeon_vm_fini(rdev, vm);
		पूर्ण

		kमुक्त(fpriv);
		file_priv->driver_priv = शून्य;
	पूर्ण
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
पूर्ण

/*
 * VBlank related functions.
 */
/**
 * radeon_get_vblank_counter_kms - get frame count
 *
 * @crtc: crtc to get the frame count from
 *
 * Gets the frame count on the requested crtc (all asics).
 * Returns frame count on success, -EINVAL on failure.
 */
u32 radeon_get_vblank_counter_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	पूर्णांक vpos, hpos, stat;
	u32 count;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (pipe >= rdev->num_crtc) अणु
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
	अगर (rdev->mode_info.crtcs[pipe]) अणु
		/* Repeat पढ़ोout अगर needed to provide stable result अगर
		 * we cross start of vsync during the queries.
		 */
		करो अणु
			count = radeon_get_vblank_counter(rdev, pipe);
			/* Ask radeon_get_crtc_scanoutpos to वापस vpos as
			 * distance to start of vblank, instead of regular
			 * vertical scanout pos.
			 */
			stat = radeon_get_crtc_scanoutpos(
				dev, pipe, GET_DISTANCE_TO_VBLANKSTART,
				&vpos, &hpos, शून्य, शून्य,
				&rdev->mode_info.crtcs[pipe]->base.hwmode);
		पूर्ण जबतक (count != radeon_get_vblank_counter(rdev, pipe));

		अगर (((stat & (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE)) !=
		    (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_ACCURATE))) अणु
			DRM_DEBUG_VBL("Query failed! stat %d\n", stat);
		पूर्ण
		अन्यथा अणु
			DRM_DEBUG_VBL("crtc %u: dist from vblank start %d\n",
				      pipe, vpos);

			/* Bump counter अगर we are at >= leading edge of vblank,
			 * but beक्रमe vsync where vpos would turn negative and
			 * the hw counter really increments.
			 */
			अगर (vpos >= 0)
				count++;
		पूर्ण
	पूर्ण
	अन्यथा अणु
	    /* Fallback to use value as is. */
	    count = radeon_get_vblank_counter(rdev, pipe);
	    DRM_DEBUG_VBL("NULL mode info! Returned count may be wrong.\n");
	पूर्ण

	वापस count;
पूर्ण

/**
 * radeon_enable_vblank_kms - enable vblank पूर्णांकerrupt
 *
 * @crtc: crtc to enable vblank पूर्णांकerrupt क्रम
 *
 * Enable the पूर्णांकerrupt on the requested crtc (all asics).
 * Returns 0 on success, -EINVAL on failure.
 */
पूर्णांक radeon_enable_vblank_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक r;

	अगर (pipe >= rdev->num_crtc) अणु
		DRM_ERROR("Invalid crtc %d\n", pipe);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	rdev->irq.crtc_vblank_पूर्णांक[pipe] = true;
	r = radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	वापस r;
पूर्ण

/**
 * radeon_disable_vblank_kms - disable vblank पूर्णांकerrupt
 *
 * @crtc: crtc to disable vblank पूर्णांकerrupt क्रम
 *
 * Disable the पूर्णांकerrupt on the requested crtc (all asics).
 */
व्योम radeon_disable_vblank_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;

	अगर (pipe >= rdev->num_crtc) अणु
		DRM_ERROR("Invalid crtc %d\n", pipe);
		वापस;
	पूर्ण

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	rdev->irq.crtc_vblank_पूर्णांक[pipe] = false;
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
पूर्ण
