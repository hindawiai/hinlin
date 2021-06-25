<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Convert NAL units between raw byte sequence payloads (RBSP) and C काष्ठाs.
 */

#अगर_अघोषित __NAL_HEVC_H__
#घोषणा __NAL_HEVC_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>

काष्ठा nal_hevc_profile_tier_level अणु
	अचिन्हित पूर्णांक general_profile_space;
	अचिन्हित पूर्णांक general_tier_flag;
	अचिन्हित पूर्णांक general_profile_idc;
	अचिन्हित पूर्णांक general_profile_compatibility_flag[32];
	अचिन्हित पूर्णांक general_progressive_source_flag;
	अचिन्हित पूर्णांक general_पूर्णांकerlaced_source_flag;
	अचिन्हित पूर्णांक general_non_packed_स्थिरraपूर्णांक_flag;
	अचिन्हित पूर्णांक general_frame_only_स्थिरraपूर्णांक_flag;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक general_max_12bit_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_max_10bit_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_max_8bit_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_max_422chroma_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_max_420chroma_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_max_monochrome_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_पूर्णांकra_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_one_picture_only_स्थिरraपूर्णांक_flag;
			अचिन्हित पूर्णांक general_lower_bit_rate_स्थिरraपूर्णांक_flag;
			जोड़ अणु
				काष्ठा अणु
					अचिन्हित पूर्णांक general_max_14bit_स्थिरraपूर्णांक_flag;
					अचिन्हित पूर्णांक general_reserved_zero_33bits;
				पूर्ण;
				अचिन्हित पूर्णांक general_reserved_zero_34bits;
			पूर्ण;
		पूर्ण;
		काष्ठा अणु
			अचिन्हित पूर्णांक general_reserved_zero_7bits;
			/* अचिन्हित पूर्णांक general_one_picture_only_स्थिरraपूर्णांक_flag; */
			अचिन्हित पूर्णांक general_reserved_zero_35bits;
		पूर्ण;
		अचिन्हित पूर्णांक general_reserved_zero_43bits;
	पूर्ण;
	जोड़ अणु
		अचिन्हित पूर्णांक general_inbld_flag;
		अचिन्हित पूर्णांक general_reserved_zero_bit;
	पूर्ण;
	अचिन्हित पूर्णांक general_level_idc;
पूर्ण;

/*
 * काष्ठा nal_hevc_vps - Video parameter set
 *
 * C काष्ठा representation of the video parameter set NAL unit as defined by
 * Rec. ITU-T H.265 (02/2018) 7.3.2.1 Video parameter set RBSP syntax
 */
काष्ठा nal_hevc_vps अणु
	अचिन्हित पूर्णांक video_parameter_set_id;
	अचिन्हित पूर्णांक base_layer_पूर्णांकernal_flag;
	अचिन्हित पूर्णांक base_layer_available_flag;
	अचिन्हित पूर्णांक max_layers_minus1;
	अचिन्हित पूर्णांक max_sub_layers_minus1;
	अचिन्हित पूर्णांक temporal_id_nesting_flag;
	काष्ठा nal_hevc_profile_tier_level profile_tier_level;
	अचिन्हित पूर्णांक sub_layer_ordering_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक max_dec_pic_buffering_minus1[7];
		अचिन्हित पूर्णांक max_num_reorder_pics[7];
		अचिन्हित पूर्णांक max_latency_increase_plus1[7];
	पूर्ण;
	अचिन्हित पूर्णांक max_layer_id;
	अचिन्हित पूर्णांक num_layer_sets_minus1;
	अचिन्हित पूर्णांक layer_id_included_flag[1024][64];
	अचिन्हित पूर्णांक timing_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक num_units_in_tick;
		अचिन्हित पूर्णांक समय_scale;
		अचिन्हित पूर्णांक poc_proportional_to_timing_flag;
		अचिन्हित पूर्णांक num_ticks_poc_dअगरf_one_minus1;
		अचिन्हित पूर्णांक num_hrd_parameters;
		काष्ठा अणु
			अचिन्हित पूर्णांक hrd_layer_set_idx[0];
			अचिन्हित पूर्णांक cprms_present_flag[0];
		पूर्ण;
		/* hrd_parameters( cprms_present_flag[ i ], max_sub_layers_minus1 ) */
	पूर्ण;
	अचिन्हित पूर्णांक extension_flag;
	अचिन्हित पूर्णांक extension_data_flag;
