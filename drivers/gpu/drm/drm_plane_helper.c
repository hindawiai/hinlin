<शैली गुरु>
/*
 * Copyright (C) 2014 Intel Corporation
 *
 * DRM universal plane helper functions
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/list.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_rect.h>

#घोषणा SUBPIXEL_MASK 0xffff

/**
 * DOC: overview
 *
 * This helper library has two parts. The first part has support to implement
 * primary plane support on top of the normal CRTC configuration पूर्णांकerface.
 * Since the legacy &drm_mode_config_funcs.set_config पूर्णांकerface ties the primary
 * plane together with the CRTC state this करोes not allow userspace to disable
 * the primary plane itself. The शेष primary plane only expose XRBG8888 and
 * ARGB8888 as valid pixel क्रमmats क्रम the attached framebuffer.
 *
 * Drivers are highly recommended to implement proper support क्रम primary
 * planes, and newly merged drivers must not rely upon these transitional
 * helpers.
 *
 * The second part also implements transitional helpers which allow drivers to
 * gradually चयन to the atomic helper infraकाष्ठाure क्रम plane updates. Once
 * that चयन is complete drivers shouldn't use these any दीर्घer, instead using
 * the proper legacy implementations क्रम update and disable plane hooks provided
 * by the atomic helpers.
 *
 * Again drivers are strongly urged to चयन to the new पूर्णांकerfaces.
 *
 * The plane helpers share the function table काष्ठाures with other helpers,
 * specअगरically also the atomic helpers. See &काष्ठा drm_plane_helper_funcs क्रम
 * the details.
 */

/*
 * Returns the connectors currently associated with a CRTC.  This function
 * should be called twice:  once with a शून्य connector list to retrieve
 * the list size, and once with the properly allocated list to be filled in.
 */
अटल पूर्णांक get_connectors_क्रम_crtc(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_connector **connector_list,
				   पूर्णांक num_connectors)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक count = 0;

	/*
	 * Note: Once we change the plane hooks to more fine-grained locking we
	 * need to grab the connection_mutex here to be able to make these
	 * checks.
	 */
	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->encoder && connector->encoder->crtc == crtc) अणु
			अगर (connector_list != शून्य && count < num_connectors)
				*(connector_list++) = connector;

			count++;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस count;
पूर्ण

अटल पूर्णांक drm_plane_helper_check_update(काष्ठा drm_plane *plane,
					 काष्ठा drm_crtc *crtc,
					 काष्ठा drm_framebuffer *fb,
					 काष्ठा drm_rect *src,
					 काष्ठा drm_rect *dst,
					 अचिन्हित पूर्णांक rotation,
					 पूर्णांक min_scale,
					 पूर्णांक max_scale,
					 bool can_position,
					 bool can_update_disabled,
					 bool *visible)
अणु
	काष्ठा drm_plane_state plane_state = अणु
		.plane = plane,
		.crtc = crtc,
		.fb = fb,
		.src_x = src->x1,
		.src_y = src->y1,
		.src_w = drm_rect_width(src),
		.src_h = drm_rect_height(src),
		.crtc_x = dst->x1,
		.crtc_y = dst->y1,
		.crtc_w = drm_rect_width(dst),
		.crtc_h = drm_rect_height(dst),
		.rotation = rotation,
		.visible = *visible,
	पूर्ण;
	काष्ठा drm_crtc_state crtc_state = अणु
		.crtc = crtc,
		.enable = crtc->enabled,
		.mode = crtc->mode,
	पूर्ण;
	पूर्णांक ret;

	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  min_scale, max_scale,
						  can_position,
						  can_update_disabled);
	अगर (ret)
		वापस ret;

	*src = plane_state.src;
	*dst = plane_state.dst;
	*visible = plane_state.visible;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_primary_helper_update(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
				     काष्ठा drm_framebuffer *fb,
				     पूर्णांक crtc_x, पूर्णांक crtc_y,
				     अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
				     uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
				     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
				     काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_mode_set set = अणु
		.crtc = crtc,
		.fb = fb,
		.mode = &crtc->mode,
		.x = src_x >> 16,
		.y = src_y >> 16,
	पूर्ण;
	काष्ठा drm_rect src = अणु
		.x1 = src_x,
		.y1 = src_y,
		.x2 = src_x + src_w,
		.y2 = src_y + src_h,
	पूर्ण;
	काष्ठा drm_rect dest = अणु
		.x1 = crtc_x,
		.y1 = crtc_y,
		.x2 = crtc_x + crtc_w,
		.y2 = crtc_y + crtc_h,
	पूर्ण;
	काष्ठा drm_connector **connector_list;
	पूर्णांक num_connectors, ret;
	bool visible;

	ret = drm_plane_helper_check_update(plane, crtc, fb,
					    &src, &dest,
					    DRM_MODE_ROTATE_0,
					    DRM_PLANE_HELPER_NO_SCALING,
					    DRM_PLANE_HELPER_NO_SCALING,
					    false, false, &visible);
	अगर (ret)
		वापस ret;

	अगर (!visible)
		/*
		 * Primary plane isn't visible.  Note that unless a driver
		 * provides their own disable function, this will just
		 * wind up वापसing -EINVAL to userspace.
		 */
		वापस plane->funcs->disable_plane(plane, ctx);

	/* Find current connectors क्रम CRTC */
	num_connectors = get_connectors_क्रम_crtc(crtc, शून्य, 0);
	BUG_ON(num_connectors == 0);
	connector_list = kसुस्मृति(num_connectors, माप(*connector_list),
				 GFP_KERNEL);
	अगर (!connector_list)
		वापस -ENOMEM;
	get_connectors_क्रम_crtc(crtc, connector_list, num_connectors);

	set.connectors = connector_list;
	set.num_connectors = num_connectors;

	/*
	 * We call set_config() directly here rather than using
	 * drm_mode_set_config_पूर्णांकernal.  We're reprogramming the same
	 * connectors that were alपढ़ोy in use, so we shouldn't need the extra
	 * cross-CRTC fb refcounting to accomodate stealing connectors.
	 * drm_mode_setplane() alपढ़ोy handles the basic refcounting क्रम the
	 * framebuffers involved in this operation.
	 */
	ret = crtc->funcs->set_config(&set, ctx);

	kमुक्त(connector_list);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_primary_helper_disable(काष्ठा drm_plane *plane,
				      काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * drm_primary_helper_destroy() - Helper क्रम primary plane deकाष्ठाion
 * @plane: plane to destroy
 *
 * Provides a शेष plane destroy handler क्रम primary planes.  This handler
 * is called during CRTC deकाष्ठाion.  We disable the primary plane, हटाओ
 * it from the DRM plane list, and deallocate the plane काष्ठाure.
 */
व्योम drm_primary_helper_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
	kमुक्त(plane);
पूर्ण
EXPORT_SYMBOL(drm_primary_helper_destroy);

स्थिर काष्ठा drm_plane_funcs drm_primary_helper_funcs = अणु
	.update_plane = drm_primary_helper_update,
	.disable_plane = drm_primary_helper_disable,
	.destroy = drm_primary_helper_destroy,
पूर्ण;
EXPORT_SYMBOL(drm_primary_helper_funcs);
