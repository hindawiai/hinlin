<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */


#समावेश "msm_drv.h"
#समावेश "mdp_kms.h"

अटल काष्ठा csc_cfg csc_convert[CSC_MAX] = अणु
	[CSC_RGB2RGB] = अणु
		.type = CSC_RGB2RGB,
		.matrix = अणु
			0x0200, 0x0000, 0x0000,
			0x0000, 0x0200, 0x0000,
			0x0000, 0x0000, 0x0200
		पूर्ण,
		.pre_bias =	अणु 0x0, 0x0, 0x0 पूर्ण,
		.post_bias =	अणु 0x0, 0x0, 0x0 पूर्ण,
		.pre_clamp =	अणु 0x0, 0xff, 0x0, 0xff, 0x0, 0xff पूर्ण,
		.post_clamp =	अणु 0x0, 0xff, 0x0, 0xff, 0x0, 0xff पूर्ण,
	पूर्ण,
	[CSC_YUV2RGB] = अणु
		.type = CSC_YUV2RGB,
		.matrix = अणु
			0x0254, 0x0000, 0x0331,
			0x0254, 0xff37, 0xfe60,
			0x0254, 0x0409, 0x0000
		पूर्ण,
		.pre_bias =	अणु 0xfff0, 0xff80, 0xff80 पूर्ण,
		.post_bias =	अणु 0x00, 0x00, 0x00 पूर्ण,
		.pre_clamp =	अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff पूर्ण,
		.post_clamp =	अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff पूर्ण,
	पूर्ण,
	[CSC_RGB2YUV] = अणु
		.type = CSC_RGB2YUV,
		.matrix = अणु
			0x0083, 0x0102, 0x0032,
			0x1fb5, 0x1f6c, 0x00e1,
			0x00e1, 0x1f45, 0x1fdc
		पूर्ण,
		.pre_bias =	अणु 0x00, 0x00, 0x00 पूर्ण,
		.post_bias =	अणु 0x10, 0x80, 0x80 पूर्ण,
		.pre_clamp =	अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff पूर्ण,
		.post_clamp =	अणु 0x10, 0xeb, 0x10, 0xf0, 0x10, 0xf0 पूर्ण,
	पूर्ण,
	[CSC_YUV2YUV] = अणु
		.type = CSC_YUV2YUV,
		.matrix = अणु
			0x0200, 0x0000, 0x0000,
			0x0000, 0x0200, 0x0000,
			0x0000, 0x0000, 0x0200
		पूर्ण,
		.pre_bias =	अणु 0x00, 0x00, 0x00 पूर्ण,
		.post_bias =	अणु 0x00, 0x00, 0x00 पूर्ण,
		.pre_clamp =	अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff पूर्ण,
		.post_clamp =	अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा FMT(name, a, r, g, b, e0, e1, e2, e3, alpha, tight, c, cnt, fp, cs, yuv) अणु \
		.base = अणु .pixel_क्रमmat = DRM_FORMAT_ ## name पूर्ण, \
		.bpc_a = BPC ## a ## A,                          \
		.bpc_r = BPC ## r,                               \
		.bpc_g = BPC ## g,                               \
		.bpc_b = BPC ## b,                               \
		.unpack = अणु e0, e1, e2, e3 पूर्ण,                    \
		.alpha_enable = alpha,                           \
		.unpack_tight = tight,                           \
		.cpp = c,                                        \
		.unpack_count = cnt,                             \
		.fetch_type = fp,                                \
		.chroma_sample = cs,                             \
		.is_yuv = yuv,                                   \
पूर्ण

#घोषणा BPC0A 0

/*
 * Note: Keep RGB क्रमmats 1st, followed by YUV क्रमmats to aव्योम अवरोधing
 * mdp_get_rgb_क्रमmats()'s implementation.
 */
