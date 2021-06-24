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
#समावेश "wndw.h"
#समावेश "atom.h"

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <nouveau_bo.h>

#समावेश <nvअगर/clc37e.h>
#समावेश <nvअगर/pushc37b.h>

#समावेश <nvhw/class/clc57e.h>

अटल पूर्णांक
wndwc57e_image_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 17)))
		वापस ret;

	PUSH_MTHD(push, NVC57E, SET_PRESENT_CONTROL,
		  NVVAL(NVC57E, SET_PRESENT_CONTROL, MIN_PRESENT_INTERVAL, asyw->image.पूर्णांकerval) |
		  NVVAL(NVC57E, SET_PRESENT_CONTROL, BEGIN_MODE, asyw->image.mode) |
		  NVDEF(NVC57E, SET_PRESENT_CONTROL, TIMESTAMP_MODE, DISABLE));

	PUSH_MTHD(push, NVC57E, SET_SIZE,
		  NVVAL(NVC57E, SET_SIZE, WIDTH, asyw->image.w) |
		  NVVAL(NVC57E, SET_SIZE, HEIGHT, asyw->image.h),

				SET_STORAGE,
		  NVVAL(NVC57E, SET_STORAGE, BLOCK_HEIGHT, asyw->image.blockh) |
		  NVVAL(NVC57E, SET_STORAGE, MEMORY_LAYOUT, asyw->image.layout),

				SET_PARAMS,
		  NVVAL(NVC57E, SET_PARAMS, FORMAT, asyw->image.क्रमmat) |
		  NVDEF(NVC57E, SET_PARAMS, CLAMP_BEFORE_BLEND, DISABLE) |
		  NVDEF(NVC57E, SET_PARAMS, SWAP_UV, DISABLE) |
		  NVDEF(NVC57E, SET_PARAMS, FMT_ROUNDING_MODE, ROUND_TO_NEAREST),

				SET_PLANAR_STORAGE(0),
		  NVVAL(NVC57E, SET_PLANAR_STORAGE, PITCH, asyw->image.blocks[0]) |
		  NVVAL(NVC57E, SET_PLANAR_STORAGE, PITCH, asyw->image.pitch[0] >> 6));

	PUSH_MTHD(push, NVC57E, SET_CONTEXT_DMA_ISO(0), asyw->image.handle, 1);
	PUSH_MTHD(push, NVC57E, SET_OFFSET(0), asyw->image.offset[0] >> 8);

	PUSH_MTHD(push, NVC57E, SET_POINT_IN(0),
		  NVVAL(NVC57E, SET_POINT_IN, X, asyw->state.src_x >> 16) |
		  NVVAL(NVC57E, SET_POINT_IN, Y, asyw->state.src_y >> 16));

	PUSH_MTHD(push, NVC57E, SET_SIZE_IN,
		  NVVAL(NVC57E, SET_SIZE_IN, WIDTH, asyw->state.src_w >> 16) |
		  NVVAL(NVC57E, SET_SIZE_IN, HEIGHT, asyw->state.src_h >> 16));

	PUSH_MTHD(push, NVC57E, SET_SIZE_OUT,
		  NVVAL(NVC57E, SET_SIZE_OUT, WIDTH, asyw->state.crtc_w) |
		  NVVAL(NVC57E, SET_SIZE_OUT, HEIGHT, asyw->state.crtc_h));
	वापस 0;
पूर्ण

पूर्णांक
wndwc57e_csc_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	स्थिर u32 identity[12] = अणु
		0x00010000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00010000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00010000, 0x00000000,
	पूर्ण;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 1 + ARRAY_SIZE(identity))))
		वापस ret;

	PUSH_MTHD(push, NVC57E, SET_FMT_COEFFICIENT_C00, identity, ARRAY_SIZE(identity));
	वापस 0;
पूर्ण

पूर्णांक
wndwc57e_csc_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 13)))
		वापस ret;

	PUSH_MTHD(push, NVC57E, SET_FMT_COEFFICIENT_C00, asyw->csc.matrix, 12);
	वापस 0;
पूर्ण

पूर्णांक
wndwc57e_ilut_clr(काष्ठा nv50_wndw *wndw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 2)))
		वापस ret;

	PUSH_MTHD(push, NVC57E, SET_CONTEXT_DMA_ILUT, 0x00000000);
	वापस 0;
पूर्ण

