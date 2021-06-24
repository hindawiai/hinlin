<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "fsl_dcu_drm_crtc.h"
#समावेश "fsl_dcu_drm_drv.h"
#समावेश "fsl_dcu_drm_plane.h"

अटल व्योम fsl_dcu_drm_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	regmap_ग_लिखो(fsl_dev->regmap,
		     DCU_UPDATE_MODE, DCU_UPDATE_MODE_READREG);

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल व्योम fsl_dcu_drm_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;

	/* always disable planes on the CRTC */
	drm_atomic_helper_disable_planes_on_crtc(old_crtc_state, true);

	drm_crtc_vblank_off(crtc);

	regmap_update_bits(fsl_dev->regmap, DCU_DCU_MODE,
			   DCU_MODE_DCU_MODE_MASK,
			   DCU_MODE_DCU_MODE(DCU_MODE_OFF));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_UPDATE_MODE,
		     DCU_UPDATE_MODE_READREG);
	clk_disable_unprepare(fsl_dev->pix_clk);
पूर्ण

अटल व्योम fsl_dcu_drm_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;

	clk_prepare_enable(fsl_dev->pix_clk);
	regmap_update_bits(fsl_dev->regmap, DCU_DCU_MODE,
			   DCU_MODE_DCU_MODE_MASK,
			   DCU_MODE_DCU_MODE(DCU_MODE_NORMAL));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_UPDATE_MODE,
		     DCU_UPDATE_MODE_READREG);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम fsl_dcu_drm_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	काष्ठा drm_connector *con = &fsl_dev->connector.base;
	काष्ठा drm_display_mode *mode = &crtc->state->mode;
	अचिन्हित पूर्णांक pol = 0;
	काष्ठा videomode vm;

	clk_set_rate(fsl_dev->pix_clk, mode->घड़ी * 1000);

	drm_display_mode_to_videomode(mode, &vm);

	/* INV_PXCK as शेष (most display sample data on rising edge) */
	अगर (!(con->display_info.bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE))
		pol |= DCU_SYN_POL_INV_PXCK;

	अगर (vm.flags & DISPLAY_FLAGS_HSYNC_LOW)
		pol |= DCU_SYN_POL_INV_HS_LOW;

	अगर (vm.flags & DISPLAY_FLAGS_VSYNC_LOW)
		pol |= DCU_SYN_POL_INV_VS_LOW;

	regmap_ग_लिखो(fsl_dev->regmap, DCU_HSYN_PARA,
		     DCU_HSYN_PARA_BP(vm.hback_porch) |
		     DCU_HSYN_PARA_PW(vm.hsync_len) |
		     DCU_HSYN_PARA_FP(vm.hfront_porch));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_VSYN_PARA,
		     DCU_VSYN_PARA_BP(vm.vback_porch) |
		     DCU_VSYN_PARA_PW(vm.vsync_len) |
		     DCU_VSYN_PARA_FP(vm.vfront_porch));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_DISP_SIZE,
		     DCU_DISP_SIZE_DELTA_Y(vm.vactive) |
		     DCU_DISP_SIZE_DELTA_X(vm.hactive));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_SYN_POL, pol);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_BGND, DCU_BGND_R(0) |
		     DCU_BGND_G(0) | DCU_BGND_B(0));
	regmap_ग_लिखो(fsl_dev->regmap, DCU_DCU_MODE,
		     DCU_MODE_BLEND_ITER(1) | DCU_MODE_RASTER_EN);
	regmap_ग_लिखो(fsl_dev->regmap, DCU_THRESHOLD,
		     DCU_THRESHOLD_LS_BF_VS(BF_VS_VAL) |
		     DCU_THRESHOLD_OUT_BUF_HIGH(BUF_MAX_VAL) |
		     DCU_THRESHOLD_OUT_BUF_LOW(BUF_MIN_VAL));
	वापस;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs fsl_dcu_drm_crtc_helper_funcs = अणु
	.atomic_disable = fsl_dcu_drm_crtc_atomic_disable,
	.atomic_flush = fsl_dcu_drm_crtc_atomic_flush,
	.atomic_enable = fsl_dcu_drm_crtc_atomic_enable,
	.mode_set_nofb = fsl_dcu_drm_crtc_mode_set_nofb,
पूर्ण;

अटल पूर्णांक fsl_dcu_drm_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(fsl_dev->regmap, DCU_INT_MASK, &value);
	value &= ~DCU_INT_MASK_VBLANK;
	regmap_ग_लिखो(fsl_dev->regmap, DCU_INT_MASK, value);

	वापस 0;
पूर्ण

अटल व्योम fsl_dcu_drm_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा fsl_dcu_drm_device *fsl_dev = dev->dev_निजी;
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(fsl_dev->regmap, DCU_INT_MASK, &value);
	value |= DCU_INT_MASK_VBLANK;
	regmap_ग_लिखो(fsl_dev->regmap, DCU_INT_MASK, value);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs fsl_dcu_drm_crtc_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.destroy = drm_crtc_cleanup,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.set_config = drm_atomic_helper_set_config,
	.enable_vblank = fsl_dcu_drm_crtc_enable_vblank,
	.disable_vblank = fsl_dcu_drm_crtc_disable_vblank,
पूर्ण;

पूर्णांक fsl_dcu_drm_crtc_create(काष्ठा fsl_dcu_drm_device *fsl_dev)
अणु
	काष्ठा drm_plane *primary;
	काष्ठा drm_crtc *crtc = &fsl_dev->crtc;
	पूर्णांक ret;

	fsl_dcu_drm_init_planes(fsl_dev->drm);

	primary = fsl_dcu_drm_primary_create_plane(fsl_dev->drm);
	अगर (!primary)
		वापस -ENOMEM;

	ret = drm_crtc_init_with_planes(fsl_dev->drm, crtc, primary, शून्य,
					&fsl_dcu_drm_crtc_funcs, शून्य);
	अगर (ret) अणु
		primary->funcs->destroy(primary);
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(crtc, &fsl_dcu_drm_crtc_helper_funcs);

	वापस 0;
पूर्ण
