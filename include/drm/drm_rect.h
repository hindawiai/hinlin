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

#अगर_अघोषित DRM_RECT_H
#घोषणा DRM_RECT_H

#समावेश <linux/types.h>

/**
 * DOC: rect utils
 *
 * Utility functions to help manage rectangular areas क्रम
 * clipping, scaling, etc. calculations.
 */

/**
 * काष्ठा drm_rect - two dimensional rectangle
 * @x1: horizontal starting coordinate (inclusive)
 * @x2: horizontal ending coordinate (exclusive)
 * @y1: vertical starting coordinate (inclusive)
 * @y2: vertical ending coordinate (exclusive)
 */
काष्ठा drm_rect अणु
	पूर्णांक x1, y1, x2, y2;
पूर्ण;

/**
 * DRM_RECT_FMT - म_लिखो string क्रम &काष्ठा drm_rect
 */
#घोषणा DRM_RECT_FMT    "%dx%d%+d%+d"
/**
 * DRM_RECT_ARG - म_लिखो arguments क्रम &काष्ठा drm_rect
 * @r: rectangle काष्ठा
 */
#घोषणा DRM_RECT_ARG(r) drm_rect_width(r), drm_rect_height(r), (r)->x1, (r)->y1

/**
 * DRM_RECT_FP_FMT - म_लिखो string क्रम &काष्ठा drm_rect in 16.16 fixed poपूर्णांक
 */
#घोषणा DRM_RECT_FP_FMT "%d.%06ux%d.%06u%+d.%06u%+d.%06u"
/**
 * DRM_RECT_FP_ARG - म_लिखो arguments क्रम &काष्ठा drm_rect in 16.16 fixed poपूर्णांक
 * @r: rectangle काष्ठा
 *
 * This is useful क्रम e.g. prपूर्णांकing plane source rectangles, which are in 16.16
 * fixed poपूर्णांक.
 */
#घोषणा DRM_RECT_FP_ARG(r) \
		drm_rect_width(r) >> 16, ((drm_rect_width(r) & 0xffff) * 15625) >> 10, \
		drm_rect_height(r) >> 16, ((drm_rect_height(r) & 0xffff) * 15625) >> 10, \
		(r)->x1 >> 16, (((r)->x1 & 0xffff) * 15625) >> 10, \
		(r)->y1 >> 16, (((r)->y1 & 0xffff) * 15625) >> 10

/**
 * drm_rect_init - initialize the rectangle from x/y/w/h
 * @r: rectangle
 * @x: x coordinate
 * @y: y coordinate
 * @width: width
 * @height: height
 */
अटल अंतरभूत व्योम drm_rect_init(काष्ठा drm_rect *r, पूर्णांक x, पूर्णांक y,
				 पूर्णांक width, पूर्णांक height)
अणु
	r->x1 = x;
	r->y1 = y;
	r->x2 = x + width;
	r->y2 = y + height;
पूर्ण

/**
 * drm_rect_adjust_size - adjust the size of the rectangle
 * @r: rectangle to be adjusted
 * @dw: horizontal adjusपंचांगent
 * @dh: vertical adjusपंचांगent
 *
 * Change the size of rectangle @r by @dw in the horizontal direction,
 * and by @dh in the vertical direction, जबतक keeping the center
 * of @r stationary.
 *
 * Positive @dw and @dh increase the size, negative values decrease it.
 */
अटल अंतरभूत व्योम drm_rect_adjust_size(काष्ठा drm_rect *r, पूर्णांक dw, पूर्णांक dh)
अणु
	r->x1 -= dw >> 1;
	r->y1 -= dh >> 1;
	r->x2 += (dw + 1) >> 1;
	r->y2 += (dh + 1) >> 1;
पूर्ण

/**
 * drm_rect_translate - translate the rectangle
 * @r: rectangle to be tranlated
 * @dx: horizontal translation
 * @dy: vertical translation
 *
 * Move rectangle @r by @dx in the horizontal direction,
 * and by @dy in the vertical direction.
 */
अटल अंतरभूत व्योम drm_rect_translate(काष्ठा drm_rect *r, पूर्णांक dx, पूर्णांक dy)
अणु
	r->x1 += dx;
	r->y1 += dy;
	r->x2 += dx;
	r->y2 += dy;
पूर्ण

/**
 * drm_rect_translate_to - translate the rectangle to an असलolute position
 * @r: rectangle to be tranlated
 * @x: horizontal position
 * @y: vertical position
 *
 * Move rectangle @r to @x in the horizontal direction,
 * and to @y in the vertical direction.
 */
