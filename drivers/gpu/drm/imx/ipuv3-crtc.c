<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX IPUv3 Graphics driver
 *
 * Copyright (C) 2011 Sascha Hauer, Pengutronix
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/imx-ipu-v3.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "imx-drm.h"
#समावेश "ipuv3-plane.h"

#घोषणा DRIVER_DESC		"i.MX IPUv3 Graphics"

काष्ठा ipu_crtc अणु
	काष्ठा device		*dev;
	काष्ठा drm_crtc		base;

	/* plane[0] is the full plane, plane[1] is the partial plane */
	काष्ठा ipu_plane	*plane[2];

	काष्ठा ipu_dc		*dc;
	काष्ठा ipu_di		*di;
	पूर्णांक			irq;
	काष्ठा drm_pending_vblank_event *event;
पूर्ण;

अटल अंतरभूत काष्ठा ipu_crtc *to_ipu_crtc(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा ipu_crtc, base);
पूर्ण

अटल व्योम ipu_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	काष्ठा ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);

	ipu_prg_enable(ipu);
	ipu_dc_enable(ipu);
	ipu_dc_enable_channel(ipu_crtc->dc);
	ipu_di_enable(ipu_crtc->di);
पूर्ण

अटल व्योम ipu_crtc_disable_planes(काष्ठा ipu_crtc *ipu_crtc,
				    काष्ठा drm_crtc_state *old_crtc_state)
अणु
	bool disable_partial = false;
	bool disable_full = false;
	काष्ठा drm_plane *plane;

	drm_atomic_crtc_state_क्रम_each_plane(plane, old_crtc_state) अणु
		अगर (plane == &ipu_crtc->plane[0]->base)
			disable_full = true;
		अगर (&ipu_crtc->plane[1] && plane == &ipu_crtc->plane[1]->base)
			disable_partial = true;
	पूर्ण

	अगर (disable_partial)
		ipu_plane_disable(ipu_crtc->plane[1], true);
	अगर (disable_full)
		ipu_plane_disable(ipu_crtc->plane[0], true);
पूर्ण

अटल व्योम ipu_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	काष्ठा ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);

	ipu_dc_disable_channel(ipu_crtc->dc);
	ipu_di_disable(ipu_crtc->di);
	/*
	 * Planes must be disabled beक्रमe DC घड़ी is हटाओd, as otherwise the
	 * attached IDMACs will be left in undefined state, possibly hanging
	 * the IPU or even प्रणाली.
	 */
	ipu_crtc_disable_planes(ipu_crtc, old_crtc_state);
	ipu_dc_disable(ipu);
	ipu_prg_disable(ipu);

	drm_crtc_vblank_off(crtc);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event && !crtc->state->active) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल व्योम imx_drm_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा imx_crtc_state *state;

	अगर (crtc->state)
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

	kमुक्त(to_imx_crtc_state(crtc->state));
	crtc->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *imx_drm_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा imx_crtc_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	WARN_ON(state->base.crtc != crtc);
	state->base.crtc = crtc;

	वापस &state->base;
पूर्ण

अटल व्योम imx_drm_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(to_imx_crtc_state(state));
पूर्ण

अटल पूर्णांक ipu_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);

	enable_irq(ipu_crtc->irq);

	वापस 0;
पूर्ण

अटल व्योम ipu_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);

	disable_irq_nosync(ipu_crtc->irq);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs ipu_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = imx_drm_crtc_reset,
	.atomic_duplicate_state = imx_drm_crtc_duplicate_state,
	.atomic_destroy_state = imx_drm_crtc_destroy_state,
	.enable_vblank = ipu_enable_vblank,
	.disable_vblank = ipu_disable_vblank,
पूर्ण;

