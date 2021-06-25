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
#समावेश "base.h"

#समावेश <nvअगर/cl507c.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/push507c.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl507c.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "nouveau_bo.h"

पूर्णांक
base507c_update(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507C, UPDATE, पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE]);
	वापस PUSH_KICK(push);
पूर्ण

पूर्णांक
base507c_image_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_PRESENT_CONTROL,
		  NVDEF(NV507C, SET_PRESENT_CONTROL, BEGIN_MODE, NON_TEARING) |
		  NVVAL(NV507C, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, 0));

	PUSH_MTHD(push, NV507C, SET_CONTEXT_DMA_ISO, 0x00000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
base507c_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 13)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_PRESENT_CONTROL,
		  NVVAL(NV507C, SET_PRESENT_CONTROL, BEGIN_MODE, asyw->image.mode) |
		  NVVAL(NV507C, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval));

	PUSH_MTHD(push, NV507C, SET_CONTEXT_DMA_ISO, asyw->image.handle[0]);

	अगर (asyw->image.क्रमmat == NV507C_SURFACE_SET_PARAMS_FORMAT_RF16_GF16_BF16_AF16) अणु
		PUSH_MTHD(push, NV507C, SET_PROCESSING,
			  NVDEF(NV507C, SET_PROCESSING, USE_GAIN_OFS, ENABLE),

					SET_CONVERSION,
			  NVVAL(NV507C, SET_CONVERSION, GAIN, 0) |
			  NVVAL(NV507C, SET_CONVERSION, OFS, 0x64));
	पूर्ण अन्यथा अणु
		PUSH_MTHD(push, NV507C, SET_PROCESSING,
			  NVDEF(NV507C, SET_PROCESSING, USE_GAIN_OFS, DISABLE),

					SET_CONVERSION,
			  NVVAL(NV507C, SET_CONVERSION, GAIN, 0) |
			  NVVAL(NV507C, SET_CONVERSION, OFS, 0));
	पूर्ण

	PUSH_MTHD(push, NV507C, SURFACE_SET_OFFSET(0, 0), asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NV507C, SURFACE_SET_SIZE(0),
		  NVVAL(NV507C, SURFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NV507C, SURFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SURFACE_SET_STORAGE(0),
		  NVVAL(NV507C, SURFACE_SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout) |
		  NVVAL(NV507C, SURFACE_SET_STORAGE, PITCH, asyw->image.pitch[0] >> 8) |
		  NVVAL(NV507C, SURFACE_SET_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NV507C, SURFACE_SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh),

				SURFACE_SET_PARAMS(0),
		  NVVAL(NV507C, SURFACE_SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVDEF(NV507C, SURFACE_SET_PARAMS, SUPER_SAMPLE, X1_AA) |
		  NVDEF(NV507C, SURFACE_SET_PARAMS, GAMMA, LINEAR) |
		  NVDEF(NV507C, SURFACE_SET_PARAMS, LAYOUT, FRM) |
		  NVVAL(NV507C, SURFACE_SET_PARAMS, KIND, asyw->image.kind) |
		  NVDEF(NV507C, SURFACE_SET_PARAMS, PART_STRIDE, PARTSTRIDE_256));
	वापस 0;
पूर्ण

पूर्णांक
base507c_xlut_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_BASE_LUT_LO,
		  NVDEF(NV507C, SET_BASE_LUT_LO, ENABLE, DISABLE));
	वापस 0;
पूर्ण

पूर्णांक
base507c_xlut_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_BASE_LUT_LO,
		  NVDEF(NV507C, SET_BASE_LUT_LO, ENABLE, USE_CORE_LUT));
	वापस 0;
पूर्ण

पूर्णांक
base507c_ntfy_रुको_begun(काष्ठा nouveau_bo *bo, u32 offset,
			 काष्ठा nvअगर_device *device)
अणु
	s64 समय = nvअगर_msec(device, 2000ULL,
		अगर (NVBO_TD32(bo, offset, NV_DISP_BASE_NOTIFIER_1, _0, STATUS, ==, BEGUN))
			अवरोध;
		usleep_range(1, 2);
	);
	वापस समय < 0 ? समय : 0;
पूर्ण

पूर्णांक
base507c_ntfy_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_CONTEXT_DMA_NOTIFIER, 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
base507c_ntfy_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 3)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_NOTIFIER_CONTROL,
		  NVVAL(NV507C, SET_NOTIFIER_CONTROL, MODE, asyw->ntfy.awaken) |
		  NVVAL(NV507C, SET_NOTIFIER_CONTROL, OFFSET, asyw->ntfy.offset >> 2),

				SET_CONTEXT_DMA_NOTIFIER, asyw->ntfy.handle);
	वापस 0;
पूर्ण

