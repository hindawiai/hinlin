<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2019 Google, Inc.
 *
 * Authors:
 * Sean Paul <seanpaul@chromium.org>
 */
#समावेश <linux/average.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mode_config.h>
#समावेश <drm/drm_modeset_lock.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_self_refresh_helper.h>

/**
 * DOC: overview
 *
 * This helper library provides an easy way क्रम drivers to leverage the atomic
 * framework to implement panel self refresh (SR) support. Drivers are
 * responsible क्रम initializing and cleaning up the SR helpers on load/unload
 * (see &drm_self_refresh_helper_init/&drm_self_refresh_helper_cleanup).
 * The connector is responsible क्रम setting
 * &drm_connector_state.self_refresh_aware to true at runसमय अगर it is SR-aware
 * (meaning it knows how to initiate self refresh on the panel).
 *
 * Once a crtc has enabled SR using &drm_self_refresh_helper_init, the
 * helpers will monitor activity and call back पूर्णांकo the driver to enable/disable
 * SR as appropriate. The best way to think about this is that it's a DPMS
 * on/off request with &drm_crtc_state.self_refresh_active set in crtc state
 * that tells you to disable/enable SR on the panel instead of घातer-cycling it.
 *
 * During SR, drivers may choose to fully disable their crtc/encoder/bridge
 * hardware (in which हाल no driver changes are necessary), or they can inspect
 * &drm_crtc_state.self_refresh_active अगर they want to enter low घातer mode
 * without full disable (in हाल full disable/enable is too slow).
 *
 * SR will be deactivated अगर there are any atomic updates affecting the
 * pipe that is in SR mode. If a crtc is driving multiple connectors, all
 * connectors must be SR aware and all will enter/निकास SR mode at the same समय.
 *
 * If the crtc and connector are SR aware, but the panel connected करोes not
 * support it (or is otherwise unable to enter SR), the driver should fail
 * atomic_check when &drm_crtc_state.self_refresh_active is true.
 */

#घोषणा SELF_REFRESH_AVG_SEED_MS 200

DECLARE_EWMA(psr_समय, 4, 4)

काष्ठा drm_self_refresh_data अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा delayed_work entry_work;

	काष्ठा mutex avg_mutex;
	काष्ठा ewma_psr_समय entry_avg_ms;
	काष्ठा ewma_psr_समय निकास_avg_ms;
पूर्ण;

अटल व्योम drm_self_refresh_helper_entry_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_self_refresh_data *sr_data = container_of(
				to_delayed_work(work),
				काष्ठा drm_self_refresh_data, entry_work);
	काष्ठा drm_crtc *crtc = sr_data->crtc;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक i, ret = 0;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out_drop_locks;
	पूर्ण

retry:
	state->acquire_ctx = &ctx;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state)) अणु
		ret = PTR_ERR(crtc_state);
		जाओ out;
	पूर्ण

	अगर (!crtc_state->enable)
		जाओ out;

	ret = drm_atomic_add_affected_connectors(state, crtc);
	अगर (ret)
		जाओ out;

	क्रम_each_new_connector_in_state(state, conn, conn_state, i) अणु
		अगर (!conn_state->self_refresh_aware)
			जाओ out;
	पूर्ण

	crtc_state->active = false;
	crtc_state->self_refresh_active = true;

	ret = drm_atomic_commit(state);
	अगर (ret)
		जाओ out;

out:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		ret = drm_modeset_backoff(&ctx);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

out_drop_locks:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
पूर्ण

/**
 * drm_self_refresh_helper_update_avg_बार - Updates a crtc's SR समय averages
 * @state: the state which has just been applied to hardware
 * @commit_समय_ms: the amount of समय in ms that this commit took to complete
 * @new_self_refresh_mask: biपंचांगask of crtc's that have self_refresh_active in
 *    new state
 *
 * Called after &drm_mode_config_funcs.atomic_commit_tail, this function will
 * update the average entry/निकास self refresh बार on self refresh transitions.
 * These averages will be used when calculating how दीर्घ to delay beक्रमe
 * entering self refresh mode after activity.
 */
