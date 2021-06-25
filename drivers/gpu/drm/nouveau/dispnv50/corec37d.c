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

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/pushc37b.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/clc37d.h>

#समावेश <nouveau_bo.h>

पूर्णांक
corec37d_wndw_owner(काष्ठा nv50_core *core)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	स्थिर u32 winकरोws = 8; /*XXX*/
	पूर्णांक ret, i;

	अगर ((ret = PUSH_WAIT(push, winकरोws * 2)))
		वापस ret;

	क्रम (i = 0; i < winकरोws; i++) अणु
		PUSH_MTHD(push, NVC37D, WINDOW_SET_CONTROL(i),
			  NVDEF(NVC37D, WINDOW_SET_CONTROL, OWNER, HEAD(i >> 1)));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
corec37d_update(काष्ठा nv50_core *core, u32 *पूर्णांकerlock, bool ntfy)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, (ntfy ? 2 * 2 : 0) + 5)))
		वापस ret;

	अगर (ntfy) अणु
		PUSH_MTHD(push, NVC37D, SET_NOTIFIER_CONTROL,
			  NVDEF(NVC37D, SET_NOTIFIER_CONTROL, MODE, WRITE) |
			  NVVAL(NVC37D, SET_NOTIFIER_CONTROL, OFFSET, NV50_DISP_CORE_NTFY >> 4) |
			  NVDEF(NVC37D, SET_NOTIFIER_CONTROL, NOTIFY, ENABLE));
	पूर्ण

	PUSH_MTHD(push, NVC37D, SET_INTERLOCK_FLAGS, पूर्णांकerlock[NV50_DISP_INTERLOCK_CURS],
				SET_WINDOW_INTERLOCK_FLAGS, पूर्णांकerlock[NV50_DISP_INTERLOCK_WNDW]);
	PUSH_MTHD(push, NVC37D, UPDATE, 0x00000001 |
		  NVDEF(NVC37D, UPDATE, SPECIAL_HANDLING, NONE) |
		  NVDEF(NVC37D, UPDATE, INHIBIT_INTERRUPTS, FALSE));

	अगर (ntfy) अणु
		PUSH_MTHD(push, NVC37D, SET_NOTIFIER_CONTROL,
			  NVDEF(NVC37D, SET_NOTIFIER_CONTROL, NOTIFY, DISABLE));
	पूर्ण

	वापस PUSH_KICK(push);
पूर्ण

पूर्णांक
corec37d_ntfy_रुको_करोne(काष्ठा nouveau_bo *bo, u32 offset,
			काष्ठा nvअगर_device *device)
अणु
	s64 समय = nvअगर_msec(device, 2000ULL,
		अगर (NVBO_TD32(bo, offset, NV_DISP_NOTIFIER, _0, STATUS, ==, FINISHED))
			अवरोध;
		usleep_range(1, 2);
	);
	वापस समय < 0 ? समय : 0;
पूर्ण

व्योम
corec37d_ntfy_init(काष्ठा nouveau_bo *bo, u32 offset)
अणु
	NVBO_WR32(bo, offset, NV_DISP_NOTIFIER, _0,
			NVDEF(NV_DISP_NOTIFIER, _0, STATUS, NOT_BEGUN));
	NVBO_WR32(bo, offset, NV_DISP_NOTIFIER, _1, 0);
	NVBO_WR32(bo, offset, NV_DISP_NOTIFIER, _2, 0);
	NVBO_WR32(bo, offset, NV_DISP_NOTIFIER, _3, 0);
पूर्ण

पूर्णांक corec37d_caps_init(काष्ठा nouveau_drm *drm, काष्ठा nv50_disp *disp)
अणु
	पूर्णांक ret;

	ret = nvअगर_object_ctor(&disp->disp->object, "dispCaps", 0,
			       GV100_DISP_CAPS, शून्य, 0, &disp->caps);
	अगर (ret) अणु
		NV_ERROR(drm,
			 "Failed to init notifier caps region: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	ret = nvअगर_object_map(&disp->caps, शून्य, 0);
	अगर (ret) अणु
		NV_ERROR(drm,
			 "Failed to map notifier caps region: %d\n",
			 ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
corec37d_init(काष्ठा nv50_core *core)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	स्थिर u32 winकरोws = 8; /*XXX*/
	पूर्णांक ret, i;

	अगर ((ret = PUSH_WAIT(push, 2 + winकरोws * 5)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, SET_CONTEXT_DMA_NOTIFIER, core->chan.sync.handle);

	क्रम (i = 0; i < winकरोws; i++) अणु
		PUSH_MTHD(push, NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS(i),
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED1BPP, TRUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED2BPP, TRUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED4BPP, TRUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED8BPP, TRUE) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, YUV_PACKED422, TRUE),

					WINDOW_SET_WINDOW_ROTATED_FORMAT_USAGE_BOUNDS(i), 0x00000000);

		PUSH_MTHD(push, NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS(i),
			  NVVAL(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, MAX_PIXELS_FETCHED_PER_LINE, 0x7fff) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_LUT, USAGE_1025) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_SCALER_TAPS, TAPS_2) |
			  NVDEF(NVC37D, WINDOW_SET_WINDOW_USAGE_BOUNDS, UPSCALING_ALLOWED, FALSE));
	पूर्ण

	core->assign_winकरोws = true;
	वापस PUSH_KICK(push);
पूर्ण

अटल स्थिर काष्ठा nv50_core_func
corec37d = अणु
	.init = corec37d_init,
	.ntfy_init = corec37d_ntfy_init,
	.caps_init = corec37d_caps_init,
	.ntfy_रुको_करोne = corec37d_ntfy_रुको_करोne,
	.update = corec37d_update,
	.wndw.owner = corec37d_wndw_owner,
	.head = &headc37d,
	.sor = &sorc37d,
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	.crc = &crcc37d,
#पूर्ण_अगर
पूर्ण;

पूर्णांक
corec37d_new(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_core **pcore)
अणु
	वापस core507d_new_(&corec37d, drm, oclass, pcore);
पूर्ण
