<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Copyright (C) 2014 Intel Corp.
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
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Daniel Vetter <daniel.vetter@ffwll.ch>
 */

#समावेश <linux/dma-fence.h>
#समावेश <linux/kसमय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_self_refresh_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश "drm_crtc_helper_internal.h"
#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * This helper library provides implementations of check and commit functions on
 * top of the CRTC modeset helper callbacks and the plane helper callbacks. It
 * also provides convenience implementations क्रम the atomic state handling
 * callbacks क्रम drivers which करोn't need to subclass the drm core काष्ठाures to
 * add their own additional पूर्णांकernal state.
 *
 * This library also provides शेष implementations क्रम the check callback in
 * drm_atomic_helper_check() and क्रम the commit callback with
 * drm_atomic_helper_commit(). But the inभागidual stages and callbacks are
 * exposed to allow drivers to mix and match and e.g. use the plane helpers only
 * together with a driver निजी modeset implementation.
 *
 * This library also provides implementations क्रम all the legacy driver
 * पूर्णांकerfaces on top of the atomic पूर्णांकerface. See drm_atomic_helper_set_config(),
 * drm_atomic_helper_disable_plane(), and the various functions to implement
 * set_property callbacks. New drivers must not implement these functions
 * themselves but must use the provided helpers.
 *
 * The atomic helper uses the same function table काष्ठाures as all other
 * modesetting helpers. See the करोcumentation क्रम &काष्ठा drm_crtc_helper_funcs,
 * काष्ठा &drm_encoder_helper_funcs and &काष्ठा drm_connector_helper_funcs. It
 * also shares the &काष्ठा drm_plane_helper_funcs function table with the plane
 * helpers.
 */
अटल व्योम
drm_atomic_helper_plane_changed(काष्ठा drm_atomic_state *state,
				काष्ठा drm_plane_state *old_plane_state,
				काष्ठा drm_plane_state *plane_state,
				काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_crtc_state *crtc_state;

	अगर (old_plane_state->crtc) अणु
		crtc_state = drm_atomic_get_new_crtc_state(state,
							   old_plane_state->crtc);

		अगर (WARN_ON(!crtc_state))
			वापस;

		crtc_state->planes_changed = true;
	पूर्ण

	अगर (plane_state->crtc) अणु
		crtc_state = drm_atomic_get_new_crtc_state(state, plane_state->crtc);

		अगर (WARN_ON(!crtc_state))
			वापस;

		crtc_state->planes_changed = true;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_conflicting_encoders(काष्ठा drm_atomic_state *state,
				       bool disable_conflicting_encoders)
अणु
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_encoder *encoder;
	अचिन्हित encoder_mask = 0;
	पूर्णांक i, ret = 0;

	/*
	 * First loop, find all newly asचिन्हित encoders from the connectors
	 * part of the state. If the same encoder is asचिन्हित to multiple
	 * connectors bail out.
	 */
	क्रम_each_new_connector_in_state(state, connector, new_conn_state, i) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *funcs = connector->helper_निजी;
		काष्ठा drm_encoder *new_encoder;

		अगर (!new_conn_state->crtc)
			जारी;

		अगर (funcs->atomic_best_encoder)
			new_encoder = funcs->atomic_best_encoder(connector,
								 state);
		अन्यथा अगर (funcs->best_encoder)
			new_encoder = funcs->best_encoder(connector);
		अन्यथा
			new_encoder = drm_connector_get_single_encoder(connector);

		अगर (new_encoder) अणु
			अगर (encoder_mask & drm_encoder_mask(new_encoder)) अणु
				DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] on [CONNECTOR:%d:%s] already assigned\n",
					new_encoder->base.id, new_encoder->name,
					connector->base.id, connector->name);

				वापस -EINVAL;
			पूर्ण

			encoder_mask |= drm_encoder_mask(new_encoder);
		पूर्ण
	पूर्ण

	अगर (!encoder_mask)
		वापस 0;

	/*
	 * Second loop, iterate over all connectors not part of the state.
	 *
	 * If a conflicting encoder is found and disable_conflicting_encoders
	 * is not set, an error is वापसed. Userspace can provide a solution
	 * through the atomic ioctl.
	 *
	 * If the flag is set conflicting connectors are हटाओd from the CRTC
	 * and the CRTC is disabled अगर no encoder is left. This preserves
	 * compatibility with the legacy set_config behavior.
	 */
	drm_connector_list_iter_begin(state->dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_crtc_state *crtc_state;

		अगर (drm_atomic_get_new_connector_state(state, connector))
			जारी;

		encoder = connector->state->best_encoder;
		अगर (!encoder || !(encoder_mask & drm_encoder_mask(encoder)))
			जारी;

		अगर (!disable_conflicting_encoders) अणु
			DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] in use on [CRTC:%d:%s] by [CONNECTOR:%d:%s]\n",
					 encoder->base.id, encoder->name,
					 connector->state->crtc->base.id,
					 connector->state->crtc->name,
					 connector->base.id, connector->name);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		new_conn_state = drm_atomic_get_connector_state(state, connector);
		अगर (IS_ERR(new_conn_state)) अणु
			ret = PTR_ERR(new_conn_state);
			जाओ out;
		पूर्ण

		DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] in use on [CRTC:%d:%s], disabling [CONNECTOR:%d:%s]\n",
				 encoder->base.id, encoder->name,
				 new_conn_state->crtc->base.id, new_conn_state->crtc->name,
				 connector->base.id, connector->name);

		crtc_state = drm_atomic_get_new_crtc_state(state, new_conn_state->crtc);

		ret = drm_atomic_set_crtc_क्रम_connector(new_conn_state, शून्य);
		अगर (ret)
			जाओ out;

		अगर (!crtc_state->connector_mask) अणु
			ret = drm_atomic_set_mode_prop_क्रम_crtc(crtc_state,
								शून्य);
			अगर (ret < 0)
				जाओ out;

			crtc_state->active = false;
		पूर्ण
	पूर्ण
out:
	drm_connector_list_iter_end(&conn_iter);

	वापस ret;
पूर्ण

अटल व्योम
set_best_encoder(काष्ठा drm_atomic_state *state,
		 काष्ठा drm_connector_state *conn_state,
		 काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;

	अगर (conn_state->best_encoder) अणु
		/* Unset the encoder_mask in the old crtc state. */
		crtc = conn_state->connector->state->crtc;

		/* A शून्य crtc is an error here because we should have
		 * duplicated a शून्य best_encoder when crtc was शून्य.
		 * As an exception restoring duplicated atomic state
		 * during resume is allowed, so करोn't warn when
		 * best_encoder is equal to encoder we पूर्णांकend to set.
		 */
		WARN_ON(!crtc && encoder != conn_state->best_encoder);
		अगर (crtc) अणु
			crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

			crtc_state->encoder_mask &=
				~drm_encoder_mask(conn_state->best_encoder);
		पूर्ण
	पूर्ण

	अगर (encoder) अणु
		crtc = conn_state->crtc;
		WARN_ON(!crtc);
		अगर (crtc) अणु
			crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

			crtc_state->encoder_mask |=
				drm_encoder_mask(encoder);
		पूर्ण
	पूर्ण

	conn_state->best_encoder = encoder;
पूर्ण

अटल व्योम
steal_encoder(काष्ठा drm_atomic_state *state,
	      काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_connector_state, *new_connector_state;
	पूर्णांक i;

	क्रम_each_oldnew_connector_in_state(state, connector, old_connector_state, new_connector_state, i) अणु
		काष्ठा drm_crtc *encoder_crtc;

		अगर (new_connector_state->best_encoder != encoder)
			जारी;

		encoder_crtc = old_connector_state->crtc;

		DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] in use on [CRTC:%d:%s], stealing it\n",
				 encoder->base.id, encoder->name,
				 encoder_crtc->base.id, encoder_crtc->name);

		set_best_encoder(state, new_connector_state, शून्य);

		crtc_state = drm_atomic_get_new_crtc_state(state, encoder_crtc);
		crtc_state->connectors_changed = true;

		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक
update_connector_routing(काष्ठा drm_atomic_state *state,
			 काष्ठा drm_connector *connector,
			 काष्ठा drm_connector_state *old_connector_state,
			 काष्ठा drm_connector_state *new_connector_state)
अणु
	स्थिर काष्ठा drm_connector_helper_funcs *funcs;
	काष्ठा drm_encoder *new_encoder;
	काष्ठा drm_crtc_state *crtc_state;

	DRM_DEBUG_ATOMIC("Updating routing for [CONNECTOR:%d:%s]\n",
			 connector->base.id,
			 connector->name);

	अगर (old_connector_state->crtc != new_connector_state->crtc) अणु
		अगर (old_connector_state->crtc) अणु
			crtc_state = drm_atomic_get_new_crtc_state(state, old_connector_state->crtc);
			crtc_state->connectors_changed = true;
		पूर्ण

		अगर (new_connector_state->crtc) अणु
			crtc_state = drm_atomic_get_new_crtc_state(state, new_connector_state->crtc);
			crtc_state->connectors_changed = true;
		पूर्ण
	पूर्ण

	अगर (!new_connector_state->crtc) अणु
		DRM_DEBUG_ATOMIC("Disabling [CONNECTOR:%d:%s]\n",
				connector->base.id,
				connector->name);

		set_best_encoder(state, new_connector_state, शून्य);

		वापस 0;
	पूर्ण

	crtc_state = drm_atomic_get_new_crtc_state(state,
						   new_connector_state->crtc);
	/*
	 * For compatibility with legacy users, we want to make sure that
	 * we allow DPMS On->Off modesets on unरेजिस्टरed connectors. Modesets
	 * which would result in anything अन्यथा must be considered invalid, to
	 * aव्योम turning on new displays on dead connectors.
	 *
	 * Since the connector can be unरेजिस्टरed at any poपूर्णांक during an
	 * atomic check or commit, this is racy. But that's OK: all we care
	 * about is ensuring that userspace can't करो anything but shut off the
	 * display on a connector that was destroyed after it's been notअगरied,
	 * not beक्रमe.
	 *
	 * Additionally, we also want to ignore connector registration when
	 * we're trying to restore an atomic state during प्रणाली resume since
	 * there's a chance the connector may have been destroyed during the
	 * process, but it's better to ignore that then cause
	 * drm_atomic_helper_resume() to fail.
	 */
	अगर (!state->duplicated && drm_connector_is_unरेजिस्टरed(connector) &&
	    crtc_state->active) अणु
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] is not registered\n",
				 connector->base.id, connector->name);
		वापस -EINVAL;
	पूर्ण

	funcs = connector->helper_निजी;

	अगर (funcs->atomic_best_encoder)
		new_encoder = funcs->atomic_best_encoder(connector, state);
	अन्यथा अगर (funcs->best_encoder)
		new_encoder = funcs->best_encoder(connector);
	अन्यथा
		new_encoder = drm_connector_get_single_encoder(connector);

	अगर (!new_encoder) अणु
		DRM_DEBUG_ATOMIC("No suitable encoder found for [CONNECTOR:%d:%s]\n",
				 connector->base.id,
				 connector->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!drm_encoder_crtc_ok(new_encoder, new_connector_state->crtc)) अणु
		DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] incompatible with [CRTC:%d:%s]\n",
				 new_encoder->base.id,
				 new_encoder->name,
				 new_connector_state->crtc->base.id,
				 new_connector_state->crtc->name);
		वापस -EINVAL;
	पूर्ण

	अगर (new_encoder == new_connector_state->best_encoder) अणु
		set_best_encoder(state, new_connector_state, new_encoder);

		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] keeps [ENCODER:%d:%s], now on [CRTC:%d:%s]\n",
				 connector->base.id,
				 connector->name,
				 new_encoder->base.id,
				 new_encoder->name,
				 new_connector_state->crtc->base.id,
				 new_connector_state->crtc->name);

		वापस 0;
	पूर्ण

	steal_encoder(state, new_encoder);

	set_best_encoder(state, new_connector_state, new_encoder);

	crtc_state->connectors_changed = true;

	DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] using [ENCODER:%d:%s] on [CRTC:%d:%s]\n",
			 connector->base.id,
			 connector->name,
			 new_encoder->base.id,
			 new_encoder->name,
			 new_connector_state->crtc->base.id,
			 new_connector_state->crtc->name);

	वापस 0;
पूर्ण

