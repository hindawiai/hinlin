<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drm gem framebuffer helper functions
 *
 * Copyright (C) 2017 Noralf Trथचnnes
 */

#समावेश <linux/slab.h>

#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_modeset_helper.h>

#घोषणा AFBC_HEADER_SIZE		16
#घोषणा AFBC_TH_LAYOUT_ALIGNMENT	8
#घोषणा AFBC_HDR_ALIGN			64
#घोषणा AFBC_SUPERBLOCK_PIXELS		256
#घोषणा AFBC_SUPERBLOCK_ALIGNMENT	128
#घोषणा AFBC_TH_BODY_START_ALIGNMENT	4096

/**
 * DOC: overview
 *
 * This library provides helpers क्रम drivers that करोn't subclass
 * &drm_framebuffer and use &drm_gem_object क्रम their backing storage.
 *
 * Drivers without additional needs to validate framebuffers can simply use
 * drm_gem_fb_create() and everything is wired up स्वतःmatically. Other drivers
 * can use all parts independently.
 */

/**
 * drm_gem_fb_get_obj() - Get GEM object backing the framebuffer
 * @fb: Framebuffer
 * @plane: Plane index
 *
 * No additional reference is taken beyond the one that the &drm_frambuffer
 * alपढ़ोy holds.
 *
 * Returns:
 * Poपूर्णांकer to &drm_gem_object क्रम the given framebuffer and plane index or शून्य
 * अगर it करोes not exist.
 */
काष्ठा drm_gem_object *drm_gem_fb_get_obj(काष्ठा drm_framebuffer *fb,
					  अचिन्हित पूर्णांक plane)
अणु
	अगर (plane >= 4)
		वापस शून्य;

	वापस fb->obj[plane];
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_get_obj);

अटल पूर्णांक
drm_gem_fb_init(काष्ठा drm_device *dev,
		 काष्ठा drm_framebuffer *fb,
		 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
		 काष्ठा drm_gem_object **obj, अचिन्हित पूर्णांक num_planes,
		 स्थिर काष्ठा drm_framebuffer_funcs *funcs)
अणु
	पूर्णांक ret, i;

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);

	क्रम (i = 0; i < num_planes; i++)
		fb->obj[i] = obj[i];

	ret = drm_framebuffer_init(dev, fb, funcs);
	अगर (ret)
		drm_err(dev, "Failed to init framebuffer: %d\n", ret);

	वापस ret;
पूर्ण

/**
 * drm_gem_fb_destroy - Free GEM backed framebuffer
 * @fb: Framebuffer
 *
 * Frees a GEM backed framebuffer with its backing buffer(s) and the काष्ठाure
 * itself. Drivers can use this as their &drm_framebuffer_funcs->destroy
 * callback.
 */
