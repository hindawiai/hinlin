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
#समावेश "head.h"

#समावेश <nvअगर/push507c.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl907d.h>

#समावेश "nouveau_bo.h"

पूर्णांक
core907d_caps_init(काष्ठा nouveau_drm *drm, काष्ठा nv50_disp *disp)
अणु
	काष्ठा nv50_core *core = disp->core;
	काष्ठा nouveau_bo *bo = disp->sync;
	s64 समय;
	पूर्णांक ret;

	NVBO_WR32(bo, NV50_DISP_CORE_NTFY, NV907D_CORE_NOTIFIER_3, CAPABILITIES_4,
				     NVDEF(NV907D_CORE_NOTIFIER_3, CAPABILITIES_4, DONE, FALSE));

	ret = core507d_पढ़ो_caps(disp);
	अगर (ret < 0)
		वापस ret;

	समय = nvअगर_msec(core->chan.base.device, 2000ULL,
			 अगर (NVBO_TD32(bo, NV50_DISP_CORE_NTFY,
				       NV907D_CORE_NOTIFIER_3, CAPABILITIES_4, DONE, ==, TRUE))
				 अवरोध;
			 usleep_range(1, 2);
			 );
	अगर (समय < 0)
		NV_ERROR(drm, "core caps notifier timeout\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_core_func
core907d = अणु
	.init = core507d_init,
	.ntfy_init = core507d_ntfy_init,
	.caps_init = core907d_caps_init,
	.ntfy_रुको_करोne = core507d_ntfy_रुको_करोne,
	.update = core507d_update,
	.head = &head907d,
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	.crc = &crc907d,
#पूर्ण_अगर
	.dac = &dac907d,
	.sor = &sor907d,
पूर्ण;

पूर्णांक
core907d_new(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_core **pcore)
अणु
	वापस core507d_new_(&core907d, drm, oclass, pcore);
पूर्ण