अटल पूर्णांक
mode_fixup(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (!new_crtc_state->mode_changed &&
		    !new_crtc_state->connectors_changed)
			जारी;

		drm_mode_copy(&new_crtc_state->adjusted_mode, &new_crtc_state->mode);
	पूर्ण

	क्रम_each_new_connector_in_state(state, connector, new_conn_state, i) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *funcs;
		काष्ठा drm_encoder *encoder;
		काष्ठा drm_bridge *bridge;

		WARN_ON(!!new_conn_state->best_encoder != !!new_conn_state->crtc);

		अगर (!new_conn_state->crtc || !new_conn_state->best_encoder)
			जारी;

		new_crtc_state =
			drm_atomic_get_new_crtc_state(state, new_conn_state->crtc);

		/*
		 * Each encoder has at most one connector (since we always steal
		 * it away), so we won't call ->mode_fixup twice.
		 */
		encoder = new_conn_state->best_encoder;
		funcs = encoder->helper_निजी;

		bridge = drm_bridge_chain_get_first_bridge(encoder);
		ret = drm_atomic_bridge_chain_check(bridge,
						    new_crtc_state,
						    new_conn_state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("Bridge atomic check failed\n");
			वापस ret;
		पूर्ण

		अगर (funcs && funcs->atomic_check) अणु
			ret = funcs->atomic_check(encoder, new_crtc_state,
						  new_conn_state);
			अगर (ret) अणु
				DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] check failed\n",
						 encoder->base.id, encoder->name);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अगर (funcs && funcs->mode_fixup) अणु
			ret = funcs->mode_fixup(encoder, &new_crtc_state->mode,
						&new_crtc_state->adjusted_mode);
			अगर (!ret) अणु
				DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] fixup failed\n",
						 encoder->base.id, encoder->name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		अगर (!new_crtc_state->enable)
			जारी;

		अगर (!new_crtc_state->mode_changed &&
		    !new_crtc_state->connectors_changed)
			जारी;

		funcs = crtc->helper_निजी;
		अगर (!funcs || !funcs->mode_fixup)
			जारी;

		ret = funcs->mode_fixup(crtc, &new_crtc_state->mode,
					&new_crtc_state->adjusted_mode);
		अगर (!ret) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] fixup failed\n",
					 crtc->base.id, crtc->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status mode_valid_path(काष्ठा drm_connector *connector,
					    काष्ठा drm_encoder *encoder,
					    काष्ठा drm_crtc *crtc,
					    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_bridge *bridge;
	क्रमागत drm_mode_status ret;

	ret = drm_encoder_mode_valid(encoder, mode);
	अगर (ret != MODE_OK) अणु
		DRM_DEBUG_ATOMIC("[ENCODER:%d:%s] mode_valid() failed\n",
				encoder->base.id, encoder->name);
		वापस ret;
	पूर्ण

	bridge = drm_bridge_chain_get_first_bridge(encoder);
	ret = drm_bridge_chain_mode_valid(bridge, &connector->display_info,
					  mode);
	अगर (ret != MODE_OK) अणु
		DRM_DEBUG_ATOMIC("[BRIDGE] mode_valid() failed\n");
		वापस ret;
	पूर्ण

	ret = drm_crtc_mode_valid(crtc, mode);
	अगर (ret != MODE_OK) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] mode_valid() failed\n",
				crtc->base.id, crtc->name);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mode_valid(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(state, connector, conn_state, i) अणु
		काष्ठा drm_encoder *encoder = conn_state->best_encoder;
		काष्ठा drm_crtc *crtc = conn_state->crtc;
		काष्ठा drm_crtc_state *crtc_state;
		क्रमागत drm_mode_status mode_status;
		स्थिर काष्ठा drm_display_mode *mode;

		अगर (!crtc || !encoder)
			जारी;

		crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
		अगर (!crtc_state)
			जारी;
		अगर (!crtc_state->mode_changed && !crtc_state->connectors_changed)
			जारी;

		mode = &crtc_state->mode;

		mode_status = mode_valid_path(connector, encoder, crtc, mode);
		अगर (mode_status != MODE_OK)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_atomic_helper_check_modeset - validate state object क्रम modeset changes
 * @dev: DRM device
 * @state: the driver state object
 *
 * Check the state object to see अगर the requested state is physically possible.
 * This करोes all the CRTC and connector related computations क्रम an atomic
 * update and adds any additional connectors needed क्रम full modesets. It calls
 * the various per-object callbacks in the follow order:
 *
 * 1. &drm_connector_helper_funcs.atomic_best_encoder क्रम determining the new encoder.
 * 2. &drm_connector_helper_funcs.atomic_check to validate the connector state.
 * 3. If it's determined a modeset is needed then all connectors on the affected
 *    CRTC are added and &drm_connector_helper_funcs.atomic_check is run on them.
 * 4. &drm_encoder_helper_funcs.mode_valid, &drm_bridge_funcs.mode_valid and
 *    &drm_crtc_helper_funcs.mode_valid are called on the affected components.
 * 5. &drm_bridge_funcs.mode_fixup is called on all encoder bridges.
 * 6. &drm_encoder_helper_funcs.atomic_check is called to validate any encoder state.
 *    This function is only called when the encoder will be part of a configured CRTC,
 *    it must not be used क्रम implementing connector property validation.
 *    If this function is शून्य, &drm_atomic_encoder_helper_funcs.mode_fixup is called
 *    instead.
 * 7. &drm_crtc_helper_funcs.mode_fixup is called last, to fix up the mode with CRTC स्थिरraपूर्णांकs.
 *
 * &drm_crtc_state.mode_changed is set when the input mode is changed.
 * &drm_crtc_state.connectors_changed is set when a connector is added or
 * हटाओd from the CRTC.  &drm_crtc_state.active_changed is set when
 * &drm_crtc_state.active changes, which is used क्रम DPMS.
 * &drm_crtc_state.no_vblank is set from the result of drm_dev_has_vblank().
 * See also: drm_atomic_crtc_needs_modeset()
 *
 * IMPORTANT:
 *
 * Drivers which set &drm_crtc_state.mode_changed (e.g. in their
 * &drm_plane_helper_funcs.atomic_check hooks अगर a plane update can't be करोne
 * without a full modeset) _must_ call this function after that change. It is
 * permitted to call this function multiple बार क्रम the same update, e.g.
 * when the &drm_crtc_helper_funcs.atomic_check functions depend upon the
 * adjusted करोtघड़ी क्रम fअगरo space allocation and watermark computation.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक
drm_atomic_helper_check_modeset(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_connector_state, *new_connector_state;
	पूर्णांक i, ret;
	अचिन्हित connectors_mask = 0;

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		bool has_connectors =
			!!new_crtc_state->connector_mask;

		WARN_ON(!drm_modeset_is_locked(&crtc->mutex));

		अगर (!drm_mode_equal(&old_crtc_state->mode, &new_crtc_state->mode)) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] mode changed\n",
					 crtc->base.id, crtc->name);
			new_crtc_state->mode_changed = true;
		पूर्ण

		अगर (old_crtc_state->enable != new_crtc_state->enable) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] enable changed\n",
					 crtc->base.id, crtc->name);

			/*
			 * For clarity this assignment is करोne here, but
			 * enable == 0 is only true when there are no
			 * connectors and a शून्य mode.
			 *
			 * The other way around is true as well. enable != 0
			 * अगरf connectors are attached and a mode is set.
			 */
			new_crtc_state->mode_changed = true;
			new_crtc_state->connectors_changed = true;
		पूर्ण

		अगर (old_crtc_state->active != new_crtc_state->active) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] active changed\n",
					 crtc->base.id, crtc->name);
			new_crtc_state->active_changed = true;
		पूर्ण

		अगर (new_crtc_state->enable != has_connectors) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] enabled/connectors mismatch\n",
					 crtc->base.id, crtc->name);

			वापस -EINVAL;
		पूर्ण

		अगर (drm_dev_has_vblank(dev))
			new_crtc_state->no_vblank = false;
		अन्यथा
			new_crtc_state->no_vblank = true;
	पूर्ण

	ret = handle_conflicting_encoders(state, false);
	अगर (ret)
		वापस ret;

	क्रम_each_oldnew_connector_in_state(state, connector, old_connector_state, new_connector_state, i) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *funcs = connector->helper_निजी;

		WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));

		/*
		 * This only sets crtc->connectors_changed क्रम routing changes,
		 * drivers must set crtc->connectors_changed themselves when
		 * connector properties need to be updated.
		 */
		ret = update_connector_routing(state, connector,
					       old_connector_state,
					       new_connector_state);
		अगर (ret)
			वापस ret;
		अगर (old_connector_state->crtc) अणु
			new_crtc_state = drm_atomic_get_new_crtc_state(state,
								       old_connector_state->crtc);
			अगर (old_connector_state->link_status !=
			    new_connector_state->link_status)
				new_crtc_state->connectors_changed = true;

			अगर (old_connector_state->max_requested_bpc !=
			    new_connector_state->max_requested_bpc)
				new_crtc_state->connectors_changed = true;
		पूर्ण

		अगर (funcs->atomic_check)
			ret = funcs->atomic_check(connector, state);
		अगर (ret)
			वापस ret;

		connectors_mask |= BIT(i);
	पूर्ण

	/*
	 * After all the routing has been prepared we need to add in any
	 * connector which is itself unchanged, but whose CRTC changes its
	 * configuration. This must be करोne beक्रमe calling mode_fixup in हाल a
	 * crtc only changed its mode but has the same set of connectors.
	 */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] needs all connectors, enable: %c, active: %c\n",
				 crtc->base.id, crtc->name,
				 new_crtc_state->enable ? 'y' : 'n',
				 new_crtc_state->active ? 'y' : 'n');

		ret = drm_atomic_add_affected_connectors(state, crtc);
		अगर (ret != 0)
			वापस ret;

		ret = drm_atomic_add_affected_planes(state, crtc);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	/*
	 * Iterate over all connectors again, to make sure atomic_check()
	 * has been called on them when a modeset is क्रमced.
	 */
	क्रम_each_oldnew_connector_in_state(state, connector, old_connector_state, new_connector_state, i) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *funcs = connector->helper_निजी;

		अगर (connectors_mask & BIT(i))
			जारी;

		अगर (funcs->atomic_check)
			ret = funcs->atomic_check(connector, state);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Iterate over all connectors again, and add all affected bridges to
	 * the state.
	 */
	क्रम_each_oldnew_connector_in_state(state, connector,
					   old_connector_state,
					   new_connector_state, i) अणु
		काष्ठा drm_encoder *encoder;

		encoder = old_connector_state->best_encoder;
		ret = drm_atomic_add_encoder_bridges(state, encoder);
		अगर (ret)
			वापस ret;

		encoder = new_connector_state->best_encoder;
		ret = drm_atomic_add_encoder_bridges(state, encoder);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mode_valid(state);
	अगर (ret)
		वापस ret;

	वापस mode_fixup(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_check_modeset);

/**
 * drm_atomic_helper_check_plane_state() - Check plane state क्रम validity
 * @plane_state: plane state to check
 * @crtc_state: CRTC state to check
 * @min_scale: minimum @src:@dest scaling factor in 16.16 fixed poपूर्णांक
 * @max_scale: maximum @src:@dest scaling factor in 16.16 fixed poपूर्णांक
 * @can_position: is it legal to position the plane such that it
 *                करोesn't cover the entire CRTC?  This will generally
 *                only be false क्रम primary planes.
 * @can_update_disabled: can the plane be updated जबतक the CRTC
 *                       is disabled?
 *
 * Checks that a desired plane update is valid, and updates various
 * bits of derived state (clipped coordinates etc.). Drivers that provide
 * their own plane handling rather than helper-provided implementations may
 * still wish to call this function to aव्योम duplication of error checking
 * code.
 *
 * RETURNS:
 * Zero अगर update appears valid, error code on failure
 */
पूर्णांक drm_atomic_helper_check_plane_state(काष्ठा drm_plane_state *plane_state,
					स्थिर काष्ठा drm_crtc_state *crtc_state,
					पूर्णांक min_scale,
					पूर्णांक max_scale,
					bool can_position,
					bool can_update_disabled)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_rect *src = &plane_state->src;
	काष्ठा drm_rect *dst = &plane_state->dst;
	अचिन्हित पूर्णांक rotation = plane_state->rotation;
	काष्ठा drm_rect clip = अणुपूर्ण;
	पूर्णांक hscale, vscale;

	WARN_ON(plane_state->crtc && plane_state->crtc != crtc_state->crtc);

	*src = drm_plane_state_src(plane_state);
	*dst = drm_plane_state_dest(plane_state);

	अगर (!fb) अणु
		plane_state->visible = false;
		वापस 0;
	पूर्ण

	/* crtc should only be शून्य when disabling (i.e., !fb) */
	अगर (WARN_ON(!plane_state->crtc)) अणु
		plane_state->visible = false;
		वापस 0;
	पूर्ण

	अगर (!crtc_state->enable && !can_update_disabled) अणु
		DRM_DEBUG_KMS("Cannot update plane of a disabled CRTC.\n");
		वापस -EINVAL;
	पूर्ण

	drm_rect_rotate(src, fb->width << 16, fb->height << 16, rotation);

	/* Check scaling */
	hscale = drm_rect_calc_hscale(src, dst, min_scale, max_scale);
	vscale = drm_rect_calc_vscale(src, dst, min_scale, max_scale);
	अगर (hscale < 0 || vscale < 0) अणु
		DRM_DEBUG_KMS("Invalid scaling of plane\n");
		drm_rect_debug_prपूर्णांक("src: ", &plane_state->src, true);
		drm_rect_debug_prपूर्णांक("dst: ", &plane_state->dst, false);
		वापस -दुस्फल;
	पूर्ण

	अगर (crtc_state->enable)
		drm_mode_get_hv_timing(&crtc_state->mode, &clip.x2, &clip.y2);

	plane_state->visible = drm_rect_clip_scaled(src, dst, &clip);

	drm_rect_rotate_inv(src, fb->width << 16, fb->height << 16, rotation);

	अगर (!plane_state->visible)
		/*
		 * Plane isn't visible; some drivers can handle this
		 * so we just वापस success here.  Drivers that can't
		 * (including those that use the primary plane helper's
		 * update function) will वापस an error from their
		 * update_plane handler.
		 */
		वापस 0;

	अगर (!can_position && !drm_rect_equals(dst, &clip)) अणु
		DRM_DEBUG_KMS("Plane must cover entire CRTC\n");
		drm_rect_debug_prपूर्णांक("dst: ", dst, false);
		drm_rect_debug_prपूर्णांक("clip: ", &clip, false);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_check_plane_state);

