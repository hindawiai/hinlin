<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * isअगर header file
 */
#अगर_अघोषित _ISIF_H
#घोषणा _ISIF_H

#समावेश <media/davinci/ccdc_types.h>
#समावेश <media/davinci/vpfe_types.h>

/* isअगर भग्न type S8Q8/U8Q8 */
काष्ठा isअगर_भग्न_8 अणु
	/* 8 bit पूर्णांकeger part */
	__u8 पूर्णांकeger;
	/* 8 bit decimal part */
	__u8 decimal;
पूर्ण;

/* isअगर भग्न type U16Q16/S16Q16 */
काष्ठा isअगर_भग्न_16 अणु
	/* 16 bit पूर्णांकeger part */
	__u16 पूर्णांकeger;
	/* 16 bit decimal part */
	__u16 decimal;
पूर्ण;

/************************************************************************
 *   Vertical Defect Correction parameters
 ***********************************************************************/
/* Defect Correction (DFC) table entry */
काष्ठा isअगर_vdfc_entry अणु
	/* vertical position of defect */
	__u16 pos_vert;
	/* horizontal position of defect */
	__u16 pos_horz;
	/*
	 * Defect level of Vertical line defect position. This is subtracted
	 * from the data at the defect position
	 */
	__u8 level_at_pos;
	/*
	 * Defect level of the pixels upper than the vertical line defect.
	 * This is subtracted from the data
	 */
	__u8 level_up_pixels;
	/*
	 * Defect level of the pixels lower than the vertical line defect.
	 * This is subtracted from the data
	 */
	__u8 level_low_pixels;
पूर्ण;

#घोषणा ISIF_VDFC_TABLE_SIZE		8
काष्ठा isअगर_dfc अणु
	/* enable vertical defect correction */
	__u8 en;
	/* Defect level subtraction. Just fed through अगर saturating */
#घोषणा	ISIF_VDFC_NORMAL		0
	/*
	 * Defect level subtraction. Horizontal पूर्णांकerpolation ((i-2)+(i+2))/2
	 * अगर data saturating
	 */
#घोषणा ISIF_VDFC_HORZ_INTERPOL_IF_SAT	1
	/* Horizontal पूर्णांकerpolation (((i-2)+(i+2))/2) */
#घोषणा	ISIF_VDFC_HORZ_INTERPOL		2
	/* one of the vertical defect correction modes above */
	__u8 corr_mode;
	/* 0 - whole line corrected, 1 - not pixels upper than the defect */
	__u8 corr_whole_line;
#घोषणा ISIF_VDFC_NO_SHIFT		0
#घोषणा ISIF_VDFC_SHIFT_1		1
#घोषणा ISIF_VDFC_SHIFT_2		2
#घोषणा ISIF_VDFC_SHIFT_3		3
#घोषणा ISIF_VDFC_SHIFT_4		4
	/*
	 * defect level shअगरt value. level_at_pos, level_upper_pos,
	 * and level_lower_pos can be shअगरted up by this value. Choose
	 * one of the values above
	 */
	__u8 def_level_shअगरt;
	/* defect saturation level */
	__u16 def_sat_level;
	/* number of vertical defects. Max is ISIF_VDFC_TABLE_SIZE */
	__u16 num_vdefects;
	/* VDFC table ptr */
	काष्ठा isअगर_vdfc_entry table[ISIF_VDFC_TABLE_SIZE];
पूर्ण;

काष्ठा isअगर_horz_bclamp अणु

	/* Horizontal clamp disabled. Only vertical clamp value is subtracted */
#घोषणा	ISIF_HORZ_BC_DISABLE		0
	/*
	 * Horizontal clamp value is calculated and subtracted from image data
	 * aदीर्घ with vertical clamp value
	 */
#घोषणा ISIF_HORZ_BC_CLAMP_CALC_ENABLED	1
	/*
	 * Horizontal clamp value calculated from previous image is subtracted
	 * from image data aदीर्घ with vertical clamp value.
	 */
