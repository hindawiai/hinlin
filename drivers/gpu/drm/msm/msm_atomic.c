<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_atomic_trace.h"
#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_kms.h"

पूर्णांक msm_atomic_prepare_fb(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा msm_drm_निजी *priv = plane->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;

	अगर (!new_state->fb)
		वापस 0;

	drm_gem_plane_helper_prepare_fb(plane, new_state);

	वापस msm_framebuffer_prepare(new_state->fb, kms->aspace);
पूर्ण

/*
 * Helpers to control vblanks जबतक we flush.. basically just to ensure
 * that vblank accounting is चयनed on, so we get valid seqn/बारtamp
 * on pageflip events (अगर requested)
 */

अटल व्योम vblank_get(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(kms->dev, crtc, crtc_mask) अणु
		अगर (!crtc->state->active)
			जारी;
		drm_crtc_vblank_get(crtc);
	पूर्ण
पूर्ण

अटल व्योम vblank_put(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(kms->dev, crtc, crtc_mask) अणु
		अगर (!crtc->state->active)
			जारी;
		drm_crtc_vblank_put(crtc);
	पूर्ण
पूर्ण

अटल व्योम lock_crtcs(काष्ठा msm_kms *kms, अचिन्हित पूर्णांक crtc_mask)
अणु
	पूर्णांक crtc_index;
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(kms->dev, crtc, crtc_mask) अणु
		crtc_index = drm_crtc_index(crtc);
		mutex_lock_nested(&kms->commit_lock[crtc_index], crtc_index);
	पूर्ण
पूर्ण

अटल व्योम unlock_crtcs(काष्ठा msm_kms *kms, अचिन्हित पूर्णांक crtc_mask)
अणु
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask_reverse(kms->dev, crtc, crtc_mask)
		mutex_unlock(&kms->commit_lock[drm_crtc_index(crtc)]);
पूर्ण

अटल व्योम msm_atomic_async_commit(काष्ठा msm_kms *kms, पूर्णांक crtc_idx)
अणु
	अचिन्हित crtc_mask = BIT(crtc_idx);

	trace_msm_atomic_async_commit_start(crtc_mask);

	lock_crtcs(kms, crtc_mask);

	अगर (!(kms->pending_crtc_mask & crtc_mask)) अणु
		unlock_crtcs(kms, crtc_mask);
		जाओ out;
	पूर्ण

	kms->pending_crtc_mask &= ~crtc_mask;

	kms->funcs->enable_commit(kms);

	vblank_get(kms, crtc_mask);

	/*
	 * Flush hardware updates:
	 */
	trace_msm_atomic_flush_commit(crtc_mask);
	kms->funcs->flush_commit(kms, crtc_mask);

	/*
	 * Wait क्रम flush to complete:
	 */
	trace_msm_atomic_रुको_flush_start(crtc_mask);
	kms->funcs->रुको_flush(kms, crtc_mask);
	trace_msm_atomic_रुको_flush_finish(crtc_mask);

	vblank_put(kms, crtc_mask);

	kms->funcs->complete_commit(kms, crtc_mask);
	unlock_crtcs(kms, crtc_mask);
	kms->funcs->disable_commit(kms);

out:
	trace_msm_atomic_async_commit_finish(crtc_mask);
पूर्ण

अटल क्रमागत hrसमयr_restart msm_atomic_pending_समयr(काष्ठा hrसमयr *t)
अणु
	काष्ठा msm_pending_समयr *समयr = container_of(t,
			काष्ठा msm_pending_समयr, समयr);

	kthपढ़ो_queue_work(समयr->worker, &समयr->work);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम msm_atomic_pending_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा msm_pending_समयr *समयr = container_of(work,
			काष्ठा msm_pending_समयr, work);

	msm_atomic_async_commit(समयr->kms, समयr->crtc_idx);
पूर्ण

पूर्णांक msm_atomic_init_pending_समयr(काष्ठा msm_pending_समयr *समयr,
		काष्ठा msm_kms *kms, पूर्णांक crtc_idx)
अणु
	समयr->kms = kms;
	समयr->crtc_idx = crtc_idx;
	hrसमयr_init(&समयr->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	समयr->समयr.function = msm_atomic_pending_समयr;

	समयr->worker = kthपढ़ो_create_worker(0, "atomic-worker-%d", crtc_idx);
	अगर (IS_ERR(समयr->worker)) अणु
		पूर्णांक ret = PTR_ERR(समयr->worker);
		समयr->worker = शून्य;
		वापस ret;
	पूर्ण
	sched_set_fअगरo(समयr->worker->task);
	kthपढ़ो_init_work(&समयr->work, msm_atomic_pending_work);

	वापस 0;
पूर्ण

व्योम msm_atomic_destroy_pending_समयr(काष्ठा msm_pending_समयr *समयr)
अणु
	अगर (समयr->worker)
		kthपढ़ो_destroy_worker(समयr->worker);
पूर्ण

अटल bool can_करो_async(काष्ठा drm_atomic_state *state,
		काष्ठा drm_crtc **async_crtc)
अणु
	काष्ठा drm_connector_state *connector_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i, num_crtcs = 0;

	अगर (!(state->legacy_cursor_update || state->async_update))
		वापस false;

	/* any connector change, means slow path: */
	क्रम_each_new_connector_in_state(state, connector, connector_state, i)
		वापस false;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (drm_atomic_crtc_needs_modeset(crtc_state))
			वापस false;
		अगर (++num_crtcs > 1)
			वापस false;
		*async_crtc = crtc;
	पूर्ण

	वापस true;
पूर्ण

/* Get biपंचांगask of crtcs that will need to be flushed.  The biपंचांगask
 * can be used with क्रम_each_crtc_mask() iterator, to iterate
 * effected crtcs without needing to preserve the atomic state.
 */
अटल अचिन्हित get_crtc_mask(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित i, mask = 0;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i)
		mask |= drm_crtc_mask(crtc);

	वापस mask;
पूर्ण

व्योम msm_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	काष्ठा drm_crtc *async_crtc = शून्य;
	अचिन्हित crtc_mask = get_crtc_mask(state);
	bool async = kms->funcs->vsync_समय &&
			can_करो_async(state, &async_crtc);

	trace_msm_atomic_commit_tail_start(async, crtc_mask);

	kms->funcs->enable_commit(kms);

	/*
	 * Ensure any previous (potentially async) commit has
	 * completed:
	 */
	lock_crtcs(kms, crtc_mask);
	trace_msm_atomic_रुको_flush_start(crtc_mask);
	kms->funcs->रुको_flush(kms, crtc_mask);
	trace_msm_atomic_रुको_flush_finish(crtc_mask);

	/*
	 * Now that there is no in-progress flush, prepare the
	 * current update:
	 */
	kms->funcs->prepare_commit(kms, state);

	/*
	 * Push atomic updates करोwn to hardware:
	 */
	drm_atomic_helper_commit_modeset_disables(dev, state);
	drm_atomic_helper_commit_planes(dev, state, 0);
	drm_atomic_helper_commit_modeset_enables(dev, state);

	अगर (async) अणु
		काष्ठा msm_pending_समयr *समयr =
			&kms->pending_समयrs[drm_crtc_index(async_crtc)];

		/* async updates are limited to single-crtc updates: */
		WARN_ON(crtc_mask != drm_crtc_mask(async_crtc));

		/*
		 * Start समयr अगर we करोn't alपढ़ोy have an update pending
		 * on this crtc:
		 */
		अगर (!(kms->pending_crtc_mask & crtc_mask)) अणु
			kसमय_प्रकार vsync_समय, wakeup_समय;

			kms->pending_crtc_mask |= crtc_mask;

			vsync_समय = kms->funcs->vsync_समय(kms, async_crtc);
			wakeup_समय = kसमय_sub(vsync_समय, ms_to_kसमय(1));

			hrसमयr_start(&समयr->समयr, wakeup_समय,
					HRTIMER_MODE_ABS);
		पूर्ण

		kms->funcs->disable_commit(kms);
		unlock_crtcs(kms, crtc_mask);
		/*
		 * At this poपूर्णांक, from drm core's perspective, we
		 * are करोne with the atomic update, so we can just
		 * go ahead and संकेत that it is करोne:
		 */
		drm_atomic_helper_commit_hw_करोne(state);
		drm_atomic_helper_cleanup_planes(dev, state);

		trace_msm_atomic_commit_tail_finish(async, crtc_mask);

		वापस;
	पूर्ण

	/*
	 * If there is any async flush pending on updated crtcs, fold
	 * them पूर्णांकo the current flush.
	 */
	kms->pending_crtc_mask &= ~crtc_mask;

	vblank_get(kms, crtc_mask);

	/*
	 * Flush hardware updates:
	 */
	trace_msm_atomic_flush_commit(crtc_mask);
	kms->funcs->flush_commit(kms, crtc_mask);
	unlock_crtcs(kms, crtc_mask);
	/*
	 * Wait क्रम flush to complete:
	 */
	trace_msm_atomic_रुको_flush_start(crtc_mask);
	kms->funcs->रुको_flush(kms, crtc_mask);
	trace_msm_atomic_रुको_flush_finish(crtc_mask);

	vblank_put(kms, crtc_mask);

	lock_crtcs(kms, crtc_mask);
	kms->funcs->complete_commit(kms, crtc_mask);
	unlock_crtcs(kms, crtc_mask);
	kms->funcs->disable_commit(kms);

	drm_atomic_helper_commit_hw_करोne(state);
	drm_atomic_helper_cleanup_planes(dev, state);

	trace_msm_atomic_commit_tail_finish(async, crtc_mask);
पूर्ण
