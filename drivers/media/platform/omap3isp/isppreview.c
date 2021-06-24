<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isppreview.c
 *
 * TI OMAP3 ISP driver - Preview module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "isppreview.h"

/* Default values in Office Fluorescent Light क्रम RGBtoRGB Blending */
अटल स्थिर काष्ठा omap3isp_prev_rgbtorgb flr_rgb2rgb = अणु
	अणु	/* RGB-RGB Matrix */
		अणु0x01E2, 0x0F30, 0x0FEEपूर्ण,
		अणु0x0F9B, 0x01AC, 0x0FB9पूर्ण,
		अणु0x0FE0, 0x0EC0, 0x0260पूर्ण
	पूर्ण,	/* RGB Offset */
	अणु0x0000, 0x0000, 0x0000पूर्ण
पूर्ण;

/* Default values in Office Fluorescent Light क्रम RGB to YUV Conversion*/
अटल स्थिर काष्ठा omap3isp_prev_csc flr_prev_csc = अणु
	अणु	/* CSC Coef Matrix */
		अणु66, 129, 25पूर्ण,
		अणु-38, -75, 112पूर्ण,
		अणु112, -94 , -18पूर्ण
	पूर्ण,	/* CSC Offset */
	अणु0x0, 0x0, 0x0पूर्ण
पूर्ण;

/* Default values in Office Fluorescent Light क्रम CFA Gradient*/
#घोषणा FLR_CFA_GRADTHRS_HORZ	0x28
#घोषणा FLR_CFA_GRADTHRS_VERT	0x28

/* Default values in Office Fluorescent Light क्रम Chroma Suppression*/
#घोषणा FLR_CSUP_GAIN		0x0D
#घोषणा FLR_CSUP_THRES		0xEB

/* Default values in Office Fluorescent Light क्रम Noise Filter*/
#घोषणा FLR_NF_STRGTH		0x03

/* Default values क्रम White Balance */
#घोषणा FLR_WBAL_DGAIN		0x100
#घोषणा FLR_WBAL_COEF		0x20

/* Default values in Office Fluorescent Light क्रम Black Adjusपंचांगent*/
#घोषणा FLR_BLKADJ_BLUE		0x0
#घोषणा FLR_BLKADJ_GREEN	0x0
#घोषणा FLR_BLKADJ_RED		0x0

#घोषणा DEF_DETECT_CORRECT_VAL	0xe

/*
 * Margins and image size limits.
 *
 * The preview engine crops several rows and columns पूर्णांकernally depending on
 * which filters are enabled. To aव्योम क्रमmat changes when the filters are
 * enabled or disabled (which would prevent them from being turned on or off
 * during streaming), the driver assumes all filters that can be configured
 * during streaming are enabled when computing sink crop and source क्रमmat
 * limits.
 *
 * If a filter is disabled, additional cropping is स्वतःmatically added at the
 * preview engine input by the driver to aव्योम overflow at line and frame end.
 * This is completely transparent क्रम applications.
 *
 * Median filter		4 pixels
 * Noise filter,
 * Faulty pixels correction	4 pixels, 4 lines
 * Color suppression		2 pixels
 * or luma enhancement
 * -------------------------------------------------------------
 * Maximum total		10 pixels, 4 lines
 *
 * The color suppression and luma enhancement filters are applied after bayer to
 * YUV conversion. They thus can crop one pixel on the left and one pixel on the
 * right side of the image without changing the color pattern. When both those
 * filters are disabled, the driver must crop the two pixels on the same side of
 * the image to aव्योम changing the bayer pattern. The left margin is thus set to
 * 6 pixels and the right margin to 4 pixels.
 */

#घोषणा PREV_MARGIN_LEFT	6
#घोषणा PREV_MARGIN_RIGHT	4
#घोषणा PREV_MARGIN_TOP		2
#घोषणा PREV_MARGIN_BOTTOM	2

#घोषणा PREV_MIN_IN_WIDTH	64
#घोषणा PREV_MIN_IN_HEIGHT	8
#घोषणा PREV_MAX_IN_HEIGHT	16384

#घोषणा PREV_MIN_OUT_WIDTH		0
#घोषणा PREV_MIN_OUT_HEIGHT		0
#घोषणा PREV_MAX_OUT_WIDTH_REV_1	1280
#घोषणा PREV_MAX_OUT_WIDTH_REV_2	3300
#घोषणा PREV_MAX_OUT_WIDTH_REV_15	4096

/*
 * Coefficient Tables क्रम the submodules in Preview.
 * Array is initialised with the values from.the tables text file.
 */

/*
 * CFA Filter Coefficient Table
 *
 */
अटल u32 cfa_coef_table[4][OMAP3ISP_PREV_CFA_BLK_SIZE] = अणु
#समावेश "cfa_coef_table.h"
पूर्ण;

/*
 * Default Gamma Correction Table - All components
 */
अटल u32 gamma_table[] = अणु
#समावेश "gamma_table.h"
पूर्ण;

/*
 * Noise Filter Threshold table
 */
अटल u32 noise_filter_table[] = अणु
#समावेश "noise_filter_table.h"
पूर्ण;

/*
 * Luminance Enhancement Table
 */
अटल u32 luma_enhance_table[] = अणु
#समावेश "luma_enhance_table.h"
पूर्ण;

/*
 * preview_config_luma_enhancement - Configure the Luminance Enhancement table
 */
अटल व्योम
preview_config_luma_enhancement(काष्ठा isp_prev_device *prev,
				स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_luma *yt = &params->luma;
	अचिन्हित पूर्णांक i;

	isp_reg_ग_लिखोl(isp, ISPPRV_YENH_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	क्रम (i = 0; i < OMAP3ISP_PREV_YENH_TBL_SIZE; i++) अणु
		isp_reg_ग_लिखोl(isp, yt->table[i],
			       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_DATA);
	पूर्ण
पूर्ण

/*
 * preview_enable_luma_enhancement - Enable/disable Luminance Enhancement
 */
अटल व्योम
preview_enable_luma_enhancement(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_YNENHEN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_YNENHEN);
पूर्ण

/*
 * preview_enable_invalaw - Enable/disable Inverse A-Law decompression
 */
अटल व्योम preview_enable_invalaw(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_INVALAW);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_INVALAW);
पूर्ण

/*
 * preview_config_hmed - Configure the Horizontal Median Filter
 */
अटल व्योम preview_config_hmed(काष्ठा isp_prev_device *prev,
				स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_hmed *hmed = &params->hmed;

	isp_reg_ग_लिखोl(isp, (hmed->odddist == 1 ? 0 : ISPPRV_HMED_ODDDIST) |
		       (hmed->evendist == 1 ? 0 : ISPPRV_HMED_EVENDIST) |
		       (hmed->thres << ISPPRV_HMED_THRESHOLD_SHIFT),
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_HMED);
पूर्ण

/*
 * preview_enable_hmed - Enable/disable the Horizontal Median Filter
 */
अटल व्योम preview_enable_hmed(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_HMEDEN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_HMEDEN);
पूर्ण

/*
 * preview_config_cfa - Configure CFA Interpolation क्रम Bayer क्रमmats
 *
 * The CFA table is organised in four blocks, one per Bayer component. The
 * hardware expects blocks to follow the Bayer order of the input data, जबतक
 * the driver stores the table in GRBG order in memory. The blocks need to be
 * reordered to support non-GRBG Bayer patterns.
 */
अटल व्योम preview_config_cfa(काष्ठा isp_prev_device *prev,
			       स्थिर काष्ठा prev_params *params)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cfa_coef_order[4][4] = अणु
		अणु 0, 1, 2, 3 पूर्ण, /* GRBG */
		अणु 1, 0, 3, 2 पूर्ण, /* RGGB */
		अणु 2, 3, 0, 1 पूर्ण, /* BGGR */
		अणु 3, 2, 1, 0 पूर्ण, /* GBRG */
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक *order = cfa_coef_order[prev->params.cfa_order];
	स्थिर काष्ठा omap3isp_prev_cfa *cfa = &params->cfa;
	काष्ठा isp_device *isp = to_isp_device(prev);
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;

	isp_reg_ग_लिखोl(isp,
		(cfa->gradthrs_vert << ISPPRV_CFA_GRADTH_VER_SHIFT) |
		(cfa->gradthrs_horz << ISPPRV_CFA_GRADTH_HOR_SHIFT),
		OMAP3_ISP_IOMEM_PREV, ISPPRV_CFA);

	isp_reg_ग_लिखोl(isp, ISPPRV_CFA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);

	क्रम (i = 0; i < 4; ++i) अणु
		स्थिर __u32 *block = cfa->table[order[i]];

		क्रम (j = 0; j < OMAP3ISP_PREV_CFA_BLK_SIZE; ++j)
			isp_reg_ग_लिखोl(isp, block[j], OMAP3_ISP_IOMEM_PREV,
				       ISPPRV_SET_TBL_DATA);
	पूर्ण
पूर्ण

/*
 * preview_config_chroma_suppression - Configure Chroma Suppression
 */
अटल व्योम
preview_config_chroma_suppression(काष्ठा isp_prev_device *prev,
				  स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_csup *cs = &params->csup;

	isp_reg_ग_लिखोl(isp,
		       cs->gain | (cs->thres << ISPPRV_CSUP_THRES_SHIFT) |
		       (cs->hypf_en << ISPPRV_CSUP_HPYF_SHIFT),
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_CSUP);
पूर्ण

/*
 * preview_enable_chroma_suppression - Enable/disable Chrominance Suppression
 */
अटल व्योम
preview_enable_chroma_suppression(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SUPEN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SUPEN);
पूर्ण

/*
 * preview_config_whitebalance - Configure White Balance parameters
 *
 * Coefficient matrix always with शेष values.
 */
अटल व्योम
preview_config_whitebalance(काष्ठा isp_prev_device *prev,
			    स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_wbal *wbal = &params->wbal;
	u32 val;

	isp_reg_ग_लिखोl(isp, wbal->dgain, OMAP3_ISP_IOMEM_PREV, ISPPRV_WB_DGAIN);

	val = wbal->coef0 << ISPPRV_WBGAIN_COEF0_SHIFT;
	val |= wbal->coef1 << ISPPRV_WBGAIN_COEF1_SHIFT;
	val |= wbal->coef2 << ISPPRV_WBGAIN_COEF2_SHIFT;
	val |= wbal->coef3 << ISPPRV_WBGAIN_COEF3_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_WBGAIN);

	isp_reg_ग_लिखोl(isp,
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N0_0_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N0_1_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N0_2_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N0_3_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N1_0_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N1_1_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N1_2_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N1_3_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N2_0_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N2_1_SHIFT |
		       ISPPRV_WBSEL_COEF0 << ISPPRV_WBSEL_N2_2_SHIFT |
		       ISPPRV_WBSEL_COEF1 << ISPPRV_WBSEL_N2_3_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N3_0_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N3_1_SHIFT |
		       ISPPRV_WBSEL_COEF2 << ISPPRV_WBSEL_N3_2_SHIFT |
		       ISPPRV_WBSEL_COEF3 << ISPPRV_WBSEL_N3_3_SHIFT,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_WBSEL);
पूर्ण

/*
 * preview_config_blkadj - Configure Black Adjusपंचांगent
 */
अटल व्योम
preview_config_blkadj(काष्ठा isp_prev_device *prev,
		      स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_blkadj *blkadj = &params->blkadj;

	isp_reg_ग_लिखोl(isp, (blkadj->blue << ISPPRV_BLKADJOFF_B_SHIFT) |
		       (blkadj->green << ISPPRV_BLKADJOFF_G_SHIFT) |
		       (blkadj->red << ISPPRV_BLKADJOFF_R_SHIFT),
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_BLKADJOFF);
पूर्ण

/*
 * preview_config_rgb_blending - Configure RGB-RGB Blending
 */
अटल व्योम
preview_config_rgb_blending(काष्ठा isp_prev_device *prev,
			    स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_rgbtorgb *rgbrgb = &params->rgb2rgb;
	u32 val;

	val = (rgbrgb->matrix[0][0] & 0xfff) << ISPPRV_RGB_MAT1_MTX_RR_SHIFT;
	val |= (rgbrgb->matrix[0][1] & 0xfff) << ISPPRV_RGB_MAT1_MTX_GR_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_MAT1);

	val = (rgbrgb->matrix[0][2] & 0xfff) << ISPPRV_RGB_MAT2_MTX_BR_SHIFT;
	val |= (rgbrgb->matrix[1][0] & 0xfff) << ISPPRV_RGB_MAT2_MTX_RG_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_MAT2);

	val = (rgbrgb->matrix[1][1] & 0xfff) << ISPPRV_RGB_MAT3_MTX_GG_SHIFT;
	val |= (rgbrgb->matrix[1][2] & 0xfff) << ISPPRV_RGB_MAT3_MTX_BG_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_MAT3);

	val = (rgbrgb->matrix[2][0] & 0xfff) << ISPPRV_RGB_MAT4_MTX_RB_SHIFT;
	val |= (rgbrgb->matrix[2][1] & 0xfff) << ISPPRV_RGB_MAT4_MTX_GB_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_MAT4);

	val = (rgbrgb->matrix[2][2] & 0xfff) << ISPPRV_RGB_MAT5_MTX_BB_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_MAT5);

	val = (rgbrgb->offset[0] & 0x3ff) << ISPPRV_RGB_OFF1_MTX_OFFR_SHIFT;
	val |= (rgbrgb->offset[1] & 0x3ff) << ISPPRV_RGB_OFF1_MTX_OFFG_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_OFF1);

	val = (rgbrgb->offset[2] & 0x3ff) << ISPPRV_RGB_OFF2_MTX_OFFB_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_RGB_OFF2);