पूर्णांक
wndwc57e_ilut_set(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_push *push = wndw->wndw.push;
	पूर्णांक ret;

	अगर ((ret = PUSH_WAIT(push, 4)))
		वापस ret;

	PUSH_MTHD(push, NVC57E, SET_ILUT_CONTROL,
		  NVVAL(NVC57E, SET_ILUT_CONTROL, SIZE, asyw->xlut.i.size) |
		  NVVAL(NVC57E, SET_ILUT_CONTROL, MODE, asyw->xlut.i.mode) |
		  NVVAL(NVC57E, SET_ILUT_CONTROL, INTERPOLATE, asyw->xlut.i.output_mode),

				SET_CONTEXT_DMA_ILUT, asyw->xlut.handle,
				SET_OFFSET_ILUT, asyw->xlut.i.offset >> 8);
	वापस 0;
पूर्ण

अटल u16
fixedU0_16_FP16(u16 fixed)
अणु
        पूर्णांक sign = 0, exp = 0, man = 0;
        अगर (fixed) अणु
                जबतक (--exp && !(fixed & 0x8000))
                        fixed <<= 1;
                man = ((fixed << 1) & 0xffc0) >> 6;
                exp += 15;
        पूर्ण
        वापस (sign << 15) | (exp << 10) | man;
पूर्ण

अटल व्योम
wndwc57e_ilut_load(काष्ठा drm_color_lut *in, पूर्णांक size, व्योम __iomem *mem)
अणु
	स_रखो_io(mem, 0x00, 0x20); /* VSS header. */
	mem += 0x20;

	क्रम (; size--; in++, mem += 0x08) अणु
		u16 r = fixedU0_16_FP16(drm_color_lut_extract(in->  red, 16));
		u16 g = fixedU0_16_FP16(drm_color_lut_extract(in->green, 16));
		u16 b = fixedU0_16_FP16(drm_color_lut_extract(in-> blue, 16));
		ग_लिखोw(r, mem + 0);
		ग_लिखोw(g, mem + 2);
		ग_लिखोw(b, mem + 4);
	पूर्ण

	/* INTERPOLATE modes require a "next" entry to पूर्णांकerpolate with,
	 * so we replicate the last entry to deal with this क्रम now.
	 */
	ग_लिखोw(पढ़ोw(mem - 8), mem + 0);
	ग_लिखोw(पढ़ोw(mem - 6), mem + 2);
	ग_लिखोw(पढ़ोw(mem - 4), mem + 4);
पूर्ण

bool
wndwc57e_ilut(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw, पूर्णांक size)
अणु
	अगर (size = size ? size : 1024, size != 256 && size != 1024)
		वापस false;

	अगर (size == 256)
		asyw->xlut.i.mode = NVC57E_SET_ILUT_CONTROL_MODE_सूचीECT8;
	अन्यथा
		asyw->xlut.i.mode = NVC57E_SET_ILUT_CONTROL_MODE_सूचीECT10;

	asyw->xlut.i.size = 4 /* VSS header. */ + size + 1 /* Entries. */;
	asyw->xlut.i.output_mode = NVC57E_SET_ILUT_CONTROL_INTERPOLATE_DISABLE;
	asyw->xlut.i.load = wndwc57e_ilut_load;
	वापस true;
पूर्ण

/****************************************************************
 *            Log2(block height) ----------------------------+  *
 *            Page Kind ----------------------------------+  |  *
 *            Gob Height/Page Kind Generation ------+     |  |  *
 *                          Sector layout -------+  |     |  |  *
 *                          Compression ------+  |  |     |  |  */
स्थिर u64 wndwc57e_modअगरiers[] = अणु /*         |  |  |     |  |  */
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 0),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 1),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 2),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 3),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 4),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 2, 0x06, 5),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर काष्ठा nv50_wndw_func
wndwc57e = अणु
	.acquire = wndwc37e_acquire,
	.release = wndwc37e_release,
	.sema_set = wndwc37e_sema_set,
	.sema_clr = wndwc37e_sema_clr,
	.ntfy_set = wndwc37e_ntfy_set,
	.ntfy_clr = wndwc37e_ntfy_clr,
	.ntfy_reset = corec37d_ntfy_init,
	.ntfy_रुको_begun = base507c_ntfy_रुको_begun,
	.ilut = wndwc57e_ilut,
	.ilut_identity = true,
	.ilut_size = 1024,
	.xlut_set = wndwc57e_ilut_set,
	.xlut_clr = wndwc57e_ilut_clr,
	.csc = base907c_csc,
	.csc_set = wndwc57e_csc_set,
	.csc_clr = wndwc57e_csc_clr,
	.image_set = wndwc57e_image_set,
	.image_clr = wndwc37e_image_clr,
	.blend_set = wndwc37e_blend_set,
	.update = wndwc37e_update,
पूर्ण;

पूर्णांक
wndwc57e_new(काष्ठा nouveau_drm *drm, क्रमागत drm_plane_type type, पूर्णांक index,
	     s32 oclass, काष्ठा nv50_wndw **pwndw)
अणु
	वापस wndwc37e_new_(&wndwc57e, drm, type, index, oclass,
			     BIT(index >> 1), pwndw);
पूर्ण
