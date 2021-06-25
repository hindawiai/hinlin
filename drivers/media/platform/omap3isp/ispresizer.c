<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispresizer.c
 *
 * TI OMAP3 ISP - Resizer module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispresizer.h"

/*
 * Resizer Constants
 */
#घोषणा MIN_RESIZE_VALUE		64
#घोषणा MID_RESIZE_VALUE		512
#घोषणा MAX_RESIZE_VALUE		1024

#घोषणा MIN_IN_WIDTH			32
#घोषणा MIN_IN_HEIGHT			32
#घोषणा MAX_IN_WIDTH_MEMORY_MODE	4095
#घोषणा MAX_IN_WIDTH_ONTHEFLY_MODE_ES1	1280
#घोषणा MAX_IN_WIDTH_ONTHEFLY_MODE_ES2	4095
#घोषणा MAX_IN_HEIGHT			4095

#घोषणा MIN_OUT_WIDTH			16
#घोषणा MIN_OUT_HEIGHT			2
#घोषणा MAX_OUT_HEIGHT			4095

/*
 * Resizer Use Constraपूर्णांकs
 * "TRM ES3.1, table 12-46"
 */
#घोषणा MAX_4TAP_OUT_WIDTH_ES1		1280
#घोषणा MAX_7TAP_OUT_WIDTH_ES1		640
#घोषणा MAX_4TAP_OUT_WIDTH_ES2		3312
#घोषणा MAX_7TAP_OUT_WIDTH_ES2		1650
#घोषणा MAX_4TAP_OUT_WIDTH_3630		4096
#घोषणा MAX_7TAP_OUT_WIDTH_3630		2048

/*
 * Constants क्रम ratio calculation
 */
#घोषणा RESIZE_DIVISOR			256
#घोषणा DEFAULT_PHASE			1

/*
 * Default (and only) configuration of filter coefficients.
 * 7-tap mode is क्रम scale factors 0.25x to 0.5x.
 * 4-tap mode is क्रम scale factors 0.5x to 4.0x.
 * There shouldn't be any reason to recalculate these, EVER.
 */
अटल स्थिर काष्ठा isprsz_coef filter_coefs = अणु
	/* For 8-phase 4-tap horizontal filter: */
	अणु
		0x0000, 0x0100, 0x0000, 0x0000,
		0x03FA, 0x00F6, 0x0010, 0x0000,
		0x03F9, 0x00DB, 0x002C, 0x0000,
		0x03FB, 0x00B3, 0x0053, 0x03FF,
		0x03FD, 0x0082, 0x0084, 0x03FD,
		0x03FF, 0x0053, 0x00B3, 0x03FB,
		0x0000, 0x002C, 0x00DB, 0x03F9,
		0x0000, 0x0010, 0x00F6, 0x03FA
	पूर्ण,
	/* For 8-phase 4-tap vertical filter: */
	अणु
		0x0000, 0x0100, 0x0000, 0x0000,
		0x03FA, 0x00F6, 0x0010, 0x0000,
		0x03F9, 0x00DB, 0x002C, 0x0000,
		0x03FB, 0x00B3, 0x0053, 0x03FF,
		0x03FD, 0x0082, 0x0084, 0x03FD,
		0x03FF, 0x0053, 0x00B3, 0x03FB,
		0x0000, 0x002C, 0x00DB, 0x03F9,
		0x0000, 0x0010, 0x00F6, 0x03FA
	पूर्ण,
	/* For 4-phase 7-tap horizontal filter: */
	#घोषणा DUMMY 0
	अणु
		0x0004, 0x0023, 0x005A, 0x0058, 0x0023, 0x0004, 0x0000, DUMMY,
		0x0002, 0x0018, 0x004d, 0x0060, 0x0031, 0x0008, 0x0000, DUMMY,
		0x0001, 0x000f, 0x003f, 0x0062, 0x003f, 0x000f, 0x0001, DUMMY,
		0x0000, 0x0008, 0x0031, 0x0060, 0x004d, 0x0018, 0x0002, DUMMY
	पूर्ण,
	/* For 4-phase 7-tap vertical filter: */
	अणु
		0x0004, 0x0023, 0x005A, 0x0058, 0x0023, 0x0004, 0x0000, DUMMY,
		0x0002, 0x0018, 0x004d, 0x0060, 0x0031, 0x0008, 0x0000, DUMMY,
		0x0001, 0x000f, 0x003f, 0x0062, 0x003f, 0x000f, 0x0001, DUMMY,
		0x0000, 0x0008, 0x0031, 0x0060, 0x004d, 0x0018, 0x0002, DUMMY
	पूर्ण
	/*
	 * The dummy padding is required in 7-tap mode because of how the
	 * रेजिस्टरs are arranged physically.
	 */
	#अघोषित DUMMY
पूर्ण;

/*
 * __resizer_get_क्रमmat - helper function क्रम getting resizer क्रमmat
 * @res   : poपूर्णांकer to resizer निजी काष्ठाure
 * @pad   : pad number
 * @cfg: V4L2 subdev pad configuration
 * @which : wanted subdev क्रमmat
 * वापस zero
 */
अटल काष्ठा v4l2_mbus_framefmt *
__resizer_get_क्रमmat(काष्ठा isp_res_device *res, काष्ठा v4l2_subdev_pad_config *cfg,
		     अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&res->subdev, cfg, pad);
	अन्यथा
		वापस &res->क्रमmats[pad];
पूर्ण

/*
 * __resizer_get_crop - helper function क्रम getting resizer crop rectangle
 * @res   : poपूर्णांकer to resizer निजी काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @which : wanted subdev crop rectangle
 */
अटल काष्ठा v4l2_rect *
__resizer_get_crop(काष्ठा isp_res_device *res, काष्ठा v4l2_subdev_pad_config *cfg,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&res->subdev, cfg, RESZ_PAD_SINK);
	अन्यथा
		वापस &res->crop.request;
पूर्ण

/*
 * resizer_set_filters - Set resizer filters
 * @res: Device context.
 * @h_coeff: horizontal coefficient
 * @v_coeff: vertical coefficient
 * Return none
 */
अटल व्योम resizer_set_filters(काष्ठा isp_res_device *res, स्थिर u16 *h_coeff,
				स्थिर u16 *v_coeff)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 startaddr_h, startaddr_v, पंचांगp_h, पंचांगp_v;
	पूर्णांक i;

	startaddr_h = ISPRSZ_HFILT10;
	startaddr_v = ISPRSZ_VFILT10;

	क्रम (i = 0; i < COEFF_CNT; i += 2) अणु
		पंचांगp_h = h_coeff[i] |
			(h_coeff[i + 1] << ISPRSZ_HFILT_COEF1_SHIFT);
		पंचांगp_v = v_coeff[i] |
			(v_coeff[i + 1] << ISPRSZ_VFILT_COEF1_SHIFT);
		isp_reg_ग_लिखोl(isp, पंचांगp_h, OMAP3_ISP_IOMEM_RESZ, startaddr_h);
		isp_reg_ग_लिखोl(isp, पंचांगp_v, OMAP3_ISP_IOMEM_RESZ, startaddr_v);
		startaddr_h += 4;
		startaddr_v += 4;
	पूर्ण
पूर्ण

/*
 * resizer_set_bilinear - Chrominance horizontal algorithm select
 * @res: Device context.
 * @type: Filtering पूर्णांकerpolation type.
 *
 * Filtering that is same as luminance processing is
 * पूर्णांकended only क्रम करोwnsampling, and bilinear पूर्णांकerpolation
 * is पूर्णांकended only क्रम upsampling.
 */
