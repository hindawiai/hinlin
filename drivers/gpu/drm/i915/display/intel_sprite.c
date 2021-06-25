<शैली गुरु>
/*
 * Copyright तऊ 2011 Intel Corporation
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
 *   Jesse Barnes <jbarnes@virtuousgeek.org>
 *
 * New plane/sprite handling.
 *
 * The older chips had a separate पूर्णांकerface क्रम programming plane related
 * रेजिस्टरs; newer ones are much simpler and we can use the new DRM plane
 * support.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_rect.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_display_types.h"
#समावेश "intel_frontbuffer.h"
#समावेश "intel_sprite.h"
#समावेश "i9xx_plane.h"
#समावेश "intel_vrr.h"

पूर्णांक पूर्णांकel_plane_check_src_coordinates(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा drm_rect *src = &plane_state->uapi.src;
	u32 src_x, src_y, src_w, src_h, hsub, vsub;
	bool rotated = drm_rotation_90_or_270(plane_state->hw.rotation);

	/*
	 * FIXME hsub/vsub vs. block size is a mess. Pre-tgl CCS
	 * abuses hsub/vsub so we can't use them here. But as they
	 * are limited to 32bpp RGB क्रमmats we करोn't actually need
	 * to check anything.
	 */
	अगर (fb->modअगरier == I915_FORMAT_MOD_Y_TILED_CCS ||
	    fb->modअगरier == I915_FORMAT_MOD_Yf_TILED_CCS)
		वापस 0;

	/*
	 * Hardware करोesn't handle subpixel coordinates.
	 * Adjust to (macro)pixel boundary, but be careful not to
	 * increase the source viewport size, because that could
	 * push the करोwnscaling factor out of bounds.
	 */
	src_x = src->x1 >> 16;
	src_w = drm_rect_width(src) >> 16;
	src_y = src->y1 >> 16;
	src_h = drm_rect_height(src) >> 16;

	drm_rect_init(src, src_x << 16, src_y << 16,
		      src_w << 16, src_h << 16);

	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_RGB565 && rotated) अणु
		hsub = 2;
		vsub = 2;
	पूर्ण अन्यथा अणु
		hsub = fb->क्रमmat->hsub;
		vsub = fb->क्रमmat->vsub;
	पूर्ण

	अगर (rotated)
		hsub = vsub = max(hsub, vsub);

	अगर (src_x % hsub || src_w % hsub) अणु
		DRM_DEBUG_KMS("src x/w (%u, %u) must be a multiple of %u (rotated: %s)\n",
			      src_x, src_w, hsub, yesno(rotated));
		वापस -EINVAL;
	पूर्ण

	अगर (src_y % vsub || src_h % vsub) अणु
		DRM_DEBUG_KMS("src y/h (%u, %u) must be a multiple of %u (rotated: %s)\n",
			      src_y, src_h, vsub, yesno(rotated));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i9xx_plane_linear_gamma(u16 gamma[8])
अणु
	/* The poपूर्णांकs are not evenly spaced. */
	अटल स्थिर u8 in[8] = अणु 0, 1, 2, 4, 8, 16, 24, 32 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		gamma[i] = (in[i] << 8) / 32;
पूर्ण

अटल व्योम
chv_update_csc(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत plane_id plane_id = plane->id;
	/*
	 * |r|   | c0 c1 c2 |   |cr|
	 * |g| = | c3 c4 c5 | x |y |
	 * |b|   | c6 c7 c8 |   |cb|
	 *
	 * Coefficients are s3.12.
	 *
	 * Cb and Cr apparently come in as चिन्हित alपढ़ोy, and
	 * we always get full range data in on account of CLRC0/1.
	 */
	अटल स्थिर s16 csc_matrix[][9] = अणु
		/* BT.601 full range YCbCr -> full range RGB */
		[DRM_COLOR_YCBCR_BT601] = अणु
			 5743, 4096,     0,
			-2925, 4096, -1410,
			    0, 4096,  7258,
		पूर्ण,
		/* BT.709 full range YCbCr -> full range RGB */
		[DRM_COLOR_YCBCR_BT709] = अणु
			 6450, 4096,     0,
			-1917, 4096,  -767,
			    0, 4096,  7601,
		पूर्ण,
	पूर्ण;
	स्थिर s16 *csc = csc_matrix[plane_state->hw.color_encoding];

	/* Seems RGB data bypasses the CSC always */
	अगर (!fb->क्रमmat->is_yuv)
		वापस;

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCYGOFF(plane_id),
			  SPCSC_OOFF(0) | SPCSC_IOFF(0));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCBOFF(plane_id),
			  SPCSC_OOFF(0) | SPCSC_IOFF(0));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCROFF(plane_id),
			  SPCSC_OOFF(0) | SPCSC_IOFF(0));

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCC01(plane_id),
			  SPCSC_C1(csc[1]) | SPCSC_C0(csc[0]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCC23(plane_id),
			  SPCSC_C1(csc[3]) | SPCSC_C0(csc[2]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCC45(plane_id),
			  SPCSC_C1(csc[5]) | SPCSC_C0(csc[4]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCC67(plane_id),
			  SPCSC_C1(csc[7]) | SPCSC_C0(csc[6]));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCC8(plane_id), SPCSC_C0(csc[8]));

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCYGICLAMP(plane_id),
			  SPCSC_IMAX(1023) | SPCSC_IMIN(0));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCBICLAMP(plane_id),
			  SPCSC_IMAX(512) | SPCSC_IMIN(-512));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCRICLAMP(plane_id),
			  SPCSC_IMAX(512) | SPCSC_IMIN(-512));

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCYGOCLAMP(plane_id),
			  SPCSC_OMAX(1023) | SPCSC_OMIN(0));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCBOCLAMP(plane_id),
			  SPCSC_OMAX(1023) | SPCSC_OMIN(0));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCSCCROCLAMP(plane_id),
			  SPCSC_OMAX(1023) | SPCSC_OMIN(0));