व्योम
drm_self_refresh_helper_update_avg_बार(काष्ठा drm_atomic_state *state,
					 अचिन्हित पूर्णांक commit_समय_ms,
					 अचिन्हित पूर्णांक new_self_refresh_mask)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक i;

	क्रम_each_old_crtc_in_state(state, crtc, old_crtc_state, i) अणु
		bool new_self_refresh_active = new_self_refresh_mask & BIT(i);
		काष्ठा drm_self_refresh_data *sr_data = crtc->self_refresh_data;
		काष्ठा ewma_psr_समय *समय;

		अगर (old_crtc_state->self_refresh_active ==
		    new_self_refresh_active)
			जारी;

		अगर (new_self_refresh_active)
			समय = &sr_data->entry_avg_ms;
		अन्यथा
			समय = &sr_data->निकास_avg_ms;

		mutex_lock(&sr_data->avg_mutex);
		ewma_psr_समय_add(समय, commit_समय_ms);
		mutex_unlock(&sr_data->avg_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_self_refresh_helper_update_avg_बार);

/**
 * drm_self_refresh_helper_alter_state - Alters the atomic state क्रम SR निकास
 * @state: the state currently being checked
 *
 * Called at the end of atomic check. This function checks the state क्रम flags
 * incompatible with self refresh निकास and changes them. This is a bit
 * disingenuous since userspace is expecting one thing and we're giving it
 * another. However in order to keep self refresh entirely hidden from
 * userspace, this is required.
 *
 * At the end, we queue up the self refresh entry work so we can enter PSR after
 * the desired delay.
 */
व्योम drm_self_refresh_helper_alter_state(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक i;

	अगर (state->async_update || !state->allow_modeset) अणु
		क्रम_each_old_crtc_in_state(state, crtc, crtc_state, i) अणु
			अगर (crtc_state->self_refresh_active) अणु
				state->async_update = false;
				state->allow_modeset = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा drm_self_refresh_data *sr_data;
		अचिन्हित पूर्णांक delay;

		/* Don't trigger the entry timer when we're alपढ़ोy in SR */
		अगर (crtc_state->self_refresh_active)
			जारी;

		sr_data = crtc->self_refresh_data;
		अगर (!sr_data)
			जारी;

		mutex_lock(&sr_data->avg_mutex);
		delay = (ewma_psr_समय_पढ़ो(&sr_data->entry_avg_ms) +
			 ewma_psr_समय_पढ़ो(&sr_data->निकास_avg_ms)) * 2;
		mutex_unlock(&sr_data->avg_mutex);

		mod_delayed_work(प्रणाली_wq, &sr_data->entry_work,
				 msecs_to_jअगरfies(delay));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_self_refresh_helper_alter_state);

/**
 * drm_self_refresh_helper_init - Initializes self refresh helpers क्रम a crtc
 * @crtc: the crtc which supports self refresh supported displays
 *
 * Returns zero अगर successful or -त्रुटि_सं on failure
 */
पूर्णांक drm_self_refresh_helper_init(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_self_refresh_data *sr_data = crtc->self_refresh_data;

	/* Helper is alपढ़ोy initialized */
	अगर (WARN_ON(sr_data))
		वापस -EINVAL;

	sr_data = kzalloc(माप(*sr_data), GFP_KERNEL);
	अगर (!sr_data)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&sr_data->entry_work,
			  drm_self_refresh_helper_entry_work);
	sr_data->crtc = crtc;
	mutex_init(&sr_data->avg_mutex);
	ewma_psr_समय_init(&sr_data->entry_avg_ms);
	ewma_psr_समय_init(&sr_data->निकास_avg_ms);

	/*
	 * Seed the averages so they're non-zero (and sufficiently large
	 * क्रम even poorly perक्रमming panels). As समय goes on, this will be
	 * averaged out and the values will trend to their true value.
	 */
	ewma_psr_समय_add(&sr_data->entry_avg_ms, SELF_REFRESH_AVG_SEED_MS);
	ewma_psr_समय_add(&sr_data->निकास_avg_ms, SELF_REFRESH_AVG_SEED_MS);

	crtc->self_refresh_data = sr_data;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_self_refresh_helper_init);

/**
 * drm_self_refresh_helper_cleanup - Cleans up self refresh helpers क्रम a crtc
 * @crtc: the crtc to cleanup
 */
व्योम drm_self_refresh_helper_cleanup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_self_refresh_data *sr_data = crtc->self_refresh_data;

	/* Helper is alपढ़ोy uninitialized */
	अगर (!sr_data)
		वापस;

	crtc->self_refresh_data = शून्य;

	cancel_delayed_work_sync(&sr_data->entry_work);
	kमुक्त(sr_data);
पूर्ण
EXPORT_SYMBOL(drm_self_refresh_helper_cleanup);
