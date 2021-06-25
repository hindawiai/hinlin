<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - Params subdevice
 *
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>	/* क्रम ISP params */

#समावेश "rkisp1-common.h"

#घोषणा RKISP1_PARAMS_DEV_NAME	RKISP1_DRIVER_NAME "_params"

#घोषणा RKISP1_ISP_PARAMS_REQ_BUFS_MIN	2
#घोषणा RKISP1_ISP_PARAMS_REQ_BUFS_MAX	8

#घोषणा RKISP1_ISP_DPCC_LINE_THRESH(n) \
			(RKISP1_CIF_ISP_DPCC_LINE_THRESH_1 + 0x14 * (n))
#घोषणा RKISP1_ISP_DPCC_LINE_MAD_FAC(n) \
			(RKISP1_CIF_ISP_DPCC_LINE_MAD_FAC_1 + 0x14 * (n))
#घोषणा RKISP1_ISP_DPCC_PG_FAC(n) \
			(RKISP1_CIF_ISP_DPCC_PG_FAC_1 + 0x14 * (n))
#घोषणा RKISP1_ISP_DPCC_RND_THRESH(n) \
			(RKISP1_CIF_ISP_DPCC_RND_THRESH_1 + 0x14 * (n))
#घोषणा RKISP1_ISP_DPCC_RG_FAC(n) \
			(RKISP1_CIF_ISP_DPCC_RG_FAC_1 + 0x14 * (n))
#घोषणा RKISP1_ISP_CC_COEFF(n) \
			(RKISP1_CIF_ISP_CC_COEFF_0 + (n) * 4)

अटल अंतरभूत व्योम
rkisp1_param_set_bits(काष्ठा rkisp1_params *params, u32 reg, u32 bit_mask)
अणु
	u32 val;

	val = rkisp1_पढ़ो(params->rkisp1, reg);
	rkisp1_ग_लिखो(params->rkisp1, val | bit_mask, reg);
पूर्ण

अटल अंतरभूत व्योम
rkisp1_param_clear_bits(काष्ठा rkisp1_params *params, u32 reg, u32 bit_mask)
अणु
	u32 val;

	val = rkisp1_पढ़ो(params->rkisp1, reg);
	rkisp1_ग_लिखो(params->rkisp1, val & ~bit_mask, reg);
पूर्ण

/* ISP BP पूर्णांकerface function */
अटल व्योम rkisp1_dpcc_config(काष्ठा rkisp1_params *params,
			       स्थिर काष्ठा rkisp1_cअगर_isp_dpcc_config *arg)
अणु
	अचिन्हित पूर्णांक i;
	u32 mode;

	/* aव्योम to override the old enable value */
	mode = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_DPCC_MODE);
	mode &= RKISP1_CIF_ISP_DPCC_ENA;
	mode |= arg->mode & ~RKISP1_CIF_ISP_DPCC_ENA;
	rkisp1_ग_लिखो(params->rkisp1, mode, RKISP1_CIF_ISP_DPCC_MODE);
	rkisp1_ग_लिखो(params->rkisp1, arg->output_mode,
		     RKISP1_CIF_ISP_DPCC_OUTPUT_MODE);
	rkisp1_ग_लिखो(params->rkisp1, arg->set_use,
		     RKISP1_CIF_ISP_DPCC_SET_USE);

	rkisp1_ग_लिखो(params->rkisp1, arg->methods[0].method,
		     RKISP1_CIF_ISP_DPCC_METHODS_SET_1);
	rkisp1_ग_लिखो(params->rkisp1, arg->methods[1].method,
		     RKISP1_CIF_ISP_DPCC_METHODS_SET_2);
	rkisp1_ग_लिखो(params->rkisp1, arg->methods[2].method,
		     RKISP1_CIF_ISP_DPCC_METHODS_SET_3);
	क्रम (i = 0; i < RKISP1_CIF_ISP_DPCC_METHODS_MAX; i++) अणु
		rkisp1_ग_लिखो(params->rkisp1, arg->methods[i].line_thresh,
			     RKISP1_ISP_DPCC_LINE_THRESH(i));
		rkisp1_ग_लिखो(params->rkisp1, arg->methods[i].line_mad_fac,
			     RKISP1_ISP_DPCC_LINE_MAD_FAC(i));
		rkisp1_ग_लिखो(params->rkisp1, arg->methods[i].pg_fac,
			     RKISP1_ISP_DPCC_PG_FAC(i));
		rkisp1_ग_लिखो(params->rkisp1, arg->methods[i].rnd_thresh,
			     RKISP1_ISP_DPCC_RND_THRESH(i));
		rkisp1_ग_लिखो(params->rkisp1, arg->methods[i].rg_fac,
			     RKISP1_ISP_DPCC_RG_FAC(i));
	पूर्ण

	rkisp1_ग_लिखो(params->rkisp1, arg->rnd_offs,
		     RKISP1_CIF_ISP_DPCC_RND_OFFS);
	rkisp1_ग_लिखो(params->rkisp1, arg->ro_limits,
		     RKISP1_CIF_ISP_DPCC_RO_LIMITS);
पूर्ण

/* ISP black level subtraction पूर्णांकerface function */
अटल व्योम rkisp1_bls_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_bls_config *arg)
अणु
	/* aव्योम to override the old enable value */
	u32 new_control;

	new_control = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_BLS_CTRL);
	new_control &= RKISP1_CIF_ISP_BLS_ENA;
	/* fixed subtraction values */
	अगर (!arg->enable_स्वतः) अणु
		स्थिर काष्ठा rkisp1_cअगर_isp_bls_fixed_val *pval =
								&arg->fixed_val;

		चयन (params->raw_type) अणु
		हाल RKISP1_RAW_BGGR:
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->r, RKISP1_CIF_ISP_BLS_D_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gr, RKISP1_CIF_ISP_BLS_C_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gb, RKISP1_CIF_ISP_BLS_B_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->b, RKISP1_CIF_ISP_BLS_A_FIXED);
			अवरोध;
		हाल RKISP1_RAW_GBRG:
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->r, RKISP1_CIF_ISP_BLS_C_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gr, RKISP1_CIF_ISP_BLS_D_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gb, RKISP1_CIF_ISP_BLS_A_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->b, RKISP1_CIF_ISP_BLS_B_FIXED);
			अवरोध;
		हाल RKISP1_RAW_GRBG:
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->r, RKISP1_CIF_ISP_BLS_B_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gr, RKISP1_CIF_ISP_BLS_A_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gb, RKISP1_CIF_ISP_BLS_D_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->b, RKISP1_CIF_ISP_BLS_C_FIXED);
			अवरोध;
		हाल RKISP1_RAW_RGGB:
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->r, RKISP1_CIF_ISP_BLS_A_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gr, RKISP1_CIF_ISP_BLS_B_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->gb, RKISP1_CIF_ISP_BLS_C_FIXED);
			rkisp1_ग_लिखो(params->rkisp1,
				     pval->b, RKISP1_CIF_ISP_BLS_D_FIXED);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (arg->en_winकरोws & BIT(1)) अणु
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw2.h_offs,
				     RKISP1_CIF_ISP_BLS_H2_START);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw2.h_size,
				     RKISP1_CIF_ISP_BLS_H2_STOP);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw2.v_offs,
				     RKISP1_CIF_ISP_BLS_V2_START);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw2.v_size,
				     RKISP1_CIF_ISP_BLS_V2_STOP);
			new_control |= RKISP1_CIF_ISP_BLS_WINDOW_2;
		पूर्ण

		अगर (arg->en_winकरोws & BIT(0)) अणु
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw1.h_offs,
				     RKISP1_CIF_ISP_BLS_H1_START);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw1.h_size,
				     RKISP1_CIF_ISP_BLS_H1_STOP);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw1.v_offs,
				     RKISP1_CIF_ISP_BLS_V1_START);
			rkisp1_ग_लिखो(params->rkisp1, arg->bls_winकरोw1.v_size,
				     RKISP1_CIF_ISP_BLS_V1_STOP);
			new_control |= RKISP1_CIF_ISP_BLS_WINDOW_1;
		पूर्ण

		rkisp1_ग_लिखो(params->rkisp1, arg->bls_samples,
			     RKISP1_CIF_ISP_BLS_SAMPLES);

		new_control |= RKISP1_CIF_ISP_BLS_MODE_MEASURED;
	पूर्ण
	rkisp1_ग_लिखो(params->rkisp1, new_control, RKISP1_CIF_ISP_BLS_CTRL);
