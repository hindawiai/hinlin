<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Media Controller Driver क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#समावेश <linux/module.h>
#समावेश "imx-media.h"

#घोषणा IMX_BUS_FMTS(fmt...) (स्थिर u32[]) अणुfmt, 0पूर्ण

/*
 * List of supported pixel क्रमmats क्रम the subdevs.
 */
अटल स्थिर काष्ठा imx_media_pixfmt pixel_क्रमmats[] = अणु
	/*** YUV क्रमmats start here ***/
	अणु
		.fourcc	= V4L2_PIX_FMT_UYVY,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_UYVY8_2X8,
			MEDIA_BUS_FMT_UYVY8_1X16
		),
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 16,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_YUYV8_2X8,
			MEDIA_BUS_FMT_YUYV8_1X16
		),
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 16,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YUV420,
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 12,
		.planar = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU420,
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 12,
		.planar = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 16,
		.planar = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 12,
		.planar = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 16,
		.planar = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_AYUV8_1X32),
		.cs     = IPUV3_COLORSPACE_YUV,
		.bpp    = 32,
		.ipufmt = true,
	पूर्ण,
	/*** RGB क्रमmats start here ***/
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB565,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_RGB565_2X8_LE),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.cycles = 2,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB24,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_RGB888_1X24,
			MEDIA_BUS_FMT_RGB888_2X12_LE
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 24,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGR24,
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 24,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_XRGB32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_ARGB8888_1X32),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_XRGB32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_ARGB8888_1X32),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 32,
		.ipufmt = true,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_XBGR32,
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGRX32,
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGBX32,
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 32,
	पूर्ण,
	/*** raw bayer and grayscale क्रमmats start here ***/
	अणु
		.fourcc = V4L2_PIX_FMT_SBGGR8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SBGGR8_1X8),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 8,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SGBRG8_1X8),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 8,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SGRBG8_1X8),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 8,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SRGGB8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SRGGB8_1X8),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 8,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SBGGR16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SBGGR10_1X10,
			MEDIA_BUS_FMT_SBGGR12_1X12,
			MEDIA_BUS_FMT_SBGGR14_1X14,
			MEDIA_BUS_FMT_SBGGR16_1X16
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SGBRG10_1X10,
			MEDIA_BUS_FMT_SGBRG12_1X12,
			MEDIA_BUS_FMT_SGBRG14_1X14,
			MEDIA_BUS_FMT_SGBRG16_1X16
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SGRBG10_1X10,
			MEDIA_BUS_FMT_SGRBG12_1X12,
			MEDIA_BUS_FMT_SGRBG14_1X14,
			MEDIA_BUS_FMT_SGRBG16_1X16
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SRGGB16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SRGGB10_1X10,
			MEDIA_BUS_FMT_SRGGB12_1X12,
			MEDIA_BUS_FMT_SRGGB14_1X14,
			MEDIA_BUS_FMT_SRGGB16_1X16
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.codes = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_Y8_1X8,
			MEDIA_BUS_FMT_Y10_1X10,
			MEDIA_BUS_FMT_Y12_1X12
		),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 8,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_Y10,
		.codes = IMX_BUS_FMTS(MEDIA_BUS_FMT_Y10_1X10),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_Y12,
		.codes = IMX_BUS_FMTS(MEDIA_BUS_FMT_Y12_1X12),
		.cs     = IPUV3_COLORSPACE_RGB,
		.bpp    = 16,
		.bayer  = true,
	पूर्ण,
पूर्ण;

/*
 * Search in the pixel_क्रमmats[] array क्रम an entry with the given fourcc
 * that matches the requested selection criteria and वापस it.
 *
 * @fourcc: Search क्रम an entry with the given fourcc pixel क्रमmat.
 * @fmt_sel: Allow entries only with the given selection criteria.
 */