पूर्ण;

काष्ठा nal_hevc_sub_layer_hrd_parameters अणु
	अचिन्हित पूर्णांक bit_rate_value_minus1[1];
	अचिन्हित पूर्णांक cpb_size_value_minus1[1];
	अचिन्हित पूर्णांक cbr_flag[1];
पूर्ण;

काष्ठा nal_hevc_hrd_parameters अणु
	अचिन्हित पूर्णांक nal_hrd_parameters_present_flag;
	अचिन्हित पूर्णांक vcl_hrd_parameters_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक sub_pic_hrd_params_present_flag;
		काष्ठा अणु
			अचिन्हित पूर्णांक tick_भागisor_minus2;
			अचिन्हित पूर्णांक du_cpb_removal_delay_increment_length_minus1;
			अचिन्हित पूर्णांक sub_pic_cpb_params_in_pic_timing_sei_flag;
			अचिन्हित पूर्णांक dpb_output_delay_du_length_minus1;
		पूर्ण;
		अचिन्हित पूर्णांक bit_rate_scale;
		अचिन्हित पूर्णांक cpb_size_scale;
		अचिन्हित पूर्णांक cpb_size_du_scale;
		अचिन्हित पूर्णांक initial_cpb_removal_delay_length_minus1;
		अचिन्हित पूर्णांक au_cpb_removal_delay_length_minus1;
		अचिन्हित पूर्णांक dpb_output_delay_length_minus1;
	पूर्ण;
	काष्ठा अणु
		अचिन्हित पूर्णांक fixed_pic_rate_general_flag[1];
		अचिन्हित पूर्णांक fixed_pic_rate_within_cvs_flag[1];
		अचिन्हित पूर्णांक elemental_duration_in_tc_minus1[1];
		अचिन्हित पूर्णांक low_delay_hrd_flag[1];
		अचिन्हित पूर्णांक cpb_cnt_minus1[1];
		काष्ठा nal_hevc_sub_layer_hrd_parameters nal_hrd[1];
		काष्ठा nal_hevc_sub_layer_hrd_parameters vcl_hrd[1];
	पूर्ण;
पूर्ण;

/*
 * काष्ठा nal_hevc_vui_parameters - VUI parameters
 *
 * C काष्ठा representation of the VUI parameters as defined by Rec. ITU-T
 * H.265 (02/2018) E.2.1 VUI parameters syntax.
 */
