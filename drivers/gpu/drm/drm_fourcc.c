<शैली गुरु>
/*
 * Copyright (c) 2016 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * DRM core क्रमmat related functions
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <linux/bug.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fourcc.h>

अटल अक्षर prपूर्णांकable_अक्षर(पूर्णांक c)
अणु
	वापस isascii(c) && है_छाप(c) ? c : '?';
पूर्ण

/**
 * drm_mode_legacy_fb_क्रमmat - compute drm fourcc code from legacy description
 * @bpp: bits per pixels
 * @depth: bit depth per pixel
 *
 * Computes a drm fourcc pixel क्रमmat code क्रम the given @bpp/@depth values.
 * Useful in fbdev emulation code, since that deals in those values.
 */
uपूर्णांक32_t drm_mode_legacy_fb_क्रमmat(uपूर्णांक32_t bpp, uपूर्णांक32_t depth)
अणु
	uपूर्णांक32_t fmt = DRM_FORMAT_INVALID;

	चयन (bpp) अणु
	हाल 8:
		अगर (depth == 8)
			fmt = DRM_FORMAT_C8;
		अवरोध;

	हाल 16:
		चयन (depth) अणु
		हाल 15:
			fmt = DRM_FORMAT_XRGB1555;
			अवरोध;
		हाल 16:
			fmt = DRM_FORMAT_RGB565;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 24:
		अगर (depth == 24)
			fmt = DRM_FORMAT_RGB888;
		अवरोध;

	हाल 32:
		चयन (depth) अणु
		हाल 24:
			fmt = DRM_FORMAT_XRGB8888;
			अवरोध;
		हाल 30:
			fmt = DRM_FORMAT_XRGB2101010;
			अवरोध;
		हाल 32:
			fmt = DRM_FORMAT_ARGB8888;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस fmt;
पूर्ण
EXPORT_SYMBOL(drm_mode_legacy_fb_क्रमmat);

/**
 * drm_driver_legacy_fb_क्रमmat - compute drm fourcc code from legacy description
 * @dev: DRM device
 * @bpp: bits per pixels
 * @depth: bit depth per pixel
 *
 * Computes a drm fourcc pixel क्रमmat code क्रम the given @bpp/@depth values.
 * Unlike drm_mode_legacy_fb_क्रमmat() this looks at the drivers mode_config,
 * and depending on the &drm_mode_config.quirk_addfb_prefer_host_byte_order flag
 * it वापसs little endian byte order or host byte order framebuffer क्रमmats.
 */
uपूर्णांक32_t drm_driver_legacy_fb_क्रमmat(काष्ठा drm_device *dev,
				     uपूर्णांक32_t bpp, uपूर्णांक32_t depth)
अणु
	uपूर्णांक32_t fmt = drm_mode_legacy_fb_क्रमmat(bpp, depth);

	अगर (dev->mode_config.quirk_addfb_prefer_host_byte_order) अणु
		अगर (fmt == DRM_FORMAT_XRGB8888)
			fmt = DRM_FORMAT_HOST_XRGB8888;
		अगर (fmt == DRM_FORMAT_ARGB8888)
			fmt = DRM_FORMAT_HOST_ARGB8888;
		अगर (fmt == DRM_FORMAT_RGB565)
			fmt = DRM_FORMAT_HOST_RGB565;
		अगर (fmt == DRM_FORMAT_XRGB1555)
			fmt = DRM_FORMAT_HOST_XRGB1555;
	पूर्ण

	अगर (dev->mode_config.quirk_addfb_prefer_xbgr_30bpp &&
	    fmt == DRM_FORMAT_XRGB2101010)
		fmt = DRM_FORMAT_XBGR2101010;

	वापस fmt;
पूर्ण
EXPORT_SYMBOL(drm_driver_legacy_fb_क्रमmat);

/**
 * drm_get_क्रमmat_name - fill a string with a drm fourcc क्रमmat's name
 * @क्रमmat: क्रमmat to compute name of
 * @buf: caller-supplied buffer
 */
