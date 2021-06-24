<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2009 Texas Instruments Inc
 *
 * CCDC hardware module क्रम DM6446
 * ------------------------------
 *
 * This module is क्रम configuring CCD controller of DM6446 VPFE to capture
 * Raw yuv or Bayer RGB data from a decoder. CCDC has several modules
 * such as Defect Pixel Correction, Color Space Conversion etc to
 * pre-process the Raw Bayer RGB data, beक्रमe writing it to SDRAM.
 * This file is named DM644x so that other variants such DM6443
 * may be supported using the same module.
 *
 * TODO: Test Raw bayer parameter settings and bayer capture
 *	 Split module parameter काष्ठाure to module specअगरic ioctl काष्ठाs
 *	 investigate अगर क्रमागत used क्रम user space type definition
 *	 to be replaced by #घोषणाs or पूर्णांकeger
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/gfp.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <media/davinci/dm644x_ccdc.h>
#समावेश <media/davinci/vpss.h>

#समावेश "dm644x_ccdc_regs.h"
#समावेश "ccdc_hw_device.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CCDC Driver for DM6446");
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
		.config_params = अणु
			.data_sz = CCDC_DATA_10BITS,
		पूर्ण,
	पूर्ण,
	.ycbcr = अणु
		.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT,
		.frm_fmt = CCDC_FRMFMT_INTERLACED,
		.win = CCDC_WIN_PAL,
		.fid_pol = VPFE_PINPOL_POSITIVE,
		.vd_pol = VPFE_PINPOL_POSITIVE,
		.hd_pol = VPFE_PINPOL_POSITIVE,
		.bt656_enable = 1,
		.pix_order = CCDC_PIXORDER_CBYCRY,
		.buf_type = CCDC_BUFTYPE_FLD_INTERLEAVED
	पूर्ण,
पूर्ण;

#घोषणा CCDC_MAX_RAW_YUV_FORMATS	2

/* Raw Bayer क्रमmats */
अटल u32 ccdc_raw_bayer_pix_क्रमmats[] =
	अणुV4L2_PIX_FMT_SBGGR8, V4L2_PIX_FMT_SBGGR16पूर्ण;

/* Raw YUV क्रमmats */
अटल u32 ccdc_raw_yuv_pix_क्रमmats[] =
	अणुV4L2_PIX_FMT_UYVY, V4L2_PIX_FMT_YUYVपूर्ण;

/* CCDC Save/Restore context */
अटल u32 ccdc_ctx[CCDC_REG_END / माप(u32)];

