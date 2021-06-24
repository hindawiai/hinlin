<शैली गुरु>
#अगर_अघोषित __DRM_GEM_FB_HELPER_H__
#घोषणा __DRM_GEM_FB_HELPER_H__

काष्ठा drm_afbc_framebuffer;
काष्ठा drm_device;
काष्ठा drm_fb_helper_surface_size;
काष्ठा drm_file;
काष्ठा drm_framebuffer;
काष्ठा drm_framebuffer_funcs;
काष्ठा drm_gem_object;
काष्ठा drm_mode_fb_cmd2;

#घोषणा AFBC_VENDOR_AND_TYPE_MASK	GENMASK_ULL(63, 52)

काष्ठा drm_gem_object *drm_gem_fb_get_obj(काष्ठा drm_framebuffer *fb,
					  अचिन्हित पूर्णांक plane);
व्योम drm_gem_fb_destroy(काष्ठा drm_framebuffer *fb);
पूर्णांक drm_gem_fb_create_handle(काष्ठा drm_framebuffer *fb, काष्ठा drm_file *file,
			     अचिन्हित पूर्णांक *handle);

पूर्णांक drm_gem_fb_init_with_funcs(काष्ठा drm_device *dev,
			       काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_file *file,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			       स्थिर काष्ठा drm_framebuffer_funcs *funcs);
काष्ठा drm_framebuffer *
drm_gem_fb_create_with_funcs(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			     स्थिर काष्ठा drm_framebuffer_funcs *funcs);
काष्ठा drm_framebuffer *
drm_gem_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
काष्ठा drm_framebuffer *
drm_gem_fb_create_with_dirty(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);

#घोषणा drm_is_afbc(modअगरier) \
	(((modअगरier) & AFBC_VENDOR_AND_TYPE_MASK) == DRM_FORMAT_MOD_ARM_AFBC(0))

पूर्णांक drm_gem_fb_afbc_init(काष्ठा drm_device *dev,
			 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			 काष्ठा drm_afbc_framebuffer *afbc_fb);

#पूर्ण_अगर
