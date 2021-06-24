<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */
#समावेश "hfi_platform.h"

अटल स्थिर काष्ठा hfi_plat_caps caps[] = अणु
अणु
	.codec = HFI_VIDEO_CODEC_H264,
	.करोमुख्य = VIDC_SESSION_TYPE_DEC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 8192, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 8192, 1पूर्ण,
	/* ((5760 * 2880) / 256) */
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 138240, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 220000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 65536, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 65536, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 960, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.num_caps = 9,
	.pl[0] = अणुHFI_H264_PROखाता_BASELINE, HFI_H264_LEVEL_52पूर्ण,
	.pl[1] = अणुHFI_H264_PROखाता_MAIN, HFI_H264_LEVEL_52पूर्ण,
	.pl[2] = अणुHFI_H264_PROखाता_HIGH, HFI_H264_LEVEL_52पूर्ण,
	.pl[3] = अणुHFI_H264_PROखाता_CONSTRAINED_BASE, HFI_H264_LEVEL_52पूर्ण,
	.pl[4] = अणुHFI_H264_PROखाता_CONSTRAINED_HIGH, HFI_H264_LEVEL_52पूर्ण,
	.num_pl = 5,
	.fmts[0] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[1] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[3] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV21पूर्ण,
	.num_fmts = 4,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_HEVC,
	.करोमुख्य = VIDC_SESSION_TYPE_DEC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 8192, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 8192, 1पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 138240, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 220000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 65536, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 65536, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 960, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 3, 1पूर्ण,
	.num_caps = 10,
	.pl[0] = अणुHFI_HEVC_PROखाता_MAIN, HFI_HEVC_LEVEL_6 | HFI_HEVC_TIER_HIGH0पूर्ण,
	.pl[1] = अणुHFI_HEVC_PROखाता_MAIN10, HFI_HEVC_LEVEL_6 | HFI_HEVC_TIER_HIGH0पूर्ण,
	.num_pl = 2,
	.fmts[0] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[1] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_YUV420_TP10_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[3] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[4] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV21पूर्ण,
	.fmts[5] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_P010पूर्ण,
	.fmts[6] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_YUV420_TP10पूर्ण,
	.num_fmts = 7,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_VP8,
	.करोमुख्य = VIDC_SESSION_TYPE_DEC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 4096, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 4096, 1पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 36864, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 100000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 65536, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 65536, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 4423680, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 120, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 3, 1पूर्ण,
	.num_caps = 10,
	.pl[0] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_0पूर्ण,
	.pl[1] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_1पूर्ण,
	.pl[2] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_2पूर्ण,
	.pl[3] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_3पूर्ण,
	.num_pl = 4,
	.fmts[0] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[1] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[3] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV21पूर्ण,
	.num_fmts = 4,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_VP9,
	.करोमुख्य = VIDC_SESSION_TYPE_DEC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 8192, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 8192, 1पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 138240, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 220000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 65536, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 65536, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 960, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 3, 1पूर्ण,
	.num_caps = 10,
	.pl[0] = अणुHFI_VP9_PROखाता_P0, 200पूर्ण,
	.pl[1] = अणुHFI_VP9_PROखाता_P2_10B, 200पूर्ण,
	.num_pl = 2,
	.fmts[0] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[1] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_YUV420_TP10_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[3] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[4] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV21पूर्ण,
	.fmts[5] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_P010पूर्ण,
	.fmts[6] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_YUV420_TP10पूर्ण,
	.num_fmts = 7,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_MPEG2,
	.करोमुख्य = VIDC_SESSION_TYPE_DEC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 1920, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 1920, 1पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 8160, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 40000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 65536, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 65536, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 30, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 1, 1पूर्ण,
	.num_caps = 10,
	.pl[0] = अणुHFI_MPEG2_PROखाता_SIMPLE, HFI_MPEG2_LEVEL_H14पूर्ण,
	.pl[1] = अणुHFI_MPEG2_PROखाता_MAIN, HFI_MPEG2_LEVEL_H14पूर्ण,
	.num_pl = 2,
	.fmts[0] = अणुHFI_BUFFER_OUTPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[1] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[3] = अणुHFI_BUFFER_OUTPUT2, HFI_COLOR_FORMAT_NV21पूर्ण,
	.num_fmts = 4,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_H264,
	.करोमुख्य = VIDC_SESSION_TYPE_ENC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 8192, 1पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 8192, 1पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 138240, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 220000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 8192, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 8192, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 960, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_PEAKBITRATE, 32000, 160000000, 1पूर्ण,
	.caps[10] = अणुHFI_CAPABILITY_HIER_P_NUM_ENH_LAYERS, 0, 6, 1पूर्ण,
	.caps[11] = अणुHFI_CAPABILITY_ENC_LTR_COUNT, 0, 2, 1पूर्ण,
	.caps[12] = अणुHFI_CAPABILITY_LCU_SIZE, 16, 16, 1पूर्ण,
	.caps[13] = अणुHFI_CAPABILITY_BFRAME, 0, 1, 1पूर्ण,
	.caps[14] = अणुHFI_CAPABILITY_HIER_P_HYBRID_NUM_ENH_LAYERS, 0, 6, 1पूर्ण,
	.caps[15] = अणुHFI_CAPABILITY_I_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[16] = अणुHFI_CAPABILITY_P_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[17] = अणुHFI_CAPABILITY_B_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[18] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 2, 1पूर्ण,
	.caps[19] = अणुHFI_CAPABILITY_RATE_CONTROL_MODES, 0x1000001, 0x1000005, 1पूर्ण,
	.caps[20] = अणुHFI_CAPABILITY_COLOR_SPACE_CONVERSION, 0, 2, 1पूर्ण,
	.num_caps = 21,
	.pl[0] = अणुHFI_H264_PROखाता_BASELINE, HFI_H264_LEVEL_52पूर्ण,
	.pl[1] = अणुHFI_H264_PROखाता_MAIN, HFI_H264_LEVEL_52पूर्ण,
	.pl[2] = अणुHFI_H264_PROखाता_HIGH, HFI_H264_LEVEL_52पूर्ण,
	.pl[3] = अणुHFI_H264_PROखाता_CONSTRAINED_BASE, HFI_H264_LEVEL_52पूर्ण,
	.pl[4] = अणुHFI_H264_PROखाता_CONSTRAINED_HIGH, HFI_H264_LEVEL_52पूर्ण,
	.num_pl = 5,
	.fmts[0] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[1] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_YUV420_TP10_UBWCपूर्ण,
	.fmts[3] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_P010पूर्ण,
	.num_fmts = 4,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_HEVC,
	.करोमुख्य = VIDC_SESSION_TYPE_ENC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 8192, 16पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 8192, 16पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 138240, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 160000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 8192, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 8192, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 7833600, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 960, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_PEAKBITRATE, 32000, 160000000, 1पूर्ण,
	.caps[10] = अणुHFI_CAPABILITY_HIER_P_NUM_ENH_LAYERS, 0, 5, 1पूर्ण,
	.caps[11] = अणुHFI_CAPABILITY_ENC_LTR_COUNT, 0, 2, 1पूर्ण,
	.caps[12] = अणुHFI_CAPABILITY_LCU_SIZE, 32, 32, 1पूर्ण,
	.caps[13] = अणुHFI_CAPABILITY_BFRAME, 0, 1, 1पूर्ण,
	.caps[14] = अणुHFI_CAPABILITY_HIER_P_HYBRID_NUM_ENH_LAYERS, 0, 5, 1पूर्ण,
	.caps[15] = अणुHFI_CAPABILITY_I_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[16] = अणुHFI_CAPABILITY_P_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[17] = अणुHFI_CAPABILITY_B_FRAME_QP, 0, 51, 1पूर्ण,
	.caps[18] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 2, 1पूर्ण,
	.caps[19] = अणुHFI_CAPABILITY_RATE_CONTROL_MODES, 0x1000001, 0x1000005, 1पूर्ण,
	.caps[20] = अणुHFI_CAPABILITY_COLOR_SPACE_CONVERSION, 0, 2, 1पूर्ण,
	.caps[21] = अणुHFI_CAPABILITY_ROTATION, 1, 4, 90पूर्ण,
	.caps[22] = अणुHFI_CAPABILITY_BLUR_WIDTH, 96, 4096, 16पूर्ण,
	.caps[23] = अणुHFI_CAPABILITY_BLUR_HEIGHT, 96, 4096, 16पूर्ण,
	.num_caps = 24,
	.pl[0] = अणुHFI_HEVC_PROखाता_MAIN, HFI_HEVC_LEVEL_6 | HFI_HEVC_TIER_HIGH0पूर्ण,
	.pl[1] = अणुHFI_HEVC_PROखाता_MAIN10, HFI_HEVC_LEVEL_6 | HFI_HEVC_TIER_HIGH0पूर्ण,
	.num_pl = 2,
	.fmts[0] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[1] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_YUV420_TP10_UBWCपूर्ण,
	.fmts[3] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_P010पूर्ण,
	.num_fmts = 4,
