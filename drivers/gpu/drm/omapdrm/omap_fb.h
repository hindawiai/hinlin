<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_fb.h -- OMAP DRM Framebuffer
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_FB_H__
#घोषणा __OMAPDRM_FB_H__

काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_framebuffer;
काष्ठा drm_gem_object;
काष्ठा drm_mode_fb_cmd2;
काष्ठा drm_plane_state;
काष्ठा omap_overlay_info;
काष्ठा seq_file;

काष्ठा drm_framebuffer *omap_framebuffer_create(काष्ठा drm_device *dev,
		काष्ठा drm_file *file, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
काष्ठा drm_framebuffer *omap_framebuffer_init(काष्ठा drm_device *dev,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd, काष्ठा drm_gem_object **bos);
पूर्णांक omap_framebuffer_pin(काष्ठा drm_framebuffer *fb);
व्योम omap_framebuffer_unpin(काष्ठा drm_framebuffer *fb);
व्योम omap_framebuffer_update_scanout(काष्ठा drm_framebuffer *fb,
		काष्ठा drm_plane_state *state, काष्ठा omap_overlay_info *info);
bool omap_framebuffer_supports_rotation(काष्ठा drm_framebuffer *fb);
व्योम omap_framebuffer_describe(काष्ठा drm_framebuffer *fb, काष्ठा seq_file *m);

#पूर्ण_अगर /* __OMAPDRM_FB_H__ */
