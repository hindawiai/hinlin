<शैली गुरु>
/*
 * Copyright तऊ 2015 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * DOC: atomic modeset support
 *
 * The functions here implement the state management and hardware programming
 * dispatch required by the atomic modeset infraकाष्ठाure.
 * See पूर्णांकel_atomic_plane.c क्रम the plane-specअगरic atomic functionality.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "intel_atomic.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_display_types.h"
#समावेश "intel_global_state.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_psr.h"
#समावेश "skl_universal_plane.h"

/**
 * पूर्णांकel_digital_connector_atomic_get_property - hook क्रम connector->atomic_get_property.
 * @connector: Connector to get the property क्रम.
 * @state: Connector state to retrieve the property from.
 * @property: Property to retrieve.
 * @val: Return value क्रम the property.
 *
 * Returns the atomic property value क्रम a digital connector.
 */
पूर्णांक पूर्णांकel_digital_connector_atomic_get_property(काष्ठा drm_connector *connector,
						स्थिर काष्ठा drm_connector_state *state,
						काष्ठा drm_property *property,
						u64 *val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(state);

	अगर (property == dev_priv->क्रमce_audio_property)
		*val = पूर्णांकel_conn_state->क्रमce_audio;
	अन्यथा अगर (property == dev_priv->broadcast_rgb_property)
		*val = पूर्णांकel_conn_state->broadcast_rgb;
	अन्यथा अणु
		drm_dbg_atomic(&dev_priv->drm,
			       "Unknown property [PROP:%d:%s]\n",
			       property->base.id, property->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_digital_connector_atomic_set_property - hook क्रम connector->atomic_set_property.
 * @connector: Connector to set the property क्रम.
 * @state: Connector state to set the property on.
 * @property: Property to set.
 * @val: New value क्रम the property.
 *
 * Sets the atomic property value क्रम a digital connector.
 */
पूर्णांक पूर्णांकel_digital_connector_atomic_set_property(काष्ठा drm_connector *connector,
						काष्ठा drm_connector_state *state,
						काष्ठा drm_property *property,
						u64 val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(state);

	अगर (property == dev_priv->क्रमce_audio_property) अणु
		पूर्णांकel_conn_state->क्रमce_audio = val;
		वापस 0;
	पूर्ण

	अगर (property == dev_priv->broadcast_rgb_property) अणु
		पूर्णांकel_conn_state->broadcast_rgb = val;
		वापस 0;
	पूर्ण

	drm_dbg_atomic(&dev_priv->drm, "Unknown property [PROP:%d:%s]\n",
		       property->base.id, property->name);
	वापस -EINVAL;
पूर्ण

अटल bool blob_equal(स्थिर काष्ठा drm_property_blob *a,
		       स्थिर काष्ठा drm_property_blob *b)
अणु
	अगर (a && b)
		वापस a->length == b->length &&
			!स_भेद(a->data, b->data, a->length);

	वापस !a == !b;
पूर्ण

पूर्णांक पूर्णांकel_digital_connector_atomic_check(काष्ठा drm_connector *conn,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_state =
		drm_atomic_get_new_connector_state(state, conn);
	काष्ठा पूर्णांकel_digital_connector_state *new_conn_state =
		to_पूर्णांकel_digital_connector_state(new_state);
	काष्ठा drm_connector_state *old_state =
		drm_atomic_get_old_connector_state(state, conn);
	काष्ठा पूर्णांकel_digital_connector_state *old_conn_state =
		to_पूर्णांकel_digital_connector_state(old_state);
	काष्ठा drm_crtc_state *crtc_state;

	पूर्णांकel_hdcp_atomic_check(conn, old_state, new_state);

	अगर (!new_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_new_crtc_state(state, new_state->crtc);

	/*
	 * These properties are handled by fastset, and might not end
	 * up in a modeset.
	 */
	अगर (new_conn_state->क्रमce_audio != old_conn_state->क्रमce_audio ||
	    new_conn_state->broadcast_rgb != old_conn_state->broadcast_rgb ||
	    new_conn_state->base.colorspace != old_conn_state->base.colorspace ||
	    new_conn_state->base.picture_aspect_ratio != old_conn_state->base.picture_aspect_ratio ||
	    new_conn_state->base.content_type != old_conn_state->base.content_type ||
	    new_conn_state->base.scaling_mode != old_conn_state->base.scaling_mode ||
	    !blob_equal(new_conn_state->base.hdr_output_metadata,
			old_conn_state->base.hdr_output_metadata))
		crtc_state->mode_changed = true;

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_digital_connector_duplicate_state - duplicate connector state
 * @connector: digital connector
 *
 * Allocates and वापसs a copy of the connector state (both common and
 * digital connector specअगरic) क्रम the specअगरied connector.
 *
 * Returns: The newly allocated connector state, or शून्य on failure.
 */
काष्ठा drm_connector_state *
पूर्णांकel_digital_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_connector_state *state;

	state = kmemdup(connector->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &state->base);
	वापस &state->base;
पूर्ण

/**
 * पूर्णांकel_connector_needs_modeset - check अगर connector needs a modeset
 * @state: the atomic state corresponding to this modeset
 * @connector: the connector
 */
bool
पूर्णांकel_connector_needs_modeset(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा drm_connector_state *old_conn_state, *new_conn_state;

	old_conn_state = drm_atomic_get_old_connector_state(&state->base, connector);
	new_conn_state = drm_atomic_get_new_connector_state(&state->base, connector);

	वापस old_conn_state->crtc != new_conn_state->crtc ||
	       (new_conn_state->crtc &&
		drm_atomic_crtc_needs_modeset(drm_atomic_get_new_crtc_state(&state->base,
									    new_conn_state->crtc)));
पूर्ण

काष्ठा पूर्णांकel_digital_connector_state *
पूर्णांकel_atomic_get_digital_connector_state(काष्ठा पूर्णांकel_atomic_state *state,
					 काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_connector_state *conn_state;

	conn_state = drm_atomic_get_connector_state(&state->base,
						    &connector->base);
	अगर (IS_ERR(conn_state))
		वापस ERR_CAST(conn_state);

	वापस to_पूर्णांकel_digital_connector_state(conn_state);
पूर्ण

/**
 * पूर्णांकel_crtc_duplicate_state - duplicate crtc state
 * @crtc: drm crtc
 *
 * Allocates and वापसs a copy of the crtc state (both common and
 * Intel-specअगरic) क्रम the specअगरied crtc.
 *
 * Returns: The newly allocated crtc state, or शून्य on failure.
 */
काष्ठा drm_crtc_state *
पूर्णांकel_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state = to_पूर्णांकel_crtc_state(crtc->state);
	काष्ठा पूर्णांकel_crtc_state *crtc_state;

	crtc_state = kmemdup(old_crtc_state, माप(*crtc_state), GFP_KERNEL);
	अगर (!crtc_state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &crtc_state->uapi);

	/* copy color blobs */
	अगर (crtc_state->hw.degamma_lut)
		drm_property_blob_get(crtc_state->hw.degamma_lut);
	अगर (crtc_state->hw.cपंचांग)
		drm_property_blob_get(crtc_state->hw.cपंचांग);
	अगर (crtc_state->hw.gamma_lut)
		drm_property_blob_get(crtc_state->hw.gamma_lut);

	crtc_state->update_pipe = false;
	crtc_state->disable_lp_wm = false;
	crtc_state->disable_cxsr = false;
	crtc_state->update_wm_pre = false;
	crtc_state->update_wm_post = false;
	crtc_state->fअगरo_changed = false;
	crtc_state->preload_luts = false;
	crtc_state->inherited = false;
	crtc_state->wm.need_postvbl_update = false;
	crtc_state->fb_bits = 0;
	crtc_state->update_planes = 0;
	crtc_state->dsb = शून्य;

	वापस &crtc_state->uapi;
पूर्ण

अटल व्योम पूर्णांकel_crtc_put_color_blobs(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	drm_property_blob_put(crtc_state->hw.degamma_lut);
	drm_property_blob_put(crtc_state->hw.gamma_lut);
	drm_property_blob_put(crtc_state->hw.cपंचांग);
पूर्ण

व्योम पूर्णांकel_crtc_मुक्त_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_crtc_put_color_blobs(crtc_state);
पूर्ण

व्योम पूर्णांकel_crtc_copy_color_blobs(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *from_crtc_state)
अणु
	drm_property_replace_blob(&crtc_state->hw.degamma_lut,
				  from_crtc_state->uapi.degamma_lut);
	drm_property_replace_blob(&crtc_state->hw.gamma_lut,
				  from_crtc_state->uapi.gamma_lut);
	drm_property_replace_blob(&crtc_state->hw.cपंचांग,
				  from_crtc_state->uapi.cपंचांग);
पूर्ण

/**
 * पूर्णांकel_crtc_destroy_state - destroy crtc state
 * @crtc: drm crtc
 * @state: the state to destroy
 *
 * Destroys the crtc state (both common and Intel-specअगरic) क्रम the
 * specअगरied crtc.
 */
व्योम
पूर्णांकel_crtc_destroy_state(काष्ठा drm_crtc *crtc,
			 काष्ठा drm_crtc_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state = to_पूर्णांकel_crtc_state(state);

	drm_WARN_ON(crtc->dev, crtc_state->dsb);

	__drm_atomic_helper_crtc_destroy_state(&crtc_state->uapi);
	पूर्णांकel_crtc_मुक्त_hw_state(crtc_state);
	kमुक्त(crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_atomic_setup_scaler(काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state,
				      पूर्णांक num_scalers_need, काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
				      स्थिर अक्षर *name, पूर्णांक idx,
				      काष्ठा पूर्णांकel_plane_state *plane_state,
				      पूर्णांक *scaler_id)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_crtc->base.dev);
	पूर्णांक j;
	u32 mode;

	अगर (*scaler_id < 0) अणु
		/* find a मुक्त scaler */
		क्रम (j = 0; j < पूर्णांकel_crtc->num_scalers; j++) अणु
			अगर (scaler_state->scalers[j].in_use)
				जारी;

			*scaler_id = j;
			scaler_state->scalers[*scaler_id].in_use = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (drm_WARN(&dev_priv->drm, *scaler_id < 0,
		     "Cannot find scaler for %s:%d\n", name, idx))
		वापस;

	/* set scaler mode */
	अगर (plane_state && plane_state->hw.fb &&
	    plane_state->hw.fb->क्रमmat->is_yuv &&
	    plane_state->hw.fb->क्रमmat->num_planes > 1) अणु
		काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
		अगर (IS_DISPLAY_VER(dev_priv, 9)) अणु
			mode = SKL_PS_SCALER_MODE_NV12;
		पूर्ण अन्यथा अगर (icl_is_hdr_plane(dev_priv, plane->id)) अणु
			/*
			 * On gen11+'s HDR planes we only use the scaler क्रम
			 * scaling. They have a dedicated chroma upsampler, so
			 * we करोn't need the scaler to upsample the UV plane.
			 */
			mode = PS_SCALER_MODE_NORMAL;
		पूर्ण अन्यथा अणु
			काष्ठा पूर्णांकel_plane *linked =
				plane_state->planar_linked_plane;

			mode = PS_SCALER_MODE_PLANAR;

			अगर (linked)
				mode |= PS_PLANE_Y_SEL(linked->id);
		पूर्ण
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		mode = PS_SCALER_MODE_NORMAL;
	पूर्ण अन्यथा अगर (num_scalers_need == 1 && पूर्णांकel_crtc->num_scalers > 1) अणु
		/*
		 * when only 1 scaler is in use on a pipe with 2 scalers
		 * scaler 0 operates in high quality (HQ) mode.
		 * In this हाल use scaler 0 to take advantage of HQ mode
		 */
		scaler_state->scalers[*scaler_id].in_use = 0;
		*scaler_id = 0;
		scaler_state->scalers[0].in_use = 1;
		mode = SKL_PS_SCALER_MODE_HQ;
	पूर्ण अन्यथा अणु
		mode = SKL_PS_SCALER_MODE_DYN;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "Attached scaler id %u.%u to %s:%d\n",
		    पूर्णांकel_crtc->pipe, *scaler_id, name, idx);
	scaler_state->scalers[*scaler_id].mode = mode;
पूर्ण

/**
 * पूर्णांकel_atomic_setup_scalers() - setup scalers क्रम crtc per staged requests
 * @dev_priv: i915 device
 * @पूर्णांकel_crtc: पूर्णांकel crtc
 * @crtc_state: incoming crtc_state to validate and setup scalers
 *
 * This function sets up scalers based on staged scaling requests क्रम
 * a @crtc and its planes. It is called from crtc level check path. If request
 * is a supportable request, it attaches scalers to requested planes and crtc.
 *
 * This function takes पूर्णांकo account the current scaler(s) in use by any planes
 * not being part of this atomic state
 *
 *  Returns:
 *         0 - scalers were setup succesfully
 *         error code - otherwise
 */
पूर्णांक पूर्णांकel_atomic_setup_scalers(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_plane *plane = शून्य;
	काष्ठा पूर्णांकel_plane *पूर्णांकel_plane;
	काष्ठा पूर्णांकel_plane_state *plane_state = शून्य;
	काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	काष्ठा drm_atomic_state *drm_state = crtc_state->uapi.state;
	काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state = to_पूर्णांकel_atomic_state(drm_state);
	पूर्णांक num_scalers_need;
	पूर्णांक i;

	num_scalers_need = hweight32(scaler_state->scaler_users);

	/*
	 * High level flow:
	 * - staged scaler requests are alपढ़ोy in scaler_state->scaler_users
	 * - check whether staged scaling requests can be supported
	 * - add planes using scalers that aren't in current transaction
	 * - assign scalers to requested users
	 * - as part of plane commit, scalers will be committed
	 *   (i.e., either attached or detached) to respective planes in hw
	 * - as part of crtc_commit, scaler will be either attached or detached
	 *   to crtc in hw
	 */

	/* fail अगर required scalers > available scalers */
	अगर (num_scalers_need > पूर्णांकel_crtc->num_scalers)अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Too many scaling requests %d > %d\n",
			    num_scalers_need, पूर्णांकel_crtc->num_scalers);
		वापस -EINVAL;
	पूर्ण

	/* walkthrough scaler_users bits and start assigning scalers */
	क्रम (i = 0; i < माप(scaler_state->scaler_users) * 8; i++) अणु
		पूर्णांक *scaler_id;
		स्थिर अक्षर *name;
		पूर्णांक idx;

		/* skip अगर scaler not required */
		अगर (!(scaler_state->scaler_users & (1 << i)))
			जारी;

		अगर (i == SKL_CRTC_INDEX) अणु
			name = "CRTC";
			idx = पूर्णांकel_crtc->base.base.id;

			/* panel fitter हाल: assign as a crtc scaler */
			scaler_id = &scaler_state->scaler_id;
		पूर्ण अन्यथा अणु
			name = "PLANE";

			/* plane scaler हाल: assign as a plane scaler */
			/* find the plane that set the bit as scaler_user */
			plane = drm_state->planes[i].ptr;

			/*
			 * to enable/disable hq mode, add planes that are using scaler
			 * पूर्णांकo this transaction
			 */
			अगर (!plane) अणु
				काष्ठा drm_plane_state *state;

				/*
				 * GLK+ scalers करोn't have a HQ mode so it
				 * isn't necessary to change between HQ and dyn mode
				 * on those platक्रमms.
				 */
				अगर (DISPLAY_VER(dev_priv) >= 10)
					जारी;

				plane = drm_plane_from_index(&dev_priv->drm, i);
				state = drm_atomic_get_plane_state(drm_state, plane);
				अगर (IS_ERR(state)) अणु
					drm_dbg_kms(&dev_priv->drm,
						    "Failed to add [PLANE:%d] to drm_state\n",
						    plane->base.id);
					वापस PTR_ERR(state);
				पूर्ण
			पूर्ण

			पूर्णांकel_plane = to_पूर्णांकel_plane(plane);
			idx = plane->base.id;

			/* plane on dअगरferent crtc cannot be a scaler user of this crtc */
			अगर (drm_WARN_ON(&dev_priv->drm,
					पूर्णांकel_plane->pipe != पूर्णांकel_crtc->pipe))
				जारी;

			plane_state = पूर्णांकel_atomic_get_new_plane_state(पूर्णांकel_state,
								       पूर्णांकel_plane);
			scaler_id = &plane_state->scaler_id;
		पूर्ण

		पूर्णांकel_atomic_setup_scaler(scaler_state, num_scalers_need,
					  पूर्णांकel_crtc, name, idx,
					  plane_state, scaler_id);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_atomic_state *
पूर्णांकel_atomic_state_alloc(काष्ठा drm_device *dev)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (!state || drm_atomic_state_init(dev, &state->base) < 0) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	वापस &state->base;
पूर्ण

व्योम पूर्णांकel_atomic_state_मुक्त(काष्ठा drm_atomic_state *_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(_state);

	drm_atomic_state_शेष_release(&state->base);
	kमुक्त(state->global_objs);

	i915_sw_fence_fini(&state->commit_पढ़ोy);

	kमुक्त(state);
पूर्ण

व्योम पूर्णांकel_atomic_state_clear(काष्ठा drm_atomic_state *s)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(s);

	drm_atomic_state_शेष_clear(&state->base);
	पूर्णांकel_atomic_clear_global_state(state);

	state->dpll_set = state->modeset = false;
पूर्ण

काष्ठा पूर्णांकel_crtc_state *
पूर्णांकel_atomic_get_crtc_state(काष्ठा drm_atomic_state *state,
			    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	crtc_state = drm_atomic_get_crtc_state(state, &crtc->base);
	अगर (IS_ERR(crtc_state))
		वापस ERR_CAST(crtc_state);

	वापस to_पूर्णांकel_crtc_state(crtc_state);
पूर्ण
