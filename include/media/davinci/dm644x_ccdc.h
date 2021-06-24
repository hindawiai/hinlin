<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006-2009 Texas Instruments Inc
 */
#अगर_अघोषित _DM644X_CCDC_H
#घोषणा _DM644X_CCDC_H
#समावेश <media/davinci/ccdc_types.h>
#समावेश <media/davinci/vpfe_types.h>

/* क्रमागत क्रम No of pixel per line to be avg. in Black Clamping*/
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
	CCDC_GAMMA_BITS_15_6,	/* use bits 15-6 क्रम gamma */
	CCDC_GAMMA_BITS_14_5,
	CCDC_GAMMA_BITS_13_4,
	CCDC_GAMMA_BITS_12_3,
	CCDC_GAMMA_BITS_11_2,
	CCDC_GAMMA_BITS_10_1,
	CCDC_GAMMA_BITS_09_0	/* use bits 9-0 क्रम gamma */
पूर्ण;

/* वापसs the highest bit used क्रम the gamma */
अटल अंतरभूत u8 ccdc_gamma_width_max_bit(क्रमागत ccdc_gamma_width width)
अणु
	वापस 15 - width;
पूर्ण

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

/* वापसs the highest bit used क्रम this data size */
अटल अंतरभूत u8 ccdc_data_size_max_bit(क्रमागत ccdc_data_size sz)
अणु
	वापस sz == CCDC_DATA_8BITS ? 7 : 15 - sz;
पूर्ण

/* काष्ठाure क्रम ALaw */
काष्ठा ccdc_a_law अणु
	/* Enable/disable A-Law */
	अचिन्हित अक्षर enable;
	/* Gamma Width Input */
	क्रमागत ccdc_gamma_width gamma_wd;
पूर्ण;

/* काष्ठाure क्रम Black Clamping */
काष्ठा ccdc_black_clamp अणु
	अचिन्हित अक्षर enable;
	/* only अगर bClampEnable is TRUE */
	क्रमागत ccdc_sample_length sample_pixel;
	/* only अगर bClampEnable is TRUE */
	क्रमागत ccdc_sample_line sample_ln;
	/* only अगर bClampEnable is TRUE */
	अचिन्हित लघु start_pixel;
	/* only अगर bClampEnable is TRUE */
	अचिन्हित लघु sgain;
	/* only अगर bClampEnable is FALSE */
	अचिन्हित लघु dc_sub;
पूर्ण;

/* काष्ठाure क्रम Black Level Compensation */
काष्ठा ccdc_black_compensation अणु
	/* Constant value to subtract from Red component */
	अक्षर r;
	/* Constant value to subtract from Gr component */
	अक्षर gr;
	/* Constant value to subtract from Blue component */
	अक्षर b;
	/* Constant value to subtract from Gb component */
	अक्षर gb;
पूर्ण;

/* Structure क्रम CCDC configuration parameters क्रम raw capture mode passed
 * by application
 */
काष्ठा ccdc_config_params_raw अणु
	/* data size value from 8 to 16 bits */
	क्रमागत ccdc_data_size data_sz;
	/* Structure क्रम Optional A-Law */
	काष्ठा ccdc_a_law alaw;
	/* Structure क्रम Optical Black Clamp */
	काष्ठा ccdc_black_clamp blk_clamp;
	/* Structure क्रम Black Compensation */
	काष्ठा ccdc_black_compensation blk_comp;
पूर्ण;


#अगर_घोषित __KERNEL__
#समावेश <linux/पन.स>
/* Define to enable/disable video port */
#घोषणा FP_NUM_BYTES		4
/* Define क्रम extra pixel/line and extra lines/frame */
#घोषणा NUM_EXTRAPIXELS		8
#घोषणा NUM_EXTRALINES		8

/* settings क्रम commonly used video क्रमmats */
#घोषणा CCDC_WIN_PAL     अणु0, 0, 720, 576पूर्ण
/* ntsc square pixel */
#घोषणा CCDC_WIN_VGA	अणु0, 0, (640 + NUM_EXTRAPIXELS), (480 + NUM_EXTRALINES)पूर्ण

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
	/*
	 * enable to store the image in inverse
	 * order in memory(bottom to top)
	 */
	अचिन्हित अक्षर image_invert_enable;
	/* configurable parameters */
	काष्ठा ccdc_config_params_raw config_params;
पूर्ण;

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
#पूर्ण_अगर
#पूर्ण_अगर				/* _DM644X_CCDC_H */
