<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Noralf Trथचnnes
 */

#अगर_अघोषित __LINUX_DRM_FORMAT_HELPER_H
#घोषणा __LINUX_DRM_FORMAT_HELPER_H

काष्ठा drm_framebuffer;
काष्ठा drm_rect;

व्योम drm_fb_स_नकल(व्योम *dst, व्योम *vaddr, काष्ठा drm_framebuffer *fb,
		   काष्ठा drm_rect *clip);
व्योम drm_fb_स_नकल_dstclip(व्योम __iomem *dst, व्योम *vaddr,
			   काष्ठा drm_framebuffer *fb,
			   काष्ठा drm_rect *clip);
व्योम drm_fb_swab(व्योम *dst, व्योम *src, काष्ठा drm_framebuffer *fb,
		 काष्ठा drm_rect *clip, bool cached);
व्योम drm_fb_xrgb8888_to_rgb565(व्योम *dst, व्योम *vaddr,
			       काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_rect *clip, bool swab);
व्योम drm_fb_xrgb8888_to_rgb565_dstclip(व्योम __iomem *dst, अचिन्हित पूर्णांक dst_pitch,
				       व्योम *vaddr, काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_rect *clip, bool swab);
व्योम drm_fb_xrgb8888_to_rgb888_dstclip(व्योम __iomem *dst, अचिन्हित पूर्णांक dst_pitch,
				       व्योम *vaddr, काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_rect *clip);
व्योम drm_fb_xrgb8888_to_gray8(u8 *dst, व्योम *vaddr, काष्ठा drm_framebuffer *fb,
			      काष्ठा drm_rect *clip);

#पूर्ण_अगर /* __LINUX_DRM_FORMAT_HELPER_H */
