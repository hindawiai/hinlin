<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Xu Han <xu.han@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Xiaoguang Chen <xiaoguang.chen@पूर्णांकel.com>
 *    Yang Liu <yang2.liu@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *
 */

#समावेश <uapi/drm/drm_fourcc.h>
#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "i915_pvinfo.h"

#घोषणा PRIMARY_FORMAT_NUM	16
काष्ठा pixel_क्रमmat अणु
	पूर्णांक	drm_क्रमmat;	/* Pixel क्रमmat in DRM definition */
	पूर्णांक	bpp;		/* Bits per pixel, 0 indicates invalid */
	अक्षर	*desc;		/* The description */
पूर्ण;

अटल काष्ठा pixel_क्रमmat bdw_pixel_क्रमmats[] = अणु
	अणुDRM_FORMAT_C8, 8, "8-bit Indexed"पूर्ण,
	अणुDRM_FORMAT_RGB565, 16, "16-bit BGRX (5:6:5 MSB-R:G:B)"पूर्ण,
	अणुDRM_FORMAT_XRGB8888, 32, "32-bit BGRX (8:8:8:8 MSB-X:R:G:B)"पूर्ण,
	अणुDRM_FORMAT_XBGR2101010, 32, "32-bit RGBX (2:10:10:10 MSB-X:B:G:R)"पूर्ण,

	अणुDRM_FORMAT_XRGB2101010, 32, "32-bit BGRX (2:10:10:10 MSB-X:R:G:B)"पूर्ण,
	अणुDRM_FORMAT_XBGR8888, 32, "32-bit RGBX (8:8:8:8 MSB-X:B:G:R)"पूर्ण,

	/* non-supported क्रमmat has bpp शेष to 0 */
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

अटल काष्ठा pixel_क्रमmat skl_pixel_क्रमmats[] = अणु
	अणुDRM_FORMAT_YUYV, 16, "16-bit packed YUYV (8:8:8:8 MSB-V:Y2:U:Y1)"पूर्ण,
	अणुDRM_FORMAT_UYVY, 16, "16-bit packed UYVY (8:8:8:8 MSB-Y2:V:Y1:U)"पूर्ण,
	अणुDRM_FORMAT_YVYU, 16, "16-bit packed YVYU (8:8:8:8 MSB-U:Y2:V:Y1)"पूर्ण,
	अणुDRM_FORMAT_VYUY, 16, "16-bit packed VYUY (8:8:8:8 MSB-Y2:U:Y1:V)"पूर्ण,

	अणुDRM_FORMAT_C8, 8, "8-bit Indexed"पूर्ण,
	अणुDRM_FORMAT_RGB565, 16, "16-bit BGRX (5:6:5 MSB-R:G:B)"पूर्ण,
	अणुDRM_FORMAT_ABGR8888, 32, "32-bit RGBA (8:8:8:8 MSB-A:B:G:R)"पूर्ण,
	अणुDRM_FORMAT_XBGR8888, 32, "32-bit RGBX (8:8:8:8 MSB-X:B:G:R)"पूर्ण,

	अणुDRM_FORMAT_ARGB8888, 32, "32-bit BGRA (8:8:8:8 MSB-A:R:G:B)"पूर्ण,
	अणुDRM_FORMAT_XRGB8888, 32, "32-bit BGRX (8:8:8:8 MSB-X:R:G:B)"पूर्ण,
	अणुDRM_FORMAT_XBGR2101010, 32, "32-bit RGBX (2:10:10:10 MSB-X:B:G:R)"पूर्ण,
	अणुDRM_FORMAT_XRGB2101010, 32, "32-bit BGRX (2:10:10:10 MSB-X:R:G:B)"पूर्ण,

	/* non-supported क्रमmat has bpp शेष to 0 */
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक bdw_क्रमmat_to_drm(पूर्णांक क्रमmat)
अणु
	पूर्णांक bdw_pixel_क्रमmats_index = 6;

	चयन (क्रमmat) अणु
	हाल DISPPLANE_8BPP:
		bdw_pixel_क्रमmats_index = 0;
		अवरोध;
	हाल DISPPLANE_BGRX565:
		bdw_pixel_क्रमmats_index = 1;
		अवरोध;
	हाल DISPPLANE_BGRX888:
		bdw_pixel_क्रमmats_index = 2;
		अवरोध;
	हाल DISPPLANE_RGBX101010:
		bdw_pixel_क्रमmats_index = 3;
		अवरोध;
	हाल DISPPLANE_BGRX101010:
		bdw_pixel_क्रमmats_index = 4;
		अवरोध;
	हाल DISPPLANE_RGBX888:
		bdw_pixel_क्रमmats_index = 5;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस bdw_pixel_क्रमmats_index;
