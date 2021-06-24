<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * Image Sensor Interface (ISIF) driver
 *
 * This driver is क्रम configuring the ISIF IP available on DM365 or any other
 * TI SoCs. This is used क्रम capturing yuv or bayer video or image data
 * from a decoder or sensor. This IP is similar to the CCDC IP on DM355
 * and DM6446, but with enhanced or additional ip blocks. The driver
 * configures the ISIF upon commands from the vpfe bridge driver through
 * ccdc_hw_device पूर्णांकerface.
 *
 * TODO: 1) Raw bayer parameter settings and bayer capture
 *	 2) Add support क्रम control ioctl
 */
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <media/davinci/isअगर.h>
#समावेश <media/davinci/vpss.h>

#समावेश "isif_regs.h"
#समावेश "ccdc_hw_device.h"

/* Defaults क्रम module configuration parameters */
अटल स्थिर काष्ठा isअगर_config_params_raw isअगर_config_शेषs = अणु
	.linearize = अणु
		.en = 0,
		.corr_shft = ISIF_NO_SHIFT,
		.scale_fact = अणु1, 0पूर्ण,
	पूर्ण,
	.df_csc = अणु
		.df_or_csc = 0,
		.csc = अणु
			.en = 0,
		पूर्ण,
	पूर्ण,
	.dfc = अणु
		.en = 0,
	पूर्ण,
	.bclamp = अणु
		.en = 0,
	पूर्ण,
	.gain_offset = अणु
		.gain = अणु
			.r_ye = अणु1, 0पूर्ण,
			.gr_cy = अणु1, 0पूर्ण,
			.gb_g = अणु1, 0पूर्ण,
			.b_mg = अणु1, 0पूर्ण,
		पूर्ण,
	पूर्ण,
	.culling = अणु
		.hcpat_odd = 0xff,
		.hcpat_even = 0xff,
		.vcpat = 0xff,
	पूर्ण,
	.compress = अणु
		.alg = ISIF_ALAW,
	पूर्ण,
पूर्ण;

/* ISIF operation configuration */
अटल काष्ठा isअगर_oper_config अणु
	काष्ठा device *dev;
	क्रमागत vpfe_hw_अगर_type अगर_type;
	काष्ठा isअगर_ycbcr_config ycbcr;
	काष्ठा isअगर_params_raw bayer;
	क्रमागत isअगर_data_pack data_pack;
	/* ISIF base address */
	व्योम __iomem *base_addr;
	/* ISIF Linear Table 0 */
	व्योम __iomem *linear_tbl0_addr;
	/* ISIF Linear Table 1 */
	व्योम __iomem *linear_tbl1_addr;
पूर्ण isअगर_cfg = अणु
	.ycbcr = अणु
		.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT,
		.frm_fmt = CCDC_FRMFMT_INTERLACED,
		.win = ISIF_WIN_NTSC,
		.fid_pol = VPFE_PINPOL_POSITIVE,
		.vd_pol = VPFE_PINPOL_POSITIVE,
		.hd_pol = VPFE_PINPOL_POSITIVE,
		.pix_order = CCDC_PIXORDER_CBYCRY,
		.buf_type = CCDC_BUFTYPE_FLD_INTERLEAVED,
	पूर्ण,
	.bayer = अणु
		.pix_fmt = CCDC_PIXFMT_RAW,
		.frm_fmt = CCDC_FRMFMT_PROGRESSIVE,
		.win = ISIF_WIN_VGA,
		.fid_pol = VPFE_PINPOL_POSITIVE,
		.vd_pol = VPFE_PINPOL_POSITIVE,
		.hd_pol = VPFE_PINPOL_POSITIVE,
		.gain = अणु
			.r_ye = अणु1, 0पूर्ण,
			.gr_cy = अणु1, 0पूर्ण,
			.gb_g = अणु1, 0पूर्ण,
			.b_mg = अणु1, 0पूर्ण,
		पूर्ण,
		.cfa_pat = ISIF_CFA_PAT_MOSAIC,
		.data_msb = ISIF_BIT_MSB_11,
		.config_params = अणु
			.data_shअगरt = ISIF_NO_SHIFT,
			.col_pat_field0 = अणु
				.olop = ISIF_GREEN_BLUE,
				.olep = ISIF_BLUE,
				.elop = ISIF_RED,
				.elep = ISIF_GREEN_RED,
			पूर्ण,
			.col_pat_field1 = अणु
				.olop = ISIF_GREEN_BLUE,
				.olep = ISIF_BLUE,
				.elop = ISIF_RED,
				.elep = ISIF_GREEN_RED,
			पूर्ण,
			.test_pat_gen = 0,
		पूर्ण,
	पूर्ण,
	.data_pack = ISIF_DATA_PACK8,
पूर्ण;

/* Raw Bayer क्रमmats */
अटल स्थिर u32 isअगर_raw_bayer_pix_क्रमmats[] = अणु
	V4L2_PIX_FMT_SBGGR8, V4L2_PIX_FMT_SBGGR16पूर्ण;

/* Raw YUV क्रमmats */
अटल स्थिर u32 isअगर_raw_yuv_pix_क्रमmats[] = अणु
	V4L2_PIX_FMT_UYVY, V4L2_PIX_FMT_YUYVपूर्ण;

/* रेजिस्टर access routines */
अटल अंतरभूत u32 regr(u32 offset)
अणु
	वापस __raw_पढ़ोl(isअगर_cfg.base_addr + offset);
पूर्ण

अटल अंतरभूत व्योम regw(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, isअगर_cfg.base_addr + offset);
पूर्ण

