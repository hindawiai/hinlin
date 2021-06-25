<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_TABLES_H
#घोषणा __IPU3_TABLES_H

#समावेश <linux/bitops.h>

#समावेश "ipu3-abi.h"

#घोषणा IMGU_BDS_GRANULARITY		32	/* Downscaling granularity */
#घोषणा IMGU_BDS_MIN_SF_INV		IMGU_BDS_GRANULARITY
#घोषणा IMGU_BDS_CONFIG_LEN		97

#घोषणा IMGU_SCALER_DOWNSCALE_4TAPS_LEN	128
#घोषणा IMGU_SCALER_DOWNSCALE_2TAPS_LEN	64
#घोषणा IMGU_SCALER_FP			BIT(31) /* 1.0 in fixed poपूर्णांक */

#घोषणा IMGU_XNR3_VMEM_LUT_LEN		16

#घोषणा IMGU_GDC_LUT_UNIT		4
#घोषणा IMGU_GDC_LUT_LEN		256

काष्ठा imgu_css_bds_config अणु
	काष्ठा imgu_abi_bds_phase_arr hor_phase_arr;
	काष्ठा imgu_abi_bds_phase_arr ver_phase_arr;
	काष्ठा imgu_abi_bds_ptrn_arr ptrn_arr;
	u16 sample_patrn_length;
	u8 hor_ds_en;
	u8 ver_ds_en;
पूर्ण;

काष्ठा imgu_css_xnr3_vmem_शेषs अणु
	s16 x[IMGU_XNR3_VMEM_LUT_LEN];
	s16 a[IMGU_XNR3_VMEM_LUT_LEN];
	s16 b[IMGU_XNR3_VMEM_LUT_LEN];
	s16 c[IMGU_XNR3_VMEM_LUT_LEN];
पूर्ण;

बाह्य स्थिर काष्ठा imgu_css_bds_config
			imgu_css_bds_configs[IMGU_BDS_CONFIG_LEN];
बाह्य स्थिर s32 imgu_css_करोwnscale_4taps[IMGU_SCALER_DOWNSCALE_4TAPS_LEN];
बाह्य स्थिर s32 imgu_css_करोwnscale_2taps[IMGU_SCALER_DOWNSCALE_2TAPS_LEN];
बाह्य स्थिर s16 imgu_css_gdc_lut[IMGU_GDC_LUT_UNIT][IMGU_GDC_LUT_LEN];
बाह्य स्थिर काष्ठा imgu_css_xnr3_vmem_शेषs imgu_css_xnr3_vmem_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_bnr_अटल_config imgu_css_bnr_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_dm_config imgu_css_dm_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_ccm_mat_config imgu_css_ccm_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_gamma_corr_lut imgu_css_gamma_lut;
बाह्य स्थिर काष्ठा ipu3_uapi_csc_mat_config imgu_css_csc_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_cds_params imgu_css_cds_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_shd_config_अटल imgu_css_shd_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp1_iefd_config imgu_css_iefd_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp1_yds_config imgu_css_yds_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp1_chnr_config imgu_css_chnr_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp1_y_ee_nr_config imgu_css_y_ee_nr_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp2_tcc_gain_pcwl_lut_अटल_config
						imgu_css_tcc_gain_pcwl_lut;
बाह्य स्थिर काष्ठा ipu3_uapi_yuvp2_tcc_r_sqr_lut_अटल_config
						imgu_css_tcc_r_sqr_lut;
बाह्य स्थिर काष्ठा imgu_abi_anr_config imgu_css_anr_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_awb_fr_config_s imgu_css_awb_fr_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_ae_grid_config imgu_css_ae_grid_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_ae_ccm imgu_css_ae_ccm_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_af_config_s imgu_css_af_शेषs;
बाह्य स्थिर काष्ठा ipu3_uapi_awb_config_s imgu_css_awb_शेषs;

#पूर्ण_अगर
