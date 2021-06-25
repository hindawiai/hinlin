<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम the drm_framebuffer functions
 */

#समावेश <linux/kernel.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "../drm_crtc_internal.h"

#समावेश "test-drm_modeset_common.h"

#घोषणा MIN_WIDTH 4
#घोषणा MAX_WIDTH 4096
#घोषणा MIN_HEIGHT 4
#घोषणा MAX_HEIGHT 4096

काष्ठा drm_framebuffer_test अणु
	पूर्णांक buffer_created;
	काष्ठा drm_mode_fb_cmd2 cmd;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा drm_framebuffer_test createbuffer_tests[] = अणु
अणु .buffer_created = 1, .name = "ABGR8888 normal sizes",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * 600, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 max sizes",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 pitch greater than min required",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH + 1, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 pitch less than min required",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH - 1, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Invalid width",
	.cmd = अणु .width = MAX_WIDTH + 1, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * (MAX_WIDTH + 1), 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Invalid buffer handle",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 0, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "No pixel format",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = 0,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Width 0",
	.cmd = अणु .width = 0, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Height 0",
	.cmd = अणु .width = MAX_WIDTH, .height = 0, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Out of bound height * pitch combination",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च - 1, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 Large buffer offset",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च / 2, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 Set DRM_MODE_FB_MODIFIERS without modifiers",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च / 2, 0, 0 पूर्ण,
		 .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 Valid buffer modifier",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च / 2, 0, 0 पूर्ण, .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण,
		 .flags = DRM_MODE_FB_MODIFIERS, .modअगरier = अणु AFBC_FORMAT_MOD_YTR, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Invalid buffer modifier(DRM_FORMAT_MOD_SAMSUNG_64_32_TILE)",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च / 2, 0, 0 पूर्ण,
		 .pitches = अणु 4 * MAX_WIDTH, 0, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "ABGR8888 Extra pitches without DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु अच_पूर्णांक_उच्च / 2, 0, 0 पूर्ण,
		 .pitches = अणु 4 * MAX_WIDTH, 4 * MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "ABGR8888 Extra pitches with DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_ABGR8888,
		 .handles = अणु 1, 0, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .pitches = अणु 4 * MAX_WIDTH, 4 * MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "NV12 Normal sizes",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .pitches = अणु 600, 600, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "NV12 Max sizes",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 Invalid pitch",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .pitches = अणु MAX_WIDTH, MAX_WIDTH - 1, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 Invalid modifier/missing DRM_MODE_FB_MODIFIERS flag",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, 0, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 different  modifier per-plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, 0, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "NV12 with DRM_FORMAT_MOD_SAMSUNG_64_32_TILE",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 Valid modifiers without DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE,
						       DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 Modifier for inexistent plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु DRM_FORMAT_MOD_SAMSUNG_64_32_TILE, DRM_FORMAT_MOD_SAMSUNG_64_32_TILE,
			       DRM_FORMAT_MOD_SAMSUNG_64_32_TILE पूर्ण,
		 .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "NV12 Handle for inexistent plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS, .pitches = अणु MAX_WIDTH, MAX_WIDTH, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "NV12 Handle for inexistent plane without DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_NV12,
		 .handles = अणु 1, 1, 1 पूर्ण, .pitches = अणु 600, 600, 600 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 Normal sizes",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .pitches = अणु 600, 300, 300 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 DRM_MODE_FB_MODIFIERS set without modifier",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .pitches = अणु 600, 300, 300 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 Max sizes",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2),
						      DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Invalid pitch",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2) - 1,
						      DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 Different pitches",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2) + 1,
						      DIV_ROUND_UP(MAX_WIDTH, 2) + 7 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 Different buffer offsets/pitches",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .offsets = अणु MAX_WIDTH, MAX_WIDTH  + MAX_WIDTH * MAX_HEIGHT,
						      MAX_WIDTH  + 2 * MAX_WIDTH * MAX_HEIGHT पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2) + 1, DIV_ROUND_UP(MAX_WIDTH, 2) + 7 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Modifier set just for plane 0, without DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, 0, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Modifier set just for planes 0, 1, without DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Modifier set just for plane 0, 1, with DRM_MODE_FB_MODIFIERS",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE, 0 पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "YVU420 Valid modifier",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Different modifiers per plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE | AFBC_FORMAT_MOD_YTR,
			       AFBC_FORMAT_MOD_SPARSE पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "YVU420 Modifier for inexistent plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_YVU420,
		 .handles = अणु 1, 1, 1 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE,
			       AFBC_FORMAT_MOD_SPARSE पूर्ण,
		 .pitches = अणु MAX_WIDTH, DIV_ROUND_UP(MAX_WIDTH, 2), DIV_ROUND_UP(MAX_WIDTH, 2) पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "X0L2 Normal sizes",
	.cmd = अणु .width = 600, .height = 600, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 1200, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "X0L2 Max sizes",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 2 * MAX_WIDTH, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "X0L2 Invalid pitch",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 2 * MAX_WIDTH - 1, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "X0L2 Pitch greater than minimum required",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "X0L2 Handle for inexistent plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 1, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
		 .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "X0L2 Offset for inexistent plane, without DRM_MODE_FB_MODIFIERS set",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .offsets = अणु 0, 0, 3 पूर्ण,
		 .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "X0L2 Modifier without DRM_MODE_FB_MODIFIERS set",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, 0, 0 पूर्ण,
	पूर्ण
