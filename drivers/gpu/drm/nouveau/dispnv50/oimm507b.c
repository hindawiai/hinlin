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
#समावेश "oimm.h"

#समावेश <nvअगर/cl507b.h>

अटल पूर्णांक
oimm507b_init_(स्थिर काष्ठा nv50_wimm_func *func, काष्ठा nouveau_drm *drm,
	       s32 oclass, काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nv50_disp_overlay_v0 args = अणु
		.head = wndw->id,
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक ret;

	ret = nvअगर_object_ctor(&disp->disp->object, "kmsOvim", 0, oclass,
			       &args, माप(args), &wndw->wimm.base.user);
	अगर (ret) अणु
		NV_ERROR(drm, "oimm%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	nvअगर_object_map(&wndw->wimm.base.user, शून्य, 0);
	wndw->immd = func;
	वापस 0;
पूर्ण

पूर्णांक
oimm507b_init(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_wndw *wndw)
अणु
	वापस oimm507b_init_(&curs507a, drm, oclass, wndw);
पूर्ण
