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
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_mode_config.h>
#समावेश <drm/drm_vblank.h>
#समावेश "nouveau_drv.h"
#समावेश "nouveau_bios.h"
#समावेश "nouveau_connector.h"
#समावेश "head.h"
#समावेश "core.h"
#समावेश "crc.h"

#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl907d.h>

पूर्णांक
head907d_or(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 3)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTROL_OUTPUT_RESOURCE(i),
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, CRC_MODE, asyh->or.crc_raster) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, HSYNC_POLARITY, asyh->or.nhsync) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, VSYNC_POLARITY, asyh->or.nvsync) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_RESOURCE, PIXEL_DEPTH, asyh->or.depth),

				HEAD_SET_CONTROL(i), 0x31ec6000 | head->base.index << 25 |
		  NVVAL(NV907D, HEAD_SET_CONTROL, STRUCTURE, asyh->mode.पूर्णांकerlace));
	वापस 0;
पूर्ण

पूर्णांक
head907d_procamp(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_PROCAMP(i),
		  NVDEF(NV907D, HEAD_SET_PROCAMP, COLOR_SPACE, RGB) |
		  NVDEF(NV907D, HEAD_SET_PROCAMP, CHROMA_LPF, AUTO) |
		  NVVAL(NV907D, HEAD_SET_PROCAMP, SAT_COS, asyh->procamp.sat.cos) |
		  NVVAL(NV907D, HEAD_SET_PROCAMP, SAT_SINE, asyh->procamp.sat.sin) |
		  NVDEF(NV907D, HEAD_SET_PROCAMP, DYNAMIC_RANGE, VESA) |
		  NVDEF(NV907D, HEAD_SET_PROCAMP, RANGE_COMPRESSION, DISABLE));
	वापस 0;
पूर्ण

अटल पूर्णांक
head907d_dither(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_DITHER_CONTROL(i),
		  NVVAL(NV907D, HEAD_SET_DITHER_CONTROL, ENABLE, asyh->dither.enable) |
		  NVVAL(NV907D, HEAD_SET_DITHER_CONTROL, BITS, asyh->dither.bits) |
		  NVVAL(NV907D, HEAD_SET_DITHER_CONTROL, MODE, asyh->dither.mode) |
		  NVVAL(NV907D, HEAD_SET_DITHER_CONTROL, PHASE, 0));
	वापस 0;
पूर्ण

पूर्णांक
head907d_ovly(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u32 bounds = 0;
	पूर्णांक ret;

	अगर (asyh->ovly.cpp) अणु
		चयन (asyh->ovly.cpp) अणु
		हाल 8: bounds |= NVDEF(NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS, PIXEL_DEPTH, BPP_64); अवरोध;
		हाल 4: bounds |= NVDEF(NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS, PIXEL_DEPTH, BPP_32); अवरोध;
		हाल 2: bounds |= NVDEF(NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS, PIXEL_DEPTH, BPP_16); अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		bounds |= NVDEF(NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS, USABLE, TRUE);
	पूर्ण अन्यथा अणु
		bounds |= NVDEF(NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS, PIXEL_DEPTH, BPP_16);
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_OVERLAY_USAGE_BOUNDS(i), bounds);
	वापस 0;
पूर्ण

अटल पूर्णांक
head907d_base(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	u32 bounds = 0;
	पूर्णांक ret;

	अगर (asyh->base.cpp) अणु
		चयन (asyh->base.cpp) अणु
		हाल 8: bounds |= NVDEF(NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_64); अवरोध;
		हाल 4: bounds |= NVDEF(NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_32); अवरोध;
		हाल 2: bounds |= NVDEF(NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_16); अवरोध;
		हाल 1: bounds |= NVDEF(NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, PIXEL_DEPTH, BPP_8); अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		bounds |= NVDEF(NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS, USABLE, TRUE);
	पूर्ण

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_BASE_CHANNEL_USAGE_BOUNDS(i), bounds);
	वापस 0;
पूर्ण

