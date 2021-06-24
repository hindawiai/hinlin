<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#समावेश "ovly.h"
#समावेश "atom.h"

#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl907e.h>

अटल पूर्णांक
ovly907e_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 12)))
		वापस ret;

	PUSH_MTHD(push, NV907E, SET_PRESENT_CONTROL,
		  NVDEF(NV907E, SET_PRESENT_CONTROL, BEGIN_MODE, ASAP) |
		  NVVAL(NV907E, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval));

	PUSH_MTHD(push, NV907E, SET_CONTEXT_DMA_ISO, asyw->image.handle[0]);

	PUSH_MTHD(push, NV907E, SET_COMPOSITION_CONTROL,
		  NVDEF(NV907E, SET_COMPOSITION_CONTROL, MODE, OPAQUE));

	PUSH_MTHD(push, NV907E, SURFACE_SET_OFFSET, asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NV907E, SURFACE_SET_SIZE,
		  NVVAL(NV907E, SURFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NV907E, SURFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SURFACE_SET_STORAGE,
		  NVVAL(NV907E, SURFACE_SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh) |
		  NVVAL(NV907E, SURFACE_SET_STORAGE, PITCH, (asyw->image.pitch[0] >> 8)) |
		  NVVAL(NV907E, SURFACE_SET_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NV907E, SURFACE_SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout),

				SURFACE_SET_PARAMS,
		  NVVAL(NV907E, SURFACE_SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVVAL(NV907E, SURFACE_SET_PARAMS, COLOR_SPACE, asyw->image.colorspace));
	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_wndw_func
ovly907e = अणु
	.acquire = ovly507e_acquire,
	.release = ovly507e_release,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_clr = base507c_ntfy_clr,
	.ntfy_reset = ovly827e_ntfy_reset,
	.ntfy_रुको_begun = ovly827e_ntfy_रुको_begun,
	.image_set = ovly907e_image_set,
	.image_clr = base507c_image_clr,
	.scale_set = ovly507e_scale_set,
	.update = base507c_update,
पूर्ण;

अटल स्थिर u32
ovly907e_क्रमmat[] = अणु
	DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XBGR16161616F,
	0
पूर्ण;

पूर्णांक
ovly907e_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस ovly507e_new_(&ovly907e, ovly907e_क्रमmat, drm, head, oclass,
			     0x00000004 << (head * 4), pwndw);
पूर्ण