/**
 * drm_atomic_helper_check_planes - validate state object क्रम planes changes
 * @dev: DRM device
 * @state: the driver state object
 *
 * Check the state object to see अगर the requested state is physically possible.
 * This करोes all the plane update related checks using by calling पूर्णांकo the
 * &drm_crtc_helper_funcs.atomic_check and &drm_plane_helper_funcs.atomic_check
 * hooks provided by the driver.
 *
 * It also sets &drm_crtc_state.planes_changed to indicate that a CRTC has
 * updated planes.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक
drm_atomic_helper_check_planes(काष्ठा drm_device *dev,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *new_plane_state, *old_plane_state;
	पूर्णांक i, ret = 0;

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *funcs;

		WARN_ON(!drm_modeset_is_locked(&plane->mutex));

		funcs = plane->helper_निजी;

		drm_atomic_helper_plane_changed(state, old_plane_state, new_plane_state, plane);

		drm_atomic_helper_check_plane_damage(state, new_plane_state);

		अगर (!funcs || !funcs->atomic_check)
			जारी;

		ret = funcs->atomic_check(plane, state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("[PLANE:%d:%s] atomic driver check failed\n",
					 plane->base.id, plane->name);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		funcs = crtc->helper_निजी;

		अगर (!funcs || !funcs->atomic_check)
			जारी;

		ret = funcs->atomic_check(crtc, state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] atomic driver check failed\n",
					 crtc->base.id, crtc->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_check_planes);

/**
 * drm_atomic_helper_check - validate state object
 * @dev: DRM device
 * @state: the driver state object
 *
 * Check the state object to see अगर the requested state is physically possible.
 * Only CRTCs and planes have check callbacks, so क्रम any additional (global)
 * checking that a driver needs it can simply wrap that around this function.
 * Drivers without such needs can directly use this as their
 * &drm_mode_config_funcs.atomic_check callback.
 *
 * This just wraps the two parts of the state checking क्रम planes and modeset
 * state in the शेष order: First it calls drm_atomic_helper_check_modeset()
 * and then drm_atomic_helper_check_planes(). The assumption is that the
 * @drm_plane_helper_funcs.atomic_check and @drm_crtc_helper_funcs.atomic_check
 * functions depend upon an updated adjusted_mode.घड़ी to e.g. properly compute
 * watermarks.
 *
 * Note that zpos normalization will add all enable planes to the state which
 * might not desired क्रम some drivers.
 * For example enable/disable of a cursor plane which have fixed zpos value
 * would trigger all other enabled planes to be क्रमced to the state change.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक drm_atomic_helper_check(काष्ठा drm_device *dev,
			    काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक ret;

	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		वापस ret;

	अगर (dev->mode_config.normalize_zpos) अणु
		ret = drm_atomic_normalize_zpos(dev, state);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = drm_atomic_helper_check_planes(dev, state);
	अगर (ret)
		वापस ret;

	अगर (state->legacy_cursor_update)
		state->async_update = !drm_atomic_helper_async_check(dev, state);

	drm_self_refresh_helper_alter_state(state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_check);

अटल bool
crtc_needs_disable(काष्ठा drm_crtc_state *old_state,
		   काष्ठा drm_crtc_state *new_state)
अणु
	/*
	 * No new_state means the CRTC is off, so the only criteria is whether
	 * it's currently active or in self refresh mode.
	 */
	अगर (!new_state)
		वापस drm_atomic_crtc_effectively_active(old_state);

	/*
	 * We need to run through the crtc_funcs->disable() function अगर the CRTC
	 * is currently on, अगर it's transitioning to self refresh mode, or अगर
	 * it's in self refresh mode and needs to be fully disabled.
	 */
	वापस old_state->active ||
	       (old_state->self_refresh_active && !new_state->enable) ||
	       new_state->self_refresh_active;
पूर्ण

अटल व्योम
disable_outमाला_दो(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_conn_state, *new_conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	पूर्णांक i;

	क्रम_each_oldnew_connector_in_state(old_state, connector, old_conn_state, new_conn_state, i) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *funcs;
		काष्ठा drm_encoder *encoder;
		काष्ठा drm_bridge *bridge;

		/* Shut करोwn everything that's in the changeset and currently
		 * still on. So need to check the old, saved state. */
		अगर (!old_conn_state->crtc)
			जारी;

		old_crtc_state = drm_atomic_get_old_crtc_state(old_state, old_conn_state->crtc);

		अगर (new_conn_state->crtc)
			new_crtc_state = drm_atomic_get_new_crtc_state(
						old_state,
						new_conn_state->crtc);
		अन्यथा
			new_crtc_state = शून्य;

		अगर (!crtc_needs_disable(old_crtc_state, new_crtc_state) ||
		    !drm_atomic_crtc_needs_modeset(old_conn_state->crtc->state))
			जारी;

		encoder = old_conn_state->best_encoder;

		/* We shouldn't get this far if we didn't previously have
		 * an encoder.. but WARN_ON() rather than explode.
		 */
		अगर (WARN_ON(!encoder))
			जारी;

		funcs = encoder->helper_निजी;

		DRM_DEBUG_ATOMIC("disabling [ENCODER:%d:%s]\n",
				 encoder->base.id, encoder->name);

		/*
		 * Each encoder has at most one connector (since we always steal
		 * it away), so we won't call disable hooks twice.
		 */
		bridge = drm_bridge_chain_get_first_bridge(encoder);
		drm_atomic_bridge_chain_disable(bridge, old_state);

		/* Right function depends upon target state. */
		अगर (funcs) अणु
			अगर (funcs->atomic_disable)
				funcs->atomic_disable(encoder, old_state);
			अन्यथा अगर (new_conn_state->crtc && funcs->prepare)
				funcs->prepare(encoder);
			अन्यथा अगर (funcs->disable)
				funcs->disable(encoder);
			अन्यथा अगर (funcs->dpms)
				funcs->dpms(encoder, DRM_MODE_DPMS_OFF);
		पूर्ण

		drm_atomic_bridge_chain_post_disable(bridge, old_state);
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;
		पूर्णांक ret;

		/* Shut करोwn everything that needs a full modeset. */
		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

		अगर (!crtc_needs_disable(old_crtc_state, new_crtc_state))
			जारी;

		funcs = crtc->helper_निजी;

		DRM_DEBUG_ATOMIC("disabling [CRTC:%d:%s]\n",
				 crtc->base.id, crtc->name);


		/* Right function depends upon target state. */
		अगर (new_crtc_state->enable && funcs->prepare)
			funcs->prepare(crtc);
		अन्यथा अगर (funcs->atomic_disable)
			funcs->atomic_disable(crtc, old_state);
		अन्यथा अगर (funcs->disable)
			funcs->disable(crtc);
		अन्यथा अगर (funcs->dpms)
			funcs->dpms(crtc, DRM_MODE_DPMS_OFF);

		अगर (!drm_dev_has_vblank(dev))
			जारी;

		ret = drm_crtc_vblank_get(crtc);
		WARN_ONCE(ret != -EINVAL, "driver forgot to call drm_crtc_vblank_off()\n");
		अगर (ret == 0)
			drm_crtc_vblank_put(crtc);
	पूर्ण
पूर्ण

/**
 * drm_atomic_helper_update_legacy_modeset_state - update legacy modeset state
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function updates all the various legacy modeset state poपूर्णांकers in
 * connectors, encoders and CRTCs.
 *
 * Drivers can use this क्रम building their own atomic commit अगर they करोn't have
 * a pure helper-based modeset implementation.
 *
 * Since these updates are not synchronized with lockings, only code paths
 * called from &drm_mode_config_helper_funcs.atomic_commit_tail can look at the
 * legacy state filled out by this helper. Defacto this means this helper and
 * the legacy state poपूर्णांकers are only really useful क्रम transitioning an
 * existing driver to the atomic world.
 */
व्योम
drm_atomic_helper_update_legacy_modeset_state(काष्ठा drm_device *dev,
					      काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_conn_state, *new_conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	पूर्णांक i;

	/* clear out existing links and update dpms */
	क्रम_each_oldnew_connector_in_state(old_state, connector, old_conn_state, new_conn_state, i) अणु
		अगर (connector->encoder) अणु
			WARN_ON(!connector->encoder->crtc);

			connector->encoder->crtc = शून्य;
			connector->encoder = शून्य;
		पूर्ण

		crtc = new_conn_state->crtc;
		अगर ((!crtc && old_conn_state->crtc) ||
		    (crtc && drm_atomic_crtc_needs_modeset(crtc->state))) अणु
			पूर्णांक mode = DRM_MODE_DPMS_OFF;

			अगर (crtc && crtc->state->active)
				mode = DRM_MODE_DPMS_ON;

			connector->dpms = mode;
		पूर्ण
	पूर्ण

	/* set new links */
	क्रम_each_new_connector_in_state(old_state, connector, new_conn_state, i) अणु
		अगर (!new_conn_state->crtc)
			जारी;

		अगर (WARN_ON(!new_conn_state->best_encoder))
			जारी;

		connector->encoder = new_conn_state->best_encoder;
		connector->encoder->crtc = new_conn_state->crtc;
	पूर्ण

	/* set legacy state in the crtc काष्ठाure */
	क्रम_each_new_crtc_in_state(old_state, crtc, new_crtc_state, i) अणु
		काष्ठा drm_plane *primary = crtc->primary;
		काष्ठा drm_plane_state *new_plane_state;

		crtc->mode = new_crtc_state->mode;
		crtc->enabled = new_crtc_state->enable;

		new_plane_state =
			drm_atomic_get_new_plane_state(old_state, primary);

		अगर (new_plane_state && new_plane_state->crtc == crtc) अणु
			crtc->x = new_plane_state->src_x >> 16;
			crtc->y = new_plane_state->src_y >> 16;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_update_legacy_modeset_state);

/**
 * drm_atomic_helper_calc_बारtamping_स्थिरants - update vblank बारtamping स्थिरants
 * @state: atomic state object
 *
 * Updates the बारtamping स्थिरants used क्रम precise vblank बारtamps
 * by calling drm_calc_बारtamping_स्थिरants() क्रम all enabled crtcs in @state.
 */
व्योम drm_atomic_helper_calc_बारtamping_स्थिरants(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->enable)
			drm_calc_बारtamping_स्थिरants(crtc,
							&new_crtc_state->adjusted_mode);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_calc_बारtamping_स्थिरants);