पूर्ण

/* ISP LS correction पूर्णांकerface function */
अटल व्योम
rkisp1_lsc_correct_matrix_config(काष्ठा rkisp1_params *params,
				 स्थिर काष्ठा rkisp1_cअगर_isp_lsc_config *pconfig)
अणु
	अचिन्हित पूर्णांक isp_lsc_status, sram_addr, isp_lsc_table_sel, i, j, data;

	isp_lsc_status = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_LSC_STATUS);

	/* RKISP1_CIF_ISP_LSC_TABLE_ADDRESS_153 = ( 17 * 18 ) >> 1 */
	sram_addr = (isp_lsc_status & RKISP1_CIF_ISP_LSC_ACTIVE_TABLE) ?
		    RKISP1_CIF_ISP_LSC_TABLE_ADDRESS_0 :
		    RKISP1_CIF_ISP_LSC_TABLE_ADDRESS_153;
	rkisp1_ग_लिखो(params->rkisp1, sram_addr,
		     RKISP1_CIF_ISP_LSC_R_TABLE_ADDR);
	rkisp1_ग_लिखो(params->rkisp1, sram_addr,
		     RKISP1_CIF_ISP_LSC_GR_TABLE_ADDR);
	rkisp1_ग_लिखो(params->rkisp1, sram_addr,
		     RKISP1_CIF_ISP_LSC_GB_TABLE_ADDR);
	rkisp1_ग_लिखो(params->rkisp1, sram_addr,
		     RKISP1_CIF_ISP_LSC_B_TABLE_ADDR);

	/* program data tables (table size is 9 * 17 = 153) */
	क्रम (i = 0; i < RKISP1_CIF_ISP_LSC_SAMPLES_MAX; i++) अणु
		/*
		 * 17 sectors with 2 values in one DWORD = 9
		 * DWORDs (2nd value of last DWORD unused)
		 */
		क्रम (j = 0; j < RKISP1_CIF_ISP_LSC_SAMPLES_MAX - 1; j += 2) अणु
			data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->r_data_tbl[i][j],
							     pconfig->r_data_tbl[i][j + 1]);
			rkisp1_ग_लिखो(params->rkisp1, data,
				     RKISP1_CIF_ISP_LSC_R_TABLE_DATA);

			data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->gr_data_tbl[i][j],
							     pconfig->gr_data_tbl[i][j + 1]);
			rkisp1_ग_लिखो(params->rkisp1, data,
				     RKISP1_CIF_ISP_LSC_GR_TABLE_DATA);

			data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->gb_data_tbl[i][j],
							     pconfig->gb_data_tbl[i][j + 1]);
			rkisp1_ग_लिखो(params->rkisp1, data,
				     RKISP1_CIF_ISP_LSC_GB_TABLE_DATA);

			data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->b_data_tbl[i][j],
							     pconfig->b_data_tbl[i][j + 1]);
			rkisp1_ग_लिखो(params->rkisp1, data,
				     RKISP1_CIF_ISP_LSC_B_TABLE_DATA);
		पूर्ण
		data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->r_data_tbl[i][j], 0);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_R_TABLE_DATA);

		data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->gr_data_tbl[i][j], 0);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_GR_TABLE_DATA);

		data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->gb_data_tbl[i][j], 0);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_GB_TABLE_DATA);

		data = RKISP1_CIF_ISP_LSC_TABLE_DATA(pconfig->b_data_tbl[i][j], 0);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_B_TABLE_DATA);
	पूर्ण
	isp_lsc_table_sel = (isp_lsc_status & RKISP1_CIF_ISP_LSC_ACTIVE_TABLE) ?
			    RKISP1_CIF_ISP_LSC_TABLE_0 :
			    RKISP1_CIF_ISP_LSC_TABLE_1;
	rkisp1_ग_लिखो(params->rkisp1, isp_lsc_table_sel,
		     RKISP1_CIF_ISP_LSC_TABLE_SEL);
पूर्ण

अटल व्योम rkisp1_lsc_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_lsc_config *arg)
अणु
	अचिन्हित पूर्णांक i, data;
	u32 lsc_ctrl;

	/* To config must be off , store the current status firstly */
	lsc_ctrl = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_LSC_CTRL);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_LSC_CTRL,
				RKISP1_CIF_ISP_LSC_CTRL_ENA);
	rkisp1_lsc_correct_matrix_config(params, arg);

	क्रम (i = 0; i < RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE / 2; i++) अणु
		/* program x size tables */
		data = RKISP1_CIF_ISP_LSC_SECT_SIZE(arg->x_माप_प्रकारbl[i * 2],
						    arg->x_माप_प्रकारbl[i * 2 + 1]);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_XSIZE_01 + i * 4);

		/* program x grad tables */
		data = RKISP1_CIF_ISP_LSC_SECT_SIZE(arg->x_grad_tbl[i * 2],
						    arg->x_grad_tbl[i * 2 + 1]);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_XGRAD_01 + i * 4);

		/* program y size tables */
		data = RKISP1_CIF_ISP_LSC_SECT_SIZE(arg->y_माप_प्रकारbl[i * 2],
						    arg->y_माप_प्रकारbl[i * 2 + 1]);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_YSIZE_01 + i * 4);

		/* program y grad tables */
		data = RKISP1_CIF_ISP_LSC_SECT_SIZE(arg->y_grad_tbl[i * 2],
						    arg->y_grad_tbl[i * 2 + 1]);
		rkisp1_ग_लिखो(params->rkisp1, data,
			     RKISP1_CIF_ISP_LSC_YGRAD_01 + i * 4);
	पूर्ण

	/* restore the lsc ctrl status */
	अगर (lsc_ctrl & RKISP1_CIF_ISP_LSC_CTRL_ENA) अणु
		rkisp1_param_set_bits(params,
				      RKISP1_CIF_ISP_LSC_CTRL,
				      RKISP1_CIF_ISP_LSC_CTRL_ENA);
	पूर्ण अन्यथा अणु
		rkisp1_param_clear_bits(params,
					RKISP1_CIF_ISP_LSC_CTRL,
					RKISP1_CIF_ISP_LSC_CTRL_ENA);
	पूर्ण
पूर्ण

/* ISP Filtering function */
अटल व्योम rkisp1_flt_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_flt_config *arg)
अणु
	u32 filt_mode;

	rkisp1_ग_लिखो(params->rkisp1,
		     arg->thresh_bl0, RKISP1_CIF_ISP_FILT_THRESH_BL0);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->thresh_bl1, RKISP1_CIF_ISP_FILT_THRESH_BL1);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->thresh_sh0, RKISP1_CIF_ISP_FILT_THRESH_SH0);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->thresh_sh1, RKISP1_CIF_ISP_FILT_THRESH_SH1);
	rkisp1_ग_लिखो(params->rkisp1, arg->fac_bl0, RKISP1_CIF_ISP_FILT_FAC_BL0);
	rkisp1_ग_लिखो(params->rkisp1, arg->fac_bl1, RKISP1_CIF_ISP_FILT_FAC_BL1);
	rkisp1_ग_लिखो(params->rkisp1, arg->fac_mid, RKISP1_CIF_ISP_FILT_FAC_MID);
	rkisp1_ग_लिखो(params->rkisp1, arg->fac_sh0, RKISP1_CIF_ISP_FILT_FAC_SH0);
	rkisp1_ग_लिखो(params->rkisp1, arg->fac_sh1, RKISP1_CIF_ISP_FILT_FAC_SH1);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->lum_weight, RKISP1_CIF_ISP_FILT_LUM_WEIGHT);

	rkisp1_ग_लिखो(params->rkisp1,
		     (arg->mode ? RKISP1_CIF_ISP_FLT_MODE_DNR : 0) |
		     RKISP1_CIF_ISP_FLT_CHROMA_V_MODE(arg->chr_v_mode) |
		     RKISP1_CIF_ISP_FLT_CHROMA_H_MODE(arg->chr_h_mode) |
		     RKISP1_CIF_ISP_FLT_GREEN_STAGE1(arg->grn_stage1),
		     RKISP1_CIF_ISP_FILT_MODE);

	/* aव्योम to override the old enable value */
	filt_mode = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_FILT_MODE);
	filt_mode &= RKISP1_CIF_ISP_FLT_ENA;
	अगर (arg->mode)
		filt_mode |= RKISP1_CIF_ISP_FLT_MODE_DNR;
	filt_mode |= RKISP1_CIF_ISP_FLT_CHROMA_V_MODE(arg->chr_v_mode) |
		     RKISP1_CIF_ISP_FLT_CHROMA_H_MODE(arg->chr_h_mode) |
		     RKISP1_CIF_ISP_FLT_GREEN_STAGE1(arg->grn_stage1);
	rkisp1_ग_लिखो(params->rkisp1, filt_mode, RKISP1_CIF_ISP_FILT_MODE);