स्थिर काष्ठा imx_media_pixfmt *
imx_media_find_pixel_क्रमmat(u32 fourcc, क्रमागत imx_pixfmt_sel fmt_sel)
अणु
	bool sel_ipu = fmt_sel & PIXFMT_SEL_IPU;
	अचिन्हित पूर्णांक i;

	fmt_sel &= ~PIXFMT_SEL_IPU;

	क्रम (i = 0; i < ARRAY_SIZE(pixel_क्रमmats); i++) अणु
		स्थिर काष्ठा imx_media_pixfmt *fmt = &pixel_क्रमmats[i];
		क्रमागत imx_pixfmt_sel sel;

		अगर (sel_ipu != fmt->ipufmt)
			जारी;

		sel = fmt->bayer ? PIXFMT_SEL_BAYER :
			((fmt->cs == IPUV3_COLORSPACE_YUV) ?
			 PIXFMT_SEL_YUV : PIXFMT_SEL_RGB);

		अगर ((fmt_sel & sel) && fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_find_pixel_क्रमmat);

/*
 * Search in the pixel_क्रमmats[] array क्रम an entry with the given media
 * bus code that matches the requested selection criteria and वापस it.
 *
 * @code: Search क्रम an entry with the given media-bus code.
 * @fmt_sel: Allow entries only with the given selection criteria.
 */
स्थिर काष्ठा imx_media_pixfmt *
imx_media_find_mbus_क्रमmat(u32 code, क्रमागत imx_pixfmt_sel fmt_sel)
अणु
	bool sel_ipu = fmt_sel & PIXFMT_SEL_IPU;
	अचिन्हित पूर्णांक i;

	fmt_sel &= ~PIXFMT_SEL_IPU;

	क्रम (i = 0; i < ARRAY_SIZE(pixel_क्रमmats); i++) अणु
		स्थिर काष्ठा imx_media_pixfmt *fmt = &pixel_क्रमmats[i];
		क्रमागत imx_pixfmt_sel sel;
		अचिन्हित पूर्णांक j;

		अगर (sel_ipu != fmt->ipufmt)
			जारी;

		sel = fmt->bayer ? PIXFMT_SEL_BAYER :
			((fmt->cs == IPUV3_COLORSPACE_YUV) ?
			 PIXFMT_SEL_YUV : PIXFMT_SEL_RGB);

		अगर (!(fmt_sel & sel) || !fmt->codes)
			जारी;

		क्रम (j = 0; fmt->codes[j]; j++) अणु
			अगर (code == fmt->codes[j])
				वापस fmt;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_find_mbus_क्रमmat);

/*
 * Enumerate entries in the pixel_क्रमmats[] array that match the
 * requested selection criteria. Return the fourcc that matches the
 * selection criteria at the requested match index.
 *
 * @fourcc: The वापसed fourcc that matches the search criteria at
 *          the requested match index.
 * @index: The requested match index.
 * @fmt_sel: Include in the क्रमागतeration entries with the given selection
 *           criteria.
 * @code: If non-zero, only include in the क्रमागतeration entries matching this
 *	media bus code.
 */
पूर्णांक imx_media_क्रमागत_pixel_क्रमmats(u32 *fourcc, u32 index,
				 क्रमागत imx_pixfmt_sel fmt_sel, u32 code)
अणु
	bool sel_ipu = fmt_sel & PIXFMT_SEL_IPU;
	अचिन्हित पूर्णांक i;

	fmt_sel &= ~PIXFMT_SEL_IPU;

	क्रम (i = 0; i < ARRAY_SIZE(pixel_क्रमmats); i++) अणु
		स्थिर काष्ठा imx_media_pixfmt *fmt = &pixel_क्रमmats[i];
		क्रमागत imx_pixfmt_sel sel;

		अगर (sel_ipu != fmt->ipufmt)
			जारी;

		sel = fmt->bayer ? PIXFMT_SEL_BAYER :
			((fmt->cs == IPUV3_COLORSPACE_YUV) ?
			 PIXFMT_SEL_YUV : PIXFMT_SEL_RGB);

		अगर (!(fmt_sel & sel))
			जारी;

		/*
		 * If a media bus code is specअगरied, only consider क्रमmats that
		 * match it.
		 */
		अगर (code) अणु
			अचिन्हित पूर्णांक j;

			अगर (!fmt->codes)
				जारी;

			क्रम (j = 0; fmt->codes[j]; j++) अणु
				अगर (code == fmt->codes[j])
					अवरोध;
			पूर्ण

			अगर (!fmt->codes[j])
				जारी;
		पूर्ण

		अगर (index == 0) अणु
			*fourcc = fmt->fourcc;
			वापस 0;
		पूर्ण

		index--;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_क्रमागत_pixel_क्रमmats);