अटल व्योम
crtc_set_mode(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(old_state, crtc, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		अगर (!new_crtc_state->mode_changed)
			जारी;

		funcs = crtc->helper_निजी;

		अगर (new_crtc_state->enable && funcs->mode_set_nofb) अणु
			DRM_DEBUG_ATOMIC("modeset on [CRTC:%d:%s]\n",
					 crtc->base.id, crtc->name);

			funcs->mode_set_nofb(crtc);
		पूर्ण
	पूर्ण

	क्रम_each_new_connector_in_state(old_state, connector, new_conn_state, i) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *funcs;
		काष्ठा drm_encoder *encoder;
		काष्ठा drm_display_mode *mode, *adjusted_mode;
		काष्ठा drm_bridge *bridge;

		अगर (!new_conn_state->best_encoder)
			जारी;

		encoder = new_conn_state->best_encoder;
		funcs = encoder->helper_निजी;
		new_crtc_state = new_conn_state->crtc->state;
		mode = &new_crtc_state->mode;
		adjusted_mode = &new_crtc_state->adjusted_mode;

		अगर (!new_crtc_state->mode_changed)
			जारी;

		DRM_DEBUG_ATOMIC("modeset on [ENCODER:%d:%s]\n",
				 encoder->base.id, encoder->name);

		/*
		 * Each encoder has at most one connector (since we always steal
		 * it away), so we won't call mode_set hooks twice.
		 */
		अगर (funcs && funcs->atomic_mode_set) अणु
			funcs->atomic_mode_set(encoder, new_crtc_state,
					       new_conn_state);
		पूर्ण अन्यथा अगर (funcs && funcs->mode_set) अणु
			funcs->mode_set(encoder, mode, adjusted_mode);
		पूर्ण

		bridge = drm_bridge_chain_get_first_bridge(encoder);
		drm_bridge_chain_mode_set(bridge, mode, adjusted_mode);
	पूर्ण
पूर्ण

/**
 * drm_atomic_helper_commit_modeset_disables - modeset commit to disable outमाला_दो
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function shuts करोwn all the outमाला_दो that need to be shut करोwn and
 * prepares them (अगर required) with the new mode.
 *
 * For compatibility with legacy CRTC helpers this should be called beक्रमe
 * drm_atomic_helper_commit_planes(), which is what the शेष commit function
 * करोes. But drivers with dअगरferent needs can group the modeset commits together
 * and करो the plane commits at the end. This is useful क्रम drivers करोing runसमय
 * PM since planes updates then only happen when the CRTC is actually enabled.
 */
व्योम drm_atomic_helper_commit_modeset_disables(काष्ठा drm_device *dev,
					       काष्ठा drm_atomic_state *old_state)
अणु
	disable_outमाला_दो(dev, old_state);

	drm_atomic_helper_update_legacy_modeset_state(dev, old_state);
	drm_atomic_helper_calc_बारtamping_स्थिरants(old_state);

	crtc_set_mode(dev, old_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_modeset_disables);

अटल व्योम drm_atomic_helper_commit_ग_लिखोbacks(काष्ठा drm_device *dev,
						काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(old_state, connector, new_conn_state, i) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *funcs;

		funcs = connector->helper_निजी;
		अगर (!funcs->atomic_commit)
			जारी;

		अगर (new_conn_state->ग_लिखोback_job && new_conn_state->ग_लिखोback_job->fb) अणु
			WARN_ON(connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK);
			funcs->atomic_commit(connector, old_state);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * drm_atomic_helper_commit_modeset_enables - modeset commit to enable outमाला_दो
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function enables all the outमाला_दो with the new configuration which had to
 * be turned off क्रम the update.
 *
 * For compatibility with legacy CRTC helpers this should be called after
 * drm_atomic_helper_commit_planes(), which is what the शेष commit function
 * करोes. But drivers with dअगरferent needs can group the modeset commits together
 * and करो the plane commits at the end. This is useful क्रम drivers करोing runसमय
 * PM since planes updates then only happen when the CRTC is actually enabled.
 */
व्योम drm_atomic_helper_commit_modeset_enables(काष्ठा drm_device *dev,
					      काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक i;

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		/* Need to filter out CRTCs where only planes change. */
		अगर (!drm_atomic_crtc_needs_modeset(new_crtc_state))
			जारी;

		अगर (!new_crtc_state->active)
			जारी;

		funcs = crtc->helper_निजी;

		अगर (new_crtc_state->enable) अणु
			DRM_DEBUG_ATOMIC("enabling [CRTC:%d:%s]\n",
					 crtc->base.id, crtc->name);
			अगर (funcs->atomic_enable)
				funcs->atomic_enable(crtc, old_state);
			अन्यथा अगर (funcs->commit)
				funcs->commit(crtc);
		पूर्ण
	पूर्ण

	क्रम_each_new_connector_in_state(old_state, connector, new_conn_state, i) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *funcs;
		काष्ठा drm_encoder *encoder;
		काष्ठा drm_bridge *bridge;

		अगर (!new_conn_state->best_encoder)
			जारी;

		अगर (!new_conn_state->crtc->state->active ||
		    !drm_atomic_crtc_needs_modeset(new_conn_state->crtc->state))
			जारी;

		encoder = new_conn_state->best_encoder;
		funcs = encoder->helper_निजी;

		DRM_DEBUG_ATOMIC("enabling [ENCODER:%d:%s]\n",
				 encoder->base.id, encoder->name);

		/*
		 * Each encoder has at most one connector (since we always steal
		 * it away), so we won't call enable hooks twice.
		 */
		bridge = drm_bridge_chain_get_first_bridge(encoder);
		drm_atomic_bridge_chain_pre_enable(bridge, old_state);

		अगर (funcs) अणु
			अगर (funcs->atomic_enable)
				funcs->atomic_enable(encoder, old_state);
			अन्यथा अगर (funcs->enable)
				funcs->enable(encoder);
			अन्यथा अगर (funcs->commit)
				funcs->commit(encoder);
		पूर्ण

		drm_atomic_bridge_chain_enable(bridge, old_state);
	पूर्ण

	drm_atomic_helper_commit_ग_लिखोbacks(dev, old_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_modeset_enables);

/**
 * drm_atomic_helper_रुको_क्रम_fences - रुको क्रम fences stashed in plane state
 * @dev: DRM device
 * @state: atomic state object with old state काष्ठाures
 * @pre_swap: If true, करो an पूर्णांकerruptible रुको, and @state is the new state.
 * 	Otherwise @state is the old state.
 *
 * For implicit sync, driver should fish the exclusive fence out from the
 * incoming fb's and stash it in the drm_plane_state.  This is called after
 * drm_atomic_helper_swap_state() so it uses the current plane state (and
 * just uses the atomic state to find the changed planes)
 *
 * Note that @pre_swap is needed since the poपूर्णांक where we block क्रम fences moves
 * around depending upon whether an atomic commit is blocking or
 * non-blocking. For non-blocking commit all रुकोing needs to happen after
 * drm_atomic_helper_swap_state() is called, but क्रम blocking commits we want
 * to रुको **beक्रमe** we करो anything that can't be easily rolled back. That is
 * beक्रमe we call drm_atomic_helper_swap_state().
 *
 * Returns zero अगर success or < 0 अगर dma_fence_रुको() fails.
 */
पूर्णांक drm_atomic_helper_रुको_क्रम_fences(काष्ठा drm_device *dev,
				      काष्ठा drm_atomic_state *state,
				      bool pre_swap)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *new_plane_state;
	पूर्णांक i, ret;

	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		अगर (!new_plane_state->fence)
			जारी;

		WARN_ON(!new_plane_state->fb);

		/*
		 * If रुकोing क्रम fences pre-swap (ie: nonblock), userspace can
		 * still पूर्णांकerrupt the operation. Instead of blocking until the
		 * समयr expires, make the रुको पूर्णांकerruptible.
		 */
		ret = dma_fence_रुको(new_plane_state->fence, pre_swap);
		अगर (ret)
			वापस ret;

		dma_fence_put(new_plane_state->fence);
		new_plane_state->fence = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_रुको_क्रम_fences);

/**
 * drm_atomic_helper_रुको_क्रम_vblanks - रुको क्रम vblank on CRTCs
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * Helper to, after atomic commit, रुको क्रम vblanks on all affected
 * CRTCs (ie. beक्रमe cleaning up old framebuffers using
 * drm_atomic_helper_cleanup_planes()). It will only रुको on CRTCs where the
 * framebuffers have actually changed to optimize क्रम the legacy cursor and
 * plane update use-हाल.
 *
 * Drivers using the nonblocking commit tracking support initialized by calling
 * drm_atomic_helper_setup_commit() should look at
 * drm_atomic_helper_रुको_क्रम_flip_करोne() as an alternative.
 */
व्योम
drm_atomic_helper_रुको_क्रम_vblanks(काष्ठा drm_device *dev,
		काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	पूर्णांक i, ret;
	अचिन्हित crtc_mask = 0;

	 /*
	  * Legacy cursor ioctls are completely unsynced, and userspace
	  * relies on that (by करोing tons of cursor updates).
	  */
	अगर (old_state->legacy_cursor_update)
		वापस;

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		अगर (!new_crtc_state->active)
			जारी;

		ret = drm_crtc_vblank_get(crtc);
		अगर (ret != 0)
			जारी;

		crtc_mask |= drm_crtc_mask(crtc);
		old_state->crtcs[i].last_vblank_count = drm_crtc_vblank_count(crtc);
	पूर्ण

	क्रम_each_old_crtc_in_state(old_state, crtc, old_crtc_state, i) अणु
		अगर (!(crtc_mask & drm_crtc_mask(crtc)))
			जारी;

		ret = रुको_event_समयout(dev->vblank[i].queue,
				old_state->crtcs[i].last_vblank_count !=
					drm_crtc_vblank_count(crtc),
				msecs_to_jअगरfies(100));

		WARN(!ret, "[CRTC:%d:%s] vblank wait timed out\n",
		     crtc->base.id, crtc->name);

		drm_crtc_vblank_put(crtc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_रुको_क्रम_vblanks);

/**
 * drm_atomic_helper_रुको_क्रम_flip_करोne - रुको क्रम all page flips to be करोne
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * Helper to, after atomic commit, रुको क्रम page flips on all affected
 * crtcs (ie. beक्रमe cleaning up old framebuffers using
 * drm_atomic_helper_cleanup_planes()). Compared to
 * drm_atomic_helper_रुको_क्रम_vblanks() this रुकोs क्रम the completion on all
 * CRTCs, assuming that cursors-only updates are संकेतling their completion
 * immediately (or using a dअगरferent path).
 *
 * This requires that drivers use the nonblocking commit tracking support
 * initialized using drm_atomic_helper_setup_commit().
 */
व्योम drm_atomic_helper_रुको_क्रम_flip_करोne(काष्ठा drm_device *dev,
					  काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम (i = 0; i < dev->mode_config.num_crtc; i++) अणु
		काष्ठा drm_crtc_commit *commit = old_state->crtcs[i].commit;
		पूर्णांक ret;

		crtc = old_state->crtcs[i].ptr;

		अगर (!crtc || !commit)
			जारी;

		ret = रुको_क्रम_completion_समयout(&commit->flip_करोne, 10 * HZ);
		अगर (ret == 0)
			DRM_ERROR("[CRTC:%d:%s] flip_done timed out\n",
				  crtc->base.id, crtc->name);
	पूर्ण

	अगर (old_state->fake_commit)
		complete_all(&old_state->fake_commit->flip_करोne);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_रुको_क्रम_flip_करोne);

/**
 * drm_atomic_helper_commit_tail - commit atomic update to hardware
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This is the शेष implementation क्रम the
 * &drm_mode_config_helper_funcs.atomic_commit_tail hook, क्रम drivers
 * that करो not support runसमय_pm or करो not need the CRTC to be
 * enabled to perक्रमm a commit. Otherwise, see
 * drm_atomic_helper_commit_tail_rpm().
 *
 * Note that the शेष ordering of how the various stages are called is to
 * match the legacy modeset helper library बंदst.
 */
व्योम drm_atomic_helper_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;

	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	drm_atomic_helper_commit_planes(dev, old_state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_fake_vblank(old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);

	drm_atomic_helper_रुको_क्रम_vblanks(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_tail);

/**
 * drm_atomic_helper_commit_tail_rpm - commit atomic update to hardware
 * @old_state: new modeset state to be committed
 *
 * This is an alternative implementation क्रम the
 * &drm_mode_config_helper_funcs.atomic_commit_tail hook, क्रम drivers
 * that support runसमय_pm or need the CRTC to be enabled to perक्रमm a
 * commit. Otherwise, one should use the शेष implementation
 * drm_atomic_helper_commit_tail().
 */
व्योम drm_atomic_helper_commit_tail_rpm(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;

	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_commit_planes(dev, old_state,
					DRM_PLANE_COMMIT_ACTIVE_ONLY);

	drm_atomic_helper_fake_vblank(old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);

	drm_atomic_helper_रुको_क्रम_vblanks(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_tail_rpm);

अटल व्योम commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;
	स्थिर काष्ठा drm_mode_config_helper_funcs *funcs;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	kसमय_प्रकार start;
	s64 commit_समय_ms;
	अचिन्हित पूर्णांक i, new_self_refresh_mask = 0;

	funcs = dev->mode_config.helper_निजी;

	/*
	 * We're measuring the _entire_ commit, so the समय will vary depending
	 * on how many fences and objects are involved. For the purposes of self
	 * refresh, this is desirable since it'll give us an idea of how
	 * congested things are. This will inक्रमm our decision on how often we
	 * should enter self refresh after idle.
	 *
	 * These बार will be averaged out in the self refresh helpers to aव्योम
	 * overreacting over one outlier frame
	 */
	start = kसमय_get();

	drm_atomic_helper_रुको_क्रम_fences(dev, old_state, false);

	drm_atomic_helper_रुको_क्रम_dependencies(old_state);

	/*
	 * We cannot safely access new_crtc_state after
	 * drm_atomic_helper_commit_hw_करोne() so figure out which crtc's have
	 * self-refresh active beक्रमehand:
	 */
	क्रम_each_new_crtc_in_state(old_state, crtc, new_crtc_state, i)
		अगर (new_crtc_state->self_refresh_active)
			new_self_refresh_mask |= BIT(i);

	अगर (funcs && funcs->atomic_commit_tail)
		funcs->atomic_commit_tail(old_state);
	अन्यथा
		drm_atomic_helper_commit_tail(old_state);

	commit_समय_ms = kसमय_ms_delta(kसमय_get(), start);
	अगर (commit_समय_ms > 0)
		drm_self_refresh_helper_update_avg_बार(old_state,
						 (अचिन्हित दीर्घ)commit_समय_ms,
						 new_self_refresh_mask);

	drm_atomic_helper_commit_cleanup_करोne(old_state);

	drm_atomic_state_put(old_state);
पूर्ण

अटल व्योम commit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_atomic_state *state = container_of(work,
						      काष्ठा drm_atomic_state,
						      commit_work);
	commit_tail(state);
पूर्ण

/**
 * drm_atomic_helper_async_check - check अगर state can be commited asynchronously
 * @dev: DRM device
 * @state: the driver state object
 *
 * This helper will check अगर it is possible to commit the state asynchronously.
 * Async commits are not supposed to swap the states like normal sync commits
 * but just करो in-place changes on the current state.
 *
 * It will वापस 0 अगर the commit can happen in an asynchronous fashion or error
 * अगर not. Note that error just mean it can't be commited asynchronously, अगर it
 * fails the commit should be treated like a normal synchronous commit.
 */
पूर्णांक drm_atomic_helper_async_check(काष्ठा drm_device *dev,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_plane *plane = शून्य;
	काष्ठा drm_plane_state *old_plane_state = शून्य;
	काष्ठा drm_plane_state *new_plane_state = शून्य;
	स्थिर काष्ठा drm_plane_helper_funcs *funcs;
	पूर्णांक i, n_planes = 0;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (drm_atomic_crtc_needs_modeset(crtc_state))
			वापस -EINVAL;
	पूर्ण

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i)
		n_planes++;

	/* FIXME: we support only single plane updates क्रम now */
	अगर (n_planes != 1)
		वापस -EINVAL;

	अगर (!new_plane_state->crtc ||
	    old_plane_state->crtc != new_plane_state->crtc)
		वापस -EINVAL;

	funcs = plane->helper_निजी;
	अगर (!funcs->atomic_async_update)
		वापस -EINVAL;

	अगर (new_plane_state->fence)
		वापस -EINVAL;

	/*
	 * Don't करो an async update अगर there is an outstanding commit modअगरying
	 * the plane.  This prevents our async update's changes from getting
	 * overridden by a previous synchronous update's state.
	 */
	अगर (old_plane_state->commit &&
	    !try_रुको_क्रम_completion(&old_plane_state->commit->hw_करोne)) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] inflight previous commit preventing async commit\n",
			plane->base.id, plane->name);
		वापस -EBUSY;
	पूर्ण

	वापस funcs->atomic_async_check(plane, state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_async_check);

/**
 * drm_atomic_helper_async_commit - commit state asynchronously
 * @dev: DRM device
 * @state: the driver state object
 *
 * This function commits a state asynchronously, i.e., not vblank
 * synchronized. It should be used on a state only when
 * drm_atomic_async_check() succeeds. Async commits are not supposed to swap
 * the states like normal sync commits, but just करो in-place changes on the
 * current state.
 *
 * TODO: Implement full swap instead of करोing in-place changes.
 */
व्योम drm_atomic_helper_async_commit(काष्ठा drm_device *dev,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	स्थिर काष्ठा drm_plane_helper_funcs *funcs;
	पूर्णांक i;

	क्रम_each_new_plane_in_state(state, plane, plane_state, i) अणु
		काष्ठा drm_framebuffer *new_fb = plane_state->fb;
		काष्ठा drm_framebuffer *old_fb = plane->state->fb;

		funcs = plane->helper_निजी;
		funcs->atomic_async_update(plane, state);

		/*
		 * ->atomic_async_update() is supposed to update the
		 * plane->state in-place, make sure at least common
		 * properties have been properly updated.
		 */
		WARN_ON_ONCE(plane->state->fb != new_fb);
		WARN_ON_ONCE(plane->state->crtc_x != plane_state->crtc_x);
		WARN_ON_ONCE(plane->state->crtc_y != plane_state->crtc_y);
		WARN_ON_ONCE(plane->state->src_x != plane_state->src_x);
		WARN_ON_ONCE(plane->state->src_y != plane_state->src_y);

		/*
		 * Make sure the FBs have been swapped so that cleanups in the
		 * new_state perक्रमms a cleanup in the old FB.
		 */
		WARN_ON_ONCE(plane_state->fb != old_fb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_async_commit);

/**
 * drm_atomic_helper_commit - commit validated state object
 * @dev: DRM device
 * @state: the driver state object
 * @nonblock: whether nonblocking behavior is requested.
 *
 * This function commits a with drm_atomic_helper_check() pre-validated state
 * object. This can still fail when e.g. the framebuffer reservation fails. This
 * function implements nonblocking commits, using
 * drm_atomic_helper_setup_commit() and related functions.
 *
 * Committing the actual hardware state is करोne through the
 * &drm_mode_config_helper_funcs.atomic_commit_tail callback, or its शेष
 * implementation drm_atomic_helper_commit_tail().
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं.
 */
पूर्णांक drm_atomic_helper_commit(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state,
			     bool nonblock)
अणु
	पूर्णांक ret;

	अगर (state->async_update) अणु
		ret = drm_atomic_helper_prepare_planes(dev, state);
		अगर (ret)
			वापस ret;

		drm_atomic_helper_async_commit(dev, state);
		drm_atomic_helper_cleanup_planes(dev, state);

		वापस 0;
	पूर्ण

	ret = drm_atomic_helper_setup_commit(state, nonblock);
	अगर (ret)
		वापस ret;

	INIT_WORK(&state->commit_work, commit_work);

	ret = drm_atomic_helper_prepare_planes(dev, state);
	अगर (ret)
		वापस ret;

	अगर (!nonblock) अणु
		ret = drm_atomic_helper_रुको_क्रम_fences(dev, state, true);
		अगर (ret)
			जाओ err;
	पूर्ण

	/*
	 * This is the poपूर्णांक of no वापस - everything below never fails except
	 * when the hw goes bonghits. Which means we can commit the new state on
	 * the software side now.
	 */

	ret = drm_atomic_helper_swap_state(state, true);
	अगर (ret)
		जाओ err;

	/*
	 * Everything below can be run asynchronously without the need to grab
	 * any modeset locks at all under one condition: It must be guaranteed
	 * that the asynchronous work has either been cancelled (अगर the driver
	 * supports it, which at least requires that the framebuffers get
	 * cleaned up with drm_atomic_helper_cleanup_planes()) or completed
	 * beक्रमe the new state माला_लो committed on the software side with
	 * drm_atomic_helper_swap_state().
	 *
	 * This scheme allows new atomic state updates to be prepared and
	 * checked in parallel to the asynchronous completion of the previous
	 * update. Which is important since compositors need to figure out the
	 * composition of the next frame right after having submitted the
	 * current layout.
	 *
	 * NOTE: Commit work has multiple phases, first hardware commit, then
	 * cleanup. We want them to overlap, hence need प्रणाली_unbound_wq to
	 * make sure work items करोn't artअगरicially stall on each another.
	 */

	drm_atomic_state_get(state);
	अगर (nonblock)
		queue_work(प्रणाली_unbound_wq, &state->commit_work);
	अन्यथा
		commit_tail(state);

	वापस 0;

err:
	drm_atomic_helper_cleanup_planes(dev, state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit);

/**
 * DOC: implementing nonblocking commit
 *
 * Nonblocking atomic commits should use काष्ठा &drm_crtc_commit to sequence
 * dअगरferent operations against each another. Locks, especially काष्ठा
 * &drm_modeset_lock, should not be held in worker thपढ़ोs or any other
 * asynchronous context used to commit the hardware state.
 *
 * drm_atomic_helper_commit() implements the recommended sequence क्रम
 * nonblocking commits, using drm_atomic_helper_setup_commit() पूर्णांकernally:
 *
 * 1. Run drm_atomic_helper_prepare_planes(). Since this can fail and we
 * need to propagate out of memory/VRAM errors to userspace, it must be called
 * synchronously.
 *
 * 2. Synchronize with any outstanding nonblocking commit worker thपढ़ोs which
 * might be affected by the new state update. This is handled by
 * drm_atomic_helper_setup_commit().
 *
 * Asynchronous workers need to have sufficient parallelism to be able to run
 * dअगरferent atomic commits on dअगरferent CRTCs in parallel. The simplest way to
 * achieve this is by running them on the &प्रणाली_unbound_wq work queue. Note
 * that drivers are not required to split up atomic commits and run an
 * inभागidual commit in parallel - userspace is supposed to करो that अगर it cares.
 * But it might be beneficial to करो that क्रम modesets, since those necessarily
 * must be करोne as one global operation, and enabling or disabling a CRTC can
 * take a दीर्घ समय. But even that is not required.
 *
 * IMPORTANT: A &drm_atomic_state update क्रम multiple CRTCs is sequenced
 * against all CRTCs therein. Thereक्रमe क्रम atomic state updates which only flip
 * planes the driver must not get the काष्ठा &drm_crtc_state of unrelated CRTCs
 * in its atomic check code: This would prevent committing of atomic updates to
 * multiple CRTCs in parallel. In general, adding additional state काष्ठाures
 * should be aव्योमed as much as possible, because this reduces parallelism in
 * (nonblocking) commits, both due to locking and due to commit sequencing
 * requirements.
 *
 * 3. The software state is updated synchronously with
 * drm_atomic_helper_swap_state(). Doing this under the protection of all modeset
 * locks means concurrent callers never see inconsistent state. Note that commit
 * workers करो not hold any locks; their access is only coordinated through
 * ordering. If workers would access state only through the poपूर्णांकers in the
 * मुक्त-standing state objects (currently not the हाल क्रम any driver) then even
 * multiple pending commits could be in-flight at the same समय.
 *
 * 4. Schedule a work item to करो all subsequent steps, using the split-out
 * commit helpers: a) pre-plane commit b) plane commit c) post-plane commit and
 * then cleaning up the framebuffers after the old framebuffer is no दीर्घer
 * being displayed. The scheduled work should synchronize against other workers
 * using the &drm_crtc_commit infraकाष्ठाure as needed. See
 * drm_atomic_helper_setup_commit() क्रम more details.
 */

अटल पूर्णांक stall_checks(काष्ठा drm_crtc *crtc, bool nonblock)
अणु
	काष्ठा drm_crtc_commit *commit, *stall_commit = शून्य;
	bool completed = true;
	पूर्णांक i;
	दीर्घ ret = 0;

	spin_lock(&crtc->commit_lock);
	i = 0;
	list_क्रम_each_entry(commit, &crtc->commit_list, commit_entry) अणु
		अगर (i == 0) अणु
			completed = try_रुको_क्रम_completion(&commit->flip_करोne);
			/* Userspace is not allowed to get ahead of the previous
			 * commit with nonblocking ones. */
			अगर (!completed && nonblock) अणु
				spin_unlock(&crtc->commit_lock);
				DRM_DEBUG_ATOMIC("[CRTC:%d:%s] busy with a previous commit\n",
					crtc->base.id, crtc->name);

				वापस -EBUSY;
			पूर्ण
		पूर्ण अन्यथा अगर (i == 1) अणु
			stall_commit = drm_crtc_commit_get(commit);
			अवरोध;
		पूर्ण

		i++;
	पूर्ण
	spin_unlock(&crtc->commit_lock);

	अगर (!stall_commit)
		वापस 0;

	/* We करोn't want to let commits get ahead of cleanup work too much,
	 * stalling on 2nd previous commit means triple-buffer won't ever stall.
	 */
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&stall_commit->cleanup_करोne,
							10*HZ);
	अगर (ret == 0)
		DRM_ERROR("[CRTC:%d:%s] cleanup_done timed out\n",
			  crtc->base.id, crtc->name);

	drm_crtc_commit_put(stall_commit);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम release_crtc_commit(काष्ठा completion *completion)
अणु
	काष्ठा drm_crtc_commit *commit = container_of(completion,
						      typeof(*commit),
						      flip_करोne);

	drm_crtc_commit_put(commit);
पूर्ण

अटल व्योम init_commit(काष्ठा drm_crtc_commit *commit, काष्ठा drm_crtc *crtc)
अणु
	init_completion(&commit->flip_करोne);
	init_completion(&commit->hw_करोne);
	init_completion(&commit->cleanup_करोne);
	INIT_LIST_HEAD(&commit->commit_entry);
	kref_init(&commit->ref);
	commit->crtc = crtc;
पूर्ण

अटल काष्ठा drm_crtc_commit *
crtc_or_fake_commit(काष्ठा drm_atomic_state *state, काष्ठा drm_crtc *crtc)
अणु
	अगर (crtc) अणु
		काष्ठा drm_crtc_state *new_crtc_state;

		new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

		वापस new_crtc_state->commit;
	पूर्ण

	अगर (!state->fake_commit) अणु
		state->fake_commit = kzalloc(माप(*state->fake_commit), GFP_KERNEL);
		अगर (!state->fake_commit)
			वापस शून्य;

		init_commit(state->fake_commit, शून्य);
	पूर्ण

	वापस state->fake_commit;
पूर्ण

/**
 * drm_atomic_helper_setup_commit - setup possibly nonblocking commit
 * @state: new modeset state to be committed
 * @nonblock: whether nonblocking behavior is requested.
 *
 * This function prepares @state to be used by the atomic helper's support क्रम
 * nonblocking commits. Drivers using the nonblocking commit infraकाष्ठाure
 * should always call this function from their
 * &drm_mode_config_funcs.atomic_commit hook.
 *
 * Drivers that need to extend the commit setup to निजी objects can use the
 * &drm_mode_config_helper_funcs.atomic_commit_setup hook.
 *
 * To be able to use this support drivers need to use a few more helper
 * functions. drm_atomic_helper_रुको_क्रम_dependencies() must be called beक्रमe
 * actually committing the hardware state, and क्रम nonblocking commits this call
 * must be placed in the async worker. See also drm_atomic_helper_swap_state()
 * and its stall parameter, क्रम when a driver's commit hooks look at the
 * &drm_crtc.state, &drm_plane.state or &drm_connector.state poपूर्णांकer directly.
 *
 * Completion of the hardware commit step must be संकेतled using
 * drm_atomic_helper_commit_hw_करोne(). After this step the driver is not allowed
 * to पढ़ो or change any permanent software or hardware modeset state. The only
 * exception is state रक्षित by other means than &drm_modeset_lock locks.
 * Only the मुक्त standing @state with poपूर्णांकers to the old state काष्ठाures can
 * be inspected, e.g. to clean up old buffers using
 * drm_atomic_helper_cleanup_planes().
 *
 * At the very end, beक्रमe cleaning up @state drivers must call
 * drm_atomic_helper_commit_cleanup_करोne().
 *
 * This is all implemented by in drm_atomic_helper_commit(), giving drivers a
 * complete and easy-to-use शेष implementation of the atomic_commit() hook.
 *
 * The tracking of asynchronously executed and still pending commits is करोne
 * using the core काष्ठाure &drm_crtc_commit.
 *
 * By शेष there's no need to clean up resources allocated by this function
 * explicitly: drm_atomic_state_शेष_clear() will take care of that
 * स्वतःmatically.
 *
 * Returns:
 *
 * 0 on success. -EBUSY when userspace schedules nonblocking commits too fast,
 * -ENOMEM on allocation failures and -EINTR when a संकेत is pending.
 */
पूर्णांक drm_atomic_helper_setup_commit(काष्ठा drm_atomic_state *state,
				   bool nonblock)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *old_conn_state, *new_conn_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा drm_crtc_commit *commit;
	स्थिर काष्ठा drm_mode_config_helper_funcs *funcs;
	पूर्णांक i, ret;

	funcs = state->dev->mode_config.helper_निजी;

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		commit = kzalloc(माप(*commit), GFP_KERNEL);
		अगर (!commit)
			वापस -ENOMEM;

		init_commit(commit, crtc);

		new_crtc_state->commit = commit;

		ret = stall_checks(crtc, nonblock);
		अगर (ret)
			वापस ret;

		/* Drivers only send out events when at least either current or
		 * new CRTC state is active. Complete right away अगर everything
		 * stays off. */
		अगर (!old_crtc_state->active && !new_crtc_state->active) अणु
			complete_all(&commit->flip_करोne);
			जारी;
		पूर्ण

		/* Legacy cursor updates are fully unsynced. */
		अगर (state->legacy_cursor_update) अणु
			complete_all(&commit->flip_करोne);
			जारी;
		पूर्ण

		अगर (!new_crtc_state->event) अणु
			commit->event = kzalloc(माप(*commit->event),
						GFP_KERNEL);
			अगर (!commit->event)
				वापस -ENOMEM;

			new_crtc_state->event = commit->event;
		पूर्ण

		new_crtc_state->event->base.completion = &commit->flip_करोne;
		new_crtc_state->event->base.completion_release = release_crtc_commit;
		drm_crtc_commit_get(commit);

		commit->पात_completion = true;

		state->crtcs[i].commit = commit;
		drm_crtc_commit_get(commit);
	पूर्ण

	क्रम_each_oldnew_connector_in_state(state, conn, old_conn_state, new_conn_state, i) अणु
		/* Userspace is not allowed to get ahead of the previous
		 * commit with nonblocking ones. */
		अगर (nonblock && old_conn_state->commit &&
		    !try_रुको_क्रम_completion(&old_conn_state->commit->flip_करोne)) अणु
			DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] busy with a previous commit\n",
				conn->base.id, conn->name);

			वापस -EBUSY;
		पूर्ण

		/* Always track connectors explicitly क्रम e.g. link retraining. */
		commit = crtc_or_fake_commit(state, new_conn_state->crtc ?: old_conn_state->crtc);
		अगर (!commit)
			वापस -ENOMEM;

		new_conn_state->commit = drm_crtc_commit_get(commit);
	पूर्ण

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		/* Userspace is not allowed to get ahead of the previous
		 * commit with nonblocking ones. */
		अगर (nonblock && old_plane_state->commit &&
		    !try_रुको_क्रम_completion(&old_plane_state->commit->flip_करोne)) अणु
			DRM_DEBUG_ATOMIC("[PLANE:%d:%s] busy with a previous commit\n",
				plane->base.id, plane->name);

			वापस -EBUSY;
		पूर्ण

		/* Always track planes explicitly क्रम async pageflip support. */
		commit = crtc_or_fake_commit(state, new_plane_state->crtc ?: old_plane_state->crtc);
		अगर (!commit)
			वापस -ENOMEM;

		new_plane_state->commit = drm_crtc_commit_get(commit);
	पूर्ण

	अगर (funcs && funcs->atomic_commit_setup)
		वापस funcs->atomic_commit_setup(state);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_setup_commit);

/**
 * drm_atomic_helper_रुको_क्रम_dependencies - रुको क्रम required preceeding commits
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function रुकोs क्रम all preceeding commits that touch the same CRTC as
 * @old_state to both be committed to the hardware (as संकेतled by
 * drm_atomic_helper_commit_hw_करोne()) and executed by the hardware (as संकेतled
 * by calling drm_crtc_send_vblank_event() on the &drm_crtc_state.event).
 *
 * This is part of the atomic helper support क्रम nonblocking commits, see
 * drm_atomic_helper_setup_commit() क्रम an overview.
 */
व्योम drm_atomic_helper_रुको_क्रम_dependencies(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *old_conn_state;
	पूर्णांक i;
	दीर्घ ret;

	क्रम_each_old_crtc_in_state(old_state, crtc, old_crtc_state, i) अणु
		ret = drm_crtc_commit_रुको(old_crtc_state->commit);
		अगर (ret)
			DRM_ERROR("[CRTC:%d:%s] commit wait timed out\n",
				  crtc->base.id, crtc->name);
	पूर्ण

	क्रम_each_old_connector_in_state(old_state, conn, old_conn_state, i) अणु
		ret = drm_crtc_commit_रुको(old_conn_state->commit);
		अगर (ret)
			DRM_ERROR("[CONNECTOR:%d:%s] commit wait timed out\n",
				  conn->base.id, conn->name);
	पूर्ण

	क्रम_each_old_plane_in_state(old_state, plane, old_plane_state, i) अणु
		ret = drm_crtc_commit_रुको(old_plane_state->commit);
		अगर (ret)
			DRM_ERROR("[PLANE:%d:%s] commit wait timed out\n",
				  plane->base.id, plane->name);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_रुको_क्रम_dependencies);

/**
 * drm_atomic_helper_fake_vblank - fake VBLANK events अगर needed
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function walks all CRTCs and fakes VBLANK events on those with
 * &drm_crtc_state.no_vblank set to true and &drm_crtc_state.event != शून्य.
 * The primary use of this function is ग_लिखोback connectors working in oneshot
 * mode and faking VBLANK events. In this हाल they only fake the VBLANK event
 * when a job is queued, and any change to the pipeline that करोes not touch the
 * connector is leading to समयouts when calling
 * drm_atomic_helper_रुको_क्रम_vblanks() or
 * drm_atomic_helper_रुको_क्रम_flip_करोne(). In addition to ग_लिखोback
 * connectors, this function can also fake VBLANK events क्रम CRTCs without
 * VBLANK पूर्णांकerrupt.
 *
 * This is part of the atomic helper support क्रम nonblocking commits, see
 * drm_atomic_helper_setup_commit() क्रम an overview.
 */
व्योम drm_atomic_helper_fake_vblank(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(old_state, crtc, new_crtc_state, i) अणु
		अचिन्हित दीर्घ flags;

		अगर (!new_crtc_state->no_vblank)
			जारी;

		spin_lock_irqsave(&old_state->dev->event_lock, flags);
		अगर (new_crtc_state->event) अणु
			drm_crtc_send_vblank_event(crtc,
						   new_crtc_state->event);
			new_crtc_state->event = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&old_state->dev->event_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_fake_vblank);

/**
 * drm_atomic_helper_commit_hw_करोne - setup possible nonblocking commit
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function is used to संकेत completion of the hardware commit step. After
 * this step the driver is not allowed to पढ़ो or change any permanent software
 * or hardware modeset state. The only exception is state रक्षित by other
 * means than &drm_modeset_lock locks.
 *
 * Drivers should try to postpone any expensive or delayed cleanup work after
 * this function is called.
 *
 * This is part of the atomic helper support क्रम nonblocking commits, see
 * drm_atomic_helper_setup_commit() क्रम an overview.
 */
व्योम drm_atomic_helper_commit_hw_करोne(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_crtc_commit *commit;
	पूर्णांक i;

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		commit = new_crtc_state->commit;
		अगर (!commit)
			जारी;

		/*
		 * copy new_crtc_state->commit to old_crtc_state->commit,
		 * it's unsafe to touch new_crtc_state after hw_करोne,
		 * but we still need to करो so in cleanup_करोne().
		 */
		अगर (old_crtc_state->commit)
			drm_crtc_commit_put(old_crtc_state->commit);

		old_crtc_state->commit = drm_crtc_commit_get(commit);

		/* backend must have consumed any event by now */
		WARN_ON(new_crtc_state->event);
		complete_all(&commit->hw_करोne);
	पूर्ण

	अगर (old_state->fake_commit) अणु
		complete_all(&old_state->fake_commit->hw_करोne);
		complete_all(&old_state->fake_commit->flip_करोne);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_hw_करोne);

/**
 * drm_atomic_helper_commit_cleanup_करोne - संकेत completion of commit
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This संकेतs completion of the atomic update @old_state, including any
 * cleanup work. If used, it must be called right beक्रमe calling
 * drm_atomic_state_put().
 *
 * This is part of the atomic helper support क्रम nonblocking commits, see
 * drm_atomic_helper_setup_commit() क्रम an overview.
 */
व्योम drm_atomic_helper_commit_cleanup_करोne(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	काष्ठा drm_crtc_commit *commit;
	पूर्णांक i;

	क्रम_each_old_crtc_in_state(old_state, crtc, old_crtc_state, i) अणु
		commit = old_crtc_state->commit;
		अगर (WARN_ON(!commit))
			जारी;

		complete_all(&commit->cleanup_करोne);
		WARN_ON(!try_रुको_क्रम_completion(&commit->hw_करोne));

		spin_lock(&crtc->commit_lock);
		list_del(&commit->commit_entry);
		spin_unlock(&crtc->commit_lock);
	पूर्ण

	अगर (old_state->fake_commit) अणु
		complete_all(&old_state->fake_commit->cleanup_करोne);
		WARN_ON(!try_रुको_क्रम_completion(&old_state->fake_commit->hw_करोne));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_cleanup_करोne);

/**
 * drm_atomic_helper_prepare_planes - prepare plane resources beक्रमe commit
 * @dev: DRM device
 * @state: atomic state object with new state काष्ठाures
 *
 * This function prepares plane state, specअगरically framebuffers, क्रम the new
 * configuration, by calling &drm_plane_helper_funcs.prepare_fb. If any failure
 * is encountered this function will call &drm_plane_helper_funcs.cleanup_fb on
 * any alपढ़ोy successfully prepared framebuffer.
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_atomic_helper_prepare_planes(काष्ठा drm_device *dev,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *new_plane_state;
	पूर्णांक ret, i, j;

	क्रम_each_new_connector_in_state(state, connector, new_conn_state, i) अणु
		अगर (!new_conn_state->ग_लिखोback_job)
			जारी;

		ret = drm_ग_लिखोback_prepare_job(new_conn_state->ग_लिखोback_job);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *funcs;

		funcs = plane->helper_निजी;

		अगर (funcs->prepare_fb) अणु
			ret = funcs->prepare_fb(plane, new_plane_state);
			अगर (ret)
				जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	क्रम_each_new_plane_in_state(state, plane, new_plane_state, j) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *funcs;

		अगर (j >= i)
			जारी;

		funcs = plane->helper_निजी;

		अगर (funcs->cleanup_fb)
			funcs->cleanup_fb(plane, new_plane_state);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_prepare_planes);

अटल bool plane_crtc_active(स्थिर काष्ठा drm_plane_state *state)
अणु
	वापस state->crtc && state->crtc->state->active;
पूर्ण

/**
 * drm_atomic_helper_commit_planes - commit plane state
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 * @flags: flags क्रम committing plane state
 *
 * This function commits the new plane state using the plane and atomic helper
 * functions क्रम planes and CRTCs. It assumes that the atomic state has alपढ़ोy
 * been pushed पूर्णांकo the relevant object state poपूर्णांकers, since this step can no
 * दीर्घer fail.
 *
 * It still requires the global state object @old_state to know which planes and
 * crtcs need to be updated though.
 *
 * Note that this function करोes all plane updates across all CRTCs in one step.
 * If the hardware can't support this approach look at
 * drm_atomic_helper_commit_planes_on_crtc() instead.
 *
 * Plane parameters can be updated by applications जबतक the associated CRTC is
 * disabled. The DRM/KMS core will store the parameters in the plane state,
 * which will be available to the driver when the CRTC is turned on. As a result
 * most drivers करोn't need to be immediately notअगरied of plane updates क्रम a
 * disabled CRTC.
 *
 * Unless otherwise needed, drivers are advised to set the ACTIVE_ONLY flag in
 * @flags in order not to receive plane update notअगरications related to a
 * disabled CRTC. This aव्योमs the need to manually ignore plane updates in
 * driver code when the driver and/or hardware can't or just don't need to deal
 * with updates on disabled CRTCs, क्रम example when supporting runसमय PM.
 *
 * Drivers may set the NO_DISABLE_AFTER_MODESET flag in @flags अगर the relevant
 * display controllers require to disable a CRTC's planes when the CRTC is
 * disabled. This function would skip the &drm_plane_helper_funcs.atomic_disable
 * call क्रम a plane अगर the CRTC of the old plane state needs a modesetting
 * operation. Of course, the drivers need to disable the planes in their CRTC
 * disable callbacks since no one अन्यथा would करो that.
 *
 * The drm_atomic_helper_commit() शेष implementation करोesn't set the
 * ACTIVE_ONLY flag to most बंदly match the behaviour of the legacy helpers.
 * This should not be copied blindly by drivers.
 */
व्योम drm_atomic_helper_commit_planes(काष्ठा drm_device *dev,
				     काष्ठा drm_atomic_state *old_state,
				     uपूर्णांक32_t flags)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	पूर्णांक i;
	bool active_only = flags & DRM_PLANE_COMMIT_ACTIVE_ONLY;
	bool no_disable = flags & DRM_PLANE_COMMIT_NO_DISABLE_AFTER_MODESET;

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		funcs = crtc->helper_निजी;

		अगर (!funcs || !funcs->atomic_begin)
			जारी;

		अगर (active_only && !new_crtc_state->active)
			जारी;

		funcs->atomic_begin(crtc, old_state);
	पूर्ण

	क्रम_each_oldnew_plane_in_state(old_state, plane, old_plane_state, new_plane_state, i) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *funcs;
		bool disabling;

		funcs = plane->helper_निजी;

		अगर (!funcs)
			जारी;

		disabling = drm_atomic_plane_disabling(old_plane_state,
						       new_plane_state);

		अगर (active_only) अणु
			/*
			 * Skip planes related to inactive CRTCs. If the plane
			 * is enabled use the state of the current CRTC. If the
			 * plane is being disabled use the state of the old
			 * CRTC to aव्योम skipping planes being disabled on an
			 * active CRTC.
			 */
			अगर (!disabling && !plane_crtc_active(new_plane_state))
				जारी;
			अगर (disabling && !plane_crtc_active(old_plane_state))
				जारी;
		पूर्ण

		/*
		 * Special-हाल disabling the plane अगर drivers support it.
		 */
		अगर (disabling && funcs->atomic_disable) अणु
			काष्ठा drm_crtc_state *crtc_state;

			crtc_state = old_plane_state->crtc->state;

			अगर (drm_atomic_crtc_needs_modeset(crtc_state) &&
			    no_disable)
				जारी;

			funcs->atomic_disable(plane, old_state);
		पूर्ण अन्यथा अगर (new_plane_state->crtc || disabling) अणु
			funcs->atomic_update(plane, old_state);
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state, new_crtc_state, i) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *funcs;

		funcs = crtc->helper_निजी;

		अगर (!funcs || !funcs->atomic_flush)
			जारी;

		अगर (active_only && !new_crtc_state->active)
			जारी;

		funcs->atomic_flush(crtc, old_state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_planes);

