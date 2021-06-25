<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005-2009 Texas Instruments Inc
 *
 * CCDC hardware module क्रम DM355
 * ------------------------------
 *
 * This module is क्रम configuring DM355 CCD controller of VPFE to capture
 * Raw yuv or Bayer RGB data from a decoder. CCDC has several modules
 * such as Defect Pixel Correction, Color Space Conversion etc to
 * pre-process the Bayer RGB data, beक्रमe writing it to SDRAM.
 *
 * TODO: 1) Raw bayer parameter settings and bayer capture
 *	 2) Split module parameter काष्ठाure to module specअगरic ioctl काष्ठाs
 *	 3) add support क्रम lense shading correction
 *	 4) investigate अगर क्रमागत used क्रम user space type definition
 *	    to be replaced by #घोषणाs or पूर्णांकeger
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <media/davinci/dm355_ccdc.h>
#समावेश <media/davinci/vpss.h>

#समावेश "dm355_ccdc_regs.h"
#समावेश "ccdc_hw_device.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CCDC Driver for DM355");
MODULE_AUTHOR("Texas Instruments");

अटल काष्ठा ccdc_oper_config अणु
	काष्ठा device *dev;
	/* CCDC पूर्णांकerface type */
	क्रमागत vpfe_hw_अगर_type अगर_type;
	/* Raw Bayer configuration */
	काष्ठा ccdc_params_raw bayer;
	/* YCbCr configuration */
	काष्ठा ccdc_params_ycbcr ycbcr;
	/* ccdc base address */
	व्योम __iomem *base_addr;
पूर्ण ccdc_cfg = अणु
	/* Raw configurations */
	.bayer = अणु
		.pix_fmt = CCDC_PIXFMT_RAW,
		.frm_fmt = CCDC_FRMFMT_PROGRESSIVE,
		.win = CCDC_WIN_VGA,
		.fid_pol = VPFE_PINPOL_POSITIVE,
		.vd_pol = VPFE_PINPOL_POSITIVE,
		.hd_pol = VPFE_PINPOL_POSITIVE,
		.gain = अणु
			.r_ye = 256,
			.gb_g = 256,
			.gr_cy = 256,
			.b_mg = 256
		पूर्ण,
		.config_params = अणु
			.datasft = 2,
			.mfilt1 = CCDC_NO_MEDIAN_FILTER1,
			.mfilt2 = CCDC_NO_MEDIAN_FILTER2,
			.alaw = अणु
				.gamma_wd = 2,
			पूर्ण,
			.blk_clamp = अणु
				.sample_pixel = 1,
				.dc_sub = 25
			पूर्ण,
			.col_pat_field0 = अणु
				.olop = CCDC_GREEN_BLUE,
				.olep = CCDC_BLUE,
				.elop = CCDC_RED,
				.elep = CCDC_GREEN_RED
			पूर्ण,
			.col_pat_field1 = अणु
				.olop = CCDC_GREEN_BLUE,
				.olep = CCDC_BLUE,
				.elop = CCDC_RED,
				.elep = CCDC_GREEN_RED
			पूर्ण,
		पूर्ण,
	पूर्ण,
	/* YCbCr configuration */
	.ycbcr = अणु
		.win = CCDC_WIN_PAL,
		.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT,
		.frm_fmt = CCDC_FRMFMT_INTERLACED,
		.fid_pol = VPFE_PINPOL_POSITIVE,
		.vd_pol = VPFE_PINPOL_POSITIVE,
		.hd_pol = VPFE_PINPOL_POSITIVE,
		.bt656_enable = 1,
		.pix_order = CCDC_PIXORDER_CBYCRY,
		.buf_type = CCDC_BUFTYPE_FLD_INTERLEAVED
	पूर्ण,
पूर्ण;


/* Raw Bayer क्रमmats */
अटल u32 ccdc_raw_bayer_pix_क्रमmats[] =
		अणुV4L2_PIX_FMT_SBGGR8, V4L2_PIX_FMT_SBGGR16पूर्ण;

/* Raw YUV क्रमmats */
अटल u32 ccdc_raw_yuv_pix_क्रमmats[] =
		अणुV4L2_PIX_FMT_UYVY, V4L2_PIX_FMT_YUYVपूर्ण;