पूर्ण

/*
 * preview_config_csc - Configure Color Space Conversion (RGB to YCbYCr)
 */
अटल व्योम
preview_config_csc(काष्ठा isp_prev_device *prev,
		   स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_csc *csc = &params->csc;
	u32 val;

	val = (csc->matrix[0][0] & 0x3ff) << ISPPRV_CSC0_RY_SHIFT;
	val |= (csc->matrix[0][1] & 0x3ff) << ISPPRV_CSC0_GY_SHIFT;
	val |= (csc->matrix[0][2] & 0x3ff) << ISPPRV_CSC0_BY_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC0);

	val = (csc->matrix[1][0] & 0x3ff) << ISPPRV_CSC1_RCB_SHIFT;
	val |= (csc->matrix[1][1] & 0x3ff) << ISPPRV_CSC1_GCB_SHIFT;
	val |= (csc->matrix[1][2] & 0x3ff) << ISPPRV_CSC1_BCB_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC1);

	val = (csc->matrix[2][0] & 0x3ff) << ISPPRV_CSC2_RCR_SHIFT;
	val |= (csc->matrix[2][1] & 0x3ff) << ISPPRV_CSC2_GCR_SHIFT;
	val |= (csc->matrix[2][2] & 0x3ff) << ISPPRV_CSC2_BCR_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC2);

	val = (csc->offset[0] & 0xff) << ISPPRV_CSC_OFFSET_Y_SHIFT;
	val |= (csc->offset[1] & 0xff) << ISPPRV_CSC_OFFSET_CB_SHIFT;
	val |= (csc->offset[2] & 0xff) << ISPPRV_CSC_OFFSET_CR_SHIFT;
	isp_reg_ग_लिखोl(isp, val, OMAP3_ISP_IOMEM_PREV, ISPPRV_CSC_OFFSET);
पूर्ण

/*
 * preview_config_yc_range - Configure the max and min Y and C values
 */
अटल व्योम
preview_config_yc_range(काष्ठा isp_prev_device *prev,
			स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_yclimit *yc = &params->yclimit;

	isp_reg_ग_लिखोl(isp,
		       yc->maxC << ISPPRV_SETUP_YC_MAXC_SHIFT |
		       yc->maxY << ISPPRV_SETUP_YC_MAXY_SHIFT |
		       yc->minC << ISPPRV_SETUP_YC_MINC_SHIFT |
		       yc->minY << ISPPRV_SETUP_YC_MINY_SHIFT,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SETUP_YC);
पूर्ण

/*
 * preview_config_dcor - Configure Couplet Defect Correction
 */
अटल व्योम
preview_config_dcor(काष्ठा isp_prev_device *prev,
		    स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_dcor *dcor = &params->dcor;

	isp_reg_ग_लिखोl(isp, dcor->detect_correct[0],
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_CDC_THR0);
	isp_reg_ग_लिखोl(isp, dcor->detect_correct[1],
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_CDC_THR1);
	isp_reg_ग_लिखोl(isp, dcor->detect_correct[2],
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_CDC_THR2);
	isp_reg_ग_लिखोl(isp, dcor->detect_correct[3],
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_CDC_THR3);
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			ISPPRV_PCR_DCCOUP,
			dcor->couplet_mode_en ? ISPPRV_PCR_DCCOUP : 0);
पूर्ण

/*
 * preview_enable_dcor - Enable/disable Couplet Defect Correction
 */
अटल व्योम preview_enable_dcor(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DCOREN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DCOREN);
पूर्ण

/*
 * preview_enable_drkframe_capture - Enable/disable Dark Frame Capture
 */
अटल व्योम
preview_enable_drkframe_capture(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DRKFCAP);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DRKFCAP);
पूर्ण

/*
 * preview_enable_drkframe - Enable/disable Dark Frame Subtraction
 */
अटल व्योम preview_enable_drkframe(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DRKFEN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_DRKFEN);
पूर्ण

/*
 * preview_config_noisefilter - Configure the Noise Filter
 */
