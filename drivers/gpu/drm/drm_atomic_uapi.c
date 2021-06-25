<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Copyright (C) 2014 Intel Corp.
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

#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_ग_लिखोback.h>
#समावेश <drm/drm_vblank.h>

#समावेश <linux/dma-fence.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/file.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * This file contains the marshalling and demarshalling glue क्रम the atomic UAPI
 * in all its क्रमms: The monster ATOMIC IOCTL itself, code क्रम GET_PROPERTY and
 * SET_PROPERTY IOCTLs. Plus पूर्णांकerface functions क्रम compatibility helpers and
 * drivers which have special needs to स्थिरruct their own atomic updates, e.g.
 * क्रम load detect or similiar.
 */

/**
 * drm_atomic_set_mode_क्रम_crtc - set mode क्रम CRTC
 * @state: the CRTC whose incoming state to update
 * @mode: kernel-पूर्णांकernal mode to use क्रम the CRTC, or शून्य to disable
 *
 * Set a mode (originating from the kernel) on the desired CRTC state and update
 * the enable property.
 *
 * RETURNS:
 * Zero on success, error code on failure. Cannot वापस -EDEADLK.
 */
पूर्णांक drm_atomic_set_mode_क्रम_crtc(काष्ठा drm_crtc_state *state,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_crtc *crtc = state->crtc;
	काष्ठा drm_mode_modeinfo umode;

	/* Early वापस क्रम no change. */
	अगर (mode && स_भेद(&state->mode, mode, माप(*mode)) == 0)
		वापस 0;

	drm_property_blob_put(state->mode_blob);
	state->mode_blob = शून्य;

	अगर (mode) अणु
		drm_mode_convert_to_umode(&umode, mode);
		state->mode_blob =
			drm_property_create_blob(state->crtc->dev,
		                                 माप(umode),
		                                 &umode);
		अगर (IS_ERR(state->mode_blob))
			वापस PTR_ERR(state->mode_blob);

		drm_mode_copy(&state->mode, mode);
		state->enable = true;
		drm_dbg_atomic(crtc->dev,
			       "Set [MODE:%s] for [CRTC:%d:%s] state %p\n",
			       mode->name, crtc->base.id, crtc->name, state);
	पूर्ण अन्यथा अणु
		स_रखो(&state->mode, 0, माप(state->mode));
		state->enable = false;
		drm_dbg_atomic(crtc->dev,
			       "Set [NOMODE] for [CRTC:%d:%s] state %p\n",
			       crtc->base.id, crtc->name, state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_mode_क्रम_crtc);

/**
 * drm_atomic_set_mode_prop_क्रम_crtc - set mode क्रम CRTC
 * @state: the CRTC whose incoming state to update
 * @blob: poपूर्णांकer to blob property to use क्रम mode
 *
 * Set a mode (originating from a blob property) on the desired CRTC state.
 * This function will take a reference on the blob property क्रम the CRTC state,
 * and release the reference held on the state's existing mode property, अगर any
 * was set.
 *
 * RETURNS:
 * Zero on success, error code on failure. Cannot वापस -EDEADLK.
 */
पूर्णांक drm_atomic_set_mode_prop_क्रम_crtc(काष्ठा drm_crtc_state *state,
                                      काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_crtc *crtc = state->crtc;

	अगर (blob == state->mode_blob)
		वापस 0;

	drm_property_blob_put(state->mode_blob);
	state->mode_blob = शून्य;

	स_रखो(&state->mode, 0, माप(state->mode));

	अगर (blob) अणु
		पूर्णांक ret;

		अगर (blob->length != माप(काष्ठा drm_mode_modeinfo)) अणु
			drm_dbg_atomic(crtc->dev,
				       "[CRTC:%d:%s] bad mode blob length: %zu\n",
				       crtc->base.id, crtc->name,
				       blob->length);
			वापस -EINVAL;
		पूर्ण

		ret = drm_mode_convert_umode(crtc->dev,
					     &state->mode, blob->data);
		अगर (ret) अणु
			drm_dbg_atomic(crtc->dev,
				       "[CRTC:%d:%s] invalid mode (ret=%d, status=%s):\n",
				       crtc->base.id, crtc->name,
				       ret, drm_get_mode_status_name(state->mode.status));
			drm_mode_debug_prपूर्णांकmodeline(&state->mode);
			वापस -EINVAL;
		पूर्ण

		state->mode_blob = drm_property_blob_get(blob);
		state->enable = true;
		drm_dbg_atomic(crtc->dev,
			       "Set [MODE:%s] for [CRTC:%d:%s] state %p\n",
			       state->mode.name, crtc->base.id, crtc->name,
			       state);
	पूर्ण अन्यथा अणु
		state->enable = false;
		drm_dbg_atomic(crtc->dev,
			       "Set [NOMODE] for [CRTC:%d:%s] state %p\n",
			       crtc->base.id, crtc->name, state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_mode_prop_क्रम_crtc);

/**
 * drm_atomic_set_crtc_क्रम_plane - set CRTC क्रम plane
 * @plane_state: the plane whose incoming state to update
 * @crtc: CRTC to use क्रम the plane
 *
 * Changing the asचिन्हित CRTC क्रम a plane requires us to grab the lock and state
 * क्रम the new CRTC, as needed. This function takes care of all these details
 * besides updating the poपूर्णांकer in the state object itself.
 *
 * Returns:
 * 0 on success or can fail with -EDEADLK or -ENOMEM. When the error is EDEADLK
 * then the w/w mutex code has detected a deadlock and the entire atomic
 * sequence must be restarted. All other errors are fatal.
 */
पूर्णांक
drm_atomic_set_crtc_क्रम_plane(काष्ठा drm_plane_state *plane_state,
			      काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_plane *plane = plane_state->plane;
	काष्ठा drm_crtc_state *crtc_state;
	/* Nothing to करो क्रम same crtc*/
	अगर (plane_state->crtc == crtc)
		वापस 0;
	अगर (plane_state->crtc) अणु
		crtc_state = drm_atomic_get_crtc_state(plane_state->state,
						       plane_state->crtc);
		अगर (WARN_ON(IS_ERR(crtc_state)))
			वापस PTR_ERR(crtc_state);

		crtc_state->plane_mask &= ~drm_plane_mask(plane);
	पूर्ण

	plane_state->crtc = crtc;

	अगर (crtc) अणु
		crtc_state = drm_atomic_get_crtc_state(plane_state->state,
						       crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);
		crtc_state->plane_mask |= drm_plane_mask(plane);
	पूर्ण

	अगर (crtc)
		drm_dbg_atomic(plane->dev,
			       "Link [PLANE:%d:%s] state %p to [CRTC:%d:%s]\n",
			       plane->base.id, plane->name, plane_state,
			       crtc->base.id, crtc->name);
	अन्यथा
		drm_dbg_atomic(plane->dev,
			       "Link [PLANE:%d:%s] state %p to [NOCRTC]\n",
			       plane->base.id, plane->name, plane_state);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_crtc_क्रम_plane);

/**
 * drm_atomic_set_fb_क्रम_plane - set framebuffer क्रम plane
 * @plane_state: atomic state object क्रम the plane
 * @fb: fb to use क्रम the plane
 *
 * Changing the asचिन्हित framebuffer क्रम a plane requires us to grab a reference
 * to the new fb and drop the reference to the old fb, अगर there is one. This
 * function takes care of all these details besides updating the poपूर्णांकer in the
 * state object itself.
 */
व्योम
drm_atomic_set_fb_क्रम_plane(काष्ठा drm_plane_state *plane_state,
			    काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_plane *plane = plane_state->plane;

	अगर (fb)
		drm_dbg_atomic(plane->dev,
			       "Set [FB:%d] for [PLANE:%d:%s] state %p\n",
			       fb->base.id, plane->base.id, plane->name,
			       plane_state);
	अन्यथा
		drm_dbg_atomic(plane->dev,
			       "Set [NOFB] for [PLANE:%d:%s] state %p\n",
			       plane->base.id, plane->name, plane_state);

	drm_framebuffer_assign(&plane_state->fb, fb);
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_fb_क्रम_plane);

/**
 * drm_atomic_set_fence_क्रम_plane - set fence क्रम plane
 * @plane_state: atomic state object क्रम the plane
 * @fence: dma_fence to use क्रम the plane
 *
 * Helper to setup the plane_state fence in हाल it is not set yet.
 * By using this drivers करोesn't need to worry अगर the user choose
 * implicit or explicit fencing.
 *
 * This function will not set the fence to the state अगर it was set
 * via explicit fencing पूर्णांकerfaces on the atomic ioctl. In that हाल it will
 * drop the reference to the fence as we are not storing it anywhere.
 * Otherwise, अगर &drm_plane_state.fence is not set this function we just set it
 * with the received implicit fence. In both हालs this function consumes a
 * reference क्रम @fence.
 *
 * This way explicit fencing can be used to overrule implicit fencing, which is
 * important to make explicit fencing use-हालs work: One example is using one
 * buffer क्रम 2 screens with dअगरferent refresh rates. Implicit fencing will
 * clamp rendering to the refresh rate of the slower screen, whereas explicit
 * fence allows 2 independent render and display loops on a single buffer. If a
 * driver allows obeys both implicit and explicit fences क्रम plane updates, then
 * it will अवरोध all the benefits of explicit fencing.
 */
व्योम
drm_atomic_set_fence_क्रम_plane(काष्ठा drm_plane_state *plane_state,
			       काष्ठा dma_fence *fence)
अणु
	अगर (plane_state->fence) अणु
		dma_fence_put(fence);
		वापस;
	पूर्ण

	plane_state->fence = fence;
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_fence_क्रम_plane);

/**
 * drm_atomic_set_crtc_क्रम_connector - set CRTC क्रम connector
 * @conn_state: atomic state object क्रम the connector
 * @crtc: CRTC to use क्रम the connector
 *
 * Changing the asचिन्हित CRTC क्रम a connector requires us to grab the lock and
 * state क्रम the new CRTC, as needed. This function takes care of all these
 * details besides updating the poपूर्णांकer in the state object itself.
 *
 * Returns:
 * 0 on success or can fail with -EDEADLK or -ENOMEM. When the error is EDEADLK
 * then the w/w mutex code has detected a deadlock and the entire atomic
 * sequence must be restarted. All other errors are fatal.
 */
पूर्णांक
drm_atomic_set_crtc_क्रम_connector(काष्ठा drm_connector_state *conn_state,
				  काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (conn_state->crtc == crtc)
		वापस 0;

	अगर (conn_state->crtc) अणु
		crtc_state = drm_atomic_get_new_crtc_state(conn_state->state,
							   conn_state->crtc);

		crtc_state->connector_mask &=
			~drm_connector_mask(conn_state->connector);

		drm_connector_put(conn_state->connector);
		conn_state->crtc = शून्य;
	पूर्ण

	अगर (crtc) अणु
		crtc_state = drm_atomic_get_crtc_state(conn_state->state, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		crtc_state->connector_mask |=
			drm_connector_mask(conn_state->connector);

		drm_connector_get(conn_state->connector);
		conn_state->crtc = crtc;

		drm_dbg_atomic(connector->dev,
			       "Link [CONNECTOR:%d:%s] state %p to [CRTC:%d:%s]\n",
			       connector->base.id, connector->name,
			       conn_state, crtc->base.id, crtc->name);
	पूर्ण अन्यथा अणु
		drm_dbg_atomic(connector->dev,
			       "Link [CONNECTOR:%d:%s] state %p to [NOCRTC]\n",
			       connector->base.id, connector->name,
			       conn_state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_set_crtc_क्रम_connector);

अटल व्योम set_out_fence_क्रम_crtc(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_crtc *crtc, s32 __user *fence_ptr)
अणु
	state->crtcs[drm_crtc_index(crtc)].out_fence_ptr = fence_ptr;
पूर्ण

अटल s32 __user *get_out_fence_क्रम_crtc(काष्ठा drm_atomic_state *state,
					  काष्ठा drm_crtc *crtc)
अणु
	s32 __user *fence_ptr;

	fence_ptr = state->crtcs[drm_crtc_index(crtc)].out_fence_ptr;
	state->crtcs[drm_crtc_index(crtc)].out_fence_ptr = शून्य;

	वापस fence_ptr;
पूर्ण

अटल पूर्णांक set_out_fence_क्रम_connector(काष्ठा drm_atomic_state *state,
					काष्ठा drm_connector *connector,
					s32 __user *fence_ptr)
अणु
	अचिन्हित पूर्णांक index = drm_connector_index(connector);

	अगर (!fence_ptr)
		वापस 0;

	अगर (put_user(-1, fence_ptr))
		वापस -EFAULT;

	state->connectors[index].out_fence_ptr = fence_ptr;

	वापस 0;
पूर्ण

अटल s32 __user *get_out_fence_क्रम_connector(काष्ठा drm_atomic_state *state,
					       काष्ठा drm_connector *connector)
अणु
	अचिन्हित पूर्णांक index = drm_connector_index(connector);
	s32 __user *fence_ptr;

	fence_ptr = state->connectors[index].out_fence_ptr;
	state->connectors[index].out_fence_ptr = शून्य;

	वापस fence_ptr;
पूर्ण

अटल पूर्णांक
drm_atomic_replace_property_blob_from_id(काष्ठा drm_device *dev,
					 काष्ठा drm_property_blob **blob,
					 uपूर्णांक64_t blob_id,
					 sमाप_प्रकार expected_size,
					 sमाप_प्रकार expected_elem_size,
					 bool *replaced)
अणु
	काष्ठा drm_property_blob *new_blob = शून्य;

	अगर (blob_id != 0) अणु
		new_blob = drm_property_lookup_blob(dev, blob_id);
		अगर (new_blob == शून्य)
			वापस -EINVAL;

		अगर (expected_size > 0 &&
		    new_blob->length != expected_size) अणु
			drm_property_blob_put(new_blob);
			वापस -EINVAL;
		पूर्ण
		अगर (expected_elem_size > 0 &&
		    new_blob->length % expected_elem_size != 0) अणु
			drm_property_blob_put(new_blob);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	*replaced |= drm_property_replace_blob(blob, new_blob);
	drm_property_blob_put(new_blob);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_atomic_crtc_set_property(काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state, काष्ठा drm_property *property,
		uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	bool replaced = false;
	पूर्णांक ret;

	अगर (property == config->prop_active)
		state->active = val;
	अन्यथा अगर (property == config->prop_mode_id) अणु
		काष्ठा drm_property_blob *mode =
			drm_property_lookup_blob(dev, val);
		ret = drm_atomic_set_mode_prop_क्रम_crtc(state, mode);
		drm_property_blob_put(mode);
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->prop_vrr_enabled) अणु
		state->vrr_enabled = val;
	पूर्ण अन्यथा अगर (property == config->degamma_lut_property) अणु
		ret = drm_atomic_replace_property_blob_from_id(dev,
					&state->degamma_lut,
					val,
					-1, माप(काष्ठा drm_color_lut),
					&replaced);
		state->color_mgmt_changed |= replaced;
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->cपंचांग_property) अणु
		ret = drm_atomic_replace_property_blob_from_id(dev,
					&state->cपंचांग,
					val,
					माप(काष्ठा drm_color_cपंचांग), -1,
					&replaced);
		state->color_mgmt_changed |= replaced;
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->gamma_lut_property) अणु
		ret = drm_atomic_replace_property_blob_from_id(dev,
					&state->gamma_lut,
					val,
					-1, माप(काष्ठा drm_color_lut),
					&replaced);
		state->color_mgmt_changed |= replaced;
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->prop_out_fence_ptr) अणु
		s32 __user *fence_ptr = u64_to_user_ptr(val);

		अगर (!fence_ptr)
			वापस 0;

		अगर (put_user(-1, fence_ptr))
			वापस -EFAULT;

		set_out_fence_क्रम_crtc(state->state, crtc, fence_ptr);
	पूर्ण अन्यथा अगर (property == crtc->scaling_filter_property) अणु
		state->scaling_filter = val;
	पूर्ण अन्यथा अगर (crtc->funcs->atomic_set_property) अणु
		वापस crtc->funcs->atomic_set_property(crtc, state, property, val);
	पूर्ण अन्यथा अणु
		drm_dbg_atomic(crtc->dev,
			       "[CRTC:%d:%s] unknown property [PROP:%d:%s]]\n",
			       crtc->base.id, crtc->name,
			       property->base.id, property->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
drm_atomic_crtc_get_property(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा drm_crtc_state *state,
		काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;

	अगर (property == config->prop_active)
		*val = drm_atomic_crtc_effectively_active(state);
	अन्यथा अगर (property == config->prop_mode_id)
		*val = (state->mode_blob) ? state->mode_blob->base.id : 0;
	अन्यथा अगर (property == config->prop_vrr_enabled)
		*val = state->vrr_enabled;
	अन्यथा अगर (property == config->degamma_lut_property)
		*val = (state->degamma_lut) ? state->degamma_lut->base.id : 0;
	अन्यथा अगर (property == config->cपंचांग_property)
		*val = (state->cपंचांग) ? state->cपंचांग->base.id : 0;
	अन्यथा अगर (property == config->gamma_lut_property)
		*val = (state->gamma_lut) ? state->gamma_lut->base.id : 0;
	अन्यथा अगर (property == config->prop_out_fence_ptr)
		*val = 0;
	अन्यथा अगर (property == crtc->scaling_filter_property)
		*val = state->scaling_filter;
	अन्यथा अगर (crtc->funcs->atomic_get_property)
		वापस crtc->funcs->atomic_get_property(crtc, state, property, val);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_atomic_plane_set_property(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *state, काष्ठा drm_file *file_priv,
		काष्ठा drm_property *property, uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	bool replaced = false;
	पूर्णांक ret;

	अगर (property == config->prop_fb_id) अणु
		काष्ठा drm_framebuffer *fb;

		fb = drm_framebuffer_lookup(dev, file_priv, val);
		drm_atomic_set_fb_क्रम_plane(state, fb);
		अगर (fb)
			drm_framebuffer_put(fb);
	पूर्ण अन्यथा अगर (property == config->prop_in_fence_fd) अणु
		अगर (state->fence)
			वापस -EINVAL;

		अगर (U642I64(val) == -1)
			वापस 0;

		state->fence = sync_file_get_fence(val);
		अगर (!state->fence)
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (property == config->prop_crtc_id) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_find(dev, file_priv, val);

		अगर (val && !crtc)
			वापस -EACCES;
		वापस drm_atomic_set_crtc_क्रम_plane(state, crtc);
	पूर्ण अन्यथा अगर (property == config->prop_crtc_x) अणु
		state->crtc_x = U642I64(val);
	पूर्ण अन्यथा अगर (property == config->prop_crtc_y) अणु
		state->crtc_y = U642I64(val);
	पूर्ण अन्यथा अगर (property == config->prop_crtc_w) अणु
		state->crtc_w = val;
	पूर्ण अन्यथा अगर (property == config->prop_crtc_h) अणु
		state->crtc_h = val;
	पूर्ण अन्यथा अगर (property == config->prop_src_x) अणु
		state->src_x = val;
	पूर्ण अन्यथा अगर (property == config->prop_src_y) अणु
		state->src_y = val;
	पूर्ण अन्यथा अगर (property == config->prop_src_w) अणु
		state->src_w = val;
	पूर्ण अन्यथा अगर (property == config->prop_src_h) अणु
		state->src_h = val;
	पूर्ण अन्यथा अगर (property == plane->alpha_property) अणु
		state->alpha = val;
	पूर्ण अन्यथा अगर (property == plane->blend_mode_property) अणु
		state->pixel_blend_mode = val;
	पूर्ण अन्यथा अगर (property == plane->rotation_property) अणु
		अगर (!is_घातer_of_2(val & DRM_MODE_ROTATE_MASK)) अणु
			drm_dbg_atomic(plane->dev,
				       "[PLANE:%d:%s] bad rotation bitmask: 0x%llx\n",
				       plane->base.id, plane->name, val);
			वापस -EINVAL;
		पूर्ण
		state->rotation = val;
	पूर्ण अन्यथा अगर (property == plane->zpos_property) अणु
		state->zpos = val;
	पूर्ण अन्यथा अगर (property == plane->color_encoding_property) अणु
		state->color_encoding = val;
	पूर्ण अन्यथा अगर (property == plane->color_range_property) अणु
		state->color_range = val;
	पूर्ण अन्यथा अगर (property == config->prop_fb_damage_clips) अणु
		ret = drm_atomic_replace_property_blob_from_id(dev,
					&state->fb_damage_clips,
					val,
					-1,
					माप(काष्ठा drm_rect),
					&replaced);
		वापस ret;
	पूर्ण अन्यथा अगर (property == plane->scaling_filter_property) अणु
		state->scaling_filter = val;
	पूर्ण अन्यथा अगर (plane->funcs->atomic_set_property) अणु
		वापस plane->funcs->atomic_set_property(plane, state,
				property, val);
	पूर्ण अन्यथा अणु
		drm_dbg_atomic(plane->dev,
			       "[PLANE:%d:%s] unknown property [PROP:%d:%s]]\n",
			       plane->base.id, plane->name,
			       property->base.id, property->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
drm_atomic_plane_get_property(काष्ठा drm_plane *plane,
		स्थिर काष्ठा drm_plane_state *state,
		काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;

	अगर (property == config->prop_fb_id) अणु
		*val = (state->fb) ? state->fb->base.id : 0;
	पूर्ण अन्यथा अगर (property == config->prop_in_fence_fd) अणु
		*val = -1;
	पूर्ण अन्यथा अगर (property == config->prop_crtc_id) अणु
		*val = (state->crtc) ? state->crtc->base.id : 0;
	पूर्ण अन्यथा अगर (property == config->prop_crtc_x) अणु
		*val = I642U64(state->crtc_x);
	पूर्ण अन्यथा अगर (property == config->prop_crtc_y) अणु
		*val = I642U64(state->crtc_y);
	पूर्ण अन्यथा अगर (property == config->prop_crtc_w) अणु
		*val = state->crtc_w;
	पूर्ण अन्यथा अगर (property == config->prop_crtc_h) अणु
		*val = state->crtc_h;
	पूर्ण अन्यथा अगर (property == config->prop_src_x) अणु
		*val = state->src_x;
	पूर्ण अन्यथा अगर (property == config->prop_src_y) अणु
		*val = state->src_y;
	पूर्ण अन्यथा अगर (property == config->prop_src_w) अणु
		*val = state->src_w;
	पूर्ण अन्यथा अगर (property == config->prop_src_h) अणु
		*val = state->src_h;
	पूर्ण अन्यथा अगर (property == plane->alpha_property) अणु
		*val = state->alpha;
	पूर्ण अन्यथा अगर (property == plane->blend_mode_property) अणु
		*val = state->pixel_blend_mode;
	पूर्ण अन्यथा अगर (property == plane->rotation_property) अणु
		*val = state->rotation;
	पूर्ण अन्यथा अगर (property == plane->zpos_property) अणु
		*val = state->zpos;
	पूर्ण अन्यथा अगर (property == plane->color_encoding_property) अणु
		*val = state->color_encoding;
	पूर्ण अन्यथा अगर (property == plane->color_range_property) अणु
		*val = state->color_range;
	पूर्ण अन्यथा अगर (property == config->prop_fb_damage_clips) अणु
		*val = (state->fb_damage_clips) ?
			state->fb_damage_clips->base.id : 0;
	पूर्ण अन्यथा अगर (property == plane->scaling_filter_property) अणु
		*val = state->scaling_filter;
	पूर्ण अन्यथा अगर (plane->funcs->atomic_get_property) अणु
		वापस plane->funcs->atomic_get_property(plane, state, property, val);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_atomic_set_ग_लिखोback_fb_क्रम_connector(
		काष्ठा drm_connector_state *conn_state,
		काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक ret;
	काष्ठा drm_connector *conn = conn_state->connector;

	ret = drm_ग_लिखोback_set_fb(conn_state, fb);
	अगर (ret < 0)
		वापस ret;

	अगर (fb)
		drm_dbg_atomic(conn->dev,
			       "Set [FB:%d] for connector state %p\n",
			       fb->base.id, conn_state);
	अन्यथा
		drm_dbg_atomic(conn->dev,
			       "Set [NOFB] for connector state %p\n",
			       conn_state);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_atomic_connector_set_property(काष्ठा drm_connector *connector,
		काष्ठा drm_connector_state *state, काष्ठा drm_file *file_priv,
		काष्ठा drm_property *property, uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	bool replaced = false;
	पूर्णांक ret;

	अगर (property == config->prop_crtc_id) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_find(dev, file_priv, val);

		अगर (val && !crtc)
			वापस -EACCES;
		वापस drm_atomic_set_crtc_क्रम_connector(state, crtc);
	पूर्ण अन्यथा अगर (property == config->dpms_property) अणु
		/* setting DPMS property requires special handling, which
		 * is करोne in legacy setprop path क्रम us.  Disallow (क्रम
		 * now?) atomic ग_लिखोs to DPMS property:
		 */
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (property == config->tv_select_subconnector_property) अणु
		state->tv.subconnector = val;
	पूर्ण अन्यथा अगर (property == config->tv_left_margin_property) अणु
		state->tv.margins.left = val;
	पूर्ण अन्यथा अगर (property == config->tv_right_margin_property) अणु
		state->tv.margins.right = val;
	पूर्ण अन्यथा अगर (property == config->tv_top_margin_property) अणु
		state->tv.margins.top = val;
	पूर्ण अन्यथा अगर (property == config->tv_bottom_margin_property) अणु
		state->tv.margins.bottom = val;
	पूर्ण अन्यथा अगर (property == config->tv_mode_property) अणु
		state->tv.mode = val;
	पूर्ण अन्यथा अगर (property == config->tv_brightness_property) अणु
		state->tv.brightness = val;
	पूर्ण अन्यथा अगर (property == config->tv_contrast_property) अणु
		state->tv.contrast = val;
	पूर्ण अन्यथा अगर (property == config->tv_flicker_reduction_property) अणु
		state->tv.flicker_reduction = val;
	पूर्ण अन्यथा अगर (property == config->tv_overscan_property) अणु
		state->tv.overscan = val;
	पूर्ण अन्यथा अगर (property == config->tv_saturation_property) अणु
		state->tv.saturation = val;
	पूर्ण अन्यथा अगर (property == config->tv_hue_property) अणु
		state->tv.hue = val;
	पूर्ण अन्यथा अगर (property == config->link_status_property) अणु
		/* Never करोwngrade from GOOD to BAD on userspace's request here,
		 * only hw issues can करो that.
		 *
		 * For an atomic property the userspace करोesn't need to be able
		 * to understand all the properties, but needs to be able to
		 * restore the state it wants on VT चयन. So अगर the userspace
		 * tries to change the link_status from GOOD to BAD, driver
		 * silently rejects it and वापसs a 0. This prevents userspace
		 * from accidently अवरोधing  the display when it restores the
		 * state.
		 */
		अगर (state->link_status != DRM_LINK_STATUS_GOOD)
			state->link_status = val;
	पूर्ण अन्यथा अगर (property == config->hdr_output_metadata_property) अणु
		ret = drm_atomic_replace_property_blob_from_id(dev,
				&state->hdr_output_metadata,
				val,
				माप(काष्ठा hdr_output_metadata), -1,
				&replaced);
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->aspect_ratio_property) अणु
		state->picture_aspect_ratio = val;
	पूर्ण अन्यथा अगर (property == config->content_type_property) अणु
		state->content_type = val;
	पूर्ण अन्यथा अगर (property == connector->scaling_mode_property) अणु
		state->scaling_mode = val;
	पूर्ण अन्यथा अगर (property == config->content_protection_property) अणु
		अगर (val == DRM_MODE_CONTENT_PROTECTION_ENABLED) अणु
			DRM_DEBUG_KMS("only drivers can set CP Enabled\n");
			वापस -EINVAL;
		पूर्ण
		state->content_protection = val;
	पूर्ण अन्यथा अगर (property == config->hdcp_content_type_property) अणु
		state->hdcp_content_type = val;
	पूर्ण अन्यथा अगर (property == connector->colorspace_property) अणु
		state->colorspace = val;
	पूर्ण अन्यथा अगर (property == config->ग_लिखोback_fb_id_property) अणु
		काष्ठा drm_framebuffer *fb;
		पूर्णांक ret;

		fb = drm_framebuffer_lookup(dev, file_priv, val);
		ret = drm_atomic_set_ग_लिखोback_fb_क्रम_connector(state, fb);
		अगर (fb)
			drm_framebuffer_put(fb);
		वापस ret;
	पूर्ण अन्यथा अगर (property == config->ग_लिखोback_out_fence_ptr_property) अणु
		s32 __user *fence_ptr = u64_to_user_ptr(val);

		वापस set_out_fence_क्रम_connector(state->state, connector,
						   fence_ptr);
	पूर्ण अन्यथा अगर (property == connector->max_bpc_property) अणु
		state->max_requested_bpc = val;
	पूर्ण अन्यथा अगर (connector->funcs->atomic_set_property) अणु
		वापस connector->funcs->atomic_set_property(connector,
				state, property, val);
	पूर्ण अन्यथा अणु
		drm_dbg_atomic(connector->dev,
			       "[CONNECTOR:%d:%s] unknown property [PROP:%d:%s]]\n",
			       connector->base.id, connector->name,
			       property->base.id, property->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
drm_atomic_connector_get_property(काष्ठा drm_connector *connector,
		स्थिर काष्ठा drm_connector_state *state,
		काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;

	अगर (property == config->prop_crtc_id) अणु
		*val = (state->crtc) ? state->crtc->base.id : 0;
	पूर्ण अन्यथा अगर (property == config->dpms_property) अणु
		अगर (state->crtc && state->crtc->state->self_refresh_active)
			*val = DRM_MODE_DPMS_ON;
		अन्यथा
			*val = connector->dpms;
	पूर्ण अन्यथा अगर (property == config->tv_select_subconnector_property) अणु
		*val = state->tv.subconnector;
	पूर्ण अन्यथा अगर (property == config->tv_left_margin_property) अणु
		*val = state->tv.margins.left;
	पूर्ण अन्यथा अगर (property == config->tv_right_margin_property) अणु
		*val = state->tv.margins.right;
	पूर्ण अन्यथा अगर (property == config->tv_top_margin_property) अणु
		*val = state->tv.margins.top;
	पूर्ण अन्यथा अगर (property == config->tv_bottom_margin_property) अणु
		*val = state->tv.margins.bottom;
	पूर्ण अन्यथा अगर (property == config->tv_mode_property) अणु
		*val = state->tv.mode;
	पूर्ण अन्यथा अगर (property == config->tv_brightness_property) अणु
		*val = state->tv.brightness;
	पूर्ण अन्यथा अगर (property == config->tv_contrast_property) अणु
		*val = state->tv.contrast;
	पूर्ण अन्यथा अगर (property == config->tv_flicker_reduction_property) अणु
		*val = state->tv.flicker_reduction;
	पूर्ण अन्यथा अगर (property == config->tv_overscan_property) अणु
		*val = state->tv.overscan;
	पूर्ण अन्यथा अगर (property == config->tv_saturation_property) अणु
		*val = state->tv.saturation;
	पूर्ण अन्यथा अगर (property == config->tv_hue_property) अणु
		*val = state->tv.hue;
	पूर्ण अन्यथा अगर (property == config->link_status_property) अणु
		*val = state->link_status;
	पूर्ण अन्यथा अगर (property == config->aspect_ratio_property) अणु
		*val = state->picture_aspect_ratio;
	पूर्ण अन्यथा अगर (property == config->content_type_property) अणु
		*val = state->content_type;
	पूर्ण अन्यथा अगर (property == connector->colorspace_property) अणु
		*val = state->colorspace;
	पूर्ण अन्यथा अगर (property == connector->scaling_mode_property) अणु
		*val = state->scaling_mode;
	पूर्ण अन्यथा अगर (property == config->hdr_output_metadata_property) अणु
		*val = state->hdr_output_metadata ?
			state->hdr_output_metadata->base.id : 0;
	पूर्ण अन्यथा अगर (property == config->content_protection_property) अणु
		*val = state->content_protection;
	पूर्ण अन्यथा अगर (property == config->hdcp_content_type_property) अणु
		*val = state->hdcp_content_type;
	पूर्ण अन्यथा अगर (property == config->ग_लिखोback_fb_id_property) अणु
		/* Writeback framebuffer is one-shot, ग_लिखो and क्रमget */
		*val = 0;
	पूर्ण अन्यथा अगर (property == config->ग_लिखोback_out_fence_ptr_property) अणु
		*val = 0;
	पूर्ण अन्यथा अगर (property == connector->max_bpc_property) अणु
		*val = state->max_requested_bpc;
	पूर्ण अन्यथा अगर (connector->funcs->atomic_get_property) अणु
		वापस connector->funcs->atomic_get_property(connector,
				state, property, val);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक drm_atomic_get_property(काष्ठा drm_mode_object *obj,
		काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = property->dev;
	पूर्णांक ret;

	चयन (obj->type) अणु
	हाल DRM_MODE_OBJECT_CONNECTOR: अणु
		काष्ठा drm_connector *connector = obj_to_connector(obj);

		WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
		ret = drm_atomic_connector_get_property(connector,
				connector->state, property, val);
		अवरोध;
	पूर्ण
	हाल DRM_MODE_OBJECT_CRTC: अणु
		काष्ठा drm_crtc *crtc = obj_to_crtc(obj);

		WARN_ON(!drm_modeset_is_locked(&crtc->mutex));
		ret = drm_atomic_crtc_get_property(crtc,
				crtc->state, property, val);
		अवरोध;
	पूर्ण
	हाल DRM_MODE_OBJECT_PLANE: अणु
		काष्ठा drm_plane *plane = obj_to_plane(obj);

		WARN_ON(!drm_modeset_is_locked(&plane->mutex));
		ret = drm_atomic_plane_get_property(plane,
				plane->state, property, val);
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The big monster ioctl
 */

अटल काष्ठा drm_pending_vblank_event *create_vblank_event(
		काष्ठा drm_crtc *crtc, uपूर्णांक64_t user_data)
अणु
	काष्ठा drm_pending_vblank_event *e = शून्य;

	e = kzalloc(माप *e, GFP_KERNEL);
	अगर (!e)
		वापस शून्य;

	e->event.base.type = DRM_EVENT_FLIP_COMPLETE;
	e->event.base.length = माप(e->event);
	e->event.vbl.crtc_id = crtc->base.id;
	e->event.vbl.user_data = user_data;

	वापस e;
पूर्ण

पूर्णांक drm_atomic_connector_commit_dpms(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_connector *connector,
				     पूर्णांक mode)
अणु
	काष्ठा drm_connector *पंचांगp_connector;
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक i, ret, old_mode = connector->dpms;
	bool active = false;

	ret = drm_modeset_lock(&state->dev->mode_config.connection_mutex,
			       state->acquire_ctx);
	अगर (ret)
		वापस ret;

	अगर (mode != DRM_MODE_DPMS_ON)
		mode = DRM_MODE_DPMS_OFF;
	connector->dpms = mode;

	crtc = connector->state->crtc;
	अगर (!crtc)
		जाओ out;
	ret = drm_atomic_add_affected_connectors(state, crtc);
	अगर (ret)
		जाओ out;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state)) अणु
		ret = PTR_ERR(crtc_state);
		जाओ out;
	पूर्ण

	क्रम_each_new_connector_in_state(state, पंचांगp_connector, new_conn_state, i) अणु
		अगर (new_conn_state->crtc != crtc)
			जारी;
		अगर (पंचांगp_connector->dpms == DRM_MODE_DPMS_ON) अणु
			active = true;
			अवरोध;
		पूर्ण
	पूर्ण

	crtc_state->active = active;
	ret = drm_atomic_commit(state);
out:
	अगर (ret != 0)
		connector->dpms = old_mode;
	वापस ret;
पूर्ण

पूर्णांक drm_atomic_set_property(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_file *file_priv,
			    काष्ठा drm_mode_object *obj,
			    काष्ठा drm_property *prop,
			    uपूर्णांक64_t prop_value)
अणु
	काष्ठा drm_mode_object *ref;
	पूर्णांक ret;

	अगर (!drm_property_change_valid_get(prop, prop_value, &ref))
		वापस -EINVAL;

	चयन (obj->type) अणु
	हाल DRM_MODE_OBJECT_CONNECTOR: अणु
		काष्ठा drm_connector *connector = obj_to_connector(obj);
		काष्ठा drm_connector_state *connector_state;

		connector_state = drm_atomic_get_connector_state(state, connector);
		अगर (IS_ERR(connector_state)) अणु
			ret = PTR_ERR(connector_state);
			अवरोध;
		पूर्ण

		ret = drm_atomic_connector_set_property(connector,
				connector_state, file_priv,
				prop, prop_value);
		अवरोध;
	पूर्ण
	हाल DRM_MODE_OBJECT_CRTC: अणु
		काष्ठा drm_crtc *crtc = obj_to_crtc(obj);
		काष्ठा drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			ret = PTR_ERR(crtc_state);
			अवरोध;
		पूर्ण

		ret = drm_atomic_crtc_set_property(crtc,
				crtc_state, prop, prop_value);
		अवरोध;
	पूर्ण
	हाल DRM_MODE_OBJECT_PLANE: अणु
		काष्ठा drm_plane *plane = obj_to_plane(obj);
		काष्ठा drm_plane_state *plane_state;

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			ret = PTR_ERR(plane_state);
			अवरोध;
		पूर्ण

		ret = drm_atomic_plane_set_property(plane,
				plane_state, file_priv,
				prop, prop_value);
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	drm_property_change_valid_put(prop, ref);
	वापस ret;
पूर्ण

/**
 * DOC: explicit fencing properties
 *
 * Explicit fencing allows userspace to control the buffer synchronization
 * between devices. A Fence or a group of fences are transfered to/from
 * userspace using Sync File fds and there are two DRM properties क्रम that.
 * IN_FENCE_FD on each DRM Plane to send fences to the kernel and
 * OUT_FENCE_PTR on each DRM CRTC to receive fences from the kernel.
 *
 * As a contrast, with implicit fencing the kernel keeps track of any
 * ongoing rendering, and स्वतःmatically ensures that the atomic update रुकोs
 * क्रम any pending rendering to complete. For shared buffers represented with
 * a &काष्ठा dma_buf this is tracked in &काष्ठा dma_resv.
 * Implicit syncing is how Linux traditionally worked (e.g. DRI2/3 on X.org),
 * whereas explicit fencing is what Android wants.
 *
 * "IN_FENCE_FDै :
 *	Use this property to pass a fence that DRM should रुको on beक्रमe
 *	proceeding with the Atomic Commit request and show the framebuffer क्रम
 *	the plane on the screen. The fence can be either a normal fence or a
 *	merged one, the sync_file framework will handle both हालs and use a
 *	fence_array अगर a merged fence is received. Passing -1 here means no
 *	fences to रुको on.
 *
 *	If the Atomic Commit request has the DRM_MODE_ATOMIC_TEST_ONLY flag
 *	it will only check अगर the Sync File is a valid one.
 *
 *	On the driver side the fence is stored on the @fence parameter of
 *	&काष्ठा drm_plane_state. Drivers which also support implicit fencing
 *	should set the implicit fence using drm_atomic_set_fence_क्रम_plane(),
 *	to make sure there's consistent behaviour between drivers in precedence
 *	of implicit vs. explicit fencing.
 *
 * "OUT_FENCE_PTRै :
 *	Use this property to pass a file descriptor poपूर्णांकer to DRM. Once the
 *	Atomic Commit request call वापसs OUT_FENCE_PTR will be filled with
 *	the file descriptor number of a Sync File. This Sync File contains the
 *	CRTC fence that will be संकेतed when all framebuffers present on the
 *	Atomic Commit * request क्रम that given CRTC are scanned out on the
 *	screen.
 *
 *	The Atomic Commit request fails अगर a invalid poपूर्णांकer is passed. If the
 *	Atomic Commit request fails क्रम any other reason the out fence fd
 *	वापसed will be -1. On a Atomic Commit with the
 *	DRM_MODE_ATOMIC_TEST_ONLY flag the out fence will also be set to -1.
 *
 *	Note that out-fences करोn't have a special पूर्णांकerface to drivers and are
 *	पूर्णांकernally represented by a &काष्ठा drm_pending_vblank_event in काष्ठा
 *	&drm_crtc_state, which is also used by the nonblocking atomic commit
 *	helpers and क्रम the DRM event handling क्रम existing userspace.
 */

काष्ठा drm_out_fence_state अणु
	s32 __user *out_fence_ptr;
	काष्ठा sync_file *sync_file;
	पूर्णांक fd;
पूर्ण;

अटल पूर्णांक setup_out_fence(काष्ठा drm_out_fence_state *fence_state,
			   काष्ठा dma_fence *fence)
अणु
	fence_state->fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fence_state->fd < 0)
		वापस fence_state->fd;

	अगर (put_user(fence_state->fd, fence_state->out_fence_ptr))
		वापस -EFAULT;

	fence_state->sync_file = sync_file_create(fence);
	अगर (!fence_state->sync_file)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_संकेतing(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state,
				  काष्ठा drm_mode_atomic *arg,
				  काष्ठा drm_file *file_priv,
				  काष्ठा drm_out_fence_state **fence_state,
				  अचिन्हित पूर्णांक *num_fences)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *conn_state;
	पूर्णांक i, c = 0, ret;

	अगर (arg->flags & DRM_MODE_ATOMIC_TEST_ONLY)
		वापस 0;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		s32 __user *fence_ptr;

		fence_ptr = get_out_fence_क्रम_crtc(crtc_state->state, crtc);

		अगर (arg->flags & DRM_MODE_PAGE_FLIP_EVENT || fence_ptr) अणु
			काष्ठा drm_pending_vblank_event *e;

			e = create_vblank_event(crtc, arg->user_data);
			अगर (!e)
				वापस -ENOMEM;

			crtc_state->event = e;
		पूर्ण

		अगर (arg->flags & DRM_MODE_PAGE_FLIP_EVENT) अणु
			काष्ठा drm_pending_vblank_event *e = crtc_state->event;

			अगर (!file_priv)
				जारी;

			ret = drm_event_reserve_init(dev, file_priv, &e->base,
						     &e->event.base);
			अगर (ret) अणु
				kमुक्त(e);
				crtc_state->event = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (fence_ptr) अणु
			काष्ठा dma_fence *fence;
			काष्ठा drm_out_fence_state *f;

			f = kपुनः_स्मृति(*fence_state, माप(**fence_state) *
				     (*num_fences + 1), GFP_KERNEL);
			अगर (!f)
				वापस -ENOMEM;

			स_रखो(&f[*num_fences], 0, माप(*f));

			f[*num_fences].out_fence_ptr = fence_ptr;
			*fence_state = f;

			fence = drm_crtc_create_fence(crtc);
			अगर (!fence)
				वापस -ENOMEM;

			ret = setup_out_fence(&f[(*num_fences)++], fence);
			अगर (ret) अणु
				dma_fence_put(fence);
				वापस ret;
			पूर्ण

			crtc_state->event->base.fence = fence;
		पूर्ण

		c++;
	पूर्ण

	क्रम_each_new_connector_in_state(state, conn, conn_state, i) अणु
		काष्ठा drm_ग_लिखोback_connector *wb_conn;
		काष्ठा drm_out_fence_state *f;
		काष्ठा dma_fence *fence;
		s32 __user *fence_ptr;

		अगर (!conn_state->ग_लिखोback_job)
			जारी;

		fence_ptr = get_out_fence_क्रम_connector(state, conn);
		अगर (!fence_ptr)
			जारी;

		f = kपुनः_स्मृति(*fence_state, माप(**fence_state) *
			     (*num_fences + 1), GFP_KERNEL);
		अगर (!f)
			वापस -ENOMEM;

		स_रखो(&f[*num_fences], 0, माप(*f));

		f[*num_fences].out_fence_ptr = fence_ptr;
		*fence_state = f;

		wb_conn = drm_connector_to_ग_लिखोback(conn);
		fence = drm_ग_लिखोback_get_out_fence(wb_conn);
		अगर (!fence)
			वापस -ENOMEM;

		ret = setup_out_fence(&f[(*num_fences)++], fence);
		अगर (ret) अणु
			dma_fence_put(fence);
			वापस ret;
		पूर्ण

		conn_state->ग_लिखोback_job->out_fence = fence;
	पूर्ण

	/*
	 * Having this flag means user mode pends on event which will never
	 * reach due to lack of at least one CRTC क्रम संकेतing
	 */
	अगर (c == 0 && (arg->flags & DRM_MODE_PAGE_FLIP_EVENT))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम complete_संकेतing(काष्ठा drm_device *dev,
			       काष्ठा drm_atomic_state *state,
			       काष्ठा drm_out_fence_state *fence_state,
			       अचिन्हित पूर्णांक num_fences,
			       bool install_fds)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक i;

	अगर (install_fds) अणु
		क्रम (i = 0; i < num_fences; i++)
			fd_install(fence_state[i].fd,
				   fence_state[i].sync_file->file);

		kमुक्त(fence_state);
		वापस;
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा drm_pending_vblank_event *event = crtc_state->event;
		/*
		 * Free the allocated event. drm_atomic_helper_setup_commit
		 * can allocate an event too, so only मुक्त it अगर it's ours
		 * to prevent a द्विगुन मुक्त in drm_atomic_state_clear.
		 */
		अगर (event && (event->base.fence || event->base.file_priv)) अणु
			drm_event_cancel_मुक्त(dev, &event->base);
			crtc_state->event = शून्य;
		पूर्ण
	पूर्ण

	अगर (!fence_state)
		वापस;

	क्रम (i = 0; i < num_fences; i++) अणु
		अगर (fence_state[i].sync_file)
			fput(fence_state[i].sync_file->file);
		अगर (fence_state[i].fd >= 0)
			put_unused_fd(fence_state[i].fd);

		/* If this fails log error to the user */
		अगर (fence_state[i].out_fence_ptr &&
		    put_user(-1, fence_state[i].out_fence_ptr))
			drm_dbg_atomic(dev, "Couldn't clear out_fence_ptr\n");
	पूर्ण

	kमुक्त(fence_state);
पूर्ण

पूर्णांक drm_mode_atomic_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_atomic *arg = data;
	uपूर्णांक32_t __user *objs_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(arg->objs_ptr);
	uपूर्णांक32_t __user *count_props_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(arg->count_props_ptr);
	uपूर्णांक32_t __user *props_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(arg->props_ptr);
	uपूर्णांक64_t __user *prop_values_ptr = (uपूर्णांक64_t __user *)(अचिन्हित दीर्घ)(arg->prop_values_ptr);
	अचिन्हित पूर्णांक copied_objs, copied_props;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_out_fence_state *fence_state;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i, j, num_fences;

	/* disallow क्रम drivers not supporting atomic: */
	अगर (!drm_core_check_feature(dev, DRIVER_ATOMIC))
		वापस -EOPNOTSUPP;

	/* disallow क्रम userspace that has not enabled atomic cap (even
	 * though this may be a bit overसमाप्त, since legacy userspace
	 * wouldn't know how to call this ioctl)
	 */
	अगर (!file_priv->atomic) अणु
		drm_dbg_atomic(dev,
			       "commit failed: atomic cap not enabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (arg->flags & ~DRM_MODE_ATOMIC_FLAGS) अणु
		drm_dbg_atomic(dev, "commit failed: invalid flag\n");
		वापस -EINVAL;
	पूर्ण

	अगर (arg->reserved) अणु
		drm_dbg_atomic(dev, "commit failed: reserved field set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (arg->flags & DRM_MODE_PAGE_FLIP_ASYNC) अणु
		drm_dbg_atomic(dev,
			       "commit failed: invalid flag DRM_MODE_PAGE_FLIP_ASYNC\n");
		वापस -EINVAL;
	पूर्ण

	/* can't test and expect an event at the same समय. */
	अगर ((arg->flags & DRM_MODE_ATOMIC_TEST_ONLY) &&
			(arg->flags & DRM_MODE_PAGE_FLIP_EVENT)) अणु
		drm_dbg_atomic(dev,
			       "commit failed: page-flip event requested with test-only commit\n");
		वापस -EINVAL;
	पूर्ण

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस -ENOMEM;

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);
	state->acquire_ctx = &ctx;
	state->allow_modeset = !!(arg->flags & DRM_MODE_ATOMIC_ALLOW_MODESET);

retry:
	copied_objs = 0;
	copied_props = 0;
	fence_state = शून्य;
	num_fences = 0;

	क्रम (i = 0; i < arg->count_objs; i++) अणु
		uपूर्णांक32_t obj_id, count_props;
		काष्ठा drm_mode_object *obj;

		अगर (get_user(obj_id, objs_ptr + copied_objs)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		obj = drm_mode_object_find(dev, file_priv, obj_id, DRM_MODE_OBJECT_ANY);
		अगर (!obj) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण

		अगर (!obj->properties) अणु
			drm_mode_object_put(obj);
			ret = -ENOENT;
			जाओ out;
		पूर्ण

		अगर (get_user(count_props, count_props_ptr + copied_objs)) अणु
			drm_mode_object_put(obj);
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		copied_objs++;

		क्रम (j = 0; j < count_props; j++) अणु
			uपूर्णांक32_t prop_id;
			uपूर्णांक64_t prop_value;
			काष्ठा drm_property *prop;

			अगर (get_user(prop_id, props_ptr + copied_props)) अणु
				drm_mode_object_put(obj);
				ret = -EFAULT;
				जाओ out;
			पूर्ण

			prop = drm_mode_obj_find_prop_id(obj, prop_id);
			अगर (!prop) अणु
				drm_mode_object_put(obj);
				ret = -ENOENT;
				जाओ out;
			पूर्ण

			अगर (copy_from_user(&prop_value,
					   prop_values_ptr + copied_props,
					   माप(prop_value))) अणु
				drm_mode_object_put(obj);
				ret = -EFAULT;
				जाओ out;
			पूर्ण

			ret = drm_atomic_set_property(state, file_priv,
						      obj, prop, prop_value);
			अगर (ret) अणु
				drm_mode_object_put(obj);
				जाओ out;
			पूर्ण

			copied_props++;
		पूर्ण

		drm_mode_object_put(obj);
	पूर्ण

	ret = prepare_संकेतing(dev, state, arg, file_priv, &fence_state,
				&num_fences);
	अगर (ret)
		जाओ out;

	अगर (arg->flags & DRM_MODE_ATOMIC_TEST_ONLY) अणु
		ret = drm_atomic_check_only(state);
	पूर्ण अन्यथा अगर (arg->flags & DRM_MODE_ATOMIC_NONBLOCK) अणु
		ret = drm_atomic_nonblocking_commit(state);
	पूर्ण अन्यथा अणु
		अगर (drm_debug_enabled(DRM_UT_STATE))
			drm_atomic_prपूर्णांक_state(state);

		ret = drm_atomic_commit(state);
	पूर्ण

out:
	complete_संकेतing(dev, state, fence_state, num_fences, !ret);

	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		ret = drm_modeset_backoff(&ctx);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण
