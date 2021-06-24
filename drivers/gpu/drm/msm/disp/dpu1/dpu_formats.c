<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <uapi/drm/drm_fourcc.h>

#समावेश "msm_media_info.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_formats.h"

#घोषणा DPU_UBWC_META_MACRO_W_H		16
#घोषणा DPU_UBWC_META_BLOCK_SIZE	256
#घोषणा DPU_UBWC_PLANE_SIZE_ALIGNMENT	4096

#घोषणा DPU_TILE_HEIGHT_DEFAULT	1
#घोषणा DPU_TILE_HEIGHT_TILED	4
#घोषणा DPU_TILE_HEIGHT_UBWC	4
#घोषणा DPU_TILE_HEIGHT_NV12	8

#घोषणा DPU_MAX_IMG_WIDTH		0x3FFF
#घोषणा DPU_MAX_IMG_HEIGHT		0x3FFF

/*
 * DPU supported क्रमmat packing, bpp, and other क्रमmat
 * inक्रमmation.
 * DPU currently only supports पूर्णांकerleaved RGB क्रमmats
 * UBWC support क्रम a pixel क्रमmat is indicated by the flag,
 * there is additional meta data plane क्रम such क्रमmats
 */

#घोषणा INTERLEAVED_RGB_FMT(fmt, a, r, g, b, e0, e1, e2, e3, uc, alpha,   \
bp, flg, fm, np)                                                          \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_INTERLEAVED,                            \
	.alpha_enable = alpha,                                            \
	.element = अणु (e0), (e1), (e2), (e3) पूर्ण,                            \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = DPU_CHROMA_RGB,                                  \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = uc,                                               \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = DPU_TILE_HEIGHT_DEFAULT                            \
पूर्ण

#घोषणा INTERLEAVED_RGB_FMT_TILED(fmt, a, r, g, b, e0, e1, e2, e3, uc,    \
alpha, bp, flg, fm, np, th)                                               \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_INTERLEAVED,                            \
	.alpha_enable = alpha,                                            \
	.element = अणु (e0), (e1), (e2), (e3) पूर्ण,                            \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = DPU_CHROMA_RGB,                                  \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = uc,                                               \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = th                                                 \
पूर्ण


#घोषणा INTERLEAVED_YUV_FMT(fmt, a, r, g, b, e0, e1, e2, e3,              \
alpha, chroma, count, bp, flg, fm, np)                                    \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_INTERLEAVED,                            \
	.alpha_enable = alpha,                                            \
	.element = अणु (e0), (e1), (e2), (e3)पूर्ण,                             \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = count,                                            \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = DPU_TILE_HEIGHT_DEFAULT                            \
पूर्ण

#घोषणा PSEUDO_YUV_FMT(fmt, a, r, g, b, e0, e1, chroma, flg, fm, np)      \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_PSEUDO_PLANAR,                          \
	.alpha_enable = false,                                            \
	.element = अणु (e0), (e1), 0, 0 पूर्ण,                                  \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = DPU_TILE_HEIGHT_DEFAULT                            \
पूर्ण

#घोषणा PSEUDO_YUV_FMT_TILED(fmt, a, r, g, b, e0, e1, chroma,             \
flg, fm, np, th)                                                          \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_PSEUDO_PLANAR,                          \
	.alpha_enable = false,                                            \
	.element = अणु (e0), (e1), 0, 0 पूर्ण,                                  \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = th                                                 \
पूर्ण

#घोषणा PSEUDO_YUV_FMT_LOOSE(fmt, a, r, g, b, e0, e1, chroma, flg, fm, np)\
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_PSEUDO_PLANAR,                          \
	.alpha_enable = false,                                            \
	.element = अणु (e0), (e1), 0, 0 पूर्ण,                                  \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 1,                                            \
	.unpack_tight = 0,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = DPU_TILE_HEIGHT_DEFAULT                            \
पूर्ण

#घोषणा PSEUDO_YUV_FMT_LOOSE_TILED(fmt, a, r, g, b, e0, e1, chroma,       \
flg, fm, np, th)                                                          \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_PSEUDO_PLANAR,                          \
	.alpha_enable = false,                                            \
	.element = अणु (e0), (e1), 0, 0 पूर्ण,                                  \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 1,                                            \
	.unpack_tight = 0,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = th                                                 \
पूर्ण


#घोषणा PLANAR_YUV_FMT(fmt, a, r, g, b, e0, e1, e2, alpha, chroma, bp,    \
flg, fm, np)                                                      \
अणु                                                                         \
	.base.pixel_क्रमmat = DRM_FORMAT_ ## fmt,                          \
	.fetch_planes = DPU_PLANE_PLANAR,                                 \
	.alpha_enable = alpha,                                            \
	.element = अणु (e0), (e1), (e2), 0 पूर्ण,                               \
	.bits = अणु g, b, r, a पूर्ण,                                           \
	.chroma_sample = chroma,                                          \
	.unpack_align_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 1,                                                \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.flag = अणु(flg)पूर्ण,                                                  \
	.num_planes = np,                                                 \
	.tile_height = DPU_TILE_HEIGHT_DEFAULT                            \
पूर्ण

/*
 * काष्ठा dpu_media_color_map - maps drm क्रमmat to media क्रमmat
 * @क्रमmat: DRM base pixel क्रमmat
 * @color: Media API color related to DRM क्रमmat
 */
काष्ठा dpu_media_color_map अणु
	uपूर्णांक32_t क्रमmat;
	uपूर्णांक32_t color;
पूर्ण;