#घोषणा ISIF_HORZ_BC_CLAMP_NOT_UPDATED	2
	/* horizontal clamp mode. One of the values above */
	__u8 mode;
	/*
	 * pixel value limit enable.
	 *  0 - limit disabled
	 *  1 - pixel value limited to 1023
	 */
	__u8 clamp_pix_limit;
	/* Select Most left winकरोw क्रम bc calculation */
#घोषणा	ISIF_SEL_MOST_LEFT_WIN		0
	/* Select Most right winकरोw क्रम bc calculation */
#घोषणा ISIF_SEL_MOST_RIGHT_WIN		1
	/* Select most left or right winकरोw क्रम clamp val calculation */
	__u8 base_win_sel_calc;
	/* Winकरोw count per color क्रम calculation. range 1-32 */
	__u8 win_count_calc;
	/* Winकरोw start position - horizontal क्रम calculation. 0 - 8191 */
	__u16 win_start_h_calc;
	/* Winकरोw start position - vertical क्रम calculation 0 - 8191 */
	__u16 win_start_v_calc;
#घोषणा ISIF_HORZ_BC_SZ_H_2PIXELS	0
#घोषणा ISIF_HORZ_BC_SZ_H_4PIXELS	1
#घोषणा ISIF_HORZ_BC_SZ_H_8PIXELS	2
#घोषणा ISIF_HORZ_BC_SZ_H_16PIXELS	3
	/* Width of the sample winकरोw in pixels क्रम calculation */
	__u8 win_h_sz_calc;
#घोषणा ISIF_HORZ_BC_SZ_V_32PIXELS	0
#घोषणा ISIF_HORZ_BC_SZ_V_64PIXELS	1
#घोषणा	ISIF_HORZ_BC_SZ_V_128PIXELS	2
#घोषणा ISIF_HORZ_BC_SZ_V_256PIXELS	3
	/* Height of the sample winकरोw in pixels क्रम calculation */
	__u8 win_v_sz_calc;
पूर्ण;

/************************************************************************
 *  Black Clamp parameters
 ***********************************************************************/
काष्ठा isअगर_vert_bclamp अणु
	/* Reset value used is the clamp value calculated */
#घोषणा	ISIF_VERT_BC_USE_HORZ_CLAMP_VAL		0
	/* Reset value used is reset_clamp_val configured */
#घोषणा	ISIF_VERT_BC_USE_CONFIG_CLAMP_VAL	1
	/* No update, previous image value is used */
#घोषणा	ISIF_VERT_BC_NO_UPDATE			2
	/*
	 * Reset value selector क्रम vertical clamp calculation. Use one of
	 * the above values
	 */
	__u8 reset_val_sel;
	/* U8Q8. Line average coefficient used in vertical clamp calculation */
	__u8 line_ave_coef;
	/* Height of the optical black region क्रम calculation */
	__u16 ob_v_sz_calc;
	/* Optical black region start position - horizontal. 0 - 8191 */
	__u16 ob_start_h;
	/* Optical black region start position - vertical 0 - 8191 */
	__u16 ob_start_v;
पूर्ण;

काष्ठा isअगर_black_clamp अणु
	/*
	 * This offset value is added irrespective of the clamp enable status.
	 * S13
	 */
	__u16 dc_offset;
	/*
	 * Enable black/digital clamp value to be subtracted from the image data
	 */
	__u8 en;
	/*
	 * black clamp mode. same/separate clamp क्रम 4 colors
	 * 0 - disable - same clamp value क्रम all colors
	 * 1 - clamp value calculated separately क्रम all colors
	 */
	__u8 bc_mode_color;
	/* Vertical start position क्रम bc subtraction */
	__u16 vert_start_sub;
	/* Black clamp क्रम horizontal direction */
	काष्ठा isअगर_horz_bclamp horz;
	/* Black clamp क्रम vertical direction */
	काष्ठा isअगर_vert_bclamp vert;
पूर्ण;

/*************************************************************************
** Color Space Conversion (CSC)
*************************************************************************/
#घोषणा ISIF_CSC_NUM_COEFF	16
काष्ठा isअगर_color_space_conv अणु
	/* Enable color space conversion */
	__u8 en;
	/*
	 * csc coefficient table. S8Q5, M00 at index 0, M01 at index 1, and
	 * so क्रमth
	 */
	काष्ठा isअगर_भग्न_8 coeff[ISIF_CSC_NUM_COEFF];
