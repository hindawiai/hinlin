<शैली गुरु>
/*
 * Copyright (C) 2018 Intel Corp.
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

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश <linux/slab.h>
#समावेश <linux/dma-fence.h>

/**
 * DOC: atomic state reset and initialization
 *
 * Both the drm core and the atomic helpers assume that there is always the full
 * and correct atomic software state क्रम all connectors, CRTCs and planes
 * available. Which is a bit a problem on driver load and also after प्रणाली
 * suspend. One way to solve this is to have a hardware state पढ़ो-out
 * infraकाष्ठाure which reस्थिरructs the full software state (e.g. the i915
 * driver).
 *
 * The simpler solution is to just reset the software state to everything off,
 * which is easiest to करो by calling drm_mode_config_reset(). To facilitate this
 * the atomic helpers provide शेष reset implementations क्रम all hooks.
 *
 * On the upside the precise state tracking of atomic simplअगरies प्रणाली suspend
 * and resume a lot. For drivers using drm_mode_config_reset() a complete recipe
 * is implemented in drm_atomic_helper_suspend() and drm_atomic_helper_resume().
 * For other drivers the building blocks are split out, see the करोcumentation
 * क्रम these functions.
 */

/**
 * __drm_atomic_helper_crtc_state_reset - reset the CRTC state
 * @crtc_state: atomic CRTC state, must not be शून्य
 * @crtc: CRTC object, must not be शून्य
 *
 * Initializes the newly allocated @crtc_state with शेष
 * values. This is useful क्रम drivers that subclass the CRTC state.
 */
व्योम
__drm_atomic_helper_crtc_state_reset(काष्ठा drm_crtc_state *crtc_state,
				     काष्ठा drm_crtc *crtc)
अणु
	crtc_state->crtc = crtc;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_crtc_state_reset);

/**
 * __drm_atomic_helper_crtc_reset - reset state on CRTC
 * @crtc: drm CRTC
 * @crtc_state: CRTC state to assign
 *
 * Initializes the newly allocated @crtc_state and assigns it to
 * the &drm_crtc->state poपूर्णांकer of @crtc, usually required when
 * initializing the drivers or when called from the &drm_crtc_funcs.reset
 * hook.
 *
 * This is useful क्रम drivers that subclass the CRTC state.
 */
व्योम
__drm_atomic_helper_crtc_reset(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_crtc_state *crtc_state)
अणु
	अगर (crtc_state)
		__drm_atomic_helper_crtc_state_reset(crtc_state, crtc);

	अगर (drm_dev_has_vblank(crtc->dev))
		drm_crtc_vblank_reset(crtc);

	crtc->state = crtc_state;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_crtc_reset);

/**
 * drm_atomic_helper_crtc_reset - शेष &drm_crtc_funcs.reset hook क्रम CRTCs
 * @crtc: drm CRTC
 *
 * Resets the atomic state क्रम @crtc by मुक्तing the state poपूर्णांकer (which might
 * be शून्य, e.g. at driver load समय) and allocating a new empty state object.
 */
व्योम drm_atomic_helper_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *crtc_state =
		kzalloc(माप(*crtc->state), GFP_KERNEL);

	अगर (crtc->state)
		crtc->funcs->atomic_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, crtc_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_crtc_reset);

/**
 * __drm_atomic_helper_crtc_duplicate_state - copy atomic CRTC state
 * @crtc: CRTC object
 * @state: atomic CRTC state
 *
 * Copies atomic state from a CRTC's current state and resets inferred values.
 * This is useful क्रम drivers that subclass the CRTC state.
 */
व्योम __drm_atomic_helper_crtc_duplicate_state(काष्ठा drm_crtc *crtc,
					      काष्ठा drm_crtc_state *state)
