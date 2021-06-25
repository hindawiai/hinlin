<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_enc.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Jeongtae Park	<jtp.park@samsung.com>
 * Kamil Debski		<k.debski@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_ctrl.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_enc.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_opr.h"

#घोषणा DEF_SRC_FMT_ENC	V4L2_PIX_FMT_NV12M
#घोषणा DEF_DST_FMT_ENC	V4L2_PIX_FMT_H264

अटल काष्ठा s5p_mfc_fmt क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12MT_16X16,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V6_BIT | MFC_V7_BIT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12MT,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V5_BIT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12M,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21M,
		.codec_mode	= S5P_MFC_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
		.versions	= MFC_V6PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_H264,
		.codec_mode	= S5P_MFC_CODEC_H264_ENC,
		.type		= MFC_FMT_ENC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_MPEG4,
		.codec_mode	= S5P_MFC_CODEC_MPEG4_ENC,
		.type		= MFC_FMT_ENC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_H263,
		.codec_mode	= S5P_MFC_CODEC_H263_ENC,
		.type		= MFC_FMT_ENC,
		.num_planes	= 1,
		.versions	= MFC_V5PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VP8,
		.codec_mode	= S5P_MFC_CODEC_VP8_ENC,
		.type		= MFC_FMT_ENC,
		.num_planes	= 1,
		.versions	= MFC_V7PLUS_BITS,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_HEVC,
		.codec_mode	= S5P_FIMV_CODEC_HEVC_ENC,
		.type		= MFC_FMT_ENC,
		.num_planes	= 1,
		.versions	= MFC_V10_BIT,
	पूर्ण,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)
