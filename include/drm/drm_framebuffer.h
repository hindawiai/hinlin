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

#अगर_अघोषित __DRM_FRAMEBUFFER_H__
#घोषणा __DRM_FRAMEBUFFER_H__

#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>

#समावेश <drm/drm_mode_object.h>

काष्ठा drm_clip_rect;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_क्रमmat_info;
काष्ठा drm_framebuffer;
काष्ठा drm_gem_object;

/**
 * काष्ठा drm_framebuffer_funcs - framebuffer hooks
 */
काष्ठा drm_framebuffer_funcs अणु
	/**
	 * @destroy:
	 *
	 * Clean up framebuffer resources, specअगरically also unreference the
	 * backing storage. The core guarantees to call this function क्रम every
	 * framebuffer successfully created by calling
	 * &drm_mode_config_funcs.fb_create. Drivers must also call
	 * drm_framebuffer_cleanup() to release DRM core resources क्रम this
	 * framebuffer.
	 */
	व्योम (*destroy)(काष्ठा drm_framebuffer *framebuffer);

	/**
	 * @create_handle:
	 *
	 * Create a buffer handle in the driver-specअगरic buffer manager (either
	 * GEM or TTM) valid क्रम the passed-in &काष्ठा drm_file. This is used by
	 * the core to implement the GETFB IOCTL, which वापसs (क्रम
	 * sufficiently priviledged user) also a native buffer handle. This can
	 * be used क्रम seamless transitions between modesetting clients by
	 * copying the current screen contents to a निजी buffer and blending
	 * between that and the new contents.
	 *
	 * GEM based drivers should call drm_gem_handle_create() to create the
	 * handle.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*create_handle)(काष्ठा drm_framebuffer *fb,
			     काष्ठा drm_file *file_priv,
			     अचिन्हित पूर्णांक *handle);
	/**
	 * @dirty:
	 *
	 * Optional callback क्रम the dirty fb IOCTL.
	 *
	 * Userspace can notअगरy the driver via this callback that an area of the
	 * framebuffer has changed and should be flushed to the display
	 * hardware. This can also be used पूर्णांकernally, e.g. by the fbdev
	 * emulation, though that's not the हाल currently.
	 *
	 * See करोcumentation in drm_mode.h क्रम the काष्ठा drm_mode_fb_dirty_cmd
	 * क्रम more inक्रमmation as all the semantics and arguments have a one to
	 * one mapping on this function.
	 *
	 * Atomic drivers should use drm_atomic_helper_dirtyfb() to implement
	 * this hook.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*dirty)(काष्ठा drm_framebuffer *framebuffer,
		     काष्ठा drm_file *file_priv, अचिन्हित flags,
		     अचिन्हित color, काष्ठा drm_clip_rect *clips,
		     अचिन्हित num_clips);
पूर्ण;

/**
 * काष्ठा drm_framebuffer - frame buffer object
 *
 * Note that the fb is refcounted क्रम the benefit of driver पूर्णांकernals,
 * क्रम example some hw, disabling a CRTC/plane is asynchronous, and
 * scanout करोes not actually complete until the next vblank.  So some
 * cleanup (like releasing the reference(s) on the backing GEM bo(s))
 * should be deferred.  In हालs like this, the driver would like to
 * hold a ref to the fb even though it has alपढ़ोy been हटाओd from
 * userspace perspective. See drm_framebuffer_get() and
 * drm_framebuffer_put().
 *
 * The refcount is stored inside the mode object @base.
 */