अणु
	स_नकल(state, crtc->state, माप(*state));

	अगर (state->mode_blob)
		drm_property_blob_get(state->mode_blob);
	अगर (state->degamma_lut)
		drm_property_blob_get(state->degamma_lut);
	अगर (state->cपंचांग)
		drm_property_blob_get(state->cपंचांग);
	अगर (state->gamma_lut)
		drm_property_blob_get(state->gamma_lut);
	state->mode_changed = false;
	state->active_changed = false;
	state->planes_changed = false;
	state->connectors_changed = false;
	state->color_mgmt_changed = false;
	state->zpos_changed = false;
	state->commit = शून्य;
	state->event = शून्य;
	state->async_flip = false;

	/* Self refresh should be canceled when a new update is available */
	state->active = drm_atomic_crtc_effectively_active(state);
	state->self_refresh_active = false;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_crtc_duplicate_state);

/**
 * drm_atomic_helper_crtc_duplicate_state - शेष state duplicate hook
 * @crtc: drm CRTC
 *
 * Default CRTC state duplicate hook क्रम drivers which करोn't have their own
 * subclassed CRTC state काष्ठाure.
 */
काष्ठा drm_crtc_state *
drm_atomic_helper_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *state;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_duplicate_state(crtc, state);

	वापस state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_crtc_duplicate_state);

/**
 * __drm_atomic_helper_crtc_destroy_state - release CRTC state
 * @state: CRTC state object to release
 *
 * Releases all resources stored in the CRTC state without actually मुक्तing
 * the memory of the CRTC state. This is useful क्रम drivers that subclass the
 * CRTC state.
 */
व्योम __drm_atomic_helper_crtc_destroy_state(काष्ठा drm_crtc_state *state)
अणु
	अगर (state->commit) अणु
		/*
		 * In the event that a non-blocking commit वापसs
		 * -ERESTARTSYS beक्रमe the commit_tail work is queued, we will
		 * have an extra reference to the commit object. Release it, अगर
		 * the event has not been consumed by the worker.
		 *
		 * state->event may be मुक्तd, so we can't directly look at
		 * state->event->base.completion.
		 */
		अगर (state->event && state->commit->पात_completion)
			drm_crtc_commit_put(state->commit);

		kमुक्त(state->commit->event);
		state->commit->event = शून्य;

		drm_crtc_commit_put(state->commit);
	पूर्ण

	drm_property_blob_put(state->mode_blob);
	drm_property_blob_put(state->degamma_lut);
	drm_property_blob_put(state->cपंचांग);
	drm_property_blob_put(state->gamma_lut);
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_crtc_destroy_state);

/**
 * drm_atomic_helper_crtc_destroy_state - शेष state destroy hook
 * @crtc: drm CRTC
 * @state: CRTC state object to release
 *
 * Default CRTC state destroy hook क्रम drivers which करोn't have their own
 * subclassed CRTC state काष्ठाure.
 */
व्योम drm_atomic_helper_crtc_destroy_state(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_crtc_destroy_state);

/**
 * __drm_atomic_helper_plane_state_reset - resets plane state to शेष values
 * @plane_state: atomic plane state, must not be शून्य
 * @plane: plane object, must not be शून्य
 *
 * Initializes the newly allocated @plane_state with शेष
 * values. This is useful क्रम drivers that subclass the CRTC state.
 */
व्योम __drm_atomic_helper_plane_state_reset(काष्ठा drm_plane_state *plane_state,
					   काष्ठा drm_plane *plane)
अणु
	plane_state->plane = plane;
	plane_state->rotation = DRM_MODE_ROTATE_0;

	plane_state->alpha = DRM_BLEND_ALPHA_OPAQUE;
	plane_state->pixel_blend_mode = DRM_MODE_BLEND_PREMULTI;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_plane_state_reset);

/**
 * __drm_atomic_helper_plane_reset - reset state on plane
 * @plane: drm plane
 * @plane_state: plane state to assign
 *
 * Initializes the newly allocated @plane_state and assigns it to
 * the &drm_crtc->state poपूर्णांकer of @plane, usually required when
 * initializing the drivers or when called from the &drm_plane_funcs.reset
 * hook.
 *
 * This is useful क्रम drivers that subclass the plane state.
 */
व्योम __drm_atomic_helper_plane_reset(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *plane_state)
अणु
	अगर (plane_state)
		__drm_atomic_helper_plane_state_reset(plane_state, plane);

	plane->state = plane_state;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_plane_reset);

