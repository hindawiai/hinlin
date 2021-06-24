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
#समावेश "curs.h"
#समावेश "core.h"
#समावेश "head.h"

#समावेश <nvअगर/cl507a.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl507a.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

bool
curs507a_space(काष्ठा nv50_wndw *wndw)
अणु
	nvअगर_msec(&nouveau_drm(wndw->plane.dev)->client.device, 100,
		अगर (NVIF_TV32(&wndw->wimm.base.user, NV507A, FREE, COUNT, >=, 4))
			वापस true;
	);

	WARN_ON(1);
	वापस false;
पूर्ण

अटल पूर्णांक
curs507a_update(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock)
अणु
	काष्ठा nvअगर_object *user = &wndw->wimm.base.user;
	पूर्णांक ret = nvअगर_chan_रुको(&wndw->wimm, 1);
	अगर (ret == 0) अणु
		NVIF_WR32(user, NV507A, UPDATE,
			  NVDEF(NV507A, UPDATE, INTERLOCK_WITH_CORE, DISABLE));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
curs507a_poपूर्णांक(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_object *user = &wndw->wimm.base.user;
	पूर्णांक ret = nvअगर_chan_रुको(&wndw->wimm, 1);
	अगर (ret == 0) अणु
		NVIF_WR32(user, NV507A, SET_CURSOR_HOT_SPOT_POINT_OUT,
			  NVVAL(NV507A, SET_CURSOR_HOT_SPOT_POINT_OUT, X, asyw->poपूर्णांक.x) |
			  NVVAL(NV507A, SET_CURSOR_HOT_SPOT_POINT_OUT, Y, asyw->poपूर्णांक.y));
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nv50_wimm_func
curs507a = अणु
	.poपूर्णांक = curs507a_poपूर्णांक,
	.update = curs507a_update,
पूर्ण;

अटल व्योम
curs507a_prepare(काष्ठा nv50_wndw *wndw, काष्ठा nv50_head_atom *asyh,
		 काष्ठा nv50_wndw_atom *asyw)
अणु
	u32 handle = nv50_disp(wndw->plane.dev)->core->chan.vram.handle;
	u32 offset = asyw->image.offset[0];
	अगर (asyh->curs.handle != handle || asyh->curs.offset != offset) अणु
		asyh->curs.handle = handle;
		asyh->curs.offset = offset;
		asyh->set.curs = asyh->curs.visible;
	पूर्ण
पूर्ण

अटल व्योम
curs507a_release(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	asyh->curs.visible = false;
पूर्ण

अटल पूर्णांक
curs507a_acquire(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
		 काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nv50_head *head = nv50_head(asyw->state.crtc);
	पूर्णांक ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	asyh->curs.visible = asyw->state.visible;
	अगर (ret || !asyh->curs.visible)
		वापस ret;

	अगर (asyw->image.w != asyw->image.h)
		वापस -EINVAL;

	ret = head->func->curs_layout(head, asyw, asyh);
	अगर (ret)
		वापस ret;

	वापस head->func->curs_क्रमmat(head, asyw, asyh);
पूर्ण

अटल स्थिर u32
curs507a_क्रमmat[] = अणु
	DRM_FORMAT_ARGB8888,
	0
पूर्ण;

अटल स्थिर काष्ठा nv50_wndw_func
curs507a_wndw = अणु
	.acquire = curs507a_acquire,
	.release = curs507a_release,
	.prepare = curs507a_prepare,
पूर्ण;

पूर्णांक
curs507a_new_(स्थिर काष्ठा nv50_wimm_func *func, काष्ठा nouveau_drm *drm,
	      पूर्णांक head, s32 oclass, u32 पूर्णांकerlock_data,
	      काष्ठा nv50_wndw **pwndw)
अणु
	काष्ठा nv50_disp_cursor_v0 args = अणु
		.head = head,
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	काष्ठा nv50_wndw *wndw;
	पूर्णांक ret;

	ret = nv50_wndw_new_(&curs507a_wndw, drm->dev, DRM_PLANE_TYPE_CURSOR,
			     "curs", head, curs507a_क्रमmat, BIT(head),
			     NV50_DISP_INTERLOCK_CURS, पूर्णांकerlock_data, &wndw);
	अगर (*pwndw = wndw, ret)
		वापस ret;

	ret = nvअगर_object_ctor(&disp->disp->object, "kmsCurs", 0, oclass,
			       &args, माप(args), &wndw->wimm.base.user);
	अगर (ret) अणु
		NV_ERROR(drm, "curs%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	nvअगर_object_map(&wndw->wimm.base.user, शून्य, 0);
	wndw->immd = func;
	wndw->ctxdma.parent = शून्य;
	वापस 0;
पूर्ण

पूर्णांक
curs507a_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस curs507a_new_(&curs507a, drm, head, oclass,
			     0x00000001 << (head * 8), pwndw);
पूर्ण