अटल व्योम resizer_set_bilinear(काष्ठा isp_res_device *res,
				 क्रमागत resizer_chroma_algo type)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	अगर (type == RSZ_BILINEAR)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_CBILIN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_CBILIN);
पूर्ण

/*
 * resizer_set_ycpos - Luminance and chrominance order
 * @res: Device context.
 * @pixelcode: pixel code.
 */
अटल व्योम resizer_set_ycpos(काष्ठा isp_res_device *res, u32 pixelcode)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	चयन (pixelcode) अणु
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_YCPOS);
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_YCPOS);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/*
 * resizer_set_phase - Setup horizontal and vertical starting phase
 * @res: Device context.
 * @h_phase: horizontal phase parameters.
 * @v_phase: vertical phase parameters.
 *
 * Horizontal and vertical phase range is 0 to 7
 */
अटल व्योम resizer_set_phase(काष्ठा isp_res_device *res, u32 h_phase,
			      u32 v_phase)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT) &
	      ~(ISPRSZ_CNT_HSTPH_MASK | ISPRSZ_CNT_VSTPH_MASK);
	rgval |= (h_phase << ISPRSZ_CNT_HSTPH_SHIFT) & ISPRSZ_CNT_HSTPH_MASK;
	rgval |= (v_phase << ISPRSZ_CNT_VSTPH_SHIFT) & ISPRSZ_CNT_VSTPH_MASK;

	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT);
पूर्ण

/*
 * resizer_set_luma - Setup luminance enhancer parameters
 * @res: Device context.
 * @luma: Structure क्रम luminance enhancer parameters.
 *
 * Algorithm select:
 *  0x0: Disable
 *  0x1: [-1  2 -1]/2 high-pass filter
 *  0x2: [-1 -2  6 -2 -1]/4 high-pass filter
 *
 * Maximum gain:
 *  The data is coded in U4Q4 representation.
 *
 * Slope:
 *  The data is coded in U4Q4 representation.
 *
 * Coring offset:
 *  The data is coded in U8Q0 representation.
 *
 * The new luminance value is computed as:
 *  Y += HPF(Y) x max(GAIN, (HPF(Y) - CORE) x SLOP + 8) >> 4.
 */
अटल व्योम resizer_set_luma(काष्ठा isp_res_device *res,
			     काष्ठा resizer_luma_yenh *luma)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval  = (luma->algo << ISPRSZ_YENH_ALGO_SHIFT)
		  & ISPRSZ_YENH_ALGO_MASK;
	rgval |= (luma->gain << ISPRSZ_YENH_GAIN_SHIFT)
		  & ISPRSZ_YENH_GAIN_MASK;
	rgval |= (luma->slope << ISPRSZ_YENH_SLOP_SHIFT)
		  & ISPRSZ_YENH_SLOP_MASK;
	rgval |= (luma->core << ISPRSZ_YENH_CORE_SHIFT)
		  & ISPRSZ_YENH_CORE_MASK;

	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_YENH);
पूर्ण

/*
 * resizer_set_source - Input source select
 * @res: Device context.
 * @source: Input source type
 *
 * If this field is set to RESIZER_INPUT_VP, the resizer input is fed from
 * Preview/CCDC engine, otherwise from memory.
 */
अटल व्योम resizer_set_source(काष्ठा isp_res_device *res,
			       क्रमागत resizer_input_entity source)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	अगर (source == RESIZER_INPUT_MEMORY)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_INPSRC);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_INPSRC);
पूर्ण

/*
 * resizer_set_ratio - Setup horizontal and vertical resizing value
 * @res: Device context.
 * @ratio: Structure क्रम ratio parameters.
 *
 * Resizing range from 64 to 1024
 */
अटल व्योम resizer_set_ratio(काष्ठा isp_res_device *res,
			      स्थिर काष्ठा resizer_ratio *ratio)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	स्थिर u16 *h_filter, *v_filter;
	u32 rgval;

	rgval = isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT) &
			      ~(ISPRSZ_CNT_HRSZ_MASK | ISPRSZ_CNT_VRSZ_MASK);
	rgval |= ((ratio->horz - 1) << ISPRSZ_CNT_HRSZ_SHIFT)
		  & ISPRSZ_CNT_HRSZ_MASK;
	rgval |= ((ratio->vert - 1) << ISPRSZ_CNT_VRSZ_SHIFT)
		  & ISPRSZ_CNT_VRSZ_MASK;
	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT);

	/* prepare horizontal filter coefficients */
	अगर (ratio->horz > MID_RESIZE_VALUE)
		h_filter = &filter_coefs.h_filter_coef_7tap[0];
	अन्यथा
		h_filter = &filter_coefs.h_filter_coef_4tap[0];

	/* prepare vertical filter coefficients */
	अगर (ratio->vert > MID_RESIZE_VALUE)
		v_filter = &filter_coefs.v_filter_coef_7tap[0];
	अन्यथा
		v_filter = &filter_coefs.v_filter_coef_4tap[0];

	resizer_set_filters(res, h_filter, v_filter);
पूर्ण

/*
 * resizer_set_dst_size - Setup the output height and width
 * @res: Device context.
 * @width: Output width.
 * @height: Output height.
 *
 * Width :
 *  The value must be EVEN.
 *
 * Height:
 *  The number of bytes written to SDRAM must be
 *  a multiple of 16-bytes अगर the vertical resizing factor
 *  is greater than 1x (upsizing)
 */
अटल व्योम resizer_set_output_size(काष्ठा isp_res_device *res,
				    u32 width, u32 height)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval  = (width << ISPRSZ_OUT_SIZE_HORZ_SHIFT)
		 & ISPRSZ_OUT_SIZE_HORZ_MASK;
	rgval |= (height << ISPRSZ_OUT_SIZE_VERT_SHIFT)
		 & ISPRSZ_OUT_SIZE_VERT_MASK;
	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_OUT_SIZE);
पूर्ण

/*
 * resizer_set_output_offset - Setup memory offset क्रम the output lines.
 * @res: Device context.
 * @offset: Memory offset.
 *
 * The 5 LSBs are क्रमced to be zeros by the hardware to align on a 32-byte
 * boundary; the 5 LSBs are पढ़ो-only. For optimal use of SDRAM bandwidth,
 * the SDRAM line offset must be set on a 256-byte boundary
 */
अटल व्योम resizer_set_output_offset(काष्ठा isp_res_device *res, u32 offset)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	isp_reg_ग_लिखोl(isp, offset, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_SDR_OUTOFF);
पूर्ण

/*
 * resizer_set_start - Setup vertical and horizontal start position
 * @res: Device context.
 * @left: Horizontal start position.
 * @top: Vertical start position.
 *
 * Vertical start line:
 *  This field makes sense only when the resizer obtains its input
 *  from the preview engine/CCDC
 *
 * Horizontal start pixel:
 *  Pixels are coded on 16 bits क्रम YUV and 8 bits क्रम color separate data.
 *  When the resizer माला_लो its input from SDRAM, this field must be set
 *  to <= 15 क्रम YUV 16-bit data and <= 31 क्रम 8-bit color separate data
 */
अटल व्योम resizer_set_start(काष्ठा isp_res_device *res, u32 left, u32 top)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval = (left << ISPRSZ_IN_START_HORZ_ST_SHIFT)
		& ISPRSZ_IN_START_HORZ_ST_MASK;
	rgval |= (top << ISPRSZ_IN_START_VERT_ST_SHIFT)
		 & ISPRSZ_IN_START_VERT_ST_MASK;

	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_IN_START);
पूर्ण

/*
 * resizer_set_input_size - Setup the input size
 * @res: Device context.
 * @width: The range is 0 to 4095 pixels
 * @height: The range is 0 to 4095 lines
 */
