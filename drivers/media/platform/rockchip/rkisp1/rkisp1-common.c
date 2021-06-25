<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - Common definitions
 *
 * Copyright (C) 2019 Collabora, Ltd.
 */

#समावेश <media/v4l2-rect.h>

#समावेश "rkisp1-common.h"

अटल स्थिर काष्ठा v4l2_rect rkisp1_sd_min_crop = अणु
	.width = RKISP1_ISP_MIN_WIDTH,
	.height = RKISP1_ISP_MIN_HEIGHT,
	.top = 0,
	.left = 0,
पूर्ण;

व्योम rkisp1_sd_adjust_crop_rect(काष्ठा v4l2_rect *crop,
				स्थिर काष्ठा v4l2_rect *bounds)
अणु
	v4l2_rect_set_min_size(crop, &rkisp1_sd_min_crop);
	v4l2_rect_map_inside(crop, bounds);
पूर्ण

व्योम rkisp1_sd_adjust_crop(काष्ठा v4l2_rect *crop,
			   स्थिर काष्ठा v4l2_mbus_framefmt *bounds)
अणु
	काष्ठा v4l2_rect crop_bounds = अणु
		.left = 0,
		.top = 0,
		.width = bounds->width,
		.height = bounds->height,
	पूर्ण;

	rkisp1_sd_adjust_crop_rect(crop, &crop_bounds);
पूर्ण