अटल काष्ठा s5p_mfc_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix_mp.pixelक्रमmat &&
		    क्रमmats[i].type == t)
			वापस &क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mfc_control controls[] = अणु
	अणु
		.id = V4L2_CID_MPEG_VIDEO_GOP_SIZE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 12,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE,
		.maximum = V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES,
		.शेष_value = V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 1,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 1900,
		.maximum = (1 << 30) - 1,
		.step = 1,
		.शेष_value = 1900,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_PADDING,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Padding Control Enable",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Padding Color YUV Value",
		.minimum = 0,
		.maximum = (1 << 25) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_BITRATE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 1,
		.maximum = (1 << 30) - 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Rate Control Reaction Coeff.",
		.minimum = 1,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "Force frame type",
		.minimum = V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_DISABLED,
		.maximum = V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_NOT_CODED,
		.शेष_value = V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_DISABLED,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME,
		.type = V4L2_CTRL_TYPE_BUTTON,
		.minimum = 0,
		.maximum = 0,
		.step = 0,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VBV_SIZE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Horizontal MV Search Range",
		.minimum = 16,
		.maximum = 128,
		.step = 16,
		.शेष_value = 32,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Vertical MV Search Range",
		.minimum = 16,
		.maximum = 128,
		.step = 16,
		.शेष_value = 32,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEADER_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE,
		.maximum = V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		.शेष_value = V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.name = "Frame Skip Enable",
		.minimum = V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_DISABLED,
		.maximum = V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT,
		.menu_skip_mask = 0,
		.शेष_value = V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_DISABLED,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.maximum = V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT,
		.शेष_value = V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_DISABLED,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Fixed Target Bit Enable",
		.minimum = 0,
		.maximum = 1,
		.शेष_value = 0,
		.step = 1,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_B_FRAMES,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 2,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE,
		.maximum = V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH,
		.शेष_value = V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE,
		.menu_skip_mask = ~(
				(1 << V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
				(1 << V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
				(1 << V4L2_MPEG_VIDEO_H264_PROखाता_HIGH)
				),
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_H264_LEVEL_1_0,
		.maximum = V4L2_MPEG_VIDEO_H264_LEVEL_4_0,
		.शेष_value = V4L2_MPEG_VIDEO_H264_LEVEL_1_0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_MPEG4_LEVEL_0,
		.maximum = V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
		.शेष_value = V4L2_MPEG_VIDEO_MPEG4_LEVEL_0,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED,
		.maximum = V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY,
		.शेष_value = V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = -6,
		.maximum = 6,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = -6,
		.maximum = 6,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC,
		.maximum = V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC,
		.शेष_value = V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "The Number of Ref. Pic for P",
		.minimum = 1,
		.maximum = 2,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_MIN_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_MAX_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 51,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H263 I-Frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H263_MIN_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H263 Minimum QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H263_MAX_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H263 Maximum QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 31,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H263 P frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H263 B frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "MPEG4 I-Frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "MPEG4 Minimum QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "MPEG4 Maximum QP value",
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 51,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "MPEG4 P frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "MPEG4 B frame QP value",
		.minimum = 1,
		.maximum = 31,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Dark Reg Adaptive RC",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Smooth Reg Adaptive RC",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Static Reg Adaptive RC",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Activity Reg Adaptive RC",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_UNSPECIFIED,
		.maximum = V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_EXTENDED,
		.शेष_value = V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_UNSPECIFIED,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_GOP_CLOSURE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_I_PERIOD,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE,
		.maximum = V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE,
		.शेष_value = V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_MPEG4_QPEL,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS,
		.type = V4L2_CTRL_TYPE_INTEGER_MENU,
		.maximum = V4L2_CID_MPEG_VIDEO_VPX_8_PARTITIONS,
		.शेष_value = V4L2_CID_MPEG_VIDEO_VPX_1_PARTITION,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES,
		.type = V4L2_CTRL_TYPE_INTEGER_MENU,
		.maximum = V4L2_CID_MPEG_VIDEO_VPX_2_REF_FRAME,
		.शेष_value = V4L2_CID_MPEG_VIDEO_VPX_1_REF_FRAME,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 63,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 7,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_USE_PREV,
		.maximum = V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_USE_REF_PERIOD,
		.शेष_value = V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_USE_PREV,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_MAX_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 127,
		.step = 1,
		.शेष_value = 127,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_MIN_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 11,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 127,
		.step = 1,
		.शेष_value = 10,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 127,
		.step = 1,
		.शेष_value = 10,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_VP8_PROखाता,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_VP8_PROखाता_0,
		.maximum = V4L2_MPEG_VIDEO_VP8_PROखाता_3,
		.शेष_value = V4L2_MPEG_VIDEO_VP8_PROखाता_0,
		.menu_skip_mask = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "HEVC I Frame QP Value",
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "HEVC P Frame QP Value",
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_PROखाता,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN,
		.maximum = V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_LEVEL,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_LEVEL_1,
		.maximum = V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_LEVEL_1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_TIER,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_TIER_MAIN,
		.maximum = V4L2_MPEG_VIDEO_HEVC_TIER_HIGH,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_TIER_MAIN,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 1,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 1,
		.maximum = 2,
		.step = 1,
		.शेष_value = 1,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_REFRESH_NONE,
		.maximum = V4L2_MPEG_VIDEO_HEVC_REFRESH_IDR,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_REFRESH_NONE,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED,
		.maximum = V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_HIERARCHICAL_CODING_B,
		.maximum = V4L2_MPEG_VIDEO_HEVC_HIERARCHICAL_CODING_P,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_HIERARCHICAL_CODING_B,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 6,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 51,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = पूर्णांक_न्यून,
		.maximum = पूर्णांक_उच्च,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 4,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = (1 << 16) - 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = -6,
		.maximum = 6,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = -6,
		.maximum = 6,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD,
		.type = V4L2_CTRL_TYPE_MENU,
		.minimum = V4L2_MPEG_VIDEO_HEVC_SIZE_0,
		.maximum = V4L2_MPEG_VIDEO_HEVC_SIZE_4,
		.step = 1,
		.शेष_value = V4L2_MPEG_VIDEO_HEVC_SIZE_0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.शेष_value = 0,
	पूर्ण,
	अणु
		.id = V4L2_CID_MIN_BUFFERS_FOR_OUTPUT,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Minimum number of output bufs",
		.minimum = 1,
		.maximum = 32,
		.step = 1,
		.शेष_value = 1,
		.is_अस्थिर = 1,
	पूर्ण,
पूर्ण;

#घोषणा NUM_CTRLS ARRAY_SIZE(controls)
अटल स्थिर अक्षर * स्थिर *mfc51_get_menu(u32 id)
अणु
	अटल स्थिर अक्षर * स्थिर mfc51_video_frame_skip[] = अणु
		"Disabled",
		"Level Limit",
		"VBV/CPB Limit",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mfc51_video_क्रमce_frame[] = अणु
		"Disabled",
		"I Frame",
		"Not Coded",
		शून्य,
	पूर्ण;
	चयन (id) अणु
	हाल V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE:
		वापस mfc51_video_frame_skip;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE:
		वापस mfc51_video_क्रमce_frame;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक s5p_mfc_ctx_पढ़ोy(काष्ठा s5p_mfc_ctx *ctx)
अणु
	mfc_debug(2, "src=%d, dst=%d, state=%d\n",
		  ctx->src_queue_cnt, ctx->dst_queue_cnt, ctx->state);
	/* context is पढ़ोy to make header */
	अगर (ctx->state == MFCINST_GOT_INST && ctx->dst_queue_cnt >= 1)
		वापस 1;
	/* context is पढ़ोy to encode a frame */
	अगर ((ctx->state == MFCINST_RUNNING ||
		ctx->state == MFCINST_HEAD_PRODUCED) &&
		ctx->src_queue_cnt >= 1 && ctx->dst_queue_cnt >= 1)
		वापस 1;
	/* context is पढ़ोy to encode reमुख्यing frames */
	अगर (ctx->state == MFCINST_FINISHING &&
		ctx->dst_queue_cnt >= 1)
		वापस 1;
	mfc_debug(2, "ctx is not ready\n");
	वापस 0;
पूर्ण

अटल व्योम cleanup_ref_queue(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_buf *mb_entry;

	/* move buffers in ref queue to src queue */
	जबतक (!list_empty(&ctx->ref_queue)) अणु
		mb_entry = list_entry((&ctx->ref_queue)->next,
						काष्ठा s5p_mfc_buf, list);
		list_del(&mb_entry->list);
		ctx->ref_queue_cnt--;
		list_add_tail(&mb_entry->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
	पूर्ण
	mfc_debug(2, "enc src count: %d, enc ref count: %d\n",
		  ctx->src_queue_cnt, ctx->ref_queue_cnt);
	INIT_LIST_HEAD(&ctx->ref_queue);
	ctx->ref_queue_cnt = 0;
पूर्ण

अटल पूर्णांक enc_pre_seq_start(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	अचिन्हित दीर्घ dst_addr;
	अचिन्हित पूर्णांक dst_size;

	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_hw_call(dev->mfc_ops, set_enc_stream_buffer, ctx, dst_addr,
			dst_size);
	वापस 0;
पूर्ण

अटल पूर्णांक enc_post_seq_start(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_buf *dst_mb;
	अचिन्हित पूर्णांक enc_pb_count;

	अगर (p->seq_hdr_mode == V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE) अणु
		अगर (!list_empty(&ctx->dst_queue)) अणु
			dst_mb = list_entry(ctx->dst_queue.next,
					काष्ठा s5p_mfc_buf, list);
			list_del(&dst_mb->list);
			ctx->dst_queue_cnt--;
			vb2_set_plane_payload(&dst_mb->b->vb2_buf, 0,
				s5p_mfc_hw_call(dev->mfc_ops, get_enc_strm_size,
						dev));
			vb2_buffer_करोne(&dst_mb->b->vb2_buf,
					VB2_BUF_STATE_DONE);
		पूर्ण
	पूर्ण

	अगर (!IS_MFCV6_PLUS(dev)) अणु
		ctx->state = MFCINST_RUNNING;
		अगर (s5p_mfc_ctx_पढ़ोy(ctx))
			set_work_bit_irqsave(ctx);
		s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	पूर्ण अन्यथा अणु
		enc_pb_count = s5p_mfc_hw_call(dev->mfc_ops,
				get_enc_dpb_count, dev);
		अगर (ctx->pb_count < enc_pb_count)
			ctx->pb_count = enc_pb_count;
		अगर (FW_HAS_E_MIN_SCRATCH_BUF(dev)) अणु
			ctx->scratch_buf_size = s5p_mfc_hw_call(dev->mfc_ops,
					get_e_min_scratch_buf_size, dev);
			ctx->bank1.size += ctx->scratch_buf_size;
		पूर्ण
		ctx->state = MFCINST_HEAD_PRODUCED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enc_pre_frame_start(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	काष्ठा s5p_mfc_buf *src_mb;
	अचिन्हित दीर्घ src_y_addr, src_c_addr, dst_addr;
	अचिन्हित पूर्णांक dst_size;

	src_mb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	src_y_addr = vb2_dma_contig_plane_dma_addr(&src_mb->b->vb2_buf, 0);
	src_c_addr = vb2_dma_contig_plane_dma_addr(&src_mb->b->vb2_buf, 1);
	s5p_mfc_hw_call(dev->mfc_ops, set_enc_frame_buffer, ctx,
							src_y_addr, src_c_addr);

	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_hw_call(dev->mfc_ops, set_enc_stream_buffer, ctx, dst_addr,
			dst_size);

	वापस 0;
पूर्ण

अटल पूर्णांक enc_post_frame_start(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *mb_entry;
	अचिन्हित दीर्घ enc_y_addr = 0, enc_c_addr = 0;
	अचिन्हित दीर्घ mb_y_addr, mb_c_addr;
	पूर्णांक slice_type;
	अचिन्हित पूर्णांक strm_size;

	slice_type = s5p_mfc_hw_call(dev->mfc_ops, get_enc_slice_type, dev);
	strm_size = s5p_mfc_hw_call(dev->mfc_ops, get_enc_strm_size, dev);
	mfc_debug(2, "Encoded slice type: %d\n", slice_type);
	mfc_debug(2, "Encoded stream size: %d\n", strm_size);
	mfc_debug(2, "Display order: %d\n",
		  mfc_पढ़ो(dev, S5P_FIMV_ENC_SI_PIC_CNT));
	अगर (slice_type >= 0) अणु
		s5p_mfc_hw_call(dev->mfc_ops, get_enc_frame_buffer, ctx,
				&enc_y_addr, &enc_c_addr);
		list_क्रम_each_entry(mb_entry, &ctx->src_queue, list) अणु
			mb_y_addr = vb2_dma_contig_plane_dma_addr(
					&mb_entry->b->vb2_buf, 0);
			mb_c_addr = vb2_dma_contig_plane_dma_addr(
					&mb_entry->b->vb2_buf, 1);
			अगर ((enc_y_addr == mb_y_addr) &&
						(enc_c_addr == mb_c_addr)) अणु
				list_del(&mb_entry->list);
				ctx->src_queue_cnt--;
				vb2_buffer_करोne(&mb_entry->b->vb2_buf,
							VB2_BUF_STATE_DONE);
				अवरोध;
			पूर्ण
		पूर्ण
		list_क्रम_each_entry(mb_entry, &ctx->ref_queue, list) अणु
			mb_y_addr = vb2_dma_contig_plane_dma_addr(
					&mb_entry->b->vb2_buf, 0);
			mb_c_addr = vb2_dma_contig_plane_dma_addr(
					&mb_entry->b->vb2_buf, 1);
			अगर ((enc_y_addr == mb_y_addr) &&
						(enc_c_addr == mb_c_addr)) अणु
				list_del(&mb_entry->list);
				ctx->ref_queue_cnt--;
				vb2_buffer_करोne(&mb_entry->b->vb2_buf,
							VB2_BUF_STATE_DONE);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((ctx->src_queue_cnt > 0) && (ctx->state == MFCINST_RUNNING)) अणु
		mb_entry = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf,
									list);
		अगर (mb_entry->flags & MFC_BUF_FLAG_USED) अणु
			list_del(&mb_entry->list);
			ctx->src_queue_cnt--;
			list_add_tail(&mb_entry->list, &ctx->ref_queue);
			ctx->ref_queue_cnt++;
		पूर्ण
	पूर्ण
	mfc_debug(2, "enc src count: %d, enc ref count: %d\n",
		  ctx->src_queue_cnt, ctx->ref_queue_cnt);
	अगर ((ctx->dst_queue_cnt > 0) && (strm_size > 0)) अणु
		mb_entry = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf,
									list);
		list_del(&mb_entry->list);
		ctx->dst_queue_cnt--;
		चयन (slice_type) अणु
		हाल S5P_FIMV_ENC_SI_SLICE_TYPE_I:
			mb_entry->b->flags |= V4L2_BUF_FLAG_KEYFRAME;
			अवरोध;
		हाल S5P_FIMV_ENC_SI_SLICE_TYPE_P:
			mb_entry->b->flags |= V4L2_BUF_FLAG_PFRAME;
			अवरोध;
		हाल S5P_FIMV_ENC_SI_SLICE_TYPE_B:
			mb_entry->b->flags |= V4L2_BUF_FLAG_BFRAME;
			अवरोध;
		पूर्ण
		vb2_set_plane_payload(&mb_entry->b->vb2_buf, 0, strm_size);
		vb2_buffer_करोne(&mb_entry->b->vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण
	अगर ((ctx->src_queue_cnt == 0) || (ctx->dst_queue_cnt == 0))
		clear_work_bit(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s5p_mfc_codec_ops encoder_codec_ops = अणु
	.pre_seq_start		= enc_pre_seq_start,
	.post_seq_start		= enc_post_seq_start,
	.pre_frame_start	= enc_pre_frame_start,
	.post_frame_start	= enc_post_frame_start,
पूर्ण;

/* Query capabilities of the device */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);

	strscpy(cap->driver, S5P_MFC_NAME, माप(cap->driver));
	strscpy(cap->card, dev->vfd_enc->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(&dev->plat_dev->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, काष्ठा v4l2_fmtdesc *f,
							bool out)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (out && क्रमmats[i].type != MFC_FMT_RAW)
			जारी;
		अन्यथा अगर (!out && क्रमmats[i].type != MFC_FMT_ENC)
			जारी;
		अन्यथा अगर ((dev->variant->version_bit & क्रमmats[i].versions) == 0)
			जारी;

		अगर (j == f->index) अणु
			f->pixelक्रमmat = क्रमmats[i].fourcc;
			वापस 0;
		पूर्ण
		++j;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *pirv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, f, false);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस vidioc_क्रमागत_fmt(file, f, true);
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	mfc_debug(2, "f->type = %d ctx->state = %d\n", f->type, ctx->state);
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		/* This is run on output (encoder dest) */
		pix_fmt_mp->width = 0;
		pix_fmt_mp->height = 0;
		pix_fmt_mp->field = V4L2_FIELD_NONE;
		pix_fmt_mp->pixelक्रमmat = ctx->dst_fmt->fourcc;
		pix_fmt_mp->num_planes = ctx->dst_fmt->num_planes;

		pix_fmt_mp->plane_fmt[0].bytesperline = ctx->enc_dst_buf_size;
		pix_fmt_mp->plane_fmt[0].sizeimage = ctx->enc_dst_buf_size;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/* This is run on capture (encoder src) */
		pix_fmt_mp->width = ctx->img_width;
		pix_fmt_mp->height = ctx->img_height;

		pix_fmt_mp->field = V4L2_FIELD_NONE;
		pix_fmt_mp->pixelक्रमmat = ctx->src_fmt->fourcc;
		pix_fmt_mp->num_planes = ctx->src_fmt->num_planes;

		pix_fmt_mp->plane_fmt[0].bytesperline = ctx->buf_width;
		pix_fmt_mp->plane_fmt[0].sizeimage = ctx->luma_size;
		pix_fmt_mp->plane_fmt[1].bytesperline = ctx->buf_width;
		pix_fmt_mp->plane_fmt[1].sizeimage = ctx->chroma_size;
	पूर्ण अन्यथा अणु
		mfc_err("invalid buf type\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_fmt *fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		fmt = find_क्रमmat(f, MFC_FMT_ENC);
		अगर (!fmt) अणु
			mfc_err("failed to try output format\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((dev->variant->version_bit & fmt->versions) == 0) अणु
			mfc_err("Unsupported format by this MFC version.\n");
			वापस -EINVAL;
		पूर्ण

		pix_fmt_mp->plane_fmt[0].bytesperline =
			pix_fmt_mp->plane_fmt[0].sizeimage;
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		fmt = find_क्रमmat(f, MFC_FMT_RAW);
		अगर (!fmt) अणु
			mfc_err("failed to try output format\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((dev->variant->version_bit & fmt->versions) == 0) अणु
			mfc_err("Unsupported format by this MFC version.\n");
			वापस -EINVAL;
		पूर्ण

		v4l_bound_align_image(&pix_fmt_mp->width, 8, 1920, 1,
			&pix_fmt_mp->height, 4, 1080, 1, 0);
	पूर्ण अन्यथा अणु
		mfc_err("invalid buf type\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_fmt_mp = &f->fmt.pix_mp;
	पूर्णांक ret = 0;

	ret = vidioc_try_fmt(file, priv, f);
	अगर (ret)
		वापस ret;
	अगर (ctx->vq_src.streaming || ctx->vq_dst.streaming) अणु
		v4l2_err(&dev->v4l2_dev, "%s queue busy\n", __func__);
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		/* dst_fmt is validated by call to vidioc_try_fmt */
		ctx->dst_fmt = find_क्रमmat(f, MFC_FMT_ENC);
		ctx->state = MFCINST_INIT;
		ctx->codec_mode = ctx->dst_fmt->codec_mode;
		ctx->enc_dst_buf_size =	pix_fmt_mp->plane_fmt[0].sizeimage;
		pix_fmt_mp->plane_fmt[0].bytesperline = 0;
		ctx->dst_bufs_cnt = 0;
		ctx->capture_state = QUEUE_FREE;
		ret = s5p_mfc_खोलो_mfc_inst(dev, ctx);
	पूर्ण अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		/* src_fmt is validated by call to vidioc_try_fmt */
		ctx->src_fmt = find_क्रमmat(f, MFC_FMT_RAW);
		ctx->img_width = pix_fmt_mp->width;
		ctx->img_height = pix_fmt_mp->height;
		mfc_debug(2, "codec number: %d\n", ctx->src_fmt->codec_mode);
		mfc_debug(2, "fmt - w: %d, h: %d, ctx - w: %d, h: %d\n",
			pix_fmt_mp->width, pix_fmt_mp->height,
			ctx->img_width, ctx->img_height);

		s5p_mfc_hw_call(dev->mfc_ops, enc_calc_src_size, ctx);
		pix_fmt_mp->plane_fmt[0].sizeimage = ctx->luma_size;
		pix_fmt_mp->plane_fmt[0].bytesperline = ctx->buf_width;
		pix_fmt_mp->plane_fmt[1].sizeimage = ctx->chroma_size;
		pix_fmt_mp->plane_fmt[1].bytesperline = ctx->buf_width;

		ctx->src_bufs_cnt = 0;
		ctx->output_state = QUEUE_FREE;
	पूर्ण अन्यथा अणु
		mfc_err("invalid buf type\n");
		ret = -EINVAL;
	पूर्ण
out:
	mfc_debug_leave();
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
					  काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा s5p_mfc_dev *dev = video_drvdata(file);
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret = 0;

	/* अगर memory is not mmp or userptr वापस error */
	अगर ((reqbufs->memory != V4L2_MEMORY_MMAP) &&
		(reqbufs->memory != V4L2_MEMORY_USERPTR))
		वापस -EINVAL;
	अगर (reqbufs->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		अगर (reqbufs->count == 0) अणु
			mfc_debug(2, "Freeing buffers\n");
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			s5p_mfc_hw_call(dev->mfc_ops, release_codec_buffers,
					ctx);
			ctx->capture_state = QUEUE_FREE;
			वापस ret;
		पूर्ण
		अगर (ctx->capture_state != QUEUE_FREE) अणु
			mfc_err("invalid capture state: %d\n",
							ctx->capture_state);
			वापस -EINVAL;
		पूर्ण
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		अगर (ret != 0) अणु
			mfc_err("error in vb2_reqbufs() for E(D)\n");
			वापस ret;
		पूर्ण
		ctx->capture_state = QUEUE_BUFS_REQUESTED;

		ret = s5p_mfc_hw_call(ctx->dev->mfc_ops,
				alloc_codec_buffers, ctx);
		अगर (ret) अणु
			mfc_err("Failed to allocate encoding buffers\n");
			reqbufs->count = 0;
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (reqbufs->count == 0) अणु
			mfc_debug(2, "Freeing buffers\n");
			ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
			s5p_mfc_hw_call(dev->mfc_ops, release_codec_buffers,
					ctx);
			ctx->output_state = QUEUE_FREE;
			वापस ret;
		पूर्ण
		अगर (ctx->output_state != QUEUE_FREE) अणु
			mfc_err("invalid output state: %d\n",
							ctx->output_state);
			वापस -EINVAL;
		पूर्ण

		अगर (IS_MFCV6_PLUS(dev)) अणु
			/* Check क्रम min encoder buffers */
			अगर (ctx->pb_count &&
				(reqbufs->count < ctx->pb_count)) अणु
				reqbufs->count = ctx->pb_count;
				mfc_debug(2, "Minimum %d output buffers needed\n",
						ctx->pb_count);
			पूर्ण अन्यथा अणु
				ctx->pb_count = reqbufs->count;
			पूर्ण
		पूर्ण

		ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
		अगर (ret != 0) अणु
			mfc_err("error in vb2_reqbufs() for E(S)\n");
			वापस ret;
		पूर्ण
		ctx->output_state = QUEUE_BUFS_REQUESTED;
	पूर्ण अन्यथा अणु
		mfc_err("invalid buf type\n");
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *priv,
						   काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret = 0;

	/* अगर memory is not mmp or userptr वापस error */
	अगर ((buf->memory != V4L2_MEMORY_MMAP) &&
		(buf->memory != V4L2_MEMORY_USERPTR))
		वापस -EINVAL;
	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		अगर (ctx->state != MFCINST_GOT_INST) अणु
			mfc_err("invalid context state: %d\n", ctx->state);
			वापस -EINVAL;
		पूर्ण
		ret = vb2_querybuf(&ctx->vq_dst, buf);
		अगर (ret != 0) अणु
			mfc_err("error in vb2_querybuf() for E(D)\n");
			वापस ret;
		पूर्ण
		buf->m.planes[0].m.mem_offset += DST_QUEUE_OFF_BASE;
	पूर्ण अन्यथा अगर (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ret = vb2_querybuf(&ctx->vq_src, buf);
		अगर (ret != 0) अणु
			mfc_err("error in vb2_querybuf() for E(S)\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_err("invalid buf type\n");
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

/* Queue a buffer */
अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->state == MFCINST_ERROR) अणु
		mfc_err("Call on QBUF after unrecoverable error\n");
		वापस -EIO;
	पूर्ण
	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (ctx->state == MFCINST_FINISHING) अणु
			mfc_err("Call on QBUF after EOS command\n");
			वापस -EIO;
		पूर्ण
		वापस vb2_qbuf(&ctx->vq_src, शून्य, buf);
	पूर्ण अन्यथा अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		वापस vb2_qbuf(&ctx->vq_dst, शून्य, buf);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Dequeue a buffer */
अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_EOS
	पूर्ण;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	पूर्णांक ret;

	अगर (ctx->state == MFCINST_ERROR) अणु
		mfc_err_limited("Call on DQBUF after unrecoverable error\n");
		वापस -EIO;
	पूर्ण
	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ret = vb2_dqbuf(&ctx->vq_src, buf, file->f_flags & O_NONBLOCK);
	पूर्ण अन्यथा अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = vb2_dqbuf(&ctx->vq_dst, buf, file->f_flags & O_NONBLOCK);
		अगर (ret == 0 && ctx->state == MFCINST_FINISHED
					&& list_empty(&ctx->vq_dst.करोne_list))
			v4l2_event_queue_fh(&ctx->fh, &ev);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/* Export DMA buffer */
अटल पूर्णांक vidioc_expbuf(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_exportbuffer *eb)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (eb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_expbuf(&ctx->vq_src, eb);
	अगर (eb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_expbuf(&ctx->vq_dst, eb);
	वापस -EINVAL;
पूर्ण

/* Stream on */
अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *priv,
			   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_streamon(&ctx->vq_src, type);
	अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_streamon(&ctx->vq_dst, type);
	वापस -EINVAL;
पूर्ण

/* Stream off, which equals to a छोड़ो */
अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *priv,
			    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस vb2_streamoff(&ctx->vq_src, type);
	अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस vb2_streamoff(&ctx->vq_dst, type);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक h264_level(क्रमागत v4l2_mpeg_video_h264_level lvl)
अणु
	अटल अचिन्हित पूर्णांक t[V4L2_MPEG_VIDEO_H264_LEVEL_4_0 + 1] = अणु
		/* V4L2_MPEG_VIDEO_H264_LEVEL_1_0   */ 10,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_1B    */ 9,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_1_1   */ 11,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_1_2   */ 12,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_1_3   */ 13,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_2_0   */ 20,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_2_1   */ 21,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_2_2   */ 22,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_3_0   */ 30,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_3_1   */ 31,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_3_2   */ 32,
		/* V4L2_MPEG_VIDEO_H264_LEVEL_4_0   */ 40,
	पूर्ण;
	वापस t[lvl];
पूर्ण

अटल अंतरभूत पूर्णांक mpeg4_level(क्रमागत v4l2_mpeg_video_mpeg4_level lvl)
अणु
	अटल अचिन्हित पूर्णांक t[V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 + 1] = अणु
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_0    */ 0,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_0B   */ 9,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_1    */ 1,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_2    */ 2,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_3    */ 3,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_3B   */ 7,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_4    */ 4,
		/* V4L2_MPEG_VIDEO_MPEG4_LEVEL_5    */ 5,
	पूर्ण;
	वापस t[lvl];
पूर्ण

अटल अंतरभूत पूर्णांक hevc_level(क्रमागत v4l2_mpeg_video_hevc_level lvl)
अणु
	अटल अचिन्हित पूर्णांक t[] = अणु
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_1    */ 10,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_2    */ 20,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1  */ 21,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_3    */ 30,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1  */ 31,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_4    */ 40,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1  */ 41,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5    */ 50,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1  */ 51,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_5_2  */ 52,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6    */ 60,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6_1  */ 61,
		/* V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2  */ 62,
	पूर्ण;
	वापस t[lvl];
पूर्ण

अटल अंतरभूत पूर्णांक vui_sar_idc(क्रमागत v4l2_mpeg_video_h264_vui_sar_idc sar)
अणु
	अटल अचिन्हित पूर्णांक t[V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_EXTENDED + 1] = अणु
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_UNSPECIFIED     */ 0,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1             */ 1,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_12x11           */ 2,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_10x11           */ 3,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_16x11           */ 4,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_40x33           */ 5,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_24x11           */ 6,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_20x11           */ 7,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_32x11           */ 8,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_80x33           */ 9,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_18x11           */ 10,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_15x11           */ 11,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_64x33           */ 12,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_160x99          */ 13,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_4x3             */ 14,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_3x2             */ 15,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_2x1             */ 16,
		/* V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_EXTENDED        */ 255,
	पूर्ण;
	वापस t[sar];
पूर्ण

/*
 * Update range of all HEVC quantization parameter controls that depend on the
 * V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP, V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP controls.
 */
अटल व्योम __enc_update_hevc_qp_ctrls_range(काष्ठा s5p_mfc_ctx *ctx,
					     पूर्णांक min, पूर्णांक max)
अणु
	अटल स्थिर पूर्णांक __hevc_qp_ctrls[] = अणु
		V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP,
		V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP,
	पूर्ण;
	काष्ठा v4l2_ctrl *ctrl = शून्य;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(__hevc_qp_ctrls); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(ctx->ctrls); j++) अणु
			अगर (ctx->ctrls[j]->id == __hevc_qp_ctrls[i]) अणु
				ctrl = ctx->ctrls[j];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (WARN_ON(!ctrl))
			अवरोध;

		__v4l2_ctrl_modअगरy_range(ctrl, min, max, ctrl->step, min);
	पूर्ण
पूर्ण

अटल पूर्णांक s5p_mfc_enc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		p->gop_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		p->slice_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
		p->slice_mb = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
		p->slice_bit = ctrl->val * 8;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
		p->पूर्णांकra_refresh_mb = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_PADDING:
		p->pad = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV:
		p->pad_luma = (ctrl->val >> 16) & 0xff;
		p->pad_cb = (ctrl->val >> 8) & 0xff;
		p->pad_cr = (ctrl->val >> 0) & 0xff;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		p->rc_frame = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		p->rc_bitrate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF:
		p->rc_reaction_coeff = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE:
		ctx->क्रमce_frame_type = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		ctx->क्रमce_frame_type =
			V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_I_FRAME;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VBV_SIZE:
		p->vbv_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:
		p->mv_h_range = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:
		p->mv_v_range = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:
		p->codec.h264.cpb_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		p->seq_hdr_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE:
	हाल V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE:
		p->frame_skip_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT:
		p->fixed_target_bit = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		p->num_b_frame = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		चयन (ctrl->val) अणु
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_MAIN:
			p->codec.h264.profile =
					S5P_FIMV_ENC_PROखाता_H264_MAIN;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_HIGH:
			p->codec.h264.profile =
					S5P_FIMV_ENC_PROखाता_H264_HIGH;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE:
			p->codec.h264.profile =
				S5P_FIMV_ENC_PROखाता_H264_BASELINE;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE:
			अगर (IS_MFCV6_PLUS(dev))
				p->codec.h264.profile =
				S5P_FIMV_ENC_PROखाता_H264_CONSTRAINED_BASELINE;
			अन्यथा
				ret = -EINVAL;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		p->codec.h264.level_v4l2 = ctrl->val;
		p->codec.h264.level = h264_level(ctrl->val);
		अगर (p->codec.h264.level < 0) अणु
			mfc_err("Level number is wrong\n");
			ret = p->codec.h264.level;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		p->codec.mpeg4.level_v4l2 = ctrl->val;
		p->codec.mpeg4.level = mpeg4_level(ctrl->val);
		अगर (p->codec.mpeg4.level < 0) अणु
			mfc_err("Level number is wrong\n");
			ret = p->codec.mpeg4.level;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		p->codec.h264.loop_filter_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
		p->codec.h264.loop_filter_alpha = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
		p->codec.h264.loop_filter_beta = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		p->codec.h264.entropy_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P:
		p->codec.h264.num_ref_pic_4p = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:
		p->codec.h264._8x8_transक्रमm = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
		p->rc_mb = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
		p->codec.h264.rc_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		p->codec.h264.rc_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		p->codec.h264.rc_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
		p->codec.h264.rc_p_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
		p->codec.h264.rc_b_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:
	हाल V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP:
		p->codec.mpeg4.rc_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP:
	हाल V4L2_CID_MPEG_VIDEO_H263_MIN_QP:
		p->codec.mpeg4.rc_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP:
	हाल V4L2_CID_MPEG_VIDEO_H263_MAX_QP:
		p->codec.mpeg4.rc_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:
	हाल V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP:
		p->codec.mpeg4.rc_p_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP:
	हाल V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP:
		p->codec.mpeg4.rc_b_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK:
		p->codec.h264.rc_mb_dark = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH:
		p->codec.h264.rc_mb_smooth = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC:
		p->codec.h264.rc_mb_अटल = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY:
		p->codec.h264.rc_mb_activity = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:
		p->codec.h264.vui_sar = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
		p->codec.h264.vui_sar_idc = vui_sar_idc(ctrl->val);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH:
		p->codec.h264.vui_ext_sar_width = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT:
		p->codec.h264.vui_ext_sar_height = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		p->codec.h264.खोलो_gop = !ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		p->codec.h264.खोलो_gop_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
		चयन (ctrl->val) अणु
		हाल V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE:
			p->codec.mpeg4.profile =
				S5P_FIMV_ENC_PROखाता_MPEG4_SIMPLE;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE:
			p->codec.mpeg4.profile =
			S5P_FIMV_ENC_PROखाता_MPEG4_ADVANCED_SIMPLE;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:
		p->codec.mpeg4.quarter_pixel = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
		p->codec.vp8.num_partitions = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4:
		p->codec.vp8.imd_4x4 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
		p->codec.vp8.num_ref = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL:
		p->codec.vp8.filter_level = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS:
		p->codec.vp8.filter_sharpness = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD:
		p->codec.vp8.golden_frame_ref_period = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
		p->codec.vp8.golden_frame_sel = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:
		p->codec.vp8.rc_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:
		p->codec.vp8.rc_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP:
		p->codec.vp8.rc_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP:
		p->codec.vp8.rc_p_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
		p->codec.vp8.profile = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP:
		p->codec.hevc.rc_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP:
		p->codec.hevc.rc_p_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP:
		p->codec.hevc.rc_b_frame_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION:
		p->codec.hevc.rc_framerate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP:
		p->codec.hevc.rc_min_qp = ctrl->val;
		__enc_update_hevc_qp_ctrls_range(ctx, ctrl->val,
						 p->codec.hevc.rc_max_qp);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP:
		p->codec.hevc.rc_max_qp = ctrl->val;
		__enc_update_hevc_qp_ctrls_range(ctx, p->codec.hevc.rc_min_qp,
						 ctrl->val);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		p->codec.hevc.level_v4l2 = ctrl->val;
		p->codec.hevc.level = hevc_level(ctrl->val);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PROखाता:
		चयन (ctrl->val) अणु
		हाल V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN:
			p->codec.hevc.profile =
				V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE:
			p->codec.hevc.profile =
			V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TIER:
		p->codec.hevc.tier = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH:
		p->codec.hevc.max_partition_depth = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES:
		p->codec.hevc.num_refs_क्रम_p = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:
		p->codec.hevc.refreshtype = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED:
		p->codec.hevc.स्थिर_पूर्णांकra_period_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU:
		p->codec.hevc.lossless_cu_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT:
		p->codec.hevc.wavefront_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:
		p->codec.hevc.loopfilter = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP:
		p->codec.hevc.hier_qp_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:
		p->codec.hevc.hier_qp_type = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER:
		p->codec.hevc.num_hier_layer = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP:
		p->codec.hevc.hier_qp_layer[0] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP:
		p->codec.hevc.hier_qp_layer[1] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP:
		p->codec.hevc.hier_qp_layer[2] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP:
		p->codec.hevc.hier_qp_layer[3] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP:
		p->codec.hevc.hier_qp_layer[4] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP:
		p->codec.hevc.hier_qp_layer[5] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP:
		p->codec.hevc.hier_qp_layer[6] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR:
		p->codec.hevc.hier_bit_layer[0] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR:
		p->codec.hevc.hier_bit_layer[1] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR:
		p->codec.hevc.hier_bit_layer[2] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR:
		p->codec.hevc.hier_bit_layer[3] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR:
		p->codec.hevc.hier_bit_layer[4] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR:
		p->codec.hevc.hier_bit_layer[5] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR:
		p->codec.hevc.hier_bit_layer[6] = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB:
		p->codec.hevc.general_pb_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID:
		p->codec.hevc.temporal_id_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING:
		p->codec.hevc.strong_पूर्णांकra_smooth = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT:
		p->codec.hevc.पूर्णांकra_pu_split_disable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION:
		p->codec.hevc.पंचांगv_prediction_disable = !ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1:
		p->codec.hevc.max_num_merge_mv = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE:
		p->codec.hevc.encoding_nostartcode_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD:
		p->codec.hevc.refreshperiod = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2:
		p->codec.hevc.lf_beta_offset_भाग2 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2:
		p->codec.hevc.lf_tc_offset_भाग2 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:
		p->codec.hevc.size_of_length_field = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR:
		p->codec.hevc.prepend_sps_pps_to_idr = ctrl->val;
		अवरोध;
	शेष:
		v4l2_err(&dev->v4l2_dev, "Invalid control, id=%d, val=%d\n",
							ctrl->id, ctrl->val);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_mfc_enc_g_v_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:
		अगर (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) अणु
			ctrl->val = ctx->pb_count;
			अवरोध;
		पूर्ण अन्यथा अगर (ctx->state != MFCINST_INIT) अणु
			v4l2_err(&dev->v4l2_dev, "Encoding not initialised\n");
			वापस -EINVAL;
		पूर्ण
		/* Should रुको क्रम the header to be produced */
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
				S5P_MFC_R2H_CMD_SEQ_DONE_RET, 0);
		अगर (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) अणु
			ctrl->val = ctx->pb_count;
		पूर्ण अन्यथा अणु
			v4l2_err(&dev->v4l2_dev, "Encoding not initialised\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5p_mfc_enc_ctrl_ops = अणु
	.s_ctrl = s5p_mfc_enc_s_ctrl,
	.g_अस्थिर_ctrl = s5p_mfc_enc_g_v_ctrl,
पूर्ण;

अटल पूर्णांक vidioc_s_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (a->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ctx->enc_params.rc_framerate_num =
					a->parm.output.समयperframe.denominator;
		ctx->enc_params.rc_framerate_denom =
					a->parm.output.समयperframe.numerator;
	पूर्ण अन्यथा अणु
		mfc_err("Setting FPS is only possible for the output queue\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	अगर (a->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		a->parm.output.समयperframe.denominator =
					ctx->enc_params.rc_framerate_num;
		a->parm.output.समयperframe.numerator =
					ctx->enc_params.rc_framerate_denom;
	पूर्ण अन्यथा अणु
		mfc_err("Setting FPS is only possible for the output queue\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_encoder_cmd(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_encoder_cmd *cmd)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *buf;
	अचिन्हित दीर्घ flags;

	चयन (cmd->cmd) अणु
	हाल V4L2_ENC_CMD_STOP:
		अगर (cmd->flags != 0)
			वापस -EINVAL;

		अगर (!ctx->vq_src.streaming)
			वापस -EINVAL;

		spin_lock_irqsave(&dev->irqlock, flags);
		अगर (list_empty(&ctx->src_queue)) अणु
			mfc_debug(2, "EOS: empty src queue, entering finishing state\n");
			ctx->state = MFCINST_FINISHING;
			अगर (s5p_mfc_ctx_पढ़ोy(ctx))
				set_work_bit_irqsave(ctx);
			spin_unlock_irqrestore(&dev->irqlock, flags);
			s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
		पूर्ण अन्यथा अणु
			mfc_debug(2, "EOS: marking last buffer of stream\n");
			buf = list_entry(ctx->src_queue.prev,
						काष्ठा s5p_mfc_buf, list);
			अगर (buf->flags & MFC_BUF_FLAG_USED)
				ctx->state = MFCINST_FINISHING;
			अन्यथा
				buf->flags |= MFC_BUF_FLAG_EOS;
			spin_unlock_irqrestore(&dev->irqlock, flags);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_subscribe_event(काष्ठा v4l2_fh *fh,
				  स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops s5p_mfc_enc_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mplane = vidioc_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = vidioc_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane = vidioc_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = vidioc_s_fmt,
	.vidioc_reqbufs = vidioc_reqbufs,
	.vidioc_querybuf = vidioc_querybuf,
	.vidioc_qbuf = vidioc_qbuf,
	.vidioc_dqbuf = vidioc_dqbuf,
	.vidioc_expbuf = vidioc_expbuf,
	.vidioc_streamon = vidioc_streamon,
	.vidioc_streamoff = vidioc_streamoff,
	.vidioc_s_parm = vidioc_s_parm,
	.vidioc_g_parm = vidioc_g_parm,
	.vidioc_encoder_cmd = vidioc_encoder_cmd,
	.vidioc_subscribe_event = vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक check_vb_with_fmt(काष्ठा s5p_mfc_fmt *fmt, काष्ठा vb2_buffer *vb)
अणु
	पूर्णांक i;

	अगर (!fmt)
		वापस -EINVAL;
	अगर (fmt->num_planes != vb->num_planes) अणु
		mfc_err("invalid plane number for the format\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < fmt->num_planes; i++) अणु
		dma_addr_t dma = vb2_dma_contig_plane_dma_addr(vb, i);
		अगर (!dma) अणु
			mfc_err("failed to get plane cookie\n");
			वापस -EINVAL;
		पूर्ण
		mfc_debug(2, "index: %d, plane[%d] cookie: %pad\n",
			  vb->index, i, &dma);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *buf_count, अचिन्हित पूर्णांक *plane_count,
			अचिन्हित पूर्णांक psize[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		अगर (ctx->state != MFCINST_GOT_INST) अणु
			mfc_err("invalid state: %d\n", ctx->state);
			वापस -EINVAL;
		पूर्ण

		अगर (ctx->dst_fmt)
			*plane_count = ctx->dst_fmt->num_planes;
		अन्यथा
			*plane_count = MFC_ENC_CAP_PLANE_COUNT;
		अगर (*buf_count < 1)
			*buf_count = 1;
		अगर (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
		psize[0] = ctx->enc_dst_buf_size;
		alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		अगर (ctx->src_fmt)
			*plane_count = ctx->src_fmt->num_planes;
		अन्यथा
			*plane_count = MFC_ENC_OUT_PLANE_COUNT;

		अगर (*buf_count < 1)
			*buf_count = 1;
		अगर (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;

		psize[0] = ctx->luma_size;
		psize[1] = ctx->chroma_size;

		अगर (IS_MFCV6_PLUS(dev)) अणु
			alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
			alloc_devs[1] = ctx->dev->mem_dev[BANK_L_CTX];
		पूर्ण अन्यथा अणु
			alloc_devs[0] = ctx->dev->mem_dev[BANK_R_CTX];
			alloc_devs[1] = ctx->dev->mem_dev[BANK_R_CTX];
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_err("invalid queue type: %d\n", vq->type);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = check_vb_with_fmt(ctx->dst_fmt, vb);
		अगर (ret < 0)
			वापस ret;
		i = vb->index;
		ctx->dst_bufs[i].b = vbuf;
		ctx->dst_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs_cnt++;
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ret = check_vb_with_fmt(ctx->src_fmt, vb);
		अगर (ret < 0)
			वापस ret;
		i = vb->index;
		ctx->src_bufs[i].b = vbuf;
		ctx->src_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->src_bufs_cnt++;
	पूर्ण अन्यथा अणु
		mfc_err("invalid queue type: %d\n", vq->type);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	पूर्णांक ret;

	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		ret = check_vb_with_fmt(ctx->dst_fmt, vb);
		अगर (ret < 0)
			वापस ret;
		mfc_debug(2, "plane size: %ld, dst size: %zu\n",
			vb2_plane_size(vb, 0), ctx->enc_dst_buf_size);
		अगर (vb2_plane_size(vb, 0) < ctx->enc_dst_buf_size) अणु
			mfc_err("plane size is too small for capture\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		ret = check_vb_with_fmt(ctx->src_fmt, vb);
		अगर (ret < 0)
			वापस ret;
		mfc_debug(2, "plane size: %ld, luma size: %d\n",
			vb2_plane_size(vb, 0), ctx->luma_size);
		mfc_debug(2, "plane size: %ld, chroma size: %d\n",
			vb2_plane_size(vb, 1), ctx->chroma_size);
		अगर (vb2_plane_size(vb, 0) < ctx->luma_size ||
		    vb2_plane_size(vb, 1) < ctx->chroma_size) अणु
			mfc_err("plane size is too small for output\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_err("invalid queue type: %d\n", vq->type);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	अगर (IS_MFCV6_PLUS(dev) &&
			(q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)) अणु

		अगर ((ctx->state == MFCINST_GOT_INST) &&
			(dev->curr_ctx == ctx->num) && dev->hw_lock) अणु
			s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
						S5P_MFC_R2H_CMD_SEQ_DONE_RET,
						0);
		पूर्ण

		अगर (ctx->src_bufs_cnt < ctx->pb_count) अणु
			mfc_err("Need minimum %d OUTPUT buffers\n",
					ctx->pb_count);
			वापस -ENOBUFS;
		पूर्ण
	पूर्ण

	/* If context is पढ़ोy then dev = work->data;schedule it to run */
	अगर (s5p_mfc_ctx_पढ़ोy(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);

	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_stop_streaming(काष्ठा vb2_queue *q)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	अगर ((ctx->state == MFCINST_FINISHING ||
		ctx->state == MFCINST_RUNNING) &&
		dev->curr_ctx == ctx->num && dev->hw_lock) अणु
		ctx->state = MFCINST_ABORT;
		s5p_mfc_रुको_क्रम_करोne_ctx(ctx, S5P_MFC_R2H_CMD_FRAME_DONE_RET,
					  0);
	पूर्ण
	ctx->state = MFCINST_FINISHED;
	spin_lock_irqsave(&dev->irqlock, flags);
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		s5p_mfc_cleanup_queue(&ctx->dst_queue, &ctx->vq_dst);
		INIT_LIST_HEAD(&ctx->dst_queue);
		ctx->dst_queue_cnt = 0;
	पूर्ण
	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		cleanup_ref_queue(ctx);
		s5p_mfc_cleanup_queue(&ctx->src_queue, &ctx->vq_src);
		INIT_LIST_HEAD(&ctx->src_queue);
		ctx->src_queue_cnt = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->irqlock, flags);
पूर्ण

अटल व्योम s5p_mfc_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित दीर्घ flags;
	काष्ठा s5p_mfc_buf *mfc_buf;

	अगर (ctx->state == MFCINST_ERROR) अणु
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		cleanup_ref_queue(ctx);
		वापस;
	पूर्ण
	अगर (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		mfc_buf = &ctx->dst_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		/* Mark destination as available क्रम use by MFC */
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&mfc_buf->list, &ctx->dst_queue);
		ctx->dst_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	पूर्ण अन्यथा अगर (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		mfc_buf = &ctx->src_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&mfc_buf->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	पूर्ण अन्यथा अणु
		mfc_err("unsupported buffer type (%d)\n", vq->type);
	पूर्ण
	अगर (s5p_mfc_ctx_पढ़ोy(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
पूर्ण

अटल काष्ठा vb2_ops s5p_mfc_enc_qops = अणु
	.queue_setup		= s5p_mfc_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_init		= s5p_mfc_buf_init,
	.buf_prepare		= s5p_mfc_buf_prepare,
	.start_streaming	= s5p_mfc_start_streaming,
	.stop_streaming		= s5p_mfc_stop_streaming,
	.buf_queue		= s5p_mfc_buf_queue,
पूर्ण;

स्थिर काष्ठा s5p_mfc_codec_ops *get_enc_codec_ops(व्योम)
अणु
	वापस &encoder_codec_ops;
पूर्ण

काष्ठा vb2_ops *get_enc_queue_ops(व्योम)
अणु
	वापस &s5p_mfc_enc_qops;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops *get_enc_v4l2_ioctl_ops(व्योम)
अणु
	वापस &s5p_mfc_enc_ioctl_ops;
पूर्ण

#घोषणा IS_MFC51_PRIV(x) ((V4L2_CTRL_ID2WHICH(x) == V4L2_CTRL_CLASS_CODEC) \
						&& V4L2_CTRL_DRIVER_PRIV(x))

पूर्णांक s5p_mfc_enc_ctrls_setup(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा v4l2_ctrl_config cfg;
	पूर्णांक i;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, NUM_CTRLS);
	अगर (ctx->ctrl_handler.error) अणु
		mfc_err("v4l2_ctrl_handler_init failed\n");
		वापस ctx->ctrl_handler.error;
	पूर्ण
	क्रम (i = 0; i < NUM_CTRLS; i++) अणु
		अगर (IS_MFC51_PRIV(controls[i].id)) अणु
			स_रखो(&cfg, 0, माप(काष्ठा v4l2_ctrl_config));
			cfg.ops = &s5p_mfc_enc_ctrl_ops;
			cfg.id = controls[i].id;
			cfg.min = controls[i].minimum;
			cfg.max = controls[i].maximum;
			cfg.def = controls[i].शेष_value;
			cfg.name = controls[i].name;
			cfg.type = controls[i].type;
			cfg.flags = 0;

			अगर (cfg.type == V4L2_CTRL_TYPE_MENU) अणु
				cfg.step = 0;
				cfg.menu_skip_mask = controls[i].menu_skip_mask;
				cfg.qmenu = mfc51_get_menu(cfg.id);
			पूर्ण अन्यथा अणु
				cfg.step = controls[i].step;
				cfg.menu_skip_mask = 0;
			पूर्ण
			ctx->ctrls[i] = v4l2_ctrl_new_custom(&ctx->ctrl_handler,
					&cfg, शून्य);
		पूर्ण अन्यथा अणु
			अगर ((controls[i].type == V4L2_CTRL_TYPE_MENU) ||
				(controls[i].type ==
					V4L2_CTRL_TYPE_INTEGER_MENU)) अणु
				ctx->ctrls[i] = v4l2_ctrl_new_std_menu(
					&ctx->ctrl_handler,
					&s5p_mfc_enc_ctrl_ops, controls[i].id,
					controls[i].maximum, 0,
					controls[i].शेष_value);
			पूर्ण अन्यथा अणु
				ctx->ctrls[i] = v4l2_ctrl_new_std(
					&ctx->ctrl_handler,
					&s5p_mfc_enc_ctrl_ops, controls[i].id,
					controls[i].minimum,
					controls[i].maximum, controls[i].step,
					controls[i].शेष_value);
			पूर्ण
		पूर्ण
		अगर (ctx->ctrl_handler.error) अणु
			mfc_err("Adding control (%d) failed\n", i);
			वापस ctx->ctrl_handler.error;
		पूर्ण
		अगर (controls[i].is_अस्थिर && ctx->ctrls[i])
			ctx->ctrls[i]->flags |= V4L2_CTRL_FLAG_VOLATILE;
	पूर्ण
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	वापस 0;
पूर्ण

व्योम s5p_mfc_enc_ctrls_delete(काष्ठा s5p_mfc_ctx *ctx)
अणु
	पूर्णांक i;

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	क्रम (i = 0; i < NUM_CTRLS; i++)
		ctx->ctrls[i] = शून्य;
पूर्ण

व्योम s5p_mfc_enc_init(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा v4l2_क्रमmat f;
	f.fmt.pix_mp.pixelक्रमmat = DEF_SRC_FMT_ENC;
	ctx->src_fmt = find_क्रमmat(&f, MFC_FMT_RAW);
	f.fmt.pix_mp.pixelक्रमmat = DEF_DST_FMT_ENC;
	ctx->dst_fmt = find_क्रमmat(&f, MFC_FMT_ENC);
पूर्ण
