<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश "vdec_platform.h"
#समावेश "vdec.h"

#समावेश "vdec_1.h"
#समावेश "vdec_hevc.h"
#समावेश "codec_mpeg12.h"
#समावेश "codec_h264.h"
#समावेश "codec_vp9.h"

अटल स्थिर काष्ठा amvdec_क्रमmat vdec_क्रमmats_gxbb[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.min_buffers = 2,
		.max_buffers = 24,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.firmware_path = "meson/vdec/gxbb_h264.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG1,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amvdec_क्रमmat vdec_क्रमmats_gxl[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_VP9,
		.min_buffers = 16,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.firmware_path = "meson/vdec/gxl_vp9.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.min_buffers = 2,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.firmware_path = "meson/vdec/gxl_h264.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG1,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amvdec_क्रमmat vdec_क्रमmats_gxm[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.min_buffers = 2,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.firmware_path = "meson/vdec/gxm_h264.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG1,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amvdec_क्रमmat vdec_क्रमmats_g12a[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_VP9,
		.min_buffers = 16,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.firmware_path = "meson/vdec/g12a_vp9.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.min_buffers = 2,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.firmware_path = "meson/vdec/g12a_h264.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG1,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amvdec_क्रमmat vdec_क्रमmats_sm1[] = अणु
	अणु
		.pixfmt = V4L2_PIX_FMT_VP9,
		.min_buffers = 16,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.firmware_path = "meson/vdec/sm1_vp9_mmu.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_H264,
		.min_buffers = 2,
		.max_buffers = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.firmware_path = "meson/vdec/g12a_h264.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED |
			 V4L2_FMT_FLAG_DYN_RESOLUTION,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG1,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण, अणु
		.pixfmt = V4L2_PIX_FMT_MPEG2,
		.min_buffers = 8,
		.max_buffers = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.firmware_path = "meson/vdec/gxl_mpeg12.bin",
		.pixfmts_cap = अणु V4L2_PIX_FMT_NV12M, V4L2_PIX_FMT_YUV420M, 0 पूर्ण,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxbb = अणु
	.क्रमmats = vdec_क्रमmats_gxbb,
	.num_क्रमmats = ARRAY_SIZE(vdec_क्रमmats_gxbb),
	.revision = VDEC_REVISION_GXBB,
पूर्ण;

स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxl = अणु
	.क्रमmats = vdec_क्रमmats_gxl,
	.num_क्रमmats = ARRAY_SIZE(vdec_क्रमmats_gxl),
	.revision = VDEC_REVISION_GXL,
पूर्ण;

स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxm = अणु
	.क्रमmats = vdec_क्रमmats_gxm,
	.num_क्रमmats = ARRAY_SIZE(vdec_क्रमmats_gxm),
	.revision = VDEC_REVISION_GXM,
पूर्ण;

स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_g12a = अणु
	.क्रमmats = vdec_क्रमmats_g12a,
	.num_क्रमmats = ARRAY_SIZE(vdec_क्रमmats_g12a),
	.revision = VDEC_REVISION_G12A,
पूर्ण;

स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_sm1 = अणु
	.क्रमmats = vdec_क्रमmats_sm1,
	.num_क्रमmats = ARRAY_SIZE(vdec_क्रमmats_sm1),
	.revision = VDEC_REVISION_SM1,
पूर्ण;
