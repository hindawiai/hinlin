<शैली गुरु>
/*
 * Copyright 2009 Ben Skeggs
 * Copyright 2008 Stuart Bennett
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#घोषणा NVIF_DEBUG_PRINT_DISABLE
#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_fbcon.h"

#समावेश <nvअगर/push006c.h>

पूर्णांक
nv04_fbcon_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा nouveau_fbdev *nfbdev = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(nfbdev->helper.dev);
	काष्ठा nouveau_channel *chan = drm->channel;
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 4);
	अगर (ret)
		वापस ret;

	PUSH_NVSQ(push, NV05F, 0x0300, (region->sy << 16) | region->sx,
			       0x0304, (region->dy << 16) | region->dx,
			       0x0308, (region->height << 16) | region->width);
	PUSH_KICK(push);
	वापस 0;
पूर्ण

पूर्णांक
nv04_fbcon_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा nouveau_fbdev *nfbdev = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(nfbdev->helper.dev);
	काष्ठा nouveau_channel *chan = drm->channel;
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 7);
	अगर (ret)
		वापस ret;

	PUSH_NVSQ(push, NV04A, 0x02fc, (rect->rop != ROP_COPY) ? 1 : 3);
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_सूचीECTCOLOR)
		PUSH_NVSQ(push, NV04A, 0x03fc, ((uपूर्णांक32_t *)info->pseuकरो_palette)[rect->color]);
	अन्यथा
		PUSH_NVSQ(push, NV04A, 0x03fc, rect->color);
	PUSH_NVSQ(push, NV04A, 0x0400, (rect->dx << 16) | rect->dy,
			       0x0404, (rect->width << 16) | rect->height);
	PUSH_KICK(push);
	वापस 0;
पूर्ण

पूर्णांक
nv04_fbcon_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा nouveau_fbdev *nfbdev = info->par;
	काष्ठा nouveau_drm *drm = nouveau_drm(nfbdev->helper.dev);
	काष्ठा nouveau_channel *chan = drm->channel;
	काष्ठा nvअगर_push *push = chan->chan.push;
	uपूर्णांक32_t fg;
	uपूर्णांक32_t bg;
	uपूर्णांक32_t dsize;
	uपूर्णांक32_t *data = (uपूर्णांक32_t *)image->data;
	पूर्णांक ret;

	अगर (image->depth != 1)
		वापस -ENODEV;

	ret = PUSH_WAIT(push, 8);
	अगर (ret)
		वापस ret;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		fg = ((uपूर्णांक32_t *) info->pseuकरो_palette)[image->fg_color];
		bg = ((uपूर्णांक32_t *) info->pseuकरो_palette)[image->bg_color];
	पूर्ण अन्यथा अणु
		fg = image->fg_color;
		bg = image->bg_color;
	पूर्ण

	PUSH_NVSQ(push, NV04A, 0x0be4, (image->dy << 16) | (image->dx & 0xffff),
			       0x0be8, ((image->dy + image->height) << 16) |
				       ((image->dx + image->width) & 0xffff),
			       0x0bec, bg,
			       0x0bf0, fg,
			       0x0bf4, (image->height << 16) | ALIGN(image->width, 8),
			       0x0bf8, (image->height << 16) | image->width,
			       0x0bfc, (image->dy << 16) | (image->dx & 0xffff));

	dsize = ALIGN(ALIGN(image->width, 8) * image->height, 32) >> 5;
	जबतक (dsize) अणु
		पूर्णांक iter_len = dsize > 128 ? 128 : dsize;

		ret = PUSH_WAIT(push, iter_len + 1);
		अगर (ret)
			वापस ret;

		PUSH_NVSQ(push, NV04A, 0x0c00, data, iter_len);
		data += iter_len;
		dsize -= iter_len;
	पूर्ण

	PUSH_KICK(push);
	वापस 0;
पूर्ण

पूर्णांक
nv04_fbcon_accel_init(काष्ठा fb_info *info)
अणु
	काष्ठा nouveau_fbdev *nfbdev = info->par;
	काष्ठा drm_device *dev = nfbdev->helper.dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_channel *chan = drm->channel;
	काष्ठा nvअगर_device *device = &drm->client.device;
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक surface_fmt, pattern_fmt, rect_fmt;
	पूर्णांक ret;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		surface_fmt = 1;
		pattern_fmt = 3;
		rect_fmt = 3;
		अवरोध;
	हाल 16:
		surface_fmt = 4;
		pattern_fmt = 1;
		rect_fmt = 1;
		अवरोध;
	हाल 32:
		चयन (info->var.transp.length) अणु
		हाल 0: /* depth 24 */
		हाल 8: /* depth 32 */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		surface_fmt = 6;
		pattern_fmt = 3;
		rect_fmt = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = nvअगर_object_ctor(&chan->user, "fbconCtxSurf2d", 0x0062,
			       device->info.family >= NV_DEVICE_INFO_V0_CELSIUS ?
			       0x0062 : 0x0042, शून्य, 0, &nfbdev->surf2d);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&chan->user, "fbconCtxClip", 0x0019, 0x0019,
			       शून्य, 0, &nfbdev->clip);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&chan->user, "fbconCtxRop", 0x0043, 0x0043,
			       शून्य, 0, &nfbdev->rop);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&chan->user, "fbconCtxPatt", 0x0044, 0x0044,
			       शून्य, 0, &nfbdev->patt);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&chan->user, "fbconGdiRectText", 0x004a, 0x004a,
			       शून्य, 0, &nfbdev->gdi);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&chan->user, "fbconImageBlit", 0x005f,
			       device->info.chipset >= 0x11 ? 0x009f : 0x005f,
			       शून्य, 0, &nfbdev->blit);
	अगर (ret)
		वापस ret;

	अगर (PUSH_WAIT(push, 49 + (device->info.chipset >= 0x11 ? 4 : 0))) अणु
		nouveau_fbcon_gpu_lockup(info);
		वापस 0;
	पूर्ण

	PUSH_NVSQ(push, NV042, 0x0000, nfbdev->surf2d.handle);
	PUSH_NVSQ(push, NV042, 0x0184, chan->vram.handle,
			       0x0188, chan->vram.handle);
	PUSH_NVSQ(push, NV042, 0x0300, surface_fmt,
			       0x0304, info->fix.line_length | (info->fix.line_length << 16),
			       0x0308, info->fix.smem_start - dev->mode_config.fb_base,
			       0x030c, info->fix.smem_start - dev->mode_config.fb_base);

	PUSH_NVSQ(push, NV043, 0x0000, nfbdev->rop.handle);
	PUSH_NVSQ(push, NV043, 0x0300, 0x55);

	PUSH_NVSQ(push, NV044, 0x0000, nfbdev->patt.handle);
	PUSH_NVSQ(push, NV044, 0x0300, pattern_fmt,
#अगर_घोषित __BIG_ENDIAN
			       0x0304, 2,
#अन्यथा
			       0x0304, 1,
#पूर्ण_अगर
			       0x0308, 0,
			       0x030c, 1,
			       0x0310, ~0,
			       0x0314, ~0,
			       0x0318, ~0,
			       0x031c, ~0);

	PUSH_NVSQ(push, NV019, 0x0000, nfbdev->clip.handle);
	PUSH_NVSQ(push, NV019, 0x0300, 0,
			       0x0304, (info->var.yres_भव << 16) | info->var.xres_भव);

	PUSH_NVSQ(push, NV05F, 0x0000, nfbdev->blit.handle);
	PUSH_NVSQ(push, NV05F, 0x019c, nfbdev->surf2d.handle);
	PUSH_NVSQ(push, NV05F, 0x02fc, 3);
	अगर (nfbdev->blit.oclass == 0x009f) अणु
		PUSH_NVSQ(push, NV09F, 0x0120, 0,
				       0x0124, 1,
				       0x0128, 2);
	पूर्ण

	PUSH_NVSQ(push, NV04A, 0x0000, nfbdev->gdi.handle);
	PUSH_NVSQ(push, NV04A, 0x0198, nfbdev->surf2d.handle);
	PUSH_NVSQ(push, NV04A, 0x0188, nfbdev->patt.handle,
			       0x018c, nfbdev->rop.handle);
	PUSH_NVSQ(push, NV04A, 0x0304, 1);
	PUSH_NVSQ(push, NV04A, 0x0300, rect_fmt);
	PUSH_NVSQ(push, NV04A, 0x02fc, 3);

	PUSH_KICK(push);
	वापस 0;
पूर्ण

