<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005-2009 Texas Instruments Inc
 */
#अगर_अघोषित _DM355_CCDC_H
#घोषणा _DM355_CCDC_H
#समावेश <media/davinci/ccdc_types.h>
#समावेश <media/davinci/vpfe_types.h>

/* क्रमागत क्रम No of pixel per line to be avg. in Black Clamping */
क्रमागत ccdc_sample_length अणु
	CCDC_SAMPLE_1PIXELS,
	CCDC_SAMPLE_2PIXELS,
	CCDC_SAMPLE_4PIXELS,
	CCDC_SAMPLE_8PIXELS,
	CCDC_SAMPLE_16PIXELS
पूर्ण;

/* क्रमागत क्रम No of lines in Black Clamping */
क्रमागत ccdc_sample_line अणु
	CCDC_SAMPLE_1LINES,
	CCDC_SAMPLE_2LINES,
	CCDC_SAMPLE_4LINES,
	CCDC_SAMPLE_8LINES,
	CCDC_SAMPLE_16LINES
पूर्ण;

/* क्रमागत क्रम Alaw gamma width */
क्रमागत ccdc_gamma_width अणु
	CCDC_GAMMA_BITS_13_4,
	CCDC_GAMMA_BITS_12_3,
	CCDC_GAMMA_BITS_11_2,
	CCDC_GAMMA_BITS_10_1,
	CCDC_GAMMA_BITS_09_0
पूर्ण;

क्रमागत ccdc_colpats अणु
	CCDC_RED,
	CCDC_GREEN_RED,
	CCDC_GREEN_BLUE,
	CCDC_BLUE
पूर्ण;

काष्ठा ccdc_col_pat अणु
	क्रमागत ccdc_colpats olop;
	क्रमागत ccdc_colpats olep;
	क्रमागत ccdc_colpats elop;
	क्रमागत ccdc_colpats elep;
पूर्ण;

क्रमागत ccdc_datasft अणु
	CCDC_DATA_NO_SHIFT,
	CCDC_DATA_SHIFT_1BIT,
	CCDC_DATA_SHIFT_2BIT,
	CCDC_DATA_SHIFT_3BIT,
	CCDC_DATA_SHIFT_4BIT,
	CCDC_DATA_SHIFT_5BIT,
	CCDC_DATA_SHIFT_6BIT
पूर्ण;

क्रमागत ccdc_data_size अणु
	CCDC_DATA_16BITS,
	CCDC_DATA_15BITS,
	CCDC_DATA_14BITS,
	CCDC_DATA_13BITS,
	CCDC_DATA_12BITS,
	CCDC_DATA_11BITS,
	CCDC_DATA_10BITS,
	CCDC_DATA_8BITS
पूर्ण;
क्रमागत ccdc_mfilt1 अणु
	CCDC_NO_MEDIAN_FILTER1,
	CCDC_AVERAGE_FILTER1,
	CCDC_MEDIAN_FILTER1
पूर्ण;

क्रमागत ccdc_mfilt2 अणु
	CCDC_NO_MEDIAN_FILTER2,
	CCDC_AVERAGE_FILTER2,
	CCDC_MEDIAN_FILTER2
पूर्ण;

/* काष्ठाure क्रम ALaw */
काष्ठा ccdc_a_law अणु
	/* Enable/disable A-Law */
	अचिन्हित अक्षर enable;
	/* Gamma Width Input */
	क्रमागत ccdc_gamma_width gamma_wd;
पूर्ण;

/* काष्ठाure क्रम Black Clamping */
काष्ठा ccdc_black_clamp अणु
	/* only अगर bClampEnable is TRUE */
	अचिन्हित अक्षर b_clamp_enable;
	/* only अगर bClampEnable is TRUE */
	क्रमागत ccdc_sample_length sample_pixel;
	/* only अगर bClampEnable is TRUE */
	क्रमागत ccdc_sample_line sample_ln;
	/* only अगर bClampEnable is TRUE */
	अचिन्हित लघु start_pixel;
	/* only अगर bClampEnable is FALSE */
	अचिन्हित लघु sgain;
	अचिन्हित लघु dc_sub;
पूर्ण;