पूर्ण

अटल पूर्णांक skl_क्रमmat_to_drm(पूर्णांक क्रमmat, bool rgb_order, bool alpha,
	पूर्णांक yuv_order)
अणु
	पूर्णांक skl_pixel_क्रमmats_index = 12;

	चयन (क्रमmat) अणु
	हाल PLANE_CTL_FORMAT_INDEXED:
		skl_pixel_क्रमmats_index = 4;
		अवरोध;
	हाल PLANE_CTL_FORMAT_RGB_565:
		skl_pixel_क्रमmats_index = 5;
		अवरोध;
	हाल PLANE_CTL_FORMAT_XRGB_8888:
		अगर (rgb_order)
			skl_pixel_क्रमmats_index = alpha ? 6 : 7;
		अन्यथा
			skl_pixel_क्रमmats_index = alpha ? 8 : 9;
		अवरोध;
	हाल PLANE_CTL_FORMAT_XRGB_2101010:
		skl_pixel_क्रमmats_index = rgb_order ? 10 : 11;
		अवरोध;
	हाल PLANE_CTL_FORMAT_YUV422:
		skl_pixel_क्रमmats_index = yuv_order >> 16;
		अगर (skl_pixel_क्रमmats_index > 3)
			वापस -EINVAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस skl_pixel_क्रमmats_index;
पूर्ण