अटल irqवापस_t ipu_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipu_crtc *ipu_crtc = dev_id;
	काष्ठा drm_crtc *crtc = &ipu_crtc->base;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	drm_crtc_handle_vblank(crtc);

	अगर (ipu_crtc->event) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ipu_crtc->plane); i++) अणु
			काष्ठा ipu_plane *plane = ipu_crtc->plane[i];

			अगर (!plane)
				जारी;

			अगर (ipu_plane_atomic_update_pending(&plane->base))
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(ipu_crtc->plane)) अणु
			spin_lock_irqsave(&crtc->dev->event_lock, flags);
			drm_crtc_send_vblank_event(crtc, ipu_crtc->event);
			ipu_crtc->event = शून्य;
			drm_crtc_vblank_put(crtc);
			spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल bool ipu_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				  स्थिर काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	काष्ठा videomode vm;
	पूर्णांक ret;

	drm_display_mode_to_videomode(adjusted_mode, &vm);

	ret = ipu_di_adjust_videomode(ipu_crtc->di, &vm);
	अगर (ret)
		वापस false;

	अगर ((vm.vsync_len == 0) || (vm.hsync_len == 0))
		वापस false;

	drm_display_mode_from_videomode(&vm, adjusted_mode);

	वापस true;
पूर्ण

अटल पूर्णांक ipu_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	u32 primary_plane_mask = drm_plane_mask(crtc->primary);

	अगर (crtc_state->active && (primary_plane_mask & crtc_state->plane_mask) == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ipu_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम ipu_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);

		WARN_ON(drm_crtc_vblank_get(crtc));
		ipu_crtc->event = crtc->state->event;
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल व्योम ipu_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_encoder *encoder;
	काष्ठा ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc->state);
	काष्ठा ipu_di_संकेत_cfg sig_cfg = अणुपूर्ण;
	अचिन्हित दीर्घ encoder_types = 0;

	dev_dbg(ipu_crtc->dev, "%s: mode->hdisplay: %d\n", __func__,
			mode->hdisplay);
	dev_dbg(ipu_crtc->dev, "%s: mode->vdisplay: %d\n", __func__,
			mode->vdisplay);

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc == crtc)
			encoder_types |= BIT(encoder->encoder_type);
	पूर्ण

	dev_dbg(ipu_crtc->dev, "%s: attached to encoder types 0x%lx\n",
		__func__, encoder_types);

	/*
	 * If we have DAC or LDB, then we need the IPU DI घड़ी to be
	 * the same as the LDB DI घड़ी. For TVDAC, derive the IPU DI
	 * घड़ी from 27 MHz TVE_DI घड़ी, but allow to भागide it.
	 */
	अगर (encoder_types & (BIT(DRM_MODE_ENCODER_DAC) |
			     BIT(DRM_MODE_ENCODER_LVDS)))
		sig_cfg.clkflags = IPU_DI_CLKMODE_SYNC | IPU_DI_CLKMODE_EXT;
	अन्यथा अगर (encoder_types & BIT(DRM_MODE_ENCODER_TVDAC))
		sig_cfg.clkflags = IPU_DI_CLKMODE_EXT;
	अन्यथा
		sig_cfg.clkflags = 0;

	sig_cfg.enable_pol = !(imx_crtc_state->bus_flags & DRM_BUS_FLAG_DE_LOW);
	/* Default to driving pixel data on negative घड़ी edges */
	sig_cfg.clk_pol = !!(imx_crtc_state->bus_flags &
			     DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE);
	sig_cfg.bus_क्रमmat = imx_crtc_state->bus_क्रमmat;
	sig_cfg.v_to_h_sync = 0;
	sig_cfg.hsync_pin = imx_crtc_state->di_hsync_pin;
	sig_cfg.vsync_pin = imx_crtc_state->di_vsync_pin;

	drm_display_mode_to_videomode(mode, &sig_cfg.mode);

	ipu_dc_init_sync(ipu_crtc->dc, ipu_crtc->di,
			 mode->flags & DRM_MODE_FLAG_INTERLACE,
			 imx_crtc_state->bus_क्रमmat, mode->hdisplay);
	ipu_di_init_sync_panel(ipu_crtc->di, &sig_cfg);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs ipu_helper_funcs = अणु
	.mode_fixup = ipu_crtc_mode_fixup,
	.mode_set_nofb = ipu_crtc_mode_set_nofb,
	.atomic_check = ipu_crtc_atomic_check,
	.atomic_begin = ipu_crtc_atomic_begin,
	.atomic_flush = ipu_crtc_atomic_flush,
	.atomic_disable = ipu_crtc_atomic_disable,
	.atomic_enable = ipu_crtc_atomic_enable,
पूर्ण;

