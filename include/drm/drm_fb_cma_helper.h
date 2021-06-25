<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRM_FB_CMA_HELPER_H__
#घोषणा __DRM_FB_CMA_HELPER_H__

#समावेश <linux/types.h>

काष्ठा drm_framebuffer;
काष्ठा drm_plane_state;

काष्ठा drm_gem_cma_object *drm_fb_cma_get_gem_obj(काष्ठा drm_framebuffer *fb,
	अचिन्हित पूर्णांक plane);

dma_addr_t drm_fb_cma_get_gem_addr(काष्ठा drm_framebuffer *fb,
				   काष्ठा drm_plane_state *state,
				   अचिन्हित पूर्णांक plane);

#पूर्ण_अगर

