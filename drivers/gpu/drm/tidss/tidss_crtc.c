<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_irq.h"
#समावेश "tidss_plane.h"

/* Page flip and frame करोne IRQs */

अटल व्योम tidss_crtc_finish_page_flip(काष्ठा tidss_crtc *tcrtc)
अणु
	काष्ठा drm_device *ddev = tcrtc->crtc.dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा drm_pending_vblank_event *event;
	अचिन्हित दीर्घ flags;
	bool busy;

	spin_lock_irqsave(&ddev->event_lock, flags);

	/*
	 * New settings are taken पूर्णांकo use at VFP, and GO bit is cleared at
	 * the same समय. This happens beक्रमe the vertical blank पूर्णांकerrupt.
	 * So there is a small change that the driver sets GO bit after VFP, but
	 * beक्रमe vblank, and we have to check क्रम that हाल here.
	 */
	busy = dispc_vp_go_busy(tidss->dispc, tcrtc->hw_videoport);
	अगर (busy) अणु
		spin_unlock_irqrestore(&ddev->event_lock, flags);
		वापस;
	पूर्ण

	event = tcrtc->event;
	tcrtc->event = शून्य;

	अगर (!event) अणु
		spin_unlock_irqrestore(&ddev->event_lock, flags);
		वापस;
	पूर्ण

	drm_crtc_send_vblank_event(&tcrtc->crtc, event);

	spin_unlock_irqrestore(&ddev->event_lock, flags);

	drm_crtc_vblank_put(&tcrtc->crtc);
पूर्ण

व्योम tidss_crtc_vblank_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);

	drm_crtc_handle_vblank(crtc);

	tidss_crtc_finish_page_flip(tcrtc);
पूर्ण

व्योम tidss_crtc_frameकरोne_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);

	complete(&tcrtc->frameकरोne_completion);
पूर्ण

व्योम tidss_crtc_error_irq(काष्ठा drm_crtc *crtc, u64 irqstatus)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);

	dev_err_ratelimited(crtc->dev->dev, "CRTC%u SYNC LOST: (irq %llx)\n",
			    tcrtc->hw_videoport, irqstatus);
पूर्ण

/* drm_crtc_helper_funcs */

अटल पूर्णांक tidss_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा dispc_device *dispc = tidss->dispc;
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	u32 hw_videoport = tcrtc->hw_videoport;
	स्थिर काष्ठा drm_display_mode *mode;
	क्रमागत drm_mode_status ok;

	dev_dbg(ddev->dev, "%s\n", __func__);

	अगर (!crtc_state->enable)
		वापस 0;

	mode = &crtc_state->adjusted_mode;

	ok = dispc_vp_mode_valid(dispc, hw_videoport, mode);
	अगर (ok != MODE_OK) अणु
		dev_dbg(ddev->dev, "%s: bad mode: %ux%u pclk %u kHz\n",
			__func__, mode->hdisplay, mode->vdisplay, mode->घड़ी);
		वापस -EINVAL;
	पूर्ण

	वापस dispc_vp_bus_check(dispc, hw_videoport, crtc_state);
पूर्ण

/*
 * This needs all affected planes to be present in the atomic
 * state. The untouched planes are added to the state in
 * tidss_atomic_check().
 */
अटल व्योम tidss_crtc_position_planes(काष्ठा tidss_device *tidss,
				       काष्ठा drm_crtc *crtc,
				       काष्ठा drm_crtc_state *old_state,
				       bool newmodeset)
अणु
	काष्ठा drm_atomic_state *ostate = old_state->state;
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	काष्ठा drm_crtc_state *cstate = crtc->state;
	पूर्णांक layer;

	अगर (!newmodeset && !cstate->zpos_changed &&
	    !to_tidss_crtc_state(cstate)->plane_pos_changed)
		वापस;

	क्रम (layer = 0; layer < tidss->feat->num_planes; layer++) अणु
		काष्ठा drm_plane_state *pstate;
		काष्ठा drm_plane *plane;
		bool layer_active = false;
		पूर्णांक i;

		क्रम_each_new_plane_in_state(ostate, plane, pstate, i) अणु
			अगर (pstate->crtc != crtc || !pstate->visible)
				जारी;

			अगर (pstate->normalized_zpos == layer) अणु
				layer_active = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (layer_active) अणु
			काष्ठा tidss_plane *tplane = to_tidss_plane(plane);

			dispc_ovr_set_plane(tidss->dispc, tplane->hw_plane_id,
					    tcrtc->hw_videoport,
					    pstate->crtc_x, pstate->crtc_y,
					    layer);
		पूर्ण
		dispc_ovr_enable_layer(tidss->dispc, tcrtc->hw_videoport, layer,
				       layer_active);
	पूर्ण