स्थिर अक्षर *drm_get_क्रमmat_name(uपूर्णांक32_t क्रमmat, काष्ठा drm_क्रमmat_name_buf *buf)
अणु
	snम_लिखो(buf->str, माप(buf->str),
		 "%c%c%c%c %s-endian (0x%08x)",
		 prपूर्णांकable_अक्षर(क्रमmat & 0xff),
		 prपूर्णांकable_अक्षर((क्रमmat >> 8) & 0xff),
		 prपूर्णांकable_अक्षर((क्रमmat >> 16) & 0xff),
		 prपूर्णांकable_अक्षर((क्रमmat >> 24) & 0x7f),
		 क्रमmat & DRM_FORMAT_BIG_ENDIAN ? "big" : "little",
		 क्रमmat);

	वापस buf->str;
पूर्ण
EXPORT_SYMBOL(drm_get_क्रमmat_name);

/*
 * Internal function to query inक्रमmation क्रम a given क्रमmat. See
 * drm_क्रमmat_info() क्रम the खुला API.
 */
स्थिर काष्ठा drm_क्रमmat_info *__drm_क्रमmat_info(u32 क्रमmat)
अणु
	अटल स्थिर काष्ठा drm_क्रमmat_info क्रमmats[] = अणु
		अणु .क्रमmat = DRM_FORMAT_C8,		.depth = 8,  .num_planes = 1, .cpp = अणु 1, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGB332,		.depth = 8,  .num_planes = 1, .cpp = अणु 1, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGR233,		.depth = 8,  .num_planes = 1, .cpp = अणु 1, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBX4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRX4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ARGB4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ABGR4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBA4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRA4444,	.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB1555,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR1555,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBX5551,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRX5551,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ARGB1555,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ABGR1555,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBA5551,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRA5551,	.depth = 15, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGB565,		.depth = 16, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGR565,		.depth = 16, .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGB888,		.depth = 24, .num_planes = 1, .cpp = अणु 3, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGR888,		.depth = 24, .num_planes = 1, .cpp = अणु 3, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB8888,	.depth = 24, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR8888,	.depth = 24, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBX8888,	.depth = 24, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRX8888,	.depth = 24, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGB565_A8,	.depth = 24, .num_planes = 2, .cpp = अणु 2, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGR565_A8,	.depth = 24, .num_planes = 2, .cpp = अणु 2, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB2101010,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR2101010,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBX1010102,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRX1010102,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ARGB2101010,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ABGR2101010,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBA1010102,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRA1010102,	.depth = 30, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ARGB8888,	.depth = 32, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ABGR8888,	.depth = 32, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBA8888,	.depth = 32, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRA8888,	.depth = 32, .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB16161616F,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR16161616F,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1 पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ARGB16161616F,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_ABGR16161616F,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_AXBXGXRX106106106106, .depth = 0, .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGB888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 3, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGR888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 3, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XRGB8888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 4, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XBGR8888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 4, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_RGBX8888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 4, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_BGRX8888_A8,	.depth = 32, .num_planes = 2, .cpp = अणु 4, 1, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV410,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 4, .vsub = 4, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVU410,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 4, .vsub = 4, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV411,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 4, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVU411,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 4, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV420,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVU420,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV422,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVU422,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV444,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVU444,		.depth = 0,  .num_planes = 3, .cpp = अणु 1, 1, 1 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV12,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV21,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV16,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV61,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV24,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV42,		.depth = 0,  .num_planes = 2, .cpp = अणु 1, 2, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUYV,		.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YVYU,		.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_UYVY,		.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_VYUY,		.depth = 0,  .num_planes = 1, .cpp = अणु 2, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XYUV8888,	.depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_VUY888,          .depth = 0,  .num_planes = 1, .cpp = अणु 3, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_AYUV,		.depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y210,            .depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y212,            .depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y216,            .depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y410,            .depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y412,            .depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y416,            .depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XVYU2101010,	.depth = 0,  .num_planes = 1, .cpp = अणु 4, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XVYU12_16161616,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_XVYU16161616,	.depth = 0,  .num_planes = 1, .cpp = अणु 8, 0, 0 पूर्ण, .hsub = 1, .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y0L0,		.depth = 0,  .num_planes = 1,
		  .अक्षर_per_block = अणु 8, 0, 0 पूर्ण, .block_w = अणु 2, 0, 0 पूर्ण, .block_h = अणु 2, 0, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_X0L0,		.depth = 0,  .num_planes = 1,
		  .अक्षर_per_block = अणु 8, 0, 0 पूर्ण, .block_w = अणु 2, 0, 0 पूर्ण, .block_h = अणु 2, 0, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Y0L2,		.depth = 0,  .num_planes = 1,
		  .अक्षर_per_block = अणु 8, 0, 0 पूर्ण, .block_w = अणु 2, 0, 0 पूर्ण, .block_h = अणु 2, 0, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .has_alpha = true, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_X0L2,		.depth = 0,  .num_planes = 1,
		  .अक्षर_per_block = अणु 8, 0, 0 पूर्ण, .block_w = अणु 2, 0, 0 पूर्ण, .block_h = अणु 2, 0, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_P010,            .depth = 0,  .num_planes = 2,
		  .अक्षर_per_block = अणु 2, 4, 0 पूर्ण, .block_w = अणु 1, 1, 0 पूर्ण, .block_h = अणु 1, 1, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .is_yuv = trueपूर्ण,
		अणु .क्रमmat = DRM_FORMAT_P012,		.depth = 0,  .num_planes = 2,
		  .अक्षर_per_block = अणु 2, 4, 0 पूर्ण, .block_w = अणु 1, 1, 0 पूर्ण, .block_h = अणु 1, 1, 0 पूर्ण,
		   .hsub = 2, .vsub = 2, .is_yuv = trueपूर्ण,
		अणु .क्रमmat = DRM_FORMAT_P016,		.depth = 0,  .num_planes = 2,
		  .अक्षर_per_block = अणु 2, 4, 0 पूर्ण, .block_w = अणु 1, 1, 0 पूर्ण, .block_h = अणु 1, 1, 0 पूर्ण,
		  .hsub = 2, .vsub = 2, .is_yuv = trueपूर्ण,
		अणु .क्रमmat = DRM_FORMAT_P210,		.depth = 0,
		  .num_planes = 2, .अक्षर_per_block = अणु 2, 4, 0 पूर्ण,
		  .block_w = अणु 1, 1, 0 पूर्ण, .block_h = अणु 1, 1, 0 पूर्ण, .hsub = 2,
		  .vsub = 1, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_VUY101010,	.depth = 0,
		  .num_planes = 1, .cpp = अणु 0, 0, 0 पूर्ण, .hsub = 1, .vsub = 1,
		  .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV420_8BIT,     .depth = 0,
		  .num_planes = 1, .cpp = अणु 0, 0, 0 पूर्ण, .hsub = 2, .vsub = 2,
		  .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_YUV420_10BIT,    .depth = 0,
		  .num_planes = 1, .cpp = अणु 0, 0, 0 पूर्ण, .hsub = 2, .vsub = 2,
		  .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_NV15,		.depth = 0,
		  .num_planes = 2, .अक्षर_per_block = अणु 5, 5, 0 पूर्ण,
		  .block_w = अणु 4, 2, 0 पूर्ण, .block_h = अणु 1, 1, 0 पूर्ण, .hsub = 2,
		  .vsub = 2, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Q410,		.depth = 0,
		  .num_planes = 3, .अक्षर_per_block = अणु 2, 2, 2 पूर्ण,
		  .block_w = अणु 1, 1, 1 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण, .hsub = 0,
		  .vsub = 0, .is_yuv = true पूर्ण,
		अणु .क्रमmat = DRM_FORMAT_Q401,		.depth = 0,
		  .num_planes = 3, .अक्षर_per_block = अणु 2, 2, 2 पूर्ण,
		  .block_w = अणु 1, 1, 1 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण, .hsub = 0,
		  .vsub = 0, .is_yuv = true पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (क्रमmats[i].क्रमmat == क्रमmat)
			वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * drm_क्रमmat_info - query inक्रमmation क्रम a given क्रमmat
 * @क्रमmat: pixel क्रमmat (DRM_FORMAT_*)
 *
 * The caller should only pass a supported pixel क्रमmat to this function.
 * Unsupported pixel क्रमmats will generate a warning in the kernel log.
 *
 * Returns:
 * The instance of काष्ठा drm_क्रमmat_info that describes the pixel क्रमmat, or
 * शून्य अगर the क्रमmat is unsupported.
 */