काष्ठा nal_hevc_vui_parameters अणु
	अचिन्हित पूर्णांक aspect_ratio_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक aspect_ratio_idc;
		अचिन्हित पूर्णांक sar_width;
		अचिन्हित पूर्णांक sar_height;
	पूर्ण;
	अचिन्हित पूर्णांक overscan_info_present_flag;
	अचिन्हित पूर्णांक overscan_appropriate_flag;
	अचिन्हित पूर्णांक video_संकेत_type_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक video_क्रमmat;
		अचिन्हित पूर्णांक video_full_range_flag;
		अचिन्हित पूर्णांक colour_description_present_flag;
		काष्ठा अणु
			अचिन्हित पूर्णांक colour_primaries;
			अचिन्हित पूर्णांक transfer_अक्षरacteristics;
			अचिन्हित पूर्णांक matrix_coeffs;
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक chroma_loc_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक chroma_sample_loc_type_top_field;
		अचिन्हित पूर्णांक chroma_sample_loc_type_bottom_field;
	पूर्ण;
	अचिन्हित पूर्णांक neutral_chroma_indication_flag;
	अचिन्हित पूर्णांक field_seq_flag;
	अचिन्हित पूर्णांक frame_field_info_present_flag;
	अचिन्हित पूर्णांक शेष_display_winकरोw_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक def_disp_win_left_offset;
		अचिन्हित पूर्णांक def_disp_win_right_offset;
		अचिन्हित पूर्णांक def_disp_win_top_offset;
		अचिन्हित पूर्णांक def_disp_win_bottom_offset;
	पूर्ण;
	अचिन्हित पूर्णांक vui_timing_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक vui_num_units_in_tick;
		अचिन्हित पूर्णांक vui_समय_scale;
		अचिन्हित पूर्णांक vui_poc_proportional_to_timing_flag;
		अचिन्हित पूर्णांक vui_num_ticks_poc_dअगरf_one_minus1;
		अचिन्हित पूर्णांक vui_hrd_parameters_present_flag;
		काष्ठा nal_hevc_hrd_parameters nal_hrd_parameters;
	पूर्ण;
	अचिन्हित पूर्णांक bitstream_restriction_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक tiles_fixed_काष्ठाure_flag;
		अचिन्हित पूर्णांक motion_vectors_over_pic_boundaries_flag;
		अचिन्हित पूर्णांक restricted_ref_pic_lists_flag;
		अचिन्हित पूर्णांक min_spatial_segmentation_idc;
		अचिन्हित पूर्णांक max_bytes_per_pic_denom;
		अचिन्हित पूर्णांक max_bits_per_min_cu_denom;
		अचिन्हित पूर्णांक log2_max_mv_length_horizontal;
		अचिन्हित पूर्णांक log2_max_mv_length_vertical;
	पूर्ण;
पूर्ण;

/*
 * काष्ठा nal_hevc_sps - Sequence parameter set
 *
 * C काष्ठा representation of the video parameter set NAL unit as defined by
 * Rec. ITU-T H.265 (02/2018) 7.3.2.2 Sequence parameter set RBSP syntax
 */
काष्ठा nal_hevc_sps अणु
	अचिन्हित पूर्णांक video_parameter_set_id;
	अचिन्हित पूर्णांक max_sub_layers_minus1;
	अचिन्हित पूर्णांक temporal_id_nesting_flag;
	काष्ठा nal_hevc_profile_tier_level profile_tier_level;
	अचिन्हित पूर्णांक seq_parameter_set_id;
	अचिन्हित पूर्णांक chroma_क्रमmat_idc;
	अचिन्हित पूर्णांक separate_colour_plane_flag;
	अचिन्हित पूर्णांक pic_width_in_luma_samples;
	अचिन्हित पूर्णांक pic_height_in_luma_samples;
	अचिन्हित पूर्णांक conक्रमmance_winकरोw_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक conf_win_left_offset;
		अचिन्हित पूर्णांक conf_win_right_offset;
		अचिन्हित पूर्णांक conf_win_top_offset;
		अचिन्हित पूर्णांक conf_win_bottom_offset;
	पूर्ण;

	अचिन्हित पूर्णांक bit_depth_luma_minus8;
	अचिन्हित पूर्णांक bit_depth_chroma_minus8;
	अचिन्हित पूर्णांक log2_max_pic_order_cnt_lsb_minus4;
	अचिन्हित पूर्णांक sub_layer_ordering_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक max_dec_pic_buffering_minus1[7];
		अचिन्हित पूर्णांक max_num_reorder_pics[7];
		अचिन्हित पूर्णांक max_latency_increase_plus1[7];
	पूर्ण;
	अचिन्हित पूर्णांक log2_min_luma_coding_block_size_minus3;
	अचिन्हित पूर्णांक log2_dअगरf_max_min_luma_coding_block_size;
	अचिन्हित पूर्णांक log2_min_luma_transक्रमm_block_size_minus2;
	अचिन्हित पूर्णांक log2_dअगरf_max_min_luma_transक्रमm_block_size;
	अचिन्हित पूर्णांक max_transक्रमm_hierarchy_depth_पूर्णांकer;
	अचिन्हित पूर्णांक max_transक्रमm_hierarchy_depth_पूर्णांकra;

	अचिन्हित पूर्णांक scaling_list_enabled_flag;
	अचिन्हित पूर्णांक scaling_list_data_present_flag;
	अचिन्हित पूर्णांक amp_enabled_flag;
	अचिन्हित पूर्णांक sample_adaptive_offset_enabled_flag;
	अचिन्हित पूर्णांक pcm_enabled_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक pcm_sample_bit_depth_luma_minus1;
		अचिन्हित पूर्णांक pcm_sample_bit_depth_chroma_minus1;
		अचिन्हित पूर्णांक log2_min_pcm_luma_coding_block_size_minus3;
		अचिन्हित पूर्णांक log2_dअगरf_max_min_pcm_luma_coding_block_size;
		अचिन्हित पूर्णांक pcm_loop_filter_disabled_flag;
	पूर्ण;

	अचिन्हित पूर्णांक num_लघु_term_ref_pic_sets;
	अचिन्हित पूर्णांक दीर्घ_term_ref_pics_present_flag;
	अचिन्हित पूर्णांक sps_temporal_mvp_enabled_flag;
	अचिन्हित पूर्णांक strong_पूर्णांकra_smoothing_enabled_flag;
	अचिन्हित पूर्णांक vui_parameters_present_flag;
	काष्ठा nal_hevc_vui_parameters vui;
	अचिन्हित पूर्णांक extension_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक sps_range_extension_flag;
		अचिन्हित पूर्णांक sps_multilayer_extension_flag;
		अचिन्हित पूर्णांक sps_3d_extension_flag;
		अचिन्हित पूर्णांक sps_scc_extension_flag;
		अचिन्हित पूर्णांक sps_extension_4bits;
	पूर्ण;