व्योम
base507c_ntfy_reset(काष्ठा nouveau_bo *bo, u32 offset)
अणु
	NVBO_WR32(bo, offset, NV_DISP_BASE_NOTIFIER_1, _0,
			NVDEF(NV_DISP_BASE_NOTIFIER_1, _0, STATUS, NOT_BEGUN));
पूर्ण

पूर्णांक
base507c_sema_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_CONTEXT_DMA_SEMAPHORE, 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
base507c_sema_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 5)))
		वापस ret;

	PUSH_MTHD(push, NV507C, SET_SEMAPHORE_CONTROL, asyw->sema.offset,
				SET_SEMAPHORE_ACQUIRE, asyw->sema.acquire,
				SET_SEMAPHORE_RELEASE, asyw->sema.release,
				SET_CONTEXT_DMA_SEMAPHORE, asyw->sema.handle);
	वापस 0;
पूर्ण

व्योम
base507c_release(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	asyh->base.cpp = 0;
पूर्ण

पूर्णांक
base507c_acquire(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = asyw->state.fb;
	पूर्णांक ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);
	अगर (ret)
		वापस ret;

	अगर (!wndw->func->ilut) अणु
		अगर ((asyh->base.cpp != 1) ^ (fb->क्रमmat->cpp[0] != 1))
			asyh->state.color_mgmt_changed = true;
	पूर्ण

	asyh->base.depth = fb->क्रमmat->depth;
	asyh->base.cpp = fb->क्रमmat->cpp[0];
	asyh->base.x = asyw->state.src.x1 >> 16;
	asyh->base.y = asyw->state.src.y1 >> 16;
	asyh->base.w = asyw->state.fb->width;
	asyh->base.h = asyw->state.fb->height;

	/* Some newer क्रमmats, esp FP16 ones, करोn't have a
	 * "depth". There's nothing that really makes sense there
	 * either, so just set it to the implicit bit count.
	 */
	अगर (!asyh->base.depth)
		asyh->base.depth = asyh->base.cpp * 8;

	वापस 0;
पूर्ण

स्थिर u32
base507c_क्रमmat[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_ABGR16161616F,
	0
पूर्ण;

अटल स्थिर काष्ठा nv50_wndw_func
base507c = अणु
	.acquire = base507c_acquire,
	.release = base507c_release,
	.sema_set = base507c_sema_set,
	.sema_clr = base507c_sema_clr,
	.ntfy_reset = base507c_ntfy_reset,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_clr = base507c_ntfy_clr,
	.ntfy_रुको_begun = base507c_ntfy_रुको_begun,
	.olut_core = 1,
	.xlut_set = base507c_xlut_set,
	.xlut_clr = base507c_xlut_clr,
	.image_set = base507c_image_set,
	.image_clr = base507c_image_clr,
	.update = base507c_update,
पूर्ण;

पूर्णांक
base507c_new_(स्थिर काष्ठा nv50_wndw_func *func, स्थिर u32 *क्रमmat,
	      काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass, u32 पूर्णांकerlock_data,
	      काष्ठा nv50_wndw **pwndw)
अणु
	काष्ठा nv50_disp_base_channel_dma_v0 args = अणु
		.head = head,
	पूर्ण;
	काष्ठा nouveau_display *disp = nouveau_display(drm->dev);
	काष्ठा nv50_disp *disp50 = nv50_disp(drm->dev);
	काष्ठा nv50_wndw *wndw;
	पूर्णांक ret;

	ret = nv50_wndw_new_(func, drm->dev, DRM_PLANE_TYPE_PRIMARY,
			     "base", head, क्रमmat, BIT(head),
			     NV50_DISP_INTERLOCK_BASE, पूर्णांकerlock_data, &wndw);
	अगर (*pwndw = wndw, ret)
		वापस ret;

	ret = nv50_dmac_create(&drm->client.device, &disp->disp.object,
			       &oclass, head, &args, माप(args),
			       disp50->sync->offset, &wndw->wndw);
	अगर (ret) अणु
		NV_ERROR(drm, "base%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	ret = nvअगर_notअगरy_ctor(&wndw->wndw.base.user, "kmsBaseNtfy",
			       wndw->notअगरy.func, false,
			       NV50_DISP_BASE_CHANNEL_DMA_V0_NTFY_UEVENT,
			       &(काष्ठा nvअगर_notअगरy_uevent_req) अणुपूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_uevent_req),
			       माप(काष्ठा nvअगर_notअगरy_uevent_rep),
			       &wndw->notअगरy);
	अगर (ret)
		वापस ret;

	wndw->ntfy = NV50_DISP_BASE_NTFY(wndw->id);
	wndw->sema = NV50_DISP_BASE_SEM0(wndw->id);
	wndw->data = 0x00000000;
	वापस 0;
पूर्ण

पूर्णांक
base507c_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस base507c_new_(&base507c, base507c_क्रमmat, drm, head, oclass,
			     0x00000002 << (head * 8), pwndw);
पूर्ण