पूर्ण, अणु
	.codec = HFI_VIDEO_CODEC_VP8,
	.करोमुख्य = VIDC_SESSION_TYPE_ENC,
	.cap_bufs_mode_dynamic = true,
	.caps[0] = अणुHFI_CAPABILITY_FRAME_WIDTH, 128, 4096, 16पूर्ण,
	.caps[1] = अणुHFI_CAPABILITY_FRAME_HEIGHT, 128, 4096, 16पूर्ण,
	.caps[2] = अणुHFI_CAPABILITY_MBS_PER_FRAME, 64, 36864, 1पूर्ण,
	.caps[3] = अणुHFI_CAPABILITY_BITRATE, 1, 74000000, 1पूर्ण,
	.caps[4] = अणुHFI_CAPABILITY_SCALE_X, 8192, 65536, 1पूर्ण,
	.caps[5] = अणुHFI_CAPABILITY_SCALE_Y, 8192, 65536, 1पूर्ण,
	.caps[6] = अणुHFI_CAPABILITY_MBS_PER_SECOND, 64, 4423680, 1पूर्ण,
	.caps[7] = अणुHFI_CAPABILITY_FRAMERATE, 1, 120, 1पूर्ण,
	.caps[8] = अणुHFI_CAPABILITY_MAX_VIDEOCORES, 0, 1, 1पूर्ण,
	.caps[9] = अणुHFI_CAPABILITY_PEAKBITRATE, 32000, 160000000, 1पूर्ण,
	.caps[10] = अणुHFI_CAPABILITY_HIER_P_NUM_ENH_LAYERS, 0, 3, 1पूर्ण,
	.caps[11] = अणुHFI_CAPABILITY_ENC_LTR_COUNT, 0, 2, 1पूर्ण,
	.caps[12] = अणुHFI_CAPABILITY_LCU_SIZE, 16, 16, 1पूर्ण,
	.caps[13] = अणुHFI_CAPABILITY_BFRAME, 0, 0, 1पूर्ण,
	.caps[14] = अणुHFI_CAPABILITY_HIER_P_HYBRID_NUM_ENH_LAYERS, 0, 5, 1पूर्ण,
	.caps[15] = अणुHFI_CAPABILITY_I_FRAME_QP, 0, 127, 1पूर्ण,
	.caps[16] = अणुHFI_CAPABILITY_P_FRAME_QP, 0, 127, 1पूर्ण,
	.caps[17] = अणुHFI_CAPABILITY_MAX_WORKMODES, 1, 2, 1पूर्ण,
	.caps[18] = अणुHFI_CAPABILITY_RATE_CONTROL_MODES, 0x1000001, 0x1000005, 1पूर्ण,
	.caps[19] = अणुHFI_CAPABILITY_BLUR_WIDTH, 96, 4096, 16पूर्ण,
	.caps[20] = अणुHFI_CAPABILITY_BLUR_HEIGHT, 96, 4096, 16पूर्ण,
	.caps[21] = अणुHFI_CAPABILITY_COLOR_SPACE_CONVERSION, 0, 2, 1पूर्ण,
	.caps[22] = अणुHFI_CAPABILITY_ROTATION, 1, 4, 90पूर्ण,
	.num_caps = 23,
	.pl[0] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_0पूर्ण,
	.pl[1] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_1पूर्ण,
	.pl[2] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_2पूर्ण,
	.pl[3] = अणुHFI_VPX_PROखाता_MAIN, HFI_VPX_LEVEL_VERSION_3पूर्ण,
	.num_pl = 4,
	.fmts[0] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12पूर्ण,
	.fmts[1] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_NV12_UBWCपूर्ण,
	.fmts[2] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_YUV420_TP10_UBWCपूर्ण,
	.fmts[3] = अणुHFI_BUFFER_INPUT, HFI_COLOR_FORMAT_P010पूर्ण,
	.num_fmts = 4,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा hfi_plat_caps *get_capabilities(अचिन्हित पूर्णांक *entries)
