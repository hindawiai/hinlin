<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __TEST_DRM_MODESET_COMMON_H__
#घोषणा __TEST_DRM_MODESET_COMMON_H__

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/prपूर्णांकk.h>

#घोषणा FAIL(test, msg, ...) \
	करो अणु \
		अगर (test) अणु \
			pr_err("%s/%u: " msg, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
			वापस -EINVAL; \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा FAIL_ON(x) FAIL((x), "%s", "FAIL_ON(" __stringअगरy(x) ")\n")

पूर्णांक igt_drm_rect_clip_scaled_भाग_by_zero(व्योम *ignored);
पूर्णांक igt_drm_rect_clip_scaled_not_clipped(व्योम *ignored);
पूर्णांक igt_drm_rect_clip_scaled_clipped(व्योम *ignored);
पूर्णांक igt_drm_rect_clip_scaled_चिन्हित_vs_अचिन्हित(व्योम *ignored);
पूर्णांक igt_check_plane_state(व्योम *ignored);
पूर्णांक igt_check_drm_क्रमmat_block_width(व्योम *ignored);
पूर्णांक igt_check_drm_क्रमmat_block_height(व्योम *ignored);
पूर्णांक igt_check_drm_क्रमmat_min_pitch(व्योम *ignored);
पूर्णांक igt_check_drm_framebuffer_create(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_fractional_src(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_src_moved(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_fractional_src_moved(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_not_visible(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_no_crtc(व्योम *ignored);
पूर्णांक igt_damage_iter_no_damage_no_fb(व्योम *ignored);
पूर्णांक igt_damage_iter_simple_damage(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_पूर्णांकersect_src(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_outside_src(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_fractional_src(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_पूर्णांकersect_fractional_src(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_outside_fractional_src(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_src_moved(व्योम *ignored);
पूर्णांक igt_damage_iter_single_damage_fractional_src_moved(व्योम *ignored);
पूर्णांक igt_damage_iter_damage(व्योम *ignored);
पूर्णांक igt_damage_iter_damage_one_पूर्णांकersect(व्योम *ignored);
पूर्णांक igt_damage_iter_damage_one_outside(व्योम *ignored);
पूर्णांक igt_damage_iter_damage_src_moved(व्योम *ignored);
पूर्णांक igt_damage_iter_damage_not_visible(व्योम *ignored);
पूर्णांक igt_dp_mst_calc_pbn_mode(व्योम *ignored);
पूर्णांक igt_dp_mst_sideband_msg_req_decode(व्योम *ignored);

#पूर्ण_अगर
