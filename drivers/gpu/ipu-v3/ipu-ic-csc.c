<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Mentor Graphics Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/sizes.h>
#समावेश "ipu-prv.h"

#घोषणा QUANT_MAP(q)					\
	((q) == V4L2_QUANTIZATION_FULL_RANGE ||		\
	 (q) == V4L2_QUANTIZATION_DEFAULT ? 0 : 1)

/* identity matrix */
अटल स्थिर काष्ठा ipu_ic_csc_params identity = अणु
	.coeff = अणु
		अणु  128,    0,    0, पूर्ण,
		अणु    0,  128,    0, पूर्ण,
		अणु    0,    0,  128, पूर्ण,
	पूर्ण,
	.offset = अणु 0, 0, 0, पूर्ण,
	.scale = 2,
पूर्ण;

/*
 * RGB full-range to RGB limited-range
 *
 * R_lim = 0.8588 * R_full + 16
 * G_lim = 0.8588 * G_full + 16
 * B_lim = 0.8588 * B_full + 16
 */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbf2rgbl = अणु
	.coeff = अणु
		अणु  220,    0,    0, पूर्ण,
		अणु    0,  220,    0, पूर्ण,
		अणु    0,    0,  220, पूर्ण,
	पूर्ण,
	.offset = अणु 64, 64, 64, पूर्ण,
	.scale = 1,
पूर्ण;

/*
 * RGB limited-range to RGB full-range
 *
 * R_full = 1.1644 * (R_lim - 16)
 * G_full = 1.1644 * (G_lim - 16)
 * B_full = 1.1644 * (B_lim - 16)
 */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbl2rgbf = अणु
	.coeff = अणु
		अणु  149,    0,    0, पूर्ण,
		अणु    0,  149,    0, पूर्ण,
		अणु    0,    0,  149, पूर्ण,
	पूर्ण,
	.offset = अणु -37, -37, -37, पूर्ण,
	.scale = 2,
पूर्ण;

/*
 * YUV full-range to YUV limited-range
 *
 * Y_lim  = 0.8588 * Y_full + 16
 * Cb_lim = 0.8784 * (Cb_full - 128) + 128
 * Cr_lim = 0.8784 * (Cr_full - 128) + 128
 */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvf2yuvl = अणु
	.coeff = अणु
		अणु  220,    0,    0, पूर्ण,
		अणु    0,  225,    0, पूर्ण,
		अणु    0,    0,  225, पूर्ण,
	पूर्ण,
	.offset = अणु 64, 62, 62, पूर्ण,
	.scale = 1,
	.sat = true,
पूर्ण;

/*
 * YUV limited-range to YUV full-range
 *
 * Y_full  = 1.1644 * (Y_lim - 16)
 * Cb_full = 1.1384 * (Cb_lim - 128) + 128
 * Cr_full = 1.1384 * (Cr_lim - 128) + 128
 */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvl2yuvf = अणु
	.coeff = अणु
		अणु  149,    0,    0, पूर्ण,
		अणु    0,  146,    0, पूर्ण,
		अणु    0,    0,  146, पूर्ण,
	पूर्ण,
	.offset = अणु -37, -35, -35, पूर्ण,
	.scale = 2,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *rgb2rgb[] = अणु
	&identity,
	&rgbf2rgbl,
	&rgbl2rgbf,
	&identity,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *yuv2yuv[] = अणु
	&identity,
	&yuvf2yuvl,
	&yuvl2yuvf,
	&identity,
पूर्ण;

/*
 * BT.601 RGB full-range to YUV full-range
 *
 * Y =  .2990 * R + .5870 * G + .1140 * B
 * U = -.1687 * R - .3313 * G + .5000 * B + 128
 * V =  .5000 * R - .4187 * G - .0813 * B + 128
 */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbf2yuvf_601 = अणु
	.coeff = अणु
		अणु   77,  150,   29, पूर्ण,
		अणु  -43,  -85,  128, पूर्ण,
		अणु  128, -107,  -21, पूर्ण,
	पूर्ण,
	.offset = अणु 0, 512, 512, पूर्ण,
	.scale = 1,
पूर्ण;

