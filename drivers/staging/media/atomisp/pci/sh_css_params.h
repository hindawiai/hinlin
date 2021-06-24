<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _SH_CSS_PARAMS_H_
#घोषणा _SH_CSS_PARAMS_H_

/*! \पile */

/* Forward declaration to अवरोध mutual dependency */
काष्ठा ia_css_isp_parameters;

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_binary.h"
#समावेश "sh_css_legacy.h"

#समावेश "sh_css_defs.h"	/* SH_CSS_MAX_STAGES */
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_isp_params.h"
#समावेश "uds/uds_1.0/ia_css_uds_param.h"
#समावेश "crop/crop_1.0/ia_css_crop_types.h"

#घोषणा PIX_SHIFT_FILTER_RUN_IN_X 12
#घोषणा PIX_SHIFT_FILTER_RUN_IN_Y 12

#समावेश "ob/ob_1.0/ia_css_ob_param.h"
/* Isp configurations per stream */
काष्ठा sh_css_isp_param_configs अणु
	/* OB (Optical Black) */
	काष्ठा sh_css_isp_ob_stream_config ob;
पूर्ण;

/* Isp parameters per stream */
काष्ठा ia_css_isp_parameters अणु
	/* UDS */
	काष्ठा sh_css_sp_uds_params uds[SH_CSS_MAX_STAGES];
	काष्ठा sh_css_isp_param_configs stream_configs;
	काष्ठा ia_css_fpn_table     fpn_config;
	काष्ठा ia_css_vector	    motion_config;
	स्थिर काष्ठा ia_css_morph_table   *morph_table;
	स्थिर काष्ठा ia_css_shading_table *sc_table;
	काष्ठा ia_css_shading_table *sc_config;
	काष्ठा ia_css_macc_table    macc_table;
	काष्ठा ia_css_gamma_table   gc_table;
	काष्ठा ia_css_ctc_table     ctc_table;
	काष्ठा ia_css_xnr_table     xnr_table;

	काष्ठा ia_css_dz_config     dz_config;
	काष्ठा ia_css_3a_config     s3a_config;
	काष्ठा ia_css_wb_config     wb_config;
	काष्ठा ia_css_cc_config     cc_config;
	काष्ठा ia_css_cc_config     yuv2rgb_cc_config;
	काष्ठा ia_css_cc_config     rgb2yuv_cc_config;
	काष्ठा ia_css_tnr_config    tnr_config;
	काष्ठा ia_css_ob_config     ob_config;
	/*----- DPC configuration -----*/
	/* The शेष DPC configuration is retained and currently set
	 * using the stream configuration. The code generated from genparams
	 * uses this configuration to set the DPC parameters per stage but this
	 * will be overwritten by the per pipe configuration */
	काष्ठा ia_css_dp_config     dp_config;
	/* ------ pipe specअगरic DPC configuration ------ */
	/* Please note that this implementation is a temporary solution and
	 * should be replaced by CSS per pipe configuration when the support
	 * is पढ़ोy (HSD 1303967698)*/
	काष्ठा ia_css_dp_config     pipe_dp_config[IA_CSS_PIPE_ID_NUM];
	काष्ठा ia_css_nr_config     nr_config;
	काष्ठा ia_css_ee_config     ee_config;
	काष्ठा ia_css_de_config     de_config;
	काष्ठा ia_css_gc_config     gc_config;
	काष्ठा ia_css_anr_config    anr_config;
	काष्ठा ia_css_ce_config     ce_config;
	काष्ठा ia_css_क्रमmats_config     क्रमmats_config;
	/* ---- deprecated: replaced with pipe_dvs_6axis_config---- */
	काष्ठा ia_css_dvs_6axis_config  *dvs_6axis_config;
	काष्ठा ia_css_ecd_config    ecd_config;
	काष्ठा ia_css_ynr_config    ynr_config;
	काष्ठा ia_css_yee_config    yee_config;
	काष्ठा ia_css_fc_config     fc_config;
	काष्ठा ia_css_cnr_config    cnr_config;
	काष्ठा ia_css_macc_config   macc_config;
	काष्ठा ia_css_ctc_config    ctc_config;
	काष्ठा ia_css_aa_config     aa_config;
	काष्ठा ia_css_aa_config     bds_config;
	काष्ठा ia_css_aa_config     raa_config;
	काष्ठा ia_css_rgb_gamma_table     r_gamma_table;
	काष्ठा ia_css_rgb_gamma_table     g_gamma_table;
	काष्ठा ia_css_rgb_gamma_table     b_gamma_table;
	काष्ठा ia_css_anr_thres     anr_thres;
	काष्ठा ia_css_xnr_config    xnr_config;
	काष्ठा ia_css_xnr3_config   xnr3_config;
	काष्ठा ia_css_uds_config    uds_config;
	काष्ठा ia_css_crop_config   crop_config;
	काष्ठा ia_css_output_config output_config;
	काष्ठा ia_css_dvs_6axis_config  *pipe_dvs_6axis_config[IA_CSS_PIPE_ID_NUM];
	/* ------ deprecated(bz675) : from ------ */
	काष्ठा ia_css_shading_settings shading_settings;
	/* ------ deprecated(bz675) : to ------ */
	काष्ठा ia_css_dvs_coefficients  dvs_coefs;
	काष्ठा ia_css_dvs2_coefficients dvs2_coefs;

	bool isp_params_changed;

	bool isp_mem_params_changed
	[IA_CSS_PIPE_ID_NUM][SH_CSS_MAX_STAGES][IA_CSS_NUM_MEMORIES];
	bool dz_config_changed;
	bool motion_config_changed;
	bool dis_coef_table_changed;
	bool dvs2_coef_table_changed;
	bool morph_table_changed;
	bool sc_table_changed;
	bool sc_table_dirty;
	अचिन्हित पूर्णांक sc_table_last_pipe_num;
	bool anr_thres_changed;
	/* ---- deprecated: replaced with pipe_dvs_6axis_config_changed ---- */
	bool dvs_6axis_config_changed;
	/* ------ pipe specअगरic DPC configuration ------ */
	/* Please note that this implementation is a temporary solution and
	 * should be replaced by CSS per pipe configuration when the support
	 * is पढ़ोy (HSD 1303967698) */
	bool pipe_dpc_config_changed[IA_CSS_PIPE_ID_NUM];
	/* ------ deprecated(bz675) : from ------ */
	bool shading_settings_changed;
	/* ------ deprecated(bz675) : to ------ */
	bool pipe_dvs_6axis_config_changed[IA_CSS_PIPE_ID_NUM];

	bool config_changed[IA_CSS_NUM_PARAMETER_IDS];

	अचिन्हित पूर्णांक sensor_binning;
	/* local buffers, used to re-order the 3a statistics in vmem-क्रमmat */
	काष्ठा sh_css_ddr_address_map pipe_ddr_ptrs[IA_CSS_PIPE_ID_NUM];
	काष्ठा sh_css_ddr_address_map_size pipe_ddr_ptrs_size[IA_CSS_PIPE_ID_NUM];
	काष्ठा sh_css_ddr_address_map ddr_ptrs;
	काष्ठा sh_css_ddr_address_map_size ddr_ptrs_size;
	काष्ठा ia_css_frame
		*output_frame; /** Output frame the config is to be applied to (optional) */
	u32 isp_parameters_id; /** Unique ID to track which config was actually applied to a particular frame */