पूर्ण,
अणु .buffer_created = 1, .name = "X0L2 Valid modifier",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT, .pixel_क्रमmat = DRM_FORMAT_X0L2,
		 .handles = अणु 1, 0, 0 पूर्ण, .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, 0, 0 पूर्ण, .flags = DRM_MODE_FB_MODIFIERS,
	पूर्ण
पूर्ण,
अणु .buffer_created = 0, .name = "X0L2 Modifier for inexistent plane",
	.cmd = अणु .width = MAX_WIDTH, .height = MAX_HEIGHT,
		 .pixel_क्रमmat = DRM_FORMAT_X0L2, .handles = अणु 1, 0, 0 पूर्ण,
		 .pitches = अणु 2 * MAX_WIDTH + 1, 0, 0 पूर्ण,
		 .modअगरier = अणु AFBC_FORMAT_MOD_SPARSE, AFBC_FORMAT_MOD_SPARSE, 0 पूर्ण,
		 .flags = DRM_MODE_FB_MODIFIERS,
	पूर्ण
पूर्ण,
पूर्ण;

अटल काष्ठा drm_framebuffer *fb_create_mock(काष्ठा drm_device *dev,
					      काष्ठा drm_file *file_priv,
					      स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	पूर्णांक *buffer_created = dev->dev_निजी;
	*buffer_created = 1;
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा drm_mode_config_funcs mock_config_funcs = अणु
	.fb_create = fb_create_mock,
पूर्ण;

अटल काष्ठा drm_device mock_drm_device = अणु
	.mode_config = अणु
		.min_width = MIN_WIDTH,
		.max_width = MAX_WIDTH,
		.min_height = MIN_HEIGHT,
		.max_height = MAX_HEIGHT,
		.allow_fb_modअगरiers = true,
		.funcs = &mock_config_funcs,
	पूर्ण,
पूर्ण;

अटल पूर्णांक execute_drm_mode_fb_cmd2(काष्ठा drm_mode_fb_cmd2 *r)
अणु
	पूर्णांक buffer_created = 0;

	mock_drm_device.dev_निजी = &buffer_created;
	drm_पूर्णांकernal_framebuffer_create(&mock_drm_device, r, शून्य);
	वापस buffer_created;
पूर्ण

पूर्णांक igt_check_drm_framebuffer_create(व्योम *ignored)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < ARRAY_SIZE(createbuffer_tests); i++) अणु
		FAIL(createbuffer_tests[i].buffer_created !=
				execute_drm_mode_fb_cmd2(&createbuffer_tests[i].cmd),
		     "Test %d: \"%s\" failed\n", i, createbuffer_tests[i].name);
	पूर्ण

	वापस 0;
पूर्ण
