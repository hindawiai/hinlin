<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Color space converter library
 *
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>

#समावेश "csc.h"

/*
 * 12 coefficients in the order:
 * a0, b0, c0, a1, b1, c1, a2, b2, c2, d0, d1, d2
 */
काष्ठा quantization अणु
	u16	coeff[12];
पूर्ण;

काष्ठा colorspace अणु
	काष्ठा quantization limited;
	काष्ठा quantization full;
पूर्ण;

काष्ठा encoding_direction अणु
	काष्ठा colorspace r601;
	काष्ठा colorspace r709;
पूर्ण;

काष्ठा csc_coeffs अणु
	काष्ठा encoding_direction y2r;
	काष्ठा encoding_direction r2y;
पूर्ण;

/* शेष colorspace coefficients */
अटल काष्ठा csc_coeffs csc_coeffs = अणु
	.y2r = अणु
		.r601 = अणु
			.limited = अणु
				अणु	/* SDTV */
				0x0400, 0x0000, 0x057D, 0x0400, 0x1EA7, 0x1D35,
				0x0400, 0x06EF, 0x1FFE, 0x0D40, 0x0210, 0x0C88,
				पूर्ण
			पूर्ण,
			.full = अणु
				अणु	/* SDTV */
				0x04A8, 0x1FFE, 0x0662, 0x04A8, 0x1E6F, 0x1CBF,
				0x04A8, 0x0812, 0x1FFF, 0x0C84, 0x0220, 0x0BAC,
				पूर्ण
			पूर्ण,
		पूर्ण,
		.r709 = अणु
			.limited = अणु
				अणु	/* HDTV */
				0x0400, 0x0000, 0x0629, 0x0400, 0x1F45, 0x1E2B,
				0x0400, 0x0742, 0x0000, 0x0CEC, 0x0148, 0x0C60,
				पूर्ण
			पूर्ण,
			.full = अणु
				अणु	/* HDTV */
				0x04A8, 0x0000, 0x072C, 0x04A8, 0x1F26, 0x1DDE,
				0x04A8, 0x0873, 0x0000, 0x0C20, 0x0134, 0x0B7C,
				पूर्ण
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.r2y = अणु
		.r601 = अणु
			.limited = अणु
				अणु	/* SDTV */
				0x0132, 0x0259, 0x0075, 0x1F50, 0x1EA5, 0x020B,
				0x020B, 0x1E4A, 0x1FAB, 0x0000, 0x0200, 0x0200,
				पूर्ण
			पूर्ण,
			.full = अणु
				अणु	/* SDTV */
				0x0107, 0x0204, 0x0064, 0x1F68, 0x1ED6, 0x01C2,
				0x01C2, 0x1E87, 0x1FB7, 0x0040, 0x0200, 0x0200,
				पूर्ण
			पूर्ण,
		पूर्ण,
		.r709 = अणु
			.limited = अणु
				अणु	/* HDTV */
				0x00DA, 0x02DC, 0x004A, 0x1F88, 0x1E6C, 0x020C,
				0x020C, 0x1E24, 0x1FD0, 0x0000, 0x0200, 0x0200,
				पूर्ण
			पूर्ण,
			.full = अणु
				अणु	/* HDTV */
				0x00bb, 0x0275, 0x003f, 0x1f99, 0x1ea5, 0x01c2,
				0x01c2, 0x1e67, 0x1fd7, 0x0040, 0x0200, 0x0200,
				पूर्ण
			पूर्ण,
		पूर्ण,
	पूर्ण,

पूर्ण;

व्योम csc_dump_regs(काष्ठा csc_data *csc)
अणु
	काष्ठा device *dev = &csc->pdev->dev;