पूर्णांक
head907d_curs_clr(काष्ठा nv50_head *head)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTROL_CURSOR(i),
		  NVDEF(NV907D, HEAD_SET_CONTROL_CURSOR, ENABLE, DISABLE) |
		  NVDEF(NV907D, HEAD_SET_CONTROL_CURSOR, FORMAT, A8R8G8B8) |
		  NVDEF(NV907D, HEAD_SET_CONTROL_CURSOR, SIZE, W64_H64));

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CURSOR(i), 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
head907d_curs_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 5)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTROL_CURSOR(i),
		  NVDEF(NV907D, HEAD_SET_CONTROL_CURSOR, ENABLE, ENABLE) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_CURSOR, FORMAT, asyh->curs.क्रमmat) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_CURSOR, SIZE, asyh->curs.layout) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_X, 0) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_CURSOR, HOT_SPOT_Y, 0) |
		  NVDEF(NV907D, HEAD_SET_CONTROL_CURSOR, COMPOSITION, ALPHA_BLEND),

				HEAD_SET_OFFSET_CURSOR(i), asyh->curs.offset >> 8);

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_CURSOR(i), asyh->curs.handle);
	वापस 0;
पूर्ण

पूर्णांक
head907d_core_clr(काष्ठा nv50_head *head)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMAS_ISO(i), 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
head907d_core_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 9)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_OFFSET(i),
		  NVVAL(NV907D, HEAD_SET_OFFSET, ORIGIN, asyh->core.offset >> 8));

	PUSH_MTHD(push, NV907D, HEAD_SET_SIZE(i),
		  NVVAL(NV907D, HEAD_SET_SIZE, WIDTH, asyh->core.w) |
		  NVVAL(NV907D, HEAD_SET_SIZE, HEIGHT, asyh->core.h),

				HEAD_SET_STORAGE(i),
		  NVVAL(NV907D, HEAD_SET_STORAGE, BLOCK_HEIGHT, asyh->core.blockh) |
		  NVVAL(NV907D, HEAD_SET_STORAGE, PITCH, asyh->core.pitch >> 8) |
		  NVVAL(NV907D, HEAD_SET_STORAGE, PITCH, asyh->core.blocks) |
		  NVVAL(NV907D, HEAD_SET_STORAGE, MEMORY_LAYOUT, asyh->core.layout),

				HEAD_SET_PARAMS(i),
		  NVVAL(NV907D, HEAD_SET_PARAMS, FORMAT, asyh->core.क्रमmat) |
		  NVDEF(NV907D, HEAD_SET_PARAMS, SUPER_SAMPLE, X1_AA) |
		  NVDEF(NV907D, HEAD_SET_PARAMS, GAMMA, LINEAR),

				HEAD_SET_CONTEXT_DMAS_ISO(i),
		  NVVAL(NV907D, HEAD_SET_CONTEXT_DMAS_ISO, HANDLE, asyh->core.handle));

	PUSH_MTHD(push, NV907D, HEAD_SET_VIEWPORT_POINT_IN(i),
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_POINT_IN, X, asyh->core.x) |
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_POINT_IN, Y, asyh->core.y));
	वापस 0;
पूर्ण

पूर्णांक
head907d_olut_clr(काष्ठा nv50_head *head)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_OUTPUT_LUT_LO(i),
		  NVDEF(NV907D, HEAD_SET_OUTPUT_LUT_LO, ENABLE, DISABLE));

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_LUT(i), 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
head907d_olut_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 5)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_OUTPUT_LUT_LO(i),
		  NVDEF(NV907D, HEAD_SET_OUTPUT_LUT_LO, ENABLE, ENABLE) |
		  NVVAL(NV907D, HEAD_SET_OUTPUT_LUT_LO, MODE, asyh->olut.mode) |
		  NVDEF(NV907D, HEAD_SET_OUTPUT_LUT_LO, NEVER_YIELD_TO_BASE, DISABLE),

				HEAD_SET_OUTPUT_LUT_HI(i),
		  NVVAL(NV907D, HEAD_SET_OUTPUT_LUT_HI, ORIGIN, asyh->olut.offset >> 8));

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTEXT_DMA_LUT(i), asyh->olut.handle);
	वापस 0;