/* reg_modअगरy() - पढ़ो, modअगरy and ग_लिखो रेजिस्टर */
अटल अंतरभूत u32 reg_modअगरy(u32 mask, u32 val, u32 offset)
अणु
	u32 new_val = (regr(offset) & ~mask) | (val & mask);

	regw(new_val, offset);
	वापस new_val;
पूर्ण

अटल अंतरभूत व्योम regw_lin_tbl(u32 val, u32 offset, पूर्णांक i)
अणु
	अगर (!i)
		__raw_ग_लिखोl(val, isअगर_cfg.linear_tbl0_addr + offset);
	अन्यथा
		__raw_ग_लिखोl(val, isअगर_cfg.linear_tbl1_addr + offset);
पूर्ण

अटल व्योम isअगर_disable_all_modules(व्योम)
अणु
	/* disable BC */
	regw(0, CLAMPCFG);
	/* disable vdfc */
	regw(0, DFCCTL);
	/* disable CSC */
	regw(0, CSCCTL);
	/* disable linearization */
	regw(0, LINCFG0);
	/* disable other modules here as they are supported */
पूर्ण

अटल व्योम isअगर_enable(पूर्णांक en)
अणु
	अगर (!en) अणु
		/* Beक्रमe disable isअगर, disable all ISIF modules */
		isअगर_disable_all_modules();
		/*
		 * रुको क्रम next VD. Assume lowest scan rate is 12 Hz. So
		 * 100 msec delay is good enough
		 */
		msleep(100);
	पूर्ण
	reg_modअगरy(ISIF_SYNCEN_VDHDEN_MASK, en, SYNCEN);
पूर्ण

अटल व्योम isअगर_enable_output_to_sdram(पूर्णांक en)
अणु
	reg_modअगरy(ISIF_SYNCEN_WEN_MASK, en << ISIF_SYNCEN_WEN_SHIFT, SYNCEN);
पूर्ण

अटल व्योम isअगर_config_culling(काष्ठा isअगर_cul *cul)
अणु
	u32 val;

	/* Horizontal pattern */
	val = (cul->hcpat_even << CULL_PAT_EVEN_LINE_SHIFT) | cul->hcpat_odd;
	regw(val, CULH);

	/* vertical pattern */
	regw(cul->vcpat, CULV);

	/* LPF */
	reg_modअगरy(ISIF_LPF_MASK << ISIF_LPF_SHIFT,
		  cul->en_lpf << ISIF_LPF_SHIFT, MODESET);
पूर्ण