#घोषणा DUMPREG(r) dev_dbg(dev, "%-35s %08x\n", #r, \
	ioपढ़ो32(csc->base + CSC_##r))

	dev_dbg(dev, "CSC Registers @ %pa:\n", &csc->res->start);

	DUMPREG(CSC00);
	DUMPREG(CSC01);
	DUMPREG(CSC02);
	DUMPREG(CSC03);
	DUMPREG(CSC04);
	DUMPREG(CSC05);

#अघोषित DUMPREG
पूर्ण
EXPORT_SYMBOL(csc_dump_regs);

व्योम csc_set_coeff_bypass(काष्ठा csc_data *csc, u32 *csc_reg5)
अणु
	*csc_reg5 |= CSC_BYPASS;
पूर्ण
EXPORT_SYMBOL(csc_set_coeff_bypass);

/*
 * set the color space converter coefficient shaकरोw रेजिस्टर values
 */
व्योम csc_set_coeff(काष्ठा csc_data *csc, u32 *csc_reg0,
		   काष्ठा v4l2_क्रमmat *src_fmt, काष्ठा v4l2_क्रमmat *dst_fmt)
अणु
	u32 *csc_reg5 = csc_reg0 + 5;
	u32 *shaकरोw_csc = csc_reg0;
	u16 *coeff, *end_coeff;
	स्थिर काष्ठा v4l2_pix_क्रमmat *pix;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *mp;
	स्थिर काष्ठा v4l2_क्रमmat_info *src_finfo, *dst_finfo;
	क्रमागत v4l2_ycbcr_encoding src_ycbcr_enc, dst_ycbcr_enc;
	क्रमागत v4l2_quantization src_quantization, dst_quantization;
	u32 src_pixelक्रमmat, dst_pixelक्रमmat;

	अगर (V4L2_TYPE_IS_MULTIPLANAR(src_fmt->type)) अणु
		mp = &src_fmt->fmt.pix_mp;
		src_pixelक्रमmat = mp->pixelक्रमmat;
		src_ycbcr_enc = mp->ycbcr_enc;
		src_quantization = mp->quantization;
	पूर्ण अन्यथा अणु
		pix = &src_fmt->fmt.pix;
		src_pixelक्रमmat = pix->pixelक्रमmat;
		src_ycbcr_enc = pix->ycbcr_enc;
		src_quantization = pix->quantization;
	पूर्ण

	अगर (V4L2_TYPE_IS_MULTIPLANAR(dst_fmt->type)) अणु
		mp = &dst_fmt->fmt.pix_mp;
		dst_pixelक्रमmat = mp->pixelक्रमmat;
		dst_ycbcr_enc = mp->ycbcr_enc;
		dst_quantization = mp->quantization;
	पूर्ण अन्यथा अणु
		pix = &dst_fmt->fmt.pix;
		dst_pixelक्रमmat = pix->pixelक्रमmat;
		dst_ycbcr_enc = pix->ycbcr_enc;
		dst_quantization = pix->quantization;
	पूर्ण

	src_finfo = v4l2_क्रमmat_info(src_pixelक्रमmat);
	dst_finfo = v4l2_क्रमmat_info(dst_pixelक्रमmat);

	अगर (v4l2_is_क्रमmat_yuv(src_finfo) &&
	    v4l2_is_क्रमmat_rgb(dst_finfo)) अणु
		/* Y2R */

		/*
		 * These are not the standard शेष values but are
		 * set this way क्रम historical compatibility
		 */
		अगर (src_ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
			src_ycbcr_enc = V4L2_YCBCR_ENC_601;

		अगर (src_quantization == V4L2_QUANTIZATION_DEFAULT)
			src_quantization = V4L2_QUANTIZATION_FULL_RANGE;

		अगर (src_ycbcr_enc == V4L2_YCBCR_ENC_601) अणु
			अगर (src_quantization == V4L2_QUANTIZATION_FULL_RANGE)
				coeff = csc_coeffs.y2r.r601.full.coeff;
			अन्यथा
				coeff = csc_coeffs.y2r.r601.limited.coeff;
		पूर्ण अन्यथा अगर (src_ycbcr_enc == V4L2_YCBCR_ENC_709) अणु
			अगर (src_quantization == V4L2_QUANTIZATION_FULL_RANGE)
				coeff = csc_coeffs.y2r.r709.full.coeff;
			अन्यथा
				coeff = csc_coeffs.y2r.r709.limited.coeff;
		पूर्ण अन्यथा अणु
			/* Should never reach this, but it keeps gcc happy */
			coeff = csc_coeffs.y2r.r601.full.coeff;
		पूर्ण
	पूर्ण अन्यथा अगर (v4l2_is_क्रमmat_rgb(src_finfo) &&
		   v4l2_is_क्रमmat_yuv(dst_finfo)) अणु
		/* R2Y */

		/*
		 * These are not the standard शेष values but are
		 * set this way क्रम historical compatibility
		 */
		अगर (dst_ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
			dst_ycbcr_enc = V4L2_YCBCR_ENC_601;

		अगर (dst_quantization == V4L2_QUANTIZATION_DEFAULT)
			dst_quantization = V4L2_QUANTIZATION_FULL_RANGE;

		अगर (dst_ycbcr_enc == V4L2_YCBCR_ENC_601) अणु
			अगर (dst_quantization == V4L2_QUANTIZATION_FULL_RANGE)
				coeff = csc_coeffs.r2y.r601.full.coeff;
			अन्यथा
				coeff = csc_coeffs.r2y.r601.limited.coeff;
		पूर्ण अन्यथा अगर (dst_ycbcr_enc == V4L2_YCBCR_ENC_709) अणु
			अगर (dst_quantization == V4L2_QUANTIZATION_FULL_RANGE)
				coeff = csc_coeffs.r2y.r709.full.coeff;
			अन्यथा
				coeff = csc_coeffs.r2y.r709.limited.coeff;
		पूर्ण अन्यथा अणु
			/* Should never reach this, but it keeps gcc happy */
			coeff = csc_coeffs.r2y.r601.full.coeff;
		पूर्ण
	पूर्ण अन्यथा अणु
		*csc_reg5 |= CSC_BYPASS;
		वापस;
	पूर्ण

	end_coeff = coeff + 12;

	क्रम (; coeff < end_coeff; coeff += 2)
		*shaकरोw_csc++ = (*(coeff + 1) << 16) | *coeff;
पूर्ण
EXPORT_SYMBOL(csc_set_coeff);

काष्ठा csc_data *csc_create(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *res_name)
अणु
	काष्ठा csc_data *csc;

	dev_dbg(&pdev->dev, "csc_create\n");

	csc = devm_kzalloc(&pdev->dev, माप(*csc), GFP_KERNEL);
	अगर (!csc) अणु
		dev_err(&pdev->dev, "couldn't alloc csc_data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	csc->pdev = pdev;

	csc->res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						res_name);
	अगर (csc->res == शून्य) अणु
		dev_err(&pdev->dev, "missing '%s' platform resources data\n",
			res_name);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	csc->base = devm_ioremap_resource(&pdev->dev, csc->res);
	अगर (IS_ERR(csc->base))
		वापस ERR_CAST(csc->base);

	वापस csc;
पूर्ण
EXPORT_SYMBOL(csc_create);

MODULE_DESCRIPTION("TI VIP/VPE Color Space Converter");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_LICENSE("GPL v2");
