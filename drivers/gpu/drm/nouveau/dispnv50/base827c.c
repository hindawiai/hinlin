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

#समावेश <nvhw/class/cl827c.h>

अटल पूर्णांक
base827c_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 13)))
		वापस ret;

	PUSH_MTHD(push, NV827C, SET_PRESENT_CONTROL,
		  NVVAL(NV827C, SET_PRESENT_CONTROL, BEGIN_MODE, asyw->image.mode) |
		  NVVAL(NV827C, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval));

	PUSH_MTHD(push, NV827C, SET_CONTEXT_DMAS_ISO(0), asyw->image.handle, 1);

	अगर (asyw->image.क्रमmat == NV827C_SURFACE_SET_PARAMS_FORMAT_RF16_GF16_BF16_AF16) अणु
		PUSH_MTHD(push, NV827C, SET_PROCESSING,
			  NVDEF(NV827C, SET_PROCESSING, USE_GAIN_OFS, ENABLE),

					SET_CONVERSION,
			  NVVAL(NV827C, SET_CONVERSION, GAIN, 0) |
			  NVVAL(NV827C, SET_CONVERSION, OFS, 0x64));
	पूर्ण अन्यथा अणु
		PUSH_MTHD(push, NV827C, SET_PROCESSING,
			  NVDEF(NV827C, SET_PROCESSING, USE_GAIN_OFS, DISABLE),

					SET_CONVERSION,
			  NVVAL(NV827C, SET_CONVERSION, GAIN, 0) |
			  NVVAL(NV827C, SET_CONVERSION, OFS, 0));
	पूर्ण

	PUSH_MTHD(push, NV827C, SURFACE_SET_OFFSET(0, 0), asyw->image.offset[0] >> 8,
				SURFACE_SET_OFFSET(0, 1), 0x00000000,

				SURFACE_SET_SIZE(0),
		  NVVAL(NV827C, SURFACE_SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NV827C, SURFACE_SET_SIZE, HEIGHT, asyw->image.h),

				SURFACE_SET_STORAGE(0),
		  NVVAL(NV827C, SURFACE_SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh) |
		  NVVAL(NV827C, SURFACE_SET_STORAGE, PITCH, asyw->image.pitch[0] >> 8) |
		  NVVAL(NV827C, SURFACE_SET_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NV827C, SURFACE_SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout),

				SURFACE_SET_PARAMS(0),
		  NVVAL(NV827C, SURFACE_SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVDEF(NV827C, SURFACE_SET_PARAMS, SUPER_SAMPLE, X1_AA) |
		  NVDEF(NV827C, SURFACE_SET_PARAMS, GAMMA, LINEAR) |
		  NVDEF(NV827C, SURFACE_SET_PARAMS, LAYOUT, FRM));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_wndw_func
base827c = अणु
	.acquire = base507c_acquire,
	.release = base507c_release,
	.sema_set = base507c_sema_set,
	.sema_clr = base507c_sema_clr,
	.ntfy_reset = base507c_ntfy_reset,
	.ntfy_set = base507c_ntfy_set,
	.ntfy_clr = base507c_ntfy_clr,
	.ntfy_रुको_begun = base507c_ntfy_रुको_begun,
	.olut_core = 1,
	.xlut_set = base507c_xlut_set,
	.xlut_clr = base507c_xlut_clr,
	.image_set = base827c_image_set,
	.image_clr = base507c_image_clr,
	.update = base507c_update,
पूर्ण;

पूर्णांक
base827c_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस base507c_new_(&base827c, base507c_क्रमmat, drm, head, oclass,
			     0x00000002 << (head * 8), pwndw);
पूर्ण