अटल व्योम resizer_set_input_size(काष्ठा isp_res_device *res,
				   u32 width, u32 height)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval = (width << ISPRSZ_IN_SIZE_HORZ_SHIFT)
		& ISPRSZ_IN_SIZE_HORZ_MASK;
	rgval |= (height << ISPRSZ_IN_SIZE_VERT_SHIFT)
		 & ISPRSZ_IN_SIZE_VERT_MASK;

	isp_reg_ग_लिखोl(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_IN_SIZE);
पूर्ण

/*
 * resizer_set_src_offs - Setup the memory offset क्रम the input lines
 * @res: Device context.
 * @offset: Memory offset.
 *
 * The 5 LSBs are क्रमced to be zeros by the hardware to align on a 32-byte
 * boundary; the 5 LSBs are पढ़ो-only. This field must be programmed to be
 * 0x0 अगर the resizer input is from preview engine/CCDC.
 */
अटल व्योम resizer_set_input_offset(काष्ठा isp_res_device *res, u32 offset)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	isp_reg_ग_लिखोl(isp, offset, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_SDR_INOFF);
पूर्ण

/*
 * resizer_set_पूर्णांकype - Input type select
 * @res: Device context.
 * @type: Pixel क्रमmat type.
 */
अटल व्योम resizer_set_पूर्णांकype(काष्ठा isp_res_device *res,
			       क्रमागत resizer_colors_type type)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	अगर (type == RSZ_COLOR8)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_INPTYP);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT,
			    ISPRSZ_CNT_INPTYP);
पूर्ण

/*
 * __resizer_set_inaddr - Helper function क्रम set input address
 * @res : poपूर्णांकer to resizer निजी data काष्ठाure
 * @addr: input address
 * वापस none
 */
अटल व्योम __resizer_set_inaddr(काष्ठा isp_res_device *res, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	isp_reg_ग_लिखोl(isp, addr, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_SDR_INADD);
पूर्ण

/*
 * The data rate at the horizontal resizer output must not exceed half the
 * functional घड़ी or 100 MP/s, whichever is lower. According to the TRM
 * there's no similar requirement क्रम the vertical resizer output. However
 * experience showed that vertical upscaling by 4 leads to SBL overflows (with
 * data rates at the resizer output exceeding 300 MP/s). Limiting the resizer
 * output data rate to the functional घड़ी or 200 MP/s, whichever is lower,
 * seems to get rid of SBL overflows.
 *
 * The maximum data rate at the output of the horizontal resizer can thus be
 * computed with
 *
 * max पूर्णांकermediate rate <= L3 घड़ी * input height / output height
 * max पूर्णांकermediate rate <= L3 घड़ी / 2
 *
 * The maximum data rate at the resizer input is then
 *
 * max input rate <= max पूर्णांकermediate rate * input width / output width
 *
 * where the input width and height are the resizer input crop rectangle size.
 * The TRM करोesn't clearly explain if that's a maximum instant data rate or a
 * maximum average data rate.
 */
व्योम omap3isp_resizer_max_rate(काष्ठा isp_res_device *res,
			       अचिन्हित पूर्णांक *max_rate)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&res->subdev.entity);
	स्थिर काष्ठा v4l2_mbus_framefmt *ofmt = &res->क्रमmats[RESZ_PAD_SOURCE];
	अचिन्हित दीर्घ limit = min(pipe->l3_ick, 200000000UL);
	अचिन्हित दीर्घ घड़ी;

	घड़ी = भाग_u64((u64)limit * res->crop.active.height, ofmt->height);
	घड़ी = min(घड़ी, limit / 2);
	*max_rate = भाग_u64((u64)घड़ी * res->crop.active.width, ofmt->width);
पूर्ण

/*
 * When the resizer processes images from memory, the driver must slow करोwn पढ़ो
 * requests on the input to at least comply with the पूर्णांकernal data rate
 * requirements. If the application real-समय requirements can cope with slower
 * processing, the resizer can be slowed करोwn even more to put less pressure on
 * the overall प्रणाली.
 *
 * When the resizer processes images on the fly (either from the CCDC or the
 * preview module), the same data rate requirements apply but they can't be
 * enक्रमced at the resizer level. The image input module (sensor, CCP2 or
 * preview module) must not provide image data faster than the resizer can
 * process.
 *
 * For live image pipelines, the data rate is set by the frame क्रमmat, size and
 * rate. The sensor output frame rate must not exceed the maximum resizer data
 * rate.
 *
 * The resizer slows करोwn पढ़ो requests by inserting रुको cycles in the SBL
 * requests. The maximum number of 256-byte requests per second can be computed
 * as (the data rate is multiplied by 2 to convert from pixels per second to
 * bytes per second)
 *
 * request per second = data rate * 2 / 256
 * cycles per request = cycles per second / requests per second
 *
 * The number of cycles per second is controlled by the L3 घड़ी, leading to
 *
 * cycles per request = L3 frequency / 2 * 256 / data rate
 */
अटल व्योम resizer_adjust_bandwidth(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&res->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(res);
	अचिन्हित दीर्घ l3_ick = pipe->l3_ick;
	काष्ठा v4l2_fract *समयperframe;
	अचिन्हित पूर्णांक cycles_per_frame;
	अचिन्हित पूर्णांक requests_per_frame;
	अचिन्हित पूर्णांक cycles_per_request;
	अचिन्हित पूर्णांक granularity;
	अचिन्हित पूर्णांक minimum;
	अचिन्हित पूर्णांक maximum;
	अचिन्हित पूर्णांक value;

	अगर (res->input != RESIZER_INPUT_MEMORY) अणु
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_SDR_REQ_EXP,
			    ISPSBL_SDR_REQ_RSZ_EXP_MASK);
		वापस;
	पूर्ण

	चयन (isp->revision) अणु
	हाल ISP_REVISION_1_0:
	हाल ISP_REVISION_2_0:
	शेष:
		granularity = 1024;
		अवरोध;

	हाल ISP_REVISION_15_0:
		granularity = 32;
		अवरोध;
	पूर्ण

	/* Compute the minimum number of cycles per request, based on the
	 * pipeline maximum data rate. This is an असलolute lower bound अगर we
	 * करोn't want SBL overflows, so round the value up.
	 */
	cycles_per_request = भाग_u64((u64)l3_ick / 2 * 256 + pipe->max_rate - 1,
				     pipe->max_rate);
	minimum = DIV_ROUND_UP(cycles_per_request, granularity);

	/* Compute the maximum number of cycles per request, based on the
	 * requested frame rate. This is a soft upper bound to achieve a frame
	 * rate equal or higher than the requested value, so round the value
	 * करोwn.
	 */
	समयperframe = &pipe->max_समयperframe;

	requests_per_frame = DIV_ROUND_UP(res->crop.active.width * 2, 256)
			   * res->crop.active.height;
	cycles_per_frame = भाग_u64((u64)l3_ick * समयperframe->numerator,
				   समयperframe->denominator);
	cycles_per_request = cycles_per_frame / requests_per_frame;

	maximum = cycles_per_request / granularity;

	value = max(minimum, maximum);

	dev_dbg(isp->dev, "%s: cycles per request = %u\n", __func__, value);
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_SDR_REQ_EXP,
			ISPSBL_SDR_REQ_RSZ_EXP_MASK,
			value << ISPSBL_SDR_REQ_RSZ_EXP_SHIFT);
पूर्ण

/*
 * omap3isp_resizer_busy - Checks अगर ISP resizer is busy.
 *
 * Returns busy field from ISPRSZ_PCR रेजिस्टर.
 */
पूर्णांक omap3isp_resizer_busy(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	वापस isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_PCR) &
			     ISPRSZ_PCR_BUSY;
पूर्ण

