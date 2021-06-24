<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#अगर_अघोषित _ROCKCHIP_DRM_FB_H
#घोषणा _ROCKCHIP_DRM_FB_H

काष्ठा drm_framebuffer *
rockchip_drm_framebuffer_init(काष्ठा drm_device *dev,
			      स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			      काष्ठा drm_gem_object *obj);
व्योम rockchip_drm_framebuffer_fini(काष्ठा drm_framebuffer *fb);

व्योम rockchip_drm_mode_config_init(काष्ठा drm_device *dev);
#पूर्ण_अगर /* _ROCKCHIP_DRM_FB_H */