अटल स्थिर काष्ठा mdp_क्रमmat क्रमmats[] = अणु
	/*  name      a  r  g  b   e0 e1 e2 e3  alpha   tight  cpp cnt ... */
	FMT(ARGB8888, 8, 8, 8, 8,  1, 0, 2, 3,  true,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(ABGR8888, 8, 8, 8, 8,  2, 0, 1, 3,  true,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(RGBA8888, 8, 8, 8, 8,  3, 1, 0, 2,  true,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(BGRA8888, 8, 8, 8, 8,  3, 2, 0, 1,  true,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(XRGB8888, 8, 8, 8, 8,  1, 0, 2, 3,  false,  true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(XBGR8888, 8, 8, 8, 8,  2, 0, 1, 3,  false,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(RGBX8888, 8, 8, 8, 8,  3, 1, 0, 2,  false,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(BGRX8888, 8, 8, 8, 8,  3, 2, 0, 1,  false,   true,  4,  4,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(RGB888,   0, 8, 8, 8,  1, 0, 2, 0,  false,  true,  3,  3,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(BGR888,   0, 8, 8, 8,  2, 0, 1, 0,  false,  true,  3,  3,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(RGB565,   0, 5, 6, 5,  1, 0, 2, 0,  false,  true,  2,  3,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),
	FMT(BGR565,   0, 5, 6, 5,  2, 0, 1, 0,  false,  true,  2,  3,
			MDP_PLANE_INTERLEAVED, CHROMA_FULL, false),

	/* --- RGB क्रमmats above / YUV क्रमmats below this line --- */

	/* 2 plane YUV */
	FMT(NV12,     0, 8, 8, 8,  1, 2, 0, 0,  false,  true,  2, 2,
			MDP_PLANE_PSEUDO_PLANAR, CHROMA_420, true),
	FMT(NV21,     0, 8, 8, 8,  2, 1, 0, 0,  false,  true,  2, 2,
			MDP_PLANE_PSEUDO_PLANAR, CHROMA_420, true),
	FMT(NV16,     0, 8, 8, 8,  1, 2, 0, 0,  false,  true,  2, 2,
			MDP_PLANE_PSEUDO_PLANAR, CHROMA_H2V1, true),
	FMT(NV61,     0, 8, 8, 8,  2, 1, 0, 0,  false,  true,  2, 2,
			MDP_PLANE_PSEUDO_PLANAR, CHROMA_H2V1, true),
	/* 1 plane YUV */
	FMT(VYUY,     0, 8, 8, 8,  2, 0, 1, 0,  false,  true,  2, 4,
			MDP_PLANE_INTERLEAVED, CHROMA_H2V1, true),
	FMT(UYVY,     0, 8, 8, 8,  1, 0, 2, 0,  false,  true,  2, 4,
			MDP_PLANE_INTERLEAVED, CHROMA_H2V1, true),
	FMT(YUYV,     0, 8, 8, 8,  0, 1, 0, 2,  false,  true,  2, 4,
			MDP_PLANE_INTERLEAVED, CHROMA_H2V1, true),
	FMT(YVYU,     0, 8, 8, 8,  0, 2, 0, 1,  false,  true,  2, 4,
			MDP_PLANE_INTERLEAVED, CHROMA_H2V1, true),
	/* 3 plane YUV */
	FMT(YUV420,   0, 8, 8, 8,  2, 1, 0, 0,  false,  true,  1, 1,
			MDP_PLANE_PLANAR, CHROMA_420, true),
	FMT(YVU420,   0, 8, 8, 8,  1, 2, 0, 0,  false,  true,  1, 1,
			MDP_PLANE_PLANAR, CHROMA_420, true),
पूर्ण;

/*
 * Note:
 * @rgb_only must be set to true, when requesting
 * supported क्रमmats क्रम RGB pipes.
 */
uपूर्णांक32_t mdp_get_क्रमmats(uपूर्णांक32_t *pixel_क्रमmats, uपूर्णांक32_t max_क्रमmats,
		bool rgb_only)
अणु
	uपूर्णांक32_t i;
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		स्थिर काष्ठा mdp_क्रमmat *f = &क्रमmats[i];

		अगर (i == max_क्रमmats)
			अवरोध;

		अगर (rgb_only && MDP_FORMAT_IS_YUV(f))
			अवरोध;

		pixel_क्रमmats[i] = f->base.pixel_क्रमmat;
	पूर्ण

	वापस i;
पूर्ण

स्थिर काष्ठा msm_क्रमmat *mdp_get_क्रमmat(काष्ठा msm_kms *kms, uपूर्णांक32_t क्रमmat,
		uपूर्णांक64_t modअगरier)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		स्थिर काष्ठा mdp_क्रमmat *f = &क्रमmats[i];
		अगर (f->base.pixel_क्रमmat == क्रमmat)
			वापस &f->base;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा csc_cfg *mdp_get_शेष_csc_cfg(क्रमागत csc_type type)
अणु
	अगर (WARN_ON(type >= CSC_MAX))
		वापस शून्य;

	वापस &csc_convert[type];
पूर्ण