/*
 * resizer_set_inaddr - Sets the memory address of the input frame.
 * @addr: 32bit memory address aligned on 32byte boundary.
 */
अटल व्योम resizer_set_inaddr(काष्ठा isp_res_device *res, u32 addr)
अणु
	res->addr_base = addr;

	/* This will handle crop settings in stream off state */
	अगर (res->crop_offset)
		addr += res->crop_offset & ~0x1f;

	__resizer_set_inaddr(res, addr);
पूर्ण

/*
 * Configures the memory address to which the output frame is written.
 * @addr: 32bit memory address aligned on 32byte boundary.
 * Note: For SBL efficiency reasons the address should be on a 256-byte
 * boundary.
 */
अटल व्योम resizer_set_outaddr(काष्ठा isp_res_device *res, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	/*
	 * Set output address. This needs to be in its own function
	 * because it changes often.
	 */
	isp_reg_ग_लिखोl(isp, addr << ISPRSZ_SDR_OUTADD_ADDR_SHIFT,
		       OMAP3_ISP_IOMEM_RESZ, ISPRSZ_SDR_OUTADD);
पूर्ण

/*
 * resizer_prपूर्णांक_status - Prपूर्णांकs the values of the resizer module रेजिस्टरs.
 */
#घोषणा RSZ_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###RSZ " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_##name))

अटल व्योम resizer_prपूर्णांक_status(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	dev_dbg(isp->dev, "-------------Resizer Register dump----------\n");

	RSZ_PRINT_REGISTER(isp, PCR);
	RSZ_PRINT_REGISTER(isp, CNT);
	RSZ_PRINT_REGISTER(isp, OUT_SIZE);
	RSZ_PRINT_REGISTER(isp, IN_START);
	RSZ_PRINT_REGISTER(isp, IN_SIZE);
	RSZ_PRINT_REGISTER(isp, SDR_INADD);
	RSZ_PRINT_REGISTER(isp, SDR_INOFF);
	RSZ_PRINT_REGISTER(isp, SDR_OUTADD);
	RSZ_PRINT_REGISTER(isp, SDR_OUTOFF);
	RSZ_PRINT_REGISTER(isp, YENH);

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

/*
 * resizer_calc_ratios - Helper function क्रम calculating resizer ratios
 * @res: poपूर्णांकer to resizer निजी data काष्ठाure
 * @input: input frame size
 * @output: output frame size
 * @ratio : वापस calculated ratios
 * वापस none
 *
 * The resizer uses a polyphase sample rate converter. The upsampling filter
 * has a fixed number of phases that depend on the resizing ratio. As the ratio
 * computation depends on the number of phases, we need to compute a first
 * approximation and then refine it.
 *
 * The input/output/ratio relationship is given by the OMAP34xx TRM:
 *
 * - 8-phase, 4-tap mode (RSZ = 64 ~ 512)
 *	iw = (32 * sph + (ow - 1) * hrsz + 16) >> 8 + 7
 *	ih = (32 * spv + (oh - 1) * vrsz + 16) >> 8 + 4
 * - 4-phase, 7-tap mode (RSZ = 513 ~ 1024)
 *	iw = (64 * sph + (ow - 1) * hrsz + 32) >> 8 + 7
 *	ih = (64 * spv + (oh - 1) * vrsz + 32) >> 8 + 7
 *
 * iw and ih are the input width and height after cropping. Those equations need
 * to be satisfied exactly क्रम the resizer to work correctly.
 *
 * The equations can't be easily reverted, as the >> 8 operation is not linear.
 * In addition, not all input sizes can be achieved क्रम a given output size. To
 * get the highest input size lower than or equal to the requested input size,
 * we need to compute the highest resizing ratio that satisfies the following
 * inequality (taking the 4-tap mode width equation as an example)
 *
 *	iw >= (32 * sph + (ow - 1) * hrsz + 16) >> 8 - 7
 *
 * (where iw is the requested input width) which can be rewritten as
 *
 *	  iw - 7            >= (32 * sph + (ow - 1) * hrsz + 16) >> 8
 *	 (iw - 7) << 8      >=  32 * sph + (ow - 1) * hrsz + 16 - b
 *	((iw - 7) << 8) + b >=  32 * sph + (ow - 1) * hrsz + 16
 *
 * where b is the value of the 8 least signअगरicant bits of the right hand side
 * expression of the last inequality. The highest resizing ratio value will be
 * achieved when b is equal to its maximum value of 255. That resizing ratio
 * value will still satisfy the original inequality, as b will disappear when
 * the expression will be shअगरted right by 8.
 *
 * The reverted equations thus become
 *
 * - 8-phase, 4-tap mode
 *	hrsz = ((iw - 7) * 256 + 255 - 16 - 32 * sph) / (ow - 1)
 *	vrsz = ((ih - 4) * 256 + 255 - 16 - 32 * spv) / (oh - 1)
 * - 4-phase, 7-tap mode
 *	hrsz = ((iw - 7) * 256 + 255 - 32 - 64 * sph) / (ow - 1)
 *	vrsz = ((ih - 7) * 256 + 255 - 32 - 64 * spv) / (oh - 1)
 *
 * The ratios are पूर्णांकeger values, and are rounded करोwn to ensure that the
 * cropped input size is not bigger than the uncropped input size.
 *
 * As the number of phases/taps, used to select the correct equations to compute
 * the ratio, depends on the ratio, we start with the 4-tap mode equations to
 * compute an approximation of the ratio, and चयन to the 7-tap mode equations
 * अगर the approximation is higher than the ratio threshold.
 *
 * As the 7-tap mode equations will वापस a ratio smaller than or equal to the
 * 4-tap mode equations, the resulting ratio could become lower than or equal to
 * the ratio threshold. This 'equations loop' isn't an issue as दीर्घ as the
 * correct equations are used to compute the final input size. Starting with the
 * 4-tap mode equations ensure that, in हाल of values resulting in a 'ratio
 * loop', the smallest of the ratio values will be used, never exceeding the
 * requested input size.
 *
 * We first clamp the output size according to the hardware capability to aव्योम
 * स्वतः-cropping the input more than required to satisfy the TRM equations. The
 * minimum output size is achieved with a scaling factor of 1024. It is thus
 * computed using the 7-tap equations.
 *
 *	min ow = ((iw - 7) * 256 - 32 - 64 * sph) / 1024 + 1
 *	min oh = ((ih - 7) * 256 - 32 - 64 * spv) / 1024 + 1
 *
 * Similarly, the maximum output size is achieved with a scaling factor of 64
 * and computed using the 4-tap equations.
 *
 *	max ow = ((iw - 7) * 256 + 255 - 16 - 32 * sph) / 64 + 1
 *	max oh = ((ih - 4) * 256 + 255 - 16 - 32 * spv) / 64 + 1
 *
 * The additional +255 term compensates क्रम the round करोwn operation perक्रमmed
 * by the TRM equations when shअगरting the value right by 8 bits.
 *
 * We then compute and clamp the ratios (x1/4 ~ x4). Clamping the output size to
 * the maximum value guarantees that the ratio value will never be smaller than
 * the minimum, but it could still slightly exceed the maximum. Clamping the
 * ratio will thus result in a resizing factor slightly larger than the
 * requested value.
 *
 * To accommodate that, and make sure the TRM equations are satisfied exactly, we
 * compute the input crop rectangle as the last step.
 *
 * As अगर the situation wasn't complex enough, the maximum output width depends
 * on the vertical resizing ratio.  Fortunately, the output height करोesn't
 * depend on the horizontal resizing ratio. We can then start by computing the
 * output height and the vertical ratio, and then move to computing the output
 * width and the horizontal ratio.
 */
अटल व्योम resizer_calc_ratios(काष्ठा isp_res_device *res,
				काष्ठा v4l2_rect *input,
				काष्ठा v4l2_mbus_framefmt *output,
				काष्ठा resizer_ratio *ratio)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);
	स्थिर अचिन्हित पूर्णांक spv = DEFAULT_PHASE;
	स्थिर अचिन्हित पूर्णांक sph = DEFAULT_PHASE;
	अचिन्हित पूर्णांक upscaled_width;
	अचिन्हित पूर्णांक upscaled_height;
	अचिन्हित पूर्णांक min_width;
	अचिन्हित पूर्णांक min_height;
	अचिन्हित पूर्णांक max_width;
	अचिन्हित पूर्णांक max_height;
	अचिन्हित पूर्णांक width_alignment;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;

	/*
	 * Clamp the output height based on the hardware capabilities and
	 * compute the vertical resizing ratio.
	 */
	min_height = ((input->height - 7) * 256 - 32 - 64 * spv) / 1024 + 1;
	min_height = max_t(अचिन्हित पूर्णांक, min_height, MIN_OUT_HEIGHT);
	max_height = ((input->height - 4) * 256 + 255 - 16 - 32 * spv) / 64 + 1;
	max_height = min_t(अचिन्हित पूर्णांक, max_height, MAX_OUT_HEIGHT);
	output->height = clamp(output->height, min_height, max_height);

	ratio->vert = ((input->height - 4) * 256 + 255 - 16 - 32 * spv)
		    / (output->height - 1);
	अगर (ratio->vert > MID_RESIZE_VALUE)
		ratio->vert = ((input->height - 7) * 256 + 255 - 32 - 64 * spv)
			    / (output->height - 1);
	ratio->vert = clamp_t(अचिन्हित पूर्णांक, ratio->vert,
			      MIN_RESIZE_VALUE, MAX_RESIZE_VALUE);

	अगर (ratio->vert <= MID_RESIZE_VALUE) अणु
		upscaled_height = (output->height - 1) * ratio->vert
				+ 32 * spv + 16;
		height = (upscaled_height >> 8) + 4;
	पूर्ण अन्यथा अणु
		upscaled_height = (output->height - 1) * ratio->vert
				+ 64 * spv + 32;
		height = (upscaled_height >> 8) + 7;
	पूर्ण

	/*
	 * Compute the minimum and maximum output widths based on the hardware
	 * capabilities. The maximum depends on the vertical resizing ratio.
	 */
	min_width = ((input->width - 7) * 256 - 32 - 64 * sph) / 1024 + 1;
	min_width = max_t(अचिन्हित पूर्णांक, min_width, MIN_OUT_WIDTH);

	अगर (ratio->vert <= MID_RESIZE_VALUE) अणु
		चयन (isp->revision) अणु
		हाल ISP_REVISION_1_0:
			max_width = MAX_4TAP_OUT_WIDTH_ES1;
			अवरोध;

		हाल ISP_REVISION_2_0:
		शेष:
			max_width = MAX_4TAP_OUT_WIDTH_ES2;
			अवरोध;

		हाल ISP_REVISION_15_0:
			max_width = MAX_4TAP_OUT_WIDTH_3630;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (isp->revision) अणु
		हाल ISP_REVISION_1_0:
			max_width = MAX_7TAP_OUT_WIDTH_ES1;
			अवरोध;

		हाल ISP_REVISION_2_0:
		शेष:
			max_width = MAX_7TAP_OUT_WIDTH_ES2;
			अवरोध;

		हाल ISP_REVISION_15_0:
			max_width = MAX_7TAP_OUT_WIDTH_3630;
			अवरोध;
		पूर्ण
	पूर्ण
	max_width = min(((input->width - 7) * 256 + 255 - 16 - 32 * sph) / 64
			+ 1, max_width);

	/*
	 * The output width must be even, and must be a multiple of 16 bytes
	 * when upscaling vertically. Clamp the output width to the valid range.
	 * Take the alignment पूर्णांकo account (the maximum width in 7-tap mode on
	 * ES2 isn't a multiple of 8) and align the result up to make sure it
	 * won't be smaller than the minimum.
	 */
	width_alignment = ratio->vert < 256 ? 8 : 2;
	output->width = clamp(output->width, min_width,
			      max_width & ~(width_alignment - 1));
	output->width = ALIGN(output->width, width_alignment);

	ratio->horz = ((input->width - 7) * 256 + 255 - 16 - 32 * sph)
		    / (output->width - 1);
	अगर (ratio->horz > MID_RESIZE_VALUE)
		ratio->horz = ((input->width - 7) * 256 + 255 - 32 - 64 * sph)
			    / (output->width - 1);
	ratio->horz = clamp_t(अचिन्हित पूर्णांक, ratio->horz,
			      MIN_RESIZE_VALUE, MAX_RESIZE_VALUE);

	अगर (ratio->horz <= MID_RESIZE_VALUE) अणु
		upscaled_width = (output->width - 1) * ratio->horz
			       + 32 * sph + 16;
		width = (upscaled_width >> 8) + 7;
	पूर्ण अन्यथा अणु
		upscaled_width = (output->width - 1) * ratio->horz
			       + 64 * sph + 32;
		width = (upscaled_width >> 8) + 7;
	पूर्ण

	/* Center the new crop rectangle. */
	input->left += (input->width - width) / 2;
	input->top += (input->height - height) / 2;
	input->width = width;
	input->height = height;
पूर्ण

/*
 * resizer_set_crop_params - Setup hardware with cropping parameters
 * @res : resizer निजी काष्ठाure
 * @input : क्रमmat on sink pad
 * @output : क्रमmat on source pad
 * वापस none
 */
अटल व्योम resizer_set_crop_params(काष्ठा isp_res_device *res,
				    स्थिर काष्ठा v4l2_mbus_framefmt *input,
				    स्थिर काष्ठा v4l2_mbus_framefmt *output)
अणु
	resizer_set_ratio(res, &res->ratio);

	/* Set chrominance horizontal algorithm */
	अगर (res->ratपन.सorz >= RESIZE_DIVISOR)
		resizer_set_bilinear(res, RSZ_THE_SAME);
	अन्यथा
		resizer_set_bilinear(res, RSZ_BILINEAR);

	resizer_adjust_bandwidth(res);

	अगर (res->input == RESIZER_INPUT_MEMORY) अणु
		/* Calculate additional offset क्रम crop */
		res->crop_offset = (res->crop.active.top * input->width +
				    res->crop.active.left) * 2;
		/*
		 * Write lowest 4 bits of horizontal pixel offset (in pixels),
		 * vertical start must be 0.
		 */
		resizer_set_start(res, (res->crop_offset / 2) & 0xf, 0);

		/*
		 * Set start (पढ़ो) address क्रम cropping, in bytes.
		 * Lowest 5 bits must be zero.
		 */
		__resizer_set_inaddr(res,
				res->addr_base + (res->crop_offset & ~0x1f));
	पूर्ण अन्यथा अणु
		/*
		 * Set vertical start line and horizontal starting pixel.
		 * If the input is from CCDC/PREV, horizontal start field is
		 * in bytes (twice number of pixels).
		 */
		resizer_set_start(res, res->crop.active.left * 2,
				  res->crop.active.top);
		/* Input address and offset must be 0 क्रम preview/ccdc input */
		__resizer_set_inaddr(res, 0);
		resizer_set_input_offset(res, 0);
	पूर्ण

	/* Set the input size */
	resizer_set_input_size(res, res->crop.active.width,
			       res->crop.active.height);
पूर्ण

अटल व्योम resizer_configure(काष्ठा isp_res_device *res)
अणु
	काष्ठा v4l2_mbus_framefmt *inक्रमmat, *outक्रमmat;
	काष्ठा resizer_luma_yenh luma = अणु0, 0, 0, 0पूर्ण;

	resizer_set_source(res, res->input);

	inक्रमmat = &res->क्रमmats[RESZ_PAD_SINK];
	outक्रमmat = &res->क्रमmats[RESZ_PAD_SOURCE];

	/* RESZ_PAD_SINK */
	अगर (res->input == RESIZER_INPUT_VP)
		resizer_set_input_offset(res, 0);
	अन्यथा
		resizer_set_input_offset(res, ALIGN(inक्रमmat->width, 0x10) * 2);

	/* YUV422 पूर्णांकerleaved, शेष phase, no luma enhancement */
	resizer_set_पूर्णांकype(res, RSZ_YUV422);
	resizer_set_ycpos(res, inक्रमmat->code);
	resizer_set_phase(res, DEFAULT_PHASE, DEFAULT_PHASE);
	resizer_set_luma(res, &luma);

	/* RESZ_PAD_SOURCE */
	resizer_set_output_offset(res, ALIGN(outक्रमmat->width * 2, 32));
	resizer_set_output_size(res, outक्रमmat->width, outक्रमmat->height);

	resizer_set_crop_params(res, inक्रमmat, outक्रमmat);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

अटल व्योम resizer_enable_oneshot(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_PCR,
		    ISPRSZ_PCR_ENABLE | ISPRSZ_PCR_ONESHOT);
पूर्ण

व्योम omap3isp_resizer_isr_frame_sync(काष्ठा isp_res_device *res)
अणु
	/*
	 * If ISP_VIDEO_DMAQUEUE_QUEUED is set, DMA queue had an underrun
	 * condition, the module was छोड़ोd and now we have a buffer queued
	 * on the output again. Restart the pipeline अगर running in continuous
	 * mode.
	 */
	अगर (res->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
	    res->video_out.dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED) अणु
		resizer_enable_oneshot(res);
		isp_video_dmaqueue_flags_clr(&res->video_out);
	पूर्ण
पूर्ण

अटल व्योम resizer_isr_buffer(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&res->subdev.entity);
	काष्ठा isp_buffer *buffer;
	पूर्णांक restart = 0;

	अगर (res->state == ISP_PIPELINE_STREAM_STOPPED)
		वापस;

	/* Complete the output buffer and, अगर पढ़ोing from memory, the input
	 * buffer.
	 */
	buffer = omap3isp_video_buffer_next(&res->video_out);
	अगर (buffer != शून्य) अणु
		resizer_set_outaddr(res, buffer->dma);
		restart = 1;
	पूर्ण

	pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;

	अगर (res->input == RESIZER_INPUT_MEMORY) अणु
		buffer = omap3isp_video_buffer_next(&res->video_in);
		अगर (buffer != शून्य)
			resizer_set_inaddr(res, buffer->dma);
		pipe->state |= ISP_PIPELINE_IDLE_INPUT;
	पूर्ण

	अगर (res->state == ISP_PIPELINE_STREAM_SINGLESHOT) अणु
		अगर (isp_pipeline_पढ़ोy(pipe))
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
	पूर्ण अन्यथा अणु
		/* If an underrun occurs, the video queue operation handler will
		 * restart the resizer. Otherwise restart it immediately.
		 */
		अगर (restart)
			resizer_enable_oneshot(res);
	पूर्ण
पूर्ण

/*
 * omap3isp_resizer_isr - ISP resizer पूर्णांकerrupt handler
 *
 * Manage the resizer video buffers and configure shaकरोwed and busy-locked
 * रेजिस्टरs.
 */
व्योम omap3isp_resizer_isr(काष्ठा isp_res_device *res)
अणु
	काष्ठा v4l2_mbus_framefmt *inक्रमmat, *outक्रमmat;
	अचिन्हित दीर्घ flags;

	अगर (omap3isp_module_sync_is_stopping(&res->रुको, &res->stopping))
		वापस;

	spin_lock_irqsave(&res->lock, flags);

	अगर (res->applycrop) अणु
		outक्रमmat = __resizer_get_क्रमmat(res, शून्य, RESZ_PAD_SOURCE,
					      V4L2_SUBDEV_FORMAT_ACTIVE);
		inक्रमmat = __resizer_get_क्रमmat(res, शून्य, RESZ_PAD_SINK,
					      V4L2_SUBDEV_FORMAT_ACTIVE);
		resizer_set_crop_params(res, inक्रमmat, outक्रमmat);
		res->applycrop = 0;
	पूर्ण

	spin_unlock_irqrestore(&res->lock, flags);

	resizer_isr_buffer(res);
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP video operations
 */

अटल पूर्णांक resizer_video_queue(काष्ठा isp_video *video,
			       काष्ठा isp_buffer *buffer)
अणु
	काष्ठा isp_res_device *res = &video->isp->isp_res;

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		resizer_set_inaddr(res, buffer->dma);

	/*
	 * We now have a buffer queued on the output. Despite what the
	 * TRM says, the resizer can't be restarted immediately.
	 * Enabling it in one shot mode in the middle of a frame (or at
	 * least asynchronously to the frame) results in the output
	 * being shअगरted अक्रमomly left/right and up/करोwn, as अगर the
	 * hardware didn't synchronize itself to the beginning of the
	 * frame correctly.
	 *
	 * Restart the resizer on the next sync पूर्णांकerrupt अगर running in
	 * continuous mode or when starting the stream.
	 */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		resizer_set_outaddr(res, buffer->dma);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isp_video_operations resizer_video_ops = अणु
	.queue = resizer_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

/*
 * resizer_set_stream - Enable/Disable streaming on resizer subdev
 * @sd: ISP resizer V4L2 subdev
 * @enable: 1 == Enable, 0 == Disable
 *
 * The resizer hardware can't be enabled without a memory buffer to ग_लिखो to.
 * As the s_stream operation is called in response to a STREAMON call without
 * any buffer queued yet, just update the state field and वापस immediately.
 * The resizer will be enabled in resizer_video_queue().
 */
अटल पूर्णांक resizer_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा isp_video *video_out = &res->video_out;
	काष्ठा isp_device *isp = to_isp_device(res);
	काष्ठा device *dev = to_device(res);

	अगर (res->state == ISP_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISP_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap3isp_subclk_enable(isp, OMAP3_ISP_SUBCLK_RESIZER);
		resizer_configure(res);
		resizer_prपूर्णांक_status(res);
	पूर्ण

	चयन (enable) अणु
	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_WRITE);
		अगर (video_out->dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED) अणु
			resizer_enable_oneshot(res);
			isp_video_dmaqueue_flags_clr(video_out);
		पूर्ण
		अवरोध;

	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		अगर (res->input == RESIZER_INPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_READ);
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_WRITE);

		resizer_enable_oneshot(res);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		अगर (omap3isp_module_sync_idle(&sd->entity, &res->रुको,
					      &res->stopping))
			dev_dbg(dev, "%s: module stop timeout.\n", sd->name);
		omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_RESIZER_READ |
				OMAP3_ISP_SBL_RESIZER_WRITE);
		omap3isp_subclk_disable(isp, OMAP3_ISP_SUBCLK_RESIZER);
		isp_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण

	res->state = enable;
	वापस 0;