अटल व्योम
preview_config_noisefilter(काष्ठा isp_prev_device *prev,
			   स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_nf *nf = &params->nf;
	अचिन्हित पूर्णांक i;

	isp_reg_ग_लिखोl(isp, nf->spपढ़ो, OMAP3_ISP_IOMEM_PREV, ISPPRV_NF);
	isp_reg_ग_लिखोl(isp, ISPPRV_NF_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	क्रम (i = 0; i < OMAP3ISP_PREV_NF_TBL_SIZE; i++) अणु
		isp_reg_ग_लिखोl(isp, nf->table[i],
			       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_DATA);
	पूर्ण
पूर्ण

/*
 * preview_enable_noisefilter - Enable/disable the Noise Filter
 */
अटल व्योम
preview_enable_noisefilter(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_NFEN);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_NFEN);
पूर्ण

/*
 * preview_config_gammacorrn - Configure the Gamma Correction tables
 */
अटल व्योम
preview_config_gammacorrn(काष्ठा isp_prev_device *prev,
			  स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा omap3isp_prev_gtables *gt = &params->gamma;
	अचिन्हित पूर्णांक i;

	isp_reg_ग_लिखोl(isp, ISPPRV_REDGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	क्रम (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_ग_लिखोl(isp, gt->red[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);

	isp_reg_ग_लिखोl(isp, ISPPRV_GREENGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	क्रम (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_ग_लिखोl(isp, gt->green[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);

	isp_reg_ग_लिखोl(isp, ISPPRV_BLUEGAMMA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);
	क्रम (i = 0; i < OMAP3ISP_PREV_GAMMA_TBL_SIZE; i++)
		isp_reg_ग_लिखोl(isp, gt->blue[i], OMAP3_ISP_IOMEM_PREV,
			       ISPPRV_SET_TBL_DATA);
पूर्ण

/*
 * preview_enable_gammacorrn - Enable/disable Gamma Correction
 *
 * When gamma correction is disabled, the module is bypassed and its output is
 * the 8 MSB of the 10-bit input .
 */
अटल व्योम
preview_enable_gammacorrn(काष्ठा isp_prev_device *prev, bool enable)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	अगर (enable)
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_GAMMA_BYPASS);
	अन्यथा
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_GAMMA_BYPASS);
पूर्ण

/*
 * preview_config_contrast - Configure the Contrast
 *
 * Value should be programmed beक्रमe enabling the module.
 */
अटल व्योम
preview_config_contrast(काष्ठा isp_prev_device *prev,
			स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_CNT_BRT,
			0xff << ISPPRV_CNT_BRT_CNT_SHIFT,
			params->contrast << ISPPRV_CNT_BRT_CNT_SHIFT);
पूर्ण

/*
 * preview_config_brightness - Configure the Brightness
 */
अटल व्योम
preview_config_brightness(काष्ठा isp_prev_device *prev,
			  स्थिर काष्ठा prev_params *params)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_CNT_BRT,
			0xff << ISPPRV_CNT_BRT_BRT_SHIFT,
			params->brightness << ISPPRV_CNT_BRT_BRT_SHIFT);
पूर्ण

/*
 * preview_update_contrast - Updates the contrast.
 * @contrast: Poपूर्णांकer to hold the current programmed contrast value.
 *
 * Value should be programmed beक्रमe enabling the module.
 */
अटल व्योम
preview_update_contrast(काष्ठा isp_prev_device *prev, u8 contrast)
अणु
	काष्ठा prev_params *params;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prev->params.lock, flags);
	params = (prev->params.active & OMAP3ISP_PREV_CONTRAST)
	       ? &prev->params.params[0] : &prev->params.params[1];

	अगर (params->contrast != (contrast * ISPPRV_CONTRAST_UNITS)) अणु
		params->contrast = contrast * ISPPRV_CONTRAST_UNITS;
		params->update |= OMAP3ISP_PREV_CONTRAST;
	पूर्ण
	spin_unlock_irqrestore(&prev->params.lock, flags);
पूर्ण

/*
 * preview_update_brightness - Updates the brightness in preview module.
 * @brightness: Poपूर्णांकer to hold the current programmed brightness value.
 *
 */
अटल व्योम
preview_update_brightness(काष्ठा isp_prev_device *prev, u8 brightness)
अणु
	काष्ठा prev_params *params;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prev->params.lock, flags);
	params = (prev->params.active & OMAP3ISP_PREV_BRIGHTNESS)
	       ? &prev->params.params[0] : &prev->params.params[1];

	अगर (params->brightness != (brightness * ISPPRV_BRIGHT_UNITS)) अणु
		params->brightness = brightness * ISPPRV_BRIGHT_UNITS;
		params->update |= OMAP3ISP_PREV_BRIGHTNESS;
	पूर्ण
	spin_unlock_irqrestore(&prev->params.lock, flags);
पूर्ण

अटल u32
preview_params_lock(काष्ठा isp_prev_device *prev, u32 update, bool shaकरोw)
अणु
	u32 active = prev->params.active;

	अगर (shaकरोw) अणु
		/* Mark all shaकरोw parameters we are going to touch as busy. */
		prev->params.params[0].busy |= ~active & update;
		prev->params.params[1].busy |= active & update;
	पूर्ण अन्यथा अणु
		/* Mark all active parameters we are going to touch as busy. */
		update = (prev->params.params[0].update & active)
		       | (prev->params.params[1].update & ~active);

		prev->params.params[0].busy |= active & update;
		prev->params.params[1].busy |= ~active & update;
	पूर्ण

	वापस update;
पूर्ण

अटल व्योम
preview_params_unlock(काष्ठा isp_prev_device *prev, u32 update, bool shaकरोw)
अणु
	u32 active = prev->params.active;

	अगर (shaकरोw) अणु
		/* Set the update flag क्रम shaकरोw parameters that have been
		 * updated and clear the busy flag क्रम all shaकरोw parameters.
		 */
		prev->params.params[0].update |= (~active & update);
		prev->params.params[1].update |= (active & update);
		prev->params.params[0].busy &= active;
		prev->params.params[1].busy &= ~active;
	पूर्ण अन्यथा अणु
		/* Clear the update flag क्रम active parameters that have been
		 * applied and the busy flag क्रम all active parameters.
		 */
		prev->params.params[0].update &= ~(active & update);
		prev->params.params[1].update &= ~(~active & update);
		prev->params.params[0].busy &= ~active;
		prev->params.params[1].busy &= active;
	पूर्ण
पूर्ण

अटल व्योम preview_params_चयन(काष्ठा isp_prev_device *prev)
अणु
	u32 to_चयन;

	/* Switch active parameters with updated shaकरोw parameters when the
	 * shaकरोw parameter has been updated and neither the active not the
	 * shaकरोw parameter is busy.
	 */
	to_चयन = (prev->params.params[0].update & ~prev->params.active)
		  | (prev->params.params[1].update & prev->params.active);
	to_चयन &= ~(prev->params.params[0].busy |
		       prev->params.params[1].busy);
	अगर (to_चयन == 0)
		वापस;

	prev->params.active ^= to_चयन;

	/* Remove the update flag क्रम the shaकरोw copy of parameters we have
	 * चयनed.
	 */
	prev->params.params[0].update &= ~(~prev->params.active & to_चयन);
	prev->params.params[1].update &= ~(prev->params.active & to_चयन);
पूर्ण

/* preview parameters update काष्ठाure */
काष्ठा preview_update अणु
	व्योम (*config)(काष्ठा isp_prev_device *, स्थिर काष्ठा prev_params *);
	व्योम (*enable)(काष्ठा isp_prev_device *, bool);
	अचिन्हित पूर्णांक param_offset;
	अचिन्हित पूर्णांक param_size;
	अचिन्हित पूर्णांक config_offset;
	bool skip;
पूर्ण;

/* Keep the array indexed by the OMAP3ISP_PREV_* bit number. */
अटल स्थिर काष्ठा preview_update update_attrs[] = अणु
	/* OMAP3ISP_PREV_LUMAENH */ अणु
		preview_config_luma_enhancement,
		preview_enable_luma_enhancement,
		दुरत्व(काष्ठा prev_params, luma),
		माप_field(काष्ठा prev_params, luma),
		दुरत्व(काष्ठा omap3isp_prev_update_config, luma),
	पूर्ण, /* OMAP3ISP_PREV_INVALAW */ अणु
		शून्य,
		preview_enable_invalaw,
	पूर्ण, /* OMAP3ISP_PREV_HRZ_MED */ अणु
		preview_config_hmed,
		preview_enable_hmed,
		दुरत्व(काष्ठा prev_params, hmed),
		माप_field(काष्ठा prev_params, hmed),
		दुरत्व(काष्ठा omap3isp_prev_update_config, hmed),
	पूर्ण, /* OMAP3ISP_PREV_CFA */ अणु
		preview_config_cfa,
		शून्य,
		दुरत्व(काष्ठा prev_params, cfa),
		माप_field(काष्ठा prev_params, cfa),
		दुरत्व(काष्ठा omap3isp_prev_update_config, cfa),
	पूर्ण, /* OMAP3ISP_PREV_CHROMA_SUPP */ अणु
		preview_config_chroma_suppression,
		preview_enable_chroma_suppression,
		दुरत्व(काष्ठा prev_params, csup),
		माप_field(काष्ठा prev_params, csup),
		दुरत्व(काष्ठा omap3isp_prev_update_config, csup),
	पूर्ण, /* OMAP3ISP_PREV_WB */ अणु
		preview_config_whitebalance,
		शून्य,
		दुरत्व(काष्ठा prev_params, wbal),
		माप_field(काष्ठा prev_params, wbal),
		दुरत्व(काष्ठा omap3isp_prev_update_config, wbal),
	पूर्ण, /* OMAP3ISP_PREV_BLKADJ */ अणु
		preview_config_blkadj,
		शून्य,
		दुरत्व(काष्ठा prev_params, blkadj),
		माप_field(काष्ठा prev_params, blkadj),
		दुरत्व(काष्ठा omap3isp_prev_update_config, blkadj),
	पूर्ण, /* OMAP3ISP_PREV_RGB2RGB */ अणु
		preview_config_rgb_blending,
		शून्य,
		दुरत्व(काष्ठा prev_params, rgb2rgb),
		माप_field(काष्ठा prev_params, rgb2rgb),
		दुरत्व(काष्ठा omap3isp_prev_update_config, rgb2rgb),
	पूर्ण, /* OMAP3ISP_PREV_COLOR_CONV */ अणु
		preview_config_csc,
		शून्य,
		दुरत्व(काष्ठा prev_params, csc),
		माप_field(काष्ठा prev_params, csc),
		दुरत्व(काष्ठा omap3isp_prev_update_config, csc),
	पूर्ण, /* OMAP3ISP_PREV_YC_LIMIT */ अणु
		preview_config_yc_range,
		शून्य,
		दुरत्व(काष्ठा prev_params, yclimit),
		माप_field(काष्ठा prev_params, yclimit),
		दुरत्व(काष्ठा omap3isp_prev_update_config, yclimit),
	पूर्ण, /* OMAP3ISP_PREV_DEFECT_COR */ अणु
		preview_config_dcor,
		preview_enable_dcor,
		दुरत्व(काष्ठा prev_params, dcor),
		माप_field(काष्ठा prev_params, dcor),
		दुरत्व(काष्ठा omap3isp_prev_update_config, dcor),
	पूर्ण, /* Previously OMAP3ISP_PREV_GAMMABYPASS, not used anymore */ अणु
		शून्य,
		शून्य,
	पूर्ण, /* OMAP3ISP_PREV_DRK_FRM_CAPTURE */ अणु
		शून्य,
		preview_enable_drkframe_capture,
	पूर्ण, /* OMAP3ISP_PREV_DRK_FRM_SUBTRACT */ अणु
		शून्य,
		preview_enable_drkframe,
	पूर्ण, /* OMAP3ISP_PREV_LENS_SHADING */ अणु
		शून्य,
		preview_enable_drkframe,
	पूर्ण, /* OMAP3ISP_PREV_NF */ अणु
		preview_config_noisefilter,
		preview_enable_noisefilter,
		दुरत्व(काष्ठा prev_params, nf),
		माप_field(काष्ठा prev_params, nf),
		दुरत्व(काष्ठा omap3isp_prev_update_config, nf),
	पूर्ण, /* OMAP3ISP_PREV_GAMMA */ अणु
		preview_config_gammacorrn,
		preview_enable_gammacorrn,
		दुरत्व(काष्ठा prev_params, gamma),
		माप_field(काष्ठा prev_params, gamma),
		दुरत्व(काष्ठा omap3isp_prev_update_config, gamma),
	पूर्ण, /* OMAP3ISP_PREV_CONTRAST */ अणु
		preview_config_contrast,
		शून्य,
		0, 0, 0, true,
	पूर्ण, /* OMAP3ISP_PREV_BRIGHTNESS */ अणु
		preview_config_brightness,
		शून्य,
		0, 0, 0, true,
	पूर्ण,
पूर्ण;

/*
 * preview_config - Copy and update local काष्ठाure with userspace preview
 *                  configuration.
 * @prev: ISP preview engine
 * @cfg: Configuration
 *
 * Return zero अगर success or -EFAULT अगर the configuration can't be copied from
 * userspace.
 */
अटल पूर्णांक preview_config(काष्ठा isp_prev_device *prev,
			  काष्ठा omap3isp_prev_update_config *cfg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक rval = 0;
	u32 update;
	u32 active;

	अगर (cfg->update == 0)
		वापस 0;

	/* Mark the shaकरोw parameters we're going to update as busy. */
	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_lock(prev, cfg->update, true);
	active = prev->params.active;
	spin_unlock_irqrestore(&prev->params.lock, flags);

	update = 0;

	क्रम (i = 0; i < ARRAY_SIZE(update_attrs); i++) अणु
		स्थिर काष्ठा preview_update *attr = &update_attrs[i];
		काष्ठा prev_params *params;
		अचिन्हित पूर्णांक bit = 1 << i;

		अगर (attr->skip || !(cfg->update & bit))
			जारी;

		params = &prev->params.params[!!(active & bit)];

		अगर (cfg->flag & bit) अणु
			व्योम __user *from = *(व्योम __user **)
				((व्योम *)cfg + attr->config_offset);
			व्योम *to = (व्योम *)params + attr->param_offset;
			माप_प्रकार size = attr->param_size;

			अगर (to && from && size) अणु
				अगर (copy_from_user(to, from, size)) अणु
					rval = -EFAULT;
					अवरोध;
				पूर्ण
			पूर्ण
			params->features |= bit;
		पूर्ण अन्यथा अणु
			params->features &= ~bit;
		पूर्ण

		update |= bit;
	पूर्ण

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_unlock(prev, update, true);
	preview_params_चयन(prev);
	spin_unlock_irqrestore(&prev->params.lock, flags);

	वापस rval;
पूर्ण

/*
 * preview_setup_hw - Setup preview रेजिस्टरs and/or पूर्णांकernal memory
 * @prev: poपूर्णांकer to preview निजी काष्ठाure
 * @update: Biपंचांगask of parameters to setup
 * @active: Biपंचांगask of parameters active in set 0
 * Note: can be called from पूर्णांकerrupt context
 * Return none
 */
अटल व्योम preview_setup_hw(काष्ठा isp_prev_device *prev, u32 update,
			     u32 active)
अणु
	अचिन्हित पूर्णांक i;

	अगर (update == 0)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(update_attrs); i++) अणु
		स्थिर काष्ठा preview_update *attr = &update_attrs[i];
		काष्ठा prev_params *params;
		अचिन्हित पूर्णांक bit = 1 << i;

		अगर (!(update & bit))
			जारी;

		params = &prev->params.params[!(active & bit)];

		अगर (params->features & bit) अणु
			अगर (attr->config)
				attr->config(prev, params);
			अगर (attr->enable)
				attr->enable(prev, true);
		पूर्ण अन्यथा अणु
			अगर (attr->enable)
				attr->enable(prev, false);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * preview_config_ycpos - Configure byte layout of YUV image.
 * @prev: poपूर्णांकer to previewer निजी काष्ठाure
 * @pixelcode: pixel code
 */
अटल व्योम preview_config_ycpos(काष्ठा isp_prev_device *prev, u32 pixelcode)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	क्रमागत preview_ycpos_mode mode;

	चयन (pixelcode) अणु
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		mode = YCPOS_CrYCbY;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		mode = YCPOS_YCrYCb;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			ISPPRV_PCR_YCPOS_CrYCbY,
			mode << ISPPRV_PCR_YCPOS_SHIFT);
पूर्ण

/*
 * preview_config_averager - Enable / disable / configure averager
 * @average: Average value to be configured.
 */
अटल व्योम preview_config_averager(काष्ठा isp_prev_device *prev, u8 average)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_ग_लिखोl(isp, ISPPRV_AVE_EVENDIST_2 << ISPPRV_AVE_EVENDIST_SHIFT |
		       ISPPRV_AVE_ODDDIST_2 << ISPPRV_AVE_ODDDIST_SHIFT |
		       average, OMAP3_ISP_IOMEM_PREV, ISPPRV_AVE);
पूर्ण


/*
 * preview_config_input_क्रमmat - Configure the input क्रमmat
 * @prev: The preview engine
 * @info: Sink pad क्रमmat inक्रमmation
 *
 * Enable and configure CFA पूर्णांकerpolation क्रम Bayer क्रमmats and disable it क्रम
 * greyscale क्रमmats.
 *
 * The CFA table is organised in four blocks, one per Bayer component. The
 * hardware expects blocks to follow the Bayer order of the input data, जबतक
 * the driver stores the table in GRBG order in memory. The blocks need to be
 * reordered to support non-GRBG Bayer patterns.
 */
अटल व्योम preview_config_input_क्रमmat(काष्ठा isp_prev_device *prev,
					स्थिर काष्ठा isp_क्रमmat_info *info)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	काष्ठा prev_params *params;

	अगर (info->width == 8)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_WIDTH);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_WIDTH);

	चयन (info->flavor) अणु
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		prev->params.cfa_order = 0;
		अवरोध;
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		prev->params.cfa_order = 1;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		prev->params.cfa_order = 2;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		prev->params.cfa_order = 3;
		अवरोध;
	शेष:
		/* Disable CFA क्रम non-Bayer क्रमmats. */
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_CFAEN);
		वापस;
	पूर्ण

	isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR, ISPPRV_PCR_CFAEN);
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			ISPPRV_PCR_CFAFMT_MASK, ISPPRV_PCR_CFAFMT_BAYER);

	params = (prev->params.active & OMAP3ISP_PREV_CFA)
	       ? &prev->params.params[0] : &prev->params.params[1];

	preview_config_cfa(prev, params);
