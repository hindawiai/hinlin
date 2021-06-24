<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2008 Red Hat Inc.
 *
 * DRM core CRTC related functions
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * Authors:
 *      Keith Packard
 *	Eric Anholt <eric@anholt.net>
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/uaccess.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modeset_lock.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_debugfs_crc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_file.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * A CRTC represents the overall display pipeline. It receives pixel data from
 * &drm_plane and blends them together. The &drm_display_mode is also attached
 * to the CRTC, specअगरying display timings. On the output side the data is fed
 * to one or more &drm_encoder, which are then each connected to one
 * &drm_connector.
 *
 * To create a CRTC, a KMS drivers allocates and zeroes an instances of
 * &काष्ठा drm_crtc (possibly as part of a larger काष्ठाure) and रेजिस्टरs it
 * with a call to drm_crtc_init_with_planes().
 *
 * The CRTC is also the entry poपूर्णांक क्रम legacy modeset operations, see
 * &drm_crtc_funcs.set_config, legacy plane operations, see
 * &drm_crtc_funcs.page_flip and &drm_crtc_funcs.cursor_set2, and other legacy
 * operations like &drm_crtc_funcs.gamma_set. For atomic drivers all these
 * features are controlled through &drm_property and
 * &drm_mode_config_funcs.atomic_check.
 */

/**
 * drm_crtc_from_index - find the रेजिस्टरed CRTC at an index
 * @dev: DRM device
 * @idx: index of रेजिस्टरed CRTC to find क्रम
 *
 * Given a CRTC index, वापस the रेजिस्टरed CRTC from DRM device's
 * list of CRTCs with matching index. This is the inverse of drm_crtc_index().
 * It's useful in the vblank callbacks (like &drm_driver.enable_vblank or
 * &drm_driver.disable_vblank), since that still deals with indices instead
 * of poपूर्णांकers to &काष्ठा drm_crtc."
 */
काष्ठा drm_crtc *drm_crtc_from_index(काष्ठा drm_device *dev, पूर्णांक idx)
अणु
	काष्ठा drm_crtc *crtc;

	drm_क्रम_each_crtc(crtc, dev)
		अगर (idx == crtc->index)
			वापस crtc;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_crtc_from_index);

पूर्णांक drm_crtc_क्रमce_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_mode_set set = अणु
		.crtc = crtc,
	पूर्ण;

	WARN_ON(drm_drv_uses_atomic_modeset(crtc->dev));

	वापस drm_mode_set_config_पूर्णांकernal(&set);
पूर्ण

अटल अचिन्हित पूर्णांक drm_num_crtcs(काष्ठा drm_device *dev)
अणु
	अचिन्हित पूर्णांक num = 0;
	काष्ठा drm_crtc *पंचांगp;

	drm_क्रम_each_crtc(पंचांगp, dev) अणु
		num++;
	पूर्ण

	वापस num;
पूर्ण

