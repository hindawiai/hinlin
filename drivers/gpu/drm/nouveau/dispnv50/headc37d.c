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
#समावेश "atom.h"
#समावेश "core.h"

#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc37d.h>

अटल पूर्णांक
headc37d_or(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u8 depth;
	पूर्णांक ret;

	/*XXX: This is a dirty hack until OR depth handling is
	 *     improved later क्रम deep colour etc.
	 */
	चयन (asyh->or.depth) अणु
	हाल 6: depth = 5; अवरोध;
	हाल 5: depth = 4; अवरोध;
	हाल 2: depth = 1; अवरोध;
	हाल 0:	depth = 4; अवरोध;
	शेष:
		depth = asyh->or.depth;
		WARN_ON(1);
		अवरोध;
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE(i),
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, CRC_MODE, asyh->or.crc_raster) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, HSYNC_POLARITY, asyh->or.nhsync) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, VSYNC_POLARITY, asyh->or.nvsync) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, PIXEL_DEPTH, depth) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, COLOR_SPACE_OVERRIDE, DISABLE));
	वापस 0;
पूर्ण

अटल पूर्णांक
headc37d_procamp(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_PROCAMP(i),
		  NVDEF(NVC37D, HEAD_SET_PROCAMP, COLOR_SPACE, RGB) |
		  NVDEF(NVC37D, HEAD_SET_PROCAMP, CHROMA_LPF, DISABLE) |
		  NVVAL(NVC37D, HEAD_SET_PROCAMP, SAT_COS, asyh->procamp.sat.cos) |
		  NVVAL(NVC37D, HEAD_SET_PROCAMP, SAT_SINE, asyh->procamp.sat.sin) |
		  NVDEF(NVC37D, HEAD_SET_PROCAMP, DYNAMIC_RANGE, VESA) |
		  NVDEF(NVC37D, HEAD_SET_PROCAMP, RANGE_COMPRESSION, DISABLE) |
		  NVDEF(NVC37D, HEAD_SET_PROCAMP, BLACK_LEVEL, GRAPHICS));
	वापस 0;
पूर्ण

पूर्णांक
headc37d_dither(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_DITHER_CONTROL(i),
		  NVVAL(NVC37D, HEAD_SET_DITHER_CONTROL, ENABLE, asyh->dither.enable) |
		  NVVAL(NVC37D, HEAD_SET_DITHER_CONTROL, BITS, asyh->dither.bits) |
		  NVDEF(NVC37D, HEAD_SET_DITHER_CONTROL, OFFSET_ENABLE, DISABLE) |
		  NVVAL(NVC37D, HEAD_SET_DITHER_CONTROL, MODE, asyh->dither.mode) |
		  NVVAL(NVC37D, HEAD_SET_DITHER_CONTROL, PHASE, 0));
	वापस 0;
पूर्ण

पूर्णांक
headc37d_curs_clr(काष्ठा nv50_head *head)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTROL_CURSOR(i),
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR, ENABLE, DISABLE) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR, FORMAT, A8R8G8B8));

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CURSOR(i, 0), 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
headc37d_curs_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 7)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTROL_CURSOR(i),
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR, ENABLE, ENABLE) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_CURSOR, FORMAT, asyh->curs.क्रमmat) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_CURSOR, SIZE, asyh->curs.layout) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_X, 0) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_Y, 0) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR, DE_GAMMA, NONE),

				HEAD_SET_CONTROL_CURSOR_COMPOSITION(i),
		  NVVAL(NVC37D, HEAD_SET_CONTROL_CURSOR_COMPOSITION, K1, 0xff) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR_COMPOSITION, CURSOR_COLOR_FACTOR_SELECT,
								     K1) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR_COMPOSITION, VIEWPORT_COLOR_FACTOR_SELECT,
								     NEG_K1_TIMES_SRC) |
		  NVDEF(NVC37D, HEAD_SET_CONTROL_CURSOR_COMPOSITION, MODE, BLEND));

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_CURSOR(i, 0), asyh->curs.handle);
	PUSH_MTHD(push, NVC37D, HEAD_SET_OFFSET_CURSOR(i, 0), asyh->curs.offset >> 8);
	वापस 0;
पूर्ण

पूर्णांक
headc37d_curs_क्रमmat(काष्ठा nv50_head *head, काष्ठा nv50_wndw_atom *asyw,
		     काष्ठा nv50_head_atom *asyh)
अणु
	asyh->curs.क्रमmat = asyw->image.क्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक
headc37d_olut_clr(काष्ठा nv50_head *head)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTEXT_DMA_OUTPUT_LUT(i), 0x00000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
headc37d_olut_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_CONTROL_OUTPUT_LUT(i),
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_LUT, SIZE, asyh->olut.size) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_LUT, RANGE, asyh->olut.range) |
		  NVVAL(NVC37D, HEAD_SET_CONTROL_OUTPUT_LUT, OUTPUT_MODE, asyh->olut.output_mode),

				HEAD_SET_OFFSET_OUTPUT_LUT(i), asyh->olut.offset >> 8,
				HEAD_SET_CONTEXT_DMA_OUTPUT_LUT(i), asyh->olut.handle);
	वापस 0;