पूर्ण

/* ISP demosaic पूर्णांकerface function */
अटल पूर्णांक rkisp1_bdm_config(काष्ठा rkisp1_params *params,
			     स्थिर काष्ठा rkisp1_cअगर_isp_bdm_config *arg)
अणु
	u32 bdm_th;

	/* aव्योम to override the old enable value */
	bdm_th = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_DEMOSAIC);
	bdm_th &= RKISP1_CIF_ISP_DEMOSAIC_BYPASS;
	bdm_th |= arg->demosaic_th & ~RKISP1_CIF_ISP_DEMOSAIC_BYPASS;
	/* set demosaic threshold */
	rkisp1_ग_लिखो(params->rkisp1, bdm_th, RKISP1_CIF_ISP_DEMOSAIC);
	वापस 0;
पूर्ण

/* ISP GAMMA correction पूर्णांकerface function */
अटल व्योम rkisp1_sdg_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_sdg_config *arg)
अणु
	अचिन्हित पूर्णांक i;

	rkisp1_ग_लिखो(params->rkisp1,
		     arg->xa_pnts.gamma_dx0, RKISP1_CIF_ISP_GAMMA_DX_LO);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->xa_pnts.gamma_dx1, RKISP1_CIF_ISP_GAMMA_DX_HI);

	क्रम (i = 0; i < RKISP1_CIF_ISP_DEGAMMA_CURVE_SIZE; i++) अणु
		rkisp1_ग_लिखो(params->rkisp1, arg->curve_r.gamma_y[i],
			     RKISP1_CIF_ISP_GAMMA_R_Y0 + i * 4);
		rkisp1_ग_लिखो(params->rkisp1, arg->curve_g.gamma_y[i],
			     RKISP1_CIF_ISP_GAMMA_G_Y0 + i * 4);
		rkisp1_ग_लिखो(params->rkisp1, arg->curve_b.gamma_y[i],
			     RKISP1_CIF_ISP_GAMMA_B_Y0 + i * 4);
	पूर्ण
पूर्ण

/* ISP GAMMA correction पूर्णांकerface function */
अटल व्योम rkisp1_goc_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_goc_config *arg)
अणु
	अचिन्हित पूर्णांक i;

	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
				RKISP1_CIF_ISP_CTRL_ISP_GAMMA_OUT_ENA);
	rkisp1_ग_लिखो(params->rkisp1, arg->mode, RKISP1_CIF_ISP_GAMMA_OUT_MODE);

	क्रम (i = 0; i < RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V10; i++)
		rkisp1_ग_लिखो(params->rkisp1, arg->gamma_y[i],
			     RKISP1_CIF_ISP_GAMMA_OUT_Y_0 + i * 4);
पूर्ण

/* ISP Cross Talk */
अटल व्योम rkisp1_ctk_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_ctk_config *arg)
अणु
	अचिन्हित पूर्णांक i, j, k = 0;

	क्रम (i = 0; i < 3; i++)
		क्रम (j = 0; j < 3; j++)
			rkisp1_ग_लिखो(params->rkisp1, arg->coeff[i][j],
				     RKISP1_CIF_ISP_CT_COEFF_0 + 4 * k++);
	क्रम (i = 0; i < 3; i++)
		rkisp1_ग_लिखो(params->rkisp1, arg->ct_offset[i],
			     RKISP1_CIF_ISP_CT_OFFSET_R + i * 4);
पूर्ण

अटल व्योम rkisp1_ctk_enable(काष्ठा rkisp1_params *params, bool en)
अणु
	अगर (en)
		वापस;

	/* Write back the शेष values. */
	rkisp1_ग_लिखो(params->rkisp1, 0x80, RKISP1_CIF_ISP_CT_COEFF_0);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_1);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_2);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_3);
	rkisp1_ग_लिखो(params->rkisp1, 0x80, RKISP1_CIF_ISP_CT_COEFF_4);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_5);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_6);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_COEFF_7);
	rkisp1_ग_लिखो(params->rkisp1, 0x80, RKISP1_CIF_ISP_CT_COEFF_8);

	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_OFFSET_R);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_OFFSET_G);
	rkisp1_ग_लिखो(params->rkisp1, 0, RKISP1_CIF_ISP_CT_OFFSET_B);
पूर्ण

/* ISP White Balance Mode */
अटल व्योम rkisp1_awb_meas_config(काष्ठा rkisp1_params *params,
				   स्थिर काष्ठा rkisp1_cअगर_isp_awb_meas_config *arg)
अणु
	u32 reg_val = 0;
	/* based on the mode,configure the awb module */
	अगर (arg->awb_mode == RKISP1_CIF_ISP_AWB_MODE_YCBCR) अणु
		/* Reference Cb and Cr */
		rkisp1_ग_लिखो(params->rkisp1,
			     RKISP1_CIF_ISP_AWB_REF_CR_SET(arg->awb_ref_cr) |
			     arg->awb_ref_cb, RKISP1_CIF_ISP_AWB_REF);
		/* Yc Threshold */
		rkisp1_ग_लिखो(params->rkisp1,
			     RKISP1_CIF_ISP_AWB_MAX_Y_SET(arg->max_y) |
			     RKISP1_CIF_ISP_AWB_MIN_Y_SET(arg->min_y) |
			     RKISP1_CIF_ISP_AWB_MAX_CS_SET(arg->max_csum) |
			     arg->min_c, RKISP1_CIF_ISP_AWB_THRESH);
	पूर्ण

	reg_val = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_AWB_PROP);
	अगर (arg->enable_ymax_cmp)
		reg_val |= RKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	अन्यथा
		reg_val &= ~RKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	rkisp1_ग_लिखो(params->rkisp1, reg_val, RKISP1_CIF_ISP_AWB_PROP);

	/* winकरोw offset */
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->awb_wnd.v_offs, RKISP1_CIF_ISP_AWB_WND_V_OFFS);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->awb_wnd.h_offs, RKISP1_CIF_ISP_AWB_WND_H_OFFS);
	/* AWB winकरोw size */
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->awb_wnd.v_size, RKISP1_CIF_ISP_AWB_WND_V_SIZE);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->awb_wnd.h_size, RKISP1_CIF_ISP_AWB_WND_H_SIZE);
	/* Number of frames */
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->frames, RKISP1_CIF_ISP_AWB_FRAMES);
पूर्ण

अटल व्योम
rkisp1_awb_meas_enable(काष्ठा rkisp1_params *params,
		       स्थिर काष्ठा rkisp1_cअगर_isp_awb_meas_config *arg,
		       bool en)
अणु
	u32 reg_val = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_AWB_PROP);

	/* चयन off */
	reg_val &= RKISP1_CIF_ISP_AWB_MODE_MASK_NONE;

	अगर (en) अणु
		अगर (arg->awb_mode == RKISP1_CIF_ISP_AWB_MODE_RGB)
			reg_val |= RKISP1_CIF_ISP_AWB_MODE_RGB_EN;
		अन्यथा
			reg_val |= RKISP1_CIF_ISP_AWB_MODE_YCBCR_EN;

		rkisp1_ग_लिखो(params->rkisp1, reg_val, RKISP1_CIF_ISP_AWB_PROP);

		/* Measurements require AWB block be active. */
		rkisp1_param_set_bits(params, RKISP1_CIF_ISP_CTRL,
				      RKISP1_CIF_ISP_CTRL_ISP_AWB_ENA);
	पूर्ण अन्यथा अणु
		rkisp1_ग_लिखो(params->rkisp1,
			     reg_val, RKISP1_CIF_ISP_AWB_PROP);
		rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
					RKISP1_CIF_ISP_CTRL_ISP_AWB_ENA);
	पूर्ण
