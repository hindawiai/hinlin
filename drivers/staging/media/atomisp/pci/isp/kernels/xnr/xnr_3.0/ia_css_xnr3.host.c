<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "type_support.h"
#समावेश "math_support.h"
#समावेश "sh_css_defs.h"
#समावेश "ia_css_types.h"
#समावेश "assert_support.h"
#समावेश "ia_css_xnr3.host.h"

/* Maximum value क्रम alpha on ISP पूर्णांकerface */
#घोषणा XNR_MAX_ALPHA  ((1 << (ISP_VEC_ELEMBITS - 1)) - 1)

/* Minimum value क्रम sigma on host पूर्णांकerface. Lower values translate to
 * max_alpha.
 */
#घोषणा XNR_MIN_SIGMA  (IA_CSS_XNR3_SIGMA_SCALE / 100)

/*
 * भागision look-up table
 * Refers to XNR3.0.5
 */
#घोषणा XNR3_LOOK_UP_TABLE_POINTS 16

अटल स्थिर s16 x[XNR3_LOOK_UP_TABLE_POINTS] = अणु
	1024, 1164, 1320, 1492, 1680, 1884, 2108, 2352,
	2616, 2900, 3208, 3540, 3896, 4276, 4684, 5120
पूर्ण;

अटल स्थिर s16 a[XNR3_LOOK_UP_TABLE_POINTS] = अणु
	-7213, -5580, -4371, -3421, -2722, -2159, -6950, -5585,
	    -4529, -3697, -3010, -2485, -2070, -1727, -1428, 0
    पूर्ण;

अटल स्थिर s16 b[XNR3_LOOK_UP_TABLE_POINTS] = अणु
	4096, 3603, 3178, 2811, 2497, 2226, 1990, 1783,
	1603, 1446, 1307, 1185, 1077, 981, 895, 819
पूर्ण;

अटल स्थिर s16 c[XNR3_LOOK_UP_TABLE_POINTS] = अणु
	1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

/*
 * Default kernel parameters. In general, शेष is bypass mode or as बंद
 * to the ineffective values as possible. Due to the chroma करोwn+upsampling,
 * perfect bypass mode is not possible क्रम xnr3 filter itself. Instead, the
 * 'blending' parameter is used to create a bypass.
 */
स्थिर काष्ठा ia_css_xnr3_config शेष_xnr3_config = अणु
	/* sigma */
	अणु 0, 0, 0, 0, 0, 0 पूर्ण,
	/* coring */
	अणु 0, 0, 0, 0 पूर्ण,
	/* blending */
	अणु 0 पूर्ण
पूर्ण;

/*
 * Compute an alpha value क्रम the ISP kernel from sigma value on the host
 * parameter पूर्णांकerface as: alpha_scale * 1/(sigma/sigma_scale)
 */
अटल पूर्णांक32_t
compute_alpha(पूर्णांक sigma)
अणु
	s32 alpha;
	पूर्णांक offset = sigma / 2;

	अगर (sigma < XNR_MIN_SIGMA) अणु
		alpha = XNR_MAX_ALPHA;
	पूर्ण अन्यथा अणु
		alpha = ((IA_CSS_XNR3_SIGMA_SCALE * XNR_ALPHA_SCALE_FACTOR) + offset) / sigma;

		अगर (alpha > XNR_MAX_ALPHA)
			alpha = XNR_MAX_ALPHA;
	पूर्ण

	वापस alpha;
पूर्ण

/*
 * Compute the scaled coring value क्रम the ISP kernel from the value on the
 * host parameter पूर्णांकerface.
 */
अटल पूर्णांक32_t
compute_coring(पूर्णांक coring)
अणु
	s32 isp_coring;
	s32 isp_scale = XNR_CORING_SCALE_FACTOR;
	s32 host_scale = IA_CSS_XNR3_CORING_SCALE;
	s32 offset = host_scale / 2; /* fixed-poपूर्णांक 0.5 */

	/* Convert from खुला host-side scale factor to isp-side scale
	 * factor. Clip to [0, isp_scale-1).
	 */
	isp_coring = ((coring * isp_scale) + offset) / host_scale;
	वापस min(max(isp_coring, 0), isp_scale - 1);
पूर्ण

/*
 * Compute the scaled blending strength क्रम the ISP kernel from the value on
 * the host parameter पूर्णांकerface.
 */
अटल पूर्णांक32_t
compute_blending(पूर्णांक strength)
अणु
	s32 isp_strength;
	s32 isp_scale = XNR_BLENDING_SCALE_FACTOR;
	s32 host_scale = IA_CSS_XNR3_BLENDING_SCALE;
	s32 offset = host_scale / 2; /* fixed-poपूर्णांक 0.5 */

	/* Convert from खुला host-side scale factor to isp-side scale
	 * factor. The blending factor is positive on the host side, but
	 * negative on the ISP side because +1.0 cannot be represented
	 * exactly as s0.11 fixed poपूर्णांक, but -1.0 can.
	 */
	isp_strength = -(((strength * isp_scale) + offset) / host_scale);
	वापस MAX(MIN(isp_strength, 0), -isp_scale);
पूर्ण

व्योम
ia_css_xnr3_encode(
    काष्ठा sh_css_isp_xnr3_params *to,
    स्थिर काष्ठा ia_css_xnr3_config *from,
    अचिन्हित पूर्णांक size)