काष्ठा drm_framebuffer अणु
	/**
	 * @dev: DRM device this framebuffer beदीर्घs to
	 */
	काष्ठा drm_device *dev;
	/**
	 * @head: Place on the &drm_mode_config.fb_list, access रक्षित by
	 * &drm_mode_config.fb_lock.
	 */
	काष्ठा list_head head;

	/**
	 * @base: base modeset object काष्ठाure, contains the reference count.
	 */
	काष्ठा drm_mode_object base;

	/**
	 * @comm: Name of the process allocating the fb, used क्रम fb dumping.
	 */
	अक्षर comm[TASK_COMM_LEN];

	/**
	 * @क्रमmat: framebuffer क्रमmat inक्रमmation
	 */
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
	/**
	 * @funcs: framebuffer vfunc table
	 */
	स्थिर काष्ठा drm_framebuffer_funcs *funcs;
	/**
	 * @pitches: Line stride per buffer. For userspace created object this
	 * is copied from drm_mode_fb_cmd2.
	 */
	अचिन्हित पूर्णांक pitches[4];
	/**
	 * @offsets: Offset from buffer start to the actual pixel data in bytes,
	 * per buffer. For userspace created object this is copied from
	 * drm_mode_fb_cmd2.
	 *
	 * Note that this is a linear offset and करोes not take पूर्णांकo account
	 * tiling or buffer laytou per @modअगरier. It meant to be used when the
	 * actual pixel data क्रम this framebuffer plane starts at an offset,
	 * e.g.  when multiple planes are allocated within the same backing
	 * storage buffer object. For tiled layouts this generally means it
	 * @offsets must at least be tile-size aligned, but hardware often has
	 * stricter requirements.
	 *
	 * This should not be used to specअगरiy x/y pixel offsets पूर्णांकo the buffer
	 * data (even क्रम linear buffers). Specअगरying an x/y pixel offset is
	 * instead करोne through the source rectangle in &काष्ठा drm_plane_state.
	 */
	अचिन्हित पूर्णांक offsets[4];
	/**
	 * @modअगरier: Data layout modअगरier. This is used to describe
	 * tiling, or also special layouts (like compression) of auxiliary
	 * buffers. For userspace created object this is copied from
	 * drm_mode_fb_cmd2.
	 */
	uपूर्णांक64_t modअगरier;
	/**
	 * @width: Logical width of the visible area of the framebuffer, in
	 * pixels.
	 */
	अचिन्हित पूर्णांक width;
	/**
	 * @height: Logical height of the visible area of the framebuffer, in
	 * pixels.
	 */
	अचिन्हित पूर्णांक height;
	/**
	 * @flags: Framebuffer flags like DRM_MODE_FB_INTERLACED or
	 * DRM_MODE_FB_MODIFIERS.
	 */
	पूर्णांक flags;
	/**
	 * @hot_x: X coordinate of the cursor hotspot. Used by the legacy cursor
	 * IOCTL when the driver supports cursor through a DRM_PLANE_TYPE_CURSOR
	 * universal plane.
	 */
	पूर्णांक hot_x;
	/**
	 * @hot_y: Y coordinate of the cursor hotspot. Used by the legacy cursor
	 * IOCTL when the driver supports cursor through a DRM_PLANE_TYPE_CURSOR
	 * universal plane.
	 */
	पूर्णांक hot_y;
	/**
	 * @filp_head: Placed on &drm_file.fbs, रक्षित by &drm_file.fbs_lock.
	 */
	काष्ठा list_head filp_head;
	/**
	 * @obj: GEM objects backing the framebuffer, one per plane (optional).
	 *
	 * This is used by the GEM framebuffer helpers, see e.g.
	 * drm_gem_fb_create().
	 */
	काष्ठा drm_gem_object *obj[4];
पूर्ण;

#घोषणा obj_to_fb(x) container_of(x, काष्ठा drm_framebuffer, base)

पूर्णांक drm_framebuffer_init(काष्ठा drm_device *dev,
			 काष्ठा drm_framebuffer *fb,
			 स्थिर काष्ठा drm_framebuffer_funcs *funcs);
काष्ठा drm_framebuffer *drm_framebuffer_lookup(काष्ठा drm_device *dev,
					       काष्ठा drm_file *file_priv,
					       uपूर्णांक32_t id);
व्योम drm_framebuffer_हटाओ(काष्ठा drm_framebuffer *fb);
व्योम drm_framebuffer_cleanup(काष्ठा drm_framebuffer *fb);
व्योम drm_framebuffer_unरेजिस्टर_निजी(काष्ठा drm_framebuffer *fb);

