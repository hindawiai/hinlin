<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/platक्रमm/s5p-mfc/s5p_mfc_opr.h
 *
 * Header file क्रम Samsung MFC (Multi Function Codec - FIMV) driver
 * Contains declarations of hw related functions.
 *
 * Kamil Debski, Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_OPR_H_
#घोषणा S5P_MFC_OPR_H_

#समावेश "s5p_mfc_common.h"

काष्ठा s5p_mfc_regs अणु

	/* codec common रेजिस्टरs */
	व्योम __iomem *risc_on;
	व्योम __iomem *risc2host_पूर्णांक;
	व्योम __iomem *host2risc_पूर्णांक;
	व्योम __iomem *risc_base_address;
	व्योम __iomem *mfc_reset;
	व्योम __iomem *host2risc_command;
	व्योम __iomem *risc2host_command;
	व्योम __iomem *mfc_bus_reset_ctrl;
	व्योम __iomem *firmware_version;
	व्योम __iomem *instance_id;
	व्योम __iomem *codec_type;
	व्योम __iomem *context_mem_addr;
	व्योम __iomem *context_mem_size;
	व्योम __iomem *pixel_क्रमmat;
	व्योम __iomem *metadata_enable;
	व्योम __iomem *mfc_version;
	व्योम __iomem *dbg_info_enable;
	व्योम __iomem *dbg_buffer_addr;
	व्योम __iomem *dbg_buffer_size;
	व्योम __iomem *hed_control;
	व्योम __iomem *mfc_समयout_value;
	व्योम __iomem *hed_shared_mem_addr;
	व्योम __iomem *dis_shared_mem_addr;/* only v7 */
	व्योम __iomem *ret_instance_id;
	व्योम __iomem *error_code;
	व्योम __iomem *dbg_buffer_output_size;
	व्योम __iomem *metadata_status;
	व्योम __iomem *metadata_addr_mb_info;
	व्योम __iomem *metadata_size_mb_info;
	व्योम __iomem *dbg_info_stage_counter;

	/* decoder रेजिस्टरs */
	व्योम __iomem *d_crc_ctrl;
	व्योम __iomem *d_dec_options;
	व्योम __iomem *d_display_delay;
	व्योम __iomem *d_set_frame_width;
	व्योम __iomem *d_set_frame_height;
	व्योम __iomem *d_sei_enable;
	व्योम __iomem *d_min_num_dpb;
	व्योम __iomem *d_min_first_plane_dpb_size;
	व्योम __iomem *d_min_second_plane_dpb_size;
	व्योम __iomem *d_min_third_plane_dpb_size;/* only v8 */
	व्योम __iomem *d_min_num_mv;
	व्योम __iomem *d_mvc_num_views;
	व्योम __iomem *d_min_num_dis;/* only v7 */
	व्योम __iomem *d_min_first_dis_size;/* only v7 */
	व्योम __iomem *d_min_second_dis_size;/* only v7 */
	व्योम __iomem *d_min_third_dis_size;/* only v7 */
	व्योम __iomem *d_post_filter_luma_dpb0;/*  v7 and v8 */
	व्योम __iomem *d_post_filter_luma_dpb1;/* v7 and v8 */
	व्योम __iomem *d_post_filter_luma_dpb2;/* only v7 */
	व्योम __iomem *d_post_filter_chroma_dpb0;/* v7 and v8 */
	व्योम __iomem *d_post_filter_chroma_dpb1;/* v7 and v8 */
	व्योम __iomem *d_post_filter_chroma_dpb2;/* only v7 */
	व्योम __iomem *d_num_dpb;
	व्योम __iomem *d_num_mv;
	व्योम __iomem *d_init_buffer_options;
	व्योम __iomem *d_first_plane_dpb_stride_size;/* only v8 */
	व्योम __iomem *d_second_plane_dpb_stride_size;/* only v8 */
	व्योम __iomem *d_third_plane_dpb_stride_size;/* only v8 */
	व्योम __iomem *d_first_plane_dpb_size;
	व्योम __iomem *d_second_plane_dpb_size;
	व्योम __iomem *d_third_plane_dpb_size;/* only v8 */
	व्योम __iomem *d_mv_buffer_size;
	व्योम __iomem *d_first_plane_dpb;
	व्योम __iomem *d_second_plane_dpb;
	व्योम __iomem *d_third_plane_dpb;
	व्योम __iomem *d_mv_buffer;
	व्योम __iomem *d_scratch_buffer_addr;
	व्योम __iomem *d_scratch_buffer_size;
	व्योम __iomem *d_metadata_buffer_addr;
	व्योम __iomem *d_metadata_buffer_size;
	व्योम __iomem *d_nal_start_options;/* v7 and v8 */
	व्योम __iomem *d_cpb_buffer_addr;
	व्योम __iomem *d_cpb_buffer_size;
	व्योम __iomem *d_available_dpb_flag_upper;
	व्योम __iomem *d_available_dpb_flag_lower;
	व्योम __iomem *d_cpb_buffer_offset;
	व्योम __iomem *d_slice_अगर_enable;
	व्योम __iomem *d_picture_tag;
	व्योम __iomem *d_stream_data_size;
	व्योम __iomem *d_dynamic_dpb_flag_upper;/* v7 and v8 */
	व्योम __iomem *d_dynamic_dpb_flag_lower;/* v7 and v8 */
	व्योम __iomem *d_display_frame_width;
	व्योम __iomem *d_display_frame_height;
	व्योम __iomem *d_display_status;
	व्योम __iomem *d_display_first_plane_addr;
	व्योम __iomem *d_display_second_plane_addr;
	व्योम __iomem *d_display_third_plane_addr;/* only v8 */
	व्योम __iomem *d_display_frame_type;
	व्योम __iomem *d_display_crop_info1;
	व्योम __iomem *d_display_crop_info2;
	व्योम __iomem *d_display_picture_profile;
	व्योम __iomem *d_display_luma_crc;/* v7 and v8 */
	व्योम __iomem *d_display_chroma0_crc;/* v7 and v8 */
	व्योम __iomem *d_display_chroma1_crc;/* only v8 */
	व्योम __iomem *d_display_luma_crc_top;/* only v6 */
	व्योम __iomem *d_display_chroma_crc_top;/* only v6 */
	व्योम __iomem *d_display_luma_crc_bot;/* only v6 */
	व्योम __iomem *d_display_chroma_crc_bot;/* only v6 */
	व्योम __iomem *d_display_aspect_ratio;
	व्योम __iomem *d_display_extended_ar;
	व्योम __iomem *d_decoded_frame_width;
	व्योम __iomem *d_decoded_frame_height;
	व्योम __iomem *d_decoded_status;
	व्योम __iomem *d_decoded_first_plane_addr;
	व्योम __iomem *d_decoded_second_plane_addr;
	व्योम __iomem *d_decoded_third_plane_addr;/* only v8 */
	व्योम __iomem *d_decoded_frame_type;
	व्योम __iomem *d_decoded_crop_info1;
	व्योम __iomem *d_decoded_crop_info2;
	व्योम __iomem *d_decoded_picture_profile;
	व्योम __iomem *d_decoded_nal_size;
	व्योम __iomem *d_decoded_luma_crc;
	व्योम __iomem *d_decoded_chroma0_crc;
	व्योम __iomem *d_decoded_chroma1_crc;/* only v8 */
	व्योम __iomem *d_ret_picture_tag_top;
	व्योम __iomem *d_ret_picture_tag_bot;
	व्योम __iomem *d_ret_picture_समय_प्रकारop;
	व्योम __iomem *d_ret_picture_समय_bot;
	व्योम __iomem *d_chroma_क्रमmat;
	व्योम __iomem *d_vc1_info;/* v7 and v8 */
	व्योम __iomem *d_mpeg4_info;
	व्योम __iomem *d_h264_info;
	व्योम __iomem *d_metadata_addr_concealed_mb;
	व्योम __iomem *d_metadata_size_concealed_mb;
	व्योम __iomem *d_metadata_addr_vc1_param;
	व्योम __iomem *d_metadata_size_vc1_param;
	व्योम __iomem *d_metadata_addr_sei_nal;
	व्योम __iomem *d_metadata_size_sei_nal;
	व्योम __iomem *d_metadata_addr_vui;
	व्योम __iomem *d_metadata_size_vui;
	व्योम __iomem *d_metadata_addr_mvcvui;/* v7 and v8 */
	व्योम __iomem *d_metadata_size_mvcvui;/* v7 and v8 */
	व्योम __iomem *d_mvc_view_id;
	व्योम __iomem *d_frame_pack_sei_avail;
	व्योम __iomem *d_frame_pack_arrgment_id;
	व्योम __iomem *d_frame_pack_sei_info;
	व्योम __iomem *d_frame_pack_grid_pos;
	व्योम __iomem *d_display_recovery_sei_info;/* v7 and v8 */
	व्योम __iomem *d_decoded_recovery_sei_info;/* v7 and v8 */
	व्योम __iomem *d_display_first_addr;/* only v7 */
	व्योम __iomem *d_display_second_addr;/* only v7 */
	व्योम __iomem *d_display_third_addr;/* only v7 */
	व्योम __iomem *d_decoded_first_addr;/* only v7 */
	व्योम __iomem *d_decoded_second_addr;/* only v7 */
	व्योम __iomem *d_decoded_third_addr;/* only v7 */
	व्योम __iomem *d_used_dpb_flag_upper;/* v7 and v8 */
	व्योम __iomem *d_used_dpb_flag_lower;/* v7 and v8 */
	व्योम __iomem *d_min_scratch_buffer_size; /* v10 */
	व्योम __iomem *d_अटल_buffer_addr; /* v10 */
	व्योम __iomem *d_अटल_buffer_size; /* v10 */

	/* encoder रेजिस्टरs */
	व्योम __iomem *e_frame_width;
	व्योम __iomem *e_frame_height;
	व्योम __iomem *e_cropped_frame_width;
	व्योम __iomem *e_cropped_frame_height;
	व्योम __iomem *e_frame_crop_offset;
	व्योम __iomem *e_enc_options;
	व्योम __iomem *e_picture_profile;
	व्योम __iomem *e_vbv_buffer_size;
	व्योम __iomem *e_vbv_init_delay;
	व्योम __iomem *e_fixed_picture_qp;
	व्योम __iomem *e_rc_config;
	व्योम __iomem *e_rc_qp_bound;
	व्योम __iomem *e_rc_qp_bound_pb;/* v7 and v8 */
	व्योम __iomem *e_rc_mode;
	व्योम __iomem *e_mb_rc_config;
	व्योम __iomem *e_padding_ctrl;
	व्योम __iomem *e_air_threshold;
	व्योम __iomem *e_mv_hor_range;
	व्योम __iomem *e_mv_ver_range;
	व्योम __iomem *e_num_dpb;
	व्योम __iomem *e_luma_dpb;
	व्योम __iomem *e_chroma_dpb;
	व्योम __iomem *e_me_buffer;
	व्योम __iomem *e_scratch_buffer_addr;
	व्योम __iomem *e_scratch_buffer_size;
	व्योम __iomem *e_पंचांगv_buffer0;
	व्योम __iomem *e_पंचांगv_buffer1;
	व्योम __iomem *e_ir_buffer_addr;/* v7 and v8 */
	व्योम __iomem *e_source_first_plane_addr;
	व्योम __iomem *e_source_second_plane_addr;
	व्योम __iomem *e_source_third_plane_addr;/* v7 and v8 */
	व्योम __iomem *e_source_first_plane_stride;/* v7 and v8 */
	व्योम __iomem *e_source_second_plane_stride;/* v7 and v8 */
	व्योम __iomem *e_source_third_plane_stride;/* v7 and v8 */
	व्योम __iomem *e_stream_buffer_addr;
	व्योम __iomem *e_stream_buffer_size;
	व्योम __iomem *e_roi_buffer_addr;
	व्योम __iomem *e_param_change;
	व्योम __iomem *e_ir_size;
	व्योम __iomem *e_gop_config;
	व्योम __iomem *e_mslice_mode;
	व्योम __iomem *e_mslice_size_mb;
	व्योम __iomem *e_mslice_size_bits;
	व्योम __iomem *e_frame_insertion;
	व्योम __iomem *e_rc_frame_rate;
	व्योम __iomem *e_rc_bit_rate;
	व्योम __iomem *e_rc_roi_ctrl;
	व्योम __iomem *e_picture_tag;
	व्योम __iomem *e_bit_count_enable;
	व्योम __iomem *e_max_bit_count;
	व्योम __iomem *e_min_bit_count;
	व्योम __iomem *e_metadata_buffer_addr;
	व्योम __iomem *e_metadata_buffer_size;
	व्योम __iomem *e_encoded_source_first_plane_addr;
	व्योम __iomem *e_encoded_source_second_plane_addr;
	व्योम __iomem *e_encoded_source_third_plane_addr;/* v7 and v8 */
	व्योम __iomem *e_stream_size;
	व्योम __iomem *e_slice_type;
	व्योम __iomem *e_picture_count;
	व्योम __iomem *e_ret_picture_tag;
	व्योम __iomem *e_stream_buffer_ग_लिखो_poपूर्णांकer; /*  only v6 */
	व्योम __iomem *e_recon_luma_dpb_addr;
	व्योम __iomem *e_recon_chroma_dpb_addr;
	व्योम __iomem *e_metadata_addr_enc_slice;
	व्योम __iomem *e_metadata_size_enc_slice;
	व्योम __iomem *e_mpeg4_options;
	व्योम __iomem *e_mpeg4_hec_period;
	व्योम __iomem *e_aspect_ratio;
	व्योम __iomem *e_extended_sar;
	व्योम __iomem *e_h264_options;
	व्योम __iomem *e_h264_options_2;/* v7 and v8 */
	व्योम __iomem *e_h264_lf_alpha_offset;
	व्योम __iomem *e_h264_lf_beta_offset;
	व्योम __iomem *e_h264_i_period;
	व्योम __iomem *e_h264_fmo_slice_grp_map_type;
	व्योम __iomem *e_h264_fmo_num_slice_grp_minus1;
	व्योम __iomem *e_h264_fmo_slice_grp_change_dir;
	व्योम __iomem *e_h264_fmo_slice_grp_change_rate_minus1;
	व्योम __iomem *e_h264_fmo_run_length_minus1_0;
	व्योम __iomem *e_h264_aso_slice_order_0;
	व्योम __iomem *e_h264_chroma_qp_offset;
	व्योम __iomem *e_h264_num_t_layer;
	व्योम __iomem *e_h264_hierarchical_qp_layer0;
	व्योम __iomem *e_h264_frame_packing_sei_info;
	व्योम __iomem *e_h264_nal_control;/* v7 and v8 */
	व्योम __iomem *e_mvc_frame_qp_view1;
	व्योम __iomem *e_mvc_rc_bit_rate_view1;
	व्योम __iomem *e_mvc_rc_qbound_view1;
	व्योम __iomem *e_mvc_rc_mode_view1;
	व्योम __iomem *e_mvc_पूर्णांकer_view_prediction_on;
	व्योम __iomem *e_vp8_options;/* v7 and v8 */
	व्योम __iomem *e_vp8_filter_options;/* v7 and v8 */
	व्योम __iomem *e_vp8_golden_frame_option;/* v7 and v8 */
	व्योम __iomem *e_vp8_num_t_layer;/* v7 and v8 */
	व्योम __iomem *e_vp8_hierarchical_qp_layer0;/* v7 and v8 */
	व्योम __iomem *e_vp8_hierarchical_qp_layer1;/* v7 and v8 */
	व्योम __iomem *e_vp8_hierarchical_qp_layer2;/* v7 and v8 */
	व्योम __iomem *e_min_scratch_buffer_size; /* v10 */
	व्योम __iomem *e_num_t_layer; /* v10 */
	व्योम __iomem *e_hier_qp_layer0; /* v10 */
	व्योम __iomem *e_hier_bit_rate_layer0; /* v10 */
	व्योम __iomem *e_hevc_options; /* v10 */
	व्योम __iomem *e_hevc_refresh_period; /* v10 */
	व्योम __iomem *e_hevc_lf_beta_offset_भाग2; /* v10 */
	व्योम __iomem *e_hevc_lf_tc_offset_भाग2; /* v10 */
	व्योम __iomem *e_hevc_nal_control; /* v10 */