/*
 * Enumerate entries in the pixel_क्रमmats[] array that match the
 * requested search criteria. Return the media-bus code that matches
 * the search criteria at the requested match index.
 *
 * @code: The वापसed media-bus code that matches the search criteria at
 *        the requested match index.
 * @index: The requested match index.
 * @fmt_sel: Include in the क्रमागतeration entries with the given selection
 *           criteria.
 */
पूर्णांक imx_media_क्रमागत_mbus_क्रमmats(u32 *code, u32 index,
				क्रमागत imx_pixfmt_sel fmt_sel)
अणु
	bool sel_ipu = fmt_sel & PIXFMT_SEL_IPU;
	अचिन्हित पूर्णांक i;

	fmt_sel &= ~PIXFMT_SEL_IPU;

	क्रम (i = 0; i < ARRAY_SIZE(pixel_क्रमmats); i++) अणु
		स्थिर काष्ठा imx_media_pixfmt *fmt = &pixel_क्रमmats[i];
		क्रमागत imx_pixfmt_sel sel;
		अचिन्हित पूर्णांक j;

		अगर (sel_ipu != fmt->ipufmt)
			जारी;

		sel = fmt->bayer ? PIXFMT_SEL_BAYER :
			((fmt->cs == IPUV3_COLORSPACE_YUV) ?
			 PIXFMT_SEL_YUV : PIXFMT_SEL_RGB);

		अगर (!(fmt_sel & sel) || !fmt->codes)
			जारी;

		क्रम (j = 0; fmt->codes[j]; j++) अणु
			अगर (index == 0) अणु
				*code = fmt->codes[j];
				वापस 0;
			पूर्ण

			index--;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_क्रमागत_mbus_क्रमmats);

पूर्णांक imx_media_init_mbus_fmt(काष्ठा v4l2_mbus_framefmt *mbus,
			    u32 width, u32 height, u32 code, u32 field,
			    स्थिर काष्ठा imx_media_pixfmt **cc)
अणु
	स्थिर काष्ठा imx_media_pixfmt *lcc;

	mbus->width = width;
	mbus->height = height;
	mbus->field = field;

	अगर (code == 0)
		imx_media_क्रमागत_mbus_क्रमmats(&code, 0, PIXFMT_SEL_YUV);

	lcc = imx_media_find_mbus_क्रमmat(code, PIXFMT_SEL_ANY);
	अगर (!lcc) अणु
		lcc = imx_media_find_ipu_क्रमmat(code, PIXFMT_SEL_YUV_RGB);
		अगर (!lcc)
			वापस -EINVAL;
	पूर्ण

	mbus->code = code;

	mbus->colorspace = V4L2_COLORSPACE_SRGB;
	mbus->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(mbus->colorspace);
	mbus->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(mbus->colorspace);
	mbus->quantization =
		V4L2_MAP_QUANTIZATION_DEFAULT(lcc->cs == IPUV3_COLORSPACE_RGB,
					      mbus->colorspace,
					      mbus->ycbcr_enc);

	अगर (cc)
		*cc = lcc;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_init_mbus_fmt);

/*
 * Initializes the TRY क्रमmat to the ACTIVE क्रमmat on all pads
 * of a subdev. Can be used as the .init_cfg pad operation.
 */
पूर्णांक imx_media_init_cfg(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_mbus_framefmt *mf_try;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक pad;
	पूर्णांक ret;

	क्रम (pad = 0; pad < sd->entity.num_pads; pad++) अणु
		स_रखो(&क्रमmat, 0, माप(क्रमmat));

		क्रमmat.pad = pad;
		क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &क्रमmat);
		अगर (ret)
			जारी;

		mf_try = v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
		*mf_try = क्रमmat.क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_init_cfg);

/*
 * Default the colorspace in tryfmt to SRGB अगर set to an unsupported
 * colorspace or not initialized. Then set the reमुख्यing colorimetry
 * parameters based on the colorspace अगर they are uninitialized.
 *
 * tryfmt->code must be set on entry.
 *
 * If this क्रमmat is destined to be routed through the Image Converter,
 * Y`CbCr encoding must be fixed. The IC supports only BT.601 Y`CbCr
 * or Rec.709 Y`CbCr encoding.
 */