पूर्ण

अटल व्योम
rkisp1_awb_gain_config(काष्ठा rkisp1_params *params,
		       स्थिर काष्ठा rkisp1_cअगर_isp_awb_gain_config *arg)
अणु
	rkisp1_ग_लिखो(params->rkisp1,
		     RKISP1_CIF_ISP_AWB_GAIN_R_SET(arg->gain_green_r) |
		     arg->gain_green_b, RKISP1_CIF_ISP_AWB_GAIN_G);

	rkisp1_ग_लिखो(params->rkisp1,
		     RKISP1_CIF_ISP_AWB_GAIN_R_SET(arg->gain_red) |
		     arg->gain_blue, RKISP1_CIF_ISP_AWB_GAIN_RB);
पूर्ण

अटल व्योम rkisp1_aec_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_aec_config *arg)
अणु
	अचिन्हित पूर्णांक block_hsize, block_vsize;
	u32 exp_ctrl;

	/* aव्योम to override the old enable value */
	exp_ctrl = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_EXP_CTRL);
	exp_ctrl &= RKISP1_CIF_ISP_EXP_ENA;
	अगर (arg->स्वतःstop)
		exp_ctrl |= RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP;
	अगर (arg->mode == RKISP1_CIF_ISP_EXP_MEASURING_MODE_1)
		exp_ctrl |= RKISP1_CIF_ISP_EXP_CTRL_MEASMODE_1;
	rkisp1_ग_लिखो(params->rkisp1, exp_ctrl, RKISP1_CIF_ISP_EXP_CTRL);

	rkisp1_ग_लिखो(params->rkisp1,
		     arg->meas_winकरोw.h_offs, RKISP1_CIF_ISP_EXP_H_OFFSET);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->meas_winकरोw.v_offs, RKISP1_CIF_ISP_EXP_V_OFFSET);

	block_hsize = arg->meas_winकरोw.h_size /
		      RKISP1_CIF_ISP_EXP_COLUMN_NUM - 1;
	block_vsize = arg->meas_winकरोw.v_size /
		      RKISP1_CIF_ISP_EXP_ROW_NUM - 1;

	rkisp1_ग_लिखो(params->rkisp1,
		     RKISP1_CIF_ISP_EXP_H_SIZE_SET(block_hsize),
		     RKISP1_CIF_ISP_EXP_H_SIZE);
	rkisp1_ग_लिखो(params->rkisp1,
		     RKISP1_CIF_ISP_EXP_V_SIZE_SET(block_vsize),
		     RKISP1_CIF_ISP_EXP_V_SIZE);
पूर्ण

अटल व्योम rkisp1_cproc_config(काष्ठा rkisp1_params *params,
				स्थिर काष्ठा rkisp1_cअगर_isp_cproc_config *arg)
अणु
	काष्ठा rkisp1_cअगर_isp_isp_other_cfg *cur_other_cfg =
		container_of(arg, काष्ठा rkisp1_cअगर_isp_isp_other_cfg, cproc_config);
	काष्ठा rkisp1_cअगर_isp_ie_config *cur_ie_config =
						&cur_other_cfg->ie_config;
	u32 effect = cur_ie_config->effect;
	u32 quantization = params->quantization;

	rkisp1_ग_लिखो(params->rkisp1, arg->contrast, RKISP1_CIF_C_PROC_CONTRAST);
	rkisp1_ग_लिखो(params->rkisp1, arg->hue, RKISP1_CIF_C_PROC_HUE);
	rkisp1_ग_लिखो(params->rkisp1, arg->sat, RKISP1_CIF_C_PROC_SATURATION);
	rkisp1_ग_लिखो(params->rkisp1, arg->brightness,
		     RKISP1_CIF_C_PROC_BRIGHTNESS);

	अगर (quantization != V4L2_QUANTIZATION_FULL_RANGE ||
	    effect != V4L2_COLORFX_NONE) अणु
		rkisp1_param_clear_bits(params, RKISP1_CIF_C_PROC_CTRL,
					RKISP1_CIF_C_PROC_YOUT_FULL |
					RKISP1_CIF_C_PROC_YIN_FULL |
					RKISP1_CIF_C_PROC_COUT_FULL);
	पूर्ण अन्यथा अणु
		rkisp1_param_set_bits(params, RKISP1_CIF_C_PROC_CTRL,
				      RKISP1_CIF_C_PROC_YOUT_FULL |
				      RKISP1_CIF_C_PROC_YIN_FULL |
				      RKISP1_CIF_C_PROC_COUT_FULL);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_hst_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_hst_config *arg)
अणु
	अचिन्हित पूर्णांक block_hsize, block_vsize;
	अटल स्थिर u32 hist_weight_regs[] = अणु
		RKISP1_CIF_ISP_HIST_WEIGHT_00TO30,
		RKISP1_CIF_ISP_HIST_WEIGHT_40TO21,
		RKISP1_CIF_ISP_HIST_WEIGHT_31TO12,
		RKISP1_CIF_ISP_HIST_WEIGHT_22TO03,
		RKISP1_CIF_ISP_HIST_WEIGHT_13TO43,
		RKISP1_CIF_ISP_HIST_WEIGHT_04TO34,
	पूर्ण;
	स्थिर u8 *weight;
	अचिन्हित पूर्णांक i;
	u32 hist_prop;

	/* aव्योम to override the old enable value */
	hist_prop = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_HIST_PROP);
	hist_prop &= RKISP1_CIF_ISP_HIST_PROP_MODE_MASK;
	hist_prop |= RKISP1_CIF_ISP_HIST_PREDIV_SET(arg->histogram_preभागider);
	rkisp1_ग_लिखो(params->rkisp1, hist_prop, RKISP1_CIF_ISP_HIST_PROP);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->meas_winकरोw.h_offs,
		     RKISP1_CIF_ISP_HIST_H_OFFS);
	rkisp1_ग_लिखो(params->rkisp1,
		     arg->meas_winकरोw.v_offs,
		     RKISP1_CIF_ISP_HIST_V_OFFS);

	block_hsize = arg->meas_winकरोw.h_size /
		      RKISP1_CIF_ISP_HIST_COLUMN_NUM - 1;
	block_vsize = arg->meas_winकरोw.v_size / RKISP1_CIF_ISP_HIST_ROW_NUM - 1;

	rkisp1_ग_लिखो(params->rkisp1, block_hsize, RKISP1_CIF_ISP_HIST_H_SIZE);
	rkisp1_ग_लिखो(params->rkisp1, block_vsize, RKISP1_CIF_ISP_HIST_V_SIZE);

	weight = arg->hist_weight;
	क्रम (i = 0; i < ARRAY_SIZE(hist_weight_regs); ++i, weight += 4)
		rkisp1_ग_लिखो(params->rkisp1,
			     RKISP1_CIF_ISP_HIST_WEIGHT_SET(weight[0],
							    weight[1],
							    weight[2],
							    weight[3]),
				 hist_weight_regs[i]);

	rkisp1_ग_लिखो(params->rkisp1, weight[0] & 0x1F, RKISP1_CIF_ISP_HIST_WEIGHT_44);
पूर्ण

अटल व्योम
rkisp1_hst_enable(काष्ठा rkisp1_params *params,
		  स्थिर काष्ठा rkisp1_cअगर_isp_hst_config *arg, bool en)
अणु
	अगर (en)	अणु
		u32 hist_prop = rkisp1_पढ़ो(params->rkisp1,
					    RKISP1_CIF_ISP_HIST_PROP);

		hist_prop &= ~RKISP1_CIF_ISP_HIST_PROP_MODE_MASK;
		hist_prop |= arg->mode;
		rkisp1_param_set_bits(params, RKISP1_CIF_ISP_HIST_PROP,
				      hist_prop);
	पूर्ण अन्यथा अणु
		rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_HIST_PROP,
					RKISP1_CIF_ISP_HIST_PROP_MODE_MASK);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_afm_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_afc_config *arg)