अटल व्योम isअगर_config_gain_offset(व्योम)
अणु
	काष्ठा isअगर_gain_offsets_adj *gain_off_p =
		&isअगर_cfg.bayer.config_params.gain_offset;
	u32 val;

	val = (!!gain_off_p->gain_sdram_en << GAIN_SDRAM_EN_SHIFT) |
	      (!!gain_off_p->gain_ipipe_en << GAIN_IPIPE_EN_SHIFT) |
	      (!!gain_off_p->gain_h3a_en << GAIN_H3A_EN_SHIFT) |
	      (!!gain_off_p->offset_sdram_en << OFST_SDRAM_EN_SHIFT) |
	      (!!gain_off_p->offset_ipipe_en << OFST_IPIPE_EN_SHIFT) |
	      (!!gain_off_p->offset_h3a_en << OFST_H3A_EN_SHIFT);

	reg_modअगरy(GAIN_OFFSET_EN_MASK, val, CGAMMAWD);

	val = (gain_off_p->gain.r_ye.पूर्णांकeger << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.r_ye.decimal;
	regw(val, CRGAIN);

	val = (gain_off_p->gain.gr_cy.पूर्णांकeger << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.gr_cy.decimal;
	regw(val, CGRGAIN);

	val = (gain_off_p->gain.gb_g.पूर्णांकeger << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.gb_g.decimal;
	regw(val, CGBGAIN);

	val = (gain_off_p->gain.b_mg.पूर्णांकeger << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.b_mg.decimal;
	regw(val, CBGAIN);

	regw(gain_off_p->offset, COFSTA);
पूर्ण

अटल व्योम isअगर_restore_शेषs(व्योम)
अणु
	क्रमागत vpss_ccdc_source_sel source = VPSS_CCDCIN;

	dev_dbg(isअगर_cfg.dev, "\nstarting isif_restore_defaults...");
	isअगर_cfg.bayer.config_params = isअगर_config_शेषs;
	/* Enable घड़ी to ISIF, IPIPEIF and BL */
	vpss_enable_घड़ी(VPSS_CCDC_CLOCK, 1);
	vpss_enable_घड़ी(VPSS_IPIPEIF_CLOCK, 1);
	vpss_enable_घड़ी(VPSS_BL_CLOCK, 1);
	/* Set शेष offset and gain */
	isअगर_config_gain_offset();
	vpss_select_ccdc_source(source);
	dev_dbg(isअगर_cfg.dev, "\nEnd of isif_restore_defaults...");
पूर्ण

अटल पूर्णांक isअगर_खोलो(काष्ठा device *device)
अणु
	isअगर_restore_शेषs();
	वापस 0;
पूर्ण

/* This function will configure the winकरोw size to be capture in ISIF reg */
अटल व्योम isअगर_setwin(काष्ठा v4l2_rect *image_win,
			क्रमागत ccdc_frmfmt frm_fmt, पूर्णांक ppc)
अणु
	पूर्णांक horz_start, horz_nr_pixels;
	पूर्णांक vert_start, vert_nr_lines;
	पूर्णांक mid_img = 0;

	dev_dbg(isअगर_cfg.dev, "\nStarting isif_setwin...");
	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, क्रम ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left << (ppc - 1);
	horz_nr_pixels = ((image_win->width) << (ppc - 1)) - 1;

	/* Writing the horizontal info पूर्णांकo the रेजिस्टरs */
	regw(horz_start & START_PX_HOR_MASK, SPH);
	regw(horz_nr_pixels & NUM_PX_HOR_MASK, LNH);
	vert_start = image_win->top;

	अगर (frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* To account क्रम VD since line 0 करोesn't have any data */
		vert_start += 1;
	पूर्ण अन्यथा अणु
		/* To account क्रम VD since line 0 करोesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/* configure VDINT0 and VDINT1 */
		mid_img = vert_start + (image_win->height / 2);
		regw(mid_img, VDINT1);
	पूर्ण

	regw(0, VDINT0);
	regw(vert_start & START_VER_ONE_MASK, SLV0);
	regw(vert_start & START_VER_TWO_MASK, SLV1);
	regw(vert_nr_lines & NUM_LINES_VER, LNV);
पूर्ण

अटल व्योम isअगर_config_bclamp(काष्ठा isअगर_black_clamp *bc)
अणु
	u32 val;

	/*
	 * DC Offset is always added to image data irrespective of bc enable
	 * status
	 */
	regw(bc->dc_offset, CLDCOFST);

	अगर (bc->en) अणु
		val = bc->bc_mode_color << ISIF_BC_MODE_COLOR_SHIFT;

		/* Enable BC and horizontal clamp calculation parameters */
		val = val | 1 | (bc->horz.mode << ISIF_HORZ_BC_MODE_SHIFT);

		regw(val, CLAMPCFG);

		अगर (bc->horz.mode != ISIF_HORZ_BC_DISABLE) अणु
			/*
			 * Winकरोw count क्रम calculation
			 * Base winकरोw selection
			 * pixel limit
			 * Horizontal size of winकरोw
			 * vertical size of the winकरोw
			 * Horizontal start position of the winकरोw
			 * Vertical start position of the winकरोw
			 */
			val = bc->horz.win_count_calc |
			      ((!!bc->horz.base_win_sel_calc) <<
				ISIF_HORZ_BC_WIN_SEL_SHIFT) |
			      ((!!bc->horz.clamp_pix_limit) <<
				ISIF_HORZ_BC_PIX_LIMIT_SHIFT) |
			      (bc->horz.win_h_sz_calc <<
				ISIF_HORZ_BC_WIN_H_SIZE_SHIFT) |
			      (bc->horz.win_v_sz_calc <<
				ISIF_HORZ_BC_WIN_V_SIZE_SHIFT);
			regw(val, CLHWIN0);

			regw(bc->horz.win_start_h_calc, CLHWIN1);
			regw(bc->horz.win_start_v_calc, CLHWIN2);
		पूर्ण

		/* vertical clamp calculation parameters */

		/* Reset clamp value sel क्रम previous line */
		val |=
		(bc->vert.reset_val_sel << ISIF_VERT_BC_RST_VAL_SEL_SHIFT) |
		(bc->vert.line_ave_coef << ISIF_VERT_BC_LINE_AVE_COEF_SHIFT);
		regw(val, CLVWIN0);

		/* Optical Black horizontal start position */
		regw(bc->vert.ob_start_h, CLVWIN1);
		/* Optical Black vertical start position */
		regw(bc->vert.ob_start_v, CLVWIN2);
		/* Optical Black vertical size क्रम calculation */
		regw(bc->vert.ob_v_sz_calc, CLVWIN3);
		/* Vertical start position क्रम BC subtraction */
		regw(bc->vert_start_sub, CLSV);
	पूर्ण
पूर्ण

अटल व्योम isअगर_config_linearization(काष्ठा isअगर_linearize *linearize)
अणु
	u32 val, i;

	अगर (!linearize->en) अणु
		regw(0, LINCFG0);
		वापस;
	पूर्ण

	/* shअगरt value क्रम correction & enable linearization (set lsb) */
	val = (linearize->corr_shft << ISIF_LIN_CORRSFT_SHIFT) | 1;
	regw(val, LINCFG0);

	/* Scale factor */
	val = ((!!linearize->scale_fact.पूर्णांकeger) <<
	       ISIF_LIN_SCALE_FACT_INTEG_SHIFT) |
	       linearize->scale_fact.decimal;
	regw(val, LINCFG1);

	क्रम (i = 0; i < ISIF_LINEAR_TAB_SIZE; i++) अणु
		अगर (i % 2)
			regw_lin_tbl(linearize->table[i], ((i >> 1) << 2), 1);
		अन्यथा
			regw_lin_tbl(linearize->table[i], ((i >> 1) << 2), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक isअगर_config_dfc(काष्ठा isअगर_dfc *vdfc)
अणु
	/* initialize retries to loop क्रम max ~ 250 usec */
	u32 val, count, retries = loops_per_jअगरfy / (4000/HZ);
	पूर्णांक i;

	अगर (!vdfc->en)
		वापस 0;

	/* Correction mode */
	val = (vdfc->corr_mode << ISIF_VDFC_CORR_MOD_SHIFT);

	/* Correct whole line or partial */
	अगर (vdfc->corr_whole_line)
		val |= 1 << ISIF_VDFC_CORR_WHOLE_LN_SHIFT;

	/* level shअगरt value */
	val |= vdfc->def_level_shअगरt << ISIF_VDFC_LEVEL_SHFT_SHIFT;

	regw(val, DFCCTL);

	/* Defect saturation level */
	regw(vdfc->def_sat_level, VDFSATLV);

	regw(vdfc->table[0].pos_vert, DFCMEM0);
	regw(vdfc->table[0].pos_horz, DFCMEM1);
	अगर (vdfc->corr_mode == ISIF_VDFC_NORMAL ||
	    vdfc->corr_mode == ISIF_VDFC_HORZ_INTERPOL_IF_SAT) अणु
		regw(vdfc->table[0].level_at_pos, DFCMEM2);
		regw(vdfc->table[0].level_up_pixels, DFCMEM3);
		regw(vdfc->table[0].level_low_pixels, DFCMEM4);
	पूर्ण

	/* set DFCMARST and set DFCMWR */
	val = regr(DFCMEMCTL) | (1 << ISIF_DFCMEMCTL_DFCMARST_SHIFT) | 1;
	regw(val, DFCMEMCTL);

	count = retries;
	जबतक (count && (regr(DFCMEMCTL) & 0x1))
		count--;

	अगर (!count) अणु
		dev_dbg(isअगर_cfg.dev, "defect table write timeout !!!\n");
		वापस -1;
	पूर्ण

	क्रम (i = 1; i < vdfc->num_vdefects; i++) अणु
		regw(vdfc->table[i].pos_vert, DFCMEM0);
		regw(vdfc->table[i].pos_horz, DFCMEM1);
		अगर (vdfc->corr_mode == ISIF_VDFC_NORMAL ||
		    vdfc->corr_mode == ISIF_VDFC_HORZ_INTERPOL_IF_SAT) अणु
			regw(vdfc->table[i].level_at_pos, DFCMEM2);
			regw(vdfc->table[i].level_up_pixels, DFCMEM3);
			regw(vdfc->table[i].level_low_pixels, DFCMEM4);
		पूर्ण
		val = regr(DFCMEMCTL);
		/* clear DFCMARST and set DFCMWR */
		val &= ~BIT(ISIF_DFCMEMCTL_DFCMARST_SHIFT);
		val |= 1;
		regw(val, DFCMEMCTL);

		count = retries;
		जबतक (count && (regr(DFCMEMCTL) & 0x1))
			count--;

		अगर (!count) अणु
			dev_err(isअगर_cfg.dev,
				"defect table write timeout !!!\n");
			वापस -1;
		पूर्ण
	पूर्ण
	अगर (vdfc->num_vdefects < ISIF_VDFC_TABLE_SIZE) अणु
		/* Extra cycle needed */
		regw(0, DFCMEM0);
		regw(0x1FFF, DFCMEM1);
		regw(1, DFCMEMCTL);
	पूर्ण

	/* enable VDFC */
	reg_modअगरy((1 << ISIF_VDFC_EN_SHIFT), (1 << ISIF_VDFC_EN_SHIFT),
		   DFCCTL);
	वापस 0;
पूर्ण

अटल व्योम isअगर_config_csc(काष्ठा isअगर_df_csc *df_csc)
अणु
	u32 val1 = 0, val2 = 0, i;

	अगर (!df_csc->csc.en) अणु
		regw(0, CSCCTL);
		वापस;
	पूर्ण
	क्रम (i = 0; i < ISIF_CSC_NUM_COEFF; i++) अणु
		अगर ((i % 2) == 0) अणु
			/* CSCM - LSB */
			val1 = (df_csc->csc.coeff[i].पूर्णांकeger <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				df_csc->csc.coeff[i].decimal;
		पूर्ण अन्यथा अणु

			/* CSCM - MSB */
			val2 = (df_csc->csc.coeff[i].पूर्णांकeger <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				df_csc->csc.coeff[i].decimal;
			val2 <<= ISIF_CSCM_MSB_SHIFT;
			val2 |= val1;
			regw(val2, (CSCM0 + ((i - 1) << 1)));
		पूर्ण
	पूर्ण

	/* program the active area */
	regw(df_csc->start_pix, FMTSPH);
	/*
	 * one extra pixel as required क्रम CSC. Actually number of
	 * pixel - 1 should be configured in this रेजिस्टर. So we
	 * need to subtract 1 beक्रमe writing to FMTSPH, but we will
	 * not करो this since csc requires one extra pixel
	 */
	regw(df_csc->num_pixels, FMTLNH);
	regw(df_csc->start_line, FMTSLV);
	/*
	 * one extra line as required क्रम CSC. See reason करोcumented क्रम
	 * num_pixels
	 */
	regw(df_csc->num_lines, FMTLNV);

	/* Enable CSC */
	regw(1, CSCCTL);
पूर्ण

अटल पूर्णांक isअगर_config_raw(व्योम)
अणु
	काष्ठा isअगर_params_raw *params = &isअगर_cfg.bayer;
	काष्ठा isअगर_config_params_raw *module_params =
		&isअगर_cfg.bayer.config_params;
	काष्ठा vpss_pg_frame_size frame_size;
	काष्ठा vpss_sync_pol sync;
	u32 val;

	dev_dbg(isअगर_cfg.dev, "\nStarting isif_config_raw..\n");

	/*
	 * Configure CCDCFG रेजिस्टर:-
	 * Set CCD Not to swap input since input is RAW data
	 * Set FID detection function to Latch at V-Sync
	 * Set WENLOG - isअगर valid area
	 * Set TRGSEL
	 * Set EXTRG
	 * Packed to 8 or 16 bits
	 */

	val = ISIF_YCINSWP_RAW | ISIF_CCDCFG_FIDMD_LATCH_VSYNC |
		ISIF_CCDCFG_WENLOG_AND | ISIF_CCDCFG_TRGSEL_WEN |
		ISIF_CCDCFG_EXTRG_DISABLE | isअगर_cfg.data_pack;

	dev_dbg(isअगर_cfg.dev, "Writing 0x%x to ...CCDCFG \n", val);
	regw(val, CCDCFG);

	/*
	 * Configure the vertical sync polarity(MODESET.VDPOL)
	 * Configure the horizontal sync polarity (MODESET.HDPOL)
	 * Configure frame id polarity (MODESET.FLDPOL)
	 * Configure data polarity
	 * Configure External WEN Selection
	 * Configure frame क्रमmat(progressive or पूर्णांकerlace)
	 * Configure pixel क्रमmat (Input mode)
	 * Configure the data shअगरt
	 */

	val = ISIF_VDHDOUT_INPUT | (params->vd_pol << ISIF_VD_POL_SHIFT) |
		(params->hd_pol << ISIF_HD_POL_SHIFT) |
		(params->fid_pol << ISIF_FID_POL_SHIFT) |
		(ISIF_DATAPOL_NORMAL << ISIF_DATAPOL_SHIFT) |
		(ISIF_EXWEN_DISABLE << ISIF_EXWEN_SHIFT) |
		(params->frm_fmt << ISIF_FRM_FMT_SHIFT) |
		(params->pix_fmt << ISIF_INPUT_SHIFT) |
		(params->config_params.data_shअगरt << ISIF_DATASFT_SHIFT);

	regw(val, MODESET);
	dev_dbg(isअगर_cfg.dev, "Writing 0x%x to MODESET...\n", val);

	/*
	 * Configure GAMMAWD रेजिस्टर
	 * CFA pattern setting
	 */
	val = params->cfa_pat << ISIF_GAMMAWD_CFA_SHIFT;

	/* Gamma msb */
	अगर (module_params->compress.alg == ISIF_ALAW)
		val |= ISIF_ALAW_ENABLE;

	val |= (params->data_msb << ISIF_ALAW_GAMMA_WD_SHIFT);
	regw(val, CGAMMAWD);

	/* Configure DPCM compression settings */
	अगर (module_params->compress.alg == ISIF_DPCM) अणु
		val =  BIT(ISIF_DPCM_EN_SHIFT) |
		       (module_params->compress.pred <<
		       ISIF_DPCM_PREDICTOR_SHIFT);
	पूर्ण

	regw(val, MISC);

	/* Configure Gain & Offset */
	isअगर_config_gain_offset();

	/* Configure Color pattern */
	val = (params->config_params.col_pat_field0.olop) |
	      (params->config_params.col_pat_field0.olep << 2) |
	      (params->config_params.col_pat_field0.elop << 4) |
	      (params->config_params.col_pat_field0.elep << 6) |
	      (params->config_params.col_pat_field1.olop << 8) |
	      (params->config_params.col_pat_field1.olep << 10) |
	      (params->config_params.col_pat_field1.elop << 12) |
	      (params->config_params.col_pat_field1.elep << 14);
	regw(val, CCOLP);
	dev_dbg(isअगर_cfg.dev, "Writing %x to CCOLP ...\n", val);

	/* Configure HSIZE रेजिस्टर  */
	val = (!!params->horz_flip_en) << ISIF_HSIZE_FLIP_SHIFT;

	/* calculate line offset in 32 bytes based on pack value */
	अगर (isअगर_cfg.data_pack == ISIF_PACK_8BIT)
		val |= ((params->win.width + 31) >> 5);
	अन्यथा अगर (isअगर_cfg.data_pack == ISIF_PACK_12BIT)
		val |= (((params->win.width +
		       (params->win.width >> 2)) + 31) >> 5);
	अन्यथा
		val |= (((params->win.width * 2) + 31) >> 5);
	regw(val, HSIZE);

	/* Configure SDOFST रेजिस्टर  */
	अगर (params->frm_fmt == CCDC_FRMFMT_INTERLACED) अणु
		अगर (params->image_invert_en) अणु
			/* For पूर्णांकerlace inverse mode */
			regw(0x4B6D, SDOFST);
			dev_dbg(isअगर_cfg.dev, "Writing 0x4B6D to SDOFST...\n");
		पूर्ण अन्यथा अणु
			/* For पूर्णांकerlace non inverse mode */
			regw(0x0B6D, SDOFST);
			dev_dbg(isअगर_cfg.dev, "Writing 0x0B6D to SDOFST...\n");
		पूर्ण
	पूर्ण अन्यथा अगर (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) अणु
		अगर (params->image_invert_en) अणु
			/* For progressive inverse mode */
			regw(0x4000, SDOFST);
			dev_dbg(isअगर_cfg.dev, "Writing 0x4000 to SDOFST...\n");
		पूर्ण अन्यथा अणु
			/* For progressive non inverse mode */
			regw(0x0000, SDOFST);
			dev_dbg(isअगर_cfg.dev, "Writing 0x0000 to SDOFST...\n");
		पूर्ण
	पूर्ण

	/* Configure video winकरोw */
	isअगर_setwin(&params->win, params->frm_fmt, 1);

	/* Configure Black Clamp */
	isअगर_config_bclamp(&module_params->bclamp);

	/* Configure Vertical Defection Pixel Correction */
	अगर (isअगर_config_dfc(&module_params->dfc) < 0)
		वापस -EFAULT;

	अगर (!module_params->df_csc.df_or_csc)
		/* Configure Color Space Conversion */
		isअगर_config_csc(&module_params->df_csc);

	isअगर_config_linearization(&module_params->linearize);

	/* Configure Culling */
	isअगर_config_culling(&module_params->culling);

	/* Configure horizontal and vertical offsets(DFC,LSC,Gain) */
	regw(module_params->horz_offset, DATAHOFST);
	regw(module_params->vert_offset, DATAVOFST);

	/* Setup test pattern अगर enabled */
	अगर (params->config_params.test_pat_gen) अणु
		/* Use the HD/VD pol settings from user */
		sync.ccdpg_hdpol = params->hd_pol;
		sync.ccdpg_vdpol = params->vd_pol;
		dm365_vpss_set_sync_pol(sync);
		frame_size.hlpfr = isअगर_cfg.bayer.win.width;
		frame_size.pplen = isअगर_cfg.bayer.win.height;
		dm365_vpss_set_pg_frame_size(frame_size);
		vpss_select_ccdc_source(VPSS_PGLPBK);
	पूर्ण

	dev_dbg(isअगर_cfg.dev, "\nEnd of isif_config_ycbcr...\n");
	वापस 0;
पूर्ण

अटल पूर्णांक isअगर_set_buftype(क्रमागत ccdc_buftype buf_type)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		isअगर_cfg.bayer.buf_type = buf_type;
	अन्यथा
		isअगर_cfg.ycbcr.buf_type = buf_type;

	वापस 0;

पूर्ण
अटल क्रमागत ccdc_buftype isअगर_get_buftype(व्योम)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस isअगर_cfg.bayer.buf_type;

	वापस isअगर_cfg.ycbcr.buf_type;
पूर्ण

अटल पूर्णांक isअगर_क्रमागत_pix(u32 *pix, पूर्णांक i)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		अगर (i < ARRAY_SIZE(isअगर_raw_bayer_pix_क्रमmats)) अणु
			*pix = isअगर_raw_bayer_pix_क्रमmats[i];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (i < ARRAY_SIZE(isअगर_raw_yuv_pix_क्रमmats)) अणु
			*pix = isअगर_raw_yuv_pix_क्रमmats[i];
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक isअगर_set_pixel_क्रमmat(अचिन्हित पूर्णांक pixfmt)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		अगर (pixfmt == V4L2_PIX_FMT_SBGGR8) अणु
			अगर ((isअगर_cfg.bayer.config_params.compress.alg !=
			     ISIF_ALAW) &&
			    (isअगर_cfg.bayer.config_params.compress.alg !=
			     ISIF_DPCM)) अणु
				dev_dbg(isअगर_cfg.dev,
					"Either configure A-Law or DPCM\n");
				वापस -EINVAL;
			पूर्ण
			isअगर_cfg.data_pack = ISIF_PACK_8BIT;
		पूर्ण अन्यथा अगर (pixfmt == V4L2_PIX_FMT_SBGGR16) अणु
			isअगर_cfg.bayer.config_params.compress.alg =
					ISIF_NO_COMPRESSION;
			isअगर_cfg.data_pack = ISIF_PACK_16BIT;
		पूर्ण अन्यथा
			वापस -EINVAL;
		isअगर_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
	पूर्ण अन्यथा अणु
		अगर (pixfmt == V4L2_PIX_FMT_YUYV)
			isअगर_cfg.ycbcr.pix_order = CCDC_PIXORDER_YCBYCR;
		अन्यथा अगर (pixfmt == V4L2_PIX_FMT_UYVY)
			isअगर_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		अन्यथा
			वापस -EINVAL;
		isअगर_cfg.data_pack = ISIF_PACK_8BIT;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 isअगर_get_pixel_क्रमmat(व्योम)
अणु
	u32 pixfmt;

	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		अगर (isअगर_cfg.bayer.config_params.compress.alg == ISIF_ALAW ||
		    isअगर_cfg.bayer.config_params.compress.alg == ISIF_DPCM)
			pixfmt = V4L2_PIX_FMT_SBGGR8;
		अन्यथा
			pixfmt = V4L2_PIX_FMT_SBGGR16;
	अन्यथा अणु
		अगर (isअगर_cfg.ycbcr.pix_order == CCDC_PIXORDER_YCBYCR)
			pixfmt = V4L2_PIX_FMT_YUYV;
		अन्यथा
			pixfmt = V4L2_PIX_FMT_UYVY;
	पूर्ण
	वापस pixfmt;
पूर्ण

अटल पूर्णांक isअगर_set_image_winकरोw(काष्ठा v4l2_rect *win)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		isअगर_cfg.bayer.win.top = win->top;
		isअगर_cfg.bayer.win.left = win->left;
		isअगर_cfg.bayer.win.width = win->width;
		isअगर_cfg.bayer.win.height = win->height;
	पूर्ण अन्यथा अणु
		isअगर_cfg.ycbcr.win.top = win->top;
		isअगर_cfg.ycbcr.win.left = win->left;
		isअगर_cfg.ycbcr.win.width = win->width;
		isअगर_cfg.ycbcr.win.height = win->height;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम isअगर_get_image_winकरोw(काष्ठा v4l2_rect *win)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		*win = isअगर_cfg.bayer.win;
	अन्यथा
		*win = isअगर_cfg.ycbcr.win;
पूर्ण

अटल अचिन्हित पूर्णांक isअगर_get_line_length(व्योम)
अणु
	अचिन्हित पूर्णांक len;

	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER) अणु
		अगर (isअगर_cfg.data_pack == ISIF_PACK_8BIT)
			len = ((isअगर_cfg.bayer.win.width));
		अन्यथा अगर (isअगर_cfg.data_pack == ISIF_PACK_12BIT)
			len = (((isअगर_cfg.bayer.win.width * 2) +
				 (isअगर_cfg.bayer.win.width >> 2)));
		अन्यथा
			len = (((isअगर_cfg.bayer.win.width * 2)));
	पूर्ण अन्यथा
		len = (((isअगर_cfg.ycbcr.win.width * 2)));
	वापस ALIGN(len, 32);
पूर्ण

अटल पूर्णांक isअगर_set_frame_क्रमmat(क्रमागत ccdc_frmfmt frm_fmt)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		isअगर_cfg.bayer.frm_fmt = frm_fmt;
	अन्यथा
		isअगर_cfg.ycbcr.frm_fmt = frm_fmt;
	वापस 0;
पूर्ण
अटल क्रमागत ccdc_frmfmt isअगर_get_frame_क्रमmat(व्योम)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस isअगर_cfg.bayer.frm_fmt;
	वापस isअगर_cfg.ycbcr.frm_fmt;
पूर्ण

अटल पूर्णांक isअगर_getfid(व्योम)
अणु
	वापस (regr(MODESET) >> 15) & 0x1;
पूर्ण

/* misc operations */
अटल व्योम isअगर_setfbaddr(अचिन्हित दीर्घ addr)
अणु
	regw((addr >> 21) & 0x07ff, CADU);
	regw((addr >> 5) & 0x0ffff, CADL);
पूर्ण

अटल पूर्णांक isअगर_set_hw_अगर_params(काष्ठा vpfe_hw_अगर_param *params)
अणु
	isअगर_cfg.अगर_type = params->अगर_type;

	चयन (params->अगर_type) अणु
	हाल VPFE_BT656:
	हाल VPFE_BT656_10BIT:
	हाल VPFE_YCBCR_SYNC_8:
		isअगर_cfg.ycbcr.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT;
		isअगर_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		अवरोध;
	हाल VPFE_BT1120:
	हाल VPFE_YCBCR_SYNC_16:
		isअगर_cfg.ycbcr.pix_fmt = CCDC_PIXFMT_YCBCR_16BIT;
		isअगर_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		अवरोध;
	हाल VPFE_RAW_BAYER:
		isअगर_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
		अवरोध;
	शेष:
		dev_dbg(isअगर_cfg.dev, "Invalid interface type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This function will configure ISIF क्रम YCbCr parameters. */
अटल पूर्णांक isअगर_config_ycbcr(व्योम)
अणु
	काष्ठा isअगर_ycbcr_config *params = &isअगर_cfg.ycbcr;
	u32 modeset = 0, ccdcfg = 0;

	dev_dbg(isअगर_cfg.dev, "\nStarting isif_config_ycbcr...");

	/* configure pixel क्रमmat or input mode */
	modeset = modeset | (params->pix_fmt << ISIF_INPUT_SHIFT) |
		  (params->frm_fmt << ISIF_FRM_FMT_SHIFT) |
		  (params->fid_pol << ISIF_FID_POL_SHIFT) |
		  (params->hd_pol << ISIF_HD_POL_SHIFT) |
		  (params->vd_pol << ISIF_VD_POL_SHIFT);

	/* pack the data to 8-bit ISIFCFG */
	चयन (isअगर_cfg.अगर_type) अणु
	हाल VPFE_BT656:
		अगर (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) अणु
			dev_dbg(isअगर_cfg.dev, "Invalid pix_fmt(input mode)\n");
			वापस -EINVAL;
		पूर्ण
		modeset |= (VPFE_PINPOL_NEGATIVE << ISIF_VD_POL_SHIFT);
		regw(3, REC656IF);
		ccdcfg = ccdcfg | ISIF_DATA_PACK8 | ISIF_YCINSWP_YCBCR;
		अवरोध;
	हाल VPFE_BT656_10BIT:
		अगर (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) अणु
			dev_dbg(isअगर_cfg.dev, "Invalid pix_fmt(input mode)\n");
			वापस -EINVAL;
		पूर्ण
		/* setup BT.656, embedded sync  */
		regw(3, REC656IF);
		/* enable 10 bit mode in ccdcfg */
		ccdcfg = ccdcfg | ISIF_DATA_PACK8 | ISIF_YCINSWP_YCBCR |
			ISIF_BW656_ENABLE;
		अवरोध;
	हाल VPFE_BT1120:
		अगर (params->pix_fmt != CCDC_PIXFMT_YCBCR_16BIT) अणु
			dev_dbg(isअगर_cfg.dev, "Invalid pix_fmt(input mode)\n");
			वापस -EINVAL;
		पूर्ण
		regw(3, REC656IF);
		अवरोध;

	हाल VPFE_YCBCR_SYNC_8:
		ccdcfg |= ISIF_DATA_PACK8;
		ccdcfg |= ISIF_YCINSWP_YCBCR;
		अगर (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) अणु
			dev_dbg(isअगर_cfg.dev, "Invalid pix_fmt(input mode)\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल VPFE_YCBCR_SYNC_16:
		अगर (params->pix_fmt != CCDC_PIXFMT_YCBCR_16BIT) अणु
			dev_dbg(isअगर_cfg.dev, "Invalid pix_fmt(input mode)\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		/* should never come here */
		dev_dbg(isअगर_cfg.dev, "Invalid interface type\n");
		वापस -EINVAL;
	पूर्ण

	regw(modeset, MODESET);

	/* Set up pix order */
	ccdcfg |= params->pix_order << ISIF_PIX_ORDER_SHIFT;

	regw(ccdcfg, CCDCFG);

	/* configure video winकरोw */
	अगर ((isअगर_cfg.अगर_type == VPFE_BT1120) ||
	    (isअगर_cfg.अगर_type == VPFE_YCBCR_SYNC_16))
		isअगर_setwin(&params->win, params->frm_fmt, 1);
	अन्यथा
		isअगर_setwin(&params->win, params->frm_fmt, 2);

	/*
	 * configure the horizontal line offset
	 * this is करोne by rounding up width to a multiple of 16 pixels
	 * and multiply by two to account क्रम y:cb:cr 4:2:2 data
	 */
	regw(((((params->win.width * 2) + 31) & 0xffffffe0) >> 5), HSIZE);

	/* configure the memory line offset */
	अगर ((params->frm_fmt == CCDC_FRMFMT_INTERLACED) &&
	    (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED))
		/* two fields are पूर्णांकerleaved in memory */
		regw(0x00000249, SDOFST);

	वापस 0;
पूर्ण

अटल पूर्णांक isअगर_configure(व्योम)
अणु
	अगर (isअगर_cfg.अगर_type == VPFE_RAW_BAYER)
		वापस isअगर_config_raw();
	वापस isअगर_config_ycbcr();
पूर्ण

अटल पूर्णांक isअगर_बंद(काष्ठा device *device)
अणु
	/* copy शेषs to module params */
	isअगर_cfg.bayer.config_params = isअगर_config_शेषs;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ccdc_hw_device isअगर_hw_dev = अणु
	.name = "ISIF",
	.owner = THIS_MODULE,
	.hw_ops = अणु
		.खोलो = isअगर_खोलो,
		.बंद = isअगर_बंद,
		.enable = isअगर_enable,
		.enable_out_to_sdram = isअगर_enable_output_to_sdram,
		.set_hw_अगर_params = isअगर_set_hw_अगर_params,
		.configure = isअगर_configure,
		.set_buftype = isअगर_set_buftype,
		.get_buftype = isअगर_get_buftype,
		.क्रमागत_pix = isअगर_क्रमागत_pix,
		.set_pixel_क्रमmat = isअगर_set_pixel_क्रमmat,
		.get_pixel_क्रमmat = isअगर_get_pixel_क्रमmat,
		.set_frame_क्रमmat = isअगर_set_frame_क्रमmat,
		.get_frame_क्रमmat = isअगर_get_frame_क्रमmat,
		.set_image_winकरोw = isअगर_set_image_winकरोw,
		.get_image_winकरोw = isअगर_get_image_winकरोw,
		.get_line_length = isअगर_get_line_length,
		.setfbaddr = isअगर_setfbaddr,
		.getfid = isअगर_getfid,
	पूर्ण,
पूर्ण;

अटल पूर्णांक isअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम (*setup_pinmux)(व्योम);
	काष्ठा resource	*res;
	व्योम __iomem *addr;
	पूर्णांक status = 0, i;

	/* Platक्रमm data holds setup_pinmux function ptr */
	अगर (!pdev->dev.platक्रमm_data)
		वापस -ENODEV;

	/*
	 * first try to रेजिस्टर with vpfe. If not correct platक्रमm, then we
	 * करोn't have to iomap
	 */
	status = vpfe_रेजिस्टर_ccdc_device(&isअगर_hw_dev);
	अगर (status < 0)
		वापस status;

	setup_pinmux = pdev->dev.platक्रमm_data;
	/*
	 * setup Mux configuration क्रम ccdc which may be dअगरferent क्रम
	 * dअगरferent SoCs using this CCDC
	 */
	setup_pinmux();

	i = 0;
	/* Get the ISIF base address, linearization table0 and table1 addr. */
	जबतक (i < 3) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res) अणु
			status = -ENODEV;
			जाओ fail_nobase_res;
		पूर्ण
		res = request_mem_region(res->start, resource_size(res),
					 res->name);
		अगर (!res) अणु
			status = -EBUSY;
			जाओ fail_nobase_res;
		पूर्ण
		addr = ioremap(res->start, resource_size(res));
		अगर (!addr) अणु
			status = -ENOMEM;
			जाओ fail_base_iomap;
		पूर्ण
		चयन (i) अणु
		हाल 0:
			/* ISIF base address */
			isअगर_cfg.base_addr = addr;
			अवरोध;
		हाल 1:
			/* ISIF linear tbl0 address */
			isअगर_cfg.linear_tbl0_addr = addr;
			अवरोध;
		शेष:
			/* ISIF linear tbl0 address */
			isअगर_cfg.linear_tbl1_addr = addr;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	isअगर_cfg.dev = &pdev->dev;

	prपूर्णांकk(KERN_NOTICE "%s is registered with vpfe.\n",
		isअगर_hw_dev.name);
	वापस 0;
fail_base_iomap:
	release_mem_region(res->start, resource_size(res));
	i--;
fail_nobase_res:
	अगर (isअगर_cfg.base_addr) अणु
		iounmap(isअगर_cfg.base_addr);
		isअगर_cfg.base_addr = शून्य;
	पूर्ण
	अगर (isअगर_cfg.linear_tbl0_addr) अणु
		iounmap(isअगर_cfg.linear_tbl0_addr);
		isअगर_cfg.linear_tbl0_addr = शून्य;
	पूर्ण

	जबतक (i >= 0) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (res)
			release_mem_region(res->start, resource_size(res));
		i--;
	पूर्ण
	vpfe_unरेजिस्टर_ccdc_device(&isअगर_hw_dev);
	वापस status;
पूर्ण

अटल पूर्णांक isअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*res;
	पूर्णांक i = 0;

	iounmap(isअगर_cfg.base_addr);
	isअगर_cfg.base_addr = शून्य;
	iounmap(isअगर_cfg.linear_tbl0_addr);
	isअगर_cfg.linear_tbl0_addr = शून्य;
	iounmap(isअगर_cfg.linear_tbl1_addr);
	isअगर_cfg.linear_tbl1_addr = शून्य;
	जबतक (i < 3) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (res)
			release_mem_region(res->start, resource_size(res));
		i++;
	पूर्ण
	vpfe_unरेजिस्टर_ccdc_device(&isअगर_hw_dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver isअगर_driver = अणु
	.driver = अणु
		.name	= "isif",
	पूर्ण,
	.हटाओ = isअगर_हटाओ,
	.probe = isअगर_probe,
पूर्ण;

module_platक्रमm_driver(isअगर_driver);

MODULE_LICENSE("GPL");