व्योम imx_media_try_colorimetry(काष्ठा v4l2_mbus_framefmt *tryfmt,
			       bool ic_route)
अणु
	स्थिर काष्ठा imx_media_pixfmt *cc;
	bool is_rgb = false;

	cc = imx_media_find_mbus_क्रमmat(tryfmt->code, PIXFMT_SEL_ANY);
	अगर (!cc)
		cc = imx_media_find_ipu_क्रमmat(tryfmt->code,
					       PIXFMT_SEL_YUV_RGB);

	अगर (cc && cc->cs == IPUV3_COLORSPACE_RGB)
		is_rgb = true;

	चयन (tryfmt->colorspace) अणु
	हाल V4L2_COLORSPACE_SMPTE170M:
	हाल V4L2_COLORSPACE_REC709:
	हाल V4L2_COLORSPACE_JPEG:
	हाल V4L2_COLORSPACE_SRGB:
	हाल V4L2_COLORSPACE_BT2020:
	हाल V4L2_COLORSPACE_OPRGB:
	हाल V4L2_COLORSPACE_DCI_P3:
	हाल V4L2_COLORSPACE_RAW:
		अवरोध;
	शेष:
		tryfmt->colorspace = V4L2_COLORSPACE_SRGB;
		अवरोध;
	पूर्ण

	अगर (tryfmt->xfer_func == V4L2_XFER_FUNC_DEFAULT)
		tryfmt->xfer_func =
			V4L2_MAP_XFER_FUNC_DEFAULT(tryfmt->colorspace);

	अगर (ic_route) अणु
		अगर (tryfmt->ycbcr_enc != V4L2_YCBCR_ENC_601 &&
		    tryfmt->ycbcr_enc != V4L2_YCBCR_ENC_709)
			tryfmt->ycbcr_enc = V4L2_YCBCR_ENC_601;
	पूर्ण अन्यथा अणु
		अगर (tryfmt->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT) अणु
			tryfmt->ycbcr_enc =
				V4L2_MAP_YCBCR_ENC_DEFAULT(tryfmt->colorspace);
		पूर्ण
	पूर्ण

	अगर (tryfmt->quantization == V4L2_QUANTIZATION_DEFAULT)
		tryfmt->quantization =
			V4L2_MAP_QUANTIZATION_DEFAULT(is_rgb,
						      tryfmt->colorspace,
						      tryfmt->ycbcr_enc);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_try_colorimetry);

पूर्णांक imx_media_mbus_fmt_to_pix_fmt(काष्ठा v4l2_pix_क्रमmat *pix,
				  स्थिर काष्ठा v4l2_mbus_framefmt *mbus,
				  स्थिर काष्ठा imx_media_pixfmt *cc)
अणु
	u32 width;
	u32 stride;

	अगर (!cc) अणु
		cc = imx_media_find_ipu_क्रमmat(mbus->code,
					       PIXFMT_SEL_YUV_RGB);
		अगर (!cc)
			cc = imx_media_find_mbus_क्रमmat(mbus->code,
							PIXFMT_SEL_ANY);
		अगर (!cc)
			वापस -EINVAL;
	पूर्ण

	/*
	 * TODO: the IPU currently करोes not support the AYUV32 क्रमmat,
	 * so until it करोes convert to a supported YUV क्रमmat.
	 */
	अगर (cc->ipufmt && cc->cs == IPUV3_COLORSPACE_YUV) अणु
		u32 code;

		imx_media_क्रमागत_mbus_क्रमmats(&code, 0, PIXFMT_SEL_YUV);
		cc = imx_media_find_mbus_क्रमmat(code, PIXFMT_SEL_YUV);
	पूर्ण

	/* Round up width क्रम minimum burst size */
	width = round_up(mbus->width, 8);

	/* Round up stride क्रम IDMAC line start address alignment */
	अगर (cc->planar)
		stride = round_up(width, 16);
	अन्यथा
		stride = round_up((width * cc->bpp) >> 3, 8);

	pix->width = width;
	pix->height = mbus->height;
	pix->pixelक्रमmat = cc->fourcc;
	pix->colorspace = mbus->colorspace;
	pix->xfer_func = mbus->xfer_func;
	pix->ycbcr_enc = mbus->ycbcr_enc;
	pix->quantization = mbus->quantization;
	pix->field = mbus->field;
	pix->bytesperline = stride;
	pix->sizeimage = cc->planar ? ((stride * pix->height * cc->bpp) >> 3) :
			 stride * pix->height;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_mbus_fmt_to_pix_fmt);

