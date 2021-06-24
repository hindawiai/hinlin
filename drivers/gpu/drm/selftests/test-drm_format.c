<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम the drm_क्रमmat functions
 */

#घोषणा pr_fmt(fmt) "drm_format: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>

#समावेश <drm/drm_fourcc.h>

#समावेश "test-drm_modeset_common.h"

पूर्णांक igt_check_drm_क्रमmat_block_width(व्योम *ignored)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = शून्य;

	/* Test invalid arguments */
	FAIL_ON(drm_क्रमmat_info_block_width(info, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, -1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 1) != 0);

	/* Test 1 plane क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_XRGB4444);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, -1) != 0);

	/* Test 2 planes क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_NV12);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 2) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, -1) != 0);

	/* Test 3 planes क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_YUV422);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 2) != 1);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 3) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, -1) != 0);

	/* Test a tiled क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_X0L0);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 0) != 2);
	FAIL_ON(drm_क्रमmat_info_block_width(info, 1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_width(info, -1) != 0);

	वापस 0;
पूर्ण

पूर्णांक igt_check_drm_क्रमmat_block_height(व्योम *ignored)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = शून्य;

	/* Test invalid arguments */
	FAIL_ON(drm_क्रमmat_info_block_height(info, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, -1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 1) != 0);

	/* Test 1 plane क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_XRGB4444);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, -1) != 0);

	/* Test 2 planes क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_NV12);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 2) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, -1) != 0);

	/* Test 3 planes क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_YUV422);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 0) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 2) != 1);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 3) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, -1) != 0);

	/* Test a tiled क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_X0L0);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 0) != 2);
	FAIL_ON(drm_क्रमmat_info_block_height(info, 1) != 0);
	FAIL_ON(drm_क्रमmat_info_block_height(info, -1) != 0);

	वापस 0;
पूर्ण

पूर्णांक igt_check_drm_क्रमmat_min_pitch(व्योम *ignored)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = शून्य;

	/* Test invalid arguments */
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	/* Test 1 plane 8 bits per pixel क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_RGB332);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 640);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 1024);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 1920);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 4096);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 671);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, (अच_पूर्णांक_उच्च - 1)) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1));

	/* Test 1 plane 16 bits per pixel क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_XRGB4444);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 4);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 1280);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 2048);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 3840);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 8192);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 1342);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च * 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, (अच_पूर्णांक_उच्च - 1)) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) * 2);

	/* Test 1 plane 24 bits per pixel क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_RGB888);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 3);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 6);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 1920);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 3072);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 5760);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 12288);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 2013);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च * 3);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च - 1) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) * 3);

	/* Test 1 plane 32 bits per pixel क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_ABGR8888);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 4);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 8);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 2560);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 4096);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 7680);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 16384);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 2684);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च * 4);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च - 1) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) * 4);

	/* Test 2 planes क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_NV12);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 1) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 1) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 640);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 320) != 640);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 1024);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 512) != 1024);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 1920);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 960) != 1920);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 4096);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 2048) != 4096);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 671);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 336) != 672);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, अच_पूर्णांक_उच्च / 2 + 1) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च + 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, (अच_पूर्णांक_उच्च - 1)) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1));
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, (अच_पूर्णांक_उच्च - 1) /  2) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1));

	/* Test 3 planes 8 bits per pixel क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_YUV422);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 3, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 1) != 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 2) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 2) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 640);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 320) != 320);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 320) != 320);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 1024);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 512) != 512);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 512) != 512);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 1920);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 960) != 960);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 960) != 960);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 4096);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 2048) != 2048);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 2048) != 2048);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 671);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 336) != 336);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, 336) != 336);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, अच_पूर्णांक_उच्च / 2 + 1) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च / 2 + 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, अच_पूर्णांक_उच्च / 2 + 1) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च / 2 + 1);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, (अच_पूर्णांक_उच्च - 1) / 2) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) / 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, (अच_पूर्णांक_उच्च - 1) / 2) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) / 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 2, (अच_पूर्णांक_उच्च - 1) / 2) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) / 2);

	/* Test tiled क्रमmat */
	info = drm_क्रमmat_info(DRM_FORMAT_X0L2);
	FAIL_ON(!info);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, -1, 0) != 0);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 1, 0) != 0);

	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1) != 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 2) != 4);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 640) != 1280);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1024) != 2048);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 1920) != 3840);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 4096) != 8192);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, 671) != 1342);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च) !=
			(uपूर्णांक64_t)अच_पूर्णांक_उच्च * 2);
	FAIL_ON(drm_क्रमmat_info_min_pitch(info, 0, अच_पूर्णांक_उच्च - 1) !=
			(uपूर्णांक64_t)(अच_पूर्णांक_उच्च - 1) * 2);

	वापस 0;
पूर्ण