/**
 * drm_framebuffer_get - acquire a framebuffer reference
 * @fb: DRM framebuffer
 *
 * This function increments the framebuffer's reference count.
 */
अटल अंतरभूत व्योम drm_framebuffer_get(काष्ठा drm_framebuffer *fb)
अणु
	drm_mode_object_get(&fb->base);
पूर्ण

/**
 * drm_framebuffer_put - release a framebuffer reference
 * @fb: DRM framebuffer
 *
 * This function decrements the framebuffer's reference count and मुक्तs the
 * framebuffer अगर the reference count drops to zero.
 */
अटल अंतरभूत व्योम drm_framebuffer_put(काष्ठा drm_framebuffer *fb)
अणु
	drm_mode_object_put(&fb->base);
पूर्ण

/**
 * drm_framebuffer_पढ़ो_refcount - पढ़ो the framebuffer reference count.
 * @fb: framebuffer
 *
 * This functions वापसs the framebuffer's reference count.
 */
अटल अंतरभूत uपूर्णांक32_t drm_framebuffer_पढ़ो_refcount(स्थिर काष्ठा drm_framebuffer *fb)
अणु
	वापस kref_पढ़ो(&fb->base.refcount);
पूर्ण

/**
 * drm_framebuffer_assign - store a reference to the fb
 * @p: location to store framebuffer
 * @fb: new framebuffer (maybe शून्य)
 *
 * This functions sets the location to store a reference to the framebuffer,
 * unreferencing the framebuffer that was previously stored in that location.
 */
अटल अंतरभूत व्योम drm_framebuffer_assign(काष्ठा drm_framebuffer **p,
					  काष्ठा drm_framebuffer *fb)
अणु
	अगर (fb)
		drm_framebuffer_get(fb);
	अगर (*p)
		drm_framebuffer_put(*p);
	*p = fb;
पूर्ण

/*
 * drm_क्रम_each_fb - iterate over all framebuffers
 * @fb: the loop cursor
 * @dev: the DRM device
 *
 * Iterate over all framebuffers of @dev. User must hold
 * &drm_mode_config.fb_lock.
 */
#घोषणा drm_क्रम_each_fb(fb, dev) \
	क्रम (WARN_ON(!mutex_is_locked(&(dev)->mode_config.fb_lock)),		\
	     fb = list_first_entry(&(dev)->mode_config.fb_list,	\
					  काष्ठा drm_framebuffer, head);	\
	     &fb->head != (&(dev)->mode_config.fb_list);			\
	     fb = list_next_entry(fb, head))

पूर्णांक drm_framebuffer_plane_width(पूर्णांक width,
				स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);
पूर्णांक drm_framebuffer_plane_height(पूर्णांक height,
				 स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);

/**
 * काष्ठा drm_afbc_framebuffer - a special afbc frame buffer object
 *
 * A derived class of काष्ठा drm_framebuffer, dedicated क्रम afbc use हालs.
 */
काष्ठा drm_afbc_framebuffer अणु
	/**
	 * @base: base framebuffer काष्ठाure.
	 */
	काष्ठा drm_framebuffer base;
	/**
	 * @block_width: width of a single afbc block
	 */
	u32 block_width;
	/**
	 * @block_height: height of a single afbc block
	 */
	u32 block_height;
	/**
	 * @aligned_width: aligned frame buffer width
	 */
	u32 aligned_width;
	/**
	 * @aligned_height: aligned frame buffer height
	 */
	u32 aligned_height;
	/**
	 * @offset: offset of the first afbc header
	 */
	u32 offset;
	/**
	 * @afbc_size: minimum size of afbc buffer
	 */
	u32 afbc_size;
पूर्ण;

#घोषणा fb_to_afbc_fb(x) container_of(x, काष्ठा drm_afbc_framebuffer, base)

#पूर्ण_अगर