अणु
	माप_प्रकार num_of_win = min_t(माप_प्रकार, ARRAY_SIZE(arg->afm_win),
				  arg->num_afm_win);
	u32 afm_ctrl = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_ISP_AFM_CTRL);
	अचिन्हित पूर्णांक i;

	/* Switch off to configure. */
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_AFM_CTRL,
				RKISP1_CIF_ISP_AFM_ENA);

	क्रम (i = 0; i < num_of_win; i++) अणु
		rkisp1_ग_लिखो(params->rkisp1,
			     RKISP1_CIF_ISP_AFM_WINDOW_X(arg->afm_win[i].h_offs) |
			     RKISP1_CIF_ISP_AFM_WINDOW_Y(arg->afm_win[i].v_offs),
			     RKISP1_CIF_ISP_AFM_LT_A + i * 8);
		rkisp1_ग_लिखो(params->rkisp1,
			     RKISP1_CIF_ISP_AFM_WINDOW_X(arg->afm_win[i].h_size +
							 arg->afm_win[i].h_offs) |
			     RKISP1_CIF_ISP_AFM_WINDOW_Y(arg->afm_win[i].v_size +
							 arg->afm_win[i].v_offs),
			     RKISP1_CIF_ISP_AFM_RB_A + i * 8);
	पूर्ण
	rkisp1_ग_लिखो(params->rkisp1, arg->thres, RKISP1_CIF_ISP_AFM_THRES);
	rkisp1_ग_लिखो(params->rkisp1, arg->var_shअगरt,
		     RKISP1_CIF_ISP_AFM_VAR_SHIFT);
	/* restore afm status */
	rkisp1_ग_लिखो(params->rkisp1, afm_ctrl, RKISP1_CIF_ISP_AFM_CTRL);
पूर्ण

अटल व्योम rkisp1_ie_config(काष्ठा rkisp1_params *params,
			     स्थिर काष्ठा rkisp1_cअगर_isp_ie_config *arg)
अणु
	u32 eff_ctrl;

	eff_ctrl = rkisp1_पढ़ो(params->rkisp1, RKISP1_CIF_IMG_EFF_CTRL);
	eff_ctrl &= ~RKISP1_CIF_IMG_EFF_CTRL_MODE_MASK;

	अगर (params->quantization == V4L2_QUANTIZATION_FULL_RANGE)
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_YCBCR_FULL;

	चयन (arg->effect) अणु
	हाल V4L2_COLORFX_SEPIA:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_SEPIA;
		अवरोध;
	हाल V4L2_COLORFX_SET_CBCR:
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_tपूर्णांक,
			     RKISP1_CIF_IMG_EFF_TINT);
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_SEPIA;
		अवरोध;
		/*
		 * Color selection is similar to water color(AQUA):
		 * grayscale + selected color w threshold
		 */
	हाल V4L2_COLORFX_AQUA:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_COLOR_SEL;
		rkisp1_ग_लिखो(params->rkisp1, arg->color_sel,
			     RKISP1_CIF_IMG_EFF_COLOR_SEL);
		अवरोध;
	हाल V4L2_COLORFX_EMBOSS:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_EMBOSS;
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_1,
			     RKISP1_CIF_IMG_EFF_MAT_1);
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_2,
			     RKISP1_CIF_IMG_EFF_MAT_2);
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_3,
			     RKISP1_CIF_IMG_EFF_MAT_3);
		अवरोध;
	हाल V4L2_COLORFX_SKETCH:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_SKETCH;
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_3,
			     RKISP1_CIF_IMG_EFF_MAT_3);
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_4,
			     RKISP1_CIF_IMG_EFF_MAT_4);
		rkisp1_ग_लिखो(params->rkisp1, arg->eff_mat_5,
			     RKISP1_CIF_IMG_EFF_MAT_5);
		अवरोध;
	हाल V4L2_COLORFX_BW:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_BLACKWHITE;
		अवरोध;
	हाल V4L2_COLORFX_NEGATIVE:
		eff_ctrl |= RKISP1_CIF_IMG_EFF_CTRL_MODE_NEGATIVE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rkisp1_ग_लिखो(params->rkisp1, eff_ctrl, RKISP1_CIF_IMG_EFF_CTRL);
पूर्ण

अटल व्योम rkisp1_ie_enable(काष्ठा rkisp1_params *params, bool en)
अणु
	अगर (en) अणु
		rkisp1_param_set_bits(params, RKISP1_CIF_ICCL,
				      RKISP1_CIF_ICCL_IE_CLK);
		rkisp1_ग_लिखो(params->rkisp1, RKISP1_CIF_IMG_EFF_CTRL_ENABLE,
			     RKISP1_CIF_IMG_EFF_CTRL);
		rkisp1_param_set_bits(params, RKISP1_CIF_IMG_EFF_CTRL,
				      RKISP1_CIF_IMG_EFF_CTRL_CFG_UPD);
	पूर्ण अन्यथा अणु
		rkisp1_param_clear_bits(params, RKISP1_CIF_IMG_EFF_CTRL,
					RKISP1_CIF_IMG_EFF_CTRL_ENABLE);
		rkisp1_param_clear_bits(params, RKISP1_CIF_ICCL,
					RKISP1_CIF_ICCL_IE_CLK);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_csm_config(काष्ठा rkisp1_params *params, bool full_range)
अणु
	अटल स्थिर u16 full_range_coeff[] = अणु
		0x0026, 0x004b, 0x000f,
		0x01ea, 0x01d6, 0x0040,
		0x0040, 0x01ca, 0x01f6
	पूर्ण;
	अटल स्थिर u16 limited_range_coeff[] = अणु
		0x0021, 0x0040, 0x000d,
		0x01ed, 0x01db, 0x0038,
		0x0038, 0x01d1, 0x01f7,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (full_range) अणु
		क्रम (i = 0; i < ARRAY_SIZE(full_range_coeff); i++)
			rkisp1_ग_लिखो(params->rkisp1, full_range_coeff[i],
				     RKISP1_CIF_ISP_CC_COEFF_0 + i * 4);

		rkisp1_param_set_bits(params, RKISP1_CIF_ISP_CTRL,
				      RKISP1_CIF_ISP_CTRL_ISP_CSM_Y_FULL_ENA |
				      RKISP1_CIF_ISP_CTRL_ISP_CSM_C_FULL_ENA);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(limited_range_coeff); i++)
			rkisp1_ग_लिखो(params->rkisp1, limited_range_coeff[i],
				     RKISP1_CIF_ISP_CC_COEFF_0 + i * 4);

		rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
					RKISP1_CIF_ISP_CTRL_ISP_CSM_Y_FULL_ENA |
					RKISP1_CIF_ISP_CTRL_ISP_CSM_C_FULL_ENA);
	पूर्ण
पूर्ण

/* ISP De-noise Pre-Filter(DPF) function */
अटल व्योम rkisp1_dpf_config(काष्ठा rkisp1_params *params,
			      स्थिर काष्ठा rkisp1_cअगर_isp_dpf_config *arg)
