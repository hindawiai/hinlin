<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "dcss-dev.h"
#समावेश "dcss-kms.h"

अटल पूर्णांक dcss_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dcss_crtc *dcss_crtc = container_of(crtc, काष्ठा dcss_crtc,
						   base);
	काष्ठा dcss_dev *dcss = crtc->dev->dev_निजी;

	dcss_dtg_vblank_irq_enable(dcss->dtg, true);

	dcss_dtg_ctxld_kick_irq_enable(dcss->dtg, true);

	enable_irq(dcss_crtc->irq);

	वापस 0;
पूर्ण

अटल व्योम dcss_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dcss_crtc *dcss_crtc = container_of(crtc, काष्ठा dcss_crtc,
						   base);
	काष्ठा dcss_dev *dcss = dcss_crtc->base.dev->dev_निजी;

	disable_irq_nosync(dcss_crtc->irq);

	dcss_dtg_vblank_irq_enable(dcss->dtg, false);

	अगर (dcss_crtc->disable_ctxld_kick_irq)
		dcss_dtg_ctxld_kick_irq_enable(dcss->dtg, false);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs dcss_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = drm_crtc_cleanup,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = dcss_enable_vblank,
	.disable_vblank = dcss_disable_vblank,
पूर्ण;

अटल व्योम dcss_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम dcss_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dcss_crtc *dcss_crtc = container_of(crtc, काष्ठा dcss_crtc,
						   base);
	काष्ठा dcss_dev *dcss = dcss_crtc->base.dev->dev_निजी;

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc));
		drm_crtc_arm_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	अगर (dcss_dtg_is_enabled(dcss->dtg))
		dcss_ctxld_enable(dcss->ctxld);
पूर्ण

अटल व्योम dcss_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा dcss_crtc *dcss_crtc = container_of(crtc, काष्ठा dcss_crtc,
						   base);
	काष्ठा dcss_dev *dcss = dcss_crtc->base.dev->dev_निजी;
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा drm_display_mode *old_mode = &old_crtc_state->adjusted_mode;
	काष्ठा videomode vm;

	drm_display_mode_to_videomode(mode, &vm);

	pm_runसमय_get_sync(dcss->dev);

	vm.pixelघड़ी = mode->crtc_घड़ी * 1000;

	dcss_ss_subsam_set(dcss->ss);
	dcss_dtg_css_set(dcss->dtg);

	अगर (!drm_mode_equal(mode, old_mode) || !old_crtc_state->active) अणु
		dcss_dtg_sync_set(dcss->dtg, &vm);
		dcss_ss_sync_set(dcss->ss, &vm,
				 mode->flags & DRM_MODE_FLAG_PHSYNC,
				 mode->flags & DRM_MODE_FLAG_PVSYNC);
	पूर्ण

	dcss_enable_dtg_and_ss(dcss);

	dcss_ctxld_enable(dcss->ctxld);

	/* Allow CTXLD kick पूर्णांकerrupt to be disabled when VBLANK is disabled. */
	dcss_crtc->disable_ctxld_kick_irq = true;
पूर्ण

अटल व्योम dcss_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा dcss_crtc *dcss_crtc = container_of(crtc, काष्ठा dcss_crtc,
						   base);
	काष्ठा dcss_dev *dcss = dcss_crtc->base.dev->dev_निजी;
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा drm_display_mode *old_mode = &old_crtc_state->adjusted_mode;

	drm_atomic_helper_disable_planes_on_crtc(old_crtc_state, false);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	dcss_dtg_ctxld_kick_irq_enable(dcss->dtg, true);

	reinit_completion(&dcss->disable_completion);

	dcss_disable_dtg_and_ss(dcss);

	dcss_ctxld_enable(dcss->ctxld);

	अगर (!drm_mode_equal(mode, old_mode) || !crtc->state->active)
		अगर (!रुको_क्रम_completion_समयout(&dcss->disable_completion,
						 msecs_to_jअगरfies(100)))
			dev_err(dcss->dev, "Shutting off DTG timed out.\n");

	/*
	 * Do not shut off CTXLD kick पूर्णांकerrupt when shutting VBLANK off. It
	 * will be needed to commit the last changes, beक्रमe going to suspend.
	 */
	dcss_crtc->disable_ctxld_kick_irq = false;

	drm_crtc_vblank_off(crtc);

	pm_runसमय_mark_last_busy(dcss->dev);
	pm_runसमय_put_स्वतःsuspend(dcss->dev);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs dcss_helper_funcs = अणु
	.atomic_begin = dcss_crtc_atomic_begin,
	.atomic_flush = dcss_crtc_atomic_flush,
	.atomic_enable = dcss_crtc_atomic_enable,
	.atomic_disable = dcss_crtc_atomic_disable,
पूर्ण;

अटल irqवापस_t dcss_crtc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dcss_crtc *dcss_crtc = dev_id;
	काष्ठा dcss_dev *dcss = dcss_crtc->base.dev->dev_निजी;

	अगर (!dcss_dtg_vblank_irq_valid(dcss->dtg))
		वापस IRQ_NONE;

	अगर (dcss_ctxld_is_flushed(dcss->ctxld))
		drm_crtc_handle_vblank(&dcss_crtc->base);

	dcss_dtg_vblank_irq_clear(dcss->dtg);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक dcss_crtc_init(काष्ठा dcss_crtc *crtc, काष्ठा drm_device *drm)
अणु
	काष्ठा dcss_dev *dcss = drm->dev_निजी;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dcss->dev);
	पूर्णांक ret;

	crtc->plane[0] = dcss_plane_init(drm, drm_crtc_mask(&crtc->base),
					 DRM_PLANE_TYPE_PRIMARY, 0);
	अगर (IS_ERR(crtc->plane[0]))
		वापस PTR_ERR(crtc->plane[0]);

	crtc->base.port = dcss->of_port;

	drm_crtc_helper_add(&crtc->base, &dcss_helper_funcs);
	ret = drm_crtc_init_with_planes(drm, &crtc->base, &crtc->plane[0]->base,
					शून्य, &dcss_crtc_funcs, शून्य);
	अगर (ret) अणु
		dev_err(dcss->dev, "failed to init crtc\n");
		वापस ret;
	पूर्ण

	crtc->irq = platक्रमm_get_irq_byname(pdev, "vblank");
	अगर (crtc->irq < 0)
		वापस crtc->irq;

	ret = request_irq(crtc->irq, dcss_crtc_irq_handler,
			  0, "dcss_drm", crtc);
	अगर (ret) अणु
		dev_err(dcss->dev, "irq request failed with %d.\n", ret);
		वापस ret;
	पूर्ण

	disable_irq(crtc->irq);

	वापस 0;
पूर्ण

व्योम dcss_crtc_deinit(काष्ठा dcss_crtc *crtc, काष्ठा drm_device *drm)
अणु
	मुक्त_irq(crtc->irq, crtc);
पूर्ण