पूर्ण;

काष्ठा s5p_mfc_hw_ops अणु
	पूर्णांक (*alloc_dec_temp_buffers)(काष्ठा s5p_mfc_ctx *ctx);
	व्योम (*release_dec_desc_buffer)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*alloc_codec_buffers)(काष्ठा s5p_mfc_ctx *ctx);
	व्योम (*release_codec_buffers)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*alloc_instance_buffer)(काष्ठा s5p_mfc_ctx *ctx);
	व्योम (*release_instance_buffer)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*alloc_dev_context_buffer)(काष्ठा s5p_mfc_dev *dev);
	व्योम (*release_dev_context_buffer)(काष्ठा s5p_mfc_dev *dev);
	व्योम (*dec_calc_dpb_size)(काष्ठा s5p_mfc_ctx *ctx);
	व्योम (*enc_calc_src_size)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*set_enc_stream_buffer)(काष्ठा s5p_mfc_ctx *ctx,
			अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size);
	व्योम (*set_enc_frame_buffer)(काष्ठा s5p_mfc_ctx *ctx,
			अचिन्हित दीर्घ y_addr, अचिन्हित दीर्घ c_addr);
	व्योम (*get_enc_frame_buffer)(काष्ठा s5p_mfc_ctx *ctx,
			अचिन्हित दीर्घ *y_addr, अचिन्हित दीर्घ *c_addr);
	व्योम (*try_run)(काष्ठा s5p_mfc_dev *dev);
	व्योम (*clear_पूर्णांक_flags)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dspl_y_adr)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dec_y_adr)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dspl_status)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dec_status)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dec_frame_type)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_disp_frame_type)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*get_consumed_stream)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_पूर्णांक_reason)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_पूर्णांक_err)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*err_dec)(अचिन्हित पूर्णांक err);
	पूर्णांक (*get_img_width)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_img_height)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_dpb_count)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_mv_count)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_inst_no)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_enc_strm_size)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_enc_slice_type)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_enc_dpb_count)(काष्ठा s5p_mfc_dev *dev);
	अचिन्हित पूर्णांक (*get_pic_type_top)(काष्ठा s5p_mfc_ctx *ctx);
	अचिन्हित पूर्णांक (*get_pic_type_bot)(काष्ठा s5p_mfc_ctx *ctx);
	अचिन्हित पूर्णांक (*get_crop_info_h)(काष्ठा s5p_mfc_ctx *ctx);
	अचिन्हित पूर्णांक (*get_crop_info_v)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*get_min_scratch_buf_size)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*get_e_min_scratch_buf_size)(काष्ठा s5p_mfc_dev *dev);
पूर्ण;

व्योम s5p_mfc_init_hw_ops(काष्ठा s5p_mfc_dev *dev);
व्योम s5p_mfc_init_regs(काष्ठा s5p_mfc_dev *dev);
पूर्णांक s5p_mfc_alloc_priv_buf(काष्ठा s5p_mfc_dev *dev, अचिन्हित पूर्णांक mem_ctx,
			   काष्ठा s5p_mfc_priv_buf *b);
व्योम s5p_mfc_release_priv_buf(काष्ठा s5p_mfc_dev *dev,
			      काष्ठा s5p_mfc_priv_buf *b);
पूर्णांक s5p_mfc_alloc_generic_buf(काष्ठा s5p_mfc_dev *dev, अचिन्हित पूर्णांक mem_ctx,
			   काष्ठा s5p_mfc_priv_buf *b);
व्योम s5p_mfc_release_generic_buf(काष्ठा s5p_mfc_dev *dev,
			      काष्ठा s5p_mfc_priv_buf *b);


#पूर्ण_अगर /* S5P_MFC_OPR_H_ */
