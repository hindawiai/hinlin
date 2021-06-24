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

#समावेश <nvअगर/cl507d.h>
#समावेश <nvअगर/push507c.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl507d.h>

#समावेश "nouveau_bo.h"

पूर्णांक
core507d_update(काष्ठा nv50_core *core, u32 *पूर्णांकerlock, bool ntfy)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, (ntfy ? 2 : 0) + 3)))
		वापस ret;

	अगर (ntfy) अणु
		PUSH_MTHD(push, NV507D, SET_NOTIFIER_CONTROL,
			  NVDEF(NV507D, SET_NOTIFIER_CONTROL, MODE, WRITE) |
			  NVVAL(NV507D, SET_NOTIFIER_CONTROL, OFFSET, NV50_DISP_CORE_NTFY >> 2) |
			  NVDEF(NV507D, SET_NOTIFIER_CONTROL, NOTIFY, ENABLE));
	पूर्ण

	PUSH_MTHD(push, NV507D, UPDATE, पूर्णांकerlock[NV50_DISP_INTERLOCK_BASE] |
					पूर्णांकerlock[NV50_DISP_INTERLOCK_OVLY] |
		  NVDEF(NV507D, UPDATE, NOT_DRIVER_FRIENDLY, FALSE) |
		  NVDEF(NV507D, UPDATE, NOT_DRIVER_UNFRIENDLY, FALSE) |
		  NVDEF(NV507D, UPDATE, INHIBIT_INTERRUPTS, FALSE),

				SET_NOTIFIER_CONTROL,
		  NVDEF(NV507D, SET_NOTIFIER_CONTROL, NOTIFY, DISABLE));

	वापस PUSH_KICK(push);
पूर्ण

पूर्णांक
core507d_ntfy_रुको_करोne(काष्ठा nouveau_bo *bo, u32 offset,
			काष्ठा nvअगर_device *device)
अणु
	s64 समय = nvअगर_msec(device, 2000ULL,
		अगर (NVBO_TD32(bo, offset, NV_DISP_CORE_NOTIFIER_1, COMPLETION_0, DONE, ==, TRUE))
			अवरोध;
		usleep_range(1, 2);
	);
	वापस समय < 0 ? समय : 0;
पूर्ण

व्योम
core507d_ntfy_init(काष्ठा nouveau_bo *bo, u32 offset)
अणु
	NVBO_WR32(bo, offset, NV_DISP_CORE_NOTIFIER_1, COMPLETION_0,
			NVDEF(NV_DISP_CORE_NOTIFIER_1, COMPLETION_0, DONE, FALSE));
पूर्ण

पूर्णांक
core507d_पढ़ो_caps(काष्ठा nv50_disp *disp)
अणु
	काष्ठा nvअगर_push *push = disp->core->chan.push;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 6);
	अगर (ret)
		वापस ret;

	PUSH_MTHD(push, NV507D, SET_NOTIFIER_CONTROL,
		  NVDEF(NV507D, SET_NOTIFIER_CONTROL, MODE, WRITE) |
		  NVVAL(NV507D, SET_NOTIFIER_CONTROL, OFFSET, NV50_DISP_CORE_NTFY >> 2) |
		  NVDEF(NV507D, SET_NOTIFIER_CONTROL, NOTIFY, ENABLE));

	PUSH_MTHD(push, NV507D, GET_CAPABILITIES, 0x00000000);

	PUSH_MTHD(push, NV507D, SET_NOTIFIER_CONTROL,
		  NVDEF(NV507D, SET_NOTIFIER_CONTROL, NOTIFY, DISABLE));

	वापस PUSH_KICK(push);
पूर्ण

पूर्णांक
core507d_caps_init(काष्ठा nouveau_drm *drm, काष्ठा nv50_disp *disp)
अणु
	काष्ठा nv50_core *core = disp->core;
	काष्ठा nouveau_bo *bo = disp->sync;
	s64 समय;
	पूर्णांक ret;

	NVBO_WR32(bo, NV50_DISP_CORE_NTFY, NV_DISP_CORE_NOTIFIER_1, CAPABILITIES_1,
				     NVDEF(NV_DISP_CORE_NOTIFIER_1, CAPABILITIES_1, DONE, FALSE));

	ret = core507d_पढ़ो_caps(disp);
	अगर (ret < 0)
		वापस ret;

	समय = nvअगर_msec(core->chan.base.device, 2000ULL,
			 अगर (NVBO_TD32(bo, NV50_DISP_CORE_NTFY,
				       NV_DISP_CORE_NOTIFIER_1, CAPABILITIES_1, DONE, ==, TRUE))
				 अवरोध;
			 usleep_range(1, 2);
			 );
	अगर (समय < 0)
		NV_ERROR(drm, "core caps notifier timeout\n");

	वापस 0;
पूर्ण

पूर्णांक
core507d_init(काष्ठा nv50_core *core)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV507D, SET_CONTEXT_DMA_NOTIFIER, core->chan.sync.handle);
	वापस PUSH_KICK(push);
पूर्ण

अटल स्थिर काष्ठा nv50_core_func
core507d = अणु
	.init = core507d_init,
	.ntfy_init = core507d_ntfy_init,
	.caps_init = core507d_caps_init,
	.ntfy_रुको_करोne = core507d_ntfy_रुको_करोne,
	.update = core507d_update,
	.head = &head507d,
	.dac = &dac507d,
	.sor = &sor507d,
	.pior = &pior507d,
पूर्ण;

पूर्णांक
core507d_new_(स्थिर काष्ठा nv50_core_func *func, काष्ठा nouveau_drm *drm,
	      s32 oclass, काष्ठा nv50_core **pcore)
अणु
	काष्ठा nv50_disp_core_channel_dma_v0 args = अणुपूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	काष्ठा nv50_core *core;
	पूर्णांक ret;

	अगर (!(core = *pcore = kzalloc(माप(*core), GFP_KERNEL)))
		वापस -ENOMEM;
	core->func = func;

	ret = nv50_dmac_create(&drm->client.device, &disp->disp->object,
			       &oclass, 0, &args, माप(args),
			       disp->sync->offset, &core->chan);
	अगर (ret) अणु
		NV_ERROR(drm, "core%04x allocation failed: %d\n", oclass, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
core507d_new(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_core **pcore)
अणु
	वापस core507d_new_(&core507d, drm, oclass, pcore);
पूर्ण