व्योम drm_gem_fb_destroy(काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		drm_gem_object_put(fb->obj[i]);

	drm_framebuffer_cleanup(fb);
	kमुक्त(fb);
पूर्ण
EXPORT_SYMBOL(drm_gem_fb_destroy);

/**
 * drm_gem_fb_create_handle - Create handle क्रम GEM backed framebuffer
 * @fb: Framebuffer
 * @file: DRM file to रेजिस्टर the handle क्रम
 * @handle: Poपूर्णांकer to वापस the created handle
 *
 * This function creates a handle क्रम the GEM object backing the framebuffer.
 * Drivers can use this as their &drm_framebuffer_funcs->create_handle
 * callback. The GETFB IOCTL calls पूर्णांकo this callback.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_fb_create_handle(काष्ठा drm_framebuffer *fb, काष्ठा drm_file *file,
			     अचिन्हित पूर्णांक *handle)
अणु
	वापस drm_gem_handle_create(file, fb->obj[0], handle);
पूर्ण
EXPORT_SYMBOL(drm_gem_fb_create_handle);

/**
 * drm_gem_fb_init_with_funcs() - Helper function क्रम implementing
 *				  &drm_mode_config_funcs.fb_create
 *				  callback in हालs when the driver
 *				  allocates a subclass of
 *				  काष्ठा drm_framebuffer
 * @dev: DRM device
 * @fb: framebuffer object
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 * @funcs: vtable to be used क्रम the new framebuffer object
 *
 * This function can be used to set &drm_framebuffer_funcs क्रम drivers that need
 * custom framebuffer callbacks. Use drm_gem_fb_create() अगर you करोn't need to
 * change &drm_framebuffer_funcs. The function करोes buffer size validation.
 * The buffer size validation is क्रम a general हाल, though, so users should
 * pay attention to the checks being appropriate क्रम them or, at least,
 * non-conflicting.
 *
 * Returns:
 * Zero or a negative error code.
 */
पूर्णांक drm_gem_fb_init_with_funcs(काष्ठा drm_device *dev,
			       काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_file *file,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			       स्थिर काष्ठा drm_framebuffer_funcs *funcs)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	काष्ठा drm_gem_object *objs[4];
	पूर्णांक ret, i;

	info = drm_get_क्रमmat_info(dev, mode_cmd);
	अगर (!info)
		वापस -EINVAL;

	क्रम (i = 0; i < info->num_planes; i++) अणु
		अचिन्हित पूर्णांक width = mode_cmd->width / (i ? info->hsub : 1);
		अचिन्हित पूर्णांक height = mode_cmd->height / (i ? info->vsub : 1);
		अचिन्हित पूर्णांक min_size;

		objs[i] = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		अगर (!objs[i]) अणु
			drm_dbg_kms(dev, "Failed to lookup GEM object\n");
			ret = -ENOENT;
			जाओ err_gem_object_put;
		पूर्ण

		min_size = (height - 1) * mode_cmd->pitches[i]
			 + drm_क्रमmat_info_min_pitch(info, i, width)
			 + mode_cmd->offsets[i];

		अगर (objs[i]->size < min_size) अणु
			drm_gem_object_put(objs[i]);
			ret = -EINVAL;
			जाओ err_gem_object_put;
		पूर्ण
	पूर्ण

	ret = drm_gem_fb_init(dev, fb, mode_cmd, objs, i, funcs);
	अगर (ret)
		जाओ err_gem_object_put;

	वापस 0;

err_gem_object_put:
	क्रम (i--; i >= 0; i--)
		drm_gem_object_put(objs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_init_with_funcs);

/**
 * drm_gem_fb_create_with_funcs() - Helper function क्रम the
 *                                  &drm_mode_config_funcs.fb_create
 *                                  callback
 * @dev: DRM device
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 * @funcs: vtable to be used क्रम the new framebuffer object
 *
 * This function can be used to set &drm_framebuffer_funcs क्रम drivers that need
 * custom framebuffer callbacks. Use drm_gem_fb_create() अगर you करोn't need to
 * change &drm_framebuffer_funcs. The function करोes buffer size validation.
 *
 * Returns:
 * Poपूर्णांकer to a &drm_framebuffer on success or an error poपूर्णांकer on failure.
 */
काष्ठा drm_framebuffer *
drm_gem_fb_create_with_funcs(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			     स्थिर काष्ठा drm_framebuffer_funcs *funcs)
अणु
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb)
		वापस ERR_PTR(-ENOMEM);

	ret = drm_gem_fb_init_with_funcs(dev, fb, file, mode_cmd, funcs);
	अगर (ret) अणु
		kमुक्त(fb);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस fb;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_create_with_funcs);

अटल स्थिर काष्ठा drm_framebuffer_funcs drm_gem_fb_funcs = अणु
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
पूर्ण;

/**
 * drm_gem_fb_create() - Helper function क्रम the
 *                       &drm_mode_config_funcs.fb_create callback
 * @dev: DRM device
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 *
 * This function creates a new framebuffer object described by
 * &drm_mode_fb_cmd2. This description includes handles क्रम the buffer(s)
 * backing the framebuffer.
 *
 * If your hardware has special alignment or pitch requirements these should be
 * checked beक्रमe calling this function. The function करोes buffer size
 * validation. Use drm_gem_fb_create_with_dirty() अगर you need framebuffer
 * flushing.
 *
 * Drivers can use this as their &drm_mode_config_funcs.fb_create callback.
 * The ADDFB2 IOCTL calls पूर्णांकo this callback.
 *
 * Returns:
 * Poपूर्णांकer to a &drm_framebuffer on success or an error poपूर्णांकer on failure.
 */
काष्ठा drm_framebuffer *
drm_gem_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	वापस drm_gem_fb_create_with_funcs(dev, file, mode_cmd,
					    &drm_gem_fb_funcs);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_create);

अटल स्थिर काष्ठा drm_framebuffer_funcs drm_gem_fb_funcs_dirtyfb = अणु
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
	.dirty		= drm_atomic_helper_dirtyfb,
पूर्ण;

/**
 * drm_gem_fb_create_with_dirty() - Helper function क्रम the
 *                       &drm_mode_config_funcs.fb_create callback
 * @dev: DRM device
 * @file: DRM file that holds the GEM handle(s) backing the framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 *
 * This function creates a new framebuffer object described by
 * &drm_mode_fb_cmd2. This description includes handles क्रम the buffer(s)
 * backing the framebuffer. drm_atomic_helper_dirtyfb() is used क्रम the dirty
 * callback giving framebuffer flushing through the atomic machinery. Use
 * drm_gem_fb_create() अगर you करोn't need the dirty callback.
 * The function करोes buffer size validation.
 *
 * Drivers should also call drm_plane_enable_fb_damage_clips() on all planes
 * to enable userspace to use damage clips also with the ATOMIC IOCTL.
 *
 * Drivers can use this as their &drm_mode_config_funcs.fb_create callback.
 * The ADDFB2 IOCTL calls पूर्णांकo this callback.
 *
 * Returns:
 * Poपूर्णांकer to a &drm_framebuffer on success or an error poपूर्णांकer on failure.
 */
