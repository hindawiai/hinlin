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
#समावेश "core.h"

#समावेश <nvअगर/class.h>

व्योम
nv50_core_del(काष्ठा nv50_core **pcore)
अणु
	काष्ठा nv50_core *core = *pcore;
	अगर (core) अणु
		nv50_dmac_destroy(&core->chan);
		kमुक्त(*pcore);
		*pcore = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nv50_core_new(काष्ठा nouveau_drm *drm, काष्ठा nv50_core **pcore)
अणु
	काष्ठा अणु
		s32 oclass;
		पूर्णांक version;
		पूर्णांक (*new)(काष्ठा nouveau_drm *, s32, काष्ठा nv50_core **);
	पूर्ण cores[] = अणु
		अणु GA102_DISP_CORE_CHANNEL_DMA, 0, corec57d_new पूर्ण,
		अणु TU102_DISP_CORE_CHANNEL_DMA, 0, corec57d_new पूर्ण,
		अणु GV100_DISP_CORE_CHANNEL_DMA, 0, corec37d_new पूर्ण,
		अणु GP102_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GP100_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GM200_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GM107_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GK110_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GK104_DISP_CORE_CHANNEL_DMA, 0, core917d_new पूर्ण,
		अणु GF110_DISP_CORE_CHANNEL_DMA, 0, core907d_new पूर्ण,
		अणु GT214_DISP_CORE_CHANNEL_DMA, 0, core827d_new पूर्ण,
		अणु GT206_DISP_CORE_CHANNEL_DMA, 0, core827d_new पूर्ण,
		अणु GT200_DISP_CORE_CHANNEL_DMA, 0, core827d_new पूर्ण,
		अणु   G82_DISP_CORE_CHANNEL_DMA, 0, core827d_new पूर्ण,
		अणु  NV50_DISP_CORE_CHANNEL_DMA, 0, core507d_new पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक cid;

	cid = nvअगर_mclass(&disp->disp->object, cores);
	अगर (cid < 0) अणु
		NV_ERROR(drm, "No supported core channel class\n");
		वापस cid;
	पूर्ण

	वापस cores[cid].new(drm, cores[cid].oclass, pcore);
पूर्ण