/**
 * drm_atomic_helper_commit_planes_on_crtc - commit plane state क्रम a CRTC
 * @old_crtc_state: atomic state object with the old CRTC state
 *
 * This function commits the new plane state using the plane and atomic helper
 * functions क्रम planes on the specअगरic CRTC. It assumes that the atomic state
 * has alपढ़ोy been pushed पूर्णांकo the relevant object state poपूर्णांकers, since this
 * step can no दीर्घer fail.
 *
 * This function is useful when plane updates should be करोne CRTC-by-CRTC
 * instead of one global step like drm_atomic_helper_commit_planes() करोes.
 *
 * This function can only be savely used when planes are not allowed to move
 * between dअगरferent CRTCs because this function करोesn't handle पूर्णांकer-CRTC
 * depencies. Callers need to ensure that either no such depencies exist,
 * resolve them through ordering of commit calls or through some other means.
 */
व्योम
drm_atomic_helper_commit_planes_on_crtc(काष्ठा drm_crtc_state *old_crtc_state)
अणु
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs;
	काष्ठा drm_crtc *crtc = old_crtc_state->crtc;
	काष्ठा drm_atomic_state *old_state = old_crtc_state->state;
	काष्ठा drm_crtc_state *new_crtc_state =
		drm_atomic_get_new_crtc_state(old_state, crtc);
	काष्ठा drm_plane *plane;
	अचिन्हित plane_mask;

	plane_mask = old_crtc_state->plane_mask;
	plane_mask |= new_crtc_state->plane_mask;

	crtc_funcs = crtc->helper_निजी;
	अगर (crtc_funcs && crtc_funcs->atomic_begin)
		crtc_funcs->atomic_begin(crtc, old_state);

	drm_क्रम_each_plane_mask(plane, crtc->dev, plane_mask) अणु
		काष्ठा drm_plane_state *old_plane_state =
			drm_atomic_get_old_plane_state(old_state, plane);
		काष्ठा drm_plane_state *new_plane_state =
			drm_atomic_get_new_plane_state(old_state, plane);
		स्थिर काष्ठा drm_plane_helper_funcs *plane_funcs;

		plane_funcs = plane->helper_निजी;

		अगर (!old_plane_state || !plane_funcs)
			जारी;

		WARN_ON(new_plane_state->crtc &&
			new_plane_state->crtc != crtc);

		अगर (drm_atomic_plane_disabling(old_plane_state, new_plane_state) &&
		    plane_funcs->atomic_disable)
			plane_funcs->atomic_disable(plane, old_state);
		अन्यथा अगर (new_plane_state->crtc ||
			 drm_atomic_plane_disabling(old_plane_state, new_plane_state))
			plane_funcs->atomic_update(plane, old_state);
	पूर्ण

	अगर (crtc_funcs && crtc_funcs->atomic_flush)
		crtc_funcs->atomic_flush(crtc, old_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_planes_on_crtc);