स्थिर काष्ठा drm_क्रमmat_info *drm_क्रमmat_info(u32 क्रमmat)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;

	info = __drm_क्रमmat_info(क्रमmat);
	WARN_ON(!info);
	वापस info;
पूर्ण
EXPORT_SYMBOL(drm_क्रमmat_info);

/**
 * drm_get_क्रमmat_info - query inक्रमmation क्रम a given framebuffer configuration
 * @dev: DRM device
 * @mode_cmd: metadata from the userspace fb creation request
 *
 * Returns:
 * The instance of काष्ठा drm_क्रमmat_info that describes the pixel क्रमmat, or
 * शून्य अगर the क्रमmat is unsupported.
 */
स्थिर काष्ठा drm_क्रमmat_info *
drm_get_क्रमmat_info(काष्ठा drm_device *dev,
		    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = शून्य;

	अगर (dev->mode_config.funcs->get_क्रमmat_info)
		info = dev->mode_config.funcs->get_क्रमmat_info(mode_cmd);

	अगर (!info)
		info = drm_क्रमmat_info(mode_cmd->pixel_क्रमmat);

	वापस info;
पूर्ण
EXPORT_SYMBOL(drm_get_क्रमmat_info);

/**
 * drm_क्रमmat_info_block_width - width in pixels of block.
 * @info: pixel क्रमmat info
 * @plane: plane index
 *
 * Returns:
 * The width in pixels of a block, depending on the plane index.
 */
अचिन्हित पूर्णांक drm_क्रमmat_info_block_width(स्थिर काष्ठा drm_क्रमmat_info *info,
					 पूर्णांक plane)
अणु
	अगर (!info || plane < 0 || plane >= info->num_planes)
		वापस 0;

	अगर (!info->block_w[plane])
		वापस 1;
	वापस info->block_w[plane];
पूर्ण
EXPORT_SYMBOL(drm_क्रमmat_info_block_width);

/**
 * drm_क्रमmat_info_block_height - height in pixels of a block
 * @info: pixel क्रमmat info
 * @plane: plane index
 *
 * Returns:
 * The height in pixels of a block, depending on the plane index.
 */
अचिन्हित पूर्णांक drm_क्रमmat_info_block_height(स्थिर काष्ठा drm_क्रमmat_info *info,
					  पूर्णांक plane)
अणु
	अगर (!info || plane < 0 || plane >= info->num_planes)
		वापस 0;

	अगर (!info->block_h[plane])
		वापस 1;
	वापस info->block_h[plane];
पूर्ण
EXPORT_SYMBOL(drm_क्रमmat_info_block_height);

/**
 * drm_क्रमmat_info_min_pitch - computes the minimum required pitch in bytes
 * @info: pixel क्रमmat info
 * @plane: plane index
 * @buffer_width: buffer width in pixels
 *
 * Returns:
 * The minimum required pitch in bytes क्रम a buffer by taking पूर्णांकo consideration
 * the pixel क्रमmat inक्रमmation and the buffer width.
 */
uपूर्णांक64_t drm_क्रमmat_info_min_pitch(स्थिर काष्ठा drm_क्रमmat_info *info,
				   पूर्णांक plane, अचिन्हित पूर्णांक buffer_width)
अणु
	अगर (!info || plane < 0 || plane >= info->num_planes)
		वापस 0;

	वापस DIV_ROUND_UP_ULL((u64)buffer_width * info->अक्षर_per_block[plane],
			    drm_क्रमmat_info_block_width(info, plane) *
			    drm_क्रमmat_info_block_height(info, plane));
पूर्ण
EXPORT_SYMBOL(drm_क्रमmat_info_min_pitch);