पूर्ण

/*
 * resizer_try_crop - mangles crop parameters.
 */
अटल व्योम resizer_try_crop(स्थिर काष्ठा v4l2_mbus_framefmt *sink,
			     स्थिर काष्ठा v4l2_mbus_framefmt *source,
			     काष्ठा v4l2_rect *crop)
अणु
	स्थिर अचिन्हित पूर्णांक spv = DEFAULT_PHASE;
	स्थिर अचिन्हित पूर्णांक sph = DEFAULT_PHASE;

	/* Crop rectangle is स्थिरrained by the output size so that zoom ratio
	 * cannot exceed +/-4.0.
	 */
	अचिन्हित पूर्णांक min_width =
		((32 * sph + (source->width - 1) * 64 + 16) >> 8) + 7;
	अचिन्हित पूर्णांक min_height =
		((32 * spv + (source->height - 1) * 64 + 16) >> 8) + 4;
	अचिन्हित पूर्णांक max_width =
		((64 * sph + (source->width - 1) * 1024 + 32) >> 8) + 7;
	अचिन्हित पूर्णांक max_height =
		((64 * spv + (source->height - 1) * 1024 + 32) >> 8) + 7;

	crop->width = clamp_t(u32, crop->width, min_width, max_width);
	crop->height = clamp_t(u32, crop->height, min_height, max_height);

	/* Crop can not go beyond of the input rectangle */
	crop->left = clamp_t(u32, crop->left, 0, sink->width - MIN_IN_WIDTH);
	crop->width = clamp_t(u32, crop->width, MIN_IN_WIDTH,
			      sink->width - crop->left);
	crop->top = clamp_t(u32, crop->top, 0, sink->height - MIN_IN_HEIGHT);
	crop->height = clamp_t(u32, crop->height, MIN_IN_HEIGHT,
			       sink->height - crop->top);