पूर्ण

/*
 * preview_config_input_size - Configure the input frame size
 *
 * The preview engine crops several rows and columns पूर्णांकernally depending on
 * which processing blocks are enabled. The driver assumes all those blocks are
 * enabled when reporting source pad क्रमmats to userspace. If this assumption is
 * not true, rows and columns must be manually cropped at the preview engine
 * input to aव्योम overflows at the end of lines and frames.
 *
 * See the explanation at the PREV_MARGIN_* definitions क्रम more details.
 */
अटल व्योम preview_config_input_size(काष्ठा isp_prev_device *prev, u32 active)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat = &prev->क्रमmats[PREV_PAD_SINK];
	काष्ठा isp_device *isp = to_isp_device(prev);
	अचिन्हित पूर्णांक sph = prev->crop.left;
	अचिन्हित पूर्णांक eph = prev->crop.left + prev->crop.width - 1;
	अचिन्हित पूर्णांक slv = prev->crop.top;
	अचिन्हित पूर्णांक elv = prev->crop.top + prev->crop.height - 1;
	u32 features;

	अगर (क्रमmat->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    क्रमmat->code != MEDIA_BUS_FMT_Y10_1X10) अणु
		sph -= 2;
		eph += 2;
		slv -= 2;
		elv += 2;
	पूर्ण

	features = (prev->params.params[0].features & active)
		 | (prev->params.params[1].features & ~active);

	अगर (features & (OMAP3ISP_PREV_DEFECT_COR | OMAP3ISP_PREV_NF)) अणु
		sph -= 2;
		eph += 2;
		slv -= 2;
		elv += 2;
	पूर्ण
	अगर (features & OMAP3ISP_PREV_HRZ_MED) अणु
		sph -= 2;
		eph += 2;
	पूर्ण
	अगर (features & (OMAP3ISP_PREV_CHROMA_SUPP | OMAP3ISP_PREV_LUMAENH))
		sph -= 2;

	isp_reg_ग_लिखोl(isp, (sph << ISPPRV_HORZ_INFO_SPH_SHIFT) | eph,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_HORZ_INFO);
	isp_reg_ग_लिखोl(isp, (slv << ISPPRV_VERT_INFO_SLV_SHIFT) | elv,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_VERT_INFO);