पूर्ण

#घोषणा SIN_0 0
#घोषणा COS_0 1

अटल व्योम
vlv_update_clrc(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	क्रमागत plane_id plane_id = plane->id;
	पूर्णांक contrast, brightness, sh_scale, sh_sin, sh_cos;

	अगर (fb->क्रमmat->is_yuv &&
	    plane_state->hw.color_range == DRM_COLOR_YCBCR_LIMITED_RANGE) अणु
		/*
		 * Expand limited range to full range:
		 * Contrast is applied first and is used to expand Y range.
		 * Brightness is applied second and is used to हटाओ the
		 * offset from Y. Saturation/hue is used to expand CbCr range.
		 */
		contrast = DIV_ROUND_CLOSEST(255 << 6, 235 - 16);
		brightness = -DIV_ROUND_CLOSEST(16 * 255, 235 - 16);
		sh_scale = DIV_ROUND_CLOSEST(128 << 7, 240 - 128);
		sh_sin = SIN_0 * sh_scale;
		sh_cos = COS_0 * sh_scale;
	पूर्ण अन्यथा अणु
		/* Pass-through everything. */
		contrast = 1 << 6;
		brightness = 0;
		sh_scale = 1 << 7;
		sh_sin = SIN_0 * sh_scale;
		sh_cos = COS_0 * sh_scale;
	पूर्ण

	/* FIXME these रेजिस्टर are single buffered :( */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCLRC0(pipe, plane_id),
			  SP_CONTRAST(contrast) | SP_BRIGHTNESS(brightness));
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCLRC1(pipe, plane_id),
			  SP_SH_SIN(sh_sin) | SP_SH_COS(sh_cos));
पूर्ण

अटल व्योम
vlv_plane_ratio(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	u8 active_planes = crtc_state->active_planes & ~BIT(PLANE_CURSOR);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];

	/*
	 * VLV bspec only considers हालs where all three planes are
	 * enabled, and हालs where the primary and one sprite is enabled.
	 * Let's assume the हाल with just two sprites enabled also
	 * maps to the latter हाल.
	 */
	अगर (hweight8(active_planes) == 3) अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 11;
			*den = 8;
			अवरोध;
		हाल 4:
			*num = 18;
			*den = 16;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (hweight8(active_planes) == 2) अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 10;
			*den = 8;
			अवरोध;
		हाल 4:
			*num = 17;
			*den = 16;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 10;
			*den = 8;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक vlv_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक pixel_rate;
	अचिन्हित पूर्णांक num, den;

	/*
	 * Note that crtc_state->pixel_rate accounts क्रम both
	 * horizontal and vertical panel fitter करोwnscaling factors.
	 * Pre-HSW bspec tells us to only consider the horizontal
	 * करोwnscaling factor here. We ignore that and just consider
	 * both क्रम simplicity.
	 */
	pixel_rate = crtc_state->pixel_rate;

	vlv_plane_ratio(crtc_state, plane_state, &num, &den);

	वापस DIV_ROUND_UP(pixel_rate * num, den);
पूर्ण

अटल u32 vlv_sprite_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 sprctl = 0;

	अगर (crtc_state->gamma_enable)
		sprctl |= SP_GAMMA_ENABLE;

	वापस sprctl;
पूर्ण

अटल u32 vlv_sprite_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	u32 sprctl;

	sprctl = SP_ENABLE;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YUYV:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_YUYV;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_YVYU;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_UYVY;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_VYUY;
		अवरोध;
	हाल DRM_FORMAT_C8:
		sprctl |= SP_FORMAT_8BPP;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		sprctl |= SP_FORMAT_BGR565;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		sprctl |= SP_FORMAT_BGRX8888;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		sprctl |= SP_FORMAT_BGRA8888;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
		sprctl |= SP_FORMAT_RGBX1010102;
		अवरोध;
	हाल DRM_FORMAT_ABGR2101010:
		sprctl |= SP_FORMAT_RGBA1010102;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
		sprctl |= SP_FORMAT_BGRX1010102;
		अवरोध;
	हाल DRM_FORMAT_ARGB2101010:
		sprctl |= SP_FORMAT_BGRA1010102;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		sprctl |= SP_FORMAT_RGBX8888;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
		sprctl |= SP_FORMAT_RGBA8888;
		अवरोध;
	शेष:
		MISSING_CASE(fb->क्रमmat->क्रमmat);
		वापस 0;
	पूर्ण

	अगर (plane_state->hw.color_encoding == DRM_COLOR_YCBCR_BT709)
		sprctl |= SP_YUV_FORMAT_BT709;

	अगर (fb->modअगरier == I915_FORMAT_MOD_X_TILED)
		sprctl |= SP_TILED;

	अगर (rotation & DRM_MODE_ROTATE_180)
		sprctl |= SP_ROTATE_180;

	अगर (rotation & DRM_MODE_REFLECT_X)
		sprctl |= SP_MIRROR;

	अगर (key->flags & I915_SET_COLORKEY_SOURCE)
		sprctl |= SP_SOURCE_KEY;

	वापस sprctl;
पूर्ण

अटल व्योम vlv_update_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	क्रमागत plane_id plane_id = plane->id;
	u16 gamma[8];
	पूर्णांक i;

	/* Seems RGB data bypasses the gamma always */
	अगर (!fb->क्रमmat->is_yuv)
		वापस;

	i9xx_plane_linear_gamma(gamma);

	/* FIXME these रेजिस्टर are single buffered :( */
	/* The two end poपूर्णांकs are implicit (0.0 and 1.0) */
	क्रम (i = 1; i < 8 - 1; i++)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPGAMC(pipe, plane_id, i - 1),
				  gamma[i] << 16 | gamma[i] << 8 | gamma[i]);
पूर्ण

अटल व्योम
vlv_update_plane(काष्ठा पूर्णांकel_plane *plane,
		 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	क्रमागत plane_id plane_id = plane->id;
	u32 sprsurf_offset = plane_state->view.color_plane[0].offset;
	u32 linear_offset;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->uapi.dst);
	u32 crtc_h = drm_rect_height(&plane_state->uapi.dst);
	u32 x = plane_state->view.color_plane[0].x;
	u32 y = plane_state->view.color_plane[0].y;
	अचिन्हित दीर्घ irqflags;
	u32 sprctl;

	sprctl = plane_state->ctl | vlv_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	crtc_w--;
	crtc_h--;

	linear_offset = पूर्णांकel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPSTRIDE(pipe, plane_id),
			  plane_state->view.color_plane[0].stride);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPPOS(pipe, plane_id),
			  (crtc_y << 16) | crtc_x);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPSIZE(pipe, plane_id),
			  (crtc_h << 16) | crtc_w);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCONSTALPHA(pipe, plane_id), 0);

	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B)
		chv_update_csc(plane_state);

	अगर (key->flags) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPKEYMINVAL(pipe, plane_id),
				  key->min_value);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPKEYMSK(pipe, plane_id),
				  key->channel_mask);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPKEYMAXVAL(pipe, plane_id),
				  key->max_value);
	पूर्ण

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPLINOFF(pipe, plane_id), linear_offset);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPTILखातापूर्णF(pipe, plane_id), (y << 16) | x);

	/*
	 * The control रेजिस्टर self-arms अगर the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control रेजिस्टर just beक्रमe the surface रेजिस्टर.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCNTR(pipe, plane_id), sprctl);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPSURF(pipe, plane_id),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + sprsurf_offset);

	vlv_update_clrc(plane_state);
	vlv_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
vlv_disable_plane(काष्ठा पूर्णांकel_plane *plane,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	क्रमागत plane_id plane_id = plane->id;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPCNTR(pipe, plane_id), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPSURF(pipe, plane_id), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल bool
vlv_plane_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
		       क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	क्रमागत plane_id plane_id = plane->id;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_de_पढ़ो(dev_priv, SPCNTR(plane->pipe, plane_id)) & SP_ENABLE;

	*pipe = plane->pipe;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम ivb_plane_ratio(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			    अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	u8 active_planes = crtc_state->active_planes & ~BIT(PLANE_CURSOR);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];

	अगर (hweight8(active_planes) == 2) अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 10;
			*den = 8;
			अवरोध;
		हाल 4:
			*num = 17;
			*den = 16;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 9;
			*den = 8;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ivb_plane_ratio_scaling(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				    अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];

	चयन (cpp) अणु
	हाल 8:
		*num = 12;
		*den = 8;
		अवरोध;
	हाल 4:
		*num = 19;
		*den = 16;
		अवरोध;
	हाल 2:
		*num = 33;
		*den = 32;
		अवरोध;
	शेष:
		*num = 1;
		*den = 1;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक ivb_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक pixel_rate;
	अचिन्हित पूर्णांक num, den;

	/*
	 * Note that crtc_state->pixel_rate accounts क्रम both
	 * horizontal and vertical panel fitter करोwnscaling factors.
	 * Pre-HSW bspec tells us to only consider the horizontal
	 * करोwnscaling factor here. We ignore that and just consider
	 * both क्रम simplicity.
	 */
	pixel_rate = crtc_state->pixel_rate;

	ivb_plane_ratio(crtc_state, plane_state, &num, &den);

	वापस DIV_ROUND_UP(pixel_rate * num, den);
पूर्ण

अटल पूर्णांक ivb_sprite_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक src_w, dst_w, pixel_rate;
	अचिन्हित पूर्णांक num, den;

	/*
	 * Note that crtc_state->pixel_rate accounts क्रम both
	 * horizontal and vertical panel fitter करोwnscaling factors.
	 * Pre-HSW bspec tells us to only consider the horizontal
	 * करोwnscaling factor here. We ignore that and just consider
	 * both क्रम simplicity.
	 */
	pixel_rate = crtc_state->pixel_rate;

	src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	dst_w = drm_rect_width(&plane_state->uapi.dst);

	अगर (src_w != dst_w)
		ivb_plane_ratio_scaling(crtc_state, plane_state, &num, &den);
	अन्यथा
		ivb_plane_ratio(crtc_state, plane_state, &num, &den);

	/* Horizontal करोwnscaling limits the maximum pixel rate */
	dst_w = min(src_w, dst_w);

	वापस DIV_ROUND_UP_ULL(mul_u32_u32(pixel_rate, num * src_w),
				den * dst_w);
पूर्ण

अटल व्योम hsw_plane_ratio(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			    अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	u8 active_planes = crtc_state->active_planes & ~BIT(PLANE_CURSOR);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];

	अगर (hweight8(active_planes) == 2) अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 10;
			*den = 8;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cpp) अणु
		हाल 8:
			*num = 9;
			*den = 8;
			अवरोध;
		शेष:
			*num = 1;
			*den = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hsw_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक pixel_rate = crtc_state->pixel_rate;
	अचिन्हित पूर्णांक num, den;

	hsw_plane_ratio(crtc_state, plane_state, &num, &den);

	वापस DIV_ROUND_UP(pixel_rate * num, den);
पूर्ण

अटल u32 ivb_sprite_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 sprctl = 0;

	अगर (crtc_state->gamma_enable)
		sprctl |= SPRITE_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		sprctl |= SPRITE_PIPE_CSC_ENABLE;

	वापस sprctl;
पूर्ण

अटल bool ivb_need_sprite_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;

	वापस fb->क्रमmat->cpp[0] == 8 &&
		(IS_IVYBRIDGE(dev_priv) || IS_HASWELL(dev_priv));
पूर्ण

अटल u32 ivb_sprite_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	u32 sprctl;

	sprctl = SPRITE_ENABLE;

	अगर (IS_IVYBRIDGE(dev_priv))
		sprctl |= SPRITE_TRICKLE_FEED_DISABLE;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XBGR8888:
		sprctl |= SPRITE_FORMAT_RGBX888 | SPRITE_RGB_ORDER_RGBX;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		sprctl |= SPRITE_FORMAT_RGBX888;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
		sprctl |= SPRITE_FORMAT_RGBX101010 | SPRITE_RGB_ORDER_RGBX;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
		sprctl |= SPRITE_FORMAT_RGBX101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
		sprctl |= SPRITE_FORMAT_RGBX161616 | SPRITE_RGB_ORDER_RGBX;
		अवरोध;
	हाल DRM_FORMAT_XRGB16161616F:
		sprctl |= SPRITE_FORMAT_RGBX161616;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_YUYV;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_YVYU;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_UYVY;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		sprctl |= SPRITE_FORMAT_YUV422 | SPRITE_YUV_ORDER_VYUY;
		अवरोध;
	शेष:
		MISSING_CASE(fb->क्रमmat->क्रमmat);
		वापस 0;
	पूर्ण

	अगर (!ivb_need_sprite_gamma(plane_state))
		sprctl |= SPRITE_INT_GAMMA_DISABLE;

	अगर (plane_state->hw.color_encoding == DRM_COLOR_YCBCR_BT709)
		sprctl |= SPRITE_YUV_TO_RGB_CSC_FORMAT_BT709;

	अगर (plane_state->hw.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
		sprctl |= SPRITE_YUV_RANGE_CORRECTION_DISABLE;

	अगर (fb->modअगरier == I915_FORMAT_MOD_X_TILED)
		sprctl |= SPRITE_TILED;

	अगर (rotation & DRM_MODE_ROTATE_180)
		sprctl |= SPRITE_ROTATE_180;

	अगर (key->flags & I915_SET_COLORKEY_DESTINATION)
		sprctl |= SPRITE_DEST_KEY;
	अन्यथा अगर (key->flags & I915_SET_COLORKEY_SOURCE)
		sprctl |= SPRITE_SOURCE_KEY;

	वापस sprctl;
पूर्ण

अटल व्योम ivb_sprite_linear_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				    u16 gamma[18])
अणु
	पूर्णांक scale, i;

	/*
	 * WaFP16GammaEnabling:ivb,hsw
	 * "Workaround : When using the 64-bit क्रमmat, the sprite output
	 *  on each color channel has one quarter amplitude. It can be
	 *  brought up to full amplitude by using sprite पूर्णांकernal gamma
	 *  correction, pipe gamma correction, or pipe color space
	 *  conversion to multiply the sprite output by four."
	 */
	scale = 4;

	क्रम (i = 0; i < 16; i++)
		gamma[i] = min((scale * i << 10) / 16, (1 << 10) - 1);

	gamma[i] = min((scale * i << 10) / 16, 1 << 10);
	i++;

	gamma[i] = 3 << 10;
	i++;
पूर्ण

अटल व्योम ivb_update_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	u16 gamma[18];
	पूर्णांक i;

	अगर (!ivb_need_sprite_gamma(plane_state))
		वापस;

	ivb_sprite_linear_gamma(plane_state, gamma);

	/* FIXME these रेजिस्टर are single buffered :( */
	क्रम (i = 0; i < 16; i++)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC(pipe, i),
				  gamma[i] << 20 | gamma[i] << 10 | gamma[i]);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC16(pipe, 0), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC16(pipe, 1), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC16(pipe, 2), gamma[i]);
	i++;

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC17(pipe, 0), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC17(pipe, 1), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRGAMC17(pipe, 2), gamma[i]);
	i++;
पूर्ण

अटल व्योम
ivb_update_plane(काष्ठा पूर्णांकel_plane *plane,
		 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	u32 sprsurf_offset = plane_state->view.color_plane[0].offset;
	u32 linear_offset;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->uapi.dst);
	u32 crtc_h = drm_rect_height(&plane_state->uapi.dst);
	u32 x = plane_state->view.color_plane[0].x;
	u32 y = plane_state->view.color_plane[0].y;
	u32 src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	u32 src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	u32 sprctl, sprscale = 0;
	अचिन्हित दीर्घ irqflags;

	sprctl = plane_state->ctl | ivb_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	अगर (crtc_w != src_w || crtc_h != src_h)
		sprscale = SPRITE_SCALE_ENABLE | (src_w << 16) | src_h;

	linear_offset = पूर्णांकel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSTRIDE(pipe),
			  plane_state->view.color_plane[0].stride);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRPOS(pipe), (crtc_y << 16) | crtc_x);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSIZE(pipe), (crtc_h << 16) | crtc_w);
	अगर (IS_IVYBRIDGE(dev_priv))
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSCALE(pipe), sprscale);

	अगर (key->flags) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRKEYVAL(pipe), key->min_value);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRKEYMSK(pipe),
				  key->channel_mask);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRKEYMAX(pipe), key->max_value);
	पूर्ण

	/* HSW consolidates SPRTILखातापूर्णF and SPRLINOFF पूर्णांकo a single SPROFFSET
	 * रेजिस्टर */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPROFFSET(pipe), (y << 16) | x);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRLINOFF(pipe), linear_offset);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRTILखातापूर्णF(pipe), (y << 16) | x);
	पूर्ण

	/*
	 * The control रेजिस्टर self-arms अगर the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control रेजिस्टर just beक्रमe the surface रेजिस्टर.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRCTL(pipe), sprctl);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSURF(pipe),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + sprsurf_offset);

	ivb_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
ivb_disable_plane(काष्ठा पूर्णांकel_plane *plane,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRCTL(pipe), 0);
	/* Disable the scaler */
	अगर (IS_IVYBRIDGE(dev_priv))
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSCALE(pipe), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, SPRSURF(pipe), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल bool
ivb_plane_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
		       क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret =  पूर्णांकel_de_पढ़ो(dev_priv, SPRCTL(plane->pipe)) & SPRITE_ENABLE;

	*pipe = plane->pipe;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल पूर्णांक g4x_sprite_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक hscale, pixel_rate;
	अचिन्हित पूर्णांक limit, decimate;

	/*
	 * Note that crtc_state->pixel_rate accounts क्रम both
	 * horizontal and vertical panel fitter करोwnscaling factors.
	 * Pre-HSW bspec tells us to only consider the horizontal
	 * करोwnscaling factor here. We ignore that and just consider
	 * both क्रम simplicity.
	 */
	pixel_rate = crtc_state->pixel_rate;

	/* Horizontal करोwnscaling limits the maximum pixel rate */
	hscale = drm_rect_calc_hscale(&plane_state->uapi.src,
				      &plane_state->uapi.dst,
				      0, पूर्णांक_उच्च);
	hscale = max(hscale, 0x10000u);

	/* Decimation steps at 2x,4x,8x,16x */
	decimate = ilog2(hscale >> 16);
	hscale >>= decimate;

	/* Starting limit is 90% of cdclk */
	limit = 9;

	/* -10% per decimation step */
	limit -= decimate;

	/* -10% क्रम RGB */
	अगर (!fb->क्रमmat->is_yuv)
		limit--;

	/*
	 * We should also करो -10% अगर sprite scaling is enabled
	 * on the other pipe, but we can't really check क्रम that,
	 * so we ignore it.
	 */

	वापस DIV_ROUND_UP_ULL(mul_u32_u32(pixel_rate, 10 * hscale),
				limit << 16);
पूर्ण

अटल अचिन्हित पूर्णांक
g4x_sprite_max_stride(काष्ठा पूर्णांकel_plane *plane,
		      u32 pixel_क्रमmat, u64 modअगरier,
		      अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/* Limit to 4k pixels to guarantee TILखातापूर्णF.x करोesn't get too big. */
	अगर (modअगरier == I915_FORMAT_MOD_X_TILED)
		वापस min(4096 * cpp, 16 * 1024);
	अन्यथा
		वापस 16 * 1024;
पूर्ण

अटल अचिन्हित पूर्णांक
hsw_sprite_max_stride(काष्ठा पूर्णांकel_plane *plane,
		      u32 pixel_क्रमmat, u64 modअगरier,
		      अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/* Limit to 8k pixels to guarantee OFFSET.x करोesn't get too big. */
	वापस min(8192 * cpp, 16 * 1024);
पूर्ण

अटल u32 g4x_sprite_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 dvscntr = 0;

	अगर (crtc_state->gamma_enable)
		dvscntr |= DVS_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		dvscntr |= DVS_PIPE_CSC_ENABLE;

	वापस dvscntr;
पूर्ण

अटल u32 g4x_sprite_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	u32 dvscntr;

	dvscntr = DVS_ENABLE;

	अगर (IS_SANDYBRIDGE(dev_priv))
		dvscntr |= DVS_TRICKLE_FEED_DISABLE;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XBGR8888:
		dvscntr |= DVS_FORMAT_RGBX888 | DVS_RGB_ORDER_XBGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		dvscntr |= DVS_FORMAT_RGBX888;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
		dvscntr |= DVS_FORMAT_RGBX101010 | DVS_RGB_ORDER_XBGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
		dvscntr |= DVS_FORMAT_RGBX101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
		dvscntr |= DVS_FORMAT_RGBX161616 | DVS_RGB_ORDER_XBGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB16161616F:
		dvscntr |= DVS_FORMAT_RGBX161616;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_YUYV;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_YVYU;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_UYVY;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		dvscntr |= DVS_FORMAT_YUV422 | DVS_YUV_ORDER_VYUY;
		अवरोध;
	शेष:
		MISSING_CASE(fb->क्रमmat->क्रमmat);
		वापस 0;
	पूर्ण

	अगर (plane_state->hw.color_encoding == DRM_COLOR_YCBCR_BT709)
		dvscntr |= DVS_YUV_FORMAT_BT709;

	अगर (plane_state->hw.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
		dvscntr |= DVS_YUV_RANGE_CORRECTION_DISABLE;

	अगर (fb->modअगरier == I915_FORMAT_MOD_X_TILED)
		dvscntr |= DVS_TILED;

	अगर (rotation & DRM_MODE_ROTATE_180)
		dvscntr |= DVS_ROTATE_180;

	अगर (key->flags & I915_SET_COLORKEY_DESTINATION)
		dvscntr |= DVS_DEST_KEY;
	अन्यथा अगर (key->flags & I915_SET_COLORKEY_SOURCE)
		dvscntr |= DVS_SOURCE_KEY;

	वापस dvscntr;
पूर्ण

अटल व्योम g4x_update_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	u16 gamma[8];
	पूर्णांक i;

	/* Seems RGB data bypasses the gamma always */
	अगर (!fb->क्रमmat->is_yuv)
		वापस;

	i9xx_plane_linear_gamma(gamma);

	/* FIXME these रेजिस्टर are single buffered :( */
	/* The two end poपूर्णांकs are implicit (0.0 and 1.0) */
	क्रम (i = 1; i < 8 - 1; i++)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSGAMC_G4X(pipe, i - 1),
				  gamma[i] << 16 | gamma[i] << 8 | gamma[i]);
पूर्ण

अटल व्योम ilk_sprite_linear_gamma(u16 gamma[17])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 17; i++)
		gamma[i] = (i << 10) / 16;
पूर्ण

अटल व्योम ilk_update_gamma(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	u16 gamma[17];
	पूर्णांक i;

	/* Seems RGB data bypasses the gamma always */
	अगर (!fb->क्रमmat->is_yuv)
		वापस;

	ilk_sprite_linear_gamma(gamma);

	/* FIXME these रेजिस्टर are single buffered :( */
	क्रम (i = 0; i < 16; i++)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSGAMC_ILK(pipe, i),
				  gamma[i] << 20 | gamma[i] << 10 | gamma[i]);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSGAMCMAX_ILK(pipe, 0), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSGAMCMAX_ILK(pipe, 1), gamma[i]);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSGAMCMAX_ILK(pipe, 2), gamma[i]);
	i++;
पूर्ण

अटल व्योम
g4x_update_plane(काष्ठा पूर्णांकel_plane *plane,
		 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	u32 dvssurf_offset = plane_state->view.color_plane[0].offset;
	u32 linear_offset;
	स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->uapi.dst);
	u32 crtc_h = drm_rect_height(&plane_state->uapi.dst);
	u32 x = plane_state->view.color_plane[0].x;
	u32 y = plane_state->view.color_plane[0].y;
	u32 src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	u32 src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	u32 dvscntr, dvsscale = 0;
	अचिन्हित दीर्घ irqflags;

	dvscntr = plane_state->ctl | g4x_sprite_ctl_crtc(crtc_state);

	/* Sizes are 0 based */
	src_w--;
	src_h--;
	crtc_w--;
	crtc_h--;

	अगर (crtc_w != src_w || crtc_h != src_h)
		dvsscale = DVS_SCALE_ENABLE | (src_w << 16) | src_h;

	linear_offset = पूर्णांकel_fb_xy_to_linear(x, y, plane_state, 0);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSTRIDE(pipe),
			  plane_state->view.color_plane[0].stride);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSPOS(pipe), (crtc_y << 16) | crtc_x);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSIZE(pipe), (crtc_h << 16) | crtc_w);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSCALE(pipe), dvsscale);

	अगर (key->flags) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSKEYVAL(pipe), key->min_value);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSKEYMSK(pipe),
				  key->channel_mask);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSKEYMAX(pipe), key->max_value);
	पूर्ण

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSLINOFF(pipe), linear_offset);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSTILखातापूर्णF(pipe), (y << 16) | x);

	/*
	 * The control रेजिस्टर self-arms अगर the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control रेजिस्टर just beक्रमe the surface रेजिस्टर.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSCNTR(pipe), dvscntr);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSURF(pipe),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + dvssurf_offset);

	अगर (IS_G4X(dev_priv))
		g4x_update_gamma(plane_state);
	अन्यथा
		ilk_update_gamma(plane_state);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
g4x_disable_plane(काष्ठा पूर्णांकel_plane *plane,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSCNTR(pipe), 0);
	/* Disable the scaler */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSCALE(pipe), 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DVSSURF(pipe), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल bool
g4x_plane_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
		       क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_de_पढ़ो(dev_priv, DVSCNTR(plane->pipe)) & DVS_ENABLE;

	*pipe = plane->pipe;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल bool g4x_fb_scalable(स्थिर काष्ठा drm_framebuffer *fb)
अणु
	अगर (!fb)
		वापस false;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_ARGB16161616F:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक
g4x_sprite_check_scaling(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	स्थिर काष्ठा drm_rect *src = &plane_state->uapi.src;
	स्थिर काष्ठा drm_rect *dst = &plane_state->uapi.dst;
	पूर्णांक src_x, src_w, src_h, crtc_w, crtc_h;
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	अचिन्हित पूर्णांक stride = plane_state->view.color_plane[0].stride;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	अचिन्हित पूर्णांक width_bytes;
	पूर्णांक min_width, min_height;

	crtc_w = drm_rect_width(dst);
	crtc_h = drm_rect_height(dst);

	src_x = src->x1 >> 16;
	src_w = drm_rect_width(src) >> 16;
	src_h = drm_rect_height(src) >> 16;

	अगर (src_w == crtc_w && src_h == crtc_h)
		वापस 0;

	min_width = 3;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (src_h & 1) अणु
			DRM_DEBUG_KMS("Source height must be even with interlaced modes\n");
			वापस -EINVAL;
		पूर्ण
		min_height = 6;
	पूर्ण अन्यथा अणु
		min_height = 3;
	पूर्ण

	width_bytes = ((src_x * cpp) & 63) + src_w * cpp;

	अगर (src_w < min_width || src_h < min_height ||
	    src_w > 2048 || src_h > 2048) अणु
		DRM_DEBUG_KMS("Source dimensions (%dx%d) exceed hardware limits (%dx%d - %dx%d)\n",
			      src_w, src_h, min_width, min_height, 2048, 2048);
		वापस -EINVAL;
	पूर्ण

	अगर (width_bytes > 4096) अणु
		DRM_DEBUG_KMS("Fetch width (%d) exceeds hardware max with scaling (%u)\n",
			      width_bytes, 4096);
		वापस -EINVAL;
	पूर्ण

	अगर (stride > 4096) अणु
		DRM_DEBUG_KMS("Stride (%u) exceeds hardware max with scaling (%u)\n",
			      stride, 4096);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
g4x_sprite_check(काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	पूर्णांक min_scale = DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक max_scale = DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक ret;

	अगर (g4x_fb_scalable(plane_state->hw.fb)) अणु
		अगर (DISPLAY_VER(dev_priv) < 7) अणु
			min_scale = 1;
			max_scale = 16 << 16;
		पूर्ण अन्यथा अगर (IS_IVYBRIDGE(dev_priv)) अणु
			min_scale = 1;
			max_scale = 2 << 16;
		पूर्ण
	पूर्ण

	ret = पूर्णांकel_atomic_plane_check_clipping(plane_state, crtc_state,
						min_scale, max_scale, true);
	अगर (ret)
		वापस ret;

	ret = i9xx_check_plane_surface(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	ret = पूर्णांकel_plane_check_src_coordinates(plane_state);
	अगर (ret)
		वापस ret;

	ret = g4x_sprite_check_scaling(crtc_state, plane_state);
	अगर (ret)
		वापस ret;

	अगर (DISPLAY_VER(dev_priv) >= 7)
		plane_state->ctl = ivb_sprite_ctl(crtc_state, plane_state);
	अन्यथा
		plane_state->ctl = g4x_sprite_ctl(crtc_state, plane_state);

	वापस 0;
पूर्ण

पूर्णांक chv_plane_check_rotation(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;

	/* CHV ignores the mirror bit when the rotate bit is set :( */
	अगर (IS_CHERRYVIEW(dev_priv) &&
	    rotation & DRM_MODE_ROTATE_180 &&
	    rotation & DRM_MODE_REFLECT_X) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Cannot rotate and reflect at the same time\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vlv_sprite_check(काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	पूर्णांक ret;

	ret = chv_plane_check_rotation(plane_state);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_atomic_plane_check_clipping(plane_state, crtc_state,
						DRM_PLANE_HELPER_NO_SCALING,
						DRM_PLANE_HELPER_NO_SCALING,
						true);
	अगर (ret)
		वापस ret;

	ret = i9xx_check_plane_surface(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	ret = पूर्णांकel_plane_check_src_coordinates(plane_state);
	अगर (ret)
		वापस ret;

	plane_state->ctl = vlv_sprite_ctl(crtc_state, plane_state);

	वापस 0;
पूर्ण

अटल bool has_dst_key_in_primary_plane(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस DISPLAY_VER(dev_priv) >= 9;
पूर्ण

अटल व्योम पूर्णांकel_plane_set_ckey(काष्ठा पूर्णांकel_plane_state *plane_state,
				 स्थिर काष्ठा drm_पूर्णांकel_sprite_colorkey *set)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	काष्ठा drm_पूर्णांकel_sprite_colorkey *key = &plane_state->ckey;

	*key = *set;

	/*
	 * We want src key enabled on the
	 * sprite and not on the primary.
	 */
	अगर (plane->id == PLANE_PRIMARY &&
	    set->flags & I915_SET_COLORKEY_SOURCE)
		key->flags = 0;

	/*
	 * On SKL+ we want dst key enabled on
	 * the primary and not on the sprite.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 9 && plane->id != PLANE_PRIMARY &&
	    set->flags & I915_SET_COLORKEY_DESTINATION)
		key->flags = 0;
पूर्ण

पूर्णांक पूर्णांकel_sprite_set_colorkey_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_पूर्णांकel_sprite_colorkey *set = data;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret = 0;

	/* ignore the poपूर्णांकless "none" flag */
	set->flags &= ~I915_SET_COLORKEY_NONE;

	अगर (set->flags & ~(I915_SET_COLORKEY_DESTINATION | I915_SET_COLORKEY_SOURCE))
		वापस -EINVAL;

	/* Make sure we करोn't try to enable both src & dest simultaneously */
	अगर ((set->flags & (I915_SET_COLORKEY_DESTINATION | I915_SET_COLORKEY_SOURCE)) == (I915_SET_COLORKEY_DESTINATION | I915_SET_COLORKEY_SOURCE))
		वापस -EINVAL;

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    set->flags & I915_SET_COLORKEY_DESTINATION)
		वापस -EINVAL;

	plane = drm_plane_find(dev, file_priv, set->plane_id);
	अगर (!plane || plane->type != DRM_PLANE_TYPE_OVERLAY)
		वापस -ENOENT;

	/*
	 * SKL+ only plane 2 can करो destination keying against plane 1.
	 * Also multiple planes can't करो destination keying on the same
	 * pipe simultaneously.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 9 &&
	    to_पूर्णांकel_plane(plane)->id >= PLANE_SPRITE1 &&
	    set->flags & I915_SET_COLORKEY_DESTINATION)
		वापस -EINVAL;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	state->acquire_ctx = &ctx;

	जबतक (1) अणु
		plane_state = drm_atomic_get_plane_state(state, plane);
		ret = PTR_ERR_OR_ZERO(plane_state);
		अगर (!ret)
			पूर्णांकel_plane_set_ckey(to_पूर्णांकel_plane_state(plane_state), set);

		/*
		 * On some platक्रमms we have to configure
		 * the dst colorkey on the primary plane.
		 */
		अगर (!ret && has_dst_key_in_primary_plane(dev_priv)) अणु
			काष्ठा पूर्णांकel_crtc *crtc =
				पूर्णांकel_get_crtc_क्रम_pipe(dev_priv,
							to_पूर्णांकel_plane(plane)->pipe);

			plane_state = drm_atomic_get_plane_state(state,
								 crtc->base.primary);
			ret = PTR_ERR_OR_ZERO(plane_state);
			अगर (!ret)
				पूर्णांकel_plane_set_ckey(to_पूर्णांकel_plane_state(plane_state), set);
		पूर्ण

		अगर (!ret)
			ret = drm_atomic_commit(state);

		अगर (ret != -EDEADLK)
			अवरोध;

		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
	पूर्ण

	drm_atomic_state_put(state);
out:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	वापस ret;
पूर्ण

अटल स्थिर u32 g4x_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
पूर्ण;

अटल स्थिर u64 i9xx_plane_क्रमmat_modअगरiers[] = अणु
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर u32 snb_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XRGB16161616F,
	DRM_FORMAT_XBGR16161616F,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
पूर्ण;

अटल स्थिर u32 vlv_plane_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
पूर्ण;

अटल स्थिर u32 chv_pipe_b_sprite_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
पूर्ण;

अटल bool g4x_sprite_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
		    modअगरier == I915_FORMAT_MOD_X_TILED)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool snb_sprite_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_XRGB16161616F:
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
		    modअगरier == I915_FORMAT_MOD_X_TILED)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool vlv_sprite_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_YVYU:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_VYUY:
		अगर (modअगरier == DRM_FORMAT_MOD_LINEAR ||
		    modअगरier == I915_FORMAT_MOD_X_TILED)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs g4x_sprite_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = g4x_sprite_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs snb_sprite_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = snb_sprite_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vlv_sprite_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = vlv_sprite_क्रमmat_mod_supported,
पूर्ण;

काष्ठा पूर्णांकel_plane *
पूर्णांकel_sprite_plane_create(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत pipe pipe, पूर्णांक sprite)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	स्थिर काष्ठा drm_plane_funcs *plane_funcs;
	अचिन्हित पूर्णांक supported_rotations;
	स्थिर u64 *modअगरiers;
	स्थिर u32 *क्रमmats;
	पूर्णांक num_क्रमmats;
	पूर्णांक ret, zpos;

	plane = पूर्णांकel_plane_alloc();
	अगर (IS_ERR(plane))
		वापस plane;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		plane->update_plane = vlv_update_plane;
		plane->disable_plane = vlv_disable_plane;
		plane->get_hw_state = vlv_plane_get_hw_state;
		plane->check_plane = vlv_sprite_check;
		plane->max_stride = i965_plane_max_stride;
		plane->min_cdclk = vlv_plane_min_cdclk;

		अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) अणु
			क्रमmats = chv_pipe_b_sprite_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(chv_pipe_b_sprite_क्रमmats);
		पूर्ण अन्यथा अणु
			क्रमmats = vlv_plane_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(vlv_plane_क्रमmats);
		पूर्ण
		modअगरiers = i9xx_plane_क्रमmat_modअगरiers;

		plane_funcs = &vlv_sprite_funcs;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7) अणु
		plane->update_plane = ivb_update_plane;
		plane->disable_plane = ivb_disable_plane;
		plane->get_hw_state = ivb_plane_get_hw_state;
		plane->check_plane = g4x_sprite_check;

		अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) अणु
			plane->max_stride = hsw_sprite_max_stride;
			plane->min_cdclk = hsw_plane_min_cdclk;
		पूर्ण अन्यथा अणु
			plane->max_stride = g4x_sprite_max_stride;
			plane->min_cdclk = ivb_sprite_min_cdclk;
		पूर्ण

		क्रमmats = snb_plane_क्रमmats;
		num_क्रमmats = ARRAY_SIZE(snb_plane_क्रमmats);
		modअगरiers = i9xx_plane_क्रमmat_modअगरiers;

		plane_funcs = &snb_sprite_funcs;
	पूर्ण अन्यथा अणु
		plane->update_plane = g4x_update_plane;
		plane->disable_plane = g4x_disable_plane;
		plane->get_hw_state = g4x_plane_get_hw_state;
		plane->check_plane = g4x_sprite_check;
		plane->max_stride = g4x_sprite_max_stride;
		plane->min_cdclk = g4x_sprite_min_cdclk;

		modअगरiers = i9xx_plane_क्रमmat_modअगरiers;
		अगर (IS_SANDYBRIDGE(dev_priv)) अणु
			क्रमmats = snb_plane_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(snb_plane_क्रमmats);

			plane_funcs = &snb_sprite_funcs;
		पूर्ण अन्यथा अणु
			क्रमmats = g4x_plane_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(g4x_plane_क्रमmats);

			plane_funcs = &g4x_sprite_funcs;
		पूर्ण
	पूर्ण

	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) अणु
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X;
	पूर्ण अन्यथा अणु
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180;
	पूर्ण

	plane->pipe = pipe;
	plane->id = PLANE_SPRITE0 + sprite;
	plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, plane->id);

	ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
				       0, plane_funcs,
				       क्रमmats, num_क्रमmats, modअगरiers,
				       DRM_PLANE_TYPE_OVERLAY,
				       "sprite %c", sprite_name(pipe, sprite));
	अगर (ret)
		जाओ fail;

	drm_plane_create_rotation_property(&plane->base,
					   DRM_MODE_ROTATE_0,
					   supported_rotations);

	drm_plane_create_color_properties(&plane->base,
					  BIT(DRM_COLOR_YCBCR_BT601) |
					  BIT(DRM_COLOR_YCBCR_BT709),
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
					  BIT(DRM_COLOR_YCBCR_FULL_RANGE),
					  DRM_COLOR_YCBCR_BT709,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	zpos = sprite + 1;
	drm_plane_create_zpos_immutable_property(&plane->base, zpos);

	drm_plane_helper_add(&plane->base, &पूर्णांकel_plane_helper_funcs);

	वापस plane;

fail:
	पूर्णांकel_plane_मुक्त(plane);

	वापस ERR_PTR(ret);
पूर्ण