पूर्णांक drm_crtc_रेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret = 0;

	drm_क्रम_each_crtc(crtc, dev) अणु
		drm_debugfs_crtc_add(crtc);

		अगर (crtc->funcs->late_रेजिस्टर)
			ret = crtc->funcs->late_रेजिस्टर(crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम drm_crtc_unरेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;

	drm_क्रम_each_crtc(crtc, dev) अणु
		अगर (crtc->funcs->early_unरेजिस्टर)
			crtc->funcs->early_unरेजिस्टर(crtc);
		drm_debugfs_crtc_हटाओ(crtc);
	पूर्ण
पूर्ण

अटल पूर्णांक drm_crtc_crc_init(काष्ठा drm_crtc *crtc)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	spin_lock_init(&crtc->crc.lock);
	init_रुकोqueue_head(&crtc->crc.wq);
	crtc->crc.source = kstrdup("auto", GFP_KERNEL);
	अगर (!crtc->crc.source)
		वापस -ENOMEM;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम drm_crtc_crc_fini(काष्ठा drm_crtc *crtc)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	kमुक्त(crtc->crc.source);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops drm_crtc_fence_ops;

अटल काष्ठा drm_crtc *fence_to_crtc(काष्ठा dma_fence *fence)
अणु
	BUG_ON(fence->ops != &drm_crtc_fence_ops);
	वापस container_of(fence->lock, काष्ठा drm_crtc, fence_lock);
पूर्ण

अटल स्थिर अक्षर *drm_crtc_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा drm_crtc *crtc = fence_to_crtc(fence);

	वापस crtc->dev->driver->name;
पूर्ण

अटल स्थिर अक्षर *drm_crtc_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा drm_crtc *crtc = fence_to_crtc(fence);

	वापस crtc->समयline_name;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops drm_crtc_fence_ops = अणु
	.get_driver_name = drm_crtc_fence_get_driver_name,
	.get_समयline_name = drm_crtc_fence_get_समयline_name,
पूर्ण;

काष्ठा dma_fence *drm_crtc_create_fence(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dma_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस शून्य;

	dma_fence_init(fence, &drm_crtc_fence_ops, &crtc->fence_lock,
		       crtc->fence_context, ++crtc->fence_seqno);

	वापस fence;
पूर्ण

/**
 * DOC: standard CRTC properties
 *
 * DRM CRTCs have a few standardized properties:
 *
 * ACTIVE:
 * 	Atomic property क्रम setting the घातer state of the CRTC. When set to 1
 * 	the CRTC will actively display content. When set to 0 the CRTC will be
 * 	घातered off. There is no expectation that user-space will reset CRTC
 * 	resources like the mode and planes when setting ACTIVE to 0.
 *
 * 	User-space can rely on an ACTIVE change to 1 to never fail an atomic
 * 	test as दीर्घ as no other property has changed. If a change to ACTIVE
 * 	fails an atomic test, this is a driver bug. For this reason setting
 * 	ACTIVE to 0 must not release पूर्णांकernal resources (like reserved memory
 * 	bandwidth or घड़ी generators).
 *
 * 	Note that the legacy DPMS property on connectors is पूर्णांकernally routed
 * 	to control this property क्रम atomic drivers.
 * MODE_ID:
 * 	Atomic property क्रम setting the CRTC display timings. The value is the
 * 	ID of a blob containing the DRM mode info. To disable the CRTC,
 * 	user-space must set this property to 0.
 *
 * 	Setting MODE_ID to 0 will release reserved resources क्रम the CRTC.
 * SCALING_FILTER:
 * 	Atomic property क्रम setting the scaling filter क्रम CRTC scaler
 *
 * 	The value of this property can be one of the following:
 *
 * 	Default:
 * 		Driver's शेष scaling filter
 * 	Nearest Neighbor:
 * 		Nearest Neighbor scaling filter
 */

__म_लिखो(6, 0)
अटल पूर्णांक __drm_crtc_init_with_planes(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
				       काष्ठा drm_plane *primary,
				       काष्ठा drm_plane *cursor,
				       स्थिर काष्ठा drm_crtc_funcs *funcs,
				       स्थिर अक्षर *name, बहु_सूची ap)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	पूर्णांक ret;

	WARN_ON(primary && primary->type != DRM_PLANE_TYPE_PRIMARY);
	WARN_ON(cursor && cursor->type != DRM_PLANE_TYPE_CURSOR);

	/* crtc index is used with 32bit biपंचांगasks */
	अगर (WARN_ON(config->num_crtc >= 32))
		वापस -EINVAL;

	WARN_ON(drm_drv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destroy_state ||
		 !funcs->atomic_duplicate_state));

	crtc->dev = dev;
	crtc->funcs = funcs;

	INIT_LIST_HEAD(&crtc->commit_list);
	spin_lock_init(&crtc->commit_lock);

	drm_modeset_lock_init(&crtc->mutex);
	ret = drm_mode_object_add(dev, &crtc->base, DRM_MODE_OBJECT_CRTC);
	अगर (ret)
		वापस ret;

	अगर (name) अणु
		crtc->name = kvaप्र_लिखो(GFP_KERNEL, name, ap);
	पूर्ण अन्यथा अणु
		crtc->name = kaप्र_लिखो(GFP_KERNEL, "crtc-%d",
				       drm_num_crtcs(dev));
	पूर्ण
	अगर (!crtc->name) अणु
		drm_mode_object_unरेजिस्टर(dev, &crtc->base);
		वापस -ENOMEM;
	पूर्ण

	crtc->fence_context = dma_fence_context_alloc(1);
	spin_lock_init(&crtc->fence_lock);
	snम_लिखो(crtc->समयline_name, माप(crtc->समयline_name),
		 "CRTC:%d-%s", crtc->base.id, crtc->name);

	crtc->base.properties = &crtc->properties;

	list_add_tail(&crtc->head, &config->crtc_list);
	crtc->index = config->num_crtc++;

	crtc->primary = primary;
	crtc->cursor = cursor;
	अगर (primary && !primary->possible_crtcs)
		primary->possible_crtcs = drm_crtc_mask(crtc);
	अगर (cursor && !cursor->possible_crtcs)
		cursor->possible_crtcs = drm_crtc_mask(crtc);

	ret = drm_crtc_crc_init(crtc);
	अगर (ret) अणु
		drm_mode_object_unरेजिस्टर(dev, &crtc->base);
		वापस ret;
	पूर्ण

	अगर (drm_core_check_feature(dev, DRIVER_ATOMIC)) अणु
		drm_object_attach_property(&crtc->base, config->prop_active, 0);
		drm_object_attach_property(&crtc->base, config->prop_mode_id, 0);
		drm_object_attach_property(&crtc->base,
					   config->prop_out_fence_ptr, 0);
		drm_object_attach_property(&crtc->base,
					   config->prop_vrr_enabled, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_crtc_init_with_planes - Initialise a new CRTC object with
 *    specअगरied primary and cursor planes.
 * @dev: DRM device
 * @crtc: CRTC object to init
 * @primary: Primary plane क्रम CRTC
 * @cursor: Cursor plane क्रम CRTC
 * @funcs: callbacks क्रम the new CRTC
 * @name: म_लिखो style क्रमmat string क्रम the CRTC name, or शून्य क्रम शेष name
 *
 * Inits a new object created as base part of a driver crtc object. Drivers
 * should use this function instead of drm_crtc_init(), which is only provided
 * क्रम backwards compatibility with drivers which करो not yet support universal
 * planes). For really simple hardware which has only 1 plane look at
 * drm_simple_display_pipe_init() instead.
 * The &drm_crtc_funcs.destroy hook should call drm_crtc_cleanup() and kमुक्त()
 * the crtc काष्ठाure. The crtc काष्ठाure should not be allocated with
 * devm_kzalloc().
 *
 * The @primary and @cursor planes are only relevant क्रम legacy uAPI, see
 * &drm_crtc.primary and &drm_crtc.cursor.
 *
 * Note: consider using drmm_crtc_alloc_with_planes() instead of
 * drm_crtc_init_with_planes() to let the DRM managed resource infraकाष्ठाure
 * take care of cleanup and deallocation.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_crtc_init_with_planes(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
			      काष्ठा drm_plane *primary,
			      काष्ठा drm_plane *cursor,
			      स्थिर काष्ठा drm_crtc_funcs *funcs,
			      स्थिर अक्षर *name, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	WARN_ON(!funcs->destroy);

	बहु_शुरू(ap, name);
	ret = __drm_crtc_init_with_planes(dev, crtc, primary, cursor, funcs,
					  name, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_crtc_init_with_planes);

अटल व्योम drmm_crtc_alloc_with_planes_cleanup(काष्ठा drm_device *dev,
						व्योम *ptr)
अणु
	काष्ठा drm_crtc *crtc = ptr;

	drm_crtc_cleanup(crtc);
पूर्ण

व्योम *__drmm_crtc_alloc_with_planes(काष्ठा drm_device *dev,
				    माप_प्रकार size, माप_प्रकार offset,
				    काष्ठा drm_plane *primary,
				    काष्ठा drm_plane *cursor,
				    स्थिर काष्ठा drm_crtc_funcs *funcs,
				    स्थिर अक्षर *name, ...)
अणु
	व्योम *container;
	काष्ठा drm_crtc *crtc;
	बहु_सूची ap;
	पूर्णांक ret;

	अगर (WARN_ON(!funcs || funcs->destroy))
		वापस ERR_PTR(-EINVAL);

	container = drmm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-ENOMEM);

	crtc = container + offset;

	बहु_शुरू(ap, name);
	ret = __drm_crtc_init_with_planes(dev, crtc, primary, cursor, funcs,
					  name, ap);
	बहु_पूर्ण(ap);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = drmm_add_action_or_reset(dev, drmm_crtc_alloc_with_planes_cleanup,
				       crtc);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस container;
पूर्ण
EXPORT_SYMBOL(__drmm_crtc_alloc_with_planes);

/**
 * drm_crtc_cleanup - Clean up the core crtc usage
 * @crtc: CRTC to cleanup
 *
 * This function cleans up @crtc and हटाओs it from the DRM mode setting
 * core. Note that the function करोes *not* मुक्त the crtc काष्ठाure itself,
 * this is the responsibility of the caller.
 */
व्योम drm_crtc_cleanup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;

	/* Note that the crtc_list is considered to be अटल; should we
	 * हटाओ the drm_crtc at runसमय we would have to decrement all
	 * the indices on the drm_crtc after us in the crtc_list.
	 */

	drm_crtc_crc_fini(crtc);

	kमुक्त(crtc->gamma_store);
	crtc->gamma_store = शून्य;

	drm_modeset_lock_fini(&crtc->mutex);

	drm_mode_object_unरेजिस्टर(dev, &crtc->base);
	list_del(&crtc->head);
	dev->mode_config.num_crtc--;

	WARN_ON(crtc->state && !crtc->funcs->atomic_destroy_state);
	अगर (crtc->state && crtc->funcs->atomic_destroy_state)
		crtc->funcs->atomic_destroy_state(crtc, crtc->state);

	kमुक्त(crtc->name);

	स_रखो(crtc, 0, माप(*crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_cleanup);

/**
 * drm_mode_अ_लोrtc - get CRTC configuration
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Conकाष्ठा a CRTC configuration काष्ठाure to वापस to the user.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_अ_लोrtc(काष्ठा drm_device *dev,
		     व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_crtc *crtc_resp = data;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	crtc = drm_crtc_find(dev, file_priv, crtc_resp->crtc_id);
	अगर (!crtc)
		वापस -ENOENT;

	plane = crtc->primary;

	crtc_resp->gamma_size = crtc->gamma_size;

	drm_modeset_lock(&plane->mutex, शून्य);
	अगर (plane->state && plane->state->fb)
		crtc_resp->fb_id = plane->state->fb->base.id;
	अन्यथा अगर (!plane->state && plane->fb)
		crtc_resp->fb_id = plane->fb->base.id;
	अन्यथा
		crtc_resp->fb_id = 0;

	अगर (plane->state) अणु
		crtc_resp->x = plane->state->src_x >> 16;
		crtc_resp->y = plane->state->src_y >> 16;
	पूर्ण
	drm_modeset_unlock(&plane->mutex);

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state) अणु
		अगर (crtc->state->enable) अणु
			drm_mode_convert_to_umode(&crtc_resp->mode, &crtc->state->mode);
			crtc_resp->mode_valid = 1;
		पूर्ण अन्यथा अणु
			crtc_resp->mode_valid = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		crtc_resp->x = crtc->x;
		crtc_resp->y = crtc->y;

		अगर (crtc->enabled) अणु
			drm_mode_convert_to_umode(&crtc_resp->mode, &crtc->mode);
			crtc_resp->mode_valid = 1;

		पूर्ण अन्यथा अणु
			crtc_resp->mode_valid = 0;
		पूर्ण
	पूर्ण
	अगर (!file_priv->aspect_ratio_allowed)
		crtc_resp->mode.flags &= ~DRM_MODE_FLAG_PIC_AR_MASK;
	drm_modeset_unlock(&crtc->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __drm_mode_set_config_पूर्णांकernal(काष्ठा drm_mode_set *set,
					  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_crtc *crtc = set->crtc;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_crtc *पंचांगp;
	पूर्णांक ret;

	WARN_ON(drm_drv_uses_atomic_modeset(crtc->dev));

	/*
	 * NOTE: ->set_config can also disable other crtcs (अगर we steal all
	 * connectors from it), hence we need to refcount the fbs across all
	 * crtcs. Atomic modeset will have saner semantics ...
	 */
	drm_क्रम_each_crtc(पंचांगp, crtc->dev) अणु
		काष्ठा drm_plane *plane = पंचांगp->primary;

		plane->old_fb = plane->fb;
	पूर्ण

	fb = set->fb;

	ret = crtc->funcs->set_config(set, ctx);
	अगर (ret == 0) अणु
		काष्ठा drm_plane *plane = crtc->primary;

		plane->crtc = fb ? crtc : शून्य;
		plane->fb = fb;
	पूर्ण

	drm_क्रम_each_crtc(पंचांगp, crtc->dev) अणु
		काष्ठा drm_plane *plane = पंचांगp->primary;

		अगर (plane->fb)
			drm_framebuffer_get(plane->fb);
		अगर (plane->old_fb)
			drm_framebuffer_put(plane->old_fb);
		plane->old_fb = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * drm_mode_set_config_पूर्णांकernal - helper to call &drm_mode_config_funcs.set_config
 * @set: modeset config to set
 *
 * This is a little helper to wrap पूर्णांकernal calls to the
 * &drm_mode_config_funcs.set_config driver पूर्णांकerface. The only thing it adds is
 * correct refcounting dance.
 *
 * This should only be used by non-atomic legacy drivers.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_set_config_पूर्णांकernal(काष्ठा drm_mode_set *set)
अणु
	WARN_ON(drm_drv_uses_atomic_modeset(set->crtc->dev));

	वापस __drm_mode_set_config_पूर्णांकernal(set, शून्य);
पूर्ण
EXPORT_SYMBOL(drm_mode_set_config_पूर्णांकernal);

/**
 * drm_crtc_check_viewport - Checks that a framebuffer is big enough क्रम the
 *     CRTC viewport
 * @crtc: CRTC that framebuffer will be displayed on
 * @x: x panning
 * @y: y panning
 * @mode: mode that framebuffer will be displayed under
 * @fb: framebuffer to check size of
 */
पूर्णांक drm_crtc_check_viewport(स्थिर काष्ठा drm_crtc *crtc,
			    पूर्णांक x, पूर्णांक y,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_framebuffer *fb)

अणु
	पूर्णांक hdisplay, vdisplay;

	drm_mode_get_hv_timing(mode, &hdisplay, &vdisplay);

	अगर (crtc->state &&
	    drm_rotation_90_or_270(crtc->primary->state->rotation))
		swap(hdisplay, vdisplay);

	वापस drm_framebuffer_check_src_coords(x << 16, y << 16,
						hdisplay << 16, vdisplay << 16,
						fb);
पूर्ण
EXPORT_SYMBOL(drm_crtc_check_viewport);

/**
 * drm_mode_setcrtc - set CRTC configuration
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Build a new CRTC configuration based on user request.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_setcrtc(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_mode_crtc *crtc_req = data;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	काष्ठा drm_connector **connector_set = शून्य, *connector;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_mode_set set;
	uपूर्णांक32_t __user *set_connectors_ptr;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	/*
	 * Universal plane src offsets are only 16.16, prevent havoc क्रम
	 * drivers using universal plane code पूर्णांकernally.
	 */
	अगर (crtc_req->x & 0xffff0000 || crtc_req->y & 0xffff0000)
		वापस -दुस्फल;

	crtc = drm_crtc_find(dev, file_priv, crtc_req->crtc_id);
	अगर (!crtc) अणु
		DRM_DEBUG_KMS("Unknown CRTC ID %d\n", crtc_req->crtc_id);
		वापस -ENOENT;
	पूर्ण
	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	plane = crtc->primary;

	/* allow disabling with the primary plane leased */
	अगर (crtc_req->mode_valid && !drm_lease_held(file_priv, plane->base.id))
		वापस -EACCES;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx,
				   DRM_MODESET_ACQUIRE_INTERRUPTIBLE, ret);

	अगर (crtc_req->mode_valid) अणु
		/* If we have a mode we need a framebuffer. */
		/* If we pass -1, set the mode with the currently bound fb */
		अगर (crtc_req->fb_id == -1) अणु
			काष्ठा drm_framebuffer *old_fb;

			अगर (plane->state)
				old_fb = plane->state->fb;
			अन्यथा
				old_fb = plane->fb;

			अगर (!old_fb) अणु
				DRM_DEBUG_KMS("CRTC doesn't have current FB\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			fb = old_fb;
			/* Make refcounting symmetric with the lookup path. */
			drm_framebuffer_get(fb);
		पूर्ण अन्यथा अणु
			fb = drm_framebuffer_lookup(dev, file_priv, crtc_req->fb_id);
			अगर (!fb) अणु
				DRM_DEBUG_KMS("Unknown FB ID%d\n",
						crtc_req->fb_id);
				ret = -ENOENT;
				जाओ out;
			पूर्ण
		पूर्ण

		mode = drm_mode_create(dev);
		अगर (!mode) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		अगर (!file_priv->aspect_ratio_allowed &&
		    (crtc_req->mode.flags & DRM_MODE_FLAG_PIC_AR_MASK) != DRM_MODE_FLAG_PIC_AR_NONE) अणु
			DRM_DEBUG_KMS("Unexpected aspect-ratio flag bits\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण


		ret = drm_mode_convert_umode(dev, mode, &crtc_req->mode);
		अगर (ret) अणु
			DRM_DEBUG_KMS("Invalid mode (ret=%d, status=%s)\n",
				      ret, drm_get_mode_status_name(mode->status));
			drm_mode_debug_prपूर्णांकmodeline(mode);
			जाओ out;
		पूर्ण

		/*
		 * Check whether the primary plane supports the fb pixel क्रमmat.
		 * Drivers not implementing the universal planes API use a
		 * शेष क्रमmats list provided by the DRM core which करोesn't
		 * match real hardware capabilities. Skip the check in that
		 * हाल.
		 */
		अगर (!plane->क्रमmat_शेष) अणु
			ret = drm_plane_check_pixel_क्रमmat(plane,
							   fb->क्रमmat->क्रमmat,
							   fb->modअगरier);
			अगर (ret) अणु
				DRM_DEBUG_KMS("Invalid pixel format %p4cc, modifier 0x%llx\n",
					      &fb->क्रमmat->क्रमmat,
					      fb->modअगरier);
				जाओ out;
			पूर्ण
		पूर्ण

		ret = drm_crtc_check_viewport(crtc, crtc_req->x, crtc_req->y,
					      mode, fb);
		अगर (ret)
			जाओ out;

	पूर्ण

	अगर (crtc_req->count_connectors == 0 && mode) अणु
		DRM_DEBUG_KMS("Count connectors is 0 but mode set\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (crtc_req->count_connectors > 0 && (!mode || !fb)) अणु
		DRM_DEBUG_KMS("Count connectors is %d but no mode or fb set\n",
			  crtc_req->count_connectors);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (crtc_req->count_connectors > 0) अणु
		u32 out_id;

		/* Aव्योम unbounded kernel memory allocation */
		अगर (crtc_req->count_connectors > config->num_connector) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		connector_set = kदो_स्मृति_array(crtc_req->count_connectors,
					      माप(काष्ठा drm_connector *),
					      GFP_KERNEL);
		अगर (!connector_set) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < crtc_req->count_connectors; i++) अणु
			connector_set[i] = शून्य;
			set_connectors_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)crtc_req->set_connectors_ptr;
			अगर (get_user(out_id, &set_connectors_ptr[i])) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण

			connector = drm_connector_lookup(dev, file_priv, out_id);
			अगर (!connector) अणु
				DRM_DEBUG_KMS("Connector id %d unknown\n",
						out_id);
				ret = -ENOENT;
				जाओ out;
			पूर्ण
			DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
					connector->base.id,
					connector->name);

			connector_set[i] = connector;
		पूर्ण
	पूर्ण

	set.crtc = crtc;
	set.x = crtc_req->x;
	set.y = crtc_req->y;
	set.mode = mode;
	set.connectors = connector_set;
	set.num_connectors = crtc_req->count_connectors;
	set.fb = fb;

	अगर (drm_drv_uses_atomic_modeset(dev))
		ret = crtc->funcs->set_config(&set, &ctx);
	अन्यथा
		ret = __drm_mode_set_config_पूर्णांकernal(&set, &ctx);

out:
	अगर (fb)
		drm_framebuffer_put(fb);

	अगर (connector_set) अणु
		क्रम (i = 0; i < crtc_req->count_connectors; i++) अणु
			अगर (connector_set[i])
				drm_connector_put(connector_set[i]);
		पूर्ण
	पूर्ण
	kमुक्त(connector_set);
	drm_mode_destroy(dev, mode);

	/* In हाल we need to retry... */
	connector_set = शून्य;
	fb = शून्य;
	mode = शून्य;

	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);

	वापस ret;