पूर्ण

/*
 * preview_config_अंतरभूतoffset - Configures the Read address line offset.
 * @prev: Preview module
 * @offset: Line offset
 *
 * According to the TRM, the line offset must be aligned on a 32 bytes boundary.
 * However, a hardware bug requires the memory start address to be aligned on a
 * 64 bytes boundary, so the offset probably should be aligned on 64 bytes as
 * well.
 */
अटल व्योम
preview_config_अंतरभूतoffset(काष्ठा isp_prev_device *prev, u32 offset)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_ग_लिखोl(isp, offset & 0xffff, OMAP3_ISP_IOMEM_PREV,
		       ISPPRV_RADR_OFFSET);
पूर्ण

/*
 * preview_set_inaddr - Sets memory address of input frame.
 * @addr: 32bit memory address aligned on 32byte boundary.
 *
 * Configures the memory address from which the input frame is to be पढ़ो.
 */
अटल व्योम preview_set_inaddr(काष्ठा isp_prev_device *prev, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_ग_लिखोl(isp, addr, OMAP3_ISP_IOMEM_PREV, ISPPRV_RSDR_ADDR);
पूर्ण

/*
 * preview_config_outlineoffset - Configures the Write address line offset.
 * @offset: Line Offset क्रम the preview output.
 *
 * The offset must be a multiple of 32 bytes.
 */
अटल व्योम preview_config_outlineoffset(काष्ठा isp_prev_device *prev,
				    u32 offset)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_ग_लिखोl(isp, offset & 0xffff, OMAP3_ISP_IOMEM_PREV,
		       ISPPRV_WADD_OFFSET);
पूर्ण

/*
 * preview_set_outaddr - Sets the memory address to store output frame
 * @addr: 32bit memory address aligned on 32byte boundary.
 *
 * Configures the memory address to which the output frame is written.
 */
अटल व्योम preview_set_outaddr(काष्ठा isp_prev_device *prev, u32 addr)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	isp_reg_ग_लिखोl(isp, addr, OMAP3_ISP_IOMEM_PREV, ISPPRV_WSDR_ADDR);
पूर्ण

अटल व्योम preview_adjust_bandwidth(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&prev->subdev.entity);
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा v4l2_mbus_framefmt *अगरmt = &prev->क्रमmats[PREV_PAD_SINK];
	अचिन्हित दीर्घ l3_ick = pipe->l3_ick;
	काष्ठा v4l2_fract *समयperframe;
	अचिन्हित पूर्णांक cycles_per_frame;
	अचिन्हित पूर्णांक requests_per_frame;
	अचिन्हित पूर्णांक cycles_per_request;
	अचिन्हित पूर्णांक minimum;
	अचिन्हित पूर्णांक maximum;
	अचिन्हित पूर्णांक value;

	अगर (prev->input != PREVIEW_INPUT_MEMORY) अणु
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_SDR_REQ_EXP,
			    ISPSBL_SDR_REQ_PRV_EXP_MASK);
		वापस;
	पूर्ण

	/* Compute the minimum number of cycles per request, based on the
	 * pipeline maximum data rate. This is an असलolute lower bound अगर we
	 * करोn't want SBL overflows, so round the value up.
	 */
	cycles_per_request = भाग_u64((u64)l3_ick / 2 * 256 + pipe->max_rate - 1,
				     pipe->max_rate);
	minimum = DIV_ROUND_UP(cycles_per_request, 32);

	/* Compute the maximum number of cycles per request, based on the
	 * requested frame rate. This is a soft upper bound to achieve a frame
	 * rate equal or higher than the requested value, so round the value
	 * करोwn.
	 */
	समयperframe = &pipe->max_समयperframe;

	requests_per_frame = DIV_ROUND_UP(अगरmt->width * 2, 256) * अगरmt->height;
	cycles_per_frame = भाग_u64((u64)l3_ick * समयperframe->numerator,
				   समयperframe->denominator);
	cycles_per_request = cycles_per_frame / requests_per_frame;

	maximum = cycles_per_request / 32;

	value = max(minimum, maximum);

	dev_dbg(isp->dev, "%s: cycles per request = %u\n", __func__, value);
	isp_reg_clr_set(isp, OMAP3_ISP_IOMEM_SBL, ISPSBL_SDR_REQ_EXP,
			ISPSBL_SDR_REQ_PRV_EXP_MASK,
			value << ISPSBL_SDR_REQ_PRV_EXP_SHIFT);
पूर्ण

/*
 * omap3isp_preview_busy - Gets busy state of preview module.
 */
पूर्णांक omap3isp_preview_busy(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	वापस isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR)
		& ISPPRV_PCR_BUSY;
पूर्ण

/*
 * omap3isp_preview_restore_context - Restores the values of preview रेजिस्टरs
 */
