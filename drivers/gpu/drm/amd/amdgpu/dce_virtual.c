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

#समावेश <drm/drm_vblank.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_i2c.h"
#समावेश "atom.h"
#समावेश "amdgpu_pll.h"
#समावेश "amdgpu_connectors.h"
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
#समावेश "dce_v6_0.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
#समावेश "dce_v8_0.h"
#पूर्ण_अगर
#समावेश "dce_v10_0.h"
#समावेश "dce_v11_0.h"
#समावेश "dce_virtual.h"
#समावेश "ivsrcid/ivsrcid_vislands30.h"
#समावेश "amdgpu_display.h"

#घोषणा DCE_VIRTUAL_VBLANK_PERIOD 16666666


अटल व्योम dce_भव_set_display_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम dce_भव_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक dce_भव_connector_encoder_init(काष्ठा amdgpu_device *adev,
					      पूर्णांक index);
अटल पूर्णांक dce_भव_pageflip(काष्ठा amdgpu_device *adev,
				अचिन्हित crtc_id);
अटल क्रमागत hrसमयr_restart dce_भव_vblank_समयr_handle(काष्ठा hrसमयr *vblank_समयr);
अटल व्योम dce_भव_set_crtc_vblank_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
							पूर्णांक crtc,
							क्रमागत amdgpu_पूर्णांकerrupt_state state);

अटल u32 dce_भव_vblank_get_counter(काष्ठा amdgpu_device *adev, पूर्णांक crtc)
अणु
	वापस 0;
पूर्ण

अटल व्योम dce_भव_page_flip(काष्ठा amdgpu_device *adev,
			      पूर्णांक crtc_id, u64 crtc_base, bool async)
अणु
	वापस;
पूर्ण

अटल पूर्णांक dce_भव_crtc_get_scanoutpos(काष्ठा amdgpu_device *adev, पूर्णांक crtc,
					u32 *vbl, u32 *position)
अणु
	*vbl = 0;
	*position = 0;

	वापस -EINVAL;
पूर्ण

अटल bool dce_भव_hpd_sense(काष्ठा amdgpu_device *adev,
			       क्रमागत amdgpu_hpd_id hpd)
अणु
	वापस true;
पूर्ण

अटल व्योम dce_भव_hpd_set_polarity(काष्ठा amdgpu_device *adev,
				      क्रमागत amdgpu_hpd_id hpd)
अणु
	वापस;
पूर्ण