/**
 * drm_atomic_helper_disable_planes_on_crtc - helper to disable CRTC's planes
 * @old_crtc_state: atomic state object with the old CRTC state
 * @atomic: अगर set, synchronize with CRTC's atomic_begin/flush hooks
 *
 * Disables all planes associated with the given CRTC. This can be
 * used क्रम instance in the CRTC helper atomic_disable callback to disable
 * all planes.
 *
 * If the atomic-parameter is set the function calls the CRTC's
 * atomic_begin hook beक्रमe and atomic_flush hook after disabling the
 * planes.
 *
 * It is a bug to call this function without having implemented the
 * &drm_plane_helper_funcs.atomic_disable plane hook.
 */
व्योम
drm_atomic_helper_disable_planes_on_crtc(काष्ठा drm_crtc_state *old_crtc_state,
					 bool atomic)
अणु
	काष्ठा drm_crtc *crtc = old_crtc_state->crtc;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs =
		crtc->helper_निजी;
	काष्ठा drm_plane *plane;

	अगर (atomic && crtc_funcs && crtc_funcs->atomic_begin)
		crtc_funcs->atomic_begin(crtc, शून्य);

	drm_atomic_crtc_state_क्रम_each_plane(plane, old_crtc_state) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *plane_funcs =
			plane->helper_निजी;

		अगर (!plane_funcs)
			जारी;

		WARN_ON(!plane_funcs->atomic_disable);
		अगर (plane_funcs->atomic_disable)
			plane_funcs->atomic_disable(plane, शून्य);
	पूर्ण

	अगर (atomic && crtc_funcs && crtc_funcs->atomic_flush)
		crtc_funcs->atomic_flush(crtc, शून्य);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_disable_planes_on_crtc);