पूर्ण

अटल व्योम tidss_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	अचिन्हित दीर्घ flags;

	dev_dbg(ddev->dev,
		"%s: %s enabled %d, needs modeset %d, event %p\n", __func__,
		crtc->name, drm_atomic_crtc_needs_modeset(crtc->state),
		crtc->state->enable, crtc->state->event);

	/* There is nothing to करो अगर CRTC is not going to be enabled. */
	अगर (!crtc->state->enable)
		वापस;

	/*
	 * Flush CRTC changes with go bit only अगर new modeset is not
	 * coming, so CRTC is enabled trough out the commit.
	 */
	अगर (drm_atomic_crtc_needs_modeset(crtc->state))
		वापस;

	/* If the GO bit is stuck we better quit here. */
	अगर (WARN_ON(dispc_vp_go_busy(tidss->dispc, tcrtc->hw_videoport)))
		वापस;

	/* We should have event अगर CRTC is enabled through out this commit. */
	अगर (WARN_ON(!crtc->state->event))
		वापस;

	/* Write vp properties to HW अगर needed. */
	dispc_vp_setup(tidss->dispc, tcrtc->hw_videoport, crtc->state, false);

	/* Update plane positions अगर needed. */
	tidss_crtc_position_planes(tidss, crtc, old_crtc_state, false);

	WARN_ON(drm_crtc_vblank_get(crtc) != 0);

	spin_lock_irqsave(&ddev->event_lock, flags);
	dispc_vp_go(tidss->dispc, tcrtc->hw_videoport);

	WARN_ON(tcrtc->event);

	tcrtc->event = crtc->state->event;
	crtc->state->event = शून्य;

	spin_unlock_irqrestore(&ddev->event_lock, flags);
पूर्ण

अटल व्योम tidss_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	स्थिर काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	dev_dbg(ddev->dev, "%s, event %p\n", __func__, crtc->state->event);

	tidss_runसमय_get(tidss);

	r = dispc_vp_set_clk_rate(tidss->dispc, tcrtc->hw_videoport,
				  mode->घड़ी * 1000);
	अगर (r != 0)
		वापस;

	r = dispc_vp_enable_clk(tidss->dispc, tcrtc->hw_videoport);
	अगर (r != 0)
		वापस;

	dispc_vp_setup(tidss->dispc, tcrtc->hw_videoport, crtc->state, true);
	tidss_crtc_position_planes(tidss, crtc, old_state, true);

	/* Turn vertical blanking पूर्णांकerrupt reporting on. */
	drm_crtc_vblank_on(crtc);

	dispc_vp_prepare(tidss->dispc, tcrtc->hw_videoport, crtc->state);

	dispc_vp_enable(tidss->dispc, tcrtc->hw_videoport, crtc->state);

	spin_lock_irqsave(&ddev->event_lock, flags);

	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&ddev->event_lock, flags);
पूर्ण

अटल व्योम tidss_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	अचिन्हित दीर्घ flags;

	dev_dbg(ddev->dev, "%s, event %p\n", __func__, crtc->state->event);

	reinit_completion(&tcrtc->frameकरोne_completion);

	dispc_vp_disable(tidss->dispc, tcrtc->hw_videoport);

	अगर (!रुको_क्रम_completion_समयout(&tcrtc->frameकरोne_completion,
					 msecs_to_jअगरfies(500)))
		dev_err(tidss->dev, "Timeout waiting for framedone on crtc %d",
			tcrtc->hw_videoport);

	dispc_vp_unprepare(tidss->dispc, tcrtc->hw_videoport);

	spin_lock_irqsave(&ddev->event_lock, flags);
	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ddev->event_lock, flags);

	drm_crtc_vblank_off(crtc);

	dispc_vp_disable_clk(tidss->dispc, tcrtc->hw_videoport);

	tidss_runसमय_put(tidss);