अटल अंतरभूत व्योम drm_rect_translate_to(काष्ठा drm_rect *r, पूर्णांक x, पूर्णांक y)
अणु
	drm_rect_translate(r, x - r->x1, y - r->y1);
पूर्ण

/**
 * drm_rect_करोwnscale - करोwnscale a rectangle
 * @r: rectangle to be करोwnscaled
 * @horz: horizontal करोwnscale factor
 * @vert: vertical करोwnscale factor
 *
 * Divide the coordinates of rectangle @r by @horz and @vert.
 */
अटल अंतरभूत व्योम drm_rect_करोwnscale(काष्ठा drm_rect *r, पूर्णांक horz, पूर्णांक vert)
अणु
	r->x1 /= horz;
	r->y1 /= vert;
	r->x2 /= horz;
	r->y2 /= vert;
पूर्ण

/**
 * drm_rect_width - determine the rectangle width
 * @r: rectangle whose width is वापसed
 *
 * RETURNS:
 * The width of the rectangle.
 */
अटल अंतरभूत पूर्णांक drm_rect_width(स्थिर काष्ठा drm_rect *r)
अणु
	वापस r->x2 - r->x1;
पूर्ण

/**
 * drm_rect_height - determine the rectangle height
 * @r: rectangle whose height is वापसed
 *
 * RETURNS:
 * The height of the rectangle.
 */
अटल अंतरभूत पूर्णांक drm_rect_height(स्थिर काष्ठा drm_rect *r)
अणु
	वापस r->y2 - r->y1;
पूर्ण

/**
 * drm_rect_visible - determine अगर the rectangle is visible
 * @r: rectangle whose visibility is वापसed
 *
 * RETURNS:
 * %true अगर the rectangle is visible, %false otherwise.
 */
अटल अंतरभूत bool drm_rect_visible(स्थिर काष्ठा drm_rect *r)
अणु
	वापस drm_rect_width(r) > 0 && drm_rect_height(r) > 0;
पूर्ण

/**
 * drm_rect_equals - determine अगर two rectangles are equal
 * @r1: first rectangle
 * @r2: second rectangle
 *
 * RETURNS:
 * %true अगर the rectangles are equal, %false otherwise.
 */
अटल अंतरभूत bool drm_rect_equals(स्थिर काष्ठा drm_rect *r1,
				   स्थिर काष्ठा drm_rect *r2)
अणु
	वापस r1->x1 == r2->x1 && r1->x2 == r2->x2 &&
		r1->y1 == r2->y1 && r1->y2 == r2->y2;
पूर्ण

/**
 * drm_rect_fp_to_पूर्णांक - Convert a rect in 16.16 fixed poपूर्णांक क्रमm to पूर्णांक क्रमm.
 * @dst: rect to be stored the converted value
 * @src: rect in 16.16 fixed poपूर्णांक क्रमm
 */
अटल अंतरभूत व्योम drm_rect_fp_to_पूर्णांक(काष्ठा drm_rect *dst,
				      स्थिर काष्ठा drm_rect *src)
अणु
	drm_rect_init(dst, src->x1 >> 16, src->y1 >> 16,
		      drm_rect_width(src) >> 16,
		      drm_rect_height(src) >> 16);
पूर्ण

bool drm_rect_पूर्णांकersect(काष्ठा drm_rect *r, स्थिर काष्ठा drm_rect *clip);
bool drm_rect_clip_scaled(काष्ठा drm_rect *src, काष्ठा drm_rect *dst,
			  स्थिर काष्ठा drm_rect *clip);
पूर्णांक drm_rect_calc_hscale(स्थिर काष्ठा drm_rect *src,
			 स्थिर काष्ठा drm_rect *dst,
			 पूर्णांक min_hscale, पूर्णांक max_hscale);
पूर्णांक drm_rect_calc_vscale(स्थिर काष्ठा drm_rect *src,
			 स्थिर काष्ठा drm_rect *dst,
			 पूर्णांक min_vscale, पूर्णांक max_vscale);
व्योम drm_rect_debug_prपूर्णांक(स्थिर अक्षर *prefix,
			  स्थिर काष्ठा drm_rect *r, bool fixed_poपूर्णांक);
व्योम drm_rect_rotate(काष्ठा drm_rect *r,
		     पूर्णांक width, पूर्णांक height,
		     अचिन्हित पूर्णांक rotation);
व्योम drm_rect_rotate_inv(काष्ठा drm_rect *r,
			 पूर्णांक width, पूर्णांक height,
			 अचिन्हित पूर्णांक rotation);

#पूर्ण_अगर