पूर्णांक imx_media_mbus_fmt_to_ipu_image(काष्ठा ipu_image *image,
				    स्थिर काष्ठा v4l2_mbus_framefmt *mbus)
अणु
	पूर्णांक ret;

	स_रखो(image, 0, माप(*image));

	ret = imx_media_mbus_fmt_to_pix_fmt(&image->pix, mbus, शून्य);
	अगर (ret)
		वापस ret;

	image->rect.width = mbus->width;
	image->rect.height = mbus->height;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_mbus_fmt_to_ipu_image);

पूर्णांक imx_media_ipu_image_to_mbus_fmt(काष्ठा v4l2_mbus_framefmt *mbus,
				    स्थिर काष्ठा ipu_image *image)
अणु
	स्थिर काष्ठा imx_media_pixfmt *fmt;

	fmt = imx_media_find_pixel_क्रमmat(image->pix.pixelक्रमmat,
					  PIXFMT_SEL_ANY);
	अगर (!fmt || !fmt->codes || !fmt->codes[0])
		वापस -EINVAL;

	स_रखो(mbus, 0, माप(*mbus));
	mbus->width = image->pix.width;
	mbus->height = image->pix.height;
	mbus->code = fmt->codes[0];
	mbus->field = image->pix.field;
	mbus->colorspace = image->pix.colorspace;
	mbus->xfer_func = image->pix.xfer_func;
	mbus->ycbcr_enc = image->pix.ycbcr_enc;
	mbus->quantization = image->pix.quantization;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_ipu_image_to_mbus_fmt);

व्योम imx_media_मुक्त_dma_buf(काष्ठा device *dev,
			    काष्ठा imx_media_dma_buf *buf)
अणु
	अगर (buf->virt)
		dma_मुक्त_coherent(dev, buf->len, buf->virt, buf->phys);

	buf->virt = शून्य;
	buf->phys = 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_मुक्त_dma_buf);

पूर्णांक imx_media_alloc_dma_buf(काष्ठा device *dev,
			    काष्ठा imx_media_dma_buf *buf,
			    पूर्णांक size)
अणु
	imx_media_मुक्त_dma_buf(dev, buf);

	buf->len = PAGE_ALIGN(size);
	buf->virt = dma_alloc_coherent(dev, buf->len, &buf->phys,
				       GFP_DMA | GFP_KERNEL);
	अगर (!buf->virt) अणु
		dev_err(dev, "%s: failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_alloc_dma_buf);

/* क्रमm a subdev name given a group id and ipu id */
व्योम imx_media_grp_id_to_sd_name(अक्षर *sd_name, पूर्णांक sz, u32 grp_id, पूर्णांक ipu_id)
अणु
	पूर्णांक id;

	चयन (grp_id) अणु
	हाल IMX_MEDIA_GRP_ID_IPU_CSI0...IMX_MEDIA_GRP_ID_IPU_CSI1:
		id = (grp_id >> IMX_MEDIA_GRP_ID_IPU_CSI_BIT) - 1;
		snम_लिखो(sd_name, sz, "ipu%d_csi%d", ipu_id + 1, id);
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_VDIC:
		snम_लिखो(sd_name, sz, "ipu%d_vdic", ipu_id + 1);
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRP:
		snम_लिखो(sd_name, sz, "ipu%d_ic_prp", ipu_id + 1);
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRPENC:
		snम_लिखो(sd_name, sz, "ipu%d_ic_prpenc", ipu_id + 1);
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRPVF:
		snम_लिखो(sd_name, sz, "ipu%d_ic_prpvf", ipu_id + 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_grp_id_to_sd_name);

काष्ठा v4l2_subdev *
imx_media_find_subdev_by_fwnode(काष्ठा imx_media_dev *imxmd,
				काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा v4l2_subdev *sd;

	list_क्रम_each_entry(sd, &imxmd->v4l2_dev.subdevs, list) अणु
		अगर (sd->fwnode == fwnode)
			वापस sd;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_find_subdev_by_fwnode);

काष्ठा v4l2_subdev *
imx_media_find_subdev_by_devname(काष्ठा imx_media_dev *imxmd,
				 स्थिर अक्षर *devname)
अणु
	काष्ठा v4l2_subdev *sd;

	list_क्रम_each_entry(sd, &imxmd->v4l2_dev.subdevs, list) अणु
		अगर (!म_भेद(devname, dev_name(sd->dev)))
			वापस sd;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_find_subdev_by_devname);