अणु
	अचिन्हित पूर्णांक isp_dpf_mode, spatial_coeff, i;

	चयन (arg->gain.mode) अणु
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS:
		isp_dpf_mode = RKISP1_CIF_ISP_DPF_MODE_USE_NF_GAIN |
			       RKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		अवरोध;
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_LSC_GAINS:
		isp_dpf_mode = RKISP1_CIF_ISP_DPF_MODE_LSC_GAIN_COMP;
		अवरोध;
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_LSC_GAINS:
		isp_dpf_mode = RKISP1_CIF_ISP_DPF_MODE_USE_NF_GAIN |
			       RKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP |
			       RKISP1_CIF_ISP_DPF_MODE_LSC_GAIN_COMP;
		अवरोध;
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS:
		isp_dpf_mode = RKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		अवरोध;
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_LSC_GAINS:
		isp_dpf_mode = RKISP1_CIF_ISP_DPF_MODE_LSC_GAIN_COMP |
			       RKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		अवरोध;
	हाल RKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABLED:
	शेष:
		isp_dpf_mode = 0;
		अवरोध;
	पूर्ण

	अगर (arg->nll.scale_mode == RKISP1_CIF_ISP_NLL_SCALE_LOGARITHMIC)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_NLL_SEGMENTATION;
	अगर (arg->rb_flt.fltsize == RKISP1_CIF_ISP_DPF_RB_FILTERSIZE_9x9)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_RB_FLTSIZE_9x9;
	अगर (!arg->rb_flt.r_enable)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_R_FLT_DIS;
	अगर (!arg->rb_flt.b_enable)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_B_FLT_DIS;
	अगर (!arg->g_flt.gb_enable)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_GB_FLT_DIS;
	अगर (!arg->g_flt.gr_enable)
		isp_dpf_mode |= RKISP1_CIF_ISP_DPF_MODE_GR_FLT_DIS;

	rkisp1_param_set_bits(params, RKISP1_CIF_ISP_DPF_MODE,
			      isp_dpf_mode);
	rkisp1_ग_लिखो(params->rkisp1, arg->gain.nf_b_gain,
		     RKISP1_CIF_ISP_DPF_NF_GAIN_B);
	rkisp1_ग_लिखो(params->rkisp1, arg->gain.nf_r_gain,
		     RKISP1_CIF_ISP_DPF_NF_GAIN_R);
	rkisp1_ग_लिखो(params->rkisp1, arg->gain.nf_gb_gain,
		     RKISP1_CIF_ISP_DPF_NF_GAIN_GB);
	rkisp1_ग_लिखो(params->rkisp1, arg->gain.nf_gr_gain,
		     RKISP1_CIF_ISP_DPF_NF_GAIN_GR);

	क्रम (i = 0; i < RKISP1_CIF_ISP_DPF_MAX_NLF_COEFFS; i++) अणु
		rkisp1_ग_लिखो(params->rkisp1, arg->nll.coeff[i],
			     RKISP1_CIF_ISP_DPF_शून्य_COEFF_0 + i * 4);
	पूर्ण

	spatial_coeff = arg->g_flt.spatial_coeff[0] |
			(arg->g_flt.spatial_coeff[1] << 8) |
			(arg->g_flt.spatial_coeff[2] << 16) |
			(arg->g_flt.spatial_coeff[3] << 24);
	rkisp1_ग_लिखो(params->rkisp1, spatial_coeff,
		     RKISP1_CIF_ISP_DPF_S_WEIGHT_G_1_4);

	spatial_coeff = arg->g_flt.spatial_coeff[4] |
			(arg->g_flt.spatial_coeff[5] << 8);
	rkisp1_ग_लिखो(params->rkisp1, spatial_coeff,
		     RKISP1_CIF_ISP_DPF_S_WEIGHT_G_5_6);

	spatial_coeff = arg->rb_flt.spatial_coeff[0] |
			(arg->rb_flt.spatial_coeff[1] << 8) |
			(arg->rb_flt.spatial_coeff[2] << 16) |
			(arg->rb_flt.spatial_coeff[3] << 24);
	rkisp1_ग_लिखो(params->rkisp1, spatial_coeff,
		     RKISP1_CIF_ISP_DPF_S_WEIGHT_RB_1_4);

	spatial_coeff = arg->rb_flt.spatial_coeff[4] |
			(arg->rb_flt.spatial_coeff[5] << 8);
	rkisp1_ग_लिखो(params->rkisp1, spatial_coeff,
		     RKISP1_CIF_ISP_DPF_S_WEIGHT_RB_5_6);
पूर्ण

अटल व्योम
rkisp1_dpf_strength_config(काष्ठा rkisp1_params *params,
			   स्थिर काष्ठा rkisp1_cअगर_isp_dpf_strength_config *arg)
अणु
	rkisp1_ग_लिखो(params->rkisp1, arg->b, RKISP1_CIF_ISP_DPF_STRENGTH_B);
	rkisp1_ग_लिखो(params->rkisp1, arg->g, RKISP1_CIF_ISP_DPF_STRENGTH_G);
	rkisp1_ग_लिखो(params->rkisp1, arg->r, RKISP1_CIF_ISP_DPF_STRENGTH_R);
पूर्ण

अटल व्योम
rkisp1_isp_isr_other_config(काष्ठा rkisp1_params *params,
			    स्थिर काष्ठा rkisp1_params_cfg *new_params)
अणु
	अचिन्हित पूर्णांक module_en_update, module_cfg_update, module_ens;

	module_en_update = new_params->module_en_update;
	module_cfg_update = new_params->module_cfg_update;
	module_ens = new_params->module_ens;

	/* update dpc config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_DPCC)
		rkisp1_dpcc_config(params,
				   &new_params->others.dpcc_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_DPCC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_DPCC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_DPCC_MODE,
					      RKISP1_CIF_ISP_DPCC_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_DPCC_MODE,
						RKISP1_CIF_ISP_DPCC_ENA);
	पूर्ण

	/* update bls config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_BLS)
		rkisp1_bls_config(params,
				  &new_params->others.bls_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_BLS) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_BLS)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_BLS_CTRL,
					      RKISP1_CIF_ISP_BLS_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_BLS_CTRL,
						RKISP1_CIF_ISP_BLS_ENA);
	पूर्ण

	/* update sdg config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_SDG)
		rkisp1_sdg_config(params,
				  &new_params->others.sdg_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_SDG) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_SDG)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_CTRL,
					      RKISP1_CIF_ISP_CTRL_ISP_GAMMA_IN_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_CTRL,
						RKISP1_CIF_ISP_CTRL_ISP_GAMMA_IN_ENA);
	पूर्ण

	/* update lsc config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_LSC)
		rkisp1_lsc_config(params,
				  &new_params->others.lsc_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_LSC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_LSC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_LSC_CTRL,
					      RKISP1_CIF_ISP_LSC_CTRL_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_LSC_CTRL,
						RKISP1_CIF_ISP_LSC_CTRL_ENA);
	पूर्ण

	/* update awb gains */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_AWB_GAIN)
		rkisp1_awb_gain_config(params, &new_params->others.awb_gain_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_AWB_GAIN) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_AWB_GAIN)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_CTRL,
					      RKISP1_CIF_ISP_CTRL_ISP_AWB_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_CTRL,
						RKISP1_CIF_ISP_CTRL_ISP_AWB_ENA);
	पूर्ण

	/* update bdm config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_BDM)
		rkisp1_bdm_config(params,
				  &new_params->others.bdm_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_BDM) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_BDM)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_DEMOSAIC,
					      RKISP1_CIF_ISP_DEMOSAIC_BYPASS);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_DEMOSAIC,
						RKISP1_CIF_ISP_DEMOSAIC_BYPASS);
	पूर्ण

	/* update filter config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_FLT)
		rkisp1_flt_config(params,
				  &new_params->others.flt_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_FLT) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_FLT)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_FILT_MODE,
					      RKISP1_CIF_ISP_FLT_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_FILT_MODE,
						RKISP1_CIF_ISP_FLT_ENA);
	पूर्ण

	/* update ctk config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_CTK)
		rkisp1_ctk_config(params,
				  &new_params->others.ctk_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_CTK)
		rkisp1_ctk_enable(params, !!(module_ens & RKISP1_CIF_ISP_MODULE_CTK));

	/* update goc config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_GOC)
		rkisp1_goc_config(params,
				  &new_params->others.goc_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_GOC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_GOC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_CTRL,
					      RKISP1_CIF_ISP_CTRL_ISP_GAMMA_OUT_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_CTRL,
						RKISP1_CIF_ISP_CTRL_ISP_GAMMA_OUT_ENA);
	पूर्ण

	/* update cproc config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_CPROC)
		rkisp1_cproc_config(params,
				    &new_params->others.cproc_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_CPROC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_CPROC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_C_PROC_CTRL,
					      RKISP1_CIF_C_PROC_CTR_ENABLE);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_C_PROC_CTRL,
						RKISP1_CIF_C_PROC_CTR_ENABLE);
	पूर्ण

	/* update ie config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_IE)
		rkisp1_ie_config(params, &new_params->others.ie_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_IE)
		rkisp1_ie_enable(params, !!(module_ens & RKISP1_CIF_ISP_MODULE_IE));

	/* update dpf config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_DPF)
		rkisp1_dpf_config(params, &new_params->others.dpf_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_DPF) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_DPF)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_DPF_MODE,
					      RKISP1_CIF_ISP_DPF_MODE_EN);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_DPF_MODE,
						RKISP1_CIF_ISP_DPF_MODE_EN);
	पूर्ण

	अगर ((module_en_update & RKISP1_CIF_ISP_MODULE_DPF_STRENGTH) ||
	    (module_cfg_update & RKISP1_CIF_ISP_MODULE_DPF_STRENGTH)) अणु
		/* update dpf strength config */
		rkisp1_dpf_strength_config(params,
					   &new_params->others.dpf_strength_config);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_isp_isr_meas_config(काष्ठा rkisp1_params *params,
				       काष्ठा  rkisp1_params_cfg *new_params)
