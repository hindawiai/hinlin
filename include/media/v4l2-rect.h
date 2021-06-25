<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * v4l2-rect.h - v4l2_rect helper functions
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _V4L2_RECT_H_
#घोषणा _V4L2_RECT_H_

#समावेश <linux/videodev2.h>

/**
 * v4l2_rect_set_माप_प्रकारo() - copy the width/height values.
 * @r: rect whose width and height fields will be set
 * @size: rect containing the width and height fields you need.
 */
अटल अंतरभूत व्योम v4l2_rect_set_माप_प्रकारo(काष्ठा v4l2_rect *r,
					 स्थिर काष्ठा v4l2_rect *size)
अणु
	r->width = size->width;
	r->height = size->height;
पूर्ण

/**
 * v4l2_rect_set_min_size() - width and height of r should be >= min_size.
 * @r: rect whose width and height will be modअगरied
 * @min_size: rect containing the minimal width and height
 */
अटल अंतरभूत व्योम v4l2_rect_set_min_size(काष्ठा v4l2_rect *r,
					  स्थिर काष्ठा v4l2_rect *min_size)
अणु
	अगर (r->width < min_size->width)
		r->width = min_size->width;
	अगर (r->height < min_size->height)
		r->height = min_size->height;
पूर्ण

/**
 * v4l2_rect_set_max_size() - width and height of r should be <= max_size
 * @r: rect whose width and height will be modअगरied
 * @max_size: rect containing the maximum width and height
 */
अटल अंतरभूत व्योम v4l2_rect_set_max_size(काष्ठा v4l2_rect *r,
					  स्थिर काष्ठा v4l2_rect *max_size)
अणु
	अगर (r->width > max_size->width)
		r->width = max_size->width;
	अगर (r->height > max_size->height)
		r->height = max_size->height;
पूर्ण

/**
 * v4l2_rect_map_inside()- r should be inside boundary.
 * @r: rect that will be modअगरied
 * @boundary: rect containing the boundary क्रम @r
 */
अटल अंतरभूत व्योम v4l2_rect_map_inside(काष्ठा v4l2_rect *r,
					स्थिर काष्ठा v4l2_rect *boundary)
अणु
	v4l2_rect_set_max_size(r, boundary);
	अगर (r->left < boundary->left)
		r->left = boundary->left;
	अगर (r->top < boundary->top)
		r->top = boundary->top;
	अगर (r->left + r->width > boundary->left + boundary->width)
		r->left = boundary->left + boundary->width - r->width;
	अगर (r->top + r->height > boundary->top + boundary->height)
		r->top = boundary->top + boundary->height - r->height;
पूर्ण

/**
 * v4l2_rect_same_size() - वापस true अगर r1 has the same size as r2
 * @r1: rectangle.
 * @r2: rectangle.
 *
 * Return true अगर both rectangles have the same size.
 */
अटल अंतरभूत bool v4l2_rect_same_size(स्थिर काष्ठा v4l2_rect *r1,
				       स्थिर काष्ठा v4l2_rect *r2)
अणु
	वापस r1->width == r2->width && r1->height == r2->height;
पूर्ण

/**
 * v4l2_rect_same_position() - वापस true अगर r1 has the same position as r2
 * @r1: rectangle.
 * @r2: rectangle.
 *
 * Return true अगर both rectangles have the same position
 */
अटल अंतरभूत bool v4l2_rect_same_position(स्थिर काष्ठा v4l2_rect *r1,
					   स्थिर काष्ठा v4l2_rect *r2)
अणु
	वापस r1->top == r2->top && r1->left == r2->left;
पूर्ण

/**
 * v4l2_rect_equal() - वापस true अगर r1 equals r2
 * @r1: rectangle.
 * @r2: rectangle.
 *
 * Return true अगर both rectangles have the same size and position.
 */
अटल अंतरभूत bool v4l2_rect_equal(स्थिर काष्ठा v4l2_rect *r1,
				   स्थिर काष्ठा v4l2_rect *r2)