काष्ठा drm_framebuffer *
drm_gem_fb_create_with_dirty(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	वापस drm_gem_fb_create_with_funcs(dev, file, mode_cmd,
					    &drm_gem_fb_funcs_dirtyfb);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_create_with_dirty);

अटल __u32 drm_gem_afbc_get_bpp(काष्ठा drm_device *dev,
				  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;

	info = drm_get_क्रमmat_info(dev, mode_cmd);

	/* use whatever a driver has set */
	अगर (info->cpp[0])
		वापस info->cpp[0] * 8;

	/* guess otherwise */
	चयन (info->क्रमmat) अणु
	हाल DRM_FORMAT_YUV420_8BIT:
		वापस 12;
	हाल DRM_FORMAT_YUV420_10BIT:
		वापस 15;
	हाल DRM_FORMAT_VUY101010:
		वापस 30;
	शेष:
		अवरोध;
	पूर्ण

	/* all attempts failed */
	वापस 0;
पूर्ण

अटल पूर्णांक drm_gem_afbc_min_size(काष्ठा drm_device *dev,
				 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
				 काष्ठा drm_afbc_framebuffer *afbc_fb)
अणु
	__u32 n_blocks, w_alignment, h_alignment, hdr_alignment;
	/* हटाओ bpp when all users properly encode cpp in drm_क्रमmat_info */
	__u32 bpp;

	चयन (mode_cmd->modअगरier[0] & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) अणु
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_16x16:
		afbc_fb->block_width = 16;
		afbc_fb->block_height = 16;
		अवरोध;
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_32x8:
		afbc_fb->block_width = 32;
		afbc_fb->block_height = 8;
		अवरोध;
	/* no user exists yet - fall through */
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_64x4:
	हाल AFBC_FORMAT_MOD_BLOCK_SIZE_32x8_64x4:
	शेष:
		drm_dbg_kms(dev, "Invalid AFBC_FORMAT_MOD_BLOCK_SIZE: %lld.\n",
			    mode_cmd->modअगरier[0]
			    & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK);
		वापस -EINVAL;
	पूर्ण

	/* tiled header afbc */
	w_alignment = afbc_fb->block_width;
	h_alignment = afbc_fb->block_height;
	hdr_alignment = AFBC_HDR_ALIGN;
	अगर (mode_cmd->modअगरier[0] & AFBC_FORMAT_MOD_TILED) अणु
		w_alignment *= AFBC_TH_LAYOUT_ALIGNMENT;
		h_alignment *= AFBC_TH_LAYOUT_ALIGNMENT;
		hdr_alignment = AFBC_TH_BODY_START_ALIGNMENT;
	पूर्ण

	afbc_fb->aligned_width = ALIGN(mode_cmd->width, w_alignment);
	afbc_fb->aligned_height = ALIGN(mode_cmd->height, h_alignment);
	afbc_fb->offset = mode_cmd->offsets[0];

	bpp = drm_gem_afbc_get_bpp(dev, mode_cmd);
	अगर (!bpp) अणु
		drm_dbg_kms(dev, "Invalid AFBC bpp value: %d\n", bpp);
		वापस -EINVAL;
	पूर्ण

	n_blocks = (afbc_fb->aligned_width * afbc_fb->aligned_height)
		   / AFBC_SUPERBLOCK_PIXELS;
	afbc_fb->afbc_size = ALIGN(n_blocks * AFBC_HEADER_SIZE, hdr_alignment);
	afbc_fb->afbc_size += n_blocks * ALIGN(bpp * AFBC_SUPERBLOCK_PIXELS / 8,
					       AFBC_SUPERBLOCK_ALIGNMENT);

	वापस 0;
पूर्ण

/**
 * drm_gem_fb_afbc_init() - Helper function क्रम drivers using afbc to
 *			    fill and validate all the afbc-specअगरic
 *			    काष्ठा drm_afbc_framebuffer members
 *
 * @dev: DRM device
 * @afbc_fb: afbc-specअगरic framebuffer
 * @mode_cmd: Metadata from the userspace framebuffer creation request
 * @afbc_fb: afbc framebuffer
 *
 * This function can be used by drivers which support afbc to complete
 * the preparation of काष्ठा drm_afbc_framebuffer. It must be called after
 * allocating the said काष्ठा and calling drm_gem_fb_init_with_funcs().
 * It is caller's responsibility to put afbc_fb->base.obj objects in हाल
 * the call is unsuccessful.
 *
 * Returns:
 * Zero on success or a negative error value on failure.
 */
पूर्णांक drm_gem_fb_afbc_init(काष्ठा drm_device *dev,
			 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			 काष्ठा drm_afbc_framebuffer *afbc_fb)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	काष्ठा drm_gem_object **objs;
	पूर्णांक ret;

	objs = afbc_fb->base.obj;
	info = drm_get_क्रमmat_info(dev, mode_cmd);
	अगर (!info)
		वापस -EINVAL;

	ret = drm_gem_afbc_min_size(dev, mode_cmd, afbc_fb);
	अगर (ret < 0)
		वापस ret;

	अगर (objs[0]->size < afbc_fb->afbc_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_fb_afbc_init);