/**
 * drm_atomic_helper_plane_reset - शेष &drm_plane_funcs.reset hook क्रम planes
 * @plane: drm plane
 *
 * Resets the atomic state क्रम @plane by मुक्तing the state poपूर्णांकer (which might
 * be शून्य, e.g. at driver load समय) and allocating a new empty state object.
 */
व्योम drm_atomic_helper_plane_reset(काष्ठा drm_plane *plane)
अणु
	अगर (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kमुक्त(plane->state);
	plane->state = kzalloc(माप(*plane->state), GFP_KERNEL);
	अगर (plane->state)
		__drm_atomic_helper_plane_reset(plane, plane->state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_plane_reset);

/**
 * __drm_atomic_helper_plane_duplicate_state - copy atomic plane state
 * @plane: plane object
 * @state: atomic plane state
 *
 * Copies atomic state from a plane's current state. This is useful क्रम
 * drivers that subclass the plane state.
 */
व्योम __drm_atomic_helper_plane_duplicate_state(काष्ठा drm_plane *plane,
					       काष्ठा drm_plane_state *state)
अणु
	स_नकल(state, plane->state, माप(*state));

	अगर (state->fb)
		drm_framebuffer_get(state->fb);

	state->fence = शून्य;
	state->commit = शून्य;
	state->fb_damage_clips = शून्य;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_plane_duplicate_state);

/**
 * drm_atomic_helper_plane_duplicate_state - शेष state duplicate hook
 * @plane: drm plane
 *
 * Default plane state duplicate hook क्रम drivers which करोn't have their own
 * subclassed plane state काष्ठाure.
 */
काष्ठा drm_plane_state *
drm_atomic_helper_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_plane_duplicate_state(plane, state);

	वापस state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_plane_duplicate_state);

/**
 * __drm_atomic_helper_plane_destroy_state - release plane state
 * @state: plane state object to release
 *
 * Releases all resources stored in the plane state without actually मुक्तing
 * the memory of the plane state. This is useful क्रम drivers that subclass the
 * plane state.
 */
व्योम __drm_atomic_helper_plane_destroy_state(काष्ठा drm_plane_state *state)
अणु
	अगर (state->fb)
		drm_framebuffer_put(state->fb);

	अगर (state->fence)
		dma_fence_put(state->fence);

	अगर (state->commit)
		drm_crtc_commit_put(state->commit);

	drm_property_blob_put(state->fb_damage_clips);
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_plane_destroy_state);

/**
 * drm_atomic_helper_plane_destroy_state - शेष state destroy hook
 * @plane: drm plane
 * @state: plane state object to release
 *
 * Default plane state destroy hook क्रम drivers which करोn't have their own
 * subclassed plane state काष्ठाure.
 */
व्योम drm_atomic_helper_plane_destroy_state(काष्ठा drm_plane *plane,
					   काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_plane_destroy_state);

/**
 * __drm_atomic_helper_connector_state_reset - reset the connector state
 * @conn_state: atomic connector state, must not be शून्य
 * @connector: connectotr object, must not be शून्य
 *
 * Initializes the newly allocated @conn_state with शेष
 * values. This is useful क्रम drivers that subclass the connector state.
 */
व्योम
__drm_atomic_helper_connector_state_reset(काष्ठा drm_connector_state *conn_state,
					  काष्ठा drm_connector *connector)
अणु
	conn_state->connector = connector;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_connector_state_reset);

/**
 * __drm_atomic_helper_connector_reset - reset state on connector
 * @connector: drm connector
 * @conn_state: connector state to assign
 *
 * Initializes the newly allocated @conn_state and assigns it to
 * the &drm_connector->state poपूर्णांकer of @connector, usually required when
 * initializing the drivers or when called from the &drm_connector_funcs.reset
 * hook.
 *
 * This is useful क्रम drivers that subclass the connector state.
 */
व्योम
__drm_atomic_helper_connector_reset(काष्ठा drm_connector *connector,
				    काष्ठा drm_connector_state *conn_state)