/*
 * Adds a video device to the master video device list. This is called
 * when a video device is रेजिस्टरed.
 */
व्योम imx_media_add_video_device(काष्ठा imx_media_dev *imxmd,
				काष्ठा imx_media_video_dev *vdev)
अणु
	mutex_lock(&imxmd->mutex);

	list_add_tail(&vdev->list, &imxmd->vdev_list);

	mutex_unlock(&imxmd->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_add_video_device);

/*
 * Search upstream/करोwnstream क्रम a subdevice or video device pad in the
 * current pipeline, starting from start_entity. Returns the device's
 * source/sink pad that it was reached from. Must be called with
 * mdev->graph_mutex held.
 *
 * If grp_id != 0, finds a subdevice's pad of given grp_id.
 * Else If buftype != 0, finds a video device's pad of given buffer type.
 * Else, वापसs the nearest source/sink pad to start_entity.
 */
काष्ठा media_pad *
imx_media_pipeline_pad(काष्ठा media_entity *start_entity, u32 grp_id,
		       क्रमागत v4l2_buf_type buftype, bool upstream)
अणु
	काष्ठा media_entity *me = start_entity;
	काष्ठा media_pad *pad = शून्य;
	काष्ठा video_device *vfd;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i;

	क्रम (i = 0; i < me->num_pads; i++) अणु
		काष्ठा media_pad *spad = &me->pads[i];

		अगर ((upstream && !(spad->flags & MEDIA_PAD_FL_SINK)) ||
		    (!upstream && !(spad->flags & MEDIA_PAD_FL_SOURCE)))
			जारी;

		pad = media_entity_remote_pad(spad);
		अगर (!pad)
			जारी;

		अगर (grp_id) अणु
			अगर (is_media_entity_v4l2_subdev(pad->entity)) अणु
				sd = media_entity_to_v4l2_subdev(pad->entity);
				अगर (sd->grp_id & grp_id)
					वापस pad;
			पूर्ण

			वापस imx_media_pipeline_pad(pad->entity, grp_id,
						      buftype, upstream);
		पूर्ण अन्यथा अगर (buftype) अणु
			अगर (is_media_entity_v4l2_video_device(pad->entity)) अणु
				vfd = media_entity_to_video_device(pad->entity);
				अगर (buftype == vfd->queue->type)
					वापस pad;
			पूर्ण

			वापस imx_media_pipeline_pad(pad->entity, grp_id,
						      buftype, upstream);
		पूर्ण अन्यथा अणु
			वापस pad;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_pipeline_pad);

/*
 * Search upstream/करोwnstream क्रम a subdev or video device in the current
 * pipeline. Must be called with mdev->graph_mutex held.
 */
अटल काष्ठा media_entity *
find_pipeline_entity(काष्ठा media_entity *start, u32 grp_id,
		     क्रमागत v4l2_buf_type buftype, bool upstream)
अणु
	काष्ठा media_pad *pad = शून्य;
	काष्ठा video_device *vfd;
	काष्ठा v4l2_subdev *sd;

	अगर (grp_id && is_media_entity_v4l2_subdev(start)) अणु
		sd = media_entity_to_v4l2_subdev(start);
		अगर (sd->grp_id & grp_id)
			वापस &sd->entity;
	पूर्ण अन्यथा अगर (buftype && is_media_entity_v4l2_video_device(start)) अणु
		vfd = media_entity_to_video_device(start);
		अगर (buftype == vfd->queue->type)
			वापस &vfd->entity;
	पूर्ण

	pad = imx_media_pipeline_pad(start, grp_id, buftype, upstream);

	वापस pad ? pad->entity : शून्य;