/**
 * drm_atomic_helper_cleanup_planes - cleanup plane resources after commit
 * @dev: DRM device
 * @old_state: atomic state object with old state काष्ठाures
 *
 * This function cleans up plane state, specअगरically framebuffers, from the old
 * configuration. Hence the old configuration must be perserved in @old_state to
 * be able to call this function.
 *
 * This function must also be called on the new state when the atomic update
 * fails at any poपूर्णांक after calling drm_atomic_helper_prepare_planes().
 */
व्योम drm_atomic_helper_cleanup_planes(काष्ठा drm_device *dev,
				      काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	पूर्णांक i;

	क्रम_each_oldnew_plane_in_state(old_state, plane, old_plane_state, new_plane_state, i) अणु
		स्थिर काष्ठा drm_plane_helper_funcs *funcs;
		काष्ठा drm_plane_state *plane_state;

		/*
		 * This might be called beक्रमe swapping when commit is पातed,
		 * in which हाल we have to cleanup the new state.
		 */
		अगर (old_plane_state == plane->state)
			plane_state = new_plane_state;
		अन्यथा
			plane_state = old_plane_state;

		funcs = plane->helper_निजी;

		अगर (funcs->cleanup_fb)
			funcs->cleanup_fb(plane, plane_state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_cleanup_planes);

/**
 * drm_atomic_helper_swap_state - store atomic state पूर्णांकo current sw state
 * @state: atomic state
 * @stall: stall क्रम preceeding commits
 *
 * This function stores the atomic state पूर्णांकo the current state poपूर्णांकers in all
 * driver objects. It should be called after all failing steps have been करोne
 * and succeeded, but beक्रमe the actual hardware state is committed.
 *
 * For cleanup and error recovery the current state क्रम all changed objects will
 * be swapped पूर्णांकo @state.
 *
 * With that sequence it fits perfectly पूर्णांकo the plane prepare/cleanup sequence:
 *
 * 1. Call drm_atomic_helper_prepare_planes() with the staged atomic state.
 *
 * 2. Do any other steps that might fail.
 *
 * 3. Put the staged state पूर्णांकo the current state poपूर्णांकers with this function.
 *
 * 4. Actually commit the hardware state.
 *
 * 5. Call drm_atomic_helper_cleanup_planes() with @state, which since step 3
 * contains the old state. Also करो any other cleanup required with that state.
 *
 * @stall must be set when nonblocking commits क्रम this driver directly access
 * the &drm_plane.state, &drm_crtc.state or &drm_connector.state poपूर्णांकer. With
 * the current atomic helpers this is almost always the हाल, since the helpers
 * करोn't pass the right state काष्ठाures to the callbacks.
 *
 * Returns:
 *
 * Returns 0 on success. Can वापस -ERESTARTSYS when @stall is true and the
 * रुकोing क्रम the previous commits has been पूर्णांकerrupted.
 */
पूर्णांक drm_atomic_helper_swap_state(काष्ठा drm_atomic_state *state,
				  bool stall)
अणु
	पूर्णांक i, ret;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_conn_state, *new_conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा drm_crtc_commit *commit;
	काष्ठा drm_निजी_obj *obj;
	काष्ठा drm_निजी_state *old_obj_state, *new_obj_state;

	अगर (stall) अणु
		/*
		 * We have to stall क्रम hw_करोne here beक्रमe
		 * drm_atomic_helper_रुको_क्रम_dependencies() because flip
		 * depth > 1 is not yet supported by all drivers. As दीर्घ as
		 * obj->state is directly dereferenced anywhere in the drivers
		 * atomic_commit_tail function, then it's unsafe to swap state
		 * beक्रमe drm_atomic_helper_commit_hw_करोne() is called.
		 */

		क्रम_each_old_crtc_in_state(state, crtc, old_crtc_state, i) अणु
			commit = old_crtc_state->commit;

			अगर (!commit)
				जारी;

			ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->hw_करोne);
			अगर (ret)
				वापस ret;
		पूर्ण

		क्रम_each_old_connector_in_state(state, connector, old_conn_state, i) अणु
			commit = old_conn_state->commit;

			अगर (!commit)
				जारी;

			ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->hw_करोne);
			अगर (ret)
				वापस ret;
		पूर्ण

		क्रम_each_old_plane_in_state(state, plane, old_plane_state, i) अणु
			commit = old_plane_state->commit;

			अगर (!commit)
				जारी;

			ret = रुको_क्रम_completion_पूर्णांकerruptible(&commit->hw_करोne);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_connector_in_state(state, connector, old_conn_state, new_conn_state, i) अणु
		WARN_ON(connector->state != old_conn_state);

		old_conn_state->state = state;
		new_conn_state->state = शून्य;

		state->connectors[i].state = old_conn_state;
		connector->state = new_conn_state;
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		WARN_ON(crtc->state != old_crtc_state);

		old_crtc_state->state = state;
		new_crtc_state->state = शून्य;

		state->crtcs[i].state = old_crtc_state;
		crtc->state = new_crtc_state;

		अगर (new_crtc_state->commit) अणु
			spin_lock(&crtc->commit_lock);
			list_add(&new_crtc_state->commit->commit_entry,
				 &crtc->commit_list);
			spin_unlock(&crtc->commit_lock);

			new_crtc_state->commit->event = शून्य;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		WARN_ON(plane->state != old_plane_state);

		old_plane_state->state = state;
		new_plane_state->state = शून्य;

		state->planes[i].state = old_plane_state;
		plane->state = new_plane_state;
	पूर्ण

	क्रम_each_oldnew_निजी_obj_in_state(state, obj, old_obj_state, new_obj_state, i) अणु
		WARN_ON(obj->state != old_obj_state);

		old_obj_state->state = state;
		new_obj_state->state = शून्य;

		state->निजी_objs[i].state = old_obj_state;
		obj->state = new_obj_state;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_swap_state);

/**
 * drm_atomic_helper_update_plane - Helper क्रम primary plane update using atomic
 * @plane: plane object to update
 * @crtc: owning CRTC of owning plane
 * @fb: framebuffer to flip onto plane
 * @crtc_x: x offset of primary plane on @crtc
 * @crtc_y: y offset of primary plane on @crtc
 * @crtc_w: width of primary plane rectangle on @crtc
 * @crtc_h: height of primary plane rectangle on @crtc
 * @src_x: x offset of @fb क्रम panning
 * @src_y: y offset of @fb क्रम panning
 * @src_w: width of source rectangle in @fb
 * @src_h: height of source rectangle in @fb
 * @ctx: lock acquire context
 *
 * Provides a शेष plane update handler using the atomic driver पूर्णांकerface.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
पूर्णांक drm_atomic_helper_update_plane(काष्ठा drm_plane *plane,
				   काष्ठा drm_crtc *crtc,
				   काष्ठा drm_framebuffer *fb,
				   पूर्णांक crtc_x, पूर्णांक crtc_y,
				   अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
				   uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
				   uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
				   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_plane_state *plane_state;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;
	plane_state = drm_atomic_get_plane_state(state, plane);
	अगर (IS_ERR(plane_state)) अणु
		ret = PTR_ERR(plane_state);
		जाओ fail;
	पूर्ण

	ret = drm_atomic_set_crtc_क्रम_plane(plane_state, crtc);
	अगर (ret != 0)
		जाओ fail;
	drm_atomic_set_fb_क्रम_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_w = crtc_w;
	plane_state->crtc_h = crtc_h;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_w = src_w;
	plane_state->src_h = src_h;

	अगर (plane == crtc->cursor)
		state->legacy_cursor_update = true;

	ret = drm_atomic_commit(state);
fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_update_plane);

/**
 * drm_atomic_helper_disable_plane - Helper क्रम primary plane disable using * atomic
 * @plane: plane to disable
 * @ctx: lock acquire context
 *
 * Provides a शेष plane disable handler using the atomic driver पूर्णांकerface.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
पूर्णांक drm_atomic_helper_disable_plane(काष्ठा drm_plane *plane,
				    काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_plane_state *plane_state;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;
	plane_state = drm_atomic_get_plane_state(state, plane);
	अगर (IS_ERR(plane_state)) अणु
		ret = PTR_ERR(plane_state);
		जाओ fail;
	पूर्ण

	अगर (plane_state->crtc && plane_state->crtc->cursor == plane)
		plane_state->state->legacy_cursor_update = true;

	ret = __drm_atomic_helper_disable_plane(plane, plane_state);
	अगर (ret != 0)
		जाओ fail;

	ret = drm_atomic_commit(state);
fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_disable_plane);

/**
 * drm_atomic_helper_set_config - set a new config from userspace
 * @set: mode set configuration
 * @ctx: lock acquisition context
 *
 * Provides a शेष CRTC set_config handler using the atomic driver पूर्णांकerface.
 *
 * NOTE: For backwards compatibility with old userspace this स्वतःmatically
 * resets the "link-status" property to GOOD, to क्रमce any link
 * re-training. The SETCRTC ioctl करोes not define whether an update करोes
 * need a full modeset or just a plane update, hence we're allowed to करो
 * that. See also drm_connector_set_link_status_property().
 *
 * Returns:
 * Returns 0 on success, negative त्रुटि_सं numbers on failure.
 */