अणु
	अगर (conn_state)
		__drm_atomic_helper_connector_state_reset(conn_state, connector);

	connector->state = conn_state;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_connector_reset);

/**
 * drm_atomic_helper_connector_reset - शेष &drm_connector_funcs.reset hook क्रम connectors
 * @connector: drm connector
 *
 * Resets the atomic state क्रम @connector by मुक्तing the state poपूर्णांकer (which
 * might be शून्य, e.g. at driver load समय) and allocating a new empty state
 * object.
 */
व्योम drm_atomic_helper_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_connector_state *conn_state =
		kzalloc(माप(*conn_state), GFP_KERNEL);

	अगर (connector->state)
		__drm_atomic_helper_connector_destroy_state(connector->state);

	kमुक्त(connector->state);
	__drm_atomic_helper_connector_reset(connector, conn_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_connector_reset);

/**
 * drm_atomic_helper_connector_tv_reset - Resets TV connector properties
 * @connector: DRM connector
 *
 * Resets the TV-related properties attached to a connector.
 */
व्योम drm_atomic_helper_connector_tv_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_cmdline_mode *cmdline = &connector->cmdline_mode;
	काष्ठा drm_connector_state *state = connector->state;

	state->tv.margins.left = cmdline->tv_margins.left;
	state->tv.margins.right = cmdline->tv_margins.right;
	state->tv.margins.top = cmdline->tv_margins.top;
	state->tv.margins.bottom = cmdline->tv_margins.bottom;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_connector_tv_reset);

/**
 * __drm_atomic_helper_connector_duplicate_state - copy atomic connector state
 * @connector: connector object
 * @state: atomic connector state
 *
 * Copies atomic state from a connector's current state. This is useful क्रम
 * drivers that subclass the connector state.
 */
व्योम
__drm_atomic_helper_connector_duplicate_state(काष्ठा drm_connector *connector,
					    काष्ठा drm_connector_state *state)
अणु
	स_नकल(state, connector->state, माप(*state));
	अगर (state->crtc)
		drm_connector_get(connector);
	state->commit = शून्य;

	अगर (state->hdr_output_metadata)
		drm_property_blob_get(state->hdr_output_metadata);

	/* Don't copy over a ग_लिखोback job, they are used only once */
	state->ग_लिखोback_job = शून्य;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_connector_duplicate_state);

/**
 * drm_atomic_helper_connector_duplicate_state - शेष state duplicate hook
 * @connector: drm connector
 *
 * Default connector state duplicate hook क्रम drivers which करोn't have their own
 * subclassed connector state काष्ठाure.
 */
काष्ठा drm_connector_state *
drm_atomic_helper_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_connector_state *state;

	अगर (WARN_ON(!connector->state))
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_connector_duplicate_state(connector, state);

	वापस state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_connector_duplicate_state);

/**
 * __drm_atomic_helper_connector_destroy_state - release connector state
 * @state: connector state object to release
 *
 * Releases all resources stored in the connector state without actually
 * मुक्तing the memory of the connector state. This is useful क्रम drivers that
 * subclass the connector state.
 */
व्योम
__drm_atomic_helper_connector_destroy_state(काष्ठा drm_connector_state *state)
अणु
	अगर (state->crtc)
		drm_connector_put(state->connector);

	अगर (state->commit)
		drm_crtc_commit_put(state->commit);

	अगर (state->ग_लिखोback_job)
		drm_ग_लिखोback_cleanup_job(state->ग_लिखोback_job);

	drm_property_blob_put(state->hdr_output_metadata);
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_connector_destroy_state);

/**
 * drm_atomic_helper_connector_destroy_state - शेष state destroy hook
 * @connector: drm connector
 * @state: connector state object to release
 *
 * Default connector state destroy hook क्रम drivers which करोn't have their own
 * subclassed connector state काष्ठाure.
 */
व्योम drm_atomic_helper_connector_destroy_state(काष्ठा drm_connector *connector,
					  काष्ठा drm_connector_state *state)
