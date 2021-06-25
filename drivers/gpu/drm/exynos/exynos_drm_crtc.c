<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_crtc.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_plane.h"

अटल व्योम exynos_drm_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->atomic_enable)
		exynos_crtc->ops->atomic_enable(exynos_crtc);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम exynos_drm_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	drm_crtc_vblank_off(crtc);

	अगर (exynos_crtc->ops->atomic_disable)
		exynos_crtc->ops->atomic_disable(exynos_crtc);

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (!crtc_state->enable)
		वापस 0;

	अगर (exynos_crtc->ops->atomic_check)
		वापस exynos_crtc->ops->atomic_check(exynos_crtc, crtc_state);

	वापस 0;
पूर्ण

अटल व्योम exynos_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->atomic_begin)
		exynos_crtc->ops->atomic_begin(exynos_crtc);
पूर्ण

अटल व्योम exynos_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->atomic_flush)
		exynos_crtc->ops->atomic_flush(exynos_crtc);
पूर्ण

अटल क्रमागत drm_mode_status exynos_crtc_mode_valid(काष्ठा drm_crtc *crtc,
	स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->mode_valid)
		वापस exynos_crtc->ops->mode_valid(exynos_crtc, mode);

	वापस MODE_OK;
पूर्ण

अटल bool exynos_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->mode_fixup)
		वापस exynos_crtc->ops->mode_fixup(exynos_crtc, mode,
				adjusted_mode);

	वापस true;
पूर्ण


अटल स्थिर काष्ठा drm_crtc_helper_funcs exynos_crtc_helper_funcs = अणु
	.mode_valid	= exynos_crtc_mode_valid,
	.mode_fixup	= exynos_crtc_mode_fixup,
	.atomic_check	= exynos_crtc_atomic_check,
	.atomic_begin	= exynos_crtc_atomic_begin,
	.atomic_flush	= exynos_crtc_atomic_flush,
	.atomic_enable	= exynos_drm_crtc_atomic_enable,
	.atomic_disable	= exynos_drm_crtc_atomic_disable,
पूर्ण;

व्योम exynos_crtc_handle_event(काष्ठा exynos_drm_crtc *exynos_crtc)
अणु
	काष्ठा drm_crtc *crtc = &exynos_crtc->base;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;
	अचिन्हित दीर्घ flags;

	अगर (!event)
		वापस;
	crtc->state->event = शून्य;

	WARN_ON(drm_crtc_vblank_get(crtc) != 0);

	spin_lock_irqsave(&crtc->dev->event_lock, flags);
	drm_crtc_arm_vblank_event(crtc, event);
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
पूर्ण

अटल व्योम exynos_drm_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	drm_crtc_cleanup(crtc);
	kमुक्त(exynos_crtc);
पूर्ण

अटल पूर्णांक exynos_drm_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->enable_vblank)
		वापस exynos_crtc->ops->enable_vblank(exynos_crtc);

	वापस 0;
पूर्ण

अटल व्योम exynos_drm_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->disable_vblank)
		exynos_crtc->ops->disable_vblank(exynos_crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs exynos_crtc_funcs = अणु
	.set_config	= drm_atomic_helper_set_config,
	.page_flip	= drm_atomic_helper_page_flip,
	.destroy	= exynos_drm_crtc_destroy,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = exynos_drm_crtc_enable_vblank,
	.disable_vblank = exynos_drm_crtc_disable_vblank,
पूर्ण;

काष्ठा exynos_drm_crtc *exynos_drm_crtc_create(काष्ठा drm_device *drm_dev,
					काष्ठा drm_plane *plane,
					क्रमागत exynos_drm_output_type type,
					स्थिर काष्ठा exynos_drm_crtc_ops *ops,
					व्योम *ctx)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	exynos_crtc = kzalloc(माप(*exynos_crtc), GFP_KERNEL);
	अगर (!exynos_crtc)
		वापस ERR_PTR(-ENOMEM);

	exynos_crtc->type = type;
	exynos_crtc->ops = ops;
	exynos_crtc->ctx = ctx;

	crtc = &exynos_crtc->base;

	ret = drm_crtc_init_with_planes(drm_dev, crtc, plane, शून्य,
					&exynos_crtc_funcs, शून्य);
	अगर (ret < 0)
		जाओ err_crtc;

	drm_crtc_helper_add(crtc, &exynos_crtc_helper_funcs);

	वापस exynos_crtc;

err_crtc:
	plane->funcs->destroy(plane);
	kमुक्त(exynos_crtc);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा exynos_drm_crtc *exynos_drm_crtc_get_by_type(काष्ठा drm_device *drm_dev,
				       क्रमागत exynos_drm_output_type out_type)
अणु
	काष्ठा drm_crtc *crtc;

	drm_क्रम_each_crtc(crtc, drm_dev)
		अगर (to_exynos_crtc(crtc)->type == out_type)
			वापस to_exynos_crtc(crtc);

	वापस ERR_PTR(-ENODEV);
पूर्ण

पूर्णांक exynos_drm_set_possible_crtcs(काष्ठा drm_encoder *encoder,
		क्रमागत exynos_drm_output_type out_type)
अणु
	काष्ठा exynos_drm_crtc *crtc = exynos_drm_crtc_get_by_type(encoder->dev,
						out_type);

	अगर (IS_ERR(crtc))
		वापस PTR_ERR(crtc);

	encoder->possible_crtcs = drm_crtc_mask(&crtc->base);

	वापस 0;
पूर्ण

व्योम exynos_drm_crtc_te_handler(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	अगर (exynos_crtc->ops->te_handler)
		exynos_crtc->ops->te_handler(exynos_crtc);
पूर्ण