पूर्ण;


/*************************************************************************
**  Black  Compensation parameters
*************************************************************************/
काष्ठा isअगर_black_comp अणु
	/* Comp क्रम Red */
	__s8 r_comp;
	/* Comp क्रम Gr */
	__s8 gr_comp;
	/* Comp क्रम Blue */
	__s8 b_comp;
	/* Comp क्रम Gb */
	__s8 gb_comp;
पूर्ण;

/*************************************************************************
**  Gain parameters
*************************************************************************/
काष्ठा isअगर_gain अणु
	/* Gain क्रम Red or ye */
	काष्ठा isअगर_भग्न_16 r_ye;
	/* Gain क्रम Gr or cy */
	काष्ठा isअगर_भग्न_16 gr_cy;
	/* Gain क्रम Gb or g */
	काष्ठा isअगर_भग्न_16 gb_g;
	/* Gain क्रम Blue or mg */
	काष्ठा isअगर_भग्न_16 b_mg;
पूर्ण;

#घोषणा ISIF_LINEAR_TAB_SIZE	192
/*************************************************************************
**  Linearization parameters
*************************************************************************/
काष्ठा isअगर_linearize अणु
	/* Enable or Disable linearization of data */
	__u8 en;
	/* Shअगरt value applied */
	__u8 corr_shft;
	/* scale factor applied U11Q10 */
	काष्ठा isअगर_भग्न_16 scale_fact;
	/* Size of the linear table */
	__u16 table[ISIF_LINEAR_TAB_SIZE];
पूर्ण;

/* Color patterns */
#घोषणा ISIF_RED	0
#घोषणा	ISIF_GREEN_RED	1
#घोषणा ISIF_GREEN_BLUE	2
#घोषणा ISIF_BLUE	3
काष्ठा isअगर_col_pat अणु
	__u8 olop;
	__u8 olep;
	__u8 elop;
	__u8 elep;
पूर्ण;

/*************************************************************************
**  Data क्रमmatter parameters
*************************************************************************/
काष्ठा isअगर_fmtplen अणु
	/*
	 * number of program entries क्रम SET0, range 1 - 16
	 * when fmपंचांगode is ISIF_SPLIT, 1 - 8 when fmपंचांगode is
	 * ISIF_COMBINE
	 */
	__u16 plen0;
	/*
	 * number of program entries क्रम SET1, range 1 - 16
	 * when fmपंचांगode is ISIF_SPLIT, 1 - 8 when fmपंचांगode is
	 * ISIF_COMBINE
	 */
	__u16 plen1;
	/**
	 * number of program entries क्रम SET2, range 1 - 16
	 * when fmपंचांगode is ISIF_SPLIT, 1 - 8 when fmपंचांगode is
	 * ISIF_COMBINE
	 */
	__u16 plen2;
	/**
	 * number of program entries क्रम SET3, range 1 - 16
	 * when fmपंचांगode is ISIF_SPLIT, 1 - 8 when fmपंचांगode is
	 * ISIF_COMBINE
	 */
	__u16 plen3;
पूर्ण;

काष्ठा isअगर_fmt_cfg अणु
#घोषणा ISIF_SPLIT		0
#घोषणा ISIF_COMBINE		1
	/* Split or combine or line alternate */
	__u8 fmपंचांगode;
	/* enable or disable line alternating mode */
	__u8 ln_alter_en;
#घोषणा ISIF_1LINE		0
#घोषणा	ISIF_2LINES		1
#घोषणा	ISIF_3LINES		2
#घोषणा	ISIF_4LINES		3
	/* Split/combine line number */
	__u8 lnum;
	/* Address increment Range 1 - 16 */
	__u8 addrinc;
पूर्ण;

काष्ठा isअगर_fmt_addr_ptr अणु
	/* Initial address */
	__u32 init_addr;
	/* output line number */
#घोषणा ISIF_1STLINE		0
#घोषणा	ISIF_2NDLINE		1
#घोषणा	ISIF_3RDLINE		2
#घोषणा	ISIF_4THLINE		3
	__u8 out_line;
