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

#समावेश <nvअगर/class.h>

पूर्णांक
nv50_oimm_init(काष्ठा nouveau_drm *drm, काष्ठा nv50_wndw *wndw)
अणु
	अटल स्थिर काष्ठा अणु
		s32 oclass;
		पूर्णांक version;
		पूर्णांक (*init)(काष्ठा nouveau_drm *, s32, काष्ठा nv50_wndw *);
	पूर्ण oimms[] = अणु
		अणु GK104_DISP_OVERLAY, 0, oimm507b_init पूर्ण,
		अणु GF110_DISP_OVERLAY, 0, oimm507b_init पूर्ण,
		अणु GT214_DISP_OVERLAY, 0, oimm507b_init पूर्ण,
		अणु   G82_DISP_OVERLAY, 0, oimm507b_init पूर्ण,
		अणु  NV50_DISP_OVERLAY, 0, oimm507b_init पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक cid;

	cid = nvअगर_mclass(&disp->disp->object, oimms);
	अगर (cid < 0) अणु
		NV_ERROR(drm, "No supported overlay immediate class\n");
		वापस cid;
	पूर्ण

	वापस oimms[cid].init(drm, oimms[cid].oclass, wndw);
पूर्ण