पूर्ण;

व्योम
ia_css_params_store_ia_css_host_data(
    ia_css_ptr ddr_addr,
    काष्ठा ia_css_host_data *data);

पूर्णांक
ia_css_params_store_sctbl(
    स्थिर काष्ठा ia_css_pipeline_stage *stage,
    ia_css_ptr ddr_addr,
    स्थिर काष्ठा ia_css_shading_table *shading_table);

काष्ठा ia_css_host_data *
ia_css_params_alloc_convert_sctbl(
    स्थिर काष्ठा ia_css_pipeline_stage *stage,
    स्थिर काष्ठा ia_css_shading_table *shading_table);

काष्ठा ia_css_isp_config *
sh_css_pipe_isp_config_get(काष्ठा ia_css_pipe *pipe);

/* ipu address allocation/मुक्त क्रम gdc lut */
ia_css_ptr
sh_css_params_alloc_gdc_lut(व्योम);
व्योम
sh_css_params_मुक्त_gdc_lut(ia_css_ptr addr);

पूर्णांक
sh_css_params_map_and_store_शेष_gdc_lut(व्योम);

व्योम
sh_css_params_मुक्त_शेष_gdc_lut(व्योम);

ia_css_ptr
sh_css_params_get_शेष_gdc_lut(व्योम);

ia_css_ptr
sh_css_pipe_get_pp_gdc_lut(स्थिर काष्ठा ia_css_pipe *pipe);

#पूर्ण_अगर /* _SH_CSS_PARAMS_H_ */