/* BT.601 RGB full-range to YUV limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbf2yuvl_601 = अणु
	.coeff = अणु
		अणु   66,  129,   25, पूर्ण,
		अणु  -38,  -74,  112, पूर्ण,
		अणु  112,  -94,  -18, पूर्ण,
	पूर्ण,
	.offset = अणु 64, 512, 512, पूर्ण,
	.scale = 1,
	.sat = true,
पूर्ण;

/* BT.601 RGB limited-range to YUV full-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbl2yuvf_601 = अणु
	.coeff = अणु
		अणु   89,  175,   34, पूर्ण,
		अणु  -50,  -99,  149, पूर्ण,
		अणु  149, -125,  -24, पूर्ण,
	पूर्ण,
	.offset = अणु -75, 512, 512, पूर्ण,
	.scale = 1,
पूर्ण;

/* BT.601 RGB limited-range to YUV limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbl2yuvl_601 = अणु
	.coeff = अणु
		अणु   77,  150,   29, पूर्ण,
		अणु  -44,  -87,  131, पूर्ण,
		अणु  131, -110,  -21, पूर्ण,
	पूर्ण,
	.offset = अणु 0, 512, 512, पूर्ण,
	.scale = 1,
	.sat = true,
पूर्ण;

/*
 * BT.601 YUV full-range to RGB full-range
 *
 * R = 1. * Y +      0 * (Cb - 128) + 1.4020 * (Cr - 128)
 * G = 1. * Y -  .3441 * (Cb - 128) -  .7141 * (Cr - 128)
 * B = 1. * Y + 1.7720 * (Cb - 128) +      0 * (Cr - 128)
 *
 * equivalently (factoring out the offsets):
 *
 * R = 1. * Y  +      0 * Cb + 1.4020 * Cr - 179.456
 * G = 1. * Y  -  .3441 * Cb -  .7141 * Cr + 135.450
 * B = 1. * Y  + 1.7720 * Cb +      0 * Cr - 226.816
 */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvf2rgbf_601 = अणु
	.coeff = अणु
		अणु  128,    0,  179, पूर्ण,
		अणु  128,  -44,  -91, पूर्ण,
		अणु  128,  227,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -359, 271, -454, पूर्ण,
	.scale = 2,
पूर्ण;

/* BT.601 YUV full-range to RGB limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvf2rgbl_601 = अणु
	.coeff = अणु
		अणु  110,    0,  154, पूर्ण,
		अणु  110,  -38,  -78, पूर्ण,
		अणु  110,  195,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -276, 265, -358, पूर्ण,
	.scale = 2,
पूर्ण;

/* BT.601 YUV limited-range to RGB full-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvl2rgbf_601 = अणु
	.coeff = अणु
		अणु   75,    0,  102, पूर्ण,
		अणु   75,  -25,  -52, पूर्ण,
		अणु   75,  129,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -223, 136, -277, पूर्ण,
	.scale = 3,
पूर्ण;

/* BT.601 YUV limited-range to RGB limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvl2rgbl_601 = अणु
	.coeff = अणु
		अणु  128,    0,  175, पूर्ण,
		अणु  128,  -43,  -89, पूर्ण,
		अणु  128,  222,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -351, 265, -443, पूर्ण,
	.scale = 2,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *rgb2yuv_601[] = अणु
	&rgbf2yuvf_601,
	&rgbf2yuvl_601,
	&rgbl2yuvf_601,
	&rgbl2yuvl_601,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *yuv2rgb_601[] = अणु
	&yuvf2rgbf_601,
	&yuvf2rgbl_601,
	&yuvl2rgbf_601,
	&yuvl2rgbl_601,
पूर्ण;

/*
 * REC.709 encoding from RGB full range to YUV full range:
 *
 * Y =  .2126 * R + .7152 * G + .0722 * B
 * U = -.1146 * R - .3854 * G + .5000 * B + 128
 * V =  .5000 * R - .4542 * G - .0458 * B + 128
 */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbf2yuvf_709 = अणु
	.coeff = अणु
		अणु  54,  183,  19 पूर्ण,
		अणु -29,  -99, 128 पूर्ण,
		अणु 128, -116, -12 पूर्ण,
	पूर्ण,
	.offset = अणु 0, 512, 512 पूर्ण,
	.scale = 1,
पूर्ण;

/* Rec.709 RGB full-range to YUV limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbf2yuvl_709 = अणु
	.coeff = अणु
		अणु   47,  157,   16, पूर्ण,
		अणु  -26,  -87,  112, पूर्ण,
		अणु  112, -102,  -10, पूर्ण,
	पूर्ण,
	.offset = अणु 64, 512, 512, पूर्ण,
	.scale = 1,
	.sat = true,
पूर्ण;

/* Rec.709 RGB limited-range to YUV full-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbl2yuvf_709 = अणु
	.coeff = अणु
		अणु   63,  213,   22, पूर्ण,
		अणु  -34, -115,  149, पूर्ण,
		अणु  149, -135,  -14, पूर्ण,
	पूर्ण,
	.offset = अणु -75, 512, 512, पूर्ण,
	.scale = 1,
पूर्ण;

/* Rec.709 RGB limited-range to YUV limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params rgbl2yuvl_709 = अणु
	.coeff = अणु
		अणु   54,  183,   18, पूर्ण,
		अणु  -30, -101,  131, पूर्ण,
		अणु  131, -119,  -12, पूर्ण,
	पूर्ण,
	.offset = अणु 0, 512, 512, पूर्ण,
	.scale = 1,
	.sat = true,
पूर्ण;

/*
 * Inverse REC.709 encoding from YUV full range to RGB full range:
 *
 * R = 1. * Y +      0 * (Cb - 128) + 1.5748 * (Cr - 128)
 * G = 1. * Y -  .1873 * (Cb - 128) -  .4681 * (Cr - 128)
 * B = 1. * Y + 1.8556 * (Cb - 128) +      0 * (Cr - 128)
 *
 * equivalently (factoring out the offsets):
 *
 * R = 1. * Y  +      0 * Cb + 1.5748 * Cr - 201.574
 * G = 1. * Y  -  .1873 * Cb -  .4681 * Cr +  83.891
 * B = 1. * Y  + 1.8556 * Cb +      0 * Cr - 237.517
 */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvf2rgbf_709 = अणु
	.coeff = अणु
		अणु  128,   0, 202 पूर्ण,
		अणु  128, -24, -60 पूर्ण,
		अणु  128, 238,   0 पूर्ण,
	पूर्ण,
	.offset = अणु -403, 168, -475 पूर्ण,
	.scale = 2,