अटल u32 पूर्णांकel_vgpu_get_stride(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक pipe,
	u32 tiled, पूर्णांक stride_mask, पूर्णांक bpp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;

	u32 stride_reg = vgpu_vreg_t(vgpu, DSPSTRIDE(pipe)) & stride_mask;
	u32 stride = stride_reg;

	अगर (INTEL_GEN(dev_priv) >= 9) अणु
		चयन (tiled) अणु
		हाल PLANE_CTL_TILED_LINEAR:
			stride = stride_reg * 64;
			अवरोध;
		हाल PLANE_CTL_TILED_X:
			stride = stride_reg * 512;
			अवरोध;
		हाल PLANE_CTL_TILED_Y:
			stride = stride_reg * 128;
			अवरोध;
		हाल PLANE_CTL_TILED_YF:
			अगर (bpp == 8)
				stride = stride_reg * 64;
			अन्यथा अगर (bpp == 16 || bpp == 32 || bpp == 64)
				stride = stride_reg * 128;
			अन्यथा
				gvt_dbg_core("skl: unsupported bpp:%d\n", bpp);
			अवरोध;
		शेष:
			gvt_dbg_core("skl: unsupported tile format:%x\n",
				tiled);
		पूर्ण
	पूर्ण

	वापस stride;
पूर्ण

अटल पूर्णांक get_active_pipe(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < I915_MAX_PIPES; i++)
		अगर (pipe_is_enabled(vgpu, i))
			अवरोध;

	वापस i;
पूर्ण

/**
 * पूर्णांकel_vgpu_decode_primary_plane - Decode primary plane
 * @vgpu: input vgpu
 * @plane: primary plane to save decoded info
 * This function is called क्रम decoding plane
 *
 * Returns:
 * 0 on success, non-zero अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_decode_primary_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_primary_plane_क्रमmat *plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	u32 val, fmt;
	पूर्णांक pipe;

	pipe = get_active_pipe(vgpu);
	अगर (pipe >= I915_MAX_PIPES)
		वापस -ENODEV;

	val = vgpu_vreg_t(vgpu, DSPCNTR(pipe));
	plane->enabled = !!(val & DISPLAY_PLANE_ENABLE);
	अगर (!plane->enabled)
		वापस -ENODEV;

	अगर (INTEL_GEN(dev_priv) >= 9) अणु
		plane->tiled = val & PLANE_CTL_TILED_MASK;
		fmt = skl_क्रमmat_to_drm(
			val & PLANE_CTL_FORMAT_MASK,
			val & PLANE_CTL_ORDER_RGBX,
			val & PLANE_CTL_ALPHA_MASK,
			val & PLANE_CTL_YUV422_ORDER_MASK);

		अगर (fmt >= ARRAY_SIZE(skl_pixel_क्रमmats)) अणु
			gvt_vgpu_err("Out-of-bounds pixel format index\n");
			वापस -EINVAL;
		पूर्ण

		plane->bpp = skl_pixel_क्रमmats[fmt].bpp;
		plane->drm_क्रमmat = skl_pixel_क्रमmats[fmt].drm_क्रमmat;
	पूर्ण अन्यथा अणु
		plane->tiled = val & DISPPLANE_TILED;
		fmt = bdw_क्रमmat_to_drm(val & DISPPLANE_PIXFORMAT_MASK);
		plane->bpp = bdw_pixel_क्रमmats[fmt].bpp;
		plane->drm_क्रमmat = bdw_pixel_क्रमmats[fmt].drm_क्रमmat;
	पूर्ण

	अगर (!plane->bpp) अणु
		gvt_vgpu_err("Non-supported pixel format (0x%x)\n", fmt);
		वापस -EINVAL;
	पूर्ण

	plane->hw_क्रमmat = fmt;

	plane->base = vgpu_vreg_t(vgpu, DSPSURF(pipe)) & I915_GTT_PAGE_MASK;
	अगर (!vgpu_gmadr_is_valid(vgpu, plane->base))
		वापस  -EINVAL;

	plane->base_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, plane->base);
	अगर (plane->base_gpa == INTEL_GVT_INVALID_ADDR) अणु
		gvt_vgpu_err("Translate primary plane gma 0x%x to gpa fail\n",
				plane->base);
		वापस  -EINVAL;
	पूर्ण

	plane->stride = पूर्णांकel_vgpu_get_stride(vgpu, pipe, plane->tiled,
		(INTEL_GEN(dev_priv) >= 9) ?
			(_PRI_PLANE_STRIDE_MASK >> 6) :
				_PRI_PLANE_STRIDE_MASK, plane->bpp);

	plane->width = (vgpu_vreg_t(vgpu, PIPESRC(pipe)) & _PIPE_H_SRCSZ_MASK) >>
		_PIPE_H_SRCSZ_SHIFT;
	plane->width += 1;
	plane->height = (vgpu_vreg_t(vgpu, PIPESRC(pipe)) &
			_PIPE_V_SRCSZ_MASK) >> _PIPE_V_SRCSZ_SHIFT;
	plane->height += 1;	/* raw height is one minus the real value */

	val = vgpu_vreg_t(vgpu, DSPTILखातापूर्णF(pipe));
	plane->x_offset = (val & _PRI_PLANE_X_OFF_MASK) >>
		_PRI_PLANE_X_OFF_SHIFT;
	plane->y_offset = (val & _PRI_PLANE_Y_OFF_MASK) >>
		_PRI_PLANE_Y_OFF_SHIFT;

	वापस 0;
पूर्ण

#घोषणा CURSOR_FORMAT_NUM	(1 << 6)
काष्ठा cursor_mode_क्रमmat अणु
	पूर्णांक	drm_क्रमmat;	/* Pixel क्रमmat in DRM definition */
	u8	bpp;		/* Bits per pixel; 0 indicates invalid */
	u32	width;		/* In pixel */
	u32	height;		/* In lines */
	अक्षर	*desc;		/* The description */
पूर्ण;

अटल काष्ठा cursor_mode_क्रमmat cursor_pixel_क्रमmats[] = अणु
	अणुDRM_FORMAT_ARGB8888, 32, 128, 128, "128x128 32bpp ARGB"पूर्ण,
	अणुDRM_FORMAT_ARGB8888, 32, 256, 256, "256x256 32bpp ARGB"पूर्ण,
	अणुDRM_FORMAT_ARGB8888, 32, 64, 64, "64x64 32bpp ARGB"पूर्ण,
	अणुDRM_FORMAT_ARGB8888, 32, 64, 64, "64x64 32bpp ARGB"पूर्ण,

	/* non-supported क्रमmat has bpp शेष to 0 */
	अणु0, 0, 0, 0, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक cursor_mode_to_drm(पूर्णांक mode)
अणु
	पूर्णांक cursor_pixel_क्रमmats_index = 4;

	चयन (mode) अणु
	हाल MCURSOR_MODE_128_ARGB_AX:
		cursor_pixel_क्रमmats_index = 0;
		अवरोध;
	हाल MCURSOR_MODE_256_ARGB_AX:
		cursor_pixel_क्रमmats_index = 1;
		अवरोध;
	हाल MCURSOR_MODE_64_ARGB_AX:
		cursor_pixel_क्रमmats_index = 2;
		अवरोध;
	हाल MCURSOR_MODE_64_32B_AX:
		cursor_pixel_क्रमmats_index = 3;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस cursor_pixel_क्रमmats_index;
पूर्ण

/**
 * पूर्णांकel_vgpu_decode_cursor_plane - Decode sprite plane
 * @vgpu: input vgpu
 * @plane: cursor plane to save decoded info
 * This function is called क्रम decoding plane
 *
 * Returns:
 * 0 on success, non-zero अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_decode_cursor_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_cursor_plane_क्रमmat *plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	u32 val, mode, index;
	u32 alpha_plane, alpha_क्रमce;
	पूर्णांक pipe;

	pipe = get_active_pipe(vgpu);
	अगर (pipe >= I915_MAX_PIPES)
		वापस -ENODEV;

	val = vgpu_vreg_t(vgpu, CURCNTR(pipe));
	mode = val & MCURSOR_MODE;
	plane->enabled = (mode != MCURSOR_MODE_DISABLE);
	अगर (!plane->enabled)
		वापस -ENODEV;

	index = cursor_mode_to_drm(mode);

	अगर (!cursor_pixel_क्रमmats[index].bpp) अणु
		gvt_vgpu_err("Non-supported cursor mode (0x%x)\n", mode);
		वापस -EINVAL;
	पूर्ण
	plane->mode = mode;
	plane->bpp = cursor_pixel_क्रमmats[index].bpp;
	plane->drm_क्रमmat = cursor_pixel_क्रमmats[index].drm_क्रमmat;
	plane->width = cursor_pixel_क्रमmats[index].width;
	plane->height = cursor_pixel_क्रमmats[index].height;

	alpha_plane = (val & _CURSOR_ALPHA_PLANE_MASK) >>
				_CURSOR_ALPHA_PLANE_SHIFT;
	alpha_क्रमce = (val & _CURSOR_ALPHA_FORCE_MASK) >>
				_CURSOR_ALPHA_FORCE_SHIFT;
	अगर (alpha_plane || alpha_क्रमce)
		gvt_dbg_core("alpha_plane=0x%x, alpha_force=0x%x\n",
			alpha_plane, alpha_क्रमce);

	plane->base = vgpu_vreg_t(vgpu, CURBASE(pipe)) & I915_GTT_PAGE_MASK;
	अगर (!vgpu_gmadr_is_valid(vgpu, plane->base))
		वापस  -EINVAL;

	plane->base_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, plane->base);
	अगर (plane->base_gpa == INTEL_GVT_INVALID_ADDR) अणु
		gvt_vgpu_err("Translate cursor plane gma 0x%x to gpa fail\n",
				plane->base);
		वापस  -EINVAL;
	पूर्ण

	val = vgpu_vreg_t(vgpu, CURPOS(pipe));
	plane->x_pos = (val & _CURSOR_POS_X_MASK) >> _CURSOR_POS_X_SHIFT;
	plane->x_sign = (val & _CURSOR_SIGN_X_MASK) >> _CURSOR_SIGN_X_SHIFT;
	plane->y_pos = (val & _CURSOR_POS_Y_MASK) >> _CURSOR_POS_Y_SHIFT;
	plane->y_sign = (val & _CURSOR_SIGN_Y_MASK) >> _CURSOR_SIGN_Y_SHIFT;

	plane->x_hot = vgpu_vreg_t(vgpu, vgtअगर_reg(cursor_x_hot));
	plane->y_hot = vgpu_vreg_t(vgpu, vgtअगर_reg(cursor_y_hot));
	वापस 0;
पूर्ण

#घोषणा SPRITE_FORMAT_NUM	(1 << 3)

अटल काष्ठा pixel_क्रमmat sprite_pixel_क्रमmats[SPRITE_FORMAT_NUM] = अणु
	[0x0] = अणुDRM_FORMAT_YUV422, 16, "YUV 16-bit 4:2:2 packed"पूर्ण,
	[0x1] = अणुDRM_FORMAT_XRGB2101010, 32, "RGB 32-bit 2:10:10:10"पूर्ण,
	[0x2] = अणुDRM_FORMAT_XRGB8888, 32, "RGB 32-bit 8:8:8:8"पूर्ण,
	[0x4] = अणुDRM_FORMAT_AYUV, 32,
		"YUV 32-bit 4:4:4 packed (8:8:8:8 MSB-X:Y:U:V)"पूर्ण,
पूर्ण;

/**
 * पूर्णांकel_vgpu_decode_sprite_plane - Decode sprite plane
 * @vgpu: input vgpu
 * @plane: sprite plane to save decoded info
 * This function is called क्रम decoding plane
 *
 * Returns:
 * 0 on success, non-zero अगर failed.
 */
पूर्णांक पूर्णांकel_vgpu_decode_sprite_plane(काष्ठा पूर्णांकel_vgpu *vgpu,
	काष्ठा पूर्णांकel_vgpu_sprite_plane_क्रमmat *plane)
अणु
	u32 val, fmt;
	u32 color_order, yuv_order;
	पूर्णांक drm_क्रमmat;
	पूर्णांक pipe;

	pipe = get_active_pipe(vgpu);
	अगर (pipe >= I915_MAX_PIPES)
		वापस -ENODEV;

	val = vgpu_vreg_t(vgpu, SPRCTL(pipe));
	plane->enabled = !!(val & SPRITE_ENABLE);
	अगर (!plane->enabled)
		वापस -ENODEV;

	plane->tiled = !!(val & SPRITE_TILED);
	color_order = !!(val & SPRITE_RGB_ORDER_RGBX);
	yuv_order = (val & SPRITE_YUV_BYTE_ORDER_MASK) >>
				_SPRITE_YUV_ORDER_SHIFT;

	fmt = (val & SPRITE_PIXFORMAT_MASK) >> _SPRITE_FMT_SHIFT;
	अगर (!sprite_pixel_क्रमmats[fmt].bpp) अणु
		gvt_vgpu_err("Non-supported pixel format (0x%x)\n", fmt);
		वापस -EINVAL;
	पूर्ण
	plane->hw_क्रमmat = fmt;
	plane->bpp = sprite_pixel_क्रमmats[fmt].bpp;
	drm_क्रमmat = sprite_pixel_क्रमmats[fmt].drm_क्रमmat;

	/* Order of RGB values in an RGBxxx buffer may be ordered RGB or
	 * BGR depending on the state of the color_order field
	 */
	अगर (!color_order) अणु
		अगर (drm_क्रमmat == DRM_FORMAT_XRGB2101010)
			drm_क्रमmat = DRM_FORMAT_XBGR2101010;
		अन्यथा अगर (drm_क्रमmat == DRM_FORMAT_XRGB8888)
			drm_क्रमmat = DRM_FORMAT_XBGR8888;
	पूर्ण

	अगर (drm_क्रमmat == DRM_FORMAT_YUV422) अणु
		चयन (yuv_order) अणु
		हाल 0:
			drm_क्रमmat = DRM_FORMAT_YUYV;
			अवरोध;
		हाल 1:
			drm_क्रमmat = DRM_FORMAT_UYVY;
			अवरोध;
		हाल 2:
			drm_क्रमmat = DRM_FORMAT_YVYU;
			अवरोध;
		हाल 3:
			drm_क्रमmat = DRM_FORMAT_VYUY;
			अवरोध;
		शेष:
			/* yuv_order has only 2 bits */
			अवरोध;
		पूर्ण
	पूर्ण

	plane->drm_क्रमmat = drm_क्रमmat;

	plane->base = vgpu_vreg_t(vgpu, SPRSURF(pipe)) & I915_GTT_PAGE_MASK;
	अगर (!vgpu_gmadr_is_valid(vgpu, plane->base))
		वापस  -EINVAL;

	plane->base_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm, plane->base);
	अगर (plane->base_gpa == INTEL_GVT_INVALID_ADDR) अणु
		gvt_vgpu_err("Translate sprite plane gma 0x%x to gpa fail\n",
				plane->base);
		वापस  -EINVAL;
	पूर्ण

	plane->stride = vgpu_vreg_t(vgpu, SPRSTRIDE(pipe)) &
				_SPRITE_STRIDE_MASK;

	val = vgpu_vreg_t(vgpu, SPRSIZE(pipe));
	plane->height = (val & _SPRITE_SIZE_HEIGHT_MASK) >>
		_SPRITE_SIZE_HEIGHT_SHIFT;
	plane->width = (val & _SPRITE_SIZE_WIDTH_MASK) >>
		_SPRITE_SIZE_WIDTH_SHIFT;
	plane->height += 1;	/* raw height is one minus the real value */
	plane->width += 1;	/* raw width is one minus the real value */

	val = vgpu_vreg_t(vgpu, SPRPOS(pipe));
	plane->x_pos = (val & _SPRITE_POS_X_MASK) >> _SPRITE_POS_X_SHIFT;
	plane->y_pos = (val & _SPRITE_POS_Y_MASK) >> _SPRITE_POS_Y_SHIFT;

	val = vgpu_vreg_t(vgpu, SPROFFSET(pipe));
	plane->x_offset = (val & _SPRITE_OFFSET_START_X_MASK) >>
			   _SPRITE_OFFSET_START_X_SHIFT;
	plane->y_offset = (val & _SPRITE_OFFSET_START_Y_MASK) >>
			   _SPRITE_OFFSET_START_Y_SHIFT;

	वापस 0;
पूर्ण