पूर्ण

पूर्णांक drm_mode_crtc_set_obj_prop(काष्ठा drm_mode_object *obj,
			       काष्ठा drm_property *property,
			       uपूर्णांक64_t value)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा drm_crtc *crtc = obj_to_crtc(obj);

	अगर (crtc->funcs->set_property)
		ret = crtc->funcs->set_property(crtc, property, value);
	अगर (!ret)
		drm_object_property_set_value(obj, property, value);

	वापस ret;
पूर्ण

/**
 * drm_crtc_create_scaling_filter_property - create a new scaling filter
 * property
 *
 * @crtc: drm CRTC
 * @supported_filters: biपंचांगask of supported scaling filters, must include
 *		       BIT(DRM_SCALING_FILTER_DEFAULT).
 *
 * This function lets driver to enable the scaling filter property on a given
 * CRTC.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक drm_crtc_create_scaling_filter_property(काष्ठा drm_crtc *crtc,
					    अचिन्हित पूर्णांक supported_filters)
अणु
	काष्ठा drm_property *prop =
		drm_create_scaling_filter_prop(crtc->dev, supported_filters);

	अगर (IS_ERR(prop))
		वापस PTR_ERR(prop);

	drm_object_attach_property(&crtc->base, prop,
				   DRM_SCALING_FILTER_DEFAULT);
	crtc->scaling_filter_property = prop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_crtc_create_scaling_filter_property);