पूर्ण;

/* Rec.709 YUV full-range to RGB limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvf2rgbl_709 = अणु
	.coeff = अणु
		अणु  110,    0,  173, पूर्ण,
		अणु  110,  -21,  -51, पूर्ण,
		अणु  110,  204,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -314, 176, -376, पूर्ण,
	.scale = 2,
पूर्ण;

/* Rec.709 YUV limited-range to RGB full-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvl2rgbf_709 = अणु
	.coeff = अणु
		अणु   75,    0,  115, पूर्ण,
		अणु   75,  -14,  -34, पूर्ण,
		अणु   75,  135,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -248, 77, -289, पूर्ण,
	.scale = 3,
पूर्ण;

/* Rec.709 YUV limited-range to RGB limited-range */
अटल स्थिर काष्ठा ipu_ic_csc_params yuvl2rgbl_709 = अणु
	.coeff = अणु
		अणु  128,    0,  197, पूर्ण,
		अणु  128,  -23,  -59, पूर्ण,
		अणु  128,  232,    0, पूर्ण,
	पूर्ण,
	.offset = अणु -394, 164, -464, पूर्ण,
	.scale = 2,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *rgb2yuv_709[] = अणु
	&rgbf2yuvf_709,
	&rgbf2yuvl_709,
	&rgbl2yuvf_709,
	&rgbl2yuvl_709,
पूर्ण;

अटल स्थिर काष्ठा ipu_ic_csc_params *yuv2rgb_709[] = अणु
	&yuvf2rgbf_709,
	&yuvf2rgbl_709,
	&yuvl2rgbf_709,
	&yuvl2rgbl_709,
पूर्ण;

अटल पूर्णांक calc_csc_coeffs(काष्ठा ipu_ic_csc *csc)
अणु
	स्थिर काष्ठा ipu_ic_csc_params **params_tbl;
	पूर्णांक tbl_idx;

	tbl_idx = (QUANT_MAP(csc->in_cs.quant) << 1) |
		QUANT_MAP(csc->out_cs.quant);

	अगर (csc->in_cs.cs == csc->out_cs.cs) अणु
		csc->params = (csc->in_cs.cs == IPUV3_COLORSPACE_YUV) ?
			*yuv2yuv[tbl_idx] : *rgb2rgb[tbl_idx];

		वापस 0;
	पूर्ण

	/* YUV <-> RGB encoding is required */

	चयन (csc->out_cs.enc) अणु
	हाल V4L2_YCBCR_ENC_601:
		params_tbl = (csc->in_cs.cs == IPUV3_COLORSPACE_YUV) ?
			yuv2rgb_601 : rgb2yuv_601;
		अवरोध;
	हाल V4L2_YCBCR_ENC_709:
		params_tbl = (csc->in_cs.cs == IPUV3_COLORSPACE_YUV) ?
			yuv2rgb_709 : rgb2yuv_709;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	csc->params = *params_tbl[tbl_idx];

	वापस 0;
पूर्ण

पूर्णांक __ipu_ic_calc_csc(काष्ठा ipu_ic_csc *csc)
अणु
	वापस calc_csc_coeffs(csc);
पूर्ण
EXPORT_SYMBOL_GPL(__ipu_ic_calc_csc);

पूर्णांक ipu_ic_calc_csc(काष्ठा ipu_ic_csc *csc,
		    क्रमागत v4l2_ycbcr_encoding in_enc,
		    क्रमागत v4l2_quantization in_quant,
		    क्रमागत ipu_color_space in_cs,
		    क्रमागत v4l2_ycbcr_encoding out_enc,
		    क्रमागत v4l2_quantization out_quant,
		    क्रमागत ipu_color_space out_cs)
अणु
	ipu_ic_fill_colorspace(&csc->in_cs, in_enc, in_quant, in_cs);
	ipu_ic_fill_colorspace(&csc->out_cs, out_enc, out_quant, out_cs);

	वापस __ipu_ic_calc_csc(csc);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_calc_csc);