अणु
	पूर्णांक kernel_size = XNR_FILTER_SIZE;
	/* The adjust factor is the next घातer of 2
	   w.r.t. the kernel size*/
	पूर्णांक adjust_factor = उच्चमान_घात2(kernel_size);
	s32 max_dअगरf = (1 << (ISP_VEC_ELEMBITS - 1)) - 1;
	s32 min_dअगरf = -(1 << (ISP_VEC_ELEMBITS - 1));

	s32 alpha_y0 = compute_alpha(from->sigma.y0);
	s32 alpha_y1 = compute_alpha(from->sigma.y1);
	s32 alpha_u0 = compute_alpha(from->sigma.u0);
	s32 alpha_u1 = compute_alpha(from->sigma.u1);
	s32 alpha_v0 = compute_alpha(from->sigma.v0);
	s32 alpha_v1 = compute_alpha(from->sigma.v1);
	s32 alpha_ydअगरf = (alpha_y1 - alpha_y0) * adjust_factor / kernel_size;
	s32 alpha_udअगरf = (alpha_u1 - alpha_u0) * adjust_factor / kernel_size;
	s32 alpha_vdअगरf = (alpha_v1 - alpha_v0) * adjust_factor / kernel_size;

	s32 coring_u0 = compute_coring(from->coring.u0);
	s32 coring_u1 = compute_coring(from->coring.u1);
	s32 coring_v0 = compute_coring(from->coring.v0);
	s32 coring_v1 = compute_coring(from->coring.v1);
	s32 coring_udअगरf = (coring_u1 - coring_u0) * adjust_factor / kernel_size;
	s32 coring_vdअगरf = (coring_v1 - coring_v0) * adjust_factor / kernel_size;

	s32 blending = compute_blending(from->blending.strength);

	(व्योम)size;

	/* alpha's are represented in qN.5 क्रमmat */
	to->alpha.y0 = alpha_y0;
	to->alpha.u0 = alpha_u0;
	to->alpha.v0 = alpha_v0;
	to->alpha.ydअगरf = min(max(alpha_ydअगरf, min_dअगरf), max_dअगरf);
	to->alpha.udअगरf = min(max(alpha_udअगरf, min_dअगरf), max_dअगरf);
	to->alpha.vdअगरf = min(max(alpha_vdअगरf, min_dअगरf), max_dअगरf);

	/* coring parameters are expressed in q1.NN क्रमmat */
	to->coring.u0 = coring_u0;
	to->coring.v0 = coring_v0;
	to->coring.udअगरf = min(max(coring_udअगरf, min_dअगरf), max_dअगरf);
	to->coring.vdअगरf = min(max(coring_vdअगरf, min_dअगरf), max_dअगरf);

	/* blending strength is expressed in q1.NN क्रमmat */
	to->blending.strength = blending;
पूर्ण

/* ISP2401 */
/* (व्योम) = ia_css_xnr3_vmem_encode(*to, *from)
 * -----------------------------------------------
 * VMEM Encode Function to translate UV parameters from userspace पूर्णांकo ISP space
*/
व्योम
ia_css_xnr3_vmem_encode(
    काष्ठा sh_css_isp_xnr3_vmem_params *to,
    स्थिर काष्ठा ia_css_xnr3_config *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i, j, base;
	स्थिर अचिन्हित पूर्णांक total_blocks = 4;
	स्थिर अचिन्हित पूर्णांक shuffle_block = 16;

	(व्योम)from;
	(व्योम)size;

	/* Init */
	क्रम (i = 0; i < ISP_VEC_NELEMS; i++) अणु
		to->x[0][i] = 0;
		to->a[0][i] = 0;
		to->b[0][i] = 0;
		to->c[0][i] = 0;
	पूर्ण

	/* Constraपूर्णांकs on "x":
	 * - values should be greater or equal to 0.
	 * - values should be ascending.
	 */
	निश्चित(x[0] >= 0);

	क्रम (j = 1; j < XNR3_LOOK_UP_TABLE_POINTS; j++) अणु
		निश्चित(x[j] >= 0);
		निश्चित(x[j] > x[j - 1]);
	पूर्ण

	/* The implementation of the calulating 1/x is based on the availability
	 * of the OP_vec_shuffle16 operation.
	 * A 64 element vector is split up in 4 blocks of 16 element. Each array is copied to
	 * a vector 4 बार, (starting at 0, 16, 32 and 48). All array elements are copied or
	 * initialised as described in the KFS. The reमुख्यing elements of a vector are set to 0.
	 */
	/* TODO: guard this code with above assumptions */
	क्रम (i = 0; i < total_blocks; i++) अणु
		base = shuffle_block * i;

		क्रम (j = 0; j < XNR3_LOOK_UP_TABLE_POINTS; j++) अणु
			to->x[0][base + j] = x[j];
			to->a[0][base + j] = a[j];
			to->b[0][base + j] = b[j];
			to->c[0][base + j] = c[j];
		पूर्ण
	पूर्ण
पूर्ण

/* Dummy Function added as the tool expects it*/
व्योम
ia_css_xnr3_debug_dtrace(
    स्थिर काष्ठा ia_css_xnr3_config *config,
    अचिन्हित पूर्णांक level)
अणु
	(व्योम)config;
	(व्योम)level;
पूर्ण