अणु
	अचिन्हित पूर्णांक module_en_update, module_cfg_update, module_ens;

	module_en_update = new_params->module_en_update;
	module_cfg_update = new_params->module_cfg_update;
	module_ens = new_params->module_ens;

	/* update awb config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_AWB)
		rkisp1_awb_meas_config(params, &new_params->meas.awb_meas_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_AWB)
		rkisp1_awb_meas_enable(params,
				       &new_params->meas.awb_meas_config,
				       !!(module_ens & RKISP1_CIF_ISP_MODULE_AWB));

	/* update afc config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_AFC)
		rkisp1_afm_config(params,
				  &new_params->meas.afc_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_AFC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_AFC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_AFM_CTRL,
					      RKISP1_CIF_ISP_AFM_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_AFM_CTRL,
						RKISP1_CIF_ISP_AFM_ENA);
	पूर्ण

	/* update hst config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_HST)
		rkisp1_hst_config(params,
				  &new_params->meas.hst_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_HST)
		rkisp1_hst_enable(params,
				  &new_params->meas.hst_config,
				  !!(module_ens & RKISP1_CIF_ISP_MODULE_HST));

	/* update aec config */
	अगर (module_cfg_update & RKISP1_CIF_ISP_MODULE_AEC)
		rkisp1_aec_config(params,
				  &new_params->meas.aec_config);

	अगर (module_en_update & RKISP1_CIF_ISP_MODULE_AEC) अणु
		अगर (module_ens & RKISP1_CIF_ISP_MODULE_AEC)
			rkisp1_param_set_bits(params,
					      RKISP1_CIF_ISP_EXP_CTRL,
					      RKISP1_CIF_ISP_EXP_ENA);
		अन्यथा
			rkisp1_param_clear_bits(params,
						RKISP1_CIF_ISP_EXP_CTRL,
						RKISP1_CIF_ISP_EXP_ENA);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_params_apply_params_cfg(काष्ठा rkisp1_params *params,
					   अचिन्हित पूर्णांक frame_sequence)
अणु
	काष्ठा rkisp1_params_cfg *new_params;
	काष्ठा rkisp1_buffer *cur_buf = शून्य;

	अगर (list_empty(&params->params))
		वापस;

	cur_buf = list_first_entry(&params->params,
				   काष्ठा rkisp1_buffer, queue);

	new_params = (काष्ठा rkisp1_params_cfg *)(cur_buf->vaddr);

	rkisp1_isp_isr_other_config(params, new_params);
	rkisp1_isp_isr_meas_config(params, new_params);

	/* update shaकरोw रेजिस्टर immediately */
	rkisp1_param_set_bits(params, RKISP1_CIF_ISP_CTRL, RKISP1_CIF_ISP_CTRL_ISP_CFG_UPD);

	list_del(&cur_buf->queue);

	cur_buf->vb.sequence = frame_sequence;
	vb2_buffer_करोne(&cur_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

व्योम rkisp1_params_isr(काष्ठा rkisp1_device *rkisp1)
अणु
	/*
	 * This isr is called when the ISR finishes processing a frame (RKISP1_CIF_ISP_FRAME).
	 * Configurations perक्रमmed here will be applied on the next frame.
	 * Since frame_sequence is updated on the vertical sync संकेत, we should use
	 * frame_sequence + 1 here to indicate to userspace on which frame these parameters
	 * are being applied.
	 */
	अचिन्हित पूर्णांक frame_sequence = rkisp1->isp.frame_sequence + 1;
	काष्ठा rkisp1_params *params = &rkisp1->params;

	spin_lock(&params->config_lock);
	rkisp1_params_apply_params_cfg(params, frame_sequence);

	spin_unlock(&params->config_lock);
पूर्ण

अटल स्थिर काष्ठा rkisp1_cअगर_isp_awb_meas_config rkisp1_awb_params_शेष_config = अणु
	अणु
		0, 0, RKISP1_DEFAULT_WIDTH, RKISP1_DEFAULT_HEIGHT
	पूर्ण,
	RKISP1_CIF_ISP_AWB_MODE_YCBCR, 200, 30, 20, 20, 0, 128, 128
पूर्ण;

अटल स्थिर काष्ठा rkisp1_cअगर_isp_aec_config rkisp1_aec_params_शेष_config = अणु
	RKISP1_CIF_ISP_EXP_MEASURING_MODE_0,
	RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP_0,
	अणु
		RKISP1_DEFAULT_WIDTH >> 2, RKISP1_DEFAULT_HEIGHT >> 2,
		RKISP1_DEFAULT_WIDTH >> 1, RKISP1_DEFAULT_HEIGHT >> 1
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rkisp1_cअगर_isp_hst_config rkisp1_hst_params_शेष_config = अणु
	RKISP1_CIF_ISP_HISTOGRAM_MODE_RGB_COMBINED,
	3,
	अणु
		RKISP1_DEFAULT_WIDTH >> 2, RKISP1_DEFAULT_HEIGHT >> 2,
		RKISP1_DEFAULT_WIDTH >> 1, RKISP1_DEFAULT_HEIGHT >> 1
	पूर्ण,
	अणु
		0, /* To be filled in with 0x01 at runसमय. */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rkisp1_cअगर_isp_afc_config rkisp1_afc_params_शेष_config = अणु
	1,
	अणु
		अणु
			300, 225, 200, 150
		पूर्ण
	पूर्ण,
	4,
	14
पूर्ण;

अटल व्योम rkisp1_params_config_parameter(काष्ठा rkisp1_params *params)
अणु
	काष्ठा rkisp1_cअगर_isp_hst_config hst = rkisp1_hst_params_शेष_config;

	rkisp1_awb_meas_config(params, &rkisp1_awb_params_शेष_config);
	rkisp1_awb_meas_enable(params, &rkisp1_awb_params_शेष_config,
			       true);

	rkisp1_aec_config(params, &rkisp1_aec_params_शेष_config);
	rkisp1_param_set_bits(params, RKISP1_CIF_ISP_EXP_CTRL,
			      RKISP1_CIF_ISP_EXP_ENA);

	rkisp1_afm_config(params, &rkisp1_afc_params_शेष_config);
	rkisp1_param_set_bits(params, RKISP1_CIF_ISP_AFM_CTRL,
			      RKISP1_CIF_ISP_AFM_ENA);

	स_रखो(hst.hist_weight, 0x01, माप(hst.hist_weight));
	rkisp1_hst_config(params, &hst);
	rkisp1_param_set_bits(params, RKISP1_CIF_ISP_HIST_PROP,
			      rkisp1_hst_params_शेष_config.mode);

	/* set the  range */
	अगर (params->quantization == V4L2_QUANTIZATION_FULL_RANGE)
		rkisp1_csm_config(params, true);
	अन्यथा
		rkisp1_csm_config(params, false);

	spin_lock_irq(&params->config_lock);

	/* apply the first buffer अगर there is one alपढ़ोy */
	rkisp1_params_apply_params_cfg(params, 0);

	spin_unlock_irq(&params->config_lock);
पूर्ण

व्योम rkisp1_params_configure(काष्ठा rkisp1_params *params,
			     क्रमागत rkisp1_fmt_raw_pat_type bayer_pat,
			     क्रमागत v4l2_quantization quantization)
अणु
	params->quantization = quantization;
	params->raw_type = bayer_pat;
	rkisp1_params_config_parameter(params);
पूर्ण

/* Not called when the camera active, thus not isr protection. */
व्योम rkisp1_params_disable(काष्ठा rkisp1_params *params)
अणु
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_DPCC_MODE,
				RKISP1_CIF_ISP_DPCC_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_LSC_CTRL,
				RKISP1_CIF_ISP_LSC_CTRL_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_BLS_CTRL,
				RKISP1_CIF_ISP_BLS_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
				RKISP1_CIF_ISP_CTRL_ISP_GAMMA_IN_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
				RKISP1_CIF_ISP_CTRL_ISP_GAMMA_OUT_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_DEMOSAIC,
				RKISP1_CIF_ISP_DEMOSAIC_BYPASS);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_FILT_MODE,
				RKISP1_CIF_ISP_FLT_ENA);
	rkisp1_awb_meas_enable(params, शून्य, false);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_CTRL,
				RKISP1_CIF_ISP_CTRL_ISP_AWB_ENA);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_EXP_CTRL,
				RKISP1_CIF_ISP_EXP_ENA);
	rkisp1_ctk_enable(params, false);
	rkisp1_param_clear_bits(params, RKISP1_CIF_C_PROC_CTRL,
				RKISP1_CIF_C_PROC_CTR_ENABLE);
	rkisp1_hst_enable(params, शून्य, false);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_AFM_CTRL,
				RKISP1_CIF_ISP_AFM_ENA);
	rkisp1_ie_enable(params, false);
	rkisp1_param_clear_bits(params, RKISP1_CIF_ISP_DPF_MODE,
				RKISP1_CIF_ISP_DPF_MODE_EN);