अटल व्योम ipu_put_resources(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा ipu_crtc *ipu_crtc = ptr;

	अगर (!IS_ERR_OR_शून्य(ipu_crtc->dc))
		ipu_dc_put(ipu_crtc->dc);
	अगर (!IS_ERR_OR_शून्य(ipu_crtc->di))
		ipu_di_put(ipu_crtc->di);
पूर्ण

अटल पूर्णांक ipu_get_resources(काष्ठा drm_device *dev, काष्ठा ipu_crtc *ipu_crtc,
			     काष्ठा ipu_client_platक्रमmdata *pdata)
अणु
	काष्ठा ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);
	पूर्णांक ret;

	ipu_crtc->dc = ipu_dc_get(ipu, pdata->dc);
	अगर (IS_ERR(ipu_crtc->dc))
		वापस PTR_ERR(ipu_crtc->dc);

	ret = drmm_add_action_or_reset(dev, ipu_put_resources, ipu_crtc);
	अगर (ret)
		वापस ret;

	ipu_crtc->di = ipu_di_get(ipu, pdata->di);
	अगर (IS_ERR(ipu_crtc->di))
		वापस PTR_ERR(ipu_crtc->di);

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_drm_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा ipu_client_platक्रमmdata *pdata = dev->platक्रमm_data;
	काष्ठा ipu_soc *ipu = dev_get_drvdata(dev->parent);
	काष्ठा drm_device *drm = data;
	काष्ठा ipu_plane *primary_plane;
	काष्ठा ipu_crtc *ipu_crtc;
	काष्ठा drm_crtc *crtc;
	पूर्णांक dp = -EINVAL;
	पूर्णांक ret;

	अगर (pdata->dp >= 0)
		dp = IPU_DP_FLOW_SYNC_BG;
	primary_plane = ipu_plane_init(drm, ipu, pdata->dma[0], dp, 0,
				       DRM_PLANE_TYPE_PRIMARY);
	अगर (IS_ERR(primary_plane))
		वापस PTR_ERR(primary_plane);

	ipu_crtc = drmm_crtc_alloc_with_planes(drm, काष्ठा ipu_crtc, base,
					       &primary_plane->base, शून्य,
					       &ipu_crtc_funcs, शून्य);
	अगर (IS_ERR(ipu_crtc))
		वापस PTR_ERR(ipu_crtc);

	ipu_crtc->dev = dev;
	ipu_crtc->plane[0] = primary_plane;

	crtc = &ipu_crtc->base;
	crtc->port = pdata->of_node;
	drm_crtc_helper_add(crtc, &ipu_helper_funcs);

	ret = ipu_get_resources(drm, ipu_crtc, pdata);
	अगर (ret) अणु
		dev_err(ipu_crtc->dev, "getting resources failed with %d.\n",
			ret);
		वापस ret;
	पूर्ण

	/* If this crtc is using the DP, add an overlay plane */
	अगर (pdata->dp >= 0 && pdata->dma[1] > 0) अणु
		ipu_crtc->plane[1] = ipu_plane_init(drm, ipu, pdata->dma[1],
						IPU_DP_FLOW_SYNC_FG,
						drm_crtc_mask(&ipu_crtc->base),
						DRM_PLANE_TYPE_OVERLAY);
		अगर (IS_ERR(ipu_crtc->plane[1]))
			ipu_crtc->plane[1] = शून्य;
	पूर्ण

	ipu_crtc->irq = ipu_plane_irq(ipu_crtc->plane[0]);
	ret = devm_request_irq(ipu_crtc->dev, ipu_crtc->irq, ipu_irq_handler, 0,
			"imx_drm", ipu_crtc);
	अगर (ret < 0) अणु
		dev_err(ipu_crtc->dev, "irq request failed with %d.\n", ret);
		वापस ret;
	पूर्ण
	/* Only enable IRQ when we actually need it to trigger work. */
	disable_irq(ipu_crtc->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा component_ops ipu_crtc_ops = अणु
	.bind = ipu_drm_bind,
पूर्ण;

अटल पूर्णांक ipu_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	अगर (!dev->platक्रमm_data)
		वापस -EINVAL;

	ret = dma_set_coherent_mask(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	वापस component_add(dev, &ipu_crtc_ops);
पूर्ण

अटल पूर्णांक ipu_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &ipu_crtc_ops);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver ipu_drm_driver = अणु
	.driver = अणु
		.name = "imx-ipuv3-crtc",
	पूर्ण,
	.probe = ipu_drm_probe,
	.हटाओ = ipu_drm_हटाओ,
पूर्ण;
