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
#समावेश "head.h"
#समावेश "core.h"

#समावेश "nvif/push.h"
#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl917d.h>

अटल पूर्णांक
head917d_dither(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV917D, HEAD_SET_DITHER_CONTROL(i),
		  NVVAL(NV917D, HEAD_SET_DITHER_CONTROL, ENABLE, asyh->dither.enable) |
		  NVVAL(NV917D, HEAD_SET_DITHER_CONTROL, BITS, asyh->dither.bits) |
		  NVVAL(NV917D, HEAD_SET_DITHER_CONTROL, MODE, asyh->dither.mode) |
		  NVVAL(NV917D, HEAD_SET_DITHER_CONTROL, PHASE, 0));
	वापस 0;
पूर्ण

अटल पूर्णांक
head917d_base(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u32 bounds = 0;
	पूर्णांक ret;

	अगर (asyh->base.cpp) अणु
		चयन (asyh->base.cpp) अणु
		हाल 8: bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_64); अवरोध;
		हाल 4: bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_32); अवरोध;
		हाल 2: bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_16); अवरोध;
		हाल 1: bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_8); अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, USABLE, TRUE);
		bounds |= NVDEF(NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, BASE_LUT, USAGE_1025);
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV917D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS(i), bounds);
	वापस 0;
पूर्ण

अटल पूर्णांक
head917d_curs_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 5);
	अगर (ret)
		वापस ret;

	PUSH_MTHD(push, NV917D, HEAD_SET_CONTROL_CURSOR(i),
		  NVDEF(NV917D, HEAD_SET_CONTROL_CURSOR, ENABLE, ENABLE) |
		  NVVAL(NV917D, HEAD_SET_CONTROL_CURSOR, FORMAT, asyh->curs.क्रमmat) |
		  NVVAL(NV917D, HEAD_SET_CONTROL_CURSOR, SIZE, asyh->curs.layout) |
		  NVVAL(NV917D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_X, 0) |
		  NVVAL(NV917D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_Y, 0) |
		  NVDEF(NV917D, HEAD_SET_CONTROL_CURSOR, COMPOSITION, ALPHA_BLEND),

				HEAD_SET_OFFSET_CURSOR(i), asyh->curs.offset >> 8);

	PUSH_MTHD(push, NV917D, HEAD_SET_CONTEXT_DMA_CURSOR(i), asyh->curs.handle);
	वापस 0;
पूर्ण

पूर्णांक
head917d_curs_layout(काष्ठा nv50_head *head, काष्ठा nv50_wndw_atom *asyw,
		     काष्ठा nv50_head_atom *asyh)
अणु
	चयन (asyw->state.fb->width) अणु
	हाल  32: asyh->curs.layout = NV917D_HEAD_SET_CONTROL_CURSOR_SIZE_W32_H32; अवरोध;
	हाल  64: asyh->curs.layout = NV917D_HEAD_SET_CONTROL_CURSOR_SIZE_W64_H64; अवरोध;
	हाल 128: asyh->curs.layout = NV917D_HEAD_SET_CONTROL_CURSOR_SIZE_W128_H128; अवरोध;
	हाल 256: asyh->curs.layout = NV917D_HEAD_SET_CONTROL_CURSOR_SIZE_W256_H256; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_head_func
head917d = अणु
	.view = head907d_view,
	.mode = head907d_mode,
	.olut = head907d_olut,
	.olut_size = 1024,
	.olut_set = head907d_olut_set,
	.olut_clr = head907d_olut_clr,
	.core_calc = head507d_core_calc,
	.core_set = head907d_core_set,
	.core_clr = head907d_core_clr,
	.curs_layout = head917d_curs_layout,
	.curs_क्रमmat = head507d_curs_क्रमmat,
	.curs_set = head917d_curs_set,
	.curs_clr = head907d_curs_clr,
	.base = head917d_base,
	.ovly = head907d_ovly,
	.dither = head917d_dither,
	.procamp = head907d_procamp,
	.or = head907d_or,
पूर्ण;