अणु
	*entries = ARRAY_SIZE(caps);
	वापस caps;
पूर्ण

अटल व्योम get_codecs(u32 *enc_codecs, u32 *dec_codecs, u32 *count)
अणु
	*enc_codecs = HFI_VIDEO_CODEC_H264 | HFI_VIDEO_CODEC_HEVC |
		      HFI_VIDEO_CODEC_VP8;
	*dec_codecs = HFI_VIDEO_CODEC_H264 | HFI_VIDEO_CODEC_HEVC |
		      HFI_VIDEO_CODEC_VP8 | HFI_VIDEO_CODEC_VP9 |
		      HFI_VIDEO_CODEC_MPEG2;
	*count = 8;
पूर्ण

अटल स्थिर काष्ठा hfi_platक्रमm_codec_freq_data codec_freq_data[] = अणु
	अणु V4L2_PIX_FMT_H264, VIDC_SESSION_TYPE_ENC, 675, 25 पूर्ण,
	अणु V4L2_PIX_FMT_HEVC, VIDC_SESSION_TYPE_ENC, 675, 25 पूर्ण,
	अणु V4L2_PIX_FMT_VP8, VIDC_SESSION_TYPE_ENC, 675, 60 पूर्ण,
	अणु V4L2_PIX_FMT_MPEG2, VIDC_SESSION_TYPE_DEC, 200, 25 पूर्ण,
	अणु V4L2_PIX_FMT_H264, VIDC_SESSION_TYPE_DEC, 200, 25 पूर्ण,
	अणु V4L2_PIX_FMT_HEVC, VIDC_SESSION_TYPE_DEC, 200, 25 पूर्ण,
	अणु V4L2_PIX_FMT_VP8, VIDC_SESSION_TYPE_DEC, 200, 60 पूर्ण,
	अणु V4L2_PIX_FMT_VP9, VIDC_SESSION_TYPE_DEC, 200, 60 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hfi_platक्रमm_codec_freq_data *