पूर्ण

व्योम
head907d_olut_load(काष्ठा drm_color_lut *in, पूर्णांक size, व्योम __iomem *mem)
अणु
	क्रम (; size--; in++, mem += 8) अणु
		ग_लिखोw(drm_color_lut_extract(in->  red, 14) + 0x6000, mem + 0);
		ग_लिखोw(drm_color_lut_extract(in->green, 14) + 0x6000, mem + 2);
		ग_लिखोw(drm_color_lut_extract(in-> blue, 14) + 0x6000, mem + 4);
	पूर्ण

	/* INTERPOLATE modes require a "next" entry to पूर्णांकerpolate with,
	 * so we replicate the last entry to deal with this क्रम now.
	 */
	ग_लिखोw(पढ़ोw(mem - 8), mem + 0);
	ग_लिखोw(पढ़ोw(mem - 6), mem + 2);
	ग_लिखोw(पढ़ोw(mem - 4), mem + 4);
पूर्ण

bool
head907d_olut(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh, पूर्णांक size)
अणु
	अगर (size != 256 && size != 1024)
		वापस false;

	अगर (size == 1024)
		asyh->olut.mode = NV907D_HEAD_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_1025_UNITY_RANGE;
	अन्यथा
		asyh->olut.mode = NV907D_HEAD_SET_OUTPUT_LUT_LO_MODE_INTERPOLATE_257_UNITY_RANGE;

	asyh->olut.load = head907d_olut_load;
	वापस true;
पूर्ण

पूर्णांक
head907d_mode(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	काष्ठा nv50_head_mode *m = &asyh->mode;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 13)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_OVERSCAN_COLOR(i),
		  NVVAL(NV907D, HEAD_SET_OVERSCAN_COLOR, RED, 0) |
		  NVVAL(NV907D, HEAD_SET_OVERSCAN_COLOR, GRN, 0) |
		  NVVAL(NV907D, HEAD_SET_OVERSCAN_COLOR, BLU, 0),

				HEAD_SET_RASTER_SIZE(i),
		  NVVAL(NV907D, HEAD_SET_RASTER_SIZE, WIDTH, m->h.active) |
		  NVVAL(NV907D, HEAD_SET_RASTER_SIZE, HEIGHT, m->v.active),

				HEAD_SET_RASTER_SYNC_END(i),
		  NVVAL(NV907D, HEAD_SET_RASTER_SYNC_END, X, m->h.synce) |
		  NVVAL(NV907D, HEAD_SET_RASTER_SYNC_END, Y, m->v.synce),

				HEAD_SET_RASTER_BLANK_END(i),
		  NVVAL(NV907D, HEAD_SET_RASTER_BLANK_END, X, m->h.blanke) |
		  NVVAL(NV907D, HEAD_SET_RASTER_BLANK_END, Y, m->v.blanke),

				HEAD_SET_RASTER_BLANK_START(i),
		  NVVAL(NV907D, HEAD_SET_RASTER_BLANK_START, X, m->h.blanks) |
		  NVVAL(NV907D, HEAD_SET_RASTER_BLANK_START, Y, m->v.blanks),

				HEAD_SET_RASTER_VERT_BLANK2(i),
		  NVVAL(NV907D, HEAD_SET_RASTER_VERT_BLANK2, YSTART, m->v.blank2s) |
		  NVVAL(NV907D, HEAD_SET_RASTER_VERT_BLANK2, YEND, m->v.blank2e));

	PUSH_MTHD(push, NV907D, HEAD_SET_DEFAULT_BASE_COLOR(i),
		  NVVAL(NV907D, HEAD_SET_DEFAULT_BASE_COLOR, RED, 0) |
		  NVVAL(NV907D, HEAD_SET_DEFAULT_BASE_COLOR, GREEN, 0) |
		  NVVAL(NV907D, HEAD_SET_DEFAULT_BASE_COLOR, BLUE, 0));

	PUSH_MTHD(push, NV907D, HEAD_SET_PIXEL_CLOCK_FREQUENCY(i),
		  NVVAL(NV907D, HEAD_SET_PIXEL_CLOCK_FREQUENCY, HERTZ, m->घड़ी * 1000) |
		  NVDEF(NV907D, HEAD_SET_PIXEL_CLOCK_FREQUENCY, ADJ1000DIV1001, FALSE),

				HEAD_SET_PIXEL_CLOCK_CONFIGURATION(i),
		  NVDEF(NV907D, HEAD_SET_PIXEL_CLOCK_CONFIGURATION, MODE, CLK_CUSTOM) |
		  NVDEF(NV907D, HEAD_SET_PIXEL_CLOCK_CONFIGURATION, NOT_DRIVER, FALSE) |
		  NVDEF(NV907D, HEAD_SET_PIXEL_CLOCK_CONFIGURATION, ENABLE_HOPPING, FALSE),

				HEAD_SET_PIXEL_CLOCK_FREQUENCY_MAX(i),
		  NVVAL(NV907D, HEAD_SET_PIXEL_CLOCK_FREQUENCY_MAX, HERTZ, m->घड़ी * 1000) |
		  NVDEF(NV907D, HEAD_SET_PIXEL_CLOCK_FREQUENCY_MAX, ADJ1000DIV1001, FALSE));
	वापस 0;
