<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
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
 */

#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_util.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * Frame buffers are असलtract memory objects that provide a source of pixels to
 * scanout to a CRTC. Applications explicitly request the creation of frame
 * buffers through the DRM_IOCTL_MODE_ADDFB(2) ioctls and receive an opaque
 * handle that can be passed to the KMS CRTC control, plane configuration and
 * page flip functions.
 *
 * Frame buffers rely on the underlying memory manager क्रम allocating backing
 * storage. When creating a frame buffer applications pass a memory handle
 * (or a list of memory handles क्रम multi-planar क्रमmats) through the
 * &काष्ठा drm_mode_fb_cmd2 argument. For drivers using GEM as their userspace
 * buffer management पूर्णांकerface this would be a GEM handle.  Drivers are however
 * मुक्त to use their own backing storage object handles, e.g. vmwgfx directly
 * exposes special TTM handles to userspace and so expects TTM handles in the
 * create ioctl and not GEM handles.
 *
 * Framebuffers are tracked with &काष्ठा drm_framebuffer. They are published
 * using drm_framebuffer_init() - after calling that function userspace can use
 * and access the framebuffer object. The helper function
 * drm_helper_mode_fill_fb_काष्ठा() can be used to pre-fill the required
 * metadata fields.
 *
 * The lअगरeसमय of a drm framebuffer is controlled with a reference count,
 * drivers can grab additional references with drm_framebuffer_get() and drop
 * them again with drm_framebuffer_put(). For driver-निजी framebuffers क्रम
 * which the last reference is never dropped (e.g. क्रम the fbdev framebuffer
 * when the काष्ठा &काष्ठा drm_framebuffer is embedded पूर्णांकo the fbdev helper
 * काष्ठा) drivers can manually clean up a framebuffer at module unload समय
 * with drm_framebuffer_unरेजिस्टर_निजी(). But करोing this is not
 * recommended, and it's better to have a normal मुक्त-standing &काष्ठा
 * drm_framebuffer.
 */

पूर्णांक drm_framebuffer_check_src_coords(uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
				     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
				     स्थिर काष्ठा drm_framebuffer *fb)
