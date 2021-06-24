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
#समावेश "base.h"

#समावेश <nvअगर/push507c.h>

#समावेश <nvhw/class/cl907c.h>

अटल पूर्णांक
base907c_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 10)))
		वापस ret;

	PUSH_MTHD(push, NV907C, SET_PRESENT_CONTROL,
		  NVVAL(NV907C, SET_PRESENT_CONTROL, BEGIN_MODE, asyw->image.mode) |
		  NVDEF(NV907C, SET_PRESENT_CONTROL, TIMESTAMP_MODE, DISABLE) |
		  NVVAL(NV907C, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMAS_ISO(0), asyw->image.handle, 1);

	PUSH_MTHD(push, NV907C, SURFACE_SET_OFFSET(0, 0), asyw->image.offset[0] >> 8,
				SURFACE_SET_OFFSET(0, 1), 0x00000000,

				SURFACE_SET_SIZE(0),
		  NVVAL(NV907C, SURFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NV907C, SURFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SURFACE_SET_STORAGE(0),
		  NVVAL(NV907C, SURFACE_SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh) |
		  NVVAL(NV907C, SURFACE_SET_STORAGE, PITCH, asyw->image.pitch[0] >> 8) |
		  NVVAL(NV907C, SURFACE_SET_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NV907C, SURFACE_SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout),

				SURFACE_SET_PARAMS(0),
		  NVVAL(NV907C, SURFACE_SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVDEF(NV907C, SURFACE_SET_PARAMS, SUPER_SAMPLE, X1_AA) |
		  NVDEF(NV907C, SURFACE_SET_PARAMS, GAMMA, LINEAR) |
		  NVDEF(NV907C, SURFACE_SET_PARAMS, LAYOUT, FRM));
	वापस 0;
पूर्ण

अटल पूर्णांक
base907c_xlut_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 6)))
		वापस ret;

	PUSH_MTHD(push, NV907C, SET_BASE_LUT_LO,
		  NVDEF(NV907C, SET_BASE_LUT_LO, ENABLE, DISABLE));

	PUSH_MTHD(push, NV907C, SET_OUTPUT_LUT_LO,
		  NVDEF(NV907C, SET_OUTPUT_LUT_LO, ENABLE, DISABLE));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMA_LUT, 0x00000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
base907c_xlut_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 6)))
		वापस ret;

	PUSH_MTHD(push, NV907C, SET_BASE_LUT_LO,
		  NVVAL(NV907C, SET_BASE_LUT_LO, ENABLE, asyw->xlut.i.enable) |
		  NVVAL(NV907C, SET_BASE_LUT_LO, MODE, asyw->xlut.i.mode),

				SET_BASE_LUT_HI, asyw->xlut.i.offset >> 8,

				SET_OUTPUT_LUT_LO,
		  NVDEF(NV907C, SET_OUTPUT_LUT_LO, ENABLE, USE_CORE_LUT));

	PUSH_MTHD(push, NV907C, SET_CONTEXT_DMA_LUT, asyw->xlut.handle);
	वापस 0;
पूर्ण

अटल bool
base907c_ilut(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw, पूर्णांक size)
अणु
	अगर (size != 256 && size != 1024)
		वापस false;

	अगर (size == 1024)
		asyw->xlut.i.mode = NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_1025_UNITY_RANGE;
	अन्यथा
		asyw->xlut.i.mode = NV907C_SET_BASE_LUT_LO_MODE_INTERPOLATE_257_UNITY_RANGE;

	asyw->xlut.i.enable = NV907C_SET_BASE_LUT_LO_ENABLE_ENABLE;
	asyw->xlut.i.load = head907d_olut_load;
	वापस true;
पूर्ण

अटल अंतरभूत u32
csc_drm_to_base(u64 in)
अणु
	/* base takes a 19-bit 2's complement value in S3.16 क्रमmat */
	bool sign = in & BIT_ULL(63);
	u32 पूर्णांकeger = (in >> 32) & 0x7fffffff;
	u32 fraction = in & 0xffffffff;

	अगर (पूर्णांकeger >= 4) अणु
		वापस (1 << 18) - (sign ? 0 : 1);
	पूर्ण अन्यथा अणु
		u32 ret = (पूर्णांकeger << 16) | (fraction >> 16);
		अगर (sign)
			ret = -ret;
		वापस ret & GENMASK(18, 0);
	पूर्ण
पूर्ण

व्योम
base907c_csc(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw,
	     स्थिर काष्ठा drm_color_cपंचांग *cपंचांग)
अणु
	पूर्णांक i, j;

	क्रम (j = 0; j < 3; j++) अणु
		क्रम (i = 0; i < 4; i++) अणु
			u32 *val = &asyw->csc.matrix[j * 4 + i];
			/* DRM करोes not support स्थिरant offset, जबतक
			 * HW CSC करोes. Skip it. */
			अगर (i == 3) अणु
				*val = 0;
			पूर्ण अन्यथा अणु
				*val = csc_drm_to_base(cपंचांग->matrix[j * 3 + i]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
base907c_csc_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NV907C, SET_CSC_RED2RED,
		  NVDEF(NV907C, SET_CSC_RED2RED, OWNER, CORE));
	वापस 0;
पूर्ण

अटल पूर्णांक
base907c_csc_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 13)))
		वापस ret;

	PUSH_MTHD(push, NV907C, SET_CSC_RED2RED,
		  NVDEF(NV907C, SET_CSC_RED2RED, OWNER, BASE) |
		  NVVAL(NV907C, SET_CSC_RED2RED, COEFF, asyw->csc.matrix[0]),

				SET_CSC_GRN2RED, &asyw->csc.matrix[1], 11);
	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_wndw_func
base907c = अणु
	.acquire = base507c_acquire,
	.release = base507c_release,
	.sema_set = base507c_sema_set,
	.sema_clr = base507c_sema_clr,
	.ntfy_reset = base507c_ntfy_reset,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_clr = base507c_ntfy_clr,
	.ntfy_रुको_begun = base507c_ntfy_रुको_begun,
	.ilut = base907c_ilut,
	.csc = base907c_csc,
	.csc_set = base907c_csc_set,
	.csc_clr = base907c_csc_clr,
	.olut_core = true,
	.ilut_size = 1024,
	.xlut_set = base907c_xlut_set,
	.xlut_clr = base907c_xlut_clr,
	.image_set = base907c_image_set,
	.image_clr = base507c_image_clr,
	.update = base507c_update,
पूर्ण;

पूर्णांक
base907c_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस base507c_new_(&base907c, base507c_क्रमmat, drm, head, oclass,
			     0x00000002 << (head * 4), pwndw);
पूर्ण
