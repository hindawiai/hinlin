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

#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc57d.h>

अटल पूर्णांक
corec57d_init(काष्ठा nv50_core *core)
अणु
	काष्ठा nvअगर_push *push = core->chan.push;
	स्थिर u32 winकरोws = 8; /*XXX*/
	पूर्णांक ret, i;

	अगर ((ret = PUSH_WAIT(push, 2 + winकरोws * 5)))
		वापस ret;

	PUSH_MTHD(push, NVC57D, SET_CONTEXT_DMA_NOTIFIER, core->chan.sync.handle);

	क्रम (i = 0; i < winकरोws; i++) अणु
		PUSH_MTHD(push, NVC57D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS(i),
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED1BPP, TRUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED2BPP, TRUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED4BPP, TRUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_FORMAT_USAGE_BOUNDS, RGB_PACKED8BPP, TRUE),

					WINDOW_SET_WINDOW_ROTATED_FORMAT_USAGE_BOUNDS(i), 0x00000000);

		PUSH_MTHD(push, NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS(i),
			  NVVAL(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, MAX_PIXELS_FETCHED_PER_LINE, 0x7fff) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, ILUT_ALLOWED, TRUE) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, INPUT_SCALER_TAPS, TAPS_2) |
			  NVDEF(NVC57D, WINDOW_SET_WINDOW_USAGE_BOUNDS, UPSCALING_ALLOWED, FALSE));
	पूर्ण

	core->assign_winकरोws = true;
	वापस PUSH_KICK(push);
पूर्ण

अटल स्थिर काष्ठा nv50_core_func
corec57d = अणु
	.init = corec57d_init,
	.ntfy_init = corec37d_ntfy_init,
	.caps_init = corec37d_caps_init,
	.ntfy_रुको_करोne = corec37d_ntfy_रुको_करोne,
	.update = corec37d_update,
	.wndw.owner = corec37d_wndw_owner,
	.head = &headc57d,
	.sor = &sorc37d,
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	.crc = &crcc37d,
#पूर्ण_अगर
पूर्ण;

पूर्णांक
corec57d_new(काष्ठा nouveau_drm *drm, s32 oclass, काष्ठा nv50_core **pcore)
अणु
	वापस core507d_new_(&corec57d, drm, oclass, pcore);
पूर्ण