/* रेजिस्टर access routines */
अटल अंतरभूत u32 regr(u32 offset)
अणु
	वापस __raw_पढ़ोl(ccdc_cfg.base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम regw(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, ccdc_cfg.base_addr + offset);
पूर्ण

अटल व्योम ccdc_enable(पूर्णांक flag)
अणु
	regw(flag, CCDC_PCR);
पूर्ण

अटल व्योम ccdc_enable_vport(पूर्णांक flag)
अणु
	अगर (flag)
		/* enable video port */
		regw(CCDC_ENABLE_VIDEO_PORT, CCDC_FMTCFG);
	अन्यथा
		regw(CCDC_DISABLE_VIDEO_PORT, CCDC_FMTCFG);
पूर्ण

/*
 * ccdc_setwin()
 * This function will configure the winकरोw size
 * to be capture in CCDC reg
 */
अटल व्योम ccdc_setwin(काष्ठा v4l2_rect *image_win,
			क्रमागत ccdc_frmfmt frm_fmt,
			पूर्णांक ppc)
अणु
	पूर्णांक horz_start, horz_nr_pixels;
	पूर्णांक vert_start, vert_nr_lines;
	पूर्णांक val = 0, mid_img = 0;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_setwin...");
	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, क्रम ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left << (ppc - 1);
	horz_nr_pixels = (image_win->width << (ppc - 1)) - 1;
	regw((horz_start << CCDC_HORZ_INFO_SPH_SHIFT) | horz_nr_pixels,
	     CCDC_HORZ_INFO);

	vert_start = image_win->top;

	अगर (frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* Since first line करोesn't have any data */
		vert_start += 1;
		/* configure VDINT0 */
		val = (vert_start << CCDC_VDINT_VDINT0_SHIFT);
		regw(val, CCDC_VDINT);

	पूर्ण अन्यथा अणु
		/* Since first line करोesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/*
		 * configure VDINT0 and VDINT1. VDINT1 will be at half
		 * of image height
		 */
		mid_img = vert_start + (image_win->height / 2);
		val = (vert_start << CCDC_VDINT_VDINT0_SHIFT) |
		    (mid_img & CCDC_VDINT_VDINT1_MASK);
		regw(val, CCDC_VDINT);

	पूर्ण
	regw((vert_start << CCDC_VERT_START_SLV0_SHIFT) | vert_start,
	     CCDC_VERT_START);
	regw(vert_nr_lines, CCDC_VERT_LINES);
	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_setwin...");
पूर्ण

अटल व्योम ccdc_पढ़ोregs(व्योम)
अणु
	अचिन्हित पूर्णांक val = 0;

	val = regr(CCDC_ALAW);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to ALAW...\n", val);
	val = regr(CCDC_CLAMP);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to CLAMP...\n", val);
	val = regr(CCDC_DCSUB);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to DCSUB...\n", val);
	val = regr(CCDC_BLKCMP);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to BLKCMP...\n", val);
	val = regr(CCDC_FPC_ADDR);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to FPC_ADDR...\n", val);
	val = regr(CCDC_FPC);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to FPC...\n", val);
	val = regr(CCDC_FMTCFG);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to FMTCFG...\n", val);
	val = regr(CCDC_COLPTN);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to COLPTN...\n", val);
	val = regr(CCDC_FMT_HORZ);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to FMT_HORZ...\n", val);
	val = regr(CCDC_FMT_VERT);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to FMT_VERT...\n", val);
	val = regr(CCDC_HSIZE_OFF);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to HSIZE_OFF...\n", val);
	val = regr(CCDC_SDOFST);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to SDOFST...\n", val);
	val = regr(CCDC_VP_OUT);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to VP_OUT...\n", val);
	val = regr(CCDC_SYN_MODE);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to SYN_MODE...\n", val);
	val = regr(CCDC_HORZ_INFO);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to HORZ_INFO...\n", val);
	val = regr(CCDC_VERT_START);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to VERT_START...\n", val);
	val = regr(CCDC_VERT_LINES);
	dev_notice(ccdc_cfg.dev, "\nReading 0x%x to VERT_LINES...\n", val);
पूर्ण

अटल पूर्णांक ccdc_बंद(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

/*
 * ccdc_restore_शेषs()
 * This function will ग_लिखो शेषs to all CCDC रेजिस्टरs
 */
अटल व्योम ccdc_restore_शेषs(व्योम)
अणु
	पूर्णांक i;

	/* disable CCDC */
	ccdc_enable(0);
	/* set all रेजिस्टरs to शेष value */
	क्रम (i = 4; i <= 0x94; i += 4)
		regw(0,  i);
	regw(CCDC_NO_CULLING, CCDC_CULLING);
	regw(CCDC_GAMMA_BITS_11_2, CCDC_ALAW);
पूर्ण

अटल पूर्णांक ccdc_खोलो(काष्ठा device *device)
अणु
	ccdc_restore_शेषs();
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc_enable_vport(1);
	वापस 0;
पूर्ण

अटल व्योम ccdc_sbl_reset(व्योम)
अणु
	vpss_clear_wbl_overflow(VPSS_PCR_CCDC_WBL_O);
पूर्ण

/*
 * ccdc_config_ycbcr()
 * This function will configure CCDC क्रम YCbCr video capture
 */
अटल व्योम ccdc_config_ycbcr(व्योम)
अणु
	काष्ठा ccdc_params_ycbcr *params = &ccdc_cfg.ycbcr;
	u32 syn_mode;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_ycbcr...");
	/*
	 * first restore the CCDC रेजिस्टरs to शेष values
	 * This is important since we assume शेष values to be set in
	 * a lot of रेजिस्टरs that we didn't touch
	 */
	ccdc_restore_शेषs();

	/*
	 * configure pixel क्रमmat, frame क्रमmat, configure video frame
	 * क्रमmat, enable output to SDRAM, enable पूर्णांकernal timing generator
	 * and 8bit pack mode
	 */
	syn_mode = (((params->pix_fmt & CCDC_SYN_MODE_INPMOD_MASK) <<
		    CCDC_SYN_MODE_INPMOD_SHIFT) |
		    ((params->frm_fmt & CCDC_SYN_FLDMODE_MASK) <<
		    CCDC_SYN_FLDMODE_SHIFT) | CCDC_VDHDEN_ENABLE |
		    CCDC_WEN_ENABLE | CCDC_DATA_PACK_ENABLE);

	/* setup BT.656 sync mode */
	अगर (params->bt656_enable) अणु
		regw(CCDC_REC656IF_BT656_EN, CCDC_REC656IF);

		/*
		 * configure the FID, VD, HD pin polarity,
		 * fld,hd pol positive, vd negative, 8-bit data
		 */
		syn_mode |= CCDC_SYN_MODE_VD_POL_NEGATIVE;
		अगर (ccdc_cfg.अगर_type == VPFE_BT656_10BIT)
			syn_mode |= CCDC_SYN_MODE_10BITS;
		अन्यथा
			syn_mode |= CCDC_SYN_MODE_8BITS;
	पूर्ण अन्यथा अणु
		/* y/c बाह्यal sync mode */
		syn_mode |= (((params->fid_pol & CCDC_FID_POL_MASK) <<
			     CCDC_FID_POL_SHIFT) |
			     ((params->hd_pol & CCDC_HD_POL_MASK) <<
			     CCDC_HD_POL_SHIFT) |
			     ((params->vd_pol & CCDC_VD_POL_MASK) <<
			     CCDC_VD_POL_SHIFT));
	पूर्ण
	regw(syn_mode, CCDC_SYN_MODE);

	/* configure video winकरोw */
	ccdc_setwin(&params->win, params->frm_fmt, 2);

	/*
	 * configure the order of y cb cr in SDRAM, and disable latch
	 * पूर्णांकernal रेजिस्टर on vsync
	 */
	अगर (ccdc_cfg.अगर_type == VPFE_BT656_10BIT)
		regw((params->pix_order << CCDC_CCDCFG_Y8POS_SHIFT) |
			CCDC_LATCH_ON_VSYNC_DISABLE | CCDC_CCDCFG_BW656_10BIT,
			CCDC_CCDCFG);
	अन्यथा
		regw((params->pix_order << CCDC_CCDCFG_Y8POS_SHIFT) |
			CCDC_LATCH_ON_VSYNC_DISABLE, CCDC_CCDCFG);

	/*
	 * configure the horizontal line offset. This should be a
	 * on 32 byte boundary. So clear LSB 5 bits
	 */
	regw(((params->win.width * 2  + 31) & ~0x1f), CCDC_HSIZE_OFF);

	/* configure the memory line offset */
	अगर (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED)
		/* two fields are पूर्णांकerleaved in memory */
		regw(CCDC_SDOFST_FIELD_INTERLEAVED, CCDC_SDOFST);

	ccdc_sbl_reset();
	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_config_ycbcr...\n");
पूर्ण

अटल व्योम ccdc_config_black_clamp(काष्ठा ccdc_black_clamp *bclamp)
अणु
	u32 val;

	अगर (!bclamp->enable) अणु
		/* configure DCSub */
		val = (bclamp->dc_sub) & CCDC_BLK_DC_SUB_MASK;
		regw(val, CCDC_DCSUB);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to DCSUB...\n", val);
		regw(CCDC_CLAMP_DEFAULT_VAL, CCDC_CLAMP);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x0000 to CLAMP...\n");
		वापस;
	पूर्ण
	/*
	 * Configure gain,  Start pixel, No of line to be avg,
	 * No of pixel/line to be avg, & Enable the Black clamping
	 */
	val = ((bclamp->sgain & CCDC_BLK_SGAIN_MASK) |
	       ((bclamp->start_pixel & CCDC_BLK_ST_PXL_MASK) <<
		CCDC_BLK_ST_PXL_SHIFT) |
	       ((bclamp->sample_ln & CCDC_BLK_SAMPLE_LINE_MASK) <<
		CCDC_BLK_SAMPLE_LINE_SHIFT) |
	       ((bclamp->sample_pixel & CCDC_BLK_SAMPLE_LN_MASK) <<
		CCDC_BLK_SAMPLE_LN_SHIFT) | CCDC_BLK_CLAMP_ENABLE);
	regw(val, CCDC_CLAMP);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to CLAMP...\n", val);
	/* If Black clamping is enable then make dcsub 0 */
	regw(CCDC_DCSUB_DEFAULT_VAL, CCDC_DCSUB);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x00000000 to DCSUB...\n");
पूर्ण

अटल व्योम ccdc_config_black_compense(काष्ठा ccdc_black_compensation *bcomp)
अणु
	u32 val;

	val = ((bcomp->b & CCDC_BLK_COMP_MASK) |
	      ((bcomp->gb & CCDC_BLK_COMP_MASK) <<
	       CCDC_BLK_COMP_GB_COMP_SHIFT) |
	      ((bcomp->gr & CCDC_BLK_COMP_MASK) <<
	       CCDC_BLK_COMP_GR_COMP_SHIFT) |
	      ((bcomp->r & CCDC_BLK_COMP_MASK) <<
	       CCDC_BLK_COMP_R_COMP_SHIFT));
	regw(val, CCDC_BLKCMP);
पूर्ण

/*
 * ccdc_config_raw()
 * This function will configure CCDC क्रम Raw capture mode
 */
अटल व्योम ccdc_config_raw(व्योम)
अणु
	काष्ठा ccdc_params_raw *params = &ccdc_cfg.bayer;
	काष्ठा ccdc_config_params_raw *config_params =
				&ccdc_cfg.bayer.config_params;
	अचिन्हित पूर्णांक syn_mode = 0;
	अचिन्हित पूर्णांक val;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_raw...");

	/*      Reset CCDC */
	ccdc_restore_शेषs();

	/* Disable latching function रेजिस्टरs on VSYNC  */
	regw(CCDC_LATCH_ON_VSYNC_DISABLE, CCDC_CCDCFG);

	/*
	 * Configure the vertical sync polarity(SYN_MODE.VDPOL),
	 * horizontal sync polarity (SYN_MODE.HDPOL), frame id polarity
	 * (SYN_MODE.FLDPOL), frame क्रमmat(progressive or पूर्णांकerlace),
	 * data size(SYNMODE.DATSIZ), &pixel क्रमmat (Input mode), output
	 * SDRAM, enable पूर्णांकernal timing generator
	 */
	syn_mode =
		(((params->vd_pol & CCDC_VD_POL_MASK) << CCDC_VD_POL_SHIFT) |
		((params->hd_pol & CCDC_HD_POL_MASK) << CCDC_HD_POL_SHIFT) |
		((params->fid_pol & CCDC_FID_POL_MASK) << CCDC_FID_POL_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) << CCDC_FRM_FMT_SHIFT) |
		((config_params->data_sz & CCDC_DATA_SZ_MASK) <<
		CCDC_DATA_SZ_SHIFT) |
		((params->pix_fmt & CCDC_PIX_FMT_MASK) << CCDC_PIX_FMT_SHIFT) |
		CCDC_WEN_ENABLE | CCDC_VDHDEN_ENABLE);

	/* Enable and configure aLaw रेजिस्टर अगर needed */
	अगर (config_params->alaw.enable) अणु
		val = ((config_params->alaw.gamma_wd &
		      CCDC_ALAW_GAMMA_WD_MASK) | CCDC_ALAW_ENABLE);
		regw(val, CCDC_ALAW);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to ALAW...\n", val);
	पूर्ण

	/* Configure video winकरोw */
	ccdc_setwin(&params->win, params->frm_fmt, CCDC_PPC_RAW);

	/* Configure Black Clamp */
	ccdc_config_black_clamp(&config_params->blk_clamp);

	/* Configure Black level compensation */
	ccdc_config_black_compense(&config_params->blk_comp);

	/* If data size is 8 bit then pack the data */
	अगर ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable)
		syn_mode |= CCDC_DATA_PACK_ENABLE;

	/* disable video port */
	val = CCDC_DISABLE_VIDEO_PORT;

	अगर (config_params->data_sz == CCDC_DATA_8BITS)
		val |= (CCDC_DATA_10BITS & CCDC_FMTCFG_VPIN_MASK)
		    << CCDC_FMTCFG_VPIN_SHIFT;
	अन्यथा
		val |= (config_params->data_sz & CCDC_FMTCFG_VPIN_MASK)
		    << CCDC_FMTCFG_VPIN_SHIFT;
	/* Write value in FMTCFG */
	regw(val, CCDC_FMTCFG);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMTCFG...\n", val);
	/* Configure the color pattern according to mt9t001 sensor */
	regw(CCDC_COLPTN_VAL, CCDC_COLPTN);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0xBB11BB11 to COLPTN...\n");
	/*
	 * Configure Data क्रमmatter(Video port) pixel selection
	 * (FMT_HORZ, FMT_VERT)
	 */
	val = ((params->win.left & CCDC_FMT_HORZ_FMTSPH_MASK) <<
	      CCDC_FMT_HORZ_FMTSPH_SHIFT) |
	      (params->win.width & CCDC_FMT_HORZ_FMTLNH_MASK);
	regw(val, CCDC_FMT_HORZ);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMT_HORZ...\n", val);
	val = (params->win.top & CCDC_FMT_VERT_FMTSLV_MASK)
	    << CCDC_FMT_VERT_FMTSLV_SHIFT;
	अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE)
		val |= (params->win.height) & CCDC_FMT_VERT_FMTLNV_MASK;
	अन्यथा
		val |= (params->win.height >> 1) & CCDC_FMT_VERT_FMTLNV_MASK;

	dev_dbg(ccdc_cfg.dev, "\nparams->win.height  0x%x ...\n",
	       params->win.height);
	regw(val, CCDC_FMT_VERT);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMT_VERT...\n", val);

	dev_dbg(ccdc_cfg.dev, "\nbelow regw(val, FMT_VERT)...");

	/*
	 * Configure Horizontal offset रेजिस्टर. If pack 8 is enabled then
	 * 1 pixel will take 1 byte
	 */
	अगर ((config_params->data_sz == CCDC_DATA_8BITS) ||
	    config_params->alaw.enable)
		regw((params->win.width + CCDC_32BYTE_ALIGN_VAL) &
		    CCDC_HSIZE_OFF_MASK, CCDC_HSIZE_OFF);
	अन्यथा
		/* अन्यथा one pixel will take 2 byte */
		regw(((params->win.width * CCDC_TWO_BYTES_PER_PIXEL) +
		    CCDC_32BYTE_ALIGN_VAL) & CCDC_HSIZE_OFF_MASK,
		    CCDC_HSIZE_OFF);

	/* Set value क्रम SDOFST */
	अगर (params->frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		अगर (params->image_invert_enable) अणु
			/* For पूर्णांकelace inverse mode */
			regw(CCDC_INTERLACED_IMAGE_INVERT, CCDC_SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting 0x4B6D to SDOFST..\n");
		पूर्ण

		अन्यथा अणु
			/* For पूर्णांकelace non inverse mode */
			regw(CCDC_INTERLACED_NO_IMAGE_INVERT, CCDC_SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting 0x0249 to SDOFST..\n");
		पूर्ण
	पूर्ण अन्यथा अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) अणु
		regw(CCDC_PROGRESSIVE_NO_IMAGE_INVERT, CCDC_SDOFST);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x0000 to SDOFST...\n");
	पूर्ण

	/*
	 * Configure video port pixel selection (VPOUT)
	 * Here -1 is to make the height value less than FMT_VERT.FMTLNV
	 */
	अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE)
		val = (((params->win.height - 1) & CCDC_VP_OUT_VERT_NUM_MASK))
		    << CCDC_VP_OUT_VERT_NUM_SHIFT;
	अन्यथा
		val =
		    ((((params->win.height >> CCDC_INTERLACED_HEIGHT_SHIFT) -
		     1) & CCDC_VP_OUT_VERT_NUM_MASK)) <<
		    CCDC_VP_OUT_VERT_NUM_SHIFT;

	val |= ((((params->win.width))) & CCDC_VP_OUT_HORZ_NUM_MASK)
	    << CCDC_VP_OUT_HORZ_NUM_SHIFT;
	val |= (params->win.left) & CCDC_VP_OUT_HORZ_ST_MASK;
	regw(val, CCDC_VP_OUT);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to VP_OUT...\n", val);
	regw(syn_mode, CCDC_SYN_MODE);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to SYN_MODE...\n", syn_mode);

	ccdc_sbl_reset();
	dev_dbg(ccdc_cfg.dev, "\nend of ccdc_config_raw...");
	ccdc_पढ़ोregs();
पूर्ण

अटल पूर्णांक ccdc_configure(व्योम)
अणु
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER)
		ccdc_config_raw();
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
	अगर (ccdc_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		ccdc_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
		अगर (pixfmt == V4L2_PIX_FMT_SBGGR8)
			ccdc_cfg.bayer.config_params.alaw.enable = 1;
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
	वापस (regr(CCDC_SYN_MODE) >> 15) & 1;
पूर्ण

/* misc operations */
अटल अंतरभूत व्योम ccdc_setfbaddr(अचिन्हित दीर्घ addr)
अणु
	regw(addr & 0xffffffe0, CCDC_SDR_ADDR);
पूर्ण

अटल पूर्णांक ccdc_set_hw_अगर_params(काष्ठा vpfe_hw_अगर_param *params)
अणु
	ccdc_cfg.अगर_type = params->अगर_type;

	चयन (params->अगर_type) अणु
	हाल VPFE_BT656:
	हाल VPFE_YCBCR_SYNC_16:
	हाल VPFE_YCBCR_SYNC_8:
	हाल VPFE_BT656_10BIT:
		ccdc_cfg.ycbcr.vd_pol = params->vdpol;
		ccdc_cfg.ycbcr.hd_pol = params->hdpol;
		अवरोध;
	शेष:
		/* TODO add support क्रम raw bayer here */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ccdc_save_context(व्योम)
अणु
	ccdc_ctx[CCDC_PCR >> 2] = regr(CCDC_PCR);
	ccdc_ctx[CCDC_SYN_MODE >> 2] = regr(CCDC_SYN_MODE);
	ccdc_ctx[CCDC_HD_VD_WID >> 2] = regr(CCDC_HD_VD_WID);
	ccdc_ctx[CCDC_PIX_LINES >> 2] = regr(CCDC_PIX_LINES);
	ccdc_ctx[CCDC_HORZ_INFO >> 2] = regr(CCDC_HORZ_INFO);
	ccdc_ctx[CCDC_VERT_START >> 2] = regr(CCDC_VERT_START);
	ccdc_ctx[CCDC_VERT_LINES >> 2] = regr(CCDC_VERT_LINES);
	ccdc_ctx[CCDC_CULLING >> 2] = regr(CCDC_CULLING);
	ccdc_ctx[CCDC_HSIZE_OFF >> 2] = regr(CCDC_HSIZE_OFF);
	ccdc_ctx[CCDC_SDOFST >> 2] = regr(CCDC_SDOFST);
	ccdc_ctx[CCDC_SDR_ADDR >> 2] = regr(CCDC_SDR_ADDR);
	ccdc_ctx[CCDC_CLAMP >> 2] = regr(CCDC_CLAMP);
	ccdc_ctx[CCDC_DCSUB >> 2] = regr(CCDC_DCSUB);
	ccdc_ctx[CCDC_COLPTN >> 2] = regr(CCDC_COLPTN);
	ccdc_ctx[CCDC_BLKCMP >> 2] = regr(CCDC_BLKCMP);
	ccdc_ctx[CCDC_FPC >> 2] = regr(CCDC_FPC);
	ccdc_ctx[CCDC_FPC_ADDR >> 2] = regr(CCDC_FPC_ADDR);
	ccdc_ctx[CCDC_VDINT >> 2] = regr(CCDC_VDINT);
	ccdc_ctx[CCDC_ALAW >> 2] = regr(CCDC_ALAW);
	ccdc_ctx[CCDC_REC656IF >> 2] = regr(CCDC_REC656IF);
	ccdc_ctx[CCDC_CCDCFG >> 2] = regr(CCDC_CCDCFG);
	ccdc_ctx[CCDC_FMTCFG >> 2] = regr(CCDC_FMTCFG);
	ccdc_ctx[CCDC_FMT_HORZ >> 2] = regr(CCDC_FMT_HORZ);
	ccdc_ctx[CCDC_FMT_VERT >> 2] = regr(CCDC_FMT_VERT);
	ccdc_ctx[CCDC_FMT_ADDR0 >> 2] = regr(CCDC_FMT_ADDR0);
	ccdc_ctx[CCDC_FMT_ADDR1 >> 2] = regr(CCDC_FMT_ADDR1);
	ccdc_ctx[CCDC_FMT_ADDR2 >> 2] = regr(CCDC_FMT_ADDR2);
	ccdc_ctx[CCDC_FMT_ADDR3 >> 2] = regr(CCDC_FMT_ADDR3);
	ccdc_ctx[CCDC_FMT_ADDR4 >> 2] = regr(CCDC_FMT_ADDR4);
	ccdc_ctx[CCDC_FMT_ADDR5 >> 2] = regr(CCDC_FMT_ADDR5);
	ccdc_ctx[CCDC_FMT_ADDR6 >> 2] = regr(CCDC_FMT_ADDR6);
	ccdc_ctx[CCDC_FMT_ADDR7 >> 2] = regr(CCDC_FMT_ADDR7);
	ccdc_ctx[CCDC_PRGEVEN_0 >> 2] = regr(CCDC_PRGEVEN_0);
	ccdc_ctx[CCDC_PRGEVEN_1 >> 2] = regr(CCDC_PRGEVEN_1);
	ccdc_ctx[CCDC_PRGODD_0 >> 2] = regr(CCDC_PRGODD_0);
	ccdc_ctx[CCDC_PRGODD_1 >> 2] = regr(CCDC_PRGODD_1);
	ccdc_ctx[CCDC_VP_OUT >> 2] = regr(CCDC_VP_OUT);
पूर्ण

अटल व्योम ccdc_restore_context(व्योम)
अणु
	regw(ccdc_ctx[CCDC_SYN_MODE >> 2], CCDC_SYN_MODE);
	regw(ccdc_ctx[CCDC_HD_VD_WID >> 2], CCDC_HD_VD_WID);
	regw(ccdc_ctx[CCDC_PIX_LINES >> 2], CCDC_PIX_LINES);
	regw(ccdc_ctx[CCDC_HORZ_INFO >> 2], CCDC_HORZ_INFO);
	regw(ccdc_ctx[CCDC_VERT_START >> 2], CCDC_VERT_START);
	regw(ccdc_ctx[CCDC_VERT_LINES >> 2], CCDC_VERT_LINES);
	regw(ccdc_ctx[CCDC_CULLING >> 2], CCDC_CULLING);
	regw(ccdc_ctx[CCDC_HSIZE_OFF >> 2], CCDC_HSIZE_OFF);
	regw(ccdc_ctx[CCDC_SDOFST >> 2], CCDC_SDOFST);
	regw(ccdc_ctx[CCDC_SDR_ADDR >> 2], CCDC_SDR_ADDR);
	regw(ccdc_ctx[CCDC_CLAMP >> 2], CCDC_CLAMP);
	regw(ccdc_ctx[CCDC_DCSUB >> 2], CCDC_DCSUB);
	regw(ccdc_ctx[CCDC_COLPTN >> 2], CCDC_COLPTN);
	regw(ccdc_ctx[CCDC_BLKCMP >> 2], CCDC_BLKCMP);
	regw(ccdc_ctx[CCDC_FPC >> 2], CCDC_FPC);
	regw(ccdc_ctx[CCDC_FPC_ADDR >> 2], CCDC_FPC_ADDR);
	regw(ccdc_ctx[CCDC_VDINT >> 2], CCDC_VDINT);
	regw(ccdc_ctx[CCDC_ALAW >> 2], CCDC_ALAW);
	regw(ccdc_ctx[CCDC_REC656IF >> 2], CCDC_REC656IF);
	regw(ccdc_ctx[CCDC_CCDCFG >> 2], CCDC_CCDCFG);
	regw(ccdc_ctx[CCDC_FMTCFG >> 2], CCDC_FMTCFG);
	regw(ccdc_ctx[CCDC_FMT_HORZ >> 2], CCDC_FMT_HORZ);
	regw(ccdc_ctx[CCDC_FMT_VERT >> 2], CCDC_FMT_VERT);
	regw(ccdc_ctx[CCDC_FMT_ADDR0 >> 2], CCDC_FMT_ADDR0);
	regw(ccdc_ctx[CCDC_FMT_ADDR1 >> 2], CCDC_FMT_ADDR1);
	regw(ccdc_ctx[CCDC_FMT_ADDR2 >> 2], CCDC_FMT_ADDR2);
	regw(ccdc_ctx[CCDC_FMT_ADDR3 >> 2], CCDC_FMT_ADDR3);
	regw(ccdc_ctx[CCDC_FMT_ADDR4 >> 2], CCDC_FMT_ADDR4);
	regw(ccdc_ctx[CCDC_FMT_ADDR5 >> 2], CCDC_FMT_ADDR5);
	regw(ccdc_ctx[CCDC_FMT_ADDR6 >> 2], CCDC_FMT_ADDR6);
	regw(ccdc_ctx[CCDC_FMT_ADDR7 >> 2], CCDC_FMT_ADDR7);
	regw(ccdc_ctx[CCDC_PRGEVEN_0 >> 2], CCDC_PRGEVEN_0);
	regw(ccdc_ctx[CCDC_PRGEVEN_1 >> 2], CCDC_PRGEVEN_1);
	regw(ccdc_ctx[CCDC_PRGODD_0 >> 2], CCDC_PRGODD_0);
	regw(ccdc_ctx[CCDC_PRGODD_1 >> 2], CCDC_PRGODD_1);
	regw(ccdc_ctx[CCDC_VP_OUT >> 2], CCDC_VP_OUT);
	regw(ccdc_ctx[CCDC_PCR >> 2], CCDC_PCR);
पूर्ण
अटल स्थिर काष्ठा ccdc_hw_device ccdc_hw_dev = अणु
	.name = "DM6446 CCDC",
	.owner = THIS_MODULE,
	.hw_ops = अणु
		.खोलो = ccdc_खोलो,
		.बंद = ccdc_बंद,
		.reset = ccdc_sbl_reset,
		.enable = ccdc_enable,
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

अटल पूर्णांक dm644x_ccdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
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

	ccdc_cfg.dev = &pdev->dev;
	prपूर्णांकk(KERN_NOTICE "%s is registered with vpfe.\n", ccdc_hw_dev.name);
	वापस 0;
fail_nomem:
	release_mem_region(res->start, resource_size(res));
fail_nores:
	vpfe_unरेजिस्टर_ccdc_device(&ccdc_hw_dev);
	वापस status;
पूर्ण

अटल पूर्णांक dm644x_ccdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*res;

	iounmap(ccdc_cfg.base_addr);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res)
		release_mem_region(res->start, resource_size(res));
	vpfe_unरेजिस्टर_ccdc_device(&ccdc_hw_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक dm644x_ccdc_suspend(काष्ठा device *dev)
अणु
	/* Save CCDC context */
	ccdc_save_context();
	/* Disable CCDC */
	ccdc_enable(0);

	वापस 0;
पूर्ण

अटल पूर्णांक dm644x_ccdc_resume(काष्ठा device *dev)
अणु
	/* Restore CCDC context */
	ccdc_restore_context();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dm644x_ccdc_pm_ops = अणु
	.suspend = dm644x_ccdc_suspend,
	.resume = dm644x_ccdc_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver dm644x_ccdc_driver = अणु
	.driver = अणु
		.name	= "dm644x_ccdc",
		.pm = &dm644x_ccdc_pm_ops,
	पूर्ण,
	.हटाओ = dm644x_ccdc_हटाओ,
	.probe = dm644x_ccdc_probe,
पूर्ण;

module_platक्रमm_driver(dm644x_ccdc_driver);
