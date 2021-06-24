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
#समावेश "oimm.h"

#समावेश <nvअगर/class.h>

पूर्णांक
nv50_ovly_new(काष्ठा nouveau_drm *drm, पूर्णांक head, काष्ठा nv50_wndw **pwndw)
अणु
	अटल स्थिर काष्ठा अणु
		s32 oclass;
		पूर्णांक version;
		पूर्णांक (*new)(काष्ठा nouveau_drm *, पूर्णांक, s32, काष्ठा nv50_wndw **);
	पूर्ण ovlys[] = अणु
		अणु GK104_DISP_OVERLAY_CONTROL_DMA, 0, ovly917e_new पूर्ण,
		अणु GF110_DISP_OVERLAY_CONTROL_DMA, 0, ovly907e_new पूर्ण,
		अणु GT214_DISP_OVERLAY_CHANNEL_DMA, 0, ovly827e_new पूर्ण,
		अणु GT200_DISP_OVERLAY_CHANNEL_DMA, 0, ovly827e_new पूर्ण,
		अणु   G82_DISP_OVERLAY_CHANNEL_DMA, 0, ovly827e_new पूर्ण,
		अणु  NV50_DISP_OVERLAY_CHANNEL_DMA, 0, ovly507e_new पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक cid, ret;

	cid = nvअगर_mclass(&disp->disp->object, ovlys);
	अगर (cid < 0) अणु
		NV_ERROR(drm, "No supported overlay class\n");
		वापस cid;
	पूर्ण

	ret = ovlys[cid].new(drm, head, ovlys[cid].oclass, pwndw);
	अगर (ret)
		वापस ret;

	वापस nv50_oimm_init(drm, *pwndw);
पूर्ण
