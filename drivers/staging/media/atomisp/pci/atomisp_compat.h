<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Clovertrail PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2012 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित __ATOMISP_COMPAT_H__
#घोषणा __ATOMISP_COMPAT_H__

#समावेश "atomisp_compat_css20.h"

#समावेश "../../include/linux/atomisp.h"
#समावेश <media/videobuf-vदो_स्मृति.h>

काष्ठा atomisp_device;
काष्ठा atomisp_sub_device;
काष्ठा video_device;
क्रमागत atomisp_input_stream_id;

काष्ठा atomisp_metadata_buf अणु
	काष्ठा ia_css_metadata *metadata;
	व्योम *md_vptr;
	काष्ठा list_head list;
पूर्ण;

व्योम atomisp_css2_hw_store_32(hrt_address addr, uपूर्णांक32_t data);
व्योम atomisp_load_uपूर्णांक32(hrt_address addr, uपूर्णांक32_t *data);

पूर्णांक atomisp_css_init(काष्ठा atomisp_device *isp);

व्योम atomisp_css_uninit(काष्ठा atomisp_device *isp);

व्योम atomisp_css_suspend(काष्ठा atomisp_device *isp);

पूर्णांक atomisp_css_resume(काष्ठा atomisp_device *isp);

व्योम atomisp_css_init_काष्ठा(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_irq_translate(काष्ठा atomisp_device *isp,
			      अचिन्हित पूर्णांक *infos);

व्योम atomisp_css_rx_get_irq_info(क्रमागत mipi_port_id port,
				 अचिन्हित पूर्णांक *infos);

व्योम atomisp_css_rx_clear_irq_info(क्रमागत mipi_port_id port,
				   अचिन्हित पूर्णांक infos);

पूर्णांक atomisp_css_irq_enable(काष्ठा atomisp_device *isp,
			   क्रमागत ia_css_irq_info info, bool enable);

पूर्णांक atomisp_q_video_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				  काष्ठा videobuf_vदो_स्मृति_memory *vm_mem,
				  क्रमागत atomisp_input_stream_id stream_id,
				  क्रमागत ia_css_buffer_type css_buf_type,
				  क्रमागत ia_css_pipe_id css_pipe_id);

पूर्णांक atomisp_q_s3a_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_s3a_buf *s3a_buf,
				क्रमागत atomisp_input_stream_id stream_id,
				क्रमागत ia_css_pipe_id css_pipe_id);

पूर्णांक atomisp_q_metadata_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				     काष्ठा atomisp_metadata_buf *metadata_buf,
				     क्रमागत atomisp_input_stream_id stream_id,
				     क्रमागत ia_css_pipe_id css_pipe_id);

पूर्णांक atomisp_q_dis_buffer_to_css(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_dis_buf *dis_buf,
				क्रमागत atomisp_input_stream_id stream_id,
				क्रमागत ia_css_pipe_id css_pipe_id);

व्योम ia_css_mmu_invalidate_cache(व्योम);

व्योम ia_css_mmu_invalidate_cache(व्योम);

पूर्णांक atomisp_css_start(काष्ठा atomisp_sub_device *asd,
		      क्रमागत ia_css_pipe_id pipe_id, bool in_reset);

व्योम atomisp_css_update_isp_params(काष्ठा atomisp_sub_device *asd);
व्योम atomisp_css_update_isp_params_on_pipe(काष्ठा atomisp_sub_device *asd,
	काष्ठा ia_css_pipe *pipe);

पूर्णांक atomisp_css_queue_buffer(काष्ठा atomisp_sub_device *asd,
			     क्रमागत atomisp_input_stream_id stream_id,
			     क्रमागत ia_css_pipe_id pipe_id,
			     क्रमागत ia_css_buffer_type buf_type,
			     काष्ठा atomisp_css_buffer *isp_css_buffer);

पूर्णांक atomisp_css_dequeue_buffer(काष्ठा atomisp_sub_device *asd,
			       क्रमागत atomisp_input_stream_id stream_id,
			       क्रमागत ia_css_pipe_id pipe_id,
			       क्रमागत ia_css_buffer_type buf_type,
			       काष्ठा atomisp_css_buffer *isp_css_buffer);