पूर्ण

/*
 * resizer_get_selection - Retrieve a selection rectangle on a pad
 * @sd: ISP resizer V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangles are the crop rectangles on the sink pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक resizer_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat_source;
	काष्ठा v4l2_mbus_framefmt *क्रमmat_sink;
	काष्ठा resizer_ratio ratio;

	अगर (sel->pad != RESZ_PAD_SINK)
		वापस -EINVAL;

	क्रमmat_sink = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SINK,
					   sel->which);
	क्रमmat_source = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SOURCE,
					     sel->which);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = पूर्णांक_उच्च;
		sel->r.height = पूर्णांक_उच्च;

		resizer_try_crop(क्रमmat_sink, क्रमmat_source, &sel->r);
		resizer_calc_ratios(res, &sel->r, क्रमmat_source, &ratio);
		अवरोध;

	हाल V4L2_SEL_TGT_CROP:
		sel->r = *__resizer_get_crop(res, cfg, sel->which);
		resizer_calc_ratios(res, &sel->r, क्रमmat_source, &ratio);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * resizer_set_selection - Set a selection rectangle on a pad
 * @sd: ISP resizer V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangle is the actual crop rectangle on the sink pad.
 *
 * FIXME: This function currently behaves as अगर the KEEP_CONFIG selection flag
 * was always set.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक resizer_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा isp_device *isp = to_isp_device(res);
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat_sink;
	काष्ठा v4l2_mbus_framefmt क्रमmat_source;
	काष्ठा resizer_ratio ratio;
	अचिन्हित दीर्घ flags;

	अगर (sel->target != V4L2_SEL_TGT_CROP ||
	    sel->pad != RESZ_PAD_SINK)
		वापस -EINVAL;

	क्रमmat_sink = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SINK,
					   sel->which);
	क्रमmat_source = *__resizer_get_क्रमmat(res, cfg, RESZ_PAD_SOURCE,
					      sel->which);

	dev_dbg(isp->dev, "%s(%s): req %ux%u -> (%d,%d)/%ux%u -> %ux%u\n",
		__func__, sel->which == V4L2_SUBDEV_FORMAT_TRY ? "try" : "act",
		क्रमmat_sink->width, क्रमmat_sink->height,
		sel->r.left, sel->r.top, sel->r.width, sel->r.height,
		क्रमmat_source.width, क्रमmat_source.height);

	/* Clamp the crop rectangle to the bounds, and then mangle it further to
	 * fulfill the TRM equations. Store the clamped but otherwise unmangled
	 * rectangle to aव्योम cropping the input multiple बार: when an
	 * application sets the output क्रमmat, the current crop rectangle is
	 * mangled during crop rectangle computation, which would lead to a new,
	 * smaller input crop rectangle every समय the output size is set अगर we
	 * stored the mangled rectangle.
	 */
	resizer_try_crop(क्रमmat_sink, &क्रमmat_source, &sel->r);
	*__resizer_get_crop(res, cfg, sel->which) = sel->r;
	resizer_calc_ratios(res, &sel->r, &क्रमmat_source, &ratio);

	dev_dbg(isp->dev, "%s(%s): got %ux%u -> (%d,%d)/%ux%u -> %ux%u\n",
		__func__, sel->which == V4L2_SUBDEV_FORMAT_TRY ? "try" : "act",
		क्रमmat_sink->width, क्रमmat_sink->height,
		sel->r.left, sel->r.top, sel->r.width, sel->r.height,
		क्रमmat_source.width, क्रमmat_source.height);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*__resizer_get_क्रमmat(res, cfg, RESZ_PAD_SOURCE, sel->which) =
			क्रमmat_source;
		वापस 0;
	पूर्ण

	/* Update the source क्रमmat, resizing ratios and crop rectangle. If
	 * streaming is on the IRQ handler will reprogram the resizer after the
	 * current frame. We thus we need to protect against race conditions.
	 */
	spin_lock_irqsave(&res->lock, flags);

	*__resizer_get_क्रमmat(res, cfg, RESZ_PAD_SOURCE, sel->which) =
		क्रमmat_source;

	res->ratio = ratio;
	res->crop.active = sel->r;

	अगर (res->state != ISP_PIPELINE_STREAM_STOPPED)
		res->applycrop = 1;

	spin_unlock_irqrestore(&res->lock, flags);

	वापस 0;