अणु
	वापस v4l2_rect_same_size(r1, r2) && v4l2_rect_same_position(r1, r2);
पूर्ण

/**
 * v4l2_rect_पूर्णांकersect() - calculate the पूर्णांकersection of two rects.
 * @r: पूर्णांकersection of @r1 and @r2.
 * @r1: rectangle.
 * @r2: rectangle.
 */
अटल अंतरभूत व्योम v4l2_rect_पूर्णांकersect(काष्ठा v4l2_rect *r,
				       स्थिर काष्ठा v4l2_rect *r1,
				       स्थिर काष्ठा v4l2_rect *r2)
अणु
	पूर्णांक right, bottom;

	r->top = max(r1->top, r2->top);
	r->left = max(r1->left, r2->left);
	bottom = min(r1->top + r1->height, r2->top + r2->height);
	right = min(r1->left + r1->width, r2->left + r2->width);
	r->height = max(0, bottom - r->top);
	r->width = max(0, right - r->left);
पूर्ण

/**
 * v4l2_rect_scale() - scale rect r by to/from
 * @r: rect to be scaled.
 * @from: from rectangle.
 * @to: to rectangle.
 *
 * This scales rectangle @r horizontally by @to->width / @from->width and
 * vertically by @to->height / @from->height.
 *
 * Typically @r is a rectangle inside @from and you want the rectangle as
 * it would appear after scaling @from to @to. So the resulting @r will
 * be the scaled rectangle inside @to.
 */
अटल अंतरभूत व्योम v4l2_rect_scale(काष्ठा v4l2_rect *r,
				   स्थिर काष्ठा v4l2_rect *from,
				   स्थिर काष्ठा v4l2_rect *to)
अणु
	अगर (from->width == 0 || from->height == 0) अणु
		r->left = r->top = r->width = r->height = 0;
		वापस;
	पूर्ण
	r->left = (((r->left - from->left) * to->width) / from->width) & ~1;
	r->width = ((r->width * to->width) / from->width) & ~1;
	r->top = ((r->top - from->top) * to->height) / from->height;
	r->height = (r->height * to->height) / from->height;
पूर्ण

/**
 * v4l2_rect_overlap() - करो r1 and r2 overlap?
 * @r1: rectangle.
 * @r2: rectangle.
 *
 * Returns true अगर @r1 and @r2 overlap.
 */
अटल अंतरभूत bool v4l2_rect_overlap(स्थिर काष्ठा v4l2_rect *r1,
				     स्थिर काष्ठा v4l2_rect *r2)
अणु
	/*
	 * IF the left side of r1 is to the right of the right side of r2 OR
	 *    the left side of r2 is to the right of the right side of r1 THEN
	 * they करो not overlap.
	 */
	अगर (r1->left >= r2->left + r2->width ||
	    r2->left >= r1->left + r1->width)
		वापस false;
	/*
	 * IF the top side of r1 is below the bottom of r2 OR
	 *    the top side of r2 is below the bottom of r1 THEN
	 * they करो not overlap.
	 */
	अगर (r1->top >= r2->top + r2->height ||
	    r2->top >= r1->top + r1->height)
		वापस false;
	वापस true;
पूर्ण

/**
 * v4l2_rect_enबंदd() - is r1 enबंदd in r2?
 * @r1: rectangle.
 * @r2: rectangle.
 *
 * Returns true अगर @r1 is enबंदd in @r2.
 */
अटल अंतरभूत bool v4l2_rect_enबंदd(काष्ठा v4l2_rect *r1,
				      काष्ठा v4l2_rect *r2)
अणु
	अगर (r1->left < r2->left || r1->top < r2->top)
		वापस false;
	अगर (r1->left + r1->width > r2->left + r2->width)
		वापस false;
	अगर (r1->top + r1->height > r2->top + r2->height)
		वापस false;

	वापस true;
पूर्ण

#पूर्ण_अगर