पूर्णांक drm_atomic_helper_set_config(काष्ठा drm_mode_set *set,
				 काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_crtc *crtc = set->crtc;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(crtc->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;
	ret = __drm_atomic_helper_set_config(set, state);
	अगर (ret != 0)
		जाओ fail;

	ret = handle_conflicting_encoders(state, true);
	अगर (ret)
		जाओ fail;

	ret = drm_atomic_commit(state);

fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_set_config);

/**
 * drm_atomic_helper_disable_all - disable all currently active outमाला_दो
 * @dev: DRM device
 * @ctx: lock acquisition context
 *
 * Loops through all connectors, finding those that aren't turned off and then
 * turns them off by setting their DPMS mode to OFF and deactivating the CRTC
 * that they are connected to.
 *
 * This is used क्रम example in suspend/resume to disable all currently active
 * functions when suspending. If you just want to shut करोwn everything at e.g.
 * driver unload, look at drm_atomic_helper_shutकरोwn().
 *
 * Note that अगर callers haven't alपढ़ोy acquired all modeset locks this might
 * वापस -EDEADLK, which must be handled by calling drm_modeset_backoff().
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 *
 * See also:
 * drm_atomic_helper_suspend(), drm_atomic_helper_resume() and
 * drm_atomic_helper_shutकरोwn().
 */
पूर्णांक drm_atomic_helper_disable_all(काष्ठा drm_device *dev,
				  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret, i;

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;

	drm_क्रम_each_crtc(crtc, dev) अणु
		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			ret = PTR_ERR(crtc_state);
			जाओ मुक्त;
		पूर्ण

		crtc_state->active = false;

		ret = drm_atomic_set_mode_prop_क्रम_crtc(crtc_state, शून्य);
		अगर (ret < 0)
			जाओ मुक्त;

		ret = drm_atomic_add_affected_planes(state, crtc);
		अगर (ret < 0)
			जाओ मुक्त;

		ret = drm_atomic_add_affected_connectors(state, crtc);
		अगर (ret < 0)
			जाओ मुक्त;
	पूर्ण

	क्रम_each_new_connector_in_state(state, conn, conn_state, i) अणु
		ret = drm_atomic_set_crtc_क्रम_connector(conn_state, शून्य);
		अगर (ret < 0)
			जाओ मुक्त;
	पूर्ण

	क्रम_each_new_plane_in_state(state, plane, plane_state, i) अणु
		ret = drm_atomic_set_crtc_क्रम_plane(plane_state, शून्य);
		अगर (ret < 0)
			जाओ मुक्त;

		drm_atomic_set_fb_क्रम_plane(plane_state, शून्य);
	पूर्ण

	ret = drm_atomic_commit(state);
मुक्त:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_disable_all);

/**
 * drm_atomic_helper_shutकरोwn - shutकरोwn all CRTC
 * @dev: DRM device
 *
 * This shuts करोwn all CRTC, which is useful क्रम driver unloading. Shutकरोwn on
 * suspend should instead be handled with drm_atomic_helper_suspend(), since
 * that also takes a snapshot of the modeset state to be restored on resume.
 *
 * This is just a convenience wrapper around drm_atomic_helper_disable_all(),
 * and it is the atomic version of drm_crtc_क्रमce_disable_all().
 */
व्योम drm_atomic_helper_shutकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, ret);

	ret = drm_atomic_helper_disable_all(dev, &ctx);
	अगर (ret)
		DRM_ERROR("Disabling all crtc's during unload failed with %i\n", ret);

	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_shutकरोwn);

/**
 * drm_atomic_helper_duplicate_state - duplicate an atomic state object
 * @dev: DRM device
 * @ctx: lock acquisition context
 *
 * Makes a copy of the current atomic state by looping over all objects and
 * duplicating their respective states. This is used क्रम example by suspend/
 * resume support code to save the state prior to suspend such that it can
 * be restored upon resume.
 *
 * Note that this treats atomic state as persistent between save and restore.
 * Drivers must make sure that this is possible and won't result in confusion
 * or erroneous behaviour.
 *
 * Note that अगर callers haven't alपढ़ोy acquired all modeset locks this might
 * वापस -EDEADLK, which must be handled by calling drm_modeset_backoff().
 *
 * Returns:
 * A poपूर्णांकer to the copy of the atomic state object on success or an
 * ERR_PTR()-encoded error code on failure.
 *
 * See also:
 * drm_atomic_helper_suspend(), drm_atomic_helper_resume()
 */
काष्ठा drm_atomic_state *
drm_atomic_helper_duplicate_state(काष्ठा drm_device *dev,
				  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc *crtc;
	पूर्णांक err = 0;

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	state->acquire_ctx = ctx;
	state->duplicated = true;

	drm_क्रम_each_crtc(crtc, dev) अणु
		काष्ठा drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			err = PTR_ERR(crtc_state);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	drm_क्रम_each_plane(plane, dev) अणु
		काष्ठा drm_plane_state *plane_state;

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			err = PTR_ERR(plane_state);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(conn, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state;

		conn_state = drm_atomic_get_connector_state(state, conn);
		अगर (IS_ERR(conn_state)) अणु
			err = PTR_ERR(conn_state);
			drm_connector_list_iter_end(&conn_iter);
			जाओ मुक्त;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* clear the acquire context so that it isn't accidentally reused */
	state->acquire_ctx = शून्य;

मुक्त:
	अगर (err < 0) अणु
		drm_atomic_state_put(state);
		state = ERR_PTR(err);
	पूर्ण

	वापस state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_duplicate_state);

/**
 * drm_atomic_helper_suspend - subप्रणाली-level suspend helper
 * @dev: DRM device
 *
 * Duplicates the current atomic state, disables all active outमाला_दो and then
 * वापसs a poपूर्णांकer to the original atomic state to the caller. Drivers can
 * pass this poपूर्णांकer to the drm_atomic_helper_resume() helper upon resume to
 * restore the output configuration that was active at the समय the प्रणाली
 * entered suspend.
 *
 * Note that it is potentially unsafe to use this. The atomic state object
 * वापसed by this function is assumed to be persistent. Drivers must ensure
 * that this holds true. Beक्रमe calling this function, drivers must make sure
 * to suspend fbdev emulation so that nothing can be using the device.
 *
 * Returns:
 * A poपूर्णांकer to a copy of the state beक्रमe suspend on success or an ERR_PTR()-
 * encoded error code on failure. Drivers should store the वापसed atomic
 * state object and pass it to the drm_atomic_helper_resume() helper upon
 * resume.
 *
 * See also:
 * drm_atomic_helper_duplicate_state(), drm_atomic_helper_disable_all(),
 * drm_atomic_helper_resume(), drm_atomic_helper_commit_duplicated_state()
 */
काष्ठा drm_atomic_state *drm_atomic_helper_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_atomic_state *state;
	पूर्णांक err;

	/* This can never be वापसed, but it makes the compiler happy */
	state = ERR_PTR(-EINVAL);

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, err);

	state = drm_atomic_helper_duplicate_state(dev, &ctx);
	अगर (IS_ERR(state))
		जाओ unlock;

	err = drm_atomic_helper_disable_all(dev, &ctx);
	अगर (err < 0) अणु
		drm_atomic_state_put(state);
		state = ERR_PTR(err);
		जाओ unlock;
	पूर्ण

unlock:
	DRM_MODESET_LOCK_ALL_END(dev, ctx, err);
	अगर (err)
		वापस ERR_PTR(err);

	वापस state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_suspend);

/**
 * drm_atomic_helper_commit_duplicated_state - commit duplicated state
 * @state: duplicated atomic state to commit
 * @ctx: poपूर्णांकer to acquire_ctx to use क्रम commit.
 *
 * The state वापसed by drm_atomic_helper_duplicate_state() and
 * drm_atomic_helper_suspend() is partially invalid, and needs to
 * be fixed up beक्रमe commit.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 *
 * See also:
 * drm_atomic_helper_suspend()
 */
पूर्णांक drm_atomic_helper_commit_duplicated_state(काष्ठा drm_atomic_state *state,
					      काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	पूर्णांक i, ret;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;

	state->acquire_ctx = ctx;

	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i)
		state->planes[i].old_state = plane->state;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i)
		state->crtcs[i].old_state = crtc->state;

	क्रम_each_new_connector_in_state(state, connector, new_conn_state, i)
		state->connectors[i].old_state = connector->state;

	ret = drm_atomic_commit(state);

	state->acquire_ctx = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_commit_duplicated_state);

/**
 * drm_atomic_helper_resume - subप्रणाली-level resume helper
 * @dev: DRM device
 * @state: atomic state to resume to
 *
 * Calls drm_mode_config_reset() to synchronize hardware and software states,
 * grअसल all modeset locks and commits the atomic state object. This can be
 * used in conjunction with the drm_atomic_helper_suspend() helper to
 * implement suspend/resume क्रम drivers that support atomic mode-setting.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 *
 * See also:
 * drm_atomic_helper_suspend()
 */
पूर्णांक drm_atomic_helper_resume(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक err;

	drm_mode_config_reset(dev);

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, err);

	err = drm_atomic_helper_commit_duplicated_state(state, &ctx);

	DRM_MODESET_LOCK_ALL_END(dev, ctx, err);
	drm_atomic_state_put(state);

	वापस err;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_resume);

अटल पूर्णांक page_flip_common(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_crtc *crtc,
			    काष्ठा drm_framebuffer *fb,
			    काष्ठा drm_pending_vblank_event *event,
			    uपूर्णांक32_t flags)
अणु
	काष्ठा drm_plane *plane = crtc->primary;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret = 0;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	crtc_state->event = event;
	crtc_state->async_flip = flags & DRM_MODE_PAGE_FLIP_ASYNC;

	plane_state = drm_atomic_get_plane_state(state, plane);
	अगर (IS_ERR(plane_state))
		वापस PTR_ERR(plane_state);

	ret = drm_atomic_set_crtc_क्रम_plane(plane_state, crtc);
	अगर (ret != 0)
		वापस ret;
	drm_atomic_set_fb_क्रम_plane(plane_state, fb);

	/* Make sure we करोn't accidentally करो a full modeset. */
	state->allow_modeset = false;
	अगर (!crtc_state->active) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] disabled, rejecting legacy flip\n",
				 crtc->base.id, crtc->name);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * drm_atomic_helper_page_flip - execute a legacy page flip
 * @crtc: DRM CRTC
 * @fb: DRM framebuffer
 * @event: optional DRM event to संकेत upon completion
 * @flags: flip flags क्रम non-vblank sync'ed updates
 * @ctx: lock acquisition context
 *
 * Provides a शेष &drm_crtc_funcs.page_flip implementation
 * using the atomic driver पूर्णांकerface.
 *
 * Returns:
 * Returns 0 on success, negative त्रुटि_सं numbers on failure.
 *
 * See also:
 * drm_atomic_helper_page_flip_target()
 */
पूर्णांक drm_atomic_helper_page_flip(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t flags,
				काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_plane *plane = crtc->primary;
	काष्ठा drm_atomic_state *state;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;

	ret = page_flip_common(state, crtc, fb, event, flags);
	अगर (ret != 0)
		जाओ fail;

	ret = drm_atomic_nonblocking_commit(state);
fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_page_flip);

/**
 * drm_atomic_helper_page_flip_target - करो page flip on target vblank period.
 * @crtc: DRM CRTC
 * @fb: DRM framebuffer
 * @event: optional DRM event to संकेत upon completion
 * @flags: flip flags क्रम non-vblank sync'ed updates
 * @target: specअगरying the target vblank period when the flip to take effect
 * @ctx: lock acquisition context
 *
 * Provides a शेष &drm_crtc_funcs.page_flip_target implementation.
 * Similar to drm_atomic_helper_page_flip() with extra parameter to specअगरy
 * target vblank period to flip.
 *
 * Returns:
 * Returns 0 on success, negative त्रुटि_सं numbers on failure.
 */
पूर्णांक drm_atomic_helper_page_flip_target(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_pending_vblank_event *event,
				       uपूर्णांक32_t flags,
				       uपूर्णांक32_t target,
				       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_plane *plane = crtc->primary;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;

	ret = page_flip_common(state, crtc, fb, event, flags);
	अगर (ret != 0)
		जाओ fail;

	crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	अगर (WARN_ON(!crtc_state)) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण
	crtc_state->target_vblank = target;

	ret = drm_atomic_nonblocking_commit(state);
fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_page_flip_target);

/**
 * drm_atomic_helper_bridge_propagate_bus_fmt() - Propagate output क्रमmat to
 *						  the input end of a bridge
 * @bridge: bridge control काष्ठाure
 * @bridge_state: new bridge state
 * @crtc_state: new CRTC state
 * @conn_state: new connector state
 * @output_fmt: tested output bus क्रमmat
 * @num_input_fmts: will contain the size of the वापसed array
 *
 * This helper is a pluggable implementation of the
 * &drm_bridge_funcs.atomic_get_input_bus_fmts operation क्रम bridges that करोn't
 * modअगरy the bus configuration between their input and their output. It
 * वापसs an array of input क्रमmats with a single element set to @output_fmt.
 *
 * RETURNS:
 * a valid क्रमmat array of size @num_input_fmts, or शून्य अगर the allocation
 * failed
 */
u32 *
drm_atomic_helper_bridge_propagate_bus_fmt(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts)
अणु
	u32 *input_fmts;

	input_fmts = kzalloc(माप(*input_fmts), GFP_KERNEL);
	अगर (!input_fmts) अणु
		*num_input_fmts = 0;
		वापस शून्य;
	पूर्ण

	*num_input_fmts = 1;
	input_fmts[0] = output_fmt;
	वापस input_fmts;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_bridge_propagate_bus_fmt);