/* काष्ठाure क्रम Black Level Compensation */
काष्ठा ccdc_black_compensation अणु
	/* Constant value to subtract from Red component */
	अचिन्हित अक्षर r;
	/* Constant value to subtract from Gr component */
	अचिन्हित अक्षर gr;
	/* Constant value to subtract from Blue component */
	अचिन्हित अक्षर b;
	/* Constant value to subtract from Gb component */
	अचिन्हित अक्षर gb;
पूर्ण;

काष्ठा ccdc_भग्न अणु
	पूर्णांक पूर्णांकeger;
	अचिन्हित पूर्णांक decimal;
पूर्ण;

#घोषणा CCDC_CSC_COEFF_TABLE_SIZE	16
/* काष्ठाure क्रम color space converter */
काष्ठा ccdc_csc अणु
	अचिन्हित अक्षर enable;
	/*
	 * S8Q5. Use 2 decimal precision, user values range from -3.00 to 3.99.
	 * example - to use 1.03, set पूर्णांकeger part as 1, and decimal part as 3
	 * to use -1.03, set पूर्णांकeger part as -1 and decimal part as 3
	 */
	काष्ठा ccdc_भग्न coeff[CCDC_CSC_COEFF_TABLE_SIZE];
पूर्ण;

/* Structures क्रम Vertical Defect Correction*/
क्रमागत ccdc_vdf_csl अणु
	CCDC_VDF_NORMAL,
	CCDC_VDF_HORZ_INTERPOL_SAT,
	CCDC_VDF_HORZ_INTERPOL
पूर्ण;

क्रमागत ccdc_vdf_cuda अणु
	CCDC_VDF_WHOLE_LINE_CORRECT,
	CCDC_VDF_UPPER_DISABLE
पूर्ण;

क्रमागत ccdc_dfc_mwr अणु
	CCDC_DFC_MWR_WRITE_COMPLETE,
	CCDC_DFC_WRITE_REG
पूर्ण;

क्रमागत ccdc_dfc_mrd अणु
	CCDC_DFC_READ_COMPLETE,
	CCDC_DFC_READ_REG
पूर्ण;

क्रमागत ccdc_dfc_ma_rst अणु
	CCDC_DFC_INCR_ADDR,
	CCDC_DFC_CLR_ADDR
पूर्ण;

क्रमागत ccdc_dfc_mclr अणु
	CCDC_DFC_CLEAR_COMPLETE,
	CCDC_DFC_CLEAR
पूर्ण;

काष्ठा ccdc_dft_corr_ctl अणु
	क्रमागत ccdc_vdf_csl vdfcsl;
	क्रमागत ccdc_vdf_cuda vdfcuda;
	अचिन्हित पूर्णांक vdflsft;
पूर्ण;

काष्ठा ccdc_dft_corr_mem_ctl अणु
	क्रमागत ccdc_dfc_mwr dfcmwr;
	क्रमागत ccdc_dfc_mrd dfcmrd;
	क्रमागत ccdc_dfc_ma_rst dfcmarst;
	क्रमागत ccdc_dfc_mclr dfcmclr;
पूर्ण;

#घोषणा CCDC_DFT_TABLE_SIZE	16
/*
 * Main Structure क्रम vertical defect correction. Vertical defect
 * correction can correct up to 16 defects अगर defects less than 16
 * then pad the rest with 0
 */
काष्ठा ccdc_vertical_dft अणु
	अचिन्हित अक्षर ver_dft_en;
	अचिन्हित अक्षर gen_dft_en;
	अचिन्हित पूर्णांक saturation_ctl;
	काष्ठा ccdc_dft_corr_ctl dft_corr_ctl;
	काष्ठा ccdc_dft_corr_mem_ctl dft_corr_mem_ctl;
	पूर्णांक table_size;
	अचिन्हित पूर्णांक dft_corr_horz[CCDC_DFT_TABLE_SIZE];
	अचिन्हित पूर्णांक dft_corr_vert[CCDC_DFT_TABLE_SIZE];
	अचिन्हित पूर्णांक dft_corr_sub1[CCDC_DFT_TABLE_SIZE];
	अचिन्हित पूर्णांक dft_corr_sub2[CCDC_DFT_TABLE_SIZE];
	अचिन्हित पूर्णांक dft_corr_sub3[CCDC_DFT_TABLE_SIZE];