पूर्ण;

काष्ठा nal_hevc_pps अणु
	अचिन्हित पूर्णांक pps_pic_parameter_set_id;
	अचिन्हित पूर्णांक pps_seq_parameter_set_id;
	अचिन्हित पूर्णांक dependent_slice_segments_enabled_flag;
	अचिन्हित पूर्णांक output_flag_present_flag;
	अचिन्हित पूर्णांक num_extra_slice_header_bits;
	अचिन्हित पूर्णांक sign_data_hiding_enabled_flag;
	अचिन्हित पूर्णांक cabac_init_present_flag;
	अचिन्हित पूर्णांक num_ref_idx_l0_शेष_active_minus1;
	अचिन्हित पूर्णांक num_ref_idx_l1_शेष_active_minus1;
	पूर्णांक init_qp_minus26;
	अचिन्हित पूर्णांक स्थिरrained_पूर्णांकra_pred_flag;
	अचिन्हित पूर्णांक transक्रमm_skip_enabled_flag;
	अचिन्हित पूर्णांक cu_qp_delta_enabled_flag;
	अचिन्हित पूर्णांक dअगरf_cu_qp_delta_depth;
	पूर्णांक pps_cb_qp_offset;
	पूर्णांक pps_cr_qp_offset;
	अचिन्हित पूर्णांक pps_slice_chroma_qp_offsets_present_flag;
	अचिन्हित पूर्णांक weighted_pred_flag;
	अचिन्हित पूर्णांक weighted_bipred_flag;
	अचिन्हित पूर्णांक transquant_bypass_enabled_flag;
	अचिन्हित पूर्णांक tiles_enabled_flag;
	अचिन्हित पूर्णांक entropy_coding_sync_enabled_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक num_tile_columns_minus1;
		अचिन्हित पूर्णांक num_tile_rows_minus1;
		अचिन्हित पूर्णांक unअगरorm_spacing_flag;
		काष्ठा अणु
			अचिन्हित पूर्णांक column_width_minus1[1];
			अचिन्हित पूर्णांक row_height_minus1[1];
		पूर्ण;
		अचिन्हित पूर्णांक loop_filter_across_tiles_enabled_flag;
	पूर्ण;
	अचिन्हित पूर्णांक pps_loop_filter_across_slices_enabled_flag;
	अचिन्हित पूर्णांक deblocking_filter_control_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक deblocking_filter_override_enabled_flag;
		अचिन्हित पूर्णांक pps_deblocking_filter_disabled_flag;
		काष्ठा अणु
			पूर्णांक pps_beta_offset_भाग2;
			पूर्णांक pps_tc_offset_भाग2;
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक pps_scaling_list_data_present_flag;
	अचिन्हित पूर्णांक lists_modअगरication_present_flag;
	अचिन्हित पूर्णांक log2_parallel_merge_level_minus2;
	अचिन्हित पूर्णांक slice_segment_header_extension_present_flag;
	अचिन्हित पूर्णांक pps_extension_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक pps_range_extension_flag;
		अचिन्हित पूर्णांक pps_multilayer_extension_flag;
		अचिन्हित पूर्णांक pps_3d_extension_flag;
		अचिन्हित पूर्णांक pps_scc_extension_flag;
		अचिन्हित पूर्णांक pps_extension_4bits;
	पूर्ण;