व्योम omap3isp_preview_restore_context(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_prev_device *prev = &isp->isp_prev;
	स्थिर u32 update = OMAP3ISP_PREV_FEATURES_END - 1;

	prev->params.params[0].update = prev->params.active & update;
	prev->params.params[1].update = ~prev->params.active & update;

	preview_setup_hw(prev, update, prev->params.active);

	prev->params.params[0].update = 0;
	prev->params.params[1].update = 0;
पूर्ण

/*
 * preview_prपूर्णांक_status - Dump preview module रेजिस्टरs to the kernel log
 */
#घोषणा PREV_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###PRV " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_##name))

अटल व्योम preview_prपूर्णांक_status(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	dev_dbg(isp->dev, "-------------Preview Register dump----------\n");

	PREV_PRINT_REGISTER(isp, PCR);
	PREV_PRINT_REGISTER(isp, HORZ_INFO);
	PREV_PRINT_REGISTER(isp, VERT_INFO);
	PREV_PRINT_REGISTER(isp, RSDR_ADDR);
	PREV_PRINT_REGISTER(isp, RADR_OFFSET);
	PREV_PRINT_REGISTER(isp, DSDR_ADDR);
	PREV_PRINT_REGISTER(isp, DRKF_OFFSET);
	PREV_PRINT_REGISTER(isp, WSDR_ADDR);
	PREV_PRINT_REGISTER(isp, WADD_OFFSET);
	PREV_PRINT_REGISTER(isp, AVE);
	PREV_PRINT_REGISTER(isp, HMED);
	PREV_PRINT_REGISTER(isp, NF);
	PREV_PRINT_REGISTER(isp, WB_DGAIN);
	PREV_PRINT_REGISTER(isp, WBGAIN);
	PREV_PRINT_REGISTER(isp, WBSEL);
	PREV_PRINT_REGISTER(isp, CFA);
	PREV_PRINT_REGISTER(isp, BLKADJOFF);
	PREV_PRINT_REGISTER(isp, RGB_MAT1);
	PREV_PRINT_REGISTER(isp, RGB_MAT2);
	PREV_PRINT_REGISTER(isp, RGB_MAT3);
	PREV_PRINT_REGISTER(isp, RGB_MAT4);
	PREV_PRINT_REGISTER(isp, RGB_MAT5);
	PREV_PRINT_REGISTER(isp, RGB_OFF1);
	PREV_PRINT_REGISTER(isp, RGB_OFF2);
	PREV_PRINT_REGISTER(isp, CSC0);
	PREV_PRINT_REGISTER(isp, CSC1);
	PREV_PRINT_REGISTER(isp, CSC2);
	PREV_PRINT_REGISTER(isp, CSC_OFFSET);
	PREV_PRINT_REGISTER(isp, CNT_BRT);
	PREV_PRINT_REGISTER(isp, CSUP);
	PREV_PRINT_REGISTER(isp, SETUP_YC);
	PREV_PRINT_REGISTER(isp, SET_TBL_ADDR);
	PREV_PRINT_REGISTER(isp, CDC_THR0);
	PREV_PRINT_REGISTER(isp, CDC_THR1);
	PREV_PRINT_REGISTER(isp, CDC_THR2);
	PREV_PRINT_REGISTER(isp, CDC_THR3);

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

/*
 * preview_init_params - init image processing parameters.
 * @prev: poपूर्णांकer to previewer निजी काष्ठाure
 */
अटल व्योम preview_init_params(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा prev_params *params;
	अचिन्हित पूर्णांक i;

	spin_lock_init(&prev->params.lock);

	prev->params.active = ~0;
	prev->params.params[0].busy = 0;
	prev->params.params[0].update = OMAP3ISP_PREV_FEATURES_END - 1;
	prev->params.params[1].busy = 0;
	prev->params.params[1].update = 0;

	params = &prev->params.params[0];

	/* Init values */
	params->contrast = ISPPRV_CONTRAST_DEF * ISPPRV_CONTRAST_UNITS;
	params->brightness = ISPPRV_BRIGHT_DEF * ISPPRV_BRIGHT_UNITS;
	params->cfa.क्रमmat = OMAP3ISP_CFAFMT_BAYER;
	स_नकल(params->cfa.table, cfa_coef_table,
	       माप(params->cfa.table));
	params->cfa.gradthrs_horz = FLR_CFA_GRADTHRS_HORZ;
	params->cfa.gradthrs_vert = FLR_CFA_GRADTHRS_VERT;
	params->csup.gain = FLR_CSUP_GAIN;
	params->csup.thres = FLR_CSUP_THRES;
	params->csup.hypf_en = 0;
	स_नकल(params->luma.table, luma_enhance_table,
	       माप(params->luma.table));
	params->nf.spपढ़ो = FLR_NF_STRGTH;
	स_नकल(params->nf.table, noise_filter_table, माप(params->nf.table));
	params->dcor.couplet_mode_en = 1;
	क्रम (i = 0; i < OMAP3ISP_PREV_DETECT_CORRECT_CHANNELS; i++)
		params->dcor.detect_correct[i] = DEF_DETECT_CORRECT_VAL;
	स_नकल(params->gamma.blue, gamma_table, माप(params->gamma.blue));
	स_नकल(params->gamma.green, gamma_table, माप(params->gamma.green));
	स_नकल(params->gamma.red, gamma_table, माप(params->gamma.red));
	params->wbal.dgain = FLR_WBAL_DGAIN;
	params->wbal.coef0 = FLR_WBAL_COEF;
	params->wbal.coef1 = FLR_WBAL_COEF;
	params->wbal.coef2 = FLR_WBAL_COEF;
	params->wbal.coef3 = FLR_WBAL_COEF;
	params->blkadj.red = FLR_BLKADJ_RED;
	params->blkadj.green = FLR_BLKADJ_GREEN;
	params->blkadj.blue = FLR_BLKADJ_BLUE;
	params->rgb2rgb = flr_rgb2rgb;
	params->csc = flr_prev_csc;
	params->yclimit.minC = ISPPRV_YC_MIN;
	params->yclimit.maxC = ISPPRV_YC_MAX;
	params->yclimit.minY = ISPPRV_YC_MIN;
	params->yclimit.maxY = ISPPRV_YC_MAX;

	params->features = OMAP3ISP_PREV_CFA | OMAP3ISP_PREV_DEFECT_COR
			 | OMAP3ISP_PREV_NF | OMAP3ISP_PREV_GAMMA
			 | OMAP3ISP_PREV_BLKADJ | OMAP3ISP_PREV_YC_LIMIT
			 | OMAP3ISP_PREV_RGB2RGB | OMAP3ISP_PREV_COLOR_CONV
			 | OMAP3ISP_PREV_WB | OMAP3ISP_PREV_BRIGHTNESS
			 | OMAP3ISP_PREV_CONTRAST;
पूर्ण

/*
 * preview_max_out_width - Handle previewer hardware output limitations
 * @prev: poपूर्णांकer to previewer निजी काष्ठाure
 * वापसs maximum width output क्रम current isp revision
 */
अटल अचिन्हित पूर्णांक preview_max_out_width(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	चयन (isp->revision) अणु
	हाल ISP_REVISION_1_0:
		वापस PREV_MAX_OUT_WIDTH_REV_1;

	हाल ISP_REVISION_2_0:
	शेष:
		वापस PREV_MAX_OUT_WIDTH_REV_2;

	हाल ISP_REVISION_15_0:
		वापस PREV_MAX_OUT_WIDTH_REV_15;
	पूर्ण
पूर्ण

अटल व्योम preview_configure(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);
	स्थिर काष्ठा isp_क्रमmat_info *info;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित दीर्घ flags;
	u32 update;
	u32 active;

	spin_lock_irqsave(&prev->params.lock, flags);
	/* Mark all active parameters we are going to touch as busy. */
	update = preview_params_lock(prev, 0, false);
	active = prev->params.active;
	spin_unlock_irqrestore(&prev->params.lock, flags);

	/* PREV_PAD_SINK */
	क्रमmat = &prev->क्रमmats[PREV_PAD_SINK];
	info = omap3isp_video_क्रमmat_info(क्रमmat->code);

	preview_adjust_bandwidth(prev);

	preview_config_input_क्रमmat(prev, info);
	preview_config_input_size(prev, active);

	अगर (prev->input == PREVIEW_INPUT_CCDC)
		preview_config_अंतरभूतoffset(prev, 0);
	अन्यथा
		preview_config_अंतरभूतoffset(prev, ALIGN(क्रमmat->width, 0x20) *
					    info->bpp);

	preview_setup_hw(prev, update, active);

	/* PREV_PAD_SOURCE */
	क्रमmat = &prev->क्रमmats[PREV_PAD_SOURCE];

	अगर (prev->output & PREVIEW_OUTPUT_MEMORY)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SDRPORT);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SDRPORT);

	अगर (prev->output & PREVIEW_OUTPUT_RESIZER)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_RSZPORT);
	अन्यथा
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_RSZPORT);

	अगर (prev->output & PREVIEW_OUTPUT_MEMORY)
		preview_config_outlineoffset(prev,
				ALIGN(क्रमmat->width, 0x10) * 2);

	preview_config_averager(prev, 0);
	preview_config_ycpos(prev, क्रमmat->code);

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_unlock(prev, update, false);
	spin_unlock_irqrestore(&prev->params.lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

अटल व्योम preview_enable_oneshot(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_device *isp = to_isp_device(prev);

	/* The PCR.SOURCE bit is स्वतःmatically reset to 0 when the PCR.ENABLE
	 * bit is set. As the preview engine is used in single-shot mode, we
	 * need to set PCR.SOURCE beक्रमe enabling the preview engine.
	 */
	अगर (prev->input == PREVIEW_INPUT_MEMORY)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
			    ISPPRV_PCR_SOURCE);

	isp_reg_set(isp, OMAP3_ISP_IOMEM_PREV, ISPPRV_PCR,
		    ISPPRV_PCR_EN | ISPPRV_PCR_ONESHOT);
पूर्ण

व्योम omap3isp_preview_isr_frame_sync(काष्ठा isp_prev_device *prev)
अणु
	/*
	 * If ISP_VIDEO_DMAQUEUE_QUEUED is set, DMA queue had an underrun
	 * condition, the module was छोड़ोd and now we have a buffer queued
	 * on the output again. Restart the pipeline अगर running in continuous
	 * mode.
	 */
	अगर (prev->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
	    prev->video_out.dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED) अणु
		preview_enable_oneshot(prev);
		isp_video_dmaqueue_flags_clr(&prev->video_out);
	पूर्ण
पूर्ण

अटल व्योम preview_isr_buffer(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&prev->subdev.entity);
	काष्ठा isp_buffer *buffer;
	पूर्णांक restart = 0;

	अगर (prev->output & PREVIEW_OUTPUT_MEMORY) अणु
		buffer = omap3isp_video_buffer_next(&prev->video_out);
		अगर (buffer != शून्य) अणु
			preview_set_outaddr(prev, buffer->dma);
			restart = 1;
		पूर्ण
		pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;
	पूर्ण

	अगर (prev->input == PREVIEW_INPUT_MEMORY) अणु
		buffer = omap3isp_video_buffer_next(&prev->video_in);
		अगर (buffer != शून्य)
			preview_set_inaddr(prev, buffer->dma);
		pipe->state |= ISP_PIPELINE_IDLE_INPUT;
	पूर्ण

	चयन (prev->state) अणु
	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		अगर (isp_pipeline_पढ़ोy(pipe))
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		/* If an underrun occurs, the video queue operation handler will
		 * restart the preview engine. Otherwise restart it immediately.
		 */
		अगर (restart)
			preview_enable_oneshot(prev);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
	शेष:
		वापस;
	पूर्ण
पूर्ण

/*
 * omap3isp_preview_isr - ISP preview engine पूर्णांकerrupt handler
 *
 * Manage the preview engine video buffers and configure shaकरोwed रेजिस्टरs.
 */
व्योम omap3isp_preview_isr(काष्ठा isp_prev_device *prev)
अणु
	अचिन्हित दीर्घ flags;
	u32 update;
	u32 active;

	अगर (omap3isp_module_sync_is_stopping(&prev->रुको, &prev->stopping))
		वापस;

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_चयन(prev);
	update = preview_params_lock(prev, 0, false);
	active = prev->params.active;
	spin_unlock_irqrestore(&prev->params.lock, flags);

	preview_setup_hw(prev, update, active);
	preview_config_input_size(prev, active);

	अगर (prev->input == PREVIEW_INPUT_MEMORY ||
	    prev->output & PREVIEW_OUTPUT_MEMORY)
		preview_isr_buffer(prev);
	अन्यथा अगर (prev->state == ISP_PIPELINE_STREAM_CONTINUOUS)
		preview_enable_oneshot(prev);

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_unlock(prev, update, false);
	spin_unlock_irqrestore(&prev->params.lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP video operations
 */

अटल पूर्णांक preview_video_queue(काष्ठा isp_video *video,
			       काष्ठा isp_buffer *buffer)
अणु
	काष्ठा isp_prev_device *prev = &video->isp->isp_prev;

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		preview_set_inaddr(prev, buffer->dma);

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		preview_set_outaddr(prev, buffer->dma);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isp_video_operations preview_video_ops = अणु
	.queue = preview_video_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

/*
 * preview_s_ctrl - Handle set control subdev method
 * @ctrl: poपूर्णांकer to v4l2 control काष्ठाure
 */
अटल पूर्णांक preview_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा isp_prev_device *prev =
		container_of(ctrl->handler, काष्ठा isp_prev_device, ctrls);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		preview_update_brightness(prev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		preview_update_contrast(prev, ctrl->val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops preview_ctrl_ops = अणु
	.s_ctrl = preview_s_ctrl,
पूर्ण;

/*
 * preview_ioctl - Handle preview module निजी ioctl's
 * @sd: poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cmd: configuration command
 * @arg: configuration argument
 * वापस -EINVAL or zero on success
 */
अटल दीर्घ preview_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);

	चयन (cmd) अणु
	हाल VIDIOC_OMAP3ISP_PRV_CFG:
		वापस preview_config(prev, arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

/*
 * preview_set_stream - Enable/Disable streaming on preview subdev
 * @sd    : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @enable: 1 == Enable, 0 == Disable
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक preview_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा isp_video *video_out = &prev->video_out;
	काष्ठा isp_device *isp = to_isp_device(prev);
	काष्ठा device *dev = to_device(prev);

	अगर (prev->state == ISP_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISP_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap3isp_subclk_enable(isp, OMAP3_ISP_SUBCLK_PREVIEW);
		preview_configure(prev);
		atomic_set(&prev->stopping, 0);
		preview_prपूर्णांक_status(prev);
	पूर्ण

	चयन (enable) अणु
	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		अगर (prev->output & PREVIEW_OUTPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_PREVIEW_WRITE);

		अगर (video_out->dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED ||
		    !(prev->output & PREVIEW_OUTPUT_MEMORY))
			preview_enable_oneshot(prev);

		isp_video_dmaqueue_flags_clr(video_out);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_SINGLESHOT:
		अगर (prev->input == PREVIEW_INPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_PREVIEW_READ);
		अगर (prev->output & PREVIEW_OUTPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_PREVIEW_WRITE);

		preview_enable_oneshot(prev);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		अगर (omap3isp_module_sync_idle(&sd->entity, &prev->रुको,
					      &prev->stopping))
			dev_dbg(dev, "%s: stop timeout.\n", sd->name);
		omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_PREVIEW_READ);
		omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_PREVIEW_WRITE);
		omap3isp_subclk_disable(isp, OMAP3_ISP_SUBCLK_PREVIEW);
		isp_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण

	prev->state = enable;
	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__preview_get_क्रमmat(काष्ठा isp_prev_device *prev, काष्ठा v4l2_subdev_pad_config *cfg,
		     अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&prev->subdev, cfg, pad);
	अन्यथा
		वापस &prev->क्रमmats[pad];
पूर्ण

अटल काष्ठा v4l2_rect *
__preview_get_crop(काष्ठा isp_prev_device *prev, काष्ठा v4l2_subdev_pad_config *cfg,
		   क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&prev->subdev, cfg, PREV_PAD_SINK);
	अन्यथा
		वापस &prev->crop;
पूर्ण

/* previewer क्रमmat descriptions */
अटल स्थिर अचिन्हित पूर्णांक preview_input_fmts[] = अणु
	MEDIA_BUS_FMT_Y8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_Y10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक preview_output_fmts[] = अणु
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
पूर्ण;

/*
 * preview_try_क्रमmat - Validate a क्रमmat
 * @prev: ISP preview engine
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad number
 * @fmt: क्रमmat to be validated
 * @which: try/active क्रमmat selector
 *
 * Validate and adjust the given क्रमmat क्रम the given pad based on the preview
 * engine limits and the क्रमmat and crop rectangles on other pads.
 */
अटल व्योम preview_try_क्रमmat(काष्ठा isp_prev_device *prev,
			       काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
			       काष्ठा v4l2_mbus_framefmt *fmt,
			       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	u32 pixelcode;
	काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल PREV_PAD_SINK:
		/* When पढ़ोing data from the CCDC, the input size has alपढ़ोy
		 * been mangled by the CCDC output pad so it can be accepted
		 * as-is.
		 *
		 * When पढ़ोing data from memory, clamp the requested width and
		 * height. The TRM करोesn't specअगरy a minimum input height, make
		 * sure we got enough lines to enable the noise filter and color
		 * filter array पूर्णांकerpolation.
		 */
		अगर (prev->input == PREVIEW_INPUT_MEMORY) अणु
			fmt->width = clamp_t(u32, fmt->width, PREV_MIN_IN_WIDTH,
					     preview_max_out_width(prev));
			fmt->height = clamp_t(u32, fmt->height,
					      PREV_MIN_IN_HEIGHT,
					      PREV_MAX_IN_HEIGHT);
		पूर्ण

		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		क्रम (i = 0; i < ARRAY_SIZE(preview_input_fmts); i++) अणु
			अगर (fmt->code == preview_input_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use SGRBG10 as शेष */
		अगर (i >= ARRAY_SIZE(preview_input_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
		अवरोध;

	हाल PREV_PAD_SOURCE:
		pixelcode = fmt->code;
		*fmt = *__preview_get_क्रमmat(prev, cfg, PREV_PAD_SINK, which);

		चयन (pixelcode) अणु
		हाल MEDIA_BUS_FMT_YUYV8_1X16:
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
			fmt->code = pixelcode;
			अवरोध;

		शेष:
			fmt->code = MEDIA_BUS_FMT_YUYV8_1X16;
			अवरोध;
		पूर्ण

		/* The preview module output size is configurable through the
		 * averager (horizontal scaling by 1/1, 1/2, 1/4 or 1/8). This
		 * is not supported yet, hardcode the output size to the crop
		 * rectangle size.
		 */
		crop = __preview_get_crop(prev, cfg, which);
		fmt->width = crop->width;
		fmt->height = crop->height;

		fmt->colorspace = V4L2_COLORSPACE_JPEG;
		अवरोध;
	पूर्ण

	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * preview_try_crop - Validate a crop rectangle
 * @prev: ISP preview engine
 * @sink: क्रमmat on the sink pad
 * @crop: crop rectangle to be validated
 *
 * The preview engine crops lines and columns क्रम its पूर्णांकernal operation,
 * depending on which filters are enabled. Enक्रमce minimum crop margins to
 * handle that transparently क्रम userspace.
 *
 * See the explanation at the PREV_MARGIN_* definitions क्रम more details.
 */
अटल व्योम preview_try_crop(काष्ठा isp_prev_device *prev,
			     स्थिर काष्ठा v4l2_mbus_framefmt *sink,
			     काष्ठा v4l2_rect *crop)
अणु
	अचिन्हित पूर्णांक left = PREV_MARGIN_LEFT;
	अचिन्हित पूर्णांक right = sink->width - PREV_MARGIN_RIGHT;
	अचिन्हित पूर्णांक top = PREV_MARGIN_TOP;
	अचिन्हित पूर्णांक bottom = sink->height - PREV_MARGIN_BOTTOM;

	/* When processing data on-the-fly from the CCDC, at least 2 pixels must
	 * be cropped from the left and right sides of the image. As we करोn't
	 * know which filters will be enabled, increase the left and right
	 * margins by two.
	 */
	अगर (prev->input == PREVIEW_INPUT_CCDC) अणु
		left += 2;
		right -= 2;
	पूर्ण

	/* The CFA filter crops 4 lines and 4 columns in Bayer mode, and 2 lines
	 * and no columns in other modes. Increase the margins based on the sink
	 * क्रमmat.
	 */
	अगर (sink->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    sink->code != MEDIA_BUS_FMT_Y10_1X10) अणु
		left += 2;
		right -= 2;
		top += 2;
		bottom -= 2;
	पूर्ण

	/* Restrict left/top to even values to keep the Bayer pattern. */
	crop->left &= ~1;
	crop->top &= ~1;

	crop->left = clamp_t(u32, crop->left, left, right - PREV_MIN_OUT_WIDTH);
	crop->top = clamp_t(u32, crop->top, top, bottom - PREV_MIN_OUT_HEIGHT);
	crop->width = clamp_t(u32, crop->width, PREV_MIN_OUT_WIDTH,
			      right - crop->left);
	crop->height = clamp_t(u32, crop->height, PREV_MIN_OUT_HEIGHT,
			       bottom - crop->top);
पूर्ण

/*
 * preview_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक preview_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	चयन (code->pad) अणु
	हाल PREV_PAD_SINK:
		अगर (code->index >= ARRAY_SIZE(preview_input_fmts))
			वापस -EINVAL;

		code->code = preview_input_fmts[code->index];
		अवरोध;
	हाल PREV_PAD_SOURCE:
		अगर (code->index >= ARRAY_SIZE(preview_output_fmts))
			वापस -EINVAL;

		code->code = preview_output_fmts[code->index];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक preview_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	preview_try_क्रमmat(prev, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	preview_try_क्रमmat(prev, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * preview_get_selection - Retrieve a selection rectangle on a pad
 * @sd: ISP preview V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangles are the crop rectangles on the sink pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक preview_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (sel->pad != PREV_PAD_SINK)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = पूर्णांक_उच्च;
		sel->r.height = पूर्णांक_उच्च;

		क्रमmat = __preview_get_क्रमmat(prev, cfg, PREV_PAD_SINK,
					      sel->which);
		preview_try_crop(prev, क्रमmat, &sel->r);
		अवरोध;

	हाल V4L2_SEL_TGT_CROP:
		sel->r = *__preview_get_crop(prev, cfg, sel->which);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * preview_set_selection - Set a selection rectangle on a pad
 * @sd: ISP preview V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangle is the actual crop rectangle on the sink pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक preview_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (sel->target != V4L2_SEL_TGT_CROP ||
	    sel->pad != PREV_PAD_SINK)
		वापस -EINVAL;

	/* The crop rectangle can't be changed जबतक streaming. */
	अगर (prev->state != ISP_PIPELINE_STREAM_STOPPED)
		वापस -EBUSY;

	/* Modअगरying the crop rectangle always changes the क्रमmat on the source
	 * pad. If the KEEP_CONFIG flag is set, just वापस the current crop
	 * rectangle.
	 */
	अगर (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) अणु
		sel->r = *__preview_get_crop(prev, cfg, sel->which);
		वापस 0;
	पूर्ण

	क्रमmat = __preview_get_क्रमmat(prev, cfg, PREV_PAD_SINK, sel->which);
	preview_try_crop(prev, क्रमmat, &sel->r);
	*__preview_get_crop(prev, cfg, sel->which) = sel->r;

	/* Update the source क्रमmat. */
	क्रमmat = __preview_get_क्रमmat(prev, cfg, PREV_PAD_SOURCE, sel->which);
	preview_try_क्रमmat(prev, cfg, PREV_PAD_SOURCE, क्रमmat, sel->which);

	वापस 0;
पूर्ण

/*
 * preview_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक preview_get_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __preview_get_क्रमmat(prev, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * preview_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक preview_set_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	क्रमmat = __preview_get_क्रमmat(prev, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	preview_try_क्रमmat(prev, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == PREV_PAD_SINK) अणु
		/* Reset the crop rectangle. */
		crop = __preview_get_crop(prev, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->क्रमmat.width;
		crop->height = fmt->क्रमmat.height;

		preview_try_crop(prev, &fmt->क्रमmat, crop);

		/* Update the source क्रमmat. */
		क्रमmat = __preview_get_क्रमmat(prev, cfg, PREV_PAD_SOURCE,
					      fmt->which);
		preview_try_क्रमmat(prev, cfg, PREV_PAD_SOURCE, क्रमmat,
				   fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * preview_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP preview V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक preview_init_क्रमmats(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = PREV_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	preview_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/* subdev core operations */
अटल स्थिर काष्ठा v4l2_subdev_core_ops preview_v4l2_core_ops = अणु
	.ioctl = preview_ioctl,
पूर्ण;

/* subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops preview_v4l2_video_ops = अणु
	.s_stream = preview_set_stream,
पूर्ण;

/* subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops preview_v4l2_pad_ops = अणु
	.क्रमागत_mbus_code = preview_क्रमागत_mbus_code,
	.क्रमागत_frame_size = preview_क्रमागत_frame_size,
	.get_fmt = preview_get_क्रमmat,
	.set_fmt = preview_set_क्रमmat,
	.get_selection = preview_get_selection,
	.set_selection = preview_set_selection,
पूर्ण;

/* subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops preview_v4l2_ops = अणु
	.core = &preview_v4l2_core_ops,
	.video = &preview_v4l2_video_ops,
	.pad = &preview_v4l2_pad_ops,
पूर्ण;

/* subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops preview_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = preview_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * preview_link_setup - Setup previewer connections.
 * @entity : Poपूर्णांकer to media entity काष्ठाure
 * @local  : Poपूर्णांकer to local pad array
 * @remote : Poपूर्णांकer to remote pad array
 * @flags  : Link flags
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक preview_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *local,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा isp_prev_device *prev = v4l2_get_subdevdata(sd);
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	चयन (index) अणु
	हाल PREV_PAD_SINK:
		/* पढ़ो from memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (prev->input == PREVIEW_INPUT_CCDC)
				वापस -EBUSY;
			prev->input = PREVIEW_INPUT_MEMORY;
		पूर्ण अन्यथा अणु
			अगर (prev->input == PREVIEW_INPUT_MEMORY)
				prev->input = PREVIEW_INPUT_NONE;
		पूर्ण
		अवरोध;

	हाल PREV_PAD_SINK | 2 << 16:
		/* पढ़ो from ccdc */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (prev->input == PREVIEW_INPUT_MEMORY)
				वापस -EBUSY;
			prev->input = PREVIEW_INPUT_CCDC;
		पूर्ण अन्यथा अणु
			अगर (prev->input == PREVIEW_INPUT_CCDC)
				prev->input = PREVIEW_INPUT_NONE;
		पूर्ण
		अवरोध;

	/*
	 * The ISP core करोesn't support pipelines with multiple video outमाला_दो.
	 * Revisit this when it will be implemented, and वापस -EBUSY क्रम now.
	 */

	हाल PREV_PAD_SOURCE:
		/* ग_लिखो to memory */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (prev->output & ~PREVIEW_OUTPUT_MEMORY)
				वापस -EBUSY;
			prev->output |= PREVIEW_OUTPUT_MEMORY;
		पूर्ण अन्यथा अणु
			prev->output &= ~PREVIEW_OUTPUT_MEMORY;
		पूर्ण
		अवरोध;

	हाल PREV_PAD_SOURCE | 2 << 16:
		/* ग_लिखो to resizer */
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (prev->output & ~PREVIEW_OUTPUT_RESIZER)
				वापस -EBUSY;
			prev->output |= PREVIEW_OUTPUT_RESIZER;
		पूर्ण अन्यथा अणु
			prev->output &= ~PREVIEW_OUTPUT_RESIZER;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations preview_media_ops = अणु
	.link_setup = preview_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

व्योम omap3isp_preview_unरेजिस्टर_entities(काष्ठा isp_prev_device *prev)
अणु
	v4l2_device_unरेजिस्टर_subdev(&prev->subdev);
	omap3isp_video_unरेजिस्टर(&prev->video_in);
	omap3isp_video_unरेजिस्टर(&prev->video_out);
पूर्ण

पूर्णांक omap3isp_preview_रेजिस्टर_entities(काष्ठा isp_prev_device *prev,
	काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	prev->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &prev->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&prev->video_in, vdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&prev->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap3isp_preview_unरेजिस्टर_entities(prev);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP previewer initialisation and cleanup
 */

/*
 * preview_init_entities - Initialize subdev and media entity.
 * @prev : Poपूर्णांकer to preview काष्ठाure
 * वापस -ENOMEM or zero on success
 */
अटल पूर्णांक preview_init_entities(काष्ठा isp_prev_device *prev)
अणु
	काष्ठा v4l2_subdev *sd = &prev->subdev;
	काष्ठा media_pad *pads = prev->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	prev->input = PREVIEW_INPUT_NONE;

	v4l2_subdev_init(sd, &preview_v4l2_ops);
	sd->पूर्णांकernal_ops = &preview_v4l2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP3 ISP preview", माप(sd->name));
	sd->grp_id = 1 << 16;	/* group ID क्रम isp subdevs */
	v4l2_set_subdevdata(sd, prev);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	v4l2_ctrl_handler_init(&prev->ctrls, 2);
	v4l2_ctrl_new_std(&prev->ctrls, &preview_ctrl_ops, V4L2_CID_BRIGHTNESS,
			  ISPPRV_BRIGHT_LOW, ISPPRV_BRIGHT_HIGH,
			  ISPPRV_BRIGHT_STEP, ISPPRV_BRIGHT_DEF);
	v4l2_ctrl_new_std(&prev->ctrls, &preview_ctrl_ops, V4L2_CID_CONTRAST,
			  ISPPRV_CONTRAST_LOW, ISPPRV_CONTRAST_HIGH,
			  ISPPRV_CONTRAST_STEP, ISPPRV_CONTRAST_DEF);
	v4l2_ctrl_handler_setup(&prev->ctrls);
	sd->ctrl_handler = &prev->ctrls;

	pads[PREV_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[PREV_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &preview_media_ops;
	ret = media_entity_pads_init(me, PREV_PADS_NUM, pads);
	अगर (ret < 0)
		जाओ error_handler_मुक्त;

	preview_init_क्रमmats(sd, शून्य);

	/* According to the OMAP34xx TRM, video buffers need to be aligned on a
	 * 32 bytes boundary. However, an unकरोcumented hardware bug requires a
	 * 64 bytes boundary at the preview engine input.
	 */
	prev->video_in.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	prev->video_in.ops = &preview_video_ops;
	prev->video_in.isp = to_isp_device(prev);
	prev->video_in.capture_mem = PAGE_ALIGN(4096 * 4096) * 2 * 3;
	prev->video_in.bpl_alignment = 64;
	prev->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	prev->video_out.ops = &preview_video_ops;
	prev->video_out.isp = to_isp_device(prev);
	prev->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 2 * 3;
	prev->video_out.bpl_alignment = 32;

	ret = omap3isp_video_init(&prev->video_in, "preview");
	अगर (ret < 0)
		जाओ error_video_in;

	ret = omap3isp_video_init(&prev->video_out, "preview");
	अगर (ret < 0)
		जाओ error_video_out;

	वापस 0;

error_video_out:
	omap3isp_video_cleanup(&prev->video_in);
error_video_in:
	media_entity_cleanup(&prev->subdev.entity);
error_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(&prev->ctrls);
	वापस ret;
पूर्ण

/*
 * omap3isp_preview_init - Previewer initialization.
 * @isp : Poपूर्णांकer to ISP device
 * वापस -ENOMEM or zero on success
 */
पूर्णांक omap3isp_preview_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_prev_device *prev = &isp->isp_prev;

	init_रुकोqueue_head(&prev->रुको);

	preview_init_params(prev);

	वापस preview_init_entities(prev);
पूर्ण

व्योम omap3isp_preview_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_prev_device *prev = &isp->isp_prev;

	v4l2_ctrl_handler_मुक्त(&prev->ctrls);
	omap3isp_video_cleanup(&prev->video_in);
	omap3isp_video_cleanup(&prev->video_out);
	media_entity_cleanup(&prev->subdev.entity);
पूर्ण
