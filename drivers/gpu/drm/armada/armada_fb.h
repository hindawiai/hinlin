<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Russell King
 */
#अगर_अघोषित ARMADA_FB_H
#घोषणा ARMADA_FB_H

काष्ठा armada_framebuffer अणु
	काष्ठा drm_framebuffer	fb;
	uपूर्णांक8_t			fmt;
	uपूर्णांक8_t			mod;
पूर्ण;
#घोषणा drm_fb_to_armada_fb(dfb) \
	container_of(dfb, काष्ठा armada_framebuffer, fb)
#घोषणा drm_fb_obj(fb) drm_to_armada_gem((fb)->obj[0])

काष्ठा armada_framebuffer *armada_framebuffer_create(काष्ठा drm_device *,
	स्थिर काष्ठा drm_mode_fb_cmd2 *, काष्ठा armada_gem_object *);
काष्ठा drm_framebuffer *armada_fb_create(काष्ठा drm_device *dev,
	काष्ठा drm_file *dfile, स्थिर काष्ठा drm_mode_fb_cmd2 *mode);
#पूर्ण_अगर
