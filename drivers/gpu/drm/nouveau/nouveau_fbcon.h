<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NOUVEAU_FBCON_H__
#घोषणा __NOUVEAU_FBCON_H__

#समावेश <drm/drm_fb_helper.h>

#समावेश "nouveau_display.h"

काष्ठा nouveau_vma;

काष्ठा nouveau_fbdev अणु
	काष्ठा drm_fb_helper helper; /* must be first */
	अचिन्हित पूर्णांक saved_flags;
	काष्ठा nvअगर_object surf2d;
	काष्ठा nvअगर_object clip;
	काष्ठा nvअगर_object rop;
	काष्ठा nvअगर_object patt;
	काष्ठा nvअगर_object gdi;
	काष्ठा nvअगर_object blit;
	काष्ठा nvअगर_object twod;
	काष्ठा nouveau_vma *vma;

	काष्ठा mutex hotplug_lock;
	bool hotplug_रुकोing;
पूर्ण;

व्योम nouveau_fbcon_restore(व्योम);

पूर्णांक nv04_fbcon_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region);
पूर्णांक nv04_fbcon_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
पूर्णांक nv04_fbcon_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
पूर्णांक nv04_fbcon_accel_init(काष्ठा fb_info *info);

पूर्णांक nv50_fbcon_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
पूर्णांक nv50_fbcon_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region);
पूर्णांक nv50_fbcon_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
पूर्णांक nv50_fbcon_accel_init(काष्ठा fb_info *info);

पूर्णांक nvc0_fbcon_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
पूर्णांक nvc0_fbcon_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region);
पूर्णांक nvc0_fbcon_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
पूर्णांक nvc0_fbcon_accel_init(काष्ठा fb_info *info);

व्योम nouveau_fbcon_gpu_lockup(काष्ठा fb_info *info);

पूर्णांक nouveau_fbcon_init(काष्ठा drm_device *dev);
व्योम nouveau_fbcon_fini(काष्ठा drm_device *dev);
व्योम nouveau_fbcon_set_suspend(काष्ठा drm_device *dev, पूर्णांक state);
व्योम nouveau_fbcon_accel_save_disable(काष्ठा drm_device *dev);
व्योम nouveau_fbcon_accel_restore(काष्ठा drm_device *dev);

व्योम nouveau_fbcon_output_poll_changed(काष्ठा drm_device *dev);
व्योम nouveau_fbcon_hotplug_resume(काष्ठा nouveau_fbdev *fbcon);
बाह्य पूर्णांक nouveau_nofbaccel;

#पूर्ण_अगर /* __NV50_FBCON_H__ */