पूर्ण;

काष्ठा ccdc_data_offset अणु
	अचिन्हित अक्षर horz_offset;
	अचिन्हित अक्षर vert_offset;
पूर्ण;

/*
 * Structure क्रम CCDC configuration parameters क्रम raw capture mode passed
 * by application
 */
काष्ठा ccdc_config_params_raw अणु
	/* data shअगरt to be applied beक्रमe storing */
	क्रमागत ccdc_datasft datasft;
	/* data size value from 8 to 16 bits */
	क्रमागत ccdc_data_size data_sz;
	/* median filter क्रम sdram */
	क्रमागत ccdc_mfilt1 mfilt1;
	क्रमागत ccdc_mfilt2 mfilt2;
	/* low pass filter enable/disable */
	अचिन्हित अक्षर lpf_enable;
	/* Threshold of median filter */
	पूर्णांक med_filt_thres;
	/*
	 * horz and vertical data offset. Applicable क्रम defect correction
	 * and lsc
	 */
	काष्ठा ccdc_data_offset data_offset;
	/* Structure क्रम Optional A-Law */
	काष्ठा ccdc_a_law alaw;
	/* Structure क्रम Optical Black Clamp */
	काष्ठा ccdc_black_clamp blk_clamp;
	/* Structure क्रम Black Compensation */
	काष्ठा ccdc_black_compensation blk_comp;
	/* काष्ठाure क्रम vertical Defect Correction Module Configuration */
	काष्ठा ccdc_vertical_dft vertical_dft;
	/* काष्ठाure क्रम color space converter Module Configuration */
	काष्ठा ccdc_csc csc;
	/* color patters क्रम bayer capture */
	काष्ठा ccdc_col_pat col_pat_field0;
	काष्ठा ccdc_col_pat col_pat_field1;
पूर्ण;

#अगर_घोषित __KERNEL__
#समावेश <linux/पन.स>

#घोषणा CCDC_WIN_PAL	अणु0, 0, 720, 576पूर्ण
#घोषणा CCDC_WIN_VGA	अणु0, 0, 640, 480पूर्ण

काष्ठा ccdc_params_ycbcr अणु
	/* pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* progressive or पूर्णांकerlaced frame */
	क्रमागत ccdc_frmfmt frm_fmt;
	/* video winकरोw */
	काष्ठा v4l2_rect win;
	/* field id polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* vertical sync polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* horizontal sync polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* enable BT.656 embedded sync mode */
	पूर्णांक bt656_enable;
	/* cb:y:cr:y or y:cb:y:cr in memory */
	क्रमागत ccdc_pixorder pix_order;
	/* पूर्णांकerleaved or separated fields  */
	क्रमागत ccdc_buftype buf_type;
पूर्ण;

/* Gain applied to Raw Bayer data */
काष्ठा ccdc_gain अणु
	अचिन्हित लघु r_ye;
	अचिन्हित लघु gr_cy;
	अचिन्हित लघु gb_g;
	अचिन्हित लघु b_mg;
पूर्ण;

/* Structure क्रम CCDC configuration parameters क्रम raw capture mode */
काष्ठा ccdc_params_raw अणु
	/* pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* progressive or पूर्णांकerlaced frame */
	क्रमागत ccdc_frmfmt frm_fmt;
	/* video winकरोw */
	काष्ठा v4l2_rect win;
	/* field id polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* vertical sync polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* horizontal sync polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* पूर्णांकerleaved or separated fields */
	क्रमागत ccdc_buftype buf_type;
	/* Gain values */
	काष्ठा ccdc_gain gain;
	/* offset */
	अचिन्हित पूर्णांक ccdc_offset;
	/* horizontal flip enable */
	अचिन्हित अक्षर horz_flip_enable;
	/*
	 * enable to store the image in inverse order in memory
	 * (bottom to top)
	 */
	अचिन्हित अक्षर image_invert_enable;
	/* Configurable part of raw data */
	काष्ठा ccdc_config_params_raw config_params;
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर				/* DM355_CCDC_H */