/* रेजिस्टर access routines */
अटल अंतरभूत u32 regr(u32 offset)
अणु
	वापस __raw_पढ़ोl(ccdc_cfg.base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम regw(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, ccdc_cfg.base_addr + offset);
पूर्ण

अटल व्योम ccdc_enable(पूर्णांक en)
अणु
	अचिन्हित पूर्णांक temp;
	temp = regr(SYNCEN);
	temp &= (~CCDC_SYNCEN_VDHDEN_MASK);
	temp |= (en & CCDC_SYNCEN_VDHDEN_MASK);
	regw(temp, SYNCEN);
पूर्ण

अटल व्योम ccdc_enable_output_to_sdram(पूर्णांक en)
अणु
	अचिन्हित पूर्णांक temp;
	temp = regr(SYNCEN);
	temp &= (~(CCDC_SYNCEN_WEN_MASK));
	temp |= ((en << CCDC_SYNCEN_WEN_SHIFT) & CCDC_SYNCEN_WEN_MASK);
	regw(temp, SYNCEN);
पूर्ण

अटल व्योम ccdc_config_gain_offset(व्योम)
अणु
	/* configure gain */
	regw(ccdc_cfg.bayer.gain.r_ye, RYEGAIN);
	regw(ccdc_cfg.bayer.gain.gr_cy, GRCYGAIN);
	regw(ccdc_cfg.bayer.gain.gb_g, GBGGAIN);
	regw(ccdc_cfg.bayer.gain.b_mg, BMGGAIN);
	/* configure offset */
	regw(ccdc_cfg.bayer.ccdc_offset, OFFSET);
पूर्ण

/*
 * ccdc_restore_शेषs()
 * This function restore घातer on शेषs in the ccdc रेजिस्टरs
 */
अटल पूर्णांक ccdc_restore_शेषs(व्योम)
अणु
	पूर्णांक i;

	dev_dbg(ccdc_cfg.dev, "\nstarting ccdc_restore_defaults...");
	/* set all रेजिस्टरs to zero */
	क्रम (i = 0; i <= CCDC_REG_LAST; i += 4)
		regw(0, i);

	/* now override the values with घातer on शेषs in रेजिस्टरs */
	regw(MODESET_DEFAULT, MODESET);
	/* no culling support */
	regw(CULH_DEFAULT, CULH);
	regw(CULV_DEFAULT, CULV);
	/* Set शेष Gain and Offset */
	ccdc_cfg.bayer.gain.r_ye = GAIN_DEFAULT;
	ccdc_cfg.bayer.gain.gb_g = GAIN_DEFAULT;
	ccdc_cfg.bayer.gain.gr_cy = GAIN_DEFAULT;
	ccdc_cfg.bayer.gain.b_mg = GAIN_DEFAULT;
	ccdc_config_gain_offset();
	regw(OUTCLIP_DEFAULT, OUTCLIP);
	regw(LSCCFG2_DEFAULT, LSCCFG2);
	/* select ccdc input */
	अगर (vpss_select_ccdc_source(VPSS_CCDCIN)) अणु
		dev_dbg(ccdc_cfg.dev, "\ncouldn't select ccdc input source");
		वापस -EFAULT;
	पूर्ण
	/* select ccdc घड़ी */
	अगर (vpss_enable_घड़ी(VPSS_CCDC_CLOCK, 1) < 0) अणु
		dev_dbg(ccdc_cfg.dev, "\ncouldn't enable ccdc clock");
		वापस -EFAULT;
	पूर्ण
	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_restore_defaults...");
	वापस 0;
पूर्ण

अटल पूर्णांक ccdc_खोलो(काष्ठा device *device)
अणु
	वापस ccdc_restore_शेषs();
पूर्ण

अटल पूर्णांक ccdc_बंद(काष्ठा device *device)
अणु
	/* disable घड़ी */
	vpss_enable_घड़ी(VPSS_CCDC_CLOCK, 0);
	/* करो nothing क्रम now */
	वापस 0;
पूर्ण
/*
 * ccdc_setwin()
 * This function will configure the winकरोw size to
 * be capture in CCDC reg.
 */
अटल व्योम ccdc_setwin(काष्ठा v4l2_rect *image_win,
			क्रमागत ccdc_frmfmt frm_fmt, पूर्णांक ppc)
अणु
	पूर्णांक horz_start, horz_nr_pixels;
	पूर्णांक vert_start, vert_nr_lines;
	पूर्णांक mid_img = 0;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_setwin...");

	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, क्रम ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left << (ppc - 1);
	horz_nr_pixels = ((image_win->width) << (ppc - 1)) - 1;

	/* Writing the horizontal info पूर्णांकo the रेजिस्टरs */
	regw(horz_start, SPH);
	regw(horz_nr_pixels, NPH);
	vert_start = image_win->top;

	अगर (frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* Since first line करोesn't have any data */
		vert_start += 1;
		/* configure VDINT0 and VDINT1 */
		regw(vert_start, VDINT0);
	पूर्ण अन्यथा अणु
		/* Since first line करोesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/* configure VDINT0 and VDINT1 */
		mid_img = vert_start + (image_win->height / 2);
		regw(vert_start, VDINT0);
		regw(mid_img, VDINT1);
	पूर्ण
	regw(vert_start & CCDC_START_VER_ONE_MASK, SLV0);
	regw(vert_start & CCDC_START_VER_TWO_MASK, SLV1);
	regw(vert_nr_lines & CCDC_NUM_LINES_VER, NLV);
	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_setwin...");
पूर्ण

/* This function will configure CCDC क्रम YCbCr video capture */
अटल व्योम ccdc_config_ycbcr(व्योम)
अणु
	काष्ठा ccdc_params_ycbcr *params = &ccdc_cfg.ycbcr;
	u32 temp;

	/* first set the CCDC घातer on शेषs values in all रेजिस्टरs */
	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_ycbcr...");
	ccdc_restore_शेषs();

	/* configure pixel क्रमmat & video frame क्रमmat */
	temp = (((params->pix_fmt & CCDC_INPUT_MODE_MASK) <<
		CCDC_INPUT_MODE_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) <<
		CCDC_FRM_FMT_SHIFT));

	/* setup BT.656 sync mode */
	अगर (params->bt656_enable) अणु
		regw(CCDC_REC656IF_BT656_EN, REC656IF);
		/*
		 * configure the FID, VD, HD pin polarity fld,hd pol positive,
		 * vd negative, 8-bit pack mode
		 */
		temp |= CCDC_VD_POL_NEGATIVE;
	पूर्ण अन्यथा अणु		/* y/c बाह्यal sync mode */
		temp |= (((params->fid_pol & CCDC_FID_POL_MASK) <<
			CCDC_FID_POL_SHIFT) |
			((params->hd_pol & CCDC_HD_POL_MASK) <<
			CCDC_HD_POL_SHIFT) |
			((params->vd_pol & CCDC_VD_POL_MASK) <<
			CCDC_VD_POL_SHIFT));
	पूर्ण

	/* pack the data to 8-bit */
	temp |= CCDC_DATA_PACK_ENABLE;

	regw(temp, MODESET);

	/* configure video winकरोw */
	ccdc_setwin(&params->win, params->frm_fmt, 2);

	/* configure the order of y cb cr in SD-RAM */
	temp = (params->pix_order << CCDC_Y8POS_SHIFT);
	temp |= CCDC_LATCH_ON_VSYNC_DISABLE | CCDC_CCDCFG_FIDMD_NO_LATCH_VSYNC;
	regw(temp, CCDCFG);

	/*
	 * configure the horizontal line offset. This is करोne by rounding up
	 * width to a multiple of 16 pixels and multiply by two to account क्रम
	 * y:cb:cr 4:2:2 data
	 */
	regw(((params->win.width * 2 + 31) >> 5), HSIZE);

	/* configure the memory line offset */
	अगर (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED) अणु
		/* two fields are पूर्णांकerleaved in memory */
		regw(CCDC_SDOFST_FIELD_INTERLEAVED, SDOFST);
	पूर्ण

	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_config_ycbcr...\n");
पूर्ण

/*
 * ccdc_config_black_clamp()
 * configure parameters क्रम Optical Black Clamp
 */
अटल व्योम ccdc_config_black_clamp(काष्ठा ccdc_black_clamp *bclamp)
अणु
	u32 val;

	अगर (!bclamp->b_clamp_enable) अणु
		/* configure DCSub */
		regw(bclamp->dc_sub & CCDC_BLK_DC_SUB_MASK, DCSUB);
		regw(0x0000, CLAMP);
		वापस;
	पूर्ण
	/* Enable the Black clamping, set sample lines and pixels */
	val = (bclamp->start_pixel & CCDC_BLK_ST_PXL_MASK) |
	      ((bclamp->sample_pixel & CCDC_BLK_SAMPLE_LN_MASK) <<
		CCDC_BLK_SAMPLE_LN_SHIFT) | CCDC_BLK_CLAMP_ENABLE;
	regw(val, CLAMP);

	/* If Black clamping is enable then make dcsub 0 */
	val = (bclamp->sample_ln & CCDC_NUM_LINE_CALC_MASK)
			<< CCDC_NUM_LINE_CALC_SHIFT;
	regw(val, DCSUB);
पूर्ण

/*
 * ccdc_config_black_compense()
 * configure parameters क्रम Black Compensation
 */
अटल व्योम ccdc_config_black_compense(काष्ठा ccdc_black_compensation *bcomp)
अणु
	u32 val;

	val = (bcomp->b & CCDC_BLK_COMP_MASK) |
		((bcomp->gb & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_GB_COMP_SHIFT);
	regw(val, BLKCMP1);

	val = ((bcomp->gr & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_GR_COMP_SHIFT) |
		((bcomp->r & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_R_COMP_SHIFT);
	regw(val, BLKCMP0);
पूर्ण

/*
 * ccdc_ग_लिखो_dfc_entry()
 * ग_लिखो an entry in the dfc table.
 */
अटल पूर्णांक ccdc_ग_लिखो_dfc_entry(पूर्णांक index, काष्ठा ccdc_vertical_dft *dfc)
अणु
/* TODO This is to be re-visited and adjusted */
#घोषणा DFC_WRITE_WAIT_COUNT	1000
	u32 val, count = DFC_WRITE_WAIT_COUNT;

	regw(dfc->dft_corr_vert[index], DFCMEM0);
	regw(dfc->dft_corr_horz[index], DFCMEM1);
	regw(dfc->dft_corr_sub1[index], DFCMEM2);
	regw(dfc->dft_corr_sub2[index], DFCMEM3);
	regw(dfc->dft_corr_sub3[index], DFCMEM4);
	/* set WR bit to ग_लिखो */
	val = regr(DFCMEMCTL) | CCDC_DFCMEMCTL_DFCMWR_MASK;
	regw(val, DFCMEMCTL);

	/*
	 * Assume, it is very लघु. If we get an error, we need to
	 * adjust this value
	 */
	जबतक (regr(DFCMEMCTL) & CCDC_DFCMEMCTL_DFCMWR_MASK)
		count--;
	/*
	 * TODO We expect the count to be non-zero to be successful. Adjust
	 * the count अगर ग_लिखो requires more समय
	 */

	अगर (count) अणु
		dev_err(ccdc_cfg.dev, "defect table write timeout !!!\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ccdc_config_vdfc()
 * configure parameters क्रम Vertical Defect Correction
 */
अटल पूर्णांक ccdc_config_vdfc(काष्ठा ccdc_vertical_dft *dfc)
अणु
	u32 val;
	पूर्णांक i;

	/* Configure General Defect Correction. The table used is from IPIPE */
	val = dfc->gen_dft_en & CCDC_DFCCTL_GDFCEN_MASK;

	/* Configure Vertical Defect Correction अगर needed */
	अगर (!dfc->ver_dft_en) अणु
		/* Enable only General Defect Correction */
		regw(val, DFCCTL);
		वापस 0;
	पूर्ण

	अगर (dfc->table_size > CCDC_DFT_TABLE_SIZE)
		वापस -EINVAL;

	val |= CCDC_DFCCTL_VDFC_DISABLE;
	val |= (dfc->dft_corr_ctl.vdfcsl & CCDC_DFCCTL_VDFCSL_MASK) <<
		CCDC_DFCCTL_VDFCSL_SHIFT;
	val |= (dfc->dft_corr_ctl.vdfcuda & CCDC_DFCCTL_VDFCUDA_MASK) <<
		CCDC_DFCCTL_VDFCUDA_SHIFT;
	val |= (dfc->dft_corr_ctl.vdflsft & CCDC_DFCCTL_VDFLSFT_MASK) <<
		CCDC_DFCCTL_VDFLSFT_SHIFT;
	regw(val , DFCCTL);

	/* clear address ptr to offset 0 */
	val = CCDC_DFCMEMCTL_DFCMARST_MASK << CCDC_DFCMEMCTL_DFCMARST_SHIFT;

	/* ग_लिखो defect table entries */
	क्रम (i = 0; i < dfc->table_size; i++) अणु
		/* increment address क्रम non zero index */
		अगर (i != 0)
			val = CCDC_DFCMEMCTL_INC_ADDR;
		regw(val, DFCMEMCTL);
		अगर (ccdc_ग_लिखो_dfc_entry(i, dfc) < 0)
			वापस -EFAULT;
	पूर्ण

	/* update saturation level and enable dfc */
	regw(dfc->saturation_ctl & CCDC_VDC_DFCVSAT_MASK, DFCVSAT);
	val = regr(DFCCTL) | (CCDC_DFCCTL_VDFCEN_MASK <<
			CCDC_DFCCTL_VDFCEN_SHIFT);
	regw(val, DFCCTL);
	वापस 0;
पूर्ण

/*
 * ccdc_config_csc()
 * configure parameters क्रम color space conversion
 * Each रेजिस्टर CSCM0-7 has two values in S8Q5 क्रमmat.
 */
अटल व्योम ccdc_config_csc(काष्ठा ccdc_csc *csc)
अणु
	u32 val1 = 0, val2;
	पूर्णांक i;

	अगर (!csc->enable)
		वापस;

	/* Enable the CSC sub-module */
	regw(CCDC_CSC_ENABLE, CSCCTL);

	/* Converting the co-eff as per the क्रमmat of the रेजिस्टर */
	क्रम (i = 0; i < CCDC_CSC_COEFF_TABLE_SIZE; i++) अणु
		अगर ((i % 2) == 0) अणु
			/* CSCM - LSB */
			val1 = (csc->coeff[i].पूर्णांकeger &
				CCDC_CSC_COEF_INTEG_MASK)
				<< CCDC_CSC_COEF_INTEG_SHIFT;
			/*
			 * convert decimal part to binary. Use 2 decimal
			 * precision, user values range from .00 - 0.99
			 */
			val1 |= (((csc->coeff[i].decimal &
				CCDC_CSC_COEF_DECIMAL_MASK) *
				CCDC_CSC_DEC_MAX) / 100);
		पूर्ण अन्यथा अणु

			/* CSCM - MSB */
			val2 = (csc->coeff[i].पूर्णांकeger &
				CCDC_CSC_COEF_INTEG_MASK)
				<< CCDC_CSC_COEF_INTEG_SHIFT;
			val2 |= (((csc->coeff[i].decimal &
				 CCDC_CSC_COEF_DECIMAL_MASK) *
				 CCDC_CSC_DEC_MAX) / 100);
			val2 <<= CCDC_CSCM_MSB_SHIFT;
			val2 |= val1;
			regw(val2, (CSCM0 + ((i - 1) << 1)));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ccdc_config_color_patterns()
 * configure parameters क्रम color patterns
 */
अटल व्योम ccdc_config_color_patterns(काष्ठा ccdc_col_pat *pat0,
				       काष्ठा ccdc_col_pat *pat1)
अणु
	u32 val;

	val = (pat0->olop | (pat0->olep << 2) | (pat0->elop << 4) |
		(pat0->elep << 6) | (pat1->olop << 8) | (pat1->olep << 10) |
		(pat1->elop << 12) | (pat1->elep << 14));
	regw(val, COLPTN);
पूर्ण

/* This function will configure CCDC क्रम Raw mode image capture */
अटल पूर्णांक ccdc_config_raw(व्योम)
अणु
	काष्ठा ccdc_params_raw *params = &ccdc_cfg.bayer;
	काष्ठा ccdc_config_params_raw *config_params =
					&ccdc_cfg.bayer.config_params;
	अचिन्हित पूर्णांक val;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_raw...");

	/* restore घातer on शेषs to रेजिस्टर */
	ccdc_restore_शेषs();

	/* CCDCFG रेजिस्टर:
	 * set CCD Not to swap input since input is RAW data
	 * set FID detection function to Latch at V-Sync
	 * set WENLOG - ccdc valid area to AND
	 * set TRGSEL to WENBIT
	 * set EXTRG to DISABLE
	 * disable latching function on VSYNC - shaकरोwed रेजिस्टरs
	 */
	regw(CCDC_YCINSWP_RAW | CCDC_CCDCFG_FIDMD_LATCH_VSYNC |
	     CCDC_CCDCFG_WENLOG_AND | CCDC_CCDCFG_TRGSEL_WEN |
	     CCDC_CCDCFG_EXTRG_DISABLE | CCDC_LATCH_ON_VSYNC_DISABLE, CCDCFG);

	/*
	 * Set VDHD direction to input,  input type to raw input
	 * normal data polarity, करो not use बाह्यal WEN
	 */
	val = (CCDC_VDHDOUT_INPUT | CCDC_RAW_IP_MODE | CCDC_DATAPOL_NORMAL |
		CCDC_EXWEN_DISABLE);

	/*
	 * Configure the vertical sync polarity (MODESET.VDPOL), horizontal
	 * sync polarity (MODESET.HDPOL), field id polarity (MODESET.FLDPOL),
	 * frame क्रमmat(progressive or पूर्णांकerlace), & pixel क्रमmat (Input mode)
	 */
	val |= (((params->vd_pol & CCDC_VD_POL_MASK) << CCDC_VD_POL_SHIFT) |
		((params->hd_pol & CCDC_HD_POL_MASK) << CCDC_HD_POL_SHIFT) |
		((params->fid_pol & CCDC_FID_POL_MASK) << CCDC_FID_POL_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) << CCDC_FRM_FMT_SHIFT) |
		((params->pix_fmt & CCDC_PIX_FMT_MASK) << CCDC_PIX_FMT_SHIFT));

	/* set pack क्रम alaw compression */
	अगर ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable)
		val |= CCDC_DATA_PACK_ENABLE;

	/* Configure क्रम LPF */
	अगर (config_params->lpf_enable)
		val |= (config_params->lpf_enable & CCDC_LPF_MASK) <<
			CCDC_LPF_SHIFT;

	/* Configure the data shअगरt */
	val |= (config_params->datasft & CCDC_DATASFT_MASK) <<
		CCDC_DATASFT_SHIFT;
	regw(val , MODESET);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to MODESET...\n", val);

	/* Configure the Median Filter threshold */
	regw((config_params->med_filt_thres) & CCDC_MED_FILT_THRESH, MEDFILT);

	/* Configure GAMMAWD रेजिस्टर. defaur 11-2, and Mosaic cfa pattern */
	val = CCDC_GAMMA_BITS_11_2 << CCDC_GAMMAWD_INPUT_SHIFT |
		CCDC_CFA_MOSAIC;

	/* Enable and configure aLaw रेजिस्टर अगर needed */
	अगर (config_params->alaw.enable) अणु
		val |= (CCDC_ALAW_ENABLE |
			((config_params->alaw.gamma_wd &
			CCDC_ALAW_GAMMA_WD_MASK) <<
			CCDC_GAMMAWD_INPUT_SHIFT));
	पूर्ण

	/* Configure Median filter1 & filter2 */
	val |= ((config_params->mfilt1 << CCDC_MFILT1_SHIFT) |
		(config_params->mfilt2 << CCDC_MFILT2_SHIFT));

	regw(val, GAMMAWD);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to GAMMAWD...\n", val);

	/* configure video winकरोw */
	ccdc_setwin(&params->win, params->frm_fmt, 1);

	/* Optical Clamp Averaging */
	ccdc_config_black_clamp(&config_params->blk_clamp);

	/* Black level compensation */
	ccdc_config_black_compense(&config_params->blk_comp);

	/* Vertical Defect Correction अगर needed */
	अगर (ccdc_config_vdfc(&config_params->vertical_dft) < 0)
		वापस -EFAULT;

	/* color space conversion */
	ccdc_config_csc(&config_params->csc);

	/* color pattern */
	ccdc_config_color_patterns(&config_params->col_pat_field0,
				   &config_params->col_pat_field1);

	/* Configure the Gain  & offset control */
	ccdc_config_gain_offset();

	dev_dbg(ccdc_cfg.dev, "\nWriting %x to COLPTN...\n", val);

	/* Configure DATAOFST  रेजिस्टर */
	val = (config_params->data_offset.horz_offset & CCDC_DATAOFST_MASK) <<
		CCDC_DATAOFST_H_SHIFT;
	val |= (config_params->data_offset.vert_offset & CCDC_DATAOFST_MASK) <<
		CCDC_DATAOFST_V_SHIFT;
	regw(val, DATAOFST);

	/* configuring HSIZE रेजिस्टर */
	val = (params->horz_flip_enable & CCDC_HSIZE_FLIP_MASK) <<
		CCDC_HSIZE_FLIP_SHIFT;

	/* If pack 8 is enable then 1 pixel will take 1 byte */
	अगर ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable) अणु
		val |= (((params->win.width) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK;

		/* adjust to multiple of 32 */
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to HSIZE...\n",
		       (((params->win.width) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK);
	पूर्ण अन्यथा अणु
		/* अन्यथा one pixel will take 2 byte */
		val |= (((params->win.width * 2) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK;

		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to HSIZE...\n",
		       (((params->win.width * 2) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK);
	पूर्ण
	regw(val, HSIZE);

	/* Configure SDOFST रेजिस्टर */
	अगर (params->frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		अगर (params->image_invert_enable) अणु
			/* For पूर्णांकerlace inverse mode */
			regw(CCDC_SDOFST_INTERLACE_INVERSE, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_INTERLACE_INVERSE);
		पूर्ण अन्यथा अणु
			/* For पूर्णांकerlace non inverse mode */
			regw(CCDC_SDOFST_INTERLACE_NORMAL, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_INTERLACE_NORMAL);
		पूर्ण
	पूर्ण अन्यथा अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) अणु
		अगर (params->image_invert_enable) अणु
			/* For progessive inverse mode */
			regw(CCDC_SDOFST_PROGRESSIVE_INVERSE, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_PROGRESSIVE_INVERSE);
		पूर्ण अन्यथा अणु
			/* For progessive non inverse mode */
			regw(CCDC_SDOFST_PROGRESSIVE_NORMAL, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_PROGRESSIVE_NORMAL);
		पूर्ण
	पूर्ण
	dev_dbg(ccdc_cfg.dev, "\nend of ccdc_config_raw...");
	वापस 0;
पूर्ण

अटल पूर्णांक ccdc_configure(व्योम)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc_config_raw();
	अन्यथा
		ccdc_config_ycbcr();
	वापस 0;
पूर्ण

अटल पूर्णांक ccdc_set_buftype(क्रमागत ccdc_buftype buf_type)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc_cfg.bayer.buf_type = buf_type;
	अन्यथा
		ccdc_cfg.ycbcr.buf_type = buf_type;
	वापस 0;
पूर्ण
अटल क्रमागत ccdc_buftype ccdc_get_buftype(व्योम)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc_cfg.bayer.buf_type;
	वापस ccdc_cfg.ycbcr.buf_type;
पूर्ण

अटल पूर्णांक ccdc_क्रमागत_pix(u32 *pix, पूर्णांक i)
अणु
	पूर्णांक ret = -EINVAL;
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		अगर (i < ARRAY_SIZE(ccdc_raw_bayer_pix_क्रमmats)) अणु
			*pix = ccdc_raw_bayer_pix_क्रमmats[i];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (i < ARRAY_SIZE(ccdc_raw_yuv_pix_क्रमmats)) अणु
			*pix = ccdc_raw_yuv_pix_क्रमmats[i];
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ccdc_set_pixel_क्रमmat(u32 pixfmt)
अणु
	काष्ठा ccdc_a_law *alaw = &ccdc_cfg.bayer.config_params.alaw;

	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		ccdc_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
		अगर (pixfmt == V4L2_PIX_FMT_SBGGR8)
			alaw->enable = 1;
		अन्यथा अगर (pixfmt != V4L2_PIX_FMT_SBGGR16)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (pixfmt == V4L2_PIX_FMT_YUYV)
			ccdc_cfg.ycbcr.pix_order = CCDC_PIXORDER_YCBYCR;
		अन्यथा अगर (pixfmt == V4L2_PIX_FMT_UYVY)
			ccdc_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
अटल u32 ccdc_get_pixel_क्रमmat(व्योम)
अणु
	काष्ठा ccdc_a_law *alaw = &ccdc_cfg.bayer.config_params.alaw;
	u32 pixfmt;

	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		अगर (alaw->enable)
			pixfmt = V4L2_PIX_FMT_SBGGR8;
		अन्यथा
			pixfmt = V4L2_PIX_FMT_SBGGR16;
	अन्यथा अणु
		अगर (ccdc_cfg.ycbcr.pix_order == CCDC_PIXORDER_YCBYCR)
			pixfmt = V4L2_PIX_FMT_YUYV;
		अन्यथा
			pixfmt = V4L2_PIX_FMT_UYVY;
	पूर्ण
	वापस pixfmt;
पूर्ण
अटल पूर्णांक ccdc_set_image_winकरोw(काष्ठा v4l2_rect *win)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc_cfg.bayer.win = *win;
	अन्यथा
		ccdc_cfg.ycbcr.win = *win;
	वापस 0;
पूर्ण

अटल व्योम ccdc_get_image_winकरोw(काष्ठा v4l2_rect *win)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		*win = ccdc_cfg.bayer.win;
	अन्यथा
		*win = ccdc_cfg.ycbcr.win;
पूर्ण

अटल अचिन्हित पूर्णांक ccdc_get_line_length(व्योम)
अणु
	काष्ठा ccdc_config_params_raw *config_params =
				&ccdc_cfg.bayer.config_params;
	अचिन्हित पूर्णांक len;

	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		अगर ((config_params->alaw.enable) ||
		    (config_params->data_sz == CCDC_DATA_8BITS))
			len = ccdc_cfg.bayer.win.width;
		अन्यथा
			len = ccdc_cfg.bayer.win.width * 2;
	पूर्ण अन्यथा
		len = ccdc_cfg.ycbcr.win.width * 2;
	वापस ALIGN(len, 32);
पूर्ण

अटल पूर्णांक ccdc_set_frame_क्रमmat(क्रमागत ccdc_frmfmt frm_fmt)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc_cfg.bayer.frm_fmt = frm_fmt;
	अन्यथा
		ccdc_cfg.ycbcr.frm_fmt = frm_fmt;
	वापस 0;
पूर्ण

अटल क्रमागत ccdc_frmfmt ccdc_get_frame_क्रमmat(व्योम)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस ccdc_cfg.bayer.frm_fmt;
	अन्यथा
		वापस ccdc_cfg.ycbcr.frm_fmt;
पूर्ण

अटल पूर्णांक ccdc_getfid(व्योम)
अणु
	वापस  (regr(MODESET) >> 15) & 1;
पूर्ण

/* misc operations */
अटल अंतरभूत व्योम ccdc_setfbaddr(अचिन्हित दीर्घ addr)
अणु
	regw((addr >> 21) & 0x007f, STADRH);
	regw((addr >> 5) & 0x0ffff, STADRL);
पूर्ण

अटल पूर्णांक ccdc_set_hw_अगर_params(काष्ठा vpfe_hw_अगर_param *params)
अणु
	ccdc_cfg.अगर_type = params->अगर_type;

	चयन (params->अगर_type) अणु
	हाल VPFE_BT656:
	हाल VPFE_YCBCR_SYNC_16:
	हाल VPFE_YCBCR_SYNC_8:
		ccdc_cfg.ycbcr.vd_pol = params->vdpol;
		ccdc_cfg.ycbcr.hd_pol = params->hdpol;
		अवरोध;
	शेष:
		/* TODO add support क्रम raw bayer here */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ccdc_hw_device ccdc_hw_dev = अणु
	.name = "DM355 CCDC",
	.owner = THIS_MODULE,
	.hw_ops = अणु
		.खोलो = ccdc_खोलो,
		.बंद = ccdc_बंद,
		.enable = ccdc_enable,
		.enable_out_to_sdram = ccdc_enable_output_to_sdram,
		.set_hw_अगर_params = ccdc_set_hw_अगर_params,
		.configure = ccdc_configure,
		.set_buftype = ccdc_set_buftype,
		.get_buftype = ccdc_get_buftype,
		.क्रमागत_pix = ccdc_क्रमागत_pix,
		.set_pixel_क्रमmat = ccdc_set_pixel_क्रमmat,
		.get_pixel_क्रमmat = ccdc_get_pixel_क्रमmat,
		.set_frame_क्रमmat = ccdc_set_frame_क्रमmat,
		.get_frame_क्रमmat = ccdc_get_frame_क्रमmat,
		.set_image_winकरोw = ccdc_set_image_winकरोw,
		.get_image_winकरोw = ccdc_get_image_winकरोw,
		.get_line_length = ccdc_get_line_length,
		.setfbaddr = ccdc_setfbaddr,
		.getfid = ccdc_getfid,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dm355_ccdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम (*setup_pinmux)(व्योम);
	काष्ठा resource	*res;
	पूर्णांक status = 0;

	/*
	 * first try to रेजिस्टर with vpfe. If not correct platक्रमm, then we
	 * करोn't have to iomap
	 */
	status = vpfe_रेजिस्टर_ccdc_device(&ccdc_hw_dev);
	अगर (status < 0)
		वापस status;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		status = -ENODEV;
		जाओ fail_nores;
	पूर्ण

	res = request_mem_region(res->start, resource_size(res), res->name);
	अगर (!res) अणु
		status = -EBUSY;
		जाओ fail_nores;
	पूर्ण

	ccdc_cfg.base_addr = ioremap(res->start, resource_size(res));
	अगर (!ccdc_cfg.base_addr) अणु
		status = -ENOMEM;
		जाओ fail_nomem;
	पूर्ण

	/* Platक्रमm data holds setup_pinmux function ptr */
	अगर (शून्य == pdev->dev.platक्रमm_data) अणु
		status = -ENODEV;
		जाओ fail_nomap;
	पूर्ण
	setup_pinmux = pdev->dev.platक्रमm_data;
	/*
	 * setup Mux configuration क्रम ccdc which may be dअगरferent क्रम
	 * dअगरferent SoCs using this CCDC
	 */
	setup_pinmux();
	ccdc_cfg.dev = &pdev->dev;
	prपूर्णांकk(KERN_NOTICE "%s is registered with vpfe.\n", ccdc_hw_dev.name);
	वापस 0;
fail_nomap:
	iounmap(ccdc_cfg.base_addr);
fail_nomem:
	release_mem_region(res->start, resource_size(res));
fail_nores:
	vpfe_unरेजिस्टर_ccdc_device(&ccdc_hw_dev);
	वापस status;
पूर्ण

अटल पूर्णांक dm355_ccdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*res;

	iounmap(ccdc_cfg.base_addr);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res)
		release_mem_region(res->start, resource_size(res));
	vpfe_unरेजिस्टर_ccdc_device(&ccdc_hw_dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dm355_ccdc_driver = अणु
	.driver = अणु
		.name	= "dm355_ccdc",
	पूर्ण,
	.हटाओ = dm355_ccdc_हटाओ,
	.probe = dm355_ccdc_probe,
पूर्ण;

module_platक्रमm_driver(dm355_ccdc_driver);
