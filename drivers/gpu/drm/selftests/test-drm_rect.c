<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम the drm_rect functions
 */

#घोषणा pr_fmt(fmt) "drm_rect: " fmt

#समावेश <linux/सीमा.स>

#समावेश <drm/drm_rect.h>

#समावेश "test-drm_modeset_common.h"

पूर्णांक igt_drm_rect_clip_scaled_भाग_by_zero(व्योम *ignored)
अणु
	काष्ठा drm_rect src, dst, clip;
	bool visible;

	/*
	 * Make sure we करोn't भागide by zero when dst
	 * width/height is zero and dst and clip करो not पूर्णांकersect.
	 */
	drm_rect_init(&src, 0, 0, 0, 0);
	drm_rect_init(&dst, 0, 0, 0, 0);
	drm_rect_init(&clip, 1, 1, 1, 1);
	visible = drm_rect_clip_scaled(&src, &dst, &clip);
	FAIL(visible, "Destination not be visible\n");
	FAIL(drm_rect_visible(&src), "Source should not be visible\n");

	drm_rect_init(&src, 0, 0, 0, 0);
	drm_rect_init(&dst, 3, 3, 0, 0);
	drm_rect_init(&clip, 1, 1, 1, 1);
	visible = drm_rect_clip_scaled(&src, &dst, &clip);
	FAIL(visible, "Destination not be visible\n");
	FAIL(drm_rect_visible(&src), "Source should not be visible\n");

	वापस 0;
पूर्ण

पूर्णांक igt_drm_rect_clip_scaled_not_clipped(व्योम *ignored)
अणु
	काष्ठा drm_rect src, dst, clip;
	bool visible;

	/* 1:1 scaling */
	drm_rect_init(&src, 0, 0, 1 << 16, 1 << 16);
	drm_rect_init(&dst, 0, 0, 1, 1);
	drm_rect_init(&clip, 0, 0, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 1 << 16 ||
	     src.y1 != 0 || src.y2 != 1 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 1 ||
	     dst.y1 != 0 || dst.y2 != 1,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 2:1 scaling */
	drm_rect_init(&src, 0, 0, 2 << 16, 2 << 16);
	drm_rect_init(&dst, 0, 0, 1, 1);
	drm_rect_init(&clip, 0, 0, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 2 << 16 ||
	     src.y1 != 0 || src.y2 != 2 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 1 ||
	     dst.y1 != 0 || dst.y2 != 1,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 1:2 scaling */
	drm_rect_init(&src, 0, 0, 1 << 16, 1 << 16);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 0, 0, 2, 2);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 1 << 16 ||
	     src.y1 != 0 || src.y2 != 1 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 2 ||
	     dst.y1 != 0 || dst.y2 != 2,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	वापस 0;
पूर्ण

पूर्णांक igt_drm_rect_clip_scaled_clipped(व्योम *ignored)
अणु
	काष्ठा drm_rect src, dst, clip;
	bool visible;

	/* 1:1 scaling top/left clip */
	drm_rect_init(&src, 0, 0, 2 << 16, 2 << 16);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 0, 0, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 1 << 16 ||
	     src.y1 != 0 || src.y2 != 1 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 1 ||
	     dst.y1 != 0 || dst.y2 != 1,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 1:1 scaling bottom/right clip */
	drm_rect_init(&src, 0, 0, 2 << 16, 2 << 16);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 1, 1, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 1 << 16 || src.x2 != 2 << 16 ||
	     src.y1 != 1 << 16 || src.y2 != 2 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 1 || dst.x2 != 2 ||
	     dst.y1 != 1 || dst.y2 != 2,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 2:1 scaling top/left clip */
	drm_rect_init(&src, 0, 0, 4 << 16, 4 << 16);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 0, 0, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 2 << 16 ||
	     src.y1 != 0 || src.y2 != 2 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 1 ||
	     dst.y1 != 0 || dst.y2 != 1,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 2:1 scaling bottom/right clip */
	drm_rect_init(&src, 0, 0, 4 << 16, 4 << 16);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 1, 1, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 2 << 16 || src.x2 != 4 << 16 ||
	     src.y1 != 2 << 16 || src.y2 != 4 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 1 || dst.x2 != 2 ||
	     dst.y1 != 1 || dst.y2 != 2,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 1:2 scaling top/left clip */
	drm_rect_init(&src, 0, 0, 2 << 16, 2 << 16);
	drm_rect_init(&dst, 0, 0, 4, 4);
	drm_rect_init(&clip, 0, 0, 2, 2);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 0 || src.x2 != 1 << 16 ||
	     src.y1 != 0 || src.y2 != 1 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 0 || dst.x2 != 2 ||
	     dst.y1 != 0 || dst.y2 != 2,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	/* 1:2 scaling bottom/right clip */
	drm_rect_init(&src, 0, 0, 2 << 16, 2 << 16);
	drm_rect_init(&dst, 0, 0, 4, 4);
	drm_rect_init(&clip, 2, 2, 2, 2);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(src.x1 != 1 << 16 || src.x2 != 2 << 16 ||
	     src.y1 != 1 << 16 || src.y2 != 2 << 16,
	     "Source badly clipped\n");
	FAIL(dst.x1 != 2 || dst.x2 != 4 ||
	     dst.y1 != 2 || dst.y2 != 4,
	     "Destination badly clipped\n");
	FAIL(!visible, "Destination should be visible\n");
	FAIL(!drm_rect_visible(&src), "Source should be visible\n");

	वापस 0;
पूर्ण

पूर्णांक igt_drm_rect_clip_scaled_चिन्हित_vs_अचिन्हित(व्योम *ignored)
अणु
	काष्ठा drm_rect src, dst, clip;
	bool visible;

	/*
	 * 'clip.x2 - dst.x1 >= dst width' could result a negative
	 * src rectangle width which is no दीर्घer expected by the
	 * code as it's using अचिन्हित types. This could lead to
	 * the clipped source rectangle appering visible when it
	 * should have been fully clipped. Make sure both rectangles
	 * end up invisible.
	 */
	drm_rect_init(&src, 0, 0, पूर्णांक_उच्च, पूर्णांक_उच्च);
	drm_rect_init(&dst, 0, 0, 2, 2);
	drm_rect_init(&clip, 3, 3, 1, 1);

	visible = drm_rect_clip_scaled(&src, &dst, &clip);

	FAIL(visible, "Destination should not be visible\n");
	FAIL(drm_rect_visible(&src), "Source should not be visible\n");

	वापस 0;
पूर्ण