अणु
	__drm_atomic_helper_connector_destroy_state(state);
	kमुक्त(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_connector_destroy_state);

/**
 * __drm_atomic_helper_निजी_obj_duplicate_state - copy atomic निजी state
 * @obj: CRTC object
 * @state: new निजी object state
 *
 * Copies atomic state from a निजी objects's current state and resets inferred values.
 * This is useful क्रम drivers that subclass the निजी state.
 */
व्योम __drm_atomic_helper_निजी_obj_duplicate_state(काष्ठा drm_निजी_obj *obj,
						     काष्ठा drm_निजी_state *state)
अणु
	स_नकल(state, obj->state, माप(*state));
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_निजी_obj_duplicate_state);

/**
 * __drm_atomic_helper_bridge_duplicate_state() - Copy atomic bridge state
 * @bridge: bridge object
 * @state: atomic bridge state
 *
 * Copies atomic state from a bridge's current state and resets inferred values.
 * This is useful क्रम drivers that subclass the bridge state.
 */
व्योम __drm_atomic_helper_bridge_duplicate_state(काष्ठा drm_bridge *bridge,
						काष्ठा drm_bridge_state *state)
अणु
	__drm_atomic_helper_निजी_obj_duplicate_state(&bridge->base,
							&state->base);
	state->bridge = bridge;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_bridge_duplicate_state);

/**
 * drm_atomic_helper_bridge_duplicate_state() - Duplicate a bridge state object
 * @bridge: bridge object
 *
 * Allocates a new bridge state and initializes it with the current bridge
 * state values. This helper is meant to be used as a bridge
 * &drm_bridge_funcs.atomic_duplicate_state hook क्रम bridges that करोn't
 * subclass the bridge state.
 */
काष्ठा drm_bridge_state *
drm_atomic_helper_bridge_duplicate_state(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_bridge_state *new;

	अगर (WARN_ON(!bridge->base.state))
		वापस शून्य;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (new)
		__drm_atomic_helper_bridge_duplicate_state(bridge, new);

	वापस new;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_bridge_duplicate_state);

/**
 * drm_atomic_helper_bridge_destroy_state() - Destroy a bridge state object
 * @bridge: the bridge this state refers to
 * @state: bridge state to destroy
 *
 * Destroys a bridge state previously created by
 * &drm_atomic_helper_bridge_reset() or
 * &drm_atomic_helper_bridge_duplicate_state(). This helper is meant to be
 * used as a bridge &drm_bridge_funcs.atomic_destroy_state hook क्रम bridges
 * that करोn't subclass the bridge state.
 */
व्योम drm_atomic_helper_bridge_destroy_state(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_bridge_state *state)
अणु
	kमुक्त(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_bridge_destroy_state);

/**
 * __drm_atomic_helper_bridge_reset() - Initialize a bridge state to its
 *					शेष
 * @bridge: the bridge this state refers to
 * @state: bridge state to initialize
 *
 * Initializes the bridge state to शेष values. This is meant to be called
 * by the bridge &drm_bridge_funcs.atomic_reset hook क्रम bridges that subclass
 * the bridge state.
 */
व्योम __drm_atomic_helper_bridge_reset(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_bridge_state *state)
अणु
	स_रखो(state, 0, माप(*state));
	state->bridge = bridge;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_bridge_reset);

/**
 * drm_atomic_helper_bridge_reset() - Allocate and initialize a bridge state
 *				      to its शेष
 * @bridge: the bridge this state refers to
 *
 * Allocates the bridge state and initializes it to शेष values. This helper
 * is meant to be used as a bridge &drm_bridge_funcs.atomic_reset hook क्रम
 * bridges that करोn't subclass the bridge state.
 */
काष्ठा drm_bridge_state *
drm_atomic_helper_bridge_reset(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_bridge_state *bridge_state;

	bridge_state = kzalloc(माप(*bridge_state), GFP_KERNEL);
	अगर (!bridge_state)
		वापस ERR_PTR(-ENOMEM);

	__drm_atomic_helper_bridge_reset(bridge, bridge_state);
	वापस bridge_state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_bridge_reset);