पूर्ण;

काष्ठा isअगर_fmtpgm_ap अणु
	/* program address poपूर्णांकer */
	__u8 pgm_aptr;
	/* program address increment or decrement */
	__u8 pgmupdt;
पूर्ण;

काष्ठा isअगर_data_क्रमmatter अणु
	/* Enable/Disable data क्रमmatter */
	__u8 en;
	/* data क्रमmatter configuration */
	काष्ठा isअगर_fmt_cfg cfg;
	/* Formatter program entries length */
	काष्ठा isअगर_fmtplen plen;
	/* first pixel in a line fed to क्रमmatter */
	__u16 fmtrlen;
	/* HD पूर्णांकerval क्रम output line. Only valid when split line */
	__u16 fmthcnt;
	/* क्रमmatter address poपूर्णांकers */
	काष्ठा isअगर_fmt_addr_ptr fmtaddr_ptr[16];
	/* program enable/disable */
	__u8 pgm_en[32];
	/* program address poपूर्णांकers */
	काष्ठा isअगर_fmtpgm_ap fmtpgm_ap[32];
पूर्ण;

काष्ठा isअगर_df_csc अणु
	/* Color Space Conversion configuration, 0 - csc, 1 - df */
	__u8 df_or_csc;
	/* csc configuration valid अगर df_or_csc is 0 */
	काष्ठा isअगर_color_space_conv csc;
	/* data क्रमmatter configuration valid अगर df_or_csc is 1 */
	काष्ठा isअगर_data_क्रमmatter df;
	/* start pixel in a line at the input */
	__u32 start_pix;
	/* number of pixels in input line */
	__u32 num_pixels;
	/* start line at the input */
	__u32 start_line;
	/* number of lines at the input */
	__u32 num_lines;
पूर्ण;

काष्ठा isअगर_gain_offsets_adj अणु
	/* Gain adjusपंचांगent per color */
	काष्ठा isअगर_gain gain;
	/* Offset adjusपंचांगent */
	__u16 offset;
	/* Enable or Disable Gain adjusपंचांगent क्रम SDRAM data */
	__u8 gain_sdram_en;
	/* Enable or Disable Gain adjusपंचांगent क्रम IPIPE data */
	__u8 gain_ipipe_en;
	/* Enable or Disable Gain adjusपंचांगent क्रम H3A data */
	__u8 gain_h3a_en;
	/* Enable or Disable Gain adjusपंचांगent क्रम SDRAM data */
	__u8 offset_sdram_en;
	/* Enable or Disable Gain adjusपंचांगent क्रम IPIPE data */
	__u8 offset_ipipe_en;
	/* Enable or Disable Gain adjusपंचांगent क्रम H3A data */
	__u8 offset_h3a_en;
पूर्ण;

काष्ठा isअगर_cul अणु
	/* Horizontal Cull pattern क्रम odd lines */
	__u8 hcpat_odd;
	/* Horizontal Cull pattern क्रम even lines */
	__u8 hcpat_even;
	/* Vertical Cull pattern */
	__u8 vcpat;
	/* Enable or disable lpf. Apply when cull is enabled */
	__u8 en_lpf;
पूर्ण;

काष्ठा isअगर_compress अणु
#घोषणा ISIF_ALAW		0
#घोषणा ISIF_DPCM		1
#घोषणा ISIF_NO_COMPRESSION	2
	/* Compression Algorithm used */
	__u8 alg;
	/* Choose Predictor1 क्रम DPCM compression */
#घोषणा ISIF_DPCM_PRED1		0
	/* Choose Predictor2 क्रम DPCM compression */
#घोषणा ISIF_DPCM_PRED2		1
	/* Predictor क्रम DPCM compression */
	__u8 pred;
पूर्ण;

