<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम the drm_plane_helper functions
 */

#घोषणा pr_fmt(fmt) "drm_plane_helper: " fmt

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_modes.h>

#समावेश "test-drm_modeset_common.h"

अटल व्योम set_src(काष्ठा drm_plane_state *plane_state,
		    अचिन्हित src_x, अचिन्हित src_y,
		    अचिन्हित src_w, अचिन्हित src_h)
अणु
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_w = src_w;
	plane_state->src_h = src_h;
पूर्ण

अटल bool check_src_eq(काष्ठा drm_plane_state *plane_state,
			 अचिन्हित src_x, अचिन्हित src_y,
			 अचिन्हित src_w, अचिन्हित src_h)
अणु
	अगर (plane_state->src.x1 < 0) अणु
		pr_err("src x coordinate %x should never be below 0.\n", plane_state->src.x1);
		drm_rect_debug_prपूर्णांक("src: ", &plane_state->src, true);
		वापस false;
	पूर्ण
	अगर (plane_state->src.y1 < 0) अणु
		pr_err("src y coordinate %x should never be below 0.\n", plane_state->src.y1);
		drm_rect_debug_prपूर्णांक("src: ", &plane_state->src, true);
		वापस false;
	पूर्ण

	अगर (plane_state->src.x1 != src_x ||
	    plane_state->src.y1 != src_y ||
	    drm_rect_width(&plane_state->src) != src_w ||
	    drm_rect_height(&plane_state->src) != src_h) अणु
		drm_rect_debug_prपूर्णांक("src: ", &plane_state->src, true);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम set_crtc(काष्ठा drm_plane_state *plane_state,
		     पूर्णांक crtc_x, पूर्णांक crtc_y,
		     अचिन्हित crtc_w, अचिन्हित crtc_h)
अणु
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_w = crtc_w;
	plane_state->crtc_h = crtc_h;
पूर्ण

अटल bool check_crtc_eq(काष्ठा drm_plane_state *plane_state,
			  पूर्णांक crtc_x, पूर्णांक crtc_y,
			  अचिन्हित crtc_w, अचिन्हित crtc_h)
अणु
	अगर (plane_state->dst.x1 != crtc_x ||
	    plane_state->dst.y1 != crtc_y ||
	    drm_rect_width(&plane_state->dst) != crtc_w ||
	    drm_rect_height(&plane_state->dst) != crtc_h) अणु
		drm_rect_debug_prपूर्णांक("dst: ", &plane_state->dst, false);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक igt_check_plane_state(व्योम *ignored)
अणु
	पूर्णांक ret;

	स्थिर काष्ठा drm_crtc_state crtc_state = अणु
		.crtc = ZERO_SIZE_PTR,
		.enable = true,
		.active = true,
		.mode = अणु
			DRM_MODE("1024x768", 0, 65000, 1024, 1048,
				1184, 1344, 0, 768, 771, 777, 806, 0,
				DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC)
		पूर्ण,
	पूर्ण;
	काष्ठा drm_framebuffer fb = अणु
		.width = 2048,
		.height = 2048
	पूर्ण;
	काष्ठा drm_plane_state plane_state = अणु
		.crtc = ZERO_SIZE_PTR,
		.fb = &fb,
		.rotation = DRM_MODE_ROTATE_0
	पूर्ण;

	/* Simple clipping, no scaling. */
	set_src(&plane_state, 0, 0, fb.width << 16, fb.height << 16);
	set_crtc(&plane_state, 0, 0, fb.width, fb.height);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(ret < 0, "Simple clipping check should pass\n");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 1024 << 16, 768 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));

	/* Rotated clipping + reflection, no scaling. */
	plane_state.rotation = DRM_MODE_ROTATE_90 | DRM_MODE_REFLECT_X;
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(ret < 0, "Rotated clipping check should pass\n");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 768 << 16, 1024 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));
	plane_state.rotation = DRM_MODE_ROTATE_0;

	/* Check whether positioning works correctly. */
	set_src(&plane_state, 0, 0, 1023 << 16, 767 << 16);
	set_crtc(&plane_state, 0, 0, 1023, 767);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(!ret, "Should not be able to position on the crtc with can_position=false\n");

	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, false);
	FAIL(ret < 0, "Simple positioning should work\n");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 1023 << 16, 767 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1023, 767));

	/* Simple scaling tests. */
	set_src(&plane_state, 0, 0, 512 << 16, 384 << 16);
	set_crtc(&plane_state, 0, 0, 1024, 768);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  0x8001,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(!ret, "Upscaling out of range should fail.\n");
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  0x8000,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(ret < 0, "Upscaling exactly 2x should work\n");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 512 << 16, 384 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));

	set_src(&plane_state, 0, 0, 2048 << 16, 1536 << 16);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  0x1ffff, false, false);
	FAIL(!ret, "Downscaling out of range should fail.\n");
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  0x20000, false, false);
	FAIL(ret < 0, "Should succeed with exact scaling limit\n");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 2048 << 16, 1536 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));

	/* Testing rounding errors. */
	set_src(&plane_state, 0, 0, 0x40001, 0x40001);
	set_crtc(&plane_state, 1022, 766, 4, 4);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  0x10001,
						  true, false);
	FAIL(ret < 0, "Should succeed by clipping to exact multiple");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 2 << 16, 2 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 1022, 766, 2, 2));

	set_src(&plane_state, 0x20001, 0x20001, 0x4040001, 0x3040001);
	set_crtc(&plane_state, -2, -2, 1028, 772);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  0x10001,
						  false, false);
	FAIL(ret < 0, "Should succeed by clipping to exact multiple");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0x40002, 0x40002, 1024 << 16, 768 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));

	set_src(&plane_state, 0, 0, 0x3ffff, 0x3ffff);
	set_crtc(&plane_state, 1022, 766, 4, 4);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  0xffff,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, false);
	FAIL(ret < 0, "Should succeed by clipping to exact multiple");
	FAIL_ON(!plane_state.visible);
	/* Should not be rounded to 0x20001, which would be upscaling. */
	FAIL_ON(!check_src_eq(&plane_state, 0, 0, 2 << 16, 2 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 1022, 766, 2, 2));

	set_src(&plane_state, 0x1ffff, 0x1ffff, 0x403ffff, 0x303ffff);
	set_crtc(&plane_state, -2, -2, 1028, 772);
	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  0xffff,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, false);
	FAIL(ret < 0, "Should succeed by clipping to exact multiple");
	FAIL_ON(!plane_state.visible);
	FAIL_ON(!check_src_eq(&plane_state, 0x3fffe, 0x3fffe, 1024 << 16, 768 << 16));
	FAIL_ON(!check_crtc_eq(&plane_state, 0, 0, 1024, 768));

	वापस 0;
पूर्ण