पूर्ण

अटल
क्रमागत drm_mode_status tidss_crtc_mode_valid(काष्ठा drm_crtc *crtc,
					   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);

	वापस dispc_vp_mode_valid(tidss->dispc, tcrtc->hw_videoport, mode);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs tidss_crtc_helper_funcs = अणु
	.atomic_check = tidss_crtc_atomic_check,
	.atomic_flush = tidss_crtc_atomic_flush,
	.atomic_enable = tidss_crtc_atomic_enable,
	.atomic_disable = tidss_crtc_atomic_disable,

	.mode_valid = tidss_crtc_mode_valid,
पूर्ण;

/* drm_crtc_funcs */

अटल पूर्णांक tidss_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_runसमय_get(tidss);

	tidss_irq_enable_vblank(crtc);

	वापस 0;
पूर्ण

अटल व्योम tidss_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_irq_disable_vblank(crtc);

	tidss_runसमय_put(tidss);
पूर्ण

अटल व्योम tidss_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tidss_crtc_state *tcrtc;

	अगर (crtc->state)
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

	kमुक्त(crtc->state);

	tcrtc = kzalloc(माप(*tcrtc), GFP_KERNEL);
	अगर (!tcrtc) अणु
		crtc->state = शून्य;
		वापस;
	पूर्ण

	__drm_atomic_helper_crtc_reset(crtc, &tcrtc->base);
पूर्ण

अटल काष्ठा drm_crtc_state *tidss_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tidss_crtc_state *state, *current_state;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	current_state = to_tidss_crtc_state(crtc->state);

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	state->plane_pos_changed = false;

	state->bus_क्रमmat = current_state->bus_क्रमmat;
	state->bus_flags = current_state->bus_flags;

	वापस &state->base;
पूर्ण

अटल व्योम tidss_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);

	drm_crtc_cleanup(crtc);
	kमुक्त(tcrtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs tidss_crtc_funcs = अणु
	.reset = tidss_crtc_reset,
	.destroy = tidss_crtc_destroy,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = tidss_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = tidss_crtc_enable_vblank,
	.disable_vblank = tidss_crtc_disable_vblank,
पूर्ण;

काष्ठा tidss_crtc *tidss_crtc_create(काष्ठा tidss_device *tidss,
				     u32 hw_videoport,
				     काष्ठा drm_plane *primary)
अणु
	काष्ठा tidss_crtc *tcrtc;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक gamma_lut_size = 0;
	bool has_cपंचांग = tidss->feat->vp_feat.color.has_cपंचांग;
	पूर्णांक ret;

	tcrtc = kzalloc(माप(*tcrtc), GFP_KERNEL);
	अगर (!tcrtc)
		वापस ERR_PTR(-ENOMEM);

	tcrtc->hw_videoport = hw_videoport;
	init_completion(&tcrtc->frameकरोne_completion);

	crtc =  &tcrtc->crtc;

	ret = drm_crtc_init_with_planes(&tidss->ddev, crtc, primary,
					शून्य, &tidss_crtc_funcs, शून्य);
	अगर (ret < 0) अणु
		kमुक्त(tcrtc);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_crtc_helper_add(crtc, &tidss_crtc_helper_funcs);

	/*
	 * The dispc gamma functions adapt to what ever size we ask
	 * from it no matter what HW supports. X-server assumes 256
	 * element gamma tables so lets use that.
	 */
	अगर (tidss->feat->vp_feat.color.gamma_size)
		gamma_lut_size = 256;

	drm_crtc_enable_color_mgmt(crtc, 0, has_cपंचांग, gamma_lut_size);
	अगर (gamma_lut_size)
		drm_mode_crtc_set_gamma_size(crtc, gamma_lut_size);

	वापस tcrtc;
पूर्ण