पूर्ण

अटल पूर्णांक rkisp1_params_क्रमागत_fmt_meta_out(काष्ठा file *file, व्योम *priv,
					   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा video_device *video = video_devdata(file);
	काष्ठा rkisp1_params *params = video_get_drvdata(video);

	अगर (f->index > 0 || f->type != video->queue->type)
		वापस -EINVAL;

	f->pixelक्रमmat = params->vdev_fmt.fmt.meta.dataक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_params_g_fmt_meta_out(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *video = video_devdata(file);
	काष्ठा rkisp1_params *params = video_get_drvdata(video);
	काष्ठा v4l2_meta_क्रमmat *meta = &f->fmt.meta;

	अगर (f->type != video->queue->type)
		वापस -EINVAL;

	स_रखो(meta, 0, माप(*meta));
	meta->dataक्रमmat = params->vdev_fmt.fmt.meta.dataक्रमmat;
	meta->buffersize = params->vdev_fmt.fmt.meta.buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_params_querycap(काष्ठा file *file,
				  व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	strscpy(cap->driver, RKISP1_DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, vdev->name, माप(cap->card));
	strscpy(cap->bus_info, RKISP1_BUS_INFO, माप(cap->bus_info));

	वापस 0;
पूर्ण

/* ISP params video device IOCTLs */
अटल स्थिर काष्ठा v4l2_ioctl_ops rkisp1_params_ioctl = अणु
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_क्रमागत_fmt_meta_out = rkisp1_params_क्रमागत_fmt_meta_out,
	.vidioc_g_fmt_meta_out = rkisp1_params_g_fmt_meta_out,
	.vidioc_s_fmt_meta_out = rkisp1_params_g_fmt_meta_out,
	.vidioc_try_fmt_meta_out = rkisp1_params_g_fmt_meta_out,
	.vidioc_querycap = rkisp1_params_querycap,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक rkisp1_params_vb2_queue_setup(काष्ठा vb2_queue *vq,
					 अचिन्हित पूर्णांक *num_buffers,
					 अचिन्हित पूर्णांक *num_planes,
					 अचिन्हित पूर्णांक sizes[],
					 काष्ठा device *alloc_devs[])
अणु
	*num_buffers = clamp_t(u32, *num_buffers,
			       RKISP1_ISP_PARAMS_REQ_BUFS_MIN,
			       RKISP1_ISP_PARAMS_REQ_BUFS_MAX);

	*num_planes = 1;

	sizes[0] = माप(काष्ठा rkisp1_params_cfg);

	वापस 0;
पूर्ण

अटल व्योम rkisp1_params_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rkisp1_buffer *params_buf =
		container_of(vbuf, काष्ठा rkisp1_buffer, vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा rkisp1_params *params = vq->drv_priv;

	params_buf->vaddr = vb2_plane_vaddr(vb, 0);
	spin_lock_irq(&params->config_lock);
	list_add_tail(&params_buf->queue, &params->params);
	spin_unlock_irq(&params->config_lock);
पूर्ण

अटल पूर्णांक rkisp1_params_vb2_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	अगर (vb2_plane_size(vb, 0) < माप(काष्ठा rkisp1_params_cfg))
		वापस -EINVAL;

	vb2_set_plane_payload(vb, 0, माप(काष्ठा rkisp1_params_cfg));

	वापस 0;
पूर्ण

अटल व्योम rkisp1_params_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा rkisp1_params *params = vq->drv_priv;
	काष्ठा rkisp1_buffer *buf;
	LIST_HEAD(पंचांगp_list);

	/*
	 * we first move the buffers पूर्णांकo a local list 'tmp_list'
	 * and then we can iterate it and call vb2_buffer_करोne
	 * without holding the lock
	 */
	spin_lock_irq(&params->config_lock);
	list_splice_init(&params->params, &पंचांगp_list);
	spin_unlock_irq(&params->config_lock);

	list_क्रम_each_entry(buf, &पंचांगp_list, queue)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rkisp1_params_vb2_ops = अणु
	.queue_setup = rkisp1_params_vb2_queue_setup,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.buf_queue = rkisp1_params_vb2_buf_queue,
	.buf_prepare = rkisp1_params_vb2_buf_prepare,
	.stop_streaming = rkisp1_params_vb2_stop_streaming,

पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations rkisp1_params_fops = अणु
	.mmap = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
	.poll = vb2_fop_poll,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release
पूर्ण;

अटल पूर्णांक rkisp1_params_init_vb2_queue(काष्ठा vb2_queue *q,
					काष्ठा rkisp1_params *params)
अणु
	काष्ठा rkisp1_vdev_node *node;

	node = container_of(q, काष्ठा rkisp1_vdev_node, buf_queue);

	q->type = V4L2_BUF_TYPE_META_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = params;
	q->ops = &rkisp1_params_vb2_ops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->buf_काष्ठा_size = माप(काष्ठा rkisp1_buffer);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &node->vlock;

	वापस vb2_queue_init(q);
पूर्ण

अटल व्योम rkisp1_init_params(काष्ठा rkisp1_params *params)
अणु
	params->vdev_fmt.fmt.meta.dataक्रमmat =
		V4L2_META_FMT_RK_ISP1_PARAMS;
	params->vdev_fmt.fmt.meta.buffersize =
		माप(काष्ठा rkisp1_params_cfg);
पूर्ण

पूर्णांक rkisp1_params_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_params *params = &rkisp1->params;
	काष्ठा rkisp1_vdev_node *node = &params->vnode;
	काष्ठा video_device *vdev = &node->vdev;
	पूर्णांक ret;

	params->rkisp1 = rkisp1;
	mutex_init(&node->vlock);
	INIT_LIST_HEAD(&params->params);
	spin_lock_init(&params->config_lock);

	strscpy(vdev->name, RKISP1_PARAMS_DEV_NAME, माप(vdev->name));

	video_set_drvdata(vdev, params);
	vdev->ioctl_ops = &rkisp1_params_ioctl;
	vdev->fops = &rkisp1_params_fops;
	vdev->release = video_device_release_empty;
	/*
	 * Provide a mutex to v4l2 core. It will be used
	 * to protect all fops and v4l2 ioctls.
	 */
	vdev->lock = &node->vlock;
	vdev->v4l2_dev = &rkisp1->v4l2_dev;
	vdev->queue = &node->buf_queue;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_META_OUTPUT;
	vdev->vfl_dir = VFL_सूची_TX;
	rkisp1_params_init_vb2_queue(vdev->queue, params);
	rkisp1_init_params(params);
	video_set_drvdata(vdev, params);

	node->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&vdev->entity, 1, &node->pad);
	अगर (ret)
		वापस ret;
	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(rkisp1->dev,
			"failed to register %s, ret=%d\n", vdev->name, ret);
		जाओ err_cleanup_media_entity;
	पूर्ण
	वापस 0;
err_cleanup_media_entity:
	media_entity_cleanup(&vdev->entity);
	वापस ret;
पूर्ण

व्योम rkisp1_params_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_params *params = &rkisp1->params;
	काष्ठा rkisp1_vdev_node *node = &params->vnode;
	काष्ठा video_device *vdev = &node->vdev;

	vb2_video_unरेजिस्टर_device(vdev);
	media_entity_cleanup(&vdev->entity);
पूर्ण