get_codec_freq_data(u32 session_type, u32 pixfmt)
अणु
	स्थिर काष्ठा hfi_platक्रमm_codec_freq_data *data = codec_freq_data;
	अचिन्हित पूर्णांक i, data_size = ARRAY_SIZE(codec_freq_data);
	स्थिर काष्ठा hfi_platक्रमm_codec_freq_data *found = शून्य;

	क्रम (i = 0; i < data_size; i++) अणु
		अगर (data[i].pixfmt == pixfmt && data[i].session_type == session_type) अणु
			found = &data[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल अचिन्हित दीर्घ codec_vpp_freq(u32 session_type, u32 codec)
अणु
	स्थिर काष्ठा hfi_platक्रमm_codec_freq_data *data;

	data = get_codec_freq_data(session_type, codec);
	अगर (data)
		वापस data->vpp_freq;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ codec_vsp_freq(u32 session_type, u32 codec)
अणु
	स्थिर काष्ठा hfi_platक्रमm_codec_freq_data *data;

	data = get_codec_freq_data(session_type, codec);
	अगर (data)
		वापस data->vsp_freq;

	वापस 0;
पूर्ण

अटल u8 num_vpp_pipes(व्योम)
अणु
	वापस 4;
पूर्ण

स्थिर काष्ठा hfi_platक्रमm hfi_plat_v6 = अणु
	.codec_vpp_freq = codec_vpp_freq,
	.codec_vsp_freq = codec_vsp_freq,
	.codecs = get_codecs,
	.capabilities = get_capabilities,
	.num_vpp_pipes = num_vpp_pipes,
	.bufreq = hfi_plat_bufreq_v6,
पूर्ण;