पूर्ण

/*
 * Find the upstream mipi-csi2 भव channel reached from the given
 * start entity in the current pipeline.
 * Must be called with mdev->graph_mutex held.
 */
पूर्णांक imx_media_pipeline_csi2_channel(काष्ठा media_entity *start_entity)
अणु
	काष्ठा media_pad *pad;
	पूर्णांक ret = -EPIPE;

	pad = imx_media_pipeline_pad(start_entity, IMX_MEDIA_GRP_ID_CSI2,
				     0, true);
	अगर (pad)
		ret = pad->index - 1;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_pipeline_csi2_channel);

/*
 * Find a subdev reached upstream from the given start entity in
 * the current pipeline.
 * Must be called with mdev->graph_mutex held.
 */
काष्ठा v4l2_subdev *
imx_media_pipeline_subdev(काष्ठा media_entity *start_entity, u32 grp_id,
			  bool upstream)
अणु
	काष्ठा media_entity *me;

	me = find_pipeline_entity(start_entity, grp_id, 0, upstream);
	अगर (!me)
		वापस ERR_PTR(-ENODEV);

	वापस media_entity_to_v4l2_subdev(me);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_pipeline_subdev);

/*
 * Find a subdev reached upstream from the given start entity in
 * the current pipeline.
 * Must be called with mdev->graph_mutex held.
 */
काष्ठा video_device *
imx_media_pipeline_video_device(काष्ठा media_entity *start_entity,
				क्रमागत v4l2_buf_type buftype, bool upstream)
अणु
	काष्ठा media_entity *me;

	me = find_pipeline_entity(start_entity, 0, buftype, upstream);
	अगर (!me)
		वापस ERR_PTR(-ENODEV);

	वापस media_entity_to_video_device(me);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_pipeline_video_device);

/*
 * Find a fwnode endpoपूर्णांक that maps to the given subdevice's pad.
 * If there are multiple endpoपूर्णांकs that map to the pad, only the
 * first endpoपूर्णांक encountered is वापसed.
 *
 * On success the refcount of the वापसed fwnode endpoपूर्णांक is
 * incremented.
 */
काष्ठा fwnode_handle *imx_media_get_pad_fwnode(काष्ठा media_pad *pad)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा v4l2_subdev *sd;

	अगर (!is_media_entity_v4l2_subdev(pad->entity))
		वापस ERR_PTR(-ENODEV);

	sd = media_entity_to_v4l2_subdev(pad->entity);

	fwnode_graph_क्रम_each_endpoपूर्णांक(dev_fwnode(sd->dev), endpoपूर्णांक) अणु
		पूर्णांक pad_idx = media_entity_get_fwnode_pad(&sd->entity,
							  endpoपूर्णांक,
							  pad->flags);
		अगर (pad_idx < 0)
			जारी;

		अगर (pad_idx == pad->index)
			वापस endpoपूर्णांक;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_get_pad_fwnode);

/*
 * Turn current pipeline streaming on/off starting from entity.
 */
पूर्णांक imx_media_pipeline_set_stream(काष्ठा imx_media_dev *imxmd,
				  काष्ठा media_entity *entity,
				  bool on)
अणु
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret = 0;

	अगर (!is_media_entity_v4l2_subdev(entity))
		वापस -EINVAL;
	sd = media_entity_to_v4l2_subdev(entity);

	mutex_lock(&imxmd->md.graph_mutex);

	अगर (on) अणु
		ret = __media_pipeline_start(entity, &imxmd->pipe);
		अगर (ret)
			जाओ out;
		ret = v4l2_subdev_call(sd, video, s_stream, 1);
		अगर (ret)
			__media_pipeline_stop(entity);
	पूर्ण अन्यथा अणु
		v4l2_subdev_call(sd, video, s_stream, 0);
		अगर (entity->pipe)
			__media_pipeline_stop(entity);
	पूर्ण

out:
	mutex_unlock(&imxmd->md.graph_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_pipeline_set_stream);

MODULE_DESCRIPTION("i.MX5/6 v4l2 media controller driver");
MODULE_AUTHOR("Steve Longerbeam <steve_longerbeam@mentor.com>");
MODULE_LICENSE("GPL");
