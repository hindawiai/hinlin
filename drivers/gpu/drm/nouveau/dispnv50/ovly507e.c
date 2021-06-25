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

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश <nvअगर/cl507e.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl507e.h>

पूर्णांक
ovly507e_scale_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NV507E, SET_POINT_IN,
		  NVVAL(NV507E, SET_POINT_IN, X, asyw->scale.sx) |
		  NVVAL(NV507E, SET_POINT_IN, Y, asyw->scale.sy),

				SET_SIZE_IN,
		  NVVAL(NV507E, SET_SIZE_IN, WIDTH, asyw->scale.sw) |
		  NVVAL(NV507E, SET_SIZE_IN, HEIGHT, asyw->scale.sh),

				SET_SIZE_OUT,
		  NVVAL(NV507E, SET_SIZE_OUT, WIDTH, asyw->scale.dw));
	वापस 0;
पूर्ण

अटल पूर्णांक
ovly507e_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 12)))
		वापस ret;

	PUSH_MTHD(push, NV507E, SET_PRESENT_CONTROL,
		  NVDEF(NV507E, SET_PRESENT_CONTROL, BEGIN_MODE, ASAP) |
		  NVVAL(NV507E, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval));

	PUSH_MTHD(push, NV507E, SET_CONTEXT_DMA_ISO, asyw->image.handle[0]);

	PUSH_MTHD(push, NV507E, SET_COMPOSITION_CONTROL,
		  NVDEF(NV507E, SET_COMPOSITION_CONTROL, MODE, OPAQUE_SUSPEND_BASE));

	PUSH_MTHD(push, NV507E, SURFACE_SET_OFFSET, asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NV507E, SURFACE_SET_SIZE,
		  NVVAL(NV507E, SURFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NV507E, SURFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SURFACE_SET_STORAGE,
		  NVVAL(NV507E, SURFACE_SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh) |
		  NVVAL(NV507E, SURFACE_SET_STORAGE, PITCH, (asyw->image.pitch[0] >> 8)) |
		  NVVAL(NV507E, SURFACE_SET_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NV507E, SURFACE_SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout),

				SURFACE_SET_PARAMS,
		  NVVAL(NV507E, SURFACE_SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVVAL(NV507E, SURFACE_SET_PARAMS, COLOR_SPACE, asyw->image.colorspace) |
		  NVVAL(NV507E, SURFACE_SET_PARAMS, KIND, asyw->image.kind) |
		  NVDEF(NV507E, SURFACE_SET_PARAMS, PART_STRIDE, PARTSTRIDE_256));
	वापस 0;
पूर्ण

व्योम
ovly507e_release(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	asyh->ovly.cpp = 0;
पूर्ण

पूर्णांक
ovly507e_acquire(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = asyw->state.fb;
	पूर्णांक ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	अगर (ret)
		वापस ret;

	asyh->ovly.cpp = fb->क्रमmat->cpp[0];
	वापस 0;
पूर्ण

#समावेश "nouveau_bo.h"

अटल स्थिर काष्ठा nv50_wndw_func
ovly507e = अणु
	.acquire = ovly507e_acquire,
	.release = ovly507e_release,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_clr = base507c_ntfy_clr,
	.ntfy_reset = base507c_ntfy_reset,
	.ntfy_रुको_begun = base507c_ntfy_रुको_begun,
	.image_set = ovly507e_image_set,
	.image_clr = base507c_image_clr,
	.scale_set = ovly507e_scale_set,
	.update = base507c_update,
पूर्ण;

अटल स्थिर u32
ovly507e_क्रमmat[] = अणु
	DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XRGB1555,
	0
पूर्ण;

पूर्णांक
ovly507e_new_(स्थिर काष्ठा nv50_wndw_func *func, स्थिर u32 *क्रमmat,
	      काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass, u32 पूर्णांकerlock_data,
	      काष्ठा nv50_wndw **pwndw)
अणु
	काष्ठा nv50_disp_overlay_channel_dma_v0 args = अणु
		.head = head,
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	काष्ठा nv50_wndw *wndw;
	पूर्णांक ret;

	ret = nv50_wndw_new_(func, drm->dev, DRM_PLANE_TYPE_OVERLAY,
			     "ovly", head, क्रमmat, BIT(head),
			     NV50_DISP_INTERLOCK_OVLY, पूर्णांकerlock_data,
			     &wndw);
	अगर (*pwndw = wndw, ret)
		वापस ret;

	ret = nv50_dmac_create(&drm->client.device, &disp->disp->object,
			       &oclass, 0, &args, माप(args),
			       disp->sync->offset, &wndw->wndw);
	अगर (ret) अणु
		NV_ERROR(drm, "ovly%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	ret = nvअगर_notअगरy_ctor(&wndw->wndw.base.user, "kmsOvlyNtfy",
			       wndw->notअगरy.func, false,
			       NV50_DISP_OVERLAY_CHANNEL_DMA_V0_NTFY_UEVENT,
			       &(काष्ठा nvअगर_notअगरy_uevent_req) अणुपूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_uevent_req),
			       माप(काष्ठा nvअगर_notअगरy_uevent_rep),
			       &wndw->notअगरy);
	अगर (ret)
		वापस ret;

	wndw->ntfy = NV50_DISP_OVLY_NTFY(wndw->id);
	wndw->sema = NV50_DISP_OVLY_SEM0(wndw->id);
	wndw->data = 0x00000000;
	वापस 0;
पूर्ण

पूर्णांक
ovly507e_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस ovly507e_new_(&ovly507e, ovly507e_क्रमmat, drm, head, oclass,
			     0x00000004 << (head * 8), pwndw);
पूर्ण
