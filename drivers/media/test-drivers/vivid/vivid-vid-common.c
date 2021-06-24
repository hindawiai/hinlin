<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vid-common.c - common video support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"

स्थिर काष्ठा v4l2_dv_timings_cap vivid_dv_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(16, MAX_WIDTH, 16, MAX_HEIGHT, 14000000, 775000000,
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
		V4L2_DV_BT_STD_CVT | V4L2_DV_BT_STD_GTF,
		V4L2_DV_BT_CAP_PROGRESSIVE | V4L2_DV_BT_CAP_INTERLACED)
पूर्ण;

/* ------------------------------------------------------------------
	Basic काष्ठाures
   ------------------------------------------------------------------*/

काष्ठा vivid_fmt vivid_क्रमmats[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 1,
		.buffers = 1,
		.data_offset = अणु PLANE0_DATA_OFFSET पूर्ण,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YVYU,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_VYUY,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV422P,
		.vकरोwnsampling = अणु 1, 1, 1 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV420,
		.vकरोwnsampling = अणु 1, 2, 2 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YVU420,
		.vकरोwnsampling = अणु 1, 2, 2 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV12,
		.vकरोwnsampling = अणु 1, 2 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV21,
		.vकरोwnsampling = अणु 1, 2 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV16,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV61,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV24,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV42,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV555, /* uuuvvvvv ayyyyyuu */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x8000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV565, /* uuuvvvvv yyyyyuuu */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV444, /* uuuuvvvv aaaayyyy */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0xf000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV32, /* ayuv */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x000000ff,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_AYUV32,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x000000ff,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XYUV32,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_VUYA32,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0xff000000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_VUYX32,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_GREY,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_LUMA,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_Y10,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_LUMA,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_Y12,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_LUMA,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_Y16,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_LUMA,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_Y16_BE,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.color_enc = TGP_COLOR_ENC_LUMA,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB332, /* rrrgggbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB565, /* gggbbbbb rrrrrggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB565X, /* rrrrrggg gggbbbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB444, /* ggggbbbb xxxxrrrr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XRGB444, /* ggggbbbb xxxxrrrr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ARGB444, /* ggggbbbb aaaarrrr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x00f0,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBX444, /* bbbbxxxx rrrrgggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBA444, /* bbbbaaaa rrrrgggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x00f0,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XBGR444, /* ggggrrrr xxxxbbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ABGR444, /* ggggrrrr aaaabbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x00f0,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRX444, /* rrrrxxxx bbbbgggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRA444, /* rrrraaaa bbbbgggg  */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x00f0,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB555, /* gggbbbbb xrrrrrgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XRGB555, /* gggbbbbb xrrrrrgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ARGB555, /* gggbbbbb arrrrrgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
		.alpha_mask = 0x8000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBX555, /* ggbbbbbx rrrrrggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBA555, /* ggbbbbba rrrrrggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
		.alpha_mask = 0x8000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XBGR555, /* gggrrrrr xbbbbbgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ABGR555, /* gggrrrrr abbbbbgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
		.alpha_mask = 0x8000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRX555, /* ggrrrrrx bbbbbggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRA555, /* ggrrrrra bbbbbggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.can_करो_overlay = true,
		.alpha_mask = 0x8000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB555X, /* xrrrrrgg gggbbbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XRGB555X, /* xrrrrrgg gggbbbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ARGB555X, /* arrrrrgg gggbbbbb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x0080,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB24, /* rgb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 24 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGR24, /* bgr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 24 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGR666, /* bbbbbbgg ggggrrrr rrxxxxxx */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB32, /* xrgb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGR32, /* bgrx */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XRGB32, /* xrgb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XBGR32, /* bgrx */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ARGB32, /* argb */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x000000ff,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ABGR32, /* bgra */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0xff000000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBX32, /* rgbx */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRX32, /* xbgr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_RGBA32, /* rgba */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0x000000ff,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_BGRA32, /* abgr */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
		.alpha_mask = 0xff000000,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SBGGR8, /* Bayer BG/GR */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGBRG8, /* Bayer GB/RG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGRBG8, /* Bayer GR/BG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SRGGB8, /* Bayer RG/GB */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 8 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SBGGR10, /* Bayer BG/GR */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGBRG10, /* Bayer GB/RG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGRBG10, /* Bayer GR/BG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SRGGB10, /* Bayer RG/GB */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SBGGR12, /* Bayer BG/GR */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGBRG12, /* Bayer GB/RG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGRBG12, /* Bayer GR/BG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SRGGB12, /* Bayer RG/GB */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SBGGR16, /* Bayer BG/GR */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGBRG16, /* Bayer GB/RG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SGRBG16, /* Bayer GR/BG */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_SRGGB16, /* Bayer RG/GB */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_HSV24, /* HSV 24bits */
		.color_enc = TGP_COLOR_ENC_HSV,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 24 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_HSV32, /* HSV 32bits */
		.color_enc = TGP_COLOR_ENC_HSV,
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 32 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,

	/* Multiplanar क्रमmats */

	अणु
		.fourcc   = V4L2_PIX_FMT_NV16M,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 2,
		.data_offset = अणु PLANE0_DATA_OFFSET, 0 पूर्ण,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV61M,
		.vकरोwnsampling = अणु 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 2,
		.data_offset = अणु 0, PLANE0_DATA_OFFSET पूर्ण,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV420M,
		.vकरोwnsampling = अणु 1, 2, 2 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YVU420M,
		.vकरोwnsampling = अणु 1, 2, 2 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV12M,
		.vकरोwnsampling = अणु 1, 2 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 2,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_NV21M,
		.vकरोwnsampling = अणु 1, 2 पूर्ण,
		.bit_depth = अणु 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 2,
		.buffers = 2,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV422M,
		.vकरोwnsampling = अणु 1, 1, 1 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YVU422M,
		.vकरोwnsampling = अणु 1, 1, 1 पूर्ण,
		.bit_depth = अणु 8, 4, 4 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YUV444M,
		.vकरोwnsampling = अणु 1, 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_YVU444M,
		.vकरोwnsampling = अणु 1, 1, 1 पूर्ण,
		.bit_depth = अणु 8, 8, 8 पूर्ण,
		.color_enc = TGP_COLOR_ENC_YCBCR,
		.planes   = 3,
		.buffers = 3,
	पूर्ण,
पूर्ण;

/* There are this many multiplanar क्रमmats in the list */
#घोषणा VIVID_MPLANAR_FORMATS 10

स्थिर काष्ठा vivid_fmt *vivid_get_क्रमmat(काष्ठा vivid_dev *dev, u32 pixelक्रमmat)
अणु
	स्थिर काष्ठा vivid_fmt *fmt;
	अचिन्हित k;

	क्रम (k = 0; k < ARRAY_SIZE(vivid_क्रमmats); k++) अणु
		fmt = &vivid_क्रमmats[k];
		अगर (fmt->fourcc == pixelक्रमmat)
			अगर (fmt->buffers == 1 || dev->multiplanar)
				वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

bool vivid_vid_can_loop(काष्ठा vivid_dev *dev)
अणु
	अगर (dev->src_rect.width != dev->sink_rect.width ||
	    dev->src_rect.height != dev->sink_rect.height)
		वापस false;
	अगर (dev->fmt_cap->fourcc != dev->fmt_out->fourcc)
		वापस false;
	अगर (dev->field_cap != dev->field_out)
		वापस false;
	/*
	 * While this can be supported, it is just too much work
	 * to actually implement.
	 */
	अगर (dev->field_cap == V4L2_FIELD_SEQ_TB ||
	    dev->field_cap == V4L2_FIELD_SEQ_BT)
		वापस false;
	अगर (vivid_is_svid_cap(dev) && vivid_is_svid_out(dev)) अणु
		अगर (!(dev->std_cap[dev->input] & V4L2_STD_525_60) !=
		    !(dev->std_out & V4L2_STD_525_60))
			वापस false;
		वापस true;
	पूर्ण
	अगर (vivid_is_hdmi_cap(dev) && vivid_is_hdmi_out(dev))
		वापस true;
	वापस false;
पूर्ण

व्योम vivid_send_source_change(काष्ठा vivid_dev *dev, अचिन्हित type)
अणु
	काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_SOURCE_CHANGE,
		.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
	पूर्ण;
	अचिन्हित i;

	क्रम (i = 0; i < dev->num_inमाला_दो; i++) अणु
		ev.id = i;
		अगर (dev->input_type[i] == type) अणु
			अगर (video_is_रेजिस्टरed(&dev->vid_cap_dev) && dev->has_vid_cap)
				v4l2_event_queue(&dev->vid_cap_dev, &ev);
			अगर (video_is_रेजिस्टरed(&dev->vbi_cap_dev) && dev->has_vbi_cap)
				v4l2_event_queue(&dev->vbi_cap_dev, &ev);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Conversion function that converts a single-planar क्रमmat to a
 * single-plane multiplanar क्रमmat.
 */
व्योम fmt_sp2mp(स्थिर काष्ठा v4l2_क्रमmat *sp_fmt, काष्ठा v4l2_क्रमmat *mp_fmt)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &mp_fmt->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *ppix = &mp->plane_fmt[0];
	स्थिर काष्ठा v4l2_pix_क्रमmat *pix = &sp_fmt->fmt.pix;
	bool is_out = sp_fmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT;

	स_रखो(mp->reserved, 0, माप(mp->reserved));
	mp_fmt->type = is_out ? V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	mp->width = pix->width;
	mp->height = pix->height;
	mp->pixelक्रमmat = pix->pixelक्रमmat;
	mp->field = pix->field;
	mp->colorspace = pix->colorspace;
	mp->xfer_func = pix->xfer_func;
	/* Also copies hsv_enc */
	mp->ycbcr_enc = pix->ycbcr_enc;
	mp->quantization = pix->quantization;
	mp->num_planes = 1;
	mp->flags = pix->flags;
	ppix->sizeimage = pix->sizeimage;
	ppix->bytesperline = pix->bytesperline;
	स_रखो(ppix->reserved, 0, माप(ppix->reserved));
पूर्ण

पूर्णांक fmt_sp2mp_func(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f, fmtfunc func)
अणु
	काष्ठा v4l2_क्रमmat fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &fmt.fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *ppix = &mp->plane_fmt[0];
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	पूर्णांक ret;

	/* Converts to a mplane क्रमmat */
	fmt_sp2mp(f, &fmt);
	/* Passes it to the generic mplane क्रमmat function */
	ret = func(file, priv, &fmt);
	/* Copies back the mplane data to the single plane क्रमmat */
	pix->width = mp->width;
	pix->height = mp->height;
	pix->pixelक्रमmat = mp->pixelक्रमmat;
	pix->field = mp->field;
	pix->colorspace = mp->colorspace;
	pix->xfer_func = mp->xfer_func;
	/* Also copies hsv_enc */
	pix->ycbcr_enc = mp->ycbcr_enc;
	pix->quantization = mp->quantization;
	pix->sizeimage = ppix->sizeimage;
	pix->bytesperline = ppix->bytesperline;
	pix->flags = mp->flags;
	वापस ret;
पूर्ण

पूर्णांक vivid_vid_adjust_sel(अचिन्हित flags, काष्ठा v4l2_rect *r)
अणु
	अचिन्हित w = r->width;
	अचिन्हित h = r->height;

	/* sanitize w and h in हाल someone passes ~0 as the value */
	w &= 0xffff;
	h &= 0xffff;
	अगर (!(flags & V4L2_SEL_FLAG_LE)) अणु
		w++;
		h++;
		अगर (w < 2)
			w = 2;
		अगर (h < 2)
			h = 2;
	पूर्ण
	अगर (!(flags & V4L2_SEL_FLAG_GE)) अणु
		अगर (w > MAX_WIDTH)
			w = MAX_WIDTH;
		अगर (h > MAX_HEIGHT)
			h = MAX_HEIGHT;
	पूर्ण
	w = w & ~1;
	h = h & ~1;
	अगर (w < 2 || h < 2)
		वापस -दुस्फल;
	अगर (w > MAX_WIDTH || h > MAX_HEIGHT)
		वापस -दुस्फल;
	अगर (r->top < 0)
		r->top = 0;
	अगर (r->left < 0)
		r->left = 0;
	/* sanitize left and top in हाल someone passes ~0 as the value */
	r->left &= 0xfffe;
	r->top &= 0xfffe;
	अगर (r->left + w > MAX_WIDTH)
		r->left = MAX_WIDTH - w;
	अगर (r->top + h > MAX_HEIGHT)
		r->top = MAX_HEIGHT - h;
	अगर ((flags & (V4L2_SEL_FLAG_GE | V4L2_SEL_FLAG_LE)) ==
			(V4L2_SEL_FLAG_GE | V4L2_SEL_FLAG_LE) &&
	    (r->width != w || r->height != h))
		वापस -दुस्फल;
	r->width = w;
	r->height = h;
	वापस 0;
पूर्ण

पूर्णांक vivid_क्रमागत_fmt_vid(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा vivid_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(vivid_क्रमmats) -
	    (dev->multiplanar ? 0 : VIVID_MPLANAR_FORMATS))
		वापस -EINVAL;

	fmt = &vivid_क्रमmats[f->index];

	f->pixelक्रमmat = fmt->fourcc;

	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस 0;
	/*
	 * For capture devices, we support the CSC API.
	 * We allow userspace to:
	 * 1. set the colorspace
	 * 2. set the xfer_func
	 * 3. set the ycbcr_enc on YUV क्रमmats
	 * 4. set the hsv_enc on HSV क्रमmats
	 * 5. set the quantization on YUV and RGB क्रमmats
	 */
	f->flags |= V4L2_FMT_FLAG_CSC_COLORSPACE;
	f->flags |= V4L2_FMT_FLAG_CSC_XFER_FUNC;

	अगर (fmt->color_enc == TGP_COLOR_ENC_YCBCR) अणु
		f->flags |= V4L2_FMT_FLAG_CSC_YCBCR_ENC;
		f->flags |= V4L2_FMT_FLAG_CSC_QUANTIZATION;
	पूर्ण अन्यथा अगर (fmt->color_enc == TGP_COLOR_ENC_HSV) अणु
		f->flags |= V4L2_FMT_FLAG_CSC_HSV_ENC;
	पूर्ण अन्यथा अगर (fmt->color_enc == TGP_COLOR_ENC_RGB) अणु
		f->flags |= V4L2_FMT_FLAG_CSC_QUANTIZATION;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		अगर (!vivid_is_sdtv_cap(dev))
			वापस -ENODATA;
		*id = dev->std_cap[dev->input];
	पूर्ण अन्यथा अणु
		अगर (!vivid_is_svid_out(dev))
			वापस -ENODATA;
		*id = dev->std_out;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		अगर (!vivid_is_hdmi_cap(dev))
			वापस -ENODATA;
		*timings = dev->dv_timings_cap[dev->input];
	पूर्ण अन्यथा अणु
		अगर (!vivid_is_hdmi_out(dev))
			वापस -ENODATA;
		*timings = dev->dv_timings_out;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागत_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		अगर (!vivid_is_hdmi_cap(dev))
			वापस -ENODATA;
	पूर्ण अन्यथा अणु
		अगर (!vivid_is_hdmi_out(dev))
			वापस -ENODATA;
	पूर्ण
	वापस v4l2_क्रमागत_dv_timings_cap(timings, &vivid_dv_timings_cap,
			शून्य, शून्य);
पूर्ण

पूर्णांक vidioc_dv_timings_cap(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);

	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		अगर (!vivid_is_hdmi_cap(dev))
			वापस -ENODATA;
	पूर्ण अन्यथा अणु
		अगर (!vivid_is_hdmi_out(dev))
			वापस -ENODATA;
	पूर्ण
	*cap = vivid_dv_timings_cap;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_edid(काष्ठा file *file, व्योम *_fh,
			 काष्ठा v4l2_edid *edid)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा cec_adapter *adap;

	स_रखो(edid->reserved, 0, माप(edid->reserved));
	अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
		अगर (edid->pad >= dev->num_inमाला_दो)
			वापस -EINVAL;
		अगर (dev->input_type[edid->pad] != HDMI)
			वापस -EINVAL;
		adap = dev->cec_rx_adap;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक bus_idx;

		अगर (edid->pad >= dev->num_outमाला_दो)
			वापस -EINVAL;
		अगर (dev->output_type[edid->pad] != HDMI)
			वापस -EINVAL;
		अगर (!dev->display_present[edid->pad])
			वापस -ENODATA;
		bus_idx = dev->cec_output2bus_map[edid->pad];
		adap = dev->cec_tx_adap[bus_idx];
	पूर्ण
	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = dev->edid_blocks;
		वापस 0;
	पूर्ण
	अगर (dev->edid_blocks == 0)
		वापस -ENODATA;
	अगर (edid->start_block >= dev->edid_blocks)
		वापस -EINVAL;
	अगर (edid->blocks > dev->edid_blocks - edid->start_block)
		edid->blocks = dev->edid_blocks - edid->start_block;
	अगर (adap)
		v4l2_set_edid_phys_addr(dev->edid, dev->edid_blocks * 128, adap->phys_addr);
	स_नकल(edid->edid, dev->edid + edid->start_block * 128, edid->blocks * 128);
	वापस 0;
पूर्ण