पूर्णांक atomisp_css_allocate_stat_buffers(काष्ठा atomisp_sub_device *asd,
				      u16 stream_id,
				      काष्ठा atomisp_s3a_buf *s3a_buf,
				      काष्ठा atomisp_dis_buf *dis_buf,
				      काष्ठा atomisp_metadata_buf *md_buf);

व्योम atomisp_css_मुक्त_stat_buffers(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_css_मुक्त_3a_buffer(काष्ठा atomisp_s3a_buf *s3a_buf);

व्योम atomisp_css_मुक्त_dis_buffer(काष्ठा atomisp_dis_buf *dis_buf);

व्योम atomisp_css_मुक्त_metadata_buffer(काष्ठा atomisp_metadata_buf
				      *metadata_buf);

पूर्णांक atomisp_css_get_grid_info(काष्ठा atomisp_sub_device *asd,
			      क्रमागत ia_css_pipe_id pipe_id,
			      पूर्णांक source_pad);

पूर्णांक atomisp_alloc_3a_output_buf(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_alloc_dis_coef_buf(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_alloc_metadata_output_buf(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_मुक्त_metadata_output_buf(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_css_get_dis_statistics(काष्ठा atomisp_sub_device *asd,
				    काष्ठा atomisp_css_buffer *isp_css_buffer,
				    काष्ठा ia_css_isp_dvs_statistics_map *dvs_map);

पूर्णांक atomisp_css_dequeue_event(काष्ठा atomisp_css_event *current_event);

व्योम atomisp_css_temp_pipe_to_pipe_id(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_css_event *current_event);

पूर्णांक atomisp_css_isys_set_resolution(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    काष्ठा v4l2_mbus_framefmt *ffmt,
				    पूर्णांक isys_stream);

व्योम atomisp_css_isys_set_link(काष्ठा atomisp_sub_device *asd,
			       क्रमागत atomisp_input_stream_id stream_id,
			       पूर्णांक link,
			       पूर्णांक isys_stream);

व्योम atomisp_css_isys_set_valid(काष्ठा atomisp_sub_device *asd,
				क्रमागत atomisp_input_stream_id stream_id,
				bool valid,
				पूर्णांक isys_stream);

व्योम atomisp_css_isys_set_क्रमmat(काष्ठा atomisp_sub_device *asd,
				 क्रमागत atomisp_input_stream_id stream_id,
				 क्रमागत atomisp_input_क्रमmat क्रमmat,
				 पूर्णांक isys_stream);

पूर्णांक atomisp_css_set_शेष_isys_config(काष्ठा atomisp_sub_device *asd,
					क्रमागत atomisp_input_stream_id stream_id,
					काष्ठा v4l2_mbus_framefmt *ffmt);

पूर्णांक atomisp_css_isys_two_stream_cfg(काष्ठा atomisp_sub_device *asd,
				    क्रमागत atomisp_input_stream_id stream_id,
				    क्रमागत atomisp_input_क्रमmat input_क्रमmat);

व्योम atomisp_css_isys_two_stream_cfg_update_stream1(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

व्योम atomisp_css_isys_two_stream_cfg_update_stream2(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

पूर्णांक atomisp_css_input_set_resolution(काष्ठा atomisp_sub_device *asd,
				     क्रमागत atomisp_input_stream_id stream_id,
				     काष्ठा v4l2_mbus_framefmt *ffmt);

व्योम atomisp_css_input_set_binning_factor(काष्ठा atomisp_sub_device *asd,
	क्रमागत atomisp_input_stream_id stream_id,
	अचिन्हित पूर्णांक bin_factor);

व्योम atomisp_css_input_set_bayer_order(काष्ठा atomisp_sub_device *asd,
				       क्रमागत atomisp_input_stream_id stream_id,
				       क्रमागत ia_css_bayer_order bayer_order);

व्योम atomisp_css_input_set_क्रमmat(काष्ठा atomisp_sub_device *asd,
				  क्रमागत atomisp_input_stream_id stream_id,
				  क्रमागत atomisp_input_क्रमmat क्रमmat);

पूर्णांक atomisp_css_input_set_effective_resolution(
    काष्ठा atomisp_sub_device *asd,
    क्रमागत atomisp_input_stream_id stream_id,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height);

व्योम atomisp_css_video_set_dis_envelope(काष्ठा atomisp_sub_device *asd,
					अचिन्हित पूर्णांक dvs_w, अचिन्हित पूर्णांक dvs_h);

व्योम atomisp_css_input_set_two_pixels_per_घड़ी(
    काष्ठा atomisp_sub_device *asd,
    bool two_ppc);

व्योम atomisp_css_enable_raw_binning(काष्ठा atomisp_sub_device *asd,
				    bool enable);

व्योम atomisp_css_enable_dz(काष्ठा atomisp_sub_device *asd, bool enable);

व्योम atomisp_css_capture_set_mode(काष्ठा atomisp_sub_device *asd,
				  क्रमागत ia_css_capture_mode mode);

व्योम atomisp_css_input_set_mode(काष्ठा atomisp_sub_device *asd,
				क्रमागत ia_css_input_mode mode);

व्योम atomisp_css_capture_enable_online(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित लघु stream_index, bool enable);

व्योम atomisp_css_preview_enable_online(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित लघु stream_index, bool enable);

व्योम atomisp_css_video_enable_online(काष्ठा atomisp_sub_device *asd,
				     bool enable);

व्योम atomisp_css_enable_continuous(काष्ठा atomisp_sub_device *asd,
				   bool enable);

व्योम atomisp_css_enable_cvf(काष्ठा atomisp_sub_device *asd,
			    bool enable);

पूर्णांक atomisp_css_input_configure_port(काष्ठा atomisp_sub_device *asd,
				     क्रमागत mipi_port_id port,
				     अचिन्हित पूर्णांक num_lanes,
				     अचिन्हित पूर्णांक समयout,
				     अचिन्हित पूर्णांक mipi_freq,
				     क्रमागत atomisp_input_क्रमmat metadata_क्रमmat,
				     अचिन्हित पूर्णांक metadata_width,
				     अचिन्हित पूर्णांक metadata_height);

व्योम atomisp_create_pipes_stream(काष्ठा atomisp_sub_device *asd);
व्योम atomisp_destroy_pipes_stream_क्रमce(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_css_stop(काष्ठा atomisp_sub_device *asd,
		      क्रमागत ia_css_pipe_id pipe_id, bool in_reset);

व्योम atomisp_css_continuous_set_num_raw_frames(
     काष्ठा atomisp_sub_device *asd,
     पूर्णांक num_frames);

पूर्णांक atomisp_css_copy_configure_output(काष्ठा atomisp_sub_device *asd,
				      अचिन्हित पूर्णांक stream_index,
				      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				      अचिन्हित पूर्णांक padded_width,
				      क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_yuvpp_configure_output(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित पूर्णांक stream_index,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       अचिन्हित पूर्णांक padded_width,
				       क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_yuvpp_configure_viewfinder(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक min_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_yuvpp_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_yuvpp_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_preview_configure_output(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_capture_configure_output(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_video_configure_output(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       अचिन्हित पूर्णांक min_width,
				       क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_get_css_frame_info(काष्ठा atomisp_sub_device *asd,
			       u16 source_pad,
			       काष्ठा ia_css_frame_info *frame_info);

पूर्णांक atomisp_css_video_configure_viewfinder(काष्ठा atomisp_sub_device *asd,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	अचिन्हित पूर्णांक min_width,
	क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_capture_configure_viewfinder(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक min_width,
    क्रमागत ia_css_frame_क्रमmat क्रमmat);

पूर्णांक atomisp_css_video_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_capture_get_viewfinder_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_copy_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक stream_index,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_capture_get_output_raw_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_preview_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_capture_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_video_get_output_frame_info(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा ia_css_frame_info *info);

पूर्णांक atomisp_css_preview_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

पूर्णांक atomisp_css_capture_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

पूर्णांक atomisp_css_video_configure_pp_input(
    काष्ठा atomisp_sub_device *asd,
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

पूर्णांक atomisp_css_offline_capture_configure(काष्ठा atomisp_sub_device *asd,
	पूर्णांक num_captures, अचिन्हित पूर्णांक skip, पूर्णांक offset);
पूर्णांक atomisp_css_exp_id_capture(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id);
पूर्णांक atomisp_css_exp_id_unlock(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id);

पूर्णांक atomisp_css_capture_enable_xnr(काष्ठा atomisp_sub_device *asd,
				   bool enable);

व्योम atomisp_css_set_ctc_table(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_ctc_table *ctc_table);

व्योम atomisp_css_video_set_dis_vector(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_dis_vector *vector);

व्योम atomisp_css_set_dvs2_coefs(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_dvs2_coefficients *coefs);

पूर्णांक atomisp_css_set_dis_coefs(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_dis_coefficients *coefs);

व्योम atomisp_css_set_zoom_factor(काष्ठा atomisp_sub_device *asd,
				 अचिन्हित पूर्णांक zoom);

पूर्णांक atomisp_css_get_wb_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_wb_config *config);

पूर्णांक atomisp_css_get_ob_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ob_config *config);

पूर्णांक atomisp_css_get_dp_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_dp_config *config);

पूर्णांक atomisp_css_get_de_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_de_config *config);

पूर्णांक atomisp_css_get_nr_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_nr_config *config);

पूर्णांक atomisp_css_get_ee_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ee_config *config);

पूर्णांक atomisp_css_get_tnr_config(काष्ठा atomisp_sub_device *asd,
			       काष्ठा atomisp_tnr_config *config);

पूर्णांक atomisp_css_get_ctc_table(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_ctc_table *config);

पूर्णांक atomisp_css_get_gamma_table(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_gamma_table *config);

पूर्णांक atomisp_css_get_gc_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_gc_config *config);

पूर्णांक atomisp_css_get_3a_config(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_3a_config *config);

पूर्णांक atomisp_css_get_क्रमmats_config(काष्ठा atomisp_sub_device *asd,
				   काष्ठा atomisp_क्रमmats_config *क्रमmats_config);

व्योम atomisp_css_set_क्रमmats_config(काष्ठा atomisp_sub_device *asd,
				    काष्ठा ia_css_क्रमmats_config *क्रमmats_config);

पूर्णांक atomisp_css_get_zoom_factor(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक *zoom);

काष्ठा ia_css_shading_table *atomisp_css_shading_table_alloc(
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

व्योम atomisp_css_set_shading_table(काष्ठा atomisp_sub_device *asd,
				   काष्ठा ia_css_shading_table *table);

व्योम atomisp_css_shading_table_मुक्त(काष्ठा ia_css_shading_table *table);

काष्ठा ia_css_morph_table *atomisp_css_morph_table_allocate(
    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);

व्योम atomisp_css_set_morph_table(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_morph_table *table);

व्योम atomisp_css_get_morph_table(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_morph_table *table);

व्योम atomisp_css_morph_table_मुक्त(काष्ठा ia_css_morph_table *table);

व्योम atomisp_css_set_cont_prev_start_समय(काष्ठा atomisp_device *isp,
	अचिन्हित पूर्णांक overlap);

पूर्णांक atomisp_css_get_dis_stat(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_dis_statistics *stats);

पूर्णांक atomisp_css_update_stream(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_create_acc_pipe(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_start_acc_pipe(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_stop_acc_pipe(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_css_destroy_acc_pipe(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_load_acc_extension(काष्ठा atomisp_sub_device *asd,
				   काष्ठा ia_css_fw_info *fw,
				   क्रमागत ia_css_pipe_id pipe_id,
				   अचिन्हित पूर्णांक type);

व्योम atomisp_css_unload_acc_extension(काष्ठा atomisp_sub_device *asd,
				      काष्ठा ia_css_fw_info *fw,
				      क्रमागत ia_css_pipe_id pipe_id);

पूर्णांक atomisp_css_रुको_acc_finish(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_css_acc_करोne(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_css_load_acc_binary(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_fw_info *fw,
				अचिन्हित पूर्णांक index);

व्योम atomisp_css_unload_acc_binary(काष्ठा atomisp_sub_device *asd);

काष्ठा atomisp_acc_fw;
पूर्णांक atomisp_css_set_acc_parameters(काष्ठा atomisp_acc_fw *acc_fw);

पूर्णांक atomisp_css_isr_thपढ़ो(काष्ठा atomisp_device *isp,
			   bool *frame_करोne_found,
			   bool *css_pipe_करोne);

bool atomisp_css_valid_sof(काष्ठा atomisp_device *isp);

व्योम atomisp_en_dz_capt_pipe(काष्ठा atomisp_sub_device *asd, bool enable);

#पूर्ण_अगर