/* all the stuff in this काष्ठा will be provided by userland */
काष्ठा isअगर_config_params_raw अणु
	/* Linearization parameters क्रम image sensor data input */
	काष्ठा isअगर_linearize linearize;
	/* Data क्रमmatter or CSC */
	काष्ठा isअगर_df_csc df_csc;
	/* Defect Pixel Correction (DFC) configuration */
	काष्ठा isअगर_dfc dfc;
	/* Black/Digital Clamp configuration */
	काष्ठा isअगर_black_clamp bclamp;
	/* Gain, offset adjusपंचांगents */
	काष्ठा isअगर_gain_offsets_adj gain_offset;
	/* Culling */
	काष्ठा isअगर_cul culling;
	/* A-Law and DPCM compression options */
	काष्ठा isअगर_compress compress;
	/* horizontal offset क्रम Gain/LSC/DFC */
	__u16 horz_offset;
	/* vertical offset क्रम Gain/LSC/DFC */
	__u16 vert_offset;
	/* color pattern क्रम field 0 */
	काष्ठा isअगर_col_pat col_pat_field0;
	/* color pattern क्रम field 1 */
	काष्ठा isअगर_col_pat col_pat_field1;
#घोषणा ISIF_NO_SHIFT		0
#घोषणा	ISIF_1BIT_SHIFT		1
#घोषणा	ISIF_2BIT_SHIFT		2
#घोषणा	ISIF_3BIT_SHIFT		3
#घोषणा	ISIF_4BIT_SHIFT		4
#घोषणा ISIF_5BIT_SHIFT		5
#घोषणा ISIF_6BIT_SHIFT		6
	/* Data shअगरt applied beक्रमe storing to SDRAM */
	__u8 data_shअगरt;
	/* enable input test pattern generation */
	__u8 test_pat_gen;
पूर्ण;

#अगर_घोषित __KERNEL__
काष्ठा isअगर_ycbcr_config अणु
	/* isअगर pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* isअगर frame क्रमmat */
	क्रमागत ccdc_frmfmt frm_fmt;
	/* ISIF crop winकरोw */
	काष्ठा v4l2_rect win;
	/* field polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* पूर्णांकerface VD polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* पूर्णांकerface HD polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* isअगर pix order. Only used क्रम ycbcr capture */
	क्रमागत ccdc_pixorder pix_order;
	/* isअगर buffer type. Only used क्रम ycbcr capture */
	क्रमागत ccdc_buftype buf_type;
पूर्ण;

/* MSB of image data connected to sensor port */
क्रमागत isअगर_data_msb अणु
	ISIF_BIT_MSB_15,
	ISIF_BIT_MSB_14,
	ISIF_BIT_MSB_13,
	ISIF_BIT_MSB_12,
	ISIF_BIT_MSB_11,
	ISIF_BIT_MSB_10,
	ISIF_BIT_MSB_9,
	ISIF_BIT_MSB_8,
	ISIF_BIT_MSB_7
पूर्ण;

क्रमागत isअगर_cfa_pattern अणु
	ISIF_CFA_PAT_MOSAIC,
	ISIF_CFA_PAT_STRIPE
पूर्ण;

काष्ठा isअगर_params_raw अणु
	/* isअगर pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* isअगर frame क्रमmat */
	क्रमागत ccdc_frmfmt frm_fmt;
	/* video winकरोw */
	काष्ठा v4l2_rect win;
	/* field polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* पूर्णांकerface VD polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* पूर्णांकerface HD polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* buffer type. Applicable क्रम पूर्णांकerlaced mode */
	क्रमागत ccdc_buftype buf_type;
	/* Gain values */
	काष्ठा isअगर_gain gain;
	/* cfa pattern */
	क्रमागत isअगर_cfa_pattern cfa_pat;
	/* Data MSB position */
	क्रमागत isअगर_data_msb data_msb;
	/* Enable horizontal flip */
	अचिन्हित अक्षर horz_flip_en;
	/* Enable image invert vertically */
	अचिन्हित अक्षर image_invert_en;

	/* all the userland defined stuff*/
	काष्ठा isअगर_config_params_raw config_params;
पूर्ण;

क्रमागत isअगर_data_pack अणु
	ISIF_PACK_16BIT,
	ISIF_PACK_12BIT,
	ISIF_PACK_8BIT
पूर्ण;

#घोषणा ISIF_WIN_NTSC				अणु0, 0, 720, 480पूर्ण
#घोषणा ISIF_WIN_VGA				अणु0, 0, 640, 480पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