पूर्ण;

पूर्णांक nal_hevc_profile_from_v4l2(क्रमागत v4l2_mpeg_video_hevc_profile profile);
पूर्णांक nal_hevc_tier_from_v4l2(क्रमागत v4l2_mpeg_video_hevc_tier tier);
पूर्णांक nal_hevc_level_from_v4l2(क्रमागत v4l2_mpeg_video_hevc_level level);

पूर्णांक nal_range_from_v4l2(क्रमागत v4l2_quantization quantization);
पूर्णांक nal_color_primaries_from_v4l2(क्रमागत v4l2_colorspace colorspace);
पूर्णांक nal_transfer_अक्षरacteristics_from_v4l2(क्रमागत v4l2_colorspace colorspace,
					   क्रमागत v4l2_xfer_func xfer_func);
पूर्णांक nal_matrix_coeffs_from_v4l2(क्रमागत v4l2_colorspace colorspace,
				क्रमागत v4l2_ycbcr_encoding ycbcr_encoding);

sमाप_प्रकार nal_hevc_ग_लिखो_vps(स्थिर काष्ठा device *dev,
			   व्योम *dest, माप_प्रकार n, काष्ठा nal_hevc_vps *vps);
sमाप_प्रकार nal_hevc_पढ़ो_vps(स्थिर काष्ठा device *dev,
			  काष्ठा nal_hevc_vps *vps, व्योम *src, माप_प्रकार n);

sमाप_प्रकार nal_hevc_ग_लिखो_sps(स्थिर काष्ठा device *dev,
			   व्योम *dest, माप_प्रकार n, काष्ठा nal_hevc_sps *sps);
sमाप_प्रकार nal_hevc_पढ़ो_sps(स्थिर काष्ठा device *dev,
			  काष्ठा nal_hevc_sps *sps, व्योम *src, माप_प्रकार n);

sमाप_प्रकार nal_hevc_ग_लिखो_pps(स्थिर काष्ठा device *dev,
			   व्योम *dest, माप_प्रकार n, काष्ठा nal_hevc_pps *pps);
sमाप_प्रकार nal_hevc_पढ़ो_pps(स्थिर काष्ठा device *dev,
			  काष्ठा nal_hevc_pps *pps, व्योम *src, माप_प्रकार n);

sमाप_प्रकार nal_hevc_ग_लिखो_filler(स्थिर काष्ठा device *dev, व्योम *dest, माप_प्रकार n);
sमाप_प्रकार nal_hevc_पढ़ो_filler(स्थिर काष्ठा device *dev, व्योम *src, माप_प्रकार n);

#पूर्ण_अगर /* __NAL_HEVC_H__ */
