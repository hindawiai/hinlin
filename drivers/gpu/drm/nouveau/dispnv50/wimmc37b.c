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
#समावेश "wimm.h"
#समावेश "atom.h"
#समावेश "wndw.h"

#समावेश <nvअगर/clc37b.h>
#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc37b.h>

अटल पूर्णांक
wimmc37b_update(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock)
अणु
	काष्ठा nvअगर_push *push = wndw->wimm.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37B, UPDATE, 0x00000001 |
		  NVVAL(NVC37B, UPDATE, INTERLOCK_WITH_WINDOW,
			!!(पूर्णांकerlock[NV50_DISP_INTERLOCK_WNDW] & wndw->पूर्णांकerlock.data)));
	वापस PUSH_KICK(push);
पूर्ण

अटल पूर्णांक
wimmc37b_poपूर्णांक(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wimm.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37B, SET_POINT_OUT(0),
		  NVVAL(NVC37B, SET_POINT_OUT, X, asyw->poपूर्णांक.x) |
		  NVVAL(NVC37B, SET_POINT_OUT, Y, asyw->poपूर्णांक.y));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_wimm_func
wimmc37b = अणु
	.poपूर्णांक = wimmc37b_poपूर्णांक,
	.update = wimmc37b_update,
पूर्ण;

अटल पूर्णांक
wimmc37b_init_(स्थिर काष्ठा nv50_wimm_func *func, काष्ठा nouveau_drm *drm,
	       s32 oclass, काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvc37b_winकरोw_imm_channel_dma_v0 args = अणु
		.pushbuf = 0xb0007b00 | wndw->id,
		.index = wndw->id,
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक ret;

	ret = nv50_dmac_create(&drm->client.device, &disp->disp->object,
			       &oclass, 0, &args, माप(args), -1,
			       &wndw->wimm);
	अगर (ret) अणु
		NV_ERROR(drm, "wimm%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	wndw->पूर्णांकerlock.wimm = wndw->पूर्णांकerlock.data;
	wndw->immd = func;
	वापस 0;
पूर्ण

पूर्णांक
wimmc37b_init(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_wndw *wndw)
अणु
	वापस wimmc37b_init_(&wimmc37b, drm, oclass, wndw);
पूर्ण