पूर्ण

/* resizer pixel क्रमmats */
अटल स्थिर अचिन्हित पूर्णांक resizer_क्रमmats[] = अणु
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
पूर्ण;

अटल अचिन्हित पूर्णांक resizer_max_in_width(काष्ठा isp_res_device *res)
अणु
	काष्ठा isp_device *isp = to_isp_device(res);

	अगर (res->input == RESIZER_INPUT_MEMORY) अणु
		वापस MAX_IN_WIDTH_MEMORY_MODE;
	पूर्ण अन्यथा अणु
		अगर (isp->revision == ISP_REVISION_1_0)
			वापस MAX_IN_WIDTH_ONTHEFLY_MODE_ES1;
		अन्यथा
			वापस MAX_IN_WIDTH_ONTHEFLY_MODE_ES2;
	पूर्ण
पूर्ण

/*
 * resizer_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @res   : ISP resizer device
 * @cfg: V4L2 subdev pad configuration
 * @pad   : pad num
 * @fmt   : poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * @which : wanted subdev क्रमmat
 */
अटल व्योम resizer_try_क्रमmat(काष्ठा isp_res_device *res,
			       काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
			       काष्ठा v4l2_mbus_framefmt *fmt,
			       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा resizer_ratio ratio;
	काष्ठा v4l2_rect crop;

	चयन (pad) अणु
	हाल RESZ_PAD_SINK:
		अगर (fmt->code != MEDIA_BUS_FMT_YUYV8_1X16 &&
		    fmt->code != MEDIA_BUS_FMT_UYVY8_1X16)
			fmt->code = MEDIA_BUS_FMT_YUYV8_1X16;

		fmt->width = clamp_t(u32, fmt->width, MIN_IN_WIDTH,
				     resizer_max_in_width(res));
		fmt->height = clamp_t(u32, fmt->height, MIN_IN_HEIGHT,
				      MAX_IN_HEIGHT);
		अवरोध;

	हाल RESZ_PAD_SOURCE:
		क्रमmat = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SINK, which);
		fmt->code = क्रमmat->code;

		crop = *__resizer_get_crop(res, cfg, which);
		resizer_calc_ratios(res, &crop, fmt, &ratio);
		अवरोध;
	पूर्ण

	fmt->colorspace = V4L2_COLORSPACE_JPEG;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * resizer_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (code->pad == RESZ_PAD_SINK) अणु
		अगर (code->index >= ARRAY_SIZE(resizer_क्रमmats))
			वापस -EINVAL;

		code->code = resizer_क्रमmats[code->index];
	पूर्ण अन्यथा अणु
		अगर (code->index != 0)
			वापस -EINVAL;

		क्रमmat = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SINK,
					      code->which);
		code->code = क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक resizer_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	resizer_try_क्रमmat(res, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	resizer_try_क्रमmat(res, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * resizer_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt   : poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_get_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __resizer_get_क्रमmat(res, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * resizer_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt   : poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_set_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	क्रमmat = __resizer_get_क्रमmat(res, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	resizer_try_क्रमmat(res, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	अगर (fmt->pad == RESZ_PAD_SINK) अणु
		/* reset crop rectangle */
		crop = __resizer_get_crop(res, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->क्रमmat.width;
		crop->height = fmt->क्रमmat.height;

		/* Propagate the क्रमmat from sink to source */
		क्रमmat = __resizer_get_क्रमmat(res, cfg, RESZ_PAD_SOURCE,
					      fmt->which);
		*क्रमmat = fmt->क्रमmat;
		resizer_try_क्रमmat(res, cfg, RESZ_PAD_SOURCE, क्रमmat,
				   fmt->which);
	पूर्ण

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		/* Compute and store the active crop rectangle and resizer
		 * ratios. क्रमmat alपढ़ोy poपूर्णांकs to the source pad active
		 * क्रमmat.
		 */
		res->crop.active = res->crop.request;
		resizer_calc_ratios(res, &res->crop.active, क्रमmat,
				       &res->ratio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक resizer_link_validate(काष्ठा v4l2_subdev *sd,
				 काष्ठा media_link *link,
				 काष्ठा v4l2_subdev_क्रमmat *source_fmt,
				 काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&sd->entity);

	omap3isp_resizer_max_rate(res, &pipe->max_rate);

	वापस v4l2_subdev_link_validate_शेष(sd, link,
						 source_fmt, sink_fmt);
पूर्ण

/*
 * resizer_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP resizer V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक resizer_init_क्रमmats(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = RESZ_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_1X16;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	resizer_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops resizer_v4l2_video_ops = अणु
	.s_stream = resizer_set_stream,
पूर्ण;

/* subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops resizer_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = resizer_क्रमागत_mbus_code,
	.क्रमागत_frame_size = resizer_क्रमागत_frame_size,
	.get_fmt = resizer_get_क्रमmat,
	.set_fmt = resizer_set_क्रमmat,
	.get_selection = resizer_get_selection,
	.set_selection = resizer_set_selection,
	.link_validate = resizer_link_validate,
पूर्ण;

/* subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops resizer_v4l2_ops = अणु
	.video = &resizer_v4l2_video_ops,
	.pad = &resizer_v4l2_pad_ops,
पूर्ण;

/* subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops resizer_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = resizer_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * resizer_link_setup - Setup resizer connections.
 * @entity : Poपूर्णांकer to media entity काष्ठाure
 * @local  : Poपूर्णांकer to local pad array
 * @remote : Poपूर्णांकer to remote pad array
 * @flags  : Link flags
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक resizer_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *local,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा isp_res_device *res = v4l2_get_subdevdata(sd);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल RESZ_PAD_SINK:
		/* पढ़ो from memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (res->input == RESIZER_INPUT_VP)
				वापस -EBUSY;
			res->input = RESIZER_INPUT_MEMORY;
		पूर्ण अन्यथा अणु
			अगर (res->input == RESIZER_INPUT_MEMORY)
				res->input = RESIZER_INPUT_NONE;
		पूर्ण
		अवरोध;

	हाल RESZ_PAD_SINK | 2 << 16:
		/* पढ़ो from ccdc or previewer */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (res->input == RESIZER_INPUT_MEMORY)
				वापस -EBUSY;
			res->input = RESIZER_INPUT_VP;
		पूर्ण अन्यथा अणु
			अगर (res->input == RESIZER_INPUT_VP)
				res->input = RESIZER_INPUT_NONE;
		पूर्ण
		अवरोध;

	हाल RESZ_PAD_SOURCE:
		/* resizer always ग_लिखो to memory */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations resizer_media_ops = अणु
	.link_setup = resizer_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

व्योम omap3isp_resizer_unरेजिस्टर_entities(काष्ठा isp_res_device *res)
अणु
	v4l2_device_unरेजिस्टर_subdev(&res->subdev);
	omap3isp_video_unरेजिस्टर(&res->video_in);
	omap3isp_video_unरेजिस्टर(&res->video_out);
पूर्ण

पूर्णांक omap3isp_resizer_रेजिस्टर_entities(काष्ठा isp_res_device *res,
				       काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	res->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &res->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&res->video_in, vdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&res->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap3isp_resizer_unरेजिस्टर_entities(res);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP resizer initialization and cleanup
 */

/*
 * resizer_init_entities - Initialize resizer subdev and media entity.
 * @res : Poपूर्णांकer to resizer device काष्ठाure
 * वापस -ENOMEM or zero on success
 */
अटल पूर्णांक resizer_init_entities(काष्ठा isp_res_device *res)
अणु
	काष्ठा v4l2_subdev *sd = &res->subdev;
	काष्ठा media_pad *pads = res->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	res->input = RESIZER_INPUT_NONE;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->पूर्णांकernal_ops = &resizer_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP3 ISP resizer", माप(sd->name));
	sd->grp_id = 1 << 16;	/* group ID क्रम isp subdevs */
	v4l2_set_subdevdata(sd, res);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESZ_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[RESZ_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESZ_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	resizer_init_क्रमmats(sd, शून्य);

	res->video_in.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	res->video_in.ops = &resizer_video_ops;
	res->video_in.isp = to_isp_device(res);
	res->video_in.capture_mem = PAGE_ALIGN(4096 * 4096) * 2 * 3;
	res->video_in.bpl_alignment = 32;
	res->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	res->video_out.ops = &resizer_video_ops;
	res->video_out.isp = to_isp_device(res);
	res->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 2 * 3;
	res->video_out.bpl_alignment = 32;

	ret = omap3isp_video_init(&res->video_in, "resizer");
	अगर (ret < 0)
		जाओ error_video_in;

	ret = omap3isp_video_init(&res->video_out, "resizer");
	अगर (ret < 0)
		जाओ error_video_out;

	res->video_out.video.entity.flags |= MEDIA_ENT_FL_DEFAULT;

	वापस 0;

error_video_out:
	omap3isp_video_cleanup(&res->video_in);
error_video_in:
	media_entity_cleanup(&res->subdev.entity);
	वापस ret;
पूर्ण

/*
 * isp_resizer_init - Resizer initialization.
 * @isp : Poपूर्णांकer to ISP device
 * वापस -ENOMEM or zero on success
 */
पूर्णांक omap3isp_resizer_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_res_device *res = &isp->isp_res;

	init_रुकोqueue_head(&res->रुको);
	atomic_set(&res->stopping, 0);
	spin_lock_init(&res->lock);

	वापस resizer_init_entities(res);
पूर्ण

व्योम omap3isp_resizer_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_res_device *res = &isp->isp_res;

	omap3isp_video_cleanup(&res->video_in);
	omap3isp_video_cleanup(&res->video_out);
	media_entity_cleanup(&res->subdev.entity);
पूर्ण