पूर्ण

पूर्णांक
head907d_view(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nvअगर_push *push = nv50_disp(head->base.base.dev)->core->chan.push;
	स्थिर पूर्णांक i = head->base.index;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 8)))
		वापस ret;

	PUSH_MTHD(push, NV907D, HEAD_SET_CONTROL_OUTPUT_SCALER(i),
		  NVDEF(NV907D, HEAD_SET_CONTROL_OUTPUT_SCALER, VERTICAL_TAPS, TAPS_1) |
		  NVDEF(NV907D, HEAD_SET_CONTROL_OUTPUT_SCALER, HORIZONTAL_TAPS, TAPS_1) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_SCALER, HRESPONSE_BIAS, 0) |
		  NVVAL(NV907D, HEAD_SET_CONTROL_OUTPUT_SCALER, VRESPONSE_BIAS, 0));

	PUSH_MTHD(push, NV907D, HEAD_SET_VIEWPORT_SIZE_IN(i),
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_IN, WIDTH, asyh->view.iW) |
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_IN, HEIGHT, asyh->view.iH));

	PUSH_MTHD(push, NV907D, HEAD_SET_VIEWPORT_SIZE_OUT(i),
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT, WIDTH, asyh->view.oW) |
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT, HEIGHT, asyh->view.oH),

				HEAD_SET_VIEWPORT_SIZE_OUT_MIN(i),
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT_MIN, WIDTH, asyh->view.oW) |
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT_MIN, HEIGHT, asyh->view.oH),

				HEAD_SET_VIEWPORT_SIZE_OUT_MAX(i),
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT_MAX, WIDTH, asyh->view.oW) |
		  NVVAL(NV907D, HEAD_SET_VIEWPORT_SIZE_OUT_MAX, HEIGHT, asyh->view.oH));
	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_head_func
head907d = अणु
	.view = head907d_view,
	.mode = head907d_mode,
	.olut = head907d_olut,
	.olut_size = 1024,
	.olut_set = head907d_olut_set,
	.olut_clr = head907d_olut_clr,
	.core_calc = head507d_core_calc,
	.core_set = head907d_core_set,
	.core_clr = head907d_core_clr,
	.curs_layout = head507d_curs_layout,
	.curs_क्रमmat = head507d_curs_क्रमmat,
	.curs_set = head907d_curs_set,
	.curs_clr = head907d_curs_clr,
	.base = head907d_base,
	.ovly = head907d_ovly,
	.dither = head907d_dither,
	.procamp = head907d_procamp,
	.or = head907d_or,
पूर्ण;
