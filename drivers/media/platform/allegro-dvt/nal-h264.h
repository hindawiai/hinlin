<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Convert NAL units between raw byte sequence payloads (RBSP) and C काष्ठाs.
 */

#अगर_अघोषित __NAL_H264_H__
#घोषणा __NAL_H264_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

/*
 * काष्ठा nal_h264_hrd_parameters - HRD parameters
 *
 * C काष्ठा representation of the sequence parameter set NAL unit as defined by
 * Rec. ITU-T H.264 (04/2017) E.1.2 HRD parameters syntax.
 */
काष्ठा nal_h264_hrd_parameters अणु
	अचिन्हित पूर्णांक cpb_cnt_minus1;
	अचिन्हित पूर्णांक bit_rate_scale;
	अचिन्हित पूर्णांक cpb_size_scale;
	काष्ठा अणु
		पूर्णांक bit_rate_value_minus1[16];
		पूर्णांक cpb_size_value_minus1[16];
		अचिन्हित पूर्णांक cbr_flag[16];
	पूर्ण;
	अचिन्हित पूर्णांक initial_cpb_removal_delay_length_minus1;
	अचिन्हित पूर्णांक cpb_removal_delay_length_minus1;
	अचिन्हित पूर्णांक dpb_output_delay_length_minus1;
	अचिन्हित पूर्णांक समय_offset_length;
पूर्ण;

/*
 * काष्ठा nal_h264_vui_parameters - VUI parameters
 *
 * C काष्ठा representation of the VUI parameters as defined by Rec. ITU-T
 * H.264 (04/2017) E.1.1 VUI parameters syntax.
 */
काष्ठा nal_h264_vui_parameters अणु
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
			अचिन्हित पूर्णांक matrix_coefficients;
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक chroma_loc_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक chroma_sample_loc_type_top_field;
		अचिन्हित पूर्णांक chroma_sample_loc_type_bottom_field;
	पूर्ण;
	अचिन्हित पूर्णांक timing_info_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक num_units_in_tick;
		अचिन्हित पूर्णांक समय_scale;
		अचिन्हित पूर्णांक fixed_frame_rate_flag;
	पूर्ण;
	अचिन्हित पूर्णांक nal_hrd_parameters_present_flag;
	काष्ठा nal_h264_hrd_parameters nal_hrd_parameters;
	अचिन्हित पूर्णांक vcl_hrd_parameters_present_flag;
	काष्ठा nal_h264_hrd_parameters vcl_hrd_parameters;
	अचिन्हित पूर्णांक low_delay_hrd_flag;
	अचिन्हित पूर्णांक pic_काष्ठा_present_flag;
	अचिन्हित पूर्णांक bitstream_restriction_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक motion_vectors_over_pic_boundaries_flag;
		अचिन्हित पूर्णांक max_bytes_per_pic_denom;
		अचिन्हित पूर्णांक max_bits_per_mb_denom;
		अचिन्हित पूर्णांक log2_max_mv_length_horizontal;
		अचिन्हित पूर्णांक log21_max_mv_length_vertical;
		अचिन्हित पूर्णांक max_num_reorder_frames;
		अचिन्हित पूर्णांक max_dec_frame_buffering;
	पूर्ण;
पूर्ण;

/*
 * काष्ठा nal_h264_sps - Sequence parameter set
 *
 * C काष्ठा representation of the sequence parameter set NAL unit as defined by
 * Rec. ITU-T H.264 (04/2017) 7.3.2.1.1 Sequence parameter set data syntax.
 */
काष्ठा nal_h264_sps अणु
	अचिन्हित पूर्णांक profile_idc;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set0_flag;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set1_flag;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set2_flag;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set3_flag;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set4_flag;
	अचिन्हित पूर्णांक स्थिरraपूर्णांक_set5_flag;
	अचिन्हित पूर्णांक reserved_zero_2bits;
	अचिन्हित पूर्णांक level_idc;
	अचिन्हित पूर्णांक seq_parameter_set_id;
	काष्ठा अणु
		अचिन्हित पूर्णांक chroma_क्रमmat_idc;
		अचिन्हित पूर्णांक separate_colour_plane_flag;
		अचिन्हित पूर्णांक bit_depth_luma_minus8;
		अचिन्हित पूर्णांक bit_depth_chroma_minus8;
		अचिन्हित पूर्णांक qpprime_y_zero_transक्रमm_bypass_flag;
		अचिन्हित पूर्णांक seq_scaling_matrix_present_flag;
	पूर्ण;
	अचिन्हित पूर्णांक log2_max_frame_num_minus4;
	अचिन्हित पूर्णांक pic_order_cnt_type;
	जोड़ अणु
		अचिन्हित पूर्णांक log2_max_pic_order_cnt_lsb_minus4;
		काष्ठा अणु
			अचिन्हित पूर्णांक delta_pic_order_always_zero_flag;
			पूर्णांक offset_क्रम_non_ref_pic;
			पूर्णांक offset_क्रम_top_to_bottom_field;
			अचिन्हित पूर्णांक num_ref_frames_in_pic_order_cnt_cycle;
			पूर्णांक offset_क्रम_ref_frame[255];
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक max_num_ref_frames;
	अचिन्हित पूर्णांक gaps_in_frame_num_value_allowed_flag;
	अचिन्हित पूर्णांक pic_width_in_mbs_minus1;
	अचिन्हित पूर्णांक pic_height_in_map_units_minus1;
	अचिन्हित पूर्णांक frame_mbs_only_flag;
	अचिन्हित पूर्णांक mb_adaptive_frame_field_flag;
	अचिन्हित पूर्णांक direct_8x8_inference_flag;
	अचिन्हित पूर्णांक frame_cropping_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक crop_left;
		अचिन्हित पूर्णांक crop_right;
		अचिन्हित पूर्णांक crop_top;
		अचिन्हित पूर्णांक crop_bottom;
	पूर्ण;
	अचिन्हित पूर्णांक vui_parameters_present_flag;
	काष्ठा nal_h264_vui_parameters vui;