अटल स्थिर काष्ठा dpu_क्रमmat dpu_क्रमmat_map[] = अणु
	INTERLEAVED_RGB_FMT(ARGB8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		true, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ABGR8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XBGR8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBA8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		true, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRA8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		true, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRX8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		false, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XRGB8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		false, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBX8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		false, 4, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGB888,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, 0, 3,
		false, 3, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGR888,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, 0, 3,
		false, 3, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGB565,
		0, COLOR_5BIT, COLOR_6BIT, COLOR_5BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, 0, 3,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGR565,
		0, COLOR_5BIT, COLOR_6BIT, COLOR_5BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, 0, 3,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ARGB1555,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ABGR1555,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBA5551,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRA5551,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XRGB1555,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XBGR1555,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBX5551,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRX5551,
		COLOR_ALPHA_1BIT, COLOR_5BIT, COLOR_5BIT, COLOR_5BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ARGB4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ABGR4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBA4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRA4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		true, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XRGB4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XBGR4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBX4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRX4444,
		COLOR_ALPHA_4BIT, COLOR_4BIT, COLOR_4BIT, COLOR_4BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		false, 2, 0,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRA1010102,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		true, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBA1010102,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		true, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ABGR2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(ARGB2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XRGB2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C3_ALPHA, 4,
		false, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(BGRX1010102,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C2_R_Cr, C0_G_Y, C1_B_Cb, 4,
		false, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(XBGR2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	INTERLEAVED_RGB_FMT(RGBX1010102,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C3_ALPHA, C1_B_Cb, C0_G_Y, C2_R_Cr, 4,
		false, 4, DPU_FORMAT_FLAG_DX,
		DPU_FETCH_LINEAR, 1),

	PSEUDO_YUV_FMT(NV12,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C2_R_Cr,
		DPU_CHROMA_420, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	PSEUDO_YUV_FMT(NV21,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C1_B_Cb,
		DPU_CHROMA_420, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	PSEUDO_YUV_FMT(NV16,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C2_R_Cr,
		DPU_CHROMA_H2V1, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	PSEUDO_YUV_FMT(NV61,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C1_B_Cb,
		DPU_CHROMA_H2V1, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	INTERLEAVED_YUV_FMT(VYUY,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C0_G_Y,
		false, DPU_CHROMA_H2V1, 4, 2, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	INTERLEAVED_YUV_FMT(UYVY,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C0_G_Y, C2_R_Cr, C0_G_Y,
		false, DPU_CHROMA_H2V1, 4, 2, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	INTERLEAVED_YUV_FMT(YUYV,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C0_G_Y, C1_B_Cb, C0_G_Y, C2_R_Cr,
		false, DPU_CHROMA_H2V1, 4, 2, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	INTERLEAVED_YUV_FMT(YVYU,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C0_G_Y, C2_R_Cr, C0_G_Y, C1_B_Cb,
		false, DPU_CHROMA_H2V1, 4, 2, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 2),

	PLANAR_YUV_FMT(YUV420,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C1_B_Cb, C0_G_Y,
		false, DPU_CHROMA_420, 1, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 3),

	PLANAR_YUV_FMT(YVU420,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C2_R_Cr, C0_G_Y,
		false, DPU_CHROMA_420, 1, DPU_FORMAT_FLAG_YUV,
		DPU_FETCH_LINEAR, 3),
पूर्ण;

/*
 * UBWC क्रमmats table:
 * This table holds the UBWC क्रमmats supported.
 * If a compression ratio needs to be used क्रम this or any other क्रमmat,
 * the data will be passed by user-space.
 */
अटल स्थिर काष्ठा dpu_क्रमmat dpu_क्रमmat_map_ubwc[] = अणु
	INTERLEAVED_RGB_FMT_TILED(BGR565,
		0, COLOR_5BIT, COLOR_6BIT, COLOR_5BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, 0, 3,
		false, 2, DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	INTERLEAVED_RGB_FMT_TILED(ABGR8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	/* ARGB8888 and ABGR8888 purposely have the same color
	 * ordering.  The hardware only supports ABGR8888 UBWC
	 * natively.
	 */
	INTERLEAVED_RGB_FMT_TILED(ARGB8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	INTERLEAVED_RGB_FMT_TILED(XBGR8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 4, DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	INTERLEAVED_RGB_FMT_TILED(XRGB8888,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		false, 4, DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	INTERLEAVED_RGB_FMT_TILED(ABGR2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_DX | DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	INTERLEAVED_RGB_FMT_TILED(XBGR2101010,
		COLOR_8BIT, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C2_R_Cr, C0_G_Y, C1_B_Cb, C3_ALPHA, 4,
		true, 4, DPU_FORMAT_FLAG_DX | DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 2, DPU_TILE_HEIGHT_UBWC),

	PSEUDO_YUV_FMT_TILED(NV12,
		0, COLOR_8BIT, COLOR_8BIT, COLOR_8BIT,
		C1_B_Cb, C2_R_Cr,
		DPU_CHROMA_420, DPU_FORMAT_FLAG_YUV |
				DPU_FORMAT_FLAG_COMPRESSED,
		DPU_FETCH_UBWC, 4, DPU_TILE_HEIGHT_NV12),
पूर्ण;

/* _dpu_get_v_h_subsample_rate - Get subsample rates क्रम all क्रमmats we support
 *   Note: Not using the drm_क्रमmat_*_subsampling since we have क्रमmats
 */
अटल व्योम _dpu_get_v_h_subsample_rate(
	क्रमागत dpu_chroma_samp_type chroma_sample,
	uपूर्णांक32_t *v_sample,
	uपूर्णांक32_t *h_sample)
अणु
	अगर (!v_sample || !h_sample)
		वापस;

	चयन (chroma_sample) अणु
	हाल DPU_CHROMA_H2V1:
		*v_sample = 1;
		*h_sample = 2;
		अवरोध;
	हाल DPU_CHROMA_H1V2:
		*v_sample = 2;
		*h_sample = 1;
		अवरोध;
	हाल DPU_CHROMA_420:
		*v_sample = 2;
		*h_sample = 2;
		अवरोध;
	शेष:
		*v_sample = 1;
		*h_sample = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक _dpu_क्रमmat_get_media_color_ubwc(स्थिर काष्ठा dpu_क्रमmat *fmt)
अणु
	अटल स्थिर काष्ठा dpu_media_color_map dpu_media_ubwc_map[] = अणु
		अणुDRM_FORMAT_ABGR8888, COLOR_FMT_RGBA8888_UBWCपूर्ण,
		अणुDRM_FORMAT_ARGB8888, COLOR_FMT_RGBA8888_UBWCपूर्ण,
		अणुDRM_FORMAT_XBGR8888, COLOR_FMT_RGBA8888_UBWCपूर्ण,
		अणुDRM_FORMAT_XRGB8888, COLOR_FMT_RGBA8888_UBWCपूर्ण,
		अणुDRM_FORMAT_ABGR2101010, COLOR_FMT_RGBA1010102_UBWCपूर्ण,
		अणुDRM_FORMAT_XBGR2101010, COLOR_FMT_RGBA1010102_UBWCपूर्ण,
		अणुDRM_FORMAT_BGR565, COLOR_FMT_RGB565_UBWCपूर्ण,
	पूर्ण;
	पूर्णांक color_fmt = -1;
	पूर्णांक i;

	अगर (fmt->base.pixel_क्रमmat == DRM_FORMAT_NV12) अणु
		अगर (DPU_FORMAT_IS_DX(fmt)) अणु
			अगर (fmt->unpack_tight)
				color_fmt = COLOR_FMT_NV12_BPP10_UBWC;
			अन्यथा
				color_fmt = COLOR_FMT_P010_UBWC;
		पूर्ण अन्यथा
			color_fmt = COLOR_FMT_NV12_UBWC;
		वापस color_fmt;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dpu_media_ubwc_map); ++i)
		अगर (fmt->base.pixel_क्रमmat == dpu_media_ubwc_map[i].क्रमmat) अणु
			color_fmt = dpu_media_ubwc_map[i].color;
			अवरोध;
		पूर्ण
	वापस color_fmt;
पूर्ण

अटल पूर्णांक _dpu_क्रमmat_get_plane_sizes_ubwc(
		स्थिर काष्ठा dpu_क्रमmat *fmt,
		स्थिर uपूर्णांक32_t width,
		स्थिर uपूर्णांक32_t height,
		काष्ठा dpu_hw_fmt_layout *layout)
अणु
	पूर्णांक i;
	पूर्णांक color;
	bool meta = DPU_FORMAT_IS_UBWC(fmt);

	स_रखो(layout, 0, माप(काष्ठा dpu_hw_fmt_layout));
	layout->क्रमmat = fmt;
	layout->width = width;
	layout->height = height;
	layout->num_planes = fmt->num_planes;

	color = _dpu_क्रमmat_get_media_color_ubwc(fmt);
	अगर (color < 0) अणु
		DRM_ERROR("UBWC format not supported for fmt: %4.4s\n",
			(अक्षर *)&fmt->base.pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (DPU_FORMAT_IS_YUV(layout->क्रमmat)) अणु
		uपूर्णांक32_t y_sclines, uv_sclines;
		uपूर्णांक32_t y_meta_scanlines = 0;
		uपूर्णांक32_t uv_meta_scanlines = 0;

		layout->num_planes = 2;
		layout->plane_pitch[0] = VENUS_Y_STRIDE(color, width);
		y_sclines = VENUS_Y_SCANLINES(color, height);
		layout->plane_size[0] = MSM_MEDIA_ALIGN(layout->plane_pitch[0] *
			y_sclines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		layout->plane_pitch[1] = VENUS_UV_STRIDE(color, width);
		uv_sclines = VENUS_UV_SCANLINES(color, height);
		layout->plane_size[1] = MSM_MEDIA_ALIGN(layout->plane_pitch[1] *
			uv_sclines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		अगर (!meta)
			जाओ करोne;

		layout->num_planes += 2;
		layout->plane_pitch[2] = VENUS_Y_META_STRIDE(color, width);
		y_meta_scanlines = VENUS_Y_META_SCANLINES(color, height);
		layout->plane_size[2] = MSM_MEDIA_ALIGN(layout->plane_pitch[2] *
			y_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		layout->plane_pitch[3] = VENUS_UV_META_STRIDE(color, width);
		uv_meta_scanlines = VENUS_UV_META_SCANLINES(color, height);
		layout->plane_size[3] = MSM_MEDIA_ALIGN(layout->plane_pitch[3] *
			uv_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

	पूर्ण अन्यथा अणु
		uपूर्णांक32_t rgb_scanlines, rgb_meta_scanlines;

		layout->num_planes = 1;

		layout->plane_pitch[0] = VENUS_RGB_STRIDE(color, width);
		rgb_scanlines = VENUS_RGB_SCANLINES(color, height);
		layout->plane_size[0] = MSM_MEDIA_ALIGN(layout->plane_pitch[0] *
			rgb_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		अगर (!meta)
			जाओ करोne;
		layout->num_planes += 2;
		layout->plane_pitch[2] = VENUS_RGB_META_STRIDE(color, width);
		rgb_meta_scanlines = VENUS_RGB_META_SCANLINES(color, height);
		layout->plane_size[2] = MSM_MEDIA_ALIGN(layout->plane_pitch[2] *
			rgb_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);
	पूर्ण

करोne:
	क्रम (i = 0; i < DPU_MAX_PLANES; i++)
		layout->total_size += layout->plane_size[i];

	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_क्रमmat_get_plane_sizes_linear(
		स्थिर काष्ठा dpu_क्रमmat *fmt,
		स्थिर uपूर्णांक32_t width,
		स्थिर uपूर्णांक32_t height,
		काष्ठा dpu_hw_fmt_layout *layout,
		स्थिर uपूर्णांक32_t *pitches)
अणु
	पूर्णांक i;

	स_रखो(layout, 0, माप(काष्ठा dpu_hw_fmt_layout));
	layout->क्रमmat = fmt;
	layout->width = width;
	layout->height = height;
	layout->num_planes = fmt->num_planes;

	/* Due to स_रखो above, only need to set planes of पूर्णांकerest */
	अगर (fmt->fetch_planes == DPU_PLANE_INTERLEAVED) अणु
		layout->num_planes = 1;
		layout->plane_size[0] = width * height * layout->क्रमmat->bpp;
		layout->plane_pitch[0] = width * layout->क्रमmat->bpp;
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t v_subsample, h_subsample;
		uपूर्णांक32_t chroma_samp;
		uपूर्णांक32_t bpp = 1;

		chroma_samp = fmt->chroma_sample;
		_dpu_get_v_h_subsample_rate(chroma_samp, &v_subsample,
				&h_subsample);

		अगर (width % h_subsample || height % v_subsample) अणु
			DRM_ERROR("mismatch in subsample vs dimensions\n");
			वापस -EINVAL;
		पूर्ण

		अगर ((fmt->base.pixel_क्रमmat == DRM_FORMAT_NV12) &&
			(DPU_FORMAT_IS_DX(fmt)))
			bpp = 2;
		layout->plane_pitch[0] = width * bpp;
		layout->plane_pitch[1] = layout->plane_pitch[0] / h_subsample;
		layout->plane_size[0] = layout->plane_pitch[0] * height;
		layout->plane_size[1] = layout->plane_pitch[1] *
				(height / v_subsample);

		अगर (fmt->fetch_planes == DPU_PLANE_PSEUDO_PLANAR) अणु
			layout->num_planes = 2;
			layout->plane_size[1] *= 2;
			layout->plane_pitch[1] *= 2;
		पूर्ण अन्यथा अणु
			/* planar */
			layout->num_planes = 3;
			layout->plane_size[2] = layout->plane_size[1];
			layout->plane_pitch[2] = layout->plane_pitch[1];
		पूर्ण
	पूर्ण

	/*
	 * linear क्रमmat: allow user allocated pitches अगर they are greater than
	 * the requirement.
	 * ubwc क्रमmat: pitch values are computed unअगरormly across
	 * all the components based on ubwc specअगरications.
	 */
	क्रम (i = 0; i < layout->num_planes && i < DPU_MAX_PLANES; ++i) अणु
		अगर (pitches && layout->plane_pitch[i] < pitches[i])
			layout->plane_pitch[i] = pitches[i];
	पूर्ण

	क्रम (i = 0; i < DPU_MAX_PLANES; i++)
		layout->total_size += layout->plane_size[i];

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_क्रमmat_get_plane_sizes(
		स्थिर काष्ठा dpu_क्रमmat *fmt,
		स्थिर uपूर्णांक32_t w,
		स्थिर uपूर्णांक32_t h,
		काष्ठा dpu_hw_fmt_layout *layout,
		स्थिर uपूर्णांक32_t *pitches)
अणु
	अगर (!layout || !fmt) अणु
		DRM_ERROR("invalid pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((w > DPU_MAX_IMG_WIDTH) || (h > DPU_MAX_IMG_HEIGHT)) अणु
		DRM_ERROR("image dimensions outside max range\n");
		वापस -दुस्फल;
	पूर्ण

	अगर (DPU_FORMAT_IS_UBWC(fmt) || DPU_FORMAT_IS_TILE(fmt))
		वापस _dpu_क्रमmat_get_plane_sizes_ubwc(fmt, w, h, layout);

	वापस _dpu_क्रमmat_get_plane_sizes_linear(fmt, w, h, layout, pitches);
पूर्ण

अटल पूर्णांक _dpu_क्रमmat_populate_addrs_ubwc(
		काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_framebuffer *fb,
		काष्ठा dpu_hw_fmt_layout *layout)
अणु
	uपूर्णांक32_t base_addr = 0;
	bool meta;

	अगर (!fb || !layout) अणु
		DRM_ERROR("invalid pointers\n");
		वापस -EINVAL;
	पूर्ण

	अगर (aspace)
		base_addr = msm_framebuffer_iova(fb, aspace, 0);
	अगर (!base_addr) अणु
		DRM_ERROR("failed to retrieve base addr\n");
		वापस -EFAULT;
	पूर्ण

	meta = DPU_FORMAT_IS_UBWC(layout->क्रमmat);

	/* Per-क्रमmat logic क्रम verअगरying active planes */
	अगर (DPU_FORMAT_IS_YUV(layout->क्रमmat)) अणु
		/************************************************/
		/*      UBWC            **                      */
		/*      buffer          **      DPU PLANE       */
		/*      क्रमmat          **                      */
		/************************************************/
		/* -------------------  ** -------------------- */
		/* |      Y meta     |  ** |    Y bitstream   | */
		/* |       data      |  ** |       plane      | */
		/* -------------------  ** -------------------- */
		/* |    Y bitstream  |  ** |  CbCr bitstream  | */
		/* |       data      |  ** |       plane      | */
		/* -------------------  ** -------------------- */
		/* |   Cbcr metadata |  ** |       Y meta     | */
		/* |       data      |  ** |       plane      | */
		/* -------------------  ** -------------------- */
		/* |  CbCr bitstream |  ** |     CbCr meta    | */
		/* |       data      |  ** |       plane      | */
		/* -------------------  ** -------------------- */
		/************************************************/

		/* configure Y bitstream plane */
		layout->plane_addr[0] = base_addr + layout->plane_size[2];

		/* configure CbCr bitstream plane */
		layout->plane_addr[1] = base_addr + layout->plane_size[0]
			+ layout->plane_size[2] + layout->plane_size[3];

		अगर (!meta)
			वापस 0;

		/* configure Y metadata plane */
		layout->plane_addr[2] = base_addr;

		/* configure CbCr metadata plane */
		layout->plane_addr[3] = base_addr + layout->plane_size[0]
			+ layout->plane_size[2];

	पूर्ण अन्यथा अणु
		/************************************************/
		/*      UBWC            **                      */
		/*      buffer          **      DPU PLANE       */
		/*      क्रमmat          **                      */
		/************************************************/
		/* -------------------  ** -------------------- */
		/* |      RGB meta   |  ** |   RGB bitstream  | */
		/* |       data      |  ** |       plane      | */
		/* -------------------  ** -------------------- */
		/* |  RGB bitstream  |  ** |       NONE       | */
		/* |       data      |  ** |                  | */
		/* -------------------  ** -------------------- */
		/*                      ** |     RGB meta     | */
		/*                      ** |       plane      | */
		/*                      ** -------------------- */
		/************************************************/

		layout->plane_addr[0] = base_addr + layout->plane_size[2];
		layout->plane_addr[1] = 0;

		अगर (!meta)
			वापस 0;

		layout->plane_addr[2] = base_addr;
		layout->plane_addr[3] = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_क्रमmat_populate_addrs_linear(
		काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_framebuffer *fb,
		काष्ठा dpu_hw_fmt_layout *layout)
अणु
	अचिन्हित पूर्णांक i;

	/* Can now check the pitches given vs pitches expected */
	क्रम (i = 0; i < layout->num_planes; ++i) अणु
		अगर (layout->plane_pitch[i] > fb->pitches[i]) अणु
			DRM_ERROR("plane %u expected pitch %u, fb %u\n",
				i, layout->plane_pitch[i], fb->pitches[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Populate addresses क्रम simple क्रमmats here */
	क्रम (i = 0; i < layout->num_planes; ++i) अणु
		अगर (aspace)
			layout->plane_addr[i] =
				msm_framebuffer_iova(fb, aspace, i);
		अगर (!layout->plane_addr[i]) अणु
			DRM_ERROR("failed to retrieve base addr\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dpu_क्रमmat_populate_layout(
		काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_framebuffer *fb,
		काष्ठा dpu_hw_fmt_layout *layout)
अणु
	uपूर्णांक32_t plane_addr[DPU_MAX_PLANES];
	पूर्णांक i, ret;

	अगर (!fb || !layout) अणु
		DRM_ERROR("invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fb->width > DPU_MAX_IMG_WIDTH) ||
			(fb->height > DPU_MAX_IMG_HEIGHT)) अणु
		DRM_ERROR("image dimensions outside max range\n");
		वापस -दुस्फल;
	पूर्ण

	layout->क्रमmat = to_dpu_क्रमmat(msm_framebuffer_क्रमmat(fb));

	/* Populate the plane sizes etc via get_क्रमmat */
	ret = dpu_क्रमmat_get_plane_sizes(layout->क्रमmat, fb->width, fb->height,
			layout, fb->pitches);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < DPU_MAX_PLANES; ++i)
		plane_addr[i] = layout->plane_addr[i];

	/* Populate the addresses given the fb */
	अगर (DPU_FORMAT_IS_UBWC(layout->क्रमmat) ||
			DPU_FORMAT_IS_TILE(layout->क्रमmat))
		ret = _dpu_क्रमmat_populate_addrs_ubwc(aspace, fb, layout);
	अन्यथा
		ret = _dpu_क्रमmat_populate_addrs_linear(aspace, fb, layout);

	/* check अगर anything changed */
	अगर (!ret && !स_भेद(plane_addr, layout->plane_addr, माप(plane_addr)))
		ret = -EAGAIN;

	वापस ret;
पूर्ण

पूर्णांक dpu_क्रमmat_check_modअगरied_क्रमmat(
		स्थिर काष्ठा msm_kms *kms,
		स्थिर काष्ठा msm_क्रमmat *msm_fmt,
		स्थिर काष्ठा drm_mode_fb_cmd2 *cmd,
		काष्ठा drm_gem_object **bos)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	स्थिर काष्ठा dpu_क्रमmat *fmt;
	काष्ठा dpu_hw_fmt_layout layout;
	uपूर्णांक32_t bos_total_size = 0;
	पूर्णांक ret, i;

	अगर (!msm_fmt || !cmd || !bos) अणु
		DRM_ERROR("invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	fmt = to_dpu_क्रमmat(msm_fmt);
	info = drm_क्रमmat_info(fmt->base.pixel_क्रमmat);
	अगर (!info)
		वापस -EINVAL;

	ret = dpu_क्रमmat_get_plane_sizes(fmt, cmd->width, cmd->height,
			&layout, cmd->pitches);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < info->num_planes; i++) अणु
		अगर (!bos[i]) अणु
			DRM_ERROR("invalid handle for plane %d\n", i);
			वापस -EINVAL;
		पूर्ण
		अगर ((i == 0) || (bos[i] != bos[0]))
			bos_total_size += bos[i]->size;
	पूर्ण

	अगर (bos_total_size < layout.total_size) अणु
		DRM_ERROR("buffers total size too small %u expected %u\n",
				bos_total_size, layout.total_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dpu_क्रमmat *dpu_get_dpu_क्रमmat_ext(
		स्थिर uपूर्णांक32_t क्रमmat,
		स्थिर uपूर्णांक64_t modअगरier)
अणु
	uपूर्णांक32_t i = 0;
	स्थिर काष्ठा dpu_क्रमmat *fmt = शून्य;
	स्थिर काष्ठा dpu_क्रमmat *map = शून्य;
	sमाप_प्रकार map_size = 0;

	/*
	 * Currently only support exactly zero or one modअगरier.
	 * All planes use the same modअगरier.
	 */
	DPU_DEBUG("plane format modifier 0x%llX\n", modअगरier);

	चयन (modअगरier) अणु
	हाल 0:
		map = dpu_क्रमmat_map;
		map_size = ARRAY_SIZE(dpu_क्रमmat_map);
		अवरोध;
	हाल DRM_FORMAT_MOD_QCOM_COMPRESSED:
		map = dpu_क्रमmat_map_ubwc;
		map_size = ARRAY_SIZE(dpu_क्रमmat_map_ubwc);
		DPU_DEBUG("found fmt: %4.4s  DRM_FORMAT_MOD_QCOM_COMPRESSED\n",
				(अक्षर *)&क्रमmat);
		अवरोध;
	शेष:
		DPU_ERROR("unsupported format modifier %llX\n", modअगरier);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < map_size; i++) अणु
		अगर (क्रमmat == map[i].base.pixel_क्रमmat) अणु
			fmt = &map[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fmt == शून्य)
		DPU_ERROR("unsupported fmt: %4.4s modifier 0x%llX\n",
			(अक्षर *)&क्रमmat, modअगरier);
	अन्यथा
		DPU_DEBUG("fmt %4.4s mod 0x%llX ubwc %d yuv %d\n",
				(अक्षर *)&क्रमmat, modअगरier,
				DPU_FORMAT_IS_UBWC(fmt),
				DPU_FORMAT_IS_YUV(fmt));

	वापस fmt;
पूर्ण

स्थिर काष्ठा msm_क्रमmat *dpu_get_msm_क्रमmat(
		काष्ठा msm_kms *kms,
		स्थिर uपूर्णांक32_t क्रमmat,
		स्थिर uपूर्णांक64_t modअगरiers)
अणु
	स्थिर काष्ठा dpu_क्रमmat *fmt = dpu_get_dpu_क्रमmat_ext(क्रमmat,
			modअगरiers);
	अगर (fmt)
		वापस &fmt->base;
	वापस शून्य;
पूर्ण