अणु
	अचिन्हित पूर्णांक fb_width, fb_height;

	fb_width = fb->width << 16;
	fb_height = fb->height << 16;

	/* Make sure source coordinates are inside the fb. */
	अगर (src_w > fb_width ||
	    src_x > fb_width - src_w ||
	    src_h > fb_height ||
	    src_y > fb_height - src_h) अणु
		DRM_DEBUG_KMS("Invalid source coordinates "
			      "%u.%06ux%u.%06u+%u.%06u+%u.%06u (fb %ux%u)\n",
			      src_w >> 16, ((src_w & 0xffff) * 15625) >> 10,
			      src_h >> 16, ((src_h & 0xffff) * 15625) >> 10,
			      src_x >> 16, ((src_x & 0xffff) * 15625) >> 10,
			      src_y >> 16, ((src_y & 0xffff) * 15625) >> 10,
			      fb->width, fb->height);
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_mode_addfb - add an FB to the graphics configuration
 * @dev: drm device क्रम the ioctl
 * @or: poपूर्णांकer to request काष्ठाure
 * @file_priv: drm file
 *
 * Add a new FB to the specअगरied CRTC, given a user request. This is the
 * original addfb ioctl which only supported RGB क्रमmats.
 *
 * Called by the user via ioctl, or by an in-kernel client.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_addfb(काष्ठा drm_device *dev, काष्ठा drm_mode_fb_cmd *or,
		   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_fb_cmd2 r = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	r.pixel_क्रमmat = drm_driver_legacy_fb_क्रमmat(dev, or->bpp, or->depth);
	अगर (r.pixel_क्रमmat == DRM_FORMAT_INVALID) अणु
		DRM_DEBUG("bad {bpp:%d, depth:%d}\n", or->bpp, or->depth);
		वापस -EINVAL;
	पूर्ण

	/* convert to new क्रमmat and call new ioctl */
	r.fb_id = or->fb_id;
	r.width = or->width;
	r.height = or->height;
	r.pitches[0] = or->pitch;
	r.handles[0] = or->handle;

	ret = drm_mode_addfb2(dev, &r, file_priv);
	अगर (ret)
		वापस ret;

	or->fb_id = r.fb_id;

	वापस 0;
पूर्ण

पूर्णांक drm_mode_addfb_ioctl(काष्ठा drm_device *dev,
			 व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस drm_mode_addfb(dev, data, file_priv);
पूर्ण

अटल पूर्णांक fb_plane_width(पूर्णांक width,
			  स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, पूर्णांक plane)
अणु
	अगर (plane == 0)
		वापस width;

	वापस DIV_ROUND_UP(width, क्रमmat->hsub);
पूर्ण

अटल पूर्णांक fb_plane_height(पूर्णांक height,
			   स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, पूर्णांक plane)
अणु
	अगर (plane == 0)
		वापस height;

	वापस DIV_ROUND_UP(height, क्रमmat->vsub);
पूर्ण

अटल पूर्णांक framebuffer_check(काष्ठा drm_device *dev,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *r)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	पूर्णांक i;

	/* check अगर the क्रमmat is supported at all */
	अगर (!__drm_क्रमmat_info(r->pixel_क्रमmat)) अणु
		DRM_DEBUG_KMS("bad framebuffer format %p4cc\n",
			      &r->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (r->width == 0) अणु
		DRM_DEBUG_KMS("bad framebuffer width %u\n", r->width);
		वापस -EINVAL;
	पूर्ण

	अगर (r->height == 0) अणु
		DRM_DEBUG_KMS("bad framebuffer height %u\n", r->height);
		वापस -EINVAL;
	पूर्ण

	/* now let the driver pick its own क्रमmat info */
	info = drm_get_क्रमmat_info(dev, r);

	क्रम (i = 0; i < info->num_planes; i++) अणु
		अचिन्हित पूर्णांक width = fb_plane_width(r->width, info, i);
		अचिन्हित पूर्णांक height = fb_plane_height(r->height, info, i);
		अचिन्हित पूर्णांक block_size = info->अक्षर_per_block[i];
		u64 min_pitch = drm_क्रमmat_info_min_pitch(info, i, width);

		अगर (!block_size && (r->modअगरier[i] == DRM_FORMAT_MOD_LINEAR)) अणु
			DRM_DEBUG_KMS("Format requires non-linear modifier for plane %d\n", i);
			वापस -EINVAL;
		पूर्ण

		अगर (!r->handles[i]) अणु
			DRM_DEBUG_KMS("no buffer object handle for plane %d\n", i);
			वापस -EINVAL;
		पूर्ण

		अगर (min_pitch > अच_पूर्णांक_उच्च)
			वापस -दुस्फल;

		अगर ((uपूर्णांक64_t) height * r->pitches[i] + r->offsets[i] > अच_पूर्णांक_उच्च)
			वापस -दुस्फल;

		अगर (block_size && r->pitches[i] < min_pitch) अणु
			DRM_DEBUG_KMS("bad pitch %u for plane %d\n", r->pitches[i], i);
			वापस -EINVAL;
		पूर्ण

		अगर (r->modअगरier[i] && !(r->flags & DRM_MODE_FB_MODIFIERS)) अणु
			DRM_DEBUG_KMS("bad fb modifier %llu for plane %d\n",
				      r->modअगरier[i], i);
			वापस -EINVAL;
		पूर्ण

		अगर (r->flags & DRM_MODE_FB_MODIFIERS &&
		    r->modअगरier[i] != r->modअगरier[0]) अणु
			DRM_DEBUG_KMS("bad fb modifier %llu for plane %d\n",
				      r->modअगरier[i], i);
			वापस -EINVAL;
		पूर्ण

		/* modअगरier specअगरic checks: */
		चयन (r->modअगरier[i]) अणु
		हाल DRM_FORMAT_MOD_SAMSUNG_64_32_TILE:
			/* NOTE: the pitch restriction may be lअगरted later अगर it turns
			 * out that no hw has this restriction:
			 */
			अगर (r->pixel_क्रमmat != DRM_FORMAT_NV12 ||
					width % 128 || height % 32 ||
					r->pitches[i] % 128) अणु
				DRM_DEBUG_KMS("bad modifier data for plane %d\n", i);
				वापस -EINVAL;
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = info->num_planes; i < 4; i++) अणु
		अगर (r->modअगरier[i]) अणु
			DRM_DEBUG_KMS("non-zero modifier for unused plane %d\n", i);
			वापस -EINVAL;
		पूर्ण

		/* Pre-FB_MODIFIERS userspace didn't clear the काष्ठाs properly. */
		अगर (!(r->flags & DRM_MODE_FB_MODIFIERS))
			जारी;

		अगर (r->handles[i]) अणु
			DRM_DEBUG_KMS("buffer object handle for unused plane %d\n", i);
			वापस -EINVAL;
		पूर्ण

		अगर (r->pitches[i]) अणु
			DRM_DEBUG_KMS("non-zero pitch for unused plane %d\n", i);
			वापस -EINVAL;
		पूर्ण

		अगर (r->offsets[i]) अणु
			DRM_DEBUG_KMS("non-zero offset for unused plane %d\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_framebuffer *
drm_पूर्णांकernal_framebuffer_create(काष्ठा drm_device *dev,
				स्थिर काष्ठा drm_mode_fb_cmd2 *r,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;

	अगर (r->flags & ~(DRM_MODE_FB_INTERLACED | DRM_MODE_FB_MODIFIERS)) अणु
		DRM_DEBUG_KMS("bad framebuffer flags 0x%08x\n", r->flags);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर ((config->min_width > r->width) || (r->width > config->max_width)) अणु
		DRM_DEBUG_KMS("bad framebuffer width %d, should be >= %d && <= %d\n",
			  r->width, config->min_width, config->max_width);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर ((config->min_height > r->height) || (r->height > config->max_height)) अणु
		DRM_DEBUG_KMS("bad framebuffer height %d, should be >= %d && <= %d\n",
			  r->height, config->min_height, config->max_height);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (r->flags & DRM_MODE_FB_MODIFIERS &&
	    !dev->mode_config.allow_fb_modअगरiers) अणु
		DRM_DEBUG_KMS("driver does not support fb modifiers\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = framebuffer_check(dev, r);
	अगर (ret)
		वापस ERR_PTR(ret);

	fb = dev->mode_config.funcs->fb_create(dev, file_priv, r);
	अगर (IS_ERR(fb)) अणु
		DRM_DEBUG_KMS("could not create framebuffer\n");
		वापस fb;
	पूर्ण

	वापस fb;
पूर्ण
EXPORT_SYMBOL_FOR_TESTS_ONLY(drm_पूर्णांकernal_framebuffer_create);

/**
 * drm_mode_addfb2 - add an FB to the graphics configuration
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Add a new FB to the specअगरied CRTC, given a user request with क्रमmat. This is
 * the 2nd version of the addfb ioctl, which supports multi-planar framebuffers
 * and uses fourcc codes as pixel क्रमmat specअगरiers.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_addfb2(काष्ठा drm_device *dev,
		    व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_fb_cmd2 *r = data;
	काष्ठा drm_framebuffer *fb;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	fb = drm_पूर्णांकernal_framebuffer_create(dev, r, file_priv);
	अगर (IS_ERR(fb))
		वापस PTR_ERR(fb);

	DRM_DEBUG_KMS("[FB:%d]\n", fb->base.id);
	r->fb_id = fb->base.id;

	/* Transfer ownership to the filp क्रम reaping on बंद */
	mutex_lock(&file_priv->fbs_lock);
	list_add(&fb->filp_head, &file_priv->fbs);
	mutex_unlock(&file_priv->fbs_lock);

	वापस 0;
पूर्ण

पूर्णांक drm_mode_addfb2_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv)
अणु
#अगर_घोषित __BIG_ENDIAN
	अगर (!dev->mode_config.quirk_addfb_prefer_host_byte_order) अणु
		/*
		 * Drivers must set the
		 * quirk_addfb_prefer_host_byte_order quirk to make
		 * the drm_mode_addfb() compat code work correctly on
		 * bigendian machines.
		 *
		 * If they करोn't they पूर्णांकerpret pixel_क्रमmat values
		 * incorrectly क्रम bug compatibility, which in turn
		 * implies the ADDFB2 ioctl करोes not work correctly
		 * then.  So block it to make userspace fallback to
		 * ADDFB.
		 */
		DRM_DEBUG_KMS("addfb2 broken on bigendian");
		वापस -EOPNOTSUPP;
	पूर्ण
#पूर्ण_अगर
	वापस drm_mode_addfb2(dev, data, file_priv);
पूर्ण

काष्ठा drm_mode_rmfb_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा list_head fbs;
पूर्ण;

अटल व्योम drm_mode_rmfb_work_fn(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा drm_mode_rmfb_work *arg = container_of(w, typeof(*arg), work);

	जबतक (!list_empty(&arg->fbs)) अणु
		काष्ठा drm_framebuffer *fb =
			list_first_entry(&arg->fbs, typeof(*fb), filp_head);

		list_del_init(&fb->filp_head);
		drm_framebuffer_हटाओ(fb);
	पूर्ण
पूर्ण

/**
 * drm_mode_rmfb - हटाओ an FB from the configuration
 * @dev: drm device
 * @fb_id: id of framebuffer to हटाओ
 * @file_priv: drm file
 *
 * Remove the specअगरied FB.
 *
 * Called by the user via ioctl, or by an in-kernel client.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_rmfb(काष्ठा drm_device *dev, u32 fb_id,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_framebuffer *fbl = शून्य;
	पूर्णांक found = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	fb = drm_framebuffer_lookup(dev, file_priv, fb_id);
	अगर (!fb)
		वापस -ENOENT;

	mutex_lock(&file_priv->fbs_lock);
	list_क्रम_each_entry(fbl, &file_priv->fbs, filp_head)
		अगर (fb == fbl)
			found = 1;
	अगर (!found) अणु
		mutex_unlock(&file_priv->fbs_lock);
		जाओ fail_unref;
	पूर्ण

	list_del_init(&fb->filp_head);
	mutex_unlock(&file_priv->fbs_lock);

	/* drop the reference we picked up in framebuffer lookup */
	drm_framebuffer_put(fb);

	/*
	 * we now own the reference that was stored in the fbs list
	 *
	 * drm_framebuffer_हटाओ may fail with -EINTR on pending संकेतs,
	 * so run this in a separate stack as there's no way to correctly
	 * handle this after the fb is alपढ़ोy हटाओd from the lookup table.
	 */
	अगर (drm_framebuffer_पढ़ो_refcount(fb) > 1) अणु
		काष्ठा drm_mode_rmfb_work arg;

		INIT_WORK_ONSTACK(&arg.work, drm_mode_rmfb_work_fn);
		INIT_LIST_HEAD(&arg.fbs);
		list_add_tail(&fb->filp_head, &arg.fbs);

		schedule_work(&arg.work);
		flush_work(&arg.work);
		destroy_work_on_stack(&arg.work);
	पूर्ण अन्यथा
		drm_framebuffer_put(fb);

	वापस 0;

fail_unref:
	drm_framebuffer_put(fb);
	वापस -ENOENT;
पूर्ण

पूर्णांक drm_mode_rmfb_ioctl(काष्ठा drm_device *dev,
			व्योम *data, काष्ठा drm_file *file_priv)
अणु
	uपूर्णांक32_t *fb_id = data;

	वापस drm_mode_rmfb(dev, *fb_id, file_priv);
पूर्ण

/**
 * drm_mode_getfb - get FB info
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Lookup the FB given its ID and वापस info about it.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_getfb(काष्ठा drm_device *dev,
		   व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_fb_cmd *r = data;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	fb = drm_framebuffer_lookup(dev, file_priv, r->fb_id);
	अगर (!fb)
		वापस -ENOENT;

	/* Multi-planar framebuffers need getfb2. */
	अगर (fb->क्रमmat->num_planes > 1) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!fb->funcs->create_handle) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	r->height = fb->height;
	r->width = fb->width;
	r->depth = fb->क्रमmat->depth;
	r->bpp = fb->क्रमmat->cpp[0] * 8;
	r->pitch = fb->pitches[0];

	/* GET_FB() is an unprivileged ioctl so we must not वापस a
	 * buffer-handle to non-master processes! For
	 * backwards-compatibility reasons, we cannot make GET_FB() privileged,
	 * so just वापस an invalid handle क्रम non-masters.
	 */
	अगर (!drm_is_current_master(file_priv) && !capable(CAP_SYS_ADMIN)) अणु
		r->handle = 0;
		ret = 0;
		जाओ out;
	पूर्ण

	ret = fb->funcs->create_handle(fb, file_priv, &r->handle);

out:
	drm_framebuffer_put(fb);
	वापस ret;
पूर्ण

/**
 * drm_mode_getfb2_ioctl - get extended FB info
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Lookup the FB given its ID and वापस info about it.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_getfb2_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_fb_cmd2 *r = data;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EINVAL;

	fb = drm_framebuffer_lookup(dev, file_priv, r->fb_id);
	अगर (!fb)
		वापस -ENOENT;

	/* For multi-plane framebuffers, we require the driver to place the
	 * GEM objects directly in the drm_framebuffer. For single-plane
	 * framebuffers, we can fall back to create_handle.
	 */
	अगर (!fb->obj[0] &&
	    (fb->क्रमmat->num_planes > 1 || !fb->funcs->create_handle)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	r->height = fb->height;
	r->width = fb->width;
	r->pixel_क्रमmat = fb->क्रमmat->क्रमmat;

	r->flags = 0;
	अगर (dev->mode_config.allow_fb_modअगरiers)
		r->flags |= DRM_MODE_FB_MODIFIERS;

	क्रम (i = 0; i < ARRAY_SIZE(r->handles); i++) अणु
		r->handles[i] = 0;
		r->pitches[i] = 0;
		r->offsets[i] = 0;
		r->modअगरier[i] = 0;
	पूर्ण

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		r->pitches[i] = fb->pitches[i];
		r->offsets[i] = fb->offsets[i];
		अगर (dev->mode_config.allow_fb_modअगरiers)
			r->modअगरier[i] = fb->modअगरier;
	पूर्ण

	/* GET_FB2() is an unprivileged ioctl so we must not वापस a
	 * buffer-handle to non master/root processes! To match GET_FB()
	 * just वापस invalid handles (0) क्रम non masters/root
	 * rather than making GET_FB2() privileged.
	 */
	अगर (!drm_is_current_master(file_priv) && !capable(CAP_SYS_ADMIN)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		पूर्णांक j;

		/* If we reuse the same object क्रम multiple planes, also
		 * वापस the same handle.
		 */
		क्रम (j = 0; j < i; j++) अणु
			अगर (fb->obj[i] == fb->obj[j]) अणु
				r->handles[i] = r->handles[j];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (r->handles[i])
			जारी;

		अगर (fb->obj[i]) अणु
			ret = drm_gem_handle_create(file_priv, fb->obj[i],
						    &r->handles[i]);
		पूर्ण अन्यथा अणु
			WARN_ON(i > 0);
			ret = fb->funcs->create_handle(fb, file_priv,
						       &r->handles[i]);
		पूर्ण

		अगर (ret != 0)
			जाओ out;
	पूर्ण

out:
	अगर (ret != 0) अणु
		/* Delete any previously-created handles on failure. */
		क्रम (i = 0; i < ARRAY_SIZE(r->handles); i++) अणु
			पूर्णांक j;

			अगर (r->handles[i])
				drm_gem_handle_delete(file_priv, r->handles[i]);

			/* Zero out any handles identical to the one we just
			 * deleted.
			 */
			क्रम (j = i + 1; j < ARRAY_SIZE(r->handles); j++) अणु
				अगर (r->handles[j] == r->handles[i])
					r->handles[j] = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	drm_framebuffer_put(fb);
	वापस ret;
पूर्ण

/**
 * drm_mode_dirtyfb_ioctl - flush frontbuffer rendering on an FB
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Lookup the FB and flush out the damaged area supplied by userspace as a clip
 * rectangle list. Generic userspace which करोes frontbuffer rendering must call
 * this ioctl to flush out the changes on manual-update display outमाला_दो, e.g.
 * usb display-link, mipi manual update panels or edp panel self refresh modes.
 *
 * Modesetting drivers which always update the frontbuffer करो not need to
 * implement the corresponding &drm_framebuffer_funcs.dirty callback.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_dirtyfb_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_clip_rect __user *clips_ptr;
	काष्ठा drm_clip_rect *clips = शून्य;
	काष्ठा drm_mode_fb_dirty_cmd *r = data;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित flags;
	पूर्णांक num_clips;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	fb = drm_framebuffer_lookup(dev, file_priv, r->fb_id);
	अगर (!fb)
		वापस -ENOENT;

	num_clips = r->num_clips;
	clips_ptr = (काष्ठा drm_clip_rect __user *)(अचिन्हित दीर्घ)r->clips_ptr;

	अगर (!num_clips != !clips_ptr) अणु
		ret = -EINVAL;
		जाओ out_err1;
	पूर्ण

	flags = DRM_MODE_FB_सूचीTY_FLAGS & r->flags;

	/* If userspace annotates copy, clips must come in pairs */
	अगर (flags & DRM_MODE_FB_सूचीTY_ANNOTATE_COPY && (num_clips % 2)) अणु
		ret = -EINVAL;
		जाओ out_err1;
	पूर्ण

	अगर (num_clips && clips_ptr) अणु
		अगर (num_clips < 0 || num_clips > DRM_MODE_FB_सूचीTY_MAX_CLIPS) अणु
			ret = -EINVAL;
			जाओ out_err1;
		पूर्ण
		clips = kसुस्मृति(num_clips, माप(*clips), GFP_KERNEL);
		अगर (!clips) अणु
			ret = -ENOMEM;
			जाओ out_err1;
		पूर्ण

		ret = copy_from_user(clips, clips_ptr,
				     num_clips * माप(*clips));
		अगर (ret) अणु
			ret = -EFAULT;
			जाओ out_err2;
		पूर्ण
	पूर्ण

	अगर (fb->funcs->dirty) अणु
		ret = fb->funcs->dirty(fb, file_priv, flags, r->color,
				       clips, num_clips);
	पूर्ण अन्यथा अणु
		ret = -ENOSYS;
	पूर्ण

out_err2:
	kमुक्त(clips);
out_err1:
	drm_framebuffer_put(fb);

	वापस ret;
पूर्ण

/**
 * drm_fb_release - हटाओ and मुक्त the FBs on this file
 * @priv: drm file क्रम the ioctl
 *
 * Destroy all the FBs associated with @filp.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
व्योम drm_fb_release(काष्ठा drm_file *priv)
अणु
	काष्ठा drm_framebuffer *fb, *tfb;
	काष्ठा drm_mode_rmfb_work arg;

	INIT_LIST_HEAD(&arg.fbs);

	/*
	 * When the file माला_लो released that means no one अन्यथा can access the fb
	 * list any more, so no need to grab fpriv->fbs_lock. And we need to
	 * aव्योम upsetting lockdep since the universal cursor code adds a
	 * framebuffer जबतक holding mutex locks.
	 *
	 * Note that a real deadlock between fpriv->fbs_lock and the modeset
	 * locks is impossible here since no one अन्यथा but this function can get
	 * at it any more.
	 */
	list_क्रम_each_entry_safe(fb, tfb, &priv->fbs, filp_head) अणु
		अगर (drm_framebuffer_पढ़ो_refcount(fb) > 1) अणु
			list_move_tail(&fb->filp_head, &arg.fbs);
		पूर्ण अन्यथा अणु
			list_del_init(&fb->filp_head);

			/* This drops the fpriv->fbs reference. */
			drm_framebuffer_put(fb);
		पूर्ण
	पूर्ण

	अगर (!list_empty(&arg.fbs)) अणु
		INIT_WORK_ONSTACK(&arg.work, drm_mode_rmfb_work_fn);

		schedule_work(&arg.work);
		flush_work(&arg.work);
		destroy_work_on_stack(&arg.work);
	पूर्ण
पूर्ण

व्योम drm_framebuffer_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_framebuffer *fb =
			container_of(kref, काष्ठा drm_framebuffer, base.refcount);
	काष्ठा drm_device *dev = fb->dev;

	/*
	 * The lookup idr holds a weak reference, which has not necessarily been
	 * हटाओd at this poपूर्णांक. Check क्रम that.
	 */
	drm_mode_object_unरेजिस्टर(dev, &fb->base);

	fb->funcs->destroy(fb);
पूर्ण

/**
 * drm_framebuffer_init - initialize a framebuffer
 * @dev: DRM device
 * @fb: framebuffer to be initialized
 * @funcs: ... with these functions
 *
 * Allocates an ID क्रम the framebuffer's parent mode object, sets its mode
 * functions & device file and adds it to the master fd list.
 *
 * IMPORTANT:
 * This functions publishes the fb and makes it available क्रम concurrent access
 * by other users. Which means by this poपूर्णांक the fb _must_ be fully set up -
 * since all the fb attributes are invariant over its lअगरeसमय, no further
 * locking but only correct reference counting is required.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_framebuffer_init(काष्ठा drm_device *dev, काष्ठा drm_framebuffer *fb,
			 स्थिर काष्ठा drm_framebuffer_funcs *funcs)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(fb->dev != dev || !fb->क्रमmat))
		वापस -EINVAL;

	INIT_LIST_HEAD(&fb->filp_head);

	fb->funcs = funcs;
	म_नकल(fb->comm, current->comm);

	ret = __drm_mode_object_add(dev, &fb->base, DRM_MODE_OBJECT_FB,
				    false, drm_framebuffer_मुक्त);
	अगर (ret)
		जाओ out;

	mutex_lock(&dev->mode_config.fb_lock);
	dev->mode_config.num_fb++;
	list_add(&fb->head, &dev->mode_config.fb_list);
	mutex_unlock(&dev->mode_config.fb_lock);

	drm_mode_object_रेजिस्टर(dev, &fb->base);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_init);

/**
 * drm_framebuffer_lookup - look up a drm framebuffer and grab a reference
 * @dev: drm device
 * @file_priv: drm file to check क्रम lease against.
 * @id: id of the fb object
 *
 * If successful, this grअसल an additional reference to the framebuffer -
 * callers need to make sure to eventually unreference the वापसed framebuffer
 * again, using drm_framebuffer_put().
 */
काष्ठा drm_framebuffer *drm_framebuffer_lookup(काष्ठा drm_device *dev,
					       काष्ठा drm_file *file_priv,
					       uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *obj;
	काष्ठा drm_framebuffer *fb = शून्य;

	obj = __drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_FB);
	अगर (obj)
		fb = obj_to_fb(obj);
	वापस fb;
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_lookup);

/**
 * drm_framebuffer_unरेजिस्टर_निजी - unरेजिस्टर a निजी fb from the lookup idr
 * @fb: fb to unरेजिस्टर
 *
 * Drivers need to call this when cleaning up driver-निजी framebuffers, e.g.
 * those used क्रम fbdev. Note that the caller must hold a reference of its own,
 * i.e. the object may not be destroyed through this call (since it'll lead to a
 * locking inversion).
 *
 * NOTE: This function is deprecated. For driver-निजी framebuffers it is not
 * recommended to embed a framebuffer काष्ठा info fbdev काष्ठा, instead, a
 * framebuffer poपूर्णांकer is preferred and drm_framebuffer_put() should be called
 * when the framebuffer is to be cleaned up.
 */
व्योम drm_framebuffer_unरेजिस्टर_निजी(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev;

	अगर (!fb)
		वापस;

	dev = fb->dev;

	/* Mark fb as reaped and drop idr ref. */
	drm_mode_object_unरेजिस्टर(dev, &fb->base);
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_unरेजिस्टर_निजी);

/**
 * drm_framebuffer_cleanup - हटाओ a framebuffer object
 * @fb: framebuffer to हटाओ
 *
 * Cleanup framebuffer. This function is पूर्णांकended to be used from the drivers
 * &drm_framebuffer_funcs.destroy callback. It can also be used to clean up
 * driver निजी framebuffers embedded पूर्णांकo a larger काष्ठाure.
 *
 * Note that this function करोes not हटाओ the fb from active usage - अगर it is
 * still used anywhere, hilarity can ensue since userspace could call getfb on
 * the id and get back -EINVAL. Obviously no concern at driver unload समय.
 *
 * Also, the framebuffer will not be हटाओd from the lookup idr - क्रम
 * user-created framebuffers this will happen in in the rmfb ioctl. For
 * driver-निजी objects (e.g. क्रम fbdev) drivers need to explicitly call
 * drm_framebuffer_unरेजिस्टर_निजी.
 */
व्योम drm_framebuffer_cleanup(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev = fb->dev;

	mutex_lock(&dev->mode_config.fb_lock);
	list_del(&fb->head);
	dev->mode_config.num_fb--;
	mutex_unlock(&dev->mode_config.fb_lock);
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_cleanup);

अटल पूर्णांक atomic_हटाओ_fb(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_device *dev = fb->dev;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_connector *conn __maybe_unused;
	काष्ठा drm_connector_state *conn_state;
	पूर्णांक i, ret;
	अचिन्हित plane_mask;
	bool disable_crtcs = false;

retry_disable:
	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	state->acquire_ctx = &ctx;

retry:
	plane_mask = 0;
	ret = drm_modeset_lock_all_ctx(dev, &ctx);
	अगर (ret)
		जाओ unlock;

	drm_क्रम_each_plane(plane, dev) अणु
		काष्ठा drm_plane_state *plane_state;

		अगर (plane->state->fb != fb)
			जारी;

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			ret = PTR_ERR(plane_state);
			जाओ unlock;
		पूर्ण

		अगर (disable_crtcs && plane_state->crtc->primary == plane) अणु
			काष्ठा drm_crtc_state *crtc_state;

			crtc_state = drm_atomic_get_existing_crtc_state(state, plane_state->crtc);

			ret = drm_atomic_add_affected_connectors(state, plane_state->crtc);
			अगर (ret)
				जाओ unlock;

			crtc_state->active = false;
			ret = drm_atomic_set_mode_क्रम_crtc(crtc_state, शून्य);
			अगर (ret)
				जाओ unlock;
		पूर्ण

		drm_atomic_set_fb_क्रम_plane(plane_state, शून्य);
		ret = drm_atomic_set_crtc_क्रम_plane(plane_state, शून्य);
		अगर (ret)
			जाओ unlock;

		plane_mask |= drm_plane_mask(plane);
	पूर्ण

	/* This list is only filled when disable_crtcs is set. */
	क्रम_each_new_connector_in_state(state, conn, conn_state, i) अणु
		ret = drm_atomic_set_crtc_क्रम_connector(conn_state, शून्य);

		अगर (ret)
			जाओ unlock;
	पूर्ण

	अगर (plane_mask)
		ret = drm_atomic_commit(state);

unlock:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

out:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	अगर (ret == -EINVAL && !disable_crtcs) अणु
		disable_crtcs = true;
		जाओ retry_disable;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम legacy_हटाओ_fb(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev = fb->dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;

	drm_modeset_lock_all(dev);
	/* हटाओ from any CRTC */
	drm_क्रम_each_crtc(crtc, dev) अणु
		अगर (crtc->primary->fb == fb) अणु
			/* should turn off the crtc */
			अगर (drm_crtc_क्रमce_disable(crtc))
				DRM_ERROR("failed to reset crtc %p when fb was deleted\n", crtc);
		पूर्ण
	पूर्ण

	drm_क्रम_each_plane(plane, dev) अणु
		अगर (plane->fb == fb)
			drm_plane_क्रमce_disable(plane);
	पूर्ण
	drm_modeset_unlock_all(dev);
पूर्ण

/**
 * drm_framebuffer_हटाओ - हटाओ and unreference a framebuffer object
 * @fb: framebuffer to हटाओ
 *
 * Scans all the CRTCs and planes in @dev's mode_config.  If they're
 * using @fb, हटाओs it, setting it to शून्य. Then drops the reference to the
 * passed-in framebuffer. Might take the modeset locks.
 *
 * Note that this function optimizes the cleanup away अगर the caller holds the
 * last reference to the framebuffer. It is also guaranteed to not take the
 * modeset locks in this हाल.
 */
व्योम drm_framebuffer_हटाओ(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev;

	अगर (!fb)
		वापस;

	dev = fb->dev;

	WARN_ON(!list_empty(&fb->filp_head));

	/*
	 * drm ABI mandates that we हटाओ any deleted framebuffers from active
	 * useage. But since most sane clients only हटाओ framebuffers they no
	 * दीर्घer need, try to optimize this away.
	 *
	 * Since we're holding a reference ourselves, observing a refcount of 1
	 * means that we're the last holder and can skip it. Also, the refcount
	 * can never increase from 1 again, so we करोn't need any barriers or
	 * locks.
	 *
	 * Note that userspace could try to race with use and instate a new
	 * usage _after_ we've cleared all current ones. End result will be an
	 * in-use fb with fb-id == 0. Userspace is allowed to shoot its own foot
	 * in this manner.
	 */
	अगर (drm_framebuffer_पढ़ो_refcount(fb) > 1) अणु
		अगर (drm_drv_uses_atomic_modeset(dev)) अणु
			पूर्णांक ret = atomic_हटाओ_fb(fb);

			WARN(ret, "atomic remove_fb failed with %i\n", ret);
		पूर्ण अन्यथा
			legacy_हटाओ_fb(fb);
	पूर्ण

	drm_framebuffer_put(fb);
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_हटाओ);

/**
 * drm_framebuffer_plane_width - width of the plane given the first plane
 * @width: width of the first plane
 * @fb: the framebuffer
 * @plane: plane index
 *
 * Returns:
 * The width of @plane, given that the width of the first plane is @width.
 */
पूर्णांक drm_framebuffer_plane_width(पूर्णांक width,
				स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	अगर (plane >= fb->क्रमmat->num_planes)
		वापस 0;

	वापस fb_plane_width(width, fb->क्रमmat, plane);
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_plane_width);

/**
 * drm_framebuffer_plane_height - height of the plane given the first plane
 * @height: height of the first plane
 * @fb: the framebuffer
 * @plane: plane index
 *
 * Returns:
 * The height of @plane, given that the height of the first plane is @height.
 */
पूर्णांक drm_framebuffer_plane_height(पूर्णांक height,
				 स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	अगर (plane >= fb->क्रमmat->num_planes)
		वापस 0;

	वापस fb_plane_height(height, fb->क्रमmat, plane);
पूर्ण
EXPORT_SYMBOL(drm_framebuffer_plane_height);

व्योम drm_framebuffer_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
				स्थिर काष्ठा drm_framebuffer *fb)
अणु
	अचिन्हित पूर्णांक i;

	drm_म_लिखो_indent(p, indent, "allocated by = %s\n", fb->comm);
	drm_म_लिखो_indent(p, indent, "refcount=%u\n",
			  drm_framebuffer_पढ़ो_refcount(fb));
	drm_म_लिखो_indent(p, indent, "format=%p4cc\n", &fb->क्रमmat->क्रमmat);
	drm_म_लिखो_indent(p, indent, "modifier=0x%llx\n", fb->modअगरier);
	drm_म_लिखो_indent(p, indent, "size=%ux%u\n", fb->width, fb->height);
	drm_म_लिखो_indent(p, indent, "layers:\n");

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		drm_म_लिखो_indent(p, indent + 1, "size[%u]=%dx%d\n", i,
				  drm_framebuffer_plane_width(fb->width, fb, i),
				  drm_framebuffer_plane_height(fb->height, fb, i));
		drm_म_लिखो_indent(p, indent + 1, "pitch[%u]=%u\n", i, fb->pitches[i]);
		drm_म_लिखो_indent(p, indent + 1, "offset[%u]=%u\n", i, fb->offsets[i]);
		drm_म_लिखो_indent(p, indent + 1, "obj[%u]:%s\n", i,
				  fb->obj[i] ? "" : "(null)");
		अगर (fb->obj[i])
			drm_gem_prपूर्णांक_info(p, indent + 2, fb->obj[i]);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक drm_framebuffer_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	काष्ठा drm_framebuffer *fb;

	mutex_lock(&dev->mode_config.fb_lock);
	drm_क्रम_each_fb(fb, dev) अणु
		drm_म_लिखो(&p, "framebuffer[%u]:\n", fb->base.id);
		drm_framebuffer_prपूर्णांक_info(&p, 1, fb);
	पूर्ण
	mutex_unlock(&dev->mode_config.fb_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list drm_framebuffer_debugfs_list[] = अणु
	अणु "framebuffer", drm_framebuffer_info, 0 पूर्ण,
पूर्ण;

व्योम drm_framebuffer_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(drm_framebuffer_debugfs_list,
				 ARRAY_SIZE(drm_framebuffer_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर
