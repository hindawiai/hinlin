<शैली गुरु>
/*
 * Copyright (C) 2011-2013 Intel Corporation
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
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>

#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_rect.h>

/**
 * drm_rect_पूर्णांकersect - पूर्णांकersect two rectangles
 * @r1: first rectangle
 * @r2: second rectangle
 *
 * Calculate the पूर्णांकersection of rectangles @r1 and @r2.
 * @r1 will be overwritten with the पूर्णांकersection.
 *
 * RETURNS:
 * %true अगर rectangle @r1 is still visible after the operation,
 * %false otherwise.
 */
bool drm_rect_पूर्णांकersect(काष्ठा drm_rect *r1, स्थिर काष्ठा drm_rect *r2)
अणु
	r1->x1 = max(r1->x1, r2->x1);
	r1->y1 = max(r1->y1, r2->y1);
	r1->x2 = min(r1->x2, r2->x2);
	r1->y2 = min(r1->y2, r2->y2);

	वापस drm_rect_visible(r1);
पूर्ण
EXPORT_SYMBOL(drm_rect_पूर्णांकersect);

अटल u32 clip_scaled(पूर्णांक src, पूर्णांक dst, पूर्णांक *clip)
अणु
	u64 पंचांगp;

	अगर (dst == 0)
		वापस 0;

	/* Only clip what we have. Keeps the result bounded. */
	*clip = min(*clip, dst);

	पंचांगp = mul_u32_u32(src, dst - *clip);

	/*
	 * Round toward 1.0 when clipping so that we करोn't accidentally
	 * change upscaling to करोwnscaling or vice versa.
	 */
	अगर (src < (dst << 16))
		वापस DIV_ROUND_UP_ULL(पंचांगp, dst);
	अन्यथा
		वापस DIV_ROUND_DOWN_ULL(पंचांगp, dst);
पूर्ण

/**
 * drm_rect_clip_scaled - perक्रमm a scaled clip operation
 * @src: source winकरोw rectangle
 * @dst: destination winकरोw rectangle
 * @clip: clip rectangle
 *
 * Clip rectangle @dst by rectangle @clip. Clip rectangle @src by the
 * the corresponding amounts, retaining the vertical and horizontal scaling
 * factors from @src to @dst.
 *
 * RETURNS:
 *
 * %true अगर rectangle @dst is still visible after being clipped,
 * %false otherwise.
 */
bool drm_rect_clip_scaled(काष्ठा drm_rect *src, काष्ठा drm_rect *dst,
			  स्थिर काष्ठा drm_rect *clip)
अणु
	पूर्णांक dअगरf;

	dअगरf = clip->x1 - dst->x1;
	अगर (dअगरf > 0) अणु
		u32 new_src_w = clip_scaled(drm_rect_width(src),
					    drm_rect_width(dst), &dअगरf);

		src->x1 = src->x2 - new_src_w;
		dst->x1 += dअगरf;
	पूर्ण
	dअगरf = clip->y1 - dst->y1;
	अगर (dअगरf > 0) अणु
		u32 new_src_h = clip_scaled(drm_rect_height(src),
					    drm_rect_height(dst), &dअगरf);

		src->y1 = src->y2 - new_src_h;
		dst->y1 += dअगरf;
	पूर्ण
	dअगरf = dst->x2 - clip->x2;
	अगर (dअगरf > 0) अणु
		u32 new_src_w = clip_scaled(drm_rect_width(src),
					    drm_rect_width(dst), &dअगरf);

		src->x2 = src->x1 + new_src_w;
		dst->x2 -= dअगरf;
	पूर्ण
	dअगरf = dst->y2 - clip->y2;
	अगर (dअगरf > 0) अणु
		u32 new_src_h = clip_scaled(drm_rect_height(src),
					    drm_rect_height(dst), &dअगरf);

		src->y2 = src->y1 + new_src_h;
		dst->y2 -= dअगरf;
	पूर्ण

	वापस drm_rect_visible(dst);
पूर्ण
EXPORT_SYMBOL(drm_rect_clip_scaled);

अटल पूर्णांक drm_calc_scale(पूर्णांक src, पूर्णांक dst)
अणु
	पूर्णांक scale = 0;

	अगर (WARN_ON(src < 0 || dst < 0))
		वापस -EINVAL;

	अगर (dst == 0)
		वापस 0;

	अगर (src > (dst << 16))
		वापस DIV_ROUND_UP(src, dst);
	अन्यथा
		scale = src / dst;

	वापस scale;
पूर्ण

/**
 * drm_rect_calc_hscale - calculate the horizontal scaling factor
 * @src: source winकरोw rectangle
 * @dst: destination winकरोw rectangle
 * @min_hscale: minimum allowed horizontal scaling factor
 * @max_hscale: maximum allowed horizontal scaling factor
 *
 * Calculate the horizontal scaling factor as
 * (@src width) / (@dst width).
 *
 * If the scale is below 1 << 16, round करोwn. If the scale is above
 * 1 << 16, round up. This will calculate the scale with the most
 * pessimistic limit calculation.
 *
 * RETURNS:
 * The horizontal scaling factor, or त्रुटि_सं of out of limits.
 */
पूर्णांक drm_rect_calc_hscale(स्थिर काष्ठा drm_rect *src,
			 स्थिर काष्ठा drm_rect *dst,
			 पूर्णांक min_hscale, पूर्णांक max_hscale)
अणु
	पूर्णांक src_w = drm_rect_width(src);
	पूर्णांक dst_w = drm_rect_width(dst);
	पूर्णांक hscale = drm_calc_scale(src_w, dst_w);

	अगर (hscale < 0 || dst_w == 0)
		वापस hscale;

	अगर (hscale < min_hscale || hscale > max_hscale)
		वापस -दुस्फल;

	वापस hscale;
पूर्ण
EXPORT_SYMBOL(drm_rect_calc_hscale);

/**
 * drm_rect_calc_vscale - calculate the vertical scaling factor
 * @src: source winकरोw rectangle
 * @dst: destination winकरोw rectangle
 * @min_vscale: minimum allowed vertical scaling factor
 * @max_vscale: maximum allowed vertical scaling factor
 *
 * Calculate the vertical scaling factor as
 * (@src height) / (@dst height).
 *
 * If the scale is below 1 << 16, round करोwn. If the scale is above
 * 1 << 16, round up. This will calculate the scale with the most
 * pessimistic limit calculation.
 *
 * RETURNS:
 * The vertical scaling factor, or त्रुटि_सं of out of limits.
 */
पूर्णांक drm_rect_calc_vscale(स्थिर काष्ठा drm_rect *src,
			 स्थिर काष्ठा drm_rect *dst,
			 पूर्णांक min_vscale, पूर्णांक max_vscale)
अणु
	पूर्णांक src_h = drm_rect_height(src);
	पूर्णांक dst_h = drm_rect_height(dst);
	पूर्णांक vscale = drm_calc_scale(src_h, dst_h);

	अगर (vscale < 0 || dst_h == 0)
		वापस vscale;

	अगर (vscale < min_vscale || vscale > max_vscale)
		वापस -दुस्फल;

	वापस vscale;
पूर्ण
EXPORT_SYMBOL(drm_rect_calc_vscale);

/**
 * drm_rect_debug_prपूर्णांक - prपूर्णांक the rectangle inक्रमmation
 * @prefix: prefix string
 * @r: rectangle to prपूर्णांक
 * @fixed_poपूर्णांक: rectangle is in 16.16 fixed poपूर्णांक क्रमmat
 */
व्योम drm_rect_debug_prपूर्णांक(स्थिर अक्षर *prefix, स्थिर काष्ठा drm_rect *r, bool fixed_poपूर्णांक)
अणु
	अगर (fixed_poपूर्णांक)
		DRM_DEBUG_KMS("%s" DRM_RECT_FP_FMT "\n", prefix, DRM_RECT_FP_ARG(r));
	अन्यथा
		DRM_DEBUG_KMS("%s" DRM_RECT_FMT "\n", prefix, DRM_RECT_ARG(r));
पूर्ण
EXPORT_SYMBOL(drm_rect_debug_prपूर्णांक);

/**
 * drm_rect_rotate - Rotate the rectangle
 * @r: rectangle to be rotated
 * @width: Width of the coordinate space
 * @height: Height of the coordinate space
 * @rotation: Transक्रमmation to be applied
 *
 * Apply @rotation to the coordinates of rectangle @r.
 *
 * @width and @height combined with @rotation define
 * the location of the new origin.
 *
 * @width correcsponds to the horizontal and @height
 * to the vertical axis of the untransक्रमmed coordinate
 * space.
 */
व्योम drm_rect_rotate(काष्ठा drm_rect *r,
		     पूर्णांक width, पूर्णांक height,
		     अचिन्हित पूर्णांक rotation)
अणु
	काष्ठा drm_rect पंचांगp;

	अगर (rotation & (DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y)) अणु
		पंचांगp = *r;

		अगर (rotation & DRM_MODE_REFLECT_X) अणु
			r->x1 = width - पंचांगp.x2;
			r->x2 = width - पंचांगp.x1;
		पूर्ण

		अगर (rotation & DRM_MODE_REFLECT_Y) अणु
			r->y1 = height - पंचांगp.y2;
			r->y2 = height - पंचांगp.y1;
		पूर्ण
	पूर्ण

	चयन (rotation & DRM_MODE_ROTATE_MASK) अणु
	हाल DRM_MODE_ROTATE_0:
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		पंचांगp = *r;
		r->x1 = पंचांगp.y1;
		r->x2 = पंचांगp.y2;
		r->y1 = width - पंचांगp.x2;
		r->y2 = width - पंचांगp.x1;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		पंचांगp = *r;
		r->x1 = width - पंचांगp.x2;
		r->x2 = width - पंचांगp.x1;
		r->y1 = height - पंचांगp.y2;
		r->y2 = height - पंचांगp.y1;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		पंचांगp = *r;
		r->x1 = height - पंचांगp.y2;
		r->x2 = height - पंचांगp.y1;
		r->y1 = पंचांगp.x1;
		r->y2 = पंचांगp.x2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_rect_rotate);

/**
 * drm_rect_rotate_inv - Inverse rotate the rectangle
 * @r: rectangle to be rotated
 * @width: Width of the coordinate space
 * @height: Height of the coordinate space
 * @rotation: Transक्रमmation whose inverse is to be applied
 *
 * Apply the inverse of @rotation to the coordinates
 * of rectangle @r.
 *
 * @width and @height combined with @rotation define
 * the location of the new origin.
 *
 * @width correcsponds to the horizontal and @height
 * to the vertical axis of the original untransक्रमmed
 * coordinate space, so that you never have to flip
 * them when करोing a rotatation and its inverse.
 * That is, अगर you करो ::
 *
 *     drm_rect_rotate(&r, width, height, rotation);
 *     drm_rect_rotate_inv(&r, width, height, rotation);
 *
 * you will always get back the original rectangle.
 */
व्योम drm_rect_rotate_inv(काष्ठा drm_rect *r,
			 पूर्णांक width, पूर्णांक height,
			 अचिन्हित पूर्णांक rotation)
अणु
	काष्ठा drm_rect पंचांगp;

	चयन (rotation & DRM_MODE_ROTATE_MASK) अणु
	हाल DRM_MODE_ROTATE_0:
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		पंचांगp = *r;
		r->x1 = width - पंचांगp.y2;
		r->x2 = width - पंचांगp.y1;
		r->y1 = पंचांगp.x1;
		r->y2 = पंचांगp.x2;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		पंचांगp = *r;
		r->x1 = width - पंचांगp.x2;
		r->x2 = width - पंचांगp.x1;
		r->y1 = height - पंचांगp.y2;
		r->y2 = height - पंचांगp.y1;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		पंचांगp = *r;
		r->x1 = पंचांगp.y1;
		r->x2 = पंचांगp.y2;
		r->y1 = height - पंचांगp.x2;
		r->y2 = height - पंचांगp.x1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rotation & (DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y)) अणु
		पंचांगp = *r;

		अगर (rotation & DRM_MODE_REFLECT_X) अणु
			r->x1 = width - पंचांगp.x2;
			r->x2 = width - पंचांगp.x1;
		पूर्ण

		अगर (rotation & DRM_MODE_REFLECT_Y) अणु
			r->y1 = height - पंचांगp.y2;
			r->y2 = height - पंचांगp.y1;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_rect_rotate_inv);