पूर्ण;

/*
 * काष्ठा nal_h264_pps - Picture parameter set
 *
 * C काष्ठा representation of the picture parameter set NAL unit as defined by
 * Rec. ITU-T H.264 (04/2017) 7.3.2.2 Picture parameter set RBSP syntax.
 */
काष्ठा nal_h264_pps अणु
	अचिन्हित पूर्णांक pic_parameter_set_id;
	अचिन्हित पूर्णांक seq_parameter_set_id;
	अचिन्हित पूर्णांक entropy_coding_mode_flag;
	अचिन्हित पूर्णांक bottom_field_pic_order_in_frame_present_flag;
	अचिन्हित पूर्णांक num_slice_groups_minus1;
	अचिन्हित पूर्णांक slice_group_map_type;
	जोड़ अणु
		अचिन्हित पूर्णांक run_length_minus1[8];
		काष्ठा अणु
			अचिन्हित पूर्णांक top_left[8];
			अचिन्हित पूर्णांक bottom_right[8];
		पूर्ण;
		काष्ठा अणु
			अचिन्हित पूर्णांक slice_group_change_direction_flag;
			अचिन्हित पूर्णांक slice_group_change_rate_minus1;
		पूर्ण;
		काष्ठा अणु
			अचिन्हित पूर्णांक pic_size_in_map_units_minus1;
			अचिन्हित पूर्णांक slice_group_id[8];
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक num_ref_idx_l0_शेष_active_minus1;
	अचिन्हित पूर्णांक num_ref_idx_l1_शेष_active_minus1;
	अचिन्हित पूर्णांक weighted_pred_flag;
	अचिन्हित पूर्णांक weighted_bipred_idc;
	पूर्णांक pic_init_qp_minus26;
	पूर्णांक pic_init_qs_minus26;
	पूर्णांक chroma_qp_index_offset;
	अचिन्हित पूर्णांक deblocking_filter_control_present_flag;
	अचिन्हित पूर्णांक स्थिरrained_पूर्णांकra_pred_flag;
	अचिन्हित पूर्णांक redundant_pic_cnt_present_flag;
	काष्ठा अणु
		अचिन्हित पूर्णांक transक्रमm_8x8_mode_flag;
		अचिन्हित पूर्णांक pic_scaling_matrix_present_flag;
		पूर्णांक second_chroma_qp_index_offset;
	पूर्ण;
पूर्ण;

पूर्णांक nal_h264_profile_from_v4l2(क्रमागत v4l2_mpeg_video_h264_profile profile);
पूर्णांक nal_h264_level_from_v4l2(क्रमागत v4l2_mpeg_video_h264_level level);

sमाप_प्रकार nal_h264_ग_लिखो_sps(स्थिर काष्ठा device *dev,
			   व्योम *dest, माप_प्रकार n, काष्ठा nal_h264_sps *sps);
sमाप_प्रकार nal_h264_पढ़ो_sps(स्थिर काष्ठा device *dev,
			  काष्ठा nal_h264_sps *sps, व्योम *src, माप_प्रकार n);
व्योम nal_h264_prपूर्णांक_sps(स्थिर काष्ठा device *dev, काष्ठा nal_h264_sps *sps);

sमाप_प्रकार nal_h264_ग_लिखो_pps(स्थिर काष्ठा device *dev,
			   व्योम *dest, माप_प्रकार n, काष्ठा nal_h264_pps *pps);
sमाप_प्रकार nal_h264_पढ़ो_pps(स्थिर काष्ठा device *dev,
			  काष्ठा nal_h264_pps *pps, व्योम *src, माप_प्रकार n);
व्योम nal_h264_prपूर्णांक_pps(स्थिर काष्ठा device *dev, काष्ठा nal_h264_pps *pps);

sमाप_प्रकार nal_h264_ग_लिखो_filler(स्थिर काष्ठा device *dev, व्योम *dest, माप_प्रकार n);
sमाप_प्रकार nal_h264_पढ़ो_filler(स्थिर काष्ठा device *dev, व्योम *src, माप_प्रकार n);

#पूर्ण_अगर /* __NAL_H264_H__ */