पूर्ण

अटल bool
headc37d_olut(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh, पूर्णांक size)
अणु
	अगर (size != 256 && size != 1024)
		वापस false;

	asyh->olut.size = size == 1024 ? NVC37D_HEAD_SET_CONTROL_OUTPUT_LUT_SIZE_SIZE_1025 :
					 NVC37D_HEAD_SET_CONTROL_OUTPUT_LUT_SIZE_SIZE_257;
	asyh->olut.range = NVC37D_HEAD_SET_CONTROL_OUTPUT_LUT_RANGE_UNITY;
	asyh->olut.output_mode = NVC37D_HEAD_SET_CONTROL_OUTPUT_LUT_OUTPUT_MODE_INTERPOLATE;
	asyh->olut.load = head907d_olut_load;
	वापस true;
पूर्ण

अटल पूर्णांक
headc37d_mode(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	काष्ठा nv50_head_mode *m = &asyh->mode;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 15)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_RASTER_SIZE(i),
		  NVVAL(NVC37D, HEAD_SET_RASTER_SIZE, WIDTH, m->h.active) |
		  NVVAL(NVC37D, HEAD_SET_RASTER_SIZE, HEIGHT, m->v.active),

				HEAD_SET_RASTER_SYNC_END(i),
		  NVVAL(NVC37D, HEAD_SET_RASTER_SYNC_END, X, m->h.synce) |
		  NVVAL(NVC37D, HEAD_SET_RASTER_SYNC_END, Y, m->v.synce),

				HEAD_SET_RASTER_BLANK_END(i),
		  NVVAL(NVC37D, HEAD_SET_RASTER_BLANK_END, X, m->h.blanke) |
		  NVVAL(NVC37D, HEAD_SET_RASTER_BLANK_END, Y, m->v.blanke),

				HEAD_SET_RASTER_BLANK_START(i),
		  NVVAL(NVC37D, HEAD_SET_RASTER_BLANK_START, X, m->h.blanks) |
		  NVVAL(NVC37D, HEAD_SET_RASTER_BLANK_START, Y, m->v.blanks));

	//XXX:
	PUSH_NVSQ(push, NVC37D, 0x2074 + (i * 0x400), m->v.blank2e << 16 | m->v.blank2s);
	PUSH_NVSQ(push, NVC37D, 0x2008 + (i * 0x400), m->पूर्णांकerlace);

	PUSH_MTHD(push, NVC37D, HEAD_SET_PIXEL_CLOCK_FREQUENCY(i),
		  NVVAL(NVC37D, HEAD_SET_PIXEL_CLOCK_FREQUENCY, HERTZ, m->घड़ी * 1000));

	PUSH_MTHD(push, NVC37D, HEAD_SET_PIXEL_CLOCK_FREQUENCY_MAX(i),
		  NVVAL(NVC37D, HEAD_SET_PIXEL_CLOCK_FREQUENCY_MAX, HERTZ, m->घड़ी * 1000));

	/*XXX: HEAD_USAGE_BOUNDS, करोesn't beदीर्घ here. */
	PUSH_MTHD(push, NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS(i),
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, CURSOR, USAGE_W256_H256) |
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, OUTPUT_LUT, USAGE_1025) |
		  NVDEF(NVC37D, HEAD_SET_HEAD_USAGE_BOUNDS, UPSCALING_ALLOWED, TRUE));
	वापस 0;
पूर्ण

पूर्णांक
headc37d_view(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NVC37D, HEAD_SET_VIEWPORT_SIZE_IN(i),
		  NVVAL(NVC37D, HEAD_SET_VIEWPORT_SIZE_IN, WIDTH, asyh->view.iW) |
		  NVVAL(NVC37D, HEAD_SET_VIEWPORT_SIZE_IN, HEIGHT, asyh->view.iH));

	PUSH_MTHD(push, NVC37D, HEAD_SET_VIEWPORT_SIZE_OUT(i),
		  NVVAL(NVC37D, HEAD_SET_VIEWPORT_SIZE_OUT, WIDTH, asyh->view.oW) |
		  NVVAL(NVC37D, HEAD_SET_VIEWPORT_SIZE_OUT, HEIGHT, asyh->view.oH));
	वापस 0;
पूर्ण

व्योम
headc37d_अटल_wndw_map(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	पूर्णांक i, end;

	क्रम (i = head->base.index * 2, end = i + 2; i < end; i++)
		asyh->wndw.owned |= BIT(i);
पूर्ण

स्थिर काष्ठा nv50_head_func
headc37d = अणु
	.view = headc37d_view,
	.mode = headc37d_mode,
	.olut = headc37d_olut,
	.olut_size = 1024,
	.olut_set = headc37d_olut_set,
	.olut_clr = headc37d_olut_clr,
	.curs_layout = head917d_curs_layout,
	.curs_क्रमmat = headc37d_curs_क्रमmat,
	.curs_set = headc37d_curs_set,
	.curs_clr = headc37d_curs_clr,
	.dither = headc37d_dither,
	.procamp = headc37d_procamp,
	.or = headc37d_or,
	.अटल_wndw_map = headc37d_अटल_wndw_map,
पूर्ण;
