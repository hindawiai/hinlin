<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#समावेश <linux/math64.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "omap_drv.h"

#घोषणा to_omap_crtc_state(x) container_of(x, काष्ठा omap_crtc_state, base)

काष्ठा omap_crtc_state अणु
	/* Must be first. */
	काष्ठा drm_crtc_state base;
	/* Shaकरोw values क्रम legacy userspace support. */
	अचिन्हित पूर्णांक rotation;
	अचिन्हित पूर्णांक zpos;
	bool manually_updated;
पूर्ण;

#घोषणा to_omap_crtc(x) container_of(x, काष्ठा omap_crtc, base)

काष्ठा omap_crtc अणु
	काष्ठा drm_crtc base;

	स्थिर अक्षर *name;
	काष्ठा omap_drm_pipeline *pipe;
	क्रमागत omap_channel channel;

	काष्ठा videomode vm;

	bool ignore_digit_sync_lost;

	bool enabled;
	bool pending;
	रुको_queue_head_t pending_रुको;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा delayed_work update_work;

	व्योम (*frameकरोne_handler)(व्योम *);
	व्योम *frameकरोne_handler_data;
पूर्ण;

/* -----------------------------------------------------------------------------
 * Helper Functions
 */

काष्ठा videomode *omap_crtc_timings(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	वापस &omap_crtc->vm;
पूर्ण

क्रमागत omap_channel omap_crtc_channel(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	वापस omap_crtc->channel;
पूर्ण

अटल bool omap_crtc_is_pending(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	अचिन्हित दीर्घ flags;
	bool pending;

	spin_lock_irqsave(&crtc->dev->event_lock, flags);
	pending = omap_crtc->pending;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

	वापस pending;
पूर्ण

पूर्णांक omap_crtc_रुको_pending(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	/*
	 * Timeout is set to a "sufficiently" high value, which should cover
	 * a single frame refresh even on slower displays.
	 */
	वापस रुको_event_समयout(omap_crtc->pending_रुको,
				  !omap_crtc_is_pending(crtc),
				  msecs_to_jअगरfies(250));
पूर्ण

/* -----------------------------------------------------------------------------
 * DSS Manager Functions
 */

/*
 * Manager-ops, callbacks from output when they need to configure
 * the upstream part of the video pipe.
 */

व्योम omap_crtc_dss_start_update(काष्ठा omap_drm_निजी *priv,
				       क्रमागत omap_channel channel)
अणु
	dispc_mgr_enable(priv->dispc, channel, true);
पूर्ण

/* Called only from the encoder enable/disable and suspend/resume handlers. */
व्योम omap_crtc_set_enabled(काष्ठा drm_crtc *crtc, bool enable)
अणु
	काष्ठा omap_crtc_state *omap_state = to_omap_crtc_state(crtc->state);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	क्रमागत omap_channel channel = omap_crtc->channel;
	काष्ठा omap_irq_रुको *रुको;
	u32 frameकरोne_irq, vsync_irq;
	पूर्णांक ret;

	अगर (WARN_ON(omap_crtc->enabled == enable))
		वापस;

	अगर (omap_state->manually_updated) अणु
		omap_irq_enable_frameकरोne(crtc, enable);
		omap_crtc->enabled = enable;
		वापस;
	पूर्ण

	अगर (omap_crtc->pipe->output->type == OMAP_DISPLAY_TYPE_HDMI) अणु
		dispc_mgr_enable(priv->dispc, channel, enable);
		omap_crtc->enabled = enable;
		वापस;
	पूर्ण

	अगर (omap_crtc->channel == OMAP_DSS_CHANNEL_DIGIT) अणु
		/*
		 * Digit output produces some sync lost पूर्णांकerrupts during the
		 * first frame when enabling, so we need to ignore those.
		 */
		omap_crtc->ignore_digit_sync_lost = true;
	पूर्ण

	frameकरोne_irq = dispc_mgr_get_frameकरोne_irq(priv->dispc,
							       channel);
	vsync_irq = dispc_mgr_get_vsync_irq(priv->dispc, channel);

	अगर (enable) अणु
		रुको = omap_irq_रुको_init(dev, vsync_irq, 1);
	पूर्ण अन्यथा अणु
		/*
		 * When we disable the digit output, we need to रुको क्रम
		 * FRAMEDONE to know that DISPC has finished with the output.
		 *
		 * OMAP2/3 करोes not have FRAMEDONE irq क्रम digit output, and in
		 * that हाल we need to use vsync पूर्णांकerrupt, and रुको क्रम both
		 * even and odd frames.
		 */

		अगर (frameकरोne_irq)
			रुको = omap_irq_रुको_init(dev, frameकरोne_irq, 1);
		अन्यथा
			रुको = omap_irq_रुको_init(dev, vsync_irq, 2);
	पूर्ण

	dispc_mgr_enable(priv->dispc, channel, enable);
	omap_crtc->enabled = enable;

	ret = omap_irq_रुको(dev, रुको, msecs_to_jअगरfies(100));
	अगर (ret) अणु
		dev_err(dev->dev, "%s: timeout waiting for %s\n",
				omap_crtc->name, enable ? "enable" : "disable");
	पूर्ण

	अगर (omap_crtc->channel == OMAP_DSS_CHANNEL_DIGIT) अणु
		omap_crtc->ignore_digit_sync_lost = false;
		/* make sure the irq handler sees the value above */
		mb();
	पूर्ण
पूर्ण


पूर्णांक omap_crtc_dss_enable(काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	dispc_mgr_set_timings(priv->dispc, omap_crtc->channel,
					 &omap_crtc->vm);
	omap_crtc_set_enabled(&omap_crtc->base, true);

	वापस 0;
पूर्ण

व्योम omap_crtc_dss_disable(काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	omap_crtc_set_enabled(&omap_crtc->base, false);
पूर्ण

व्योम omap_crtc_dss_set_timings(काष्ठा omap_drm_निजी *priv,
		क्रमागत omap_channel channel,
		स्थिर काष्ठा videomode *vm)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	DBG("%s", omap_crtc->name);
	omap_crtc->vm = *vm;
पूर्ण

व्योम omap_crtc_dss_set_lcd_config(काष्ठा omap_drm_निजी *priv,
		क्रमागत omap_channel channel,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	DBG("%s", omap_crtc->name);
	dispc_mgr_set_lcd_config(priv->dispc, omap_crtc->channel,
					    config);
पूर्ण

पूर्णांक omap_crtc_dss_रेजिस्टर_frameकरोne(
		काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा drm_device *dev = omap_crtc->base.dev;

	अगर (omap_crtc->frameकरोne_handler)
		वापस -EBUSY;

	dev_dbg(dev->dev, "register framedone %s", omap_crtc->name);

	omap_crtc->frameकरोne_handler = handler;
	omap_crtc->frameकरोne_handler_data = data;

	वापस 0;
पूर्ण

व्योम omap_crtc_dss_unरेजिस्टर_frameकरोne(
		काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा drm_crtc *crtc = priv->channels[channel]->crtc;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा drm_device *dev = omap_crtc->base.dev;

	dev_dbg(dev->dev, "unregister framedone %s", omap_crtc->name);

	WARN_ON(omap_crtc->frameकरोne_handler != handler);
	WARN_ON(omap_crtc->frameकरोne_handler_data != data);

	omap_crtc->frameकरोne_handler = शून्य;
	omap_crtc->frameकरोne_handler_data = शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Setup, Flush and Page Flip
 */

व्योम omap_crtc_error_irq(काष्ठा drm_crtc *crtc, u32 irqstatus)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	अगर (omap_crtc->ignore_digit_sync_lost) अणु
		irqstatus &= ~DISPC_IRQ_SYNC_LOST_DIGIT;
		अगर (!irqstatus)
			वापस;
	पूर्ण

	DRM_ERROR_RATELIMITED("%s: errors: %08x\n", omap_crtc->name, irqstatus);
पूर्ण

व्योम omap_crtc_vblank_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा drm_device *dev = omap_crtc->base.dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	bool pending;

	spin_lock(&crtc->dev->event_lock);
	/*
	 * If the dispc is busy we're racing the flush operation. Try again on
	 * the next vblank पूर्णांकerrupt.
	 */
	अगर (dispc_mgr_go_busy(priv->dispc, omap_crtc->channel)) अणु
		spin_unlock(&crtc->dev->event_lock);
		वापस;
	पूर्ण

	/* Send the vblank event अगर one has been requested. */
	अगर (omap_crtc->event) अणु
		drm_crtc_send_vblank_event(crtc, omap_crtc->event);
		omap_crtc->event = शून्य;
	पूर्ण

	pending = omap_crtc->pending;
	omap_crtc->pending = false;
	spin_unlock(&crtc->dev->event_lock);

	अगर (pending)
		drm_crtc_vblank_put(crtc);

	/* Wake up omap_atomic_complete. */
	wake_up(&omap_crtc->pending_रुको);

	DBG("%s: apply done", omap_crtc->name);
पूर्ण

व्योम omap_crtc_frameकरोne_irq(काष्ठा drm_crtc *crtc, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	अगर (!omap_crtc->frameकरोne_handler)
		वापस;

	omap_crtc->frameकरोne_handler(omap_crtc->frameकरोne_handler_data);

	spin_lock(&crtc->dev->event_lock);
	/* Send the vblank event अगर one has been requested. */
	अगर (omap_crtc->event) अणु
		drm_crtc_send_vblank_event(crtc, omap_crtc->event);
		omap_crtc->event = शून्य;
	पूर्ण
	omap_crtc->pending = false;
	spin_unlock(&crtc->dev->event_lock);

	/* Wake up omap_atomic_complete. */
	wake_up(&omap_crtc->pending_रुको);
पूर्ण

व्योम omap_crtc_flush(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा omap_crtc_state *omap_state = to_omap_crtc_state(crtc->state);

	अगर (!omap_state->manually_updated)
		वापस;

	अगर (!delayed_work_pending(&omap_crtc->update_work))
		schedule_delayed_work(&omap_crtc->update_work, 0);
पूर्ण

अटल व्योम omap_crtc_manual_display_update(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा omap_crtc *omap_crtc =
			container_of(data, काष्ठा omap_crtc, update_work.work);
	काष्ठा omap_dss_device *dssdev = omap_crtc->pipe->output;
	काष्ठा drm_device *dev = omap_crtc->base.dev;
	पूर्णांक ret;

	अगर (!dssdev || !dssdev->dsi_ops || !dssdev->dsi_ops->update)
		वापस;

	ret = dssdev->dsi_ops->update(dssdev);
	अगर (ret < 0) अणु
		spin_lock_irq(&dev->event_lock);
		omap_crtc->pending = false;
		spin_unlock_irq(&dev->event_lock);
		wake_up(&omap_crtc->pending_रुको);
	पूर्ण
पूर्ण

अटल s16 omap_crtc_s31_32_to_s2_8(s64 coef)
अणु
	u64 sign_bit = 1ULL << 63;
	u64 cbits = (u64)coef;

	s16 ret = clamp_val(((cbits & ~sign_bit) >> 24), 0, 0x1ff);

	अगर (cbits & sign_bit)
		ret = -ret;

	वापस ret;
पूर्ण

अटल व्योम omap_crtc_cpr_coefs_from_cपंचांग(स्थिर काष्ठा drm_color_cपंचांग *cपंचांग,
					 काष्ठा omap_dss_cpr_coefs *cpr)
अणु
	cpr->rr = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[0]);
	cpr->rg = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[1]);
	cpr->rb = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[2]);
	cpr->gr = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[3]);
	cpr->gg = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[4]);
	cpr->gb = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[5]);
	cpr->br = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[6]);
	cpr->bg = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[7]);
	cpr->bb = omap_crtc_s31_32_to_s2_8(cपंचांग->matrix[8]);
पूर्ण

अटल व्योम omap_crtc_ग_लिखो_crtc_properties(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा omap_overlay_manager_info info;

	स_रखो(&info, 0, माप(info));

	info.शेष_color = 0x000000;
	info.trans_enabled = false;
	info.partial_alpha_enabled = false;

	अगर (crtc->state->cपंचांग) अणु
		काष्ठा drm_color_cपंचांग *cपंचांग = crtc->state->cपंचांग->data;

		info.cpr_enable = true;
		omap_crtc_cpr_coefs_from_cपंचांग(cपंचांग, &info.cpr_coefs);
	पूर्ण अन्यथा अणु
		info.cpr_enable = false;
	पूर्ण

	dispc_mgr_setup(priv->dispc, omap_crtc->channel, &info);
पूर्ण

/* -----------------------------------------------------------------------------
 * CRTC Functions
 */

अटल व्योम omap_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	DBG("%s", omap_crtc->name);

	drm_crtc_cleanup(crtc);

	kमुक्त(omap_crtc);
पूर्ण

अटल व्योम omap_crtc_arm_event(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);

	WARN_ON(omap_crtc->pending);
	omap_crtc->pending = true;

	अगर (crtc->state->event) अणु
		omap_crtc->event = crtc->state->event;
		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम omap_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा omap_crtc_state *omap_state = to_omap_crtc_state(crtc->state);
	पूर्णांक ret;

	DBG("%s", omap_crtc->name);

	dispc_runसमय_get(priv->dispc);

	/* manual updated display will not trigger vsync irq */
	अगर (omap_state->manually_updated)
		वापस;

	drm_crtc_vblank_on(crtc);

	ret = drm_crtc_vblank_get(crtc);
	WARN_ON(ret != 0);

	spin_lock_irq(&crtc->dev->event_lock);
	omap_crtc_arm_event(crtc);
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल व्योम omap_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;

	DBG("%s", omap_crtc->name);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	cancel_delayed_work(&omap_crtc->update_work);

	अगर (!omap_crtc_रुको_pending(crtc))
		dev_warn(dev->dev, "manual display update did not finish!");

	drm_crtc_vblank_off(crtc);

	dispc_runसमय_put(priv->dispc);
पूर्ण

अटल क्रमागत drm_mode_status omap_crtc_mode_valid(काष्ठा drm_crtc *crtc,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा videomode vm = अणु0पूर्ण;
	पूर्णांक r;

	drm_display_mode_to_videomode(mode, &vm);

	/*
	 * DSI might not call this, since the supplied mode is not a
	 * valid DISPC mode. DSI will calculate and configure the
	 * proper DISPC mode later.
	 */
	अगर (omap_crtc->pipe->output->type != OMAP_DISPLAY_TYPE_DSI) अणु
		r = dispc_mgr_check_timings(priv->dispc,
						       omap_crtc->channel,
						       &vm);
		अगर (r)
			वापस r;
	पूर्ण

	/* Check क्रम bandwidth limit */
	अगर (priv->max_bandwidth) अणु
		/*
		 * Estimation क्रम the bandwidth need of a given mode with one
		 * full screen plane:
		 * bandwidth = resolution * 32bpp * (pclk / (vtotal * htotal))
		 *					^^ Refresh rate ^^
		 *
		 * The पूर्णांकerlaced mode is taken पूर्णांकo account by using the
		 * pixelघड़ी in the calculation.
		 *
		 * The equation is rearranged क्रम 64bit arithmetic.
		 */
		uपूर्णांक64_t bandwidth = mode->घड़ी * 1000;
		अचिन्हित पूर्णांक bpp = 4;

		bandwidth = bandwidth * mode->hdisplay * mode->vdisplay * bpp;
		bandwidth = भाग_u64(bandwidth, mode->htotal * mode->vtotal);

		/*
		 * Reject modes which would need more bandwidth अगर used with one
		 * full resolution plane (most common use हाल).
		 */
		अगर (priv->max_bandwidth < bandwidth)
			वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल व्योम omap_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;

	DBG("%s: set mode: " DRM_MODE_FMT,
	    omap_crtc->name, DRM_MODE_ARG(mode));

	drm_display_mode_to_videomode(mode, &omap_crtc->vm);
पूर्ण

अटल bool omap_crtc_is_manually_updated(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा omap_dss_device *dssdev = omap_crtc->pipe->output;

	अगर (!dssdev || !dssdev->dsi_ops || !dssdev->dsi_ops->is_video_mode)
		वापस false;

	अगर (dssdev->dsi_ops->is_video_mode(dssdev))
		वापस false;

	DBG("detected manually updated display!");
	वापस true;
पूर्ण

अटल पूर्णांक omap_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_plane_state *pri_state;

	अगर (crtc_state->color_mgmt_changed && crtc_state->degamma_lut) अणु
		अचिन्हित पूर्णांक length = crtc_state->degamma_lut->length /
			माप(काष्ठा drm_color_lut);

		अगर (length < 2)
			वापस -EINVAL;
	पूर्ण

	pri_state = drm_atomic_get_new_plane_state(state,
						   crtc->primary);
	अगर (pri_state) अणु
		काष्ठा omap_crtc_state *omap_crtc_state =
			to_omap_crtc_state(crtc_state);

		/* Mirror new values क्रम zpos and rotation in omap_crtc_state */
		omap_crtc_state->zpos = pri_state->zpos;
		omap_crtc_state->rotation = pri_state->rotation;

		/* Check अगर this CRTC is क्रम a manually updated display */
		omap_crtc_state->manually_updated = omap_crtc_is_manually_updated(crtc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल व्योम omap_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc *omap_crtc = to_omap_crtc(crtc);
	काष्ठा omap_crtc_state *omap_crtc_state = to_omap_crtc_state(crtc->state);
	पूर्णांक ret;

	अगर (crtc->state->color_mgmt_changed) अणु
		काष्ठा drm_color_lut *lut = शून्य;
		अचिन्हित पूर्णांक length = 0;

		अगर (crtc->state->degamma_lut) अणु
			lut = (काष्ठा drm_color_lut *)
				crtc->state->degamma_lut->data;
			length = crtc->state->degamma_lut->length /
				माप(*lut);
		पूर्ण
		dispc_mgr_set_gamma(priv->dispc, omap_crtc->channel,
					       lut, length);
	पूर्ण

	omap_crtc_ग_लिखो_crtc_properties(crtc);

	/* Only flush the CRTC अगर it is currently enabled. */
	अगर (!omap_crtc->enabled)
		वापस;

	DBG("%s: GO", omap_crtc->name);

	अगर (omap_crtc_state->manually_updated) अणु
		/* send new image क्रम page flips and modeset changes */
		spin_lock_irq(&crtc->dev->event_lock);
		omap_crtc_flush(crtc);
		omap_crtc_arm_event(crtc);
		spin_unlock_irq(&crtc->dev->event_lock);
		वापस;
	पूर्ण

	ret = drm_crtc_vblank_get(crtc);
	WARN_ON(ret != 0);

	spin_lock_irq(&crtc->dev->event_lock);
	dispc_mgr_go(priv->dispc, omap_crtc->channel);
	omap_crtc_arm_event(crtc);
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल पूर्णांक omap_crtc_atomic_set_property(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_crtc_state *state,
					 काष्ठा drm_property *property,
					 u64 val)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा drm_plane_state *plane_state;

	/*
	 * Delegate property set to the primary plane. Get the plane state and
	 * set the property directly, the shaकरोw copy will be asचिन्हित in the
	 * omap_crtc_atomic_check callback. This way updates to plane state will
	 * always be mirrored in the crtc state correctly.
	 */
	plane_state = drm_atomic_get_plane_state(state->state, crtc->primary);
	अगर (IS_ERR(plane_state))
		वापस PTR_ERR(plane_state);

	अगर (property == crtc->primary->rotation_property)
		plane_state->rotation = val;
	अन्यथा अगर (property == priv->zorder_prop)
		plane_state->zpos = val;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_crtc_atomic_get_property(काष्ठा drm_crtc *crtc,
					 स्थिर काष्ठा drm_crtc_state *state,
					 काष्ठा drm_property *property,
					 u64 *val)
अणु
	काष्ठा omap_drm_निजी *priv = crtc->dev->dev_निजी;
	काष्ठा omap_crtc_state *omap_state = to_omap_crtc_state(state);

	अगर (property == crtc->primary->rotation_property)
		*val = omap_state->rotation;
	अन्यथा अगर (property == priv->zorder_prop)
		*val = omap_state->zpos;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम omap_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc_state *state;

	अगर (crtc->state)
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

	kमुक्त(crtc->state);

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
omap_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा omap_crtc_state *state, *current_state;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	current_state = to_omap_crtc_state(crtc->state);

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	state->zpos = current_state->zpos;
	state->rotation = current_state->rotation;
	state->manually_updated = current_state->manually_updated;

	वापस &state->base;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs omap_crtc_funcs = अणु
	.reset = omap_crtc_reset,
	.set_config = drm_atomic_helper_set_config,
	.destroy = omap_crtc_destroy,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = omap_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.atomic_set_property = omap_crtc_atomic_set_property,
	.atomic_get_property = omap_crtc_atomic_get_property,
	.enable_vblank = omap_irq_enable_vblank,
	.disable_vblank = omap_irq_disable_vblank,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs omap_crtc_helper_funcs = अणु
	.mode_set_nofb = omap_crtc_mode_set_nofb,
	.atomic_check = omap_crtc_atomic_check,
	.atomic_begin = omap_crtc_atomic_begin,
	.atomic_flush = omap_crtc_atomic_flush,
	.atomic_enable = omap_crtc_atomic_enable,
	.atomic_disable = omap_crtc_atomic_disable,
	.mode_valid = omap_crtc_mode_valid,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Init and Cleanup
 */

अटल स्थिर अक्षर *channel_names[] = अणु
	[OMAP_DSS_CHANNEL_LCD] = "lcd",
	[OMAP_DSS_CHANNEL_DIGIT] = "tv",
	[OMAP_DSS_CHANNEL_LCD2] = "lcd2",
	[OMAP_DSS_CHANNEL_LCD3] = "lcd3",
पूर्ण;

/* initialize crtc */
काष्ठा drm_crtc *omap_crtc_init(काष्ठा drm_device *dev,
				काष्ठा omap_drm_pipeline *pipe,
				काष्ठा drm_plane *plane)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा omap_crtc *omap_crtc;
	क्रमागत omap_channel channel;
	पूर्णांक ret;

	channel = pipe->output->dispc_channel;

	DBG("%s", channel_names[channel]);

	omap_crtc = kzalloc(माप(*omap_crtc), GFP_KERNEL);
	अगर (!omap_crtc)
		वापस ERR_PTR(-ENOMEM);

	crtc = &omap_crtc->base;

	init_रुकोqueue_head(&omap_crtc->pending_रुको);

	omap_crtc->pipe = pipe;
	omap_crtc->channel = channel;
	omap_crtc->name = channel_names[channel];

	/*
	 * We want to refresh manually updated displays from dirty callback,
	 * which is called quite often (e.g. क्रम each drawn line). This will
	 * be used to करो the display update asynchronously to aव्योम blocking
	 * the rendering process and merges multiple dirty calls पूर्णांकo one
	 * update अगर they arrive very fast. We also call this function क्रम
	 * atomic display updates (e.g. क्रम page flips), which means we करो
	 * not need extra locking. Atomic updates should be synchronous, but
	 * need to रुको क्रम the frameकरोne पूर्णांकerrupt anyways.
	 */
	INIT_DELAYED_WORK(&omap_crtc->update_work,
			  omap_crtc_manual_display_update);

	ret = drm_crtc_init_with_planes(dev, crtc, plane, शून्य,
					&omap_crtc_funcs, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "%s(): could not init crtc for: %s\n",
			__func__, pipe->output->name);
		kमुक्त(omap_crtc);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_crtc_helper_add(crtc, &omap_crtc_helper_funcs);

	/* The dispc API adapts to what ever size, but the HW supports
	 * 256 element gamma table क्रम LCDs and 1024 element table क्रम
	 * OMAP_DSS_CHANNEL_DIGIT. X server assumes 256 element gamma
	 * tables so lets use that. Size of HW gamma table can be
	 * extracted with dispc_mgr_gamma_size(). If it वापसs 0
	 * gamma table is not supported.
	 */
	अगर (dispc_mgr_gamma_size(priv->dispc, channel)) अणु
		अचिन्हित पूर्णांक gamma_lut_size = 256;

		drm_crtc_enable_color_mgmt(crtc, gamma_lut_size, true, 0);
		drm_mode_crtc_set_gamma_size(crtc, gamma_lut_size);
	पूर्ण

	omap_plane_install_properties(crtc->primary, &crtc->base);

	वापस crtc;
पूर्ण