अटल u32 dce_भव_hpd_get_gpio_reg(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण

/**
 * dce_भव_bandwidth_update - program display watermarks
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Calculate and program the display watermarks and line
 * buffer allocation (CIK).
 */
अटल व्योम dce_भव_bandwidth_update(काष्ठा amdgpu_device *adev)
अणु
	वापस;
पूर्ण

अटल पूर्णांक dce_भव_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red,
				      u16 *green, u16 *blue, uपूर्णांक32_t size,
				      काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	वापस 0;
पूर्ण

अटल व्योम dce_भव_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	drm_crtc_cleanup(crtc);
	kमुक्त(amdgpu_crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs dce_भव_crtc_funcs = अणु
	.cursor_set2 = शून्य,
	.cursor_move = शून्य,
	.gamma_set = dce_भव_crtc_gamma_set,
	.set_config = amdgpu_display_crtc_set_config,
	.destroy = dce_भव_crtc_destroy,
	.page_flip_target = amdgpu_display_crtc_page_flip_target,
	.get_vblank_counter = amdgpu_get_vblank_counter_kms,
	.enable_vblank = amdgpu_enable_vblank_kms,
	.disable_vblank = amdgpu_disable_vblank_kms,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल व्योम dce_भव_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	अचिन्हित type;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		amdgpu_crtc->enabled = true;
		/* Make sure VBLANK पूर्णांकerrupts are still enabled */
		type = amdgpu_display_crtc_idx_to_irq_type(adev,
						amdgpu_crtc->crtc_id);
		amdgpu_irq_update(adev, &adev->crtc_irq, type);
		drm_crtc_vblank_on(crtc);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		drm_crtc_vblank_off(crtc);
		amdgpu_crtc->enabled = false;
		अवरोध;
	पूर्ण
पूर्ण


अटल व्योम dce_भव_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	dce_भव_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम dce_भव_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	dce_भव_crtc_dpms(crtc, DRM_MODE_DPMS_ON);
पूर्ण

अटल व्योम dce_भव_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;

	अगर (dev->num_crtcs)
		drm_crtc_vblank_off(crtc);

	amdgpu_crtc->enabled = false;
	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->encoder = शून्य;
	amdgpu_crtc->connector = शून्य;
पूर्ण

अटल पूर्णांक dce_भव_crtc_mode_set(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode,
				  पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	/* update the hw version fpr dpm */
	amdgpu_crtc->hw_mode = *adjusted_mode;

	वापस 0;
पूर्ण

अटल bool dce_भव_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				     स्थिर काष्ठा drm_display_mode *mode,
				     काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस true;
पूर्ण


अटल पूर्णांक dce_भव_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
				  काष्ठा drm_framebuffer *old_fb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_framebuffer *fb,
					 पूर्णांक x, पूर्णांक y, क्रमागत mode_set_atomic state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs dce_भव_crtc_helper_funcs = अणु
	.dpms = dce_भव_crtc_dpms,
	.mode_fixup = dce_भव_crtc_mode_fixup,
	.mode_set = dce_भव_crtc_mode_set,
	.mode_set_base = dce_भव_crtc_set_base,
	.mode_set_base_atomic = dce_भव_crtc_set_base_atomic,
	.prepare = dce_भव_crtc_prepare,
	.commit = dce_भव_crtc_commit,
	.disable = dce_भव_crtc_disable,
	.get_scanout_position = amdgpu_crtc_get_scanout_position,
पूर्ण;

अटल पूर्णांक dce_भव_crtc_init(काष्ठा amdgpu_device *adev, पूर्णांक index)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc;

	amdgpu_crtc = kzalloc(माप(काष्ठा amdgpu_crtc) +
			      (AMDGPUFB_CONN_LIMIT * माप(काष्ठा drm_connector *)), GFP_KERNEL);
	अगर (amdgpu_crtc == शून्य)
		वापस -ENOMEM;

	drm_crtc_init(adev_to_drm(adev), &amdgpu_crtc->base, &dce_भव_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&amdgpu_crtc->base, 256);
	amdgpu_crtc->crtc_id = index;
	adev->mode_info.crtcs[index] = amdgpu_crtc;

	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->encoder = शून्य;
	amdgpu_crtc->connector = शून्य;
	amdgpu_crtc->vsync_समयr_enabled = AMDGPU_IRQ_STATE_DISABLE;
	drm_crtc_helper_add(&amdgpu_crtc->base, &dce_भव_crtc_helper_funcs);

	hrसमयr_init(&amdgpu_crtc->vblank_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrसमयr_set_expires(&amdgpu_crtc->vblank_समयr, DCE_VIRTUAL_VBLANK_PERIOD);
	amdgpu_crtc->vblank_समयr.function = dce_भव_vblank_समयr_handle;
	hrसमयr_start(&amdgpu_crtc->vblank_समयr,
		      DCE_VIRTUAL_VBLANK_PERIOD, HRTIMER_MODE_REL);
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	dce_भव_set_display_funcs(adev);
	dce_भव_set_irq_funcs(adev);

	adev->mode_info.num_hpd = 1;
	adev->mode_info.num_dig = 1;
	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder *
dce_भव_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_VIRTUAL)
			वापस encoder;
	पूर्ण

	/* pick the first one */
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

अटल पूर्णांक dce_भव_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode = शून्य;
	अचिन्हित i;
	अटल स्थिर काष्ठा mode_size अणु
		पूर्णांक w;
		पूर्णांक h;
	पूर्ण common_modes[] = अणु
		अणु 640,  480पूर्ण,
		अणु 720,  480पूर्ण,
		अणु 800,  600पूर्ण,
		अणु 848,  480पूर्ण,
		अणु1024,  768पूर्ण,
		अणु1152,  768पूर्ण,
		अणु1280,  720पूर्ण,
		अणु1280,  800पूर्ण,
		अणु1280,  854पूर्ण,
		अणु1280,  960पूर्ण,
		अणु1280, 1024पूर्ण,
		अणु1440,  900पूर्ण,
		अणु1400, 1050पूर्ण,
		अणु1680, 1050पूर्ण,
		अणु1600, 1200पूर्ण,
		अणु1920, 1080पूर्ण,
		अणु1920, 1200पूर्ण,
		अणु2560, 1440पूर्ण,
		अणु4096, 3112पूर्ण,
		अणु3656, 2664पूर्ण,
		अणु3840, 2160पूर्ण,
		अणु4096, 2160पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(common_modes); i++) अणु
		mode = drm_cvt_mode(dev, common_modes[i].w, common_modes[i].h, 60, false, false, false);
		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status dce_भव_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल पूर्णांक
dce_भव_dpms(काष्ठा drm_connector *connector, पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
dce_भव_set_property(काष्ठा drm_connector *connector,
			 काष्ठा drm_property *property,
			 uपूर्णांक64_t val)
अणु
	वापस 0;
पूर्ण

अटल व्योम dce_भव_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल व्योम dce_भव_क्रमce(काष्ठा drm_connector *connector)
अणु
	वापस;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs dce_भव_connector_helper_funcs = अणु
	.get_modes = dce_भव_get_modes,
	.mode_valid = dce_भव_mode_valid,
	.best_encoder = dce_भव_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs dce_भव_connector_funcs = अणु
	.dpms = dce_भव_dpms,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = dce_भव_set_property,
	.destroy = dce_भव_destroy,
	.क्रमce = dce_भव_क्रमce,
पूर्ण;

अटल पूर्णांक dce_भव_sw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SMU_DISP_TIMER2_TRIGGER, &adev->crtc_irq);
	अगर (r)
		वापस r;

	adev_to_drm(adev)->max_vblank_count = 0;

	adev_to_drm(adev)->mode_config.funcs = &amdgpu_mode_funcs;

	adev_to_drm(adev)->mode_config.max_width = 16384;
	adev_to_drm(adev)->mode_config.max_height = 16384;

	adev_to_drm(adev)->mode_config.preferred_depth = 24;
	adev_to_drm(adev)->mode_config.prefer_shaकरोw = 1;

	adev_to_drm(adev)->mode_config.fb_base = adev->gmc.aper_base;

	r = amdgpu_display_modeset_create_props(adev);
	अगर (r)
		वापस r;

	adev_to_drm(adev)->mode_config.max_width = 16384;
	adev_to_drm(adev)->mode_config.max_height = 16384;

	/* allocate crtcs, encoders, connectors */
	क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
		r = dce_भव_crtc_init(adev, i);
		अगर (r)
			वापस r;
		r = dce_भव_connector_encoder_init(adev, i);
		अगर (r)
			वापस r;
	पूर्ण

	drm_kms_helper_poll_init(adev_to_drm(adev));

	adev->mode_info.mode_config_initialized = true;
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	kमुक्त(adev->mode_info.bios_hardcoded_edid);

	drm_kms_helper_poll_fini(adev_to_drm(adev));

	drm_mode_config_cleanup(adev_to_drm(adev));
	/* clear crtcs poपूर्णांकer to aव्योम dce irq finish routine access मुक्तd data */
	स_रखो(adev->mode_info.crtcs, 0, माप(adev->mode_info.crtcs[0]) * AMDGPU_MAX_CRTCS);
	adev->mode_info.mode_config_initialized = false;
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
		dce_v6_0_disable_dce(adev);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		dce_v8_0_disable_dce(adev);
		अवरोध;
#पूर्ण_अगर
	हाल CHIP_FIJI:
	हाल CHIP_TONGA:
		dce_v10_0_disable_dce(adev);
		अवरोध;
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_VEGAM:
		dce_v11_0_disable_dce(adev);
		अवरोध;
	हाल CHIP_TOPAZ:
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_HAIन_अंक:
#पूर्ण_अगर
		/* no DCE */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i = 0;

	क्रम (i = 0; i<adev->mode_info.num_crtc; i++)
		अगर (adev->mode_info.crtcs[i])
			hrसमयr_cancel(&adev->mode_info.crtcs[i]->vblank_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_display_suspend_helper(adev);
	अगर (r)
		वापस r;
	वापस dce_भव_hw_fini(handle);
पूर्ण

अटल पूर्णांक dce_भव_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = dce_भव_hw_init(handle);
	अगर (r)
		वापस r;
	वापस amdgpu_display_resume_helper(adev);
पूर्ण

अटल bool dce_भव_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक dce_भव_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dce_भव_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs dce_भव_ip_funcs = अणु
	.name = "dce_virtual",
	.early_init = dce_भव_early_init,
	.late_init = शून्य,
	.sw_init = dce_भव_sw_init,
	.sw_fini = dce_भव_sw_fini,
	.hw_init = dce_भव_hw_init,
	.hw_fini = dce_भव_hw_fini,
	.suspend = dce_भव_suspend,
	.resume = dce_भव_resume,
	.is_idle = dce_भव_is_idle,
	.रुको_क्रम_idle = dce_भव_रुको_क्रम_idle,
	.soft_reset = dce_भव_soft_reset,
	.set_घड़ीgating_state = dce_भव_set_घड़ीgating_state,
	.set_घातergating_state = dce_भव_set_घातergating_state,
पूर्ण;

/* these are handled by the primary encoders */
अटल व्योम dce_भव_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	वापस;
पूर्ण

अटल व्योम dce_भव_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	वापस;
पूर्ण

अटल व्योम
dce_भव_encoder_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस;
पूर्ण

अटल व्योम dce_भव_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	वापस;
पूर्ण

अटल व्योम
dce_भव_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	वापस;
पूर्ण

अटल bool dce_भव_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dce_भव_encoder_helper_funcs = अणु
	.dpms = dce_भव_encoder_dpms,
	.mode_fixup = dce_भव_encoder_mode_fixup,
	.prepare = dce_भव_encoder_prepare,
	.mode_set = dce_भव_encoder_mode_set,
	.commit = dce_भव_encoder_commit,
	.disable = dce_भव_encoder_disable,
पूर्ण;

अटल व्योम dce_भव_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs dce_भव_encoder_funcs = अणु
	.destroy = dce_भव_encoder_destroy,
पूर्ण;

अटल पूर्णांक dce_भव_connector_encoder_init(काष्ठा amdgpu_device *adev,
					      पूर्णांक index)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;

	/* add a new encoder */
	encoder = kzalloc(माप(काष्ठा drm_encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस -ENOMEM;
	encoder->possible_crtcs = 1 << index;
	drm_encoder_init(adev_to_drm(adev), encoder, &dce_भव_encoder_funcs,
			 DRM_MODE_ENCODER_VIRTUAL, शून्य);
	drm_encoder_helper_add(encoder, &dce_भव_encoder_helper_funcs);

	connector = kzalloc(माप(काष्ठा drm_connector), GFP_KERNEL);
	अगर (!connector) अणु
		kमुक्त(encoder);
		वापस -ENOMEM;
	पूर्ण

	/* add a new connector */
	drm_connector_init(adev_to_drm(adev), connector, &dce_भव_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector, &dce_भव_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	/* link them */
	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_display_funcs dce_भव_display_funcs = अणु
	.bandwidth_update = &dce_भव_bandwidth_update,
	.vblank_get_counter = &dce_भव_vblank_get_counter,
	.backlight_set_level = शून्य,
	.backlight_get_level = शून्य,
	.hpd_sense = &dce_भव_hpd_sense,
	.hpd_set_polarity = &dce_भव_hpd_set_polarity,
	.hpd_get_gpio_reg = &dce_भव_hpd_get_gpio_reg,
	.page_flip = &dce_भव_page_flip,
	.page_flip_get_scanoutpos = &dce_भव_crtc_get_scanoutpos,
	.add_encoder = शून्य,
	.add_connector = शून्य,
पूर्ण;

अटल व्योम dce_भव_set_display_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->mode_info.funcs = &dce_भव_display_funcs;
पूर्ण

अटल पूर्णांक dce_भव_pageflip(काष्ठा amdgpu_device *adev,
				अचिन्हित crtc_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amdgpu_crtc *amdgpu_crtc;
	काष्ठा amdgpu_flip_work *works;

	amdgpu_crtc = adev->mode_info.crtcs[crtc_id];

	अगर (crtc_id >= adev->mode_info.num_crtc) अणु
		DRM_ERROR("invalid pageflip crtc %d\n", crtc_id);
		वापस -EINVAL;
	पूर्ण

	/* IRQ could occur when in initial stage */
	अगर (amdgpu_crtc == शून्य)
		वापस 0;

	spin_lock_irqsave(&adev_to_drm(adev)->event_lock, flags);
	works = amdgpu_crtc->pflip_works;
	अगर (amdgpu_crtc->pflip_status != AMDGPU_FLIP_SUBMITTED) अणु
		DRM_DEBUG_DRIVER("amdgpu_crtc->pflip_status = %d != "
			"AMDGPU_FLIP_SUBMITTED(%d)\n",
			amdgpu_crtc->pflip_status,
			AMDGPU_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);
		वापस 0;
	पूर्ण

	/* page flip completed. clean up */
	amdgpu_crtc->pflip_status = AMDGPU_FLIP_NONE;
	amdgpu_crtc->pflip_works = शून्य;

	/* wakeup usersapce */
	अगर (works->event)
		drm_crtc_send_vblank_event(&amdgpu_crtc->base, works->event);

	spin_unlock_irqrestore(&adev_to_drm(adev)->event_lock, flags);

	drm_crtc_vblank_put(&amdgpu_crtc->base);
	amdgpu_bo_unref(&works->old_abo);
	kमुक्त(works->shared);
	kमुक्त(works);

	वापस 0;
पूर्ण

अटल क्रमागत hrसमयr_restart dce_भव_vblank_समयr_handle(काष्ठा hrसमयr *vblank_समयr)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = container_of(vblank_समयr,
						       काष्ठा amdgpu_crtc, vblank_समयr);
	काष्ठा drm_device *ddev = amdgpu_crtc->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा amdgpu_irq_src *source = adev->irq.client[AMDGPU_IRQ_CLIENTID_LEGACY].sources
		[VISLANDS30_IV_SRCID_SMU_DISP_TIMER2_TRIGGER];
	पूर्णांक irq_type = amdgpu_display_crtc_idx_to_irq_type(adev,
						amdgpu_crtc->crtc_id);

	अगर (amdgpu_irq_enabled(adev, source, irq_type)) अणु
		drm_handle_vblank(ddev, amdgpu_crtc->crtc_id);
		dce_भव_pageflip(adev, amdgpu_crtc->crtc_id);
	पूर्ण
	hrसमयr_start(vblank_समयr, DCE_VIRTUAL_VBLANK_PERIOD,
		      HRTIMER_MODE_REL);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम dce_भव_set_crtc_vblank_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
							पूर्णांक crtc,
							क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	अगर (crtc >= adev->mode_info.num_crtc || !adev->mode_info.crtcs[crtc]) अणु
		DRM_DEBUG("invalid crtc %d\n", crtc);
		वापस;
	पूर्ण

	adev->mode_info.crtcs[crtc]->vsync_समयr_enabled = state;
	DRM_DEBUG("[FM]set crtc %d vblank interrupt state %d\n", crtc, state);
पूर्ण


अटल पूर्णांक dce_भव_set_crtc_irq_state(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_irq_src *source,
					  अचिन्हित type,
					  क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	अगर (type > AMDGPU_CRTC_IRQ_VBLANK6)
		वापस -EINVAL;

	dce_भव_set_crtc_vblank_पूर्णांकerrupt_state(adev, type, state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dce_भव_crtc_irq_funcs = अणु
	.set = dce_भव_set_crtc_irq_state,
	.process = शून्य,
पूर्ण;

अटल व्योम dce_भव_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->crtc_irq.num_types = AMDGPU_CRTC_IRQ_VBLANK6 + 1;
	adev->crtc_irq.funcs = &dce_भव_crtc_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version dce_भव_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_DCE,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &dce_भव_ip_funcs,
पूर्ण;
