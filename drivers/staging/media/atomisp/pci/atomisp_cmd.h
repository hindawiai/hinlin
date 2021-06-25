<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
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

#अगर_अघोषित	__ATOMISP_CMD_H__
#घोषणा	__ATOMISP_CMD_H__

#समावेश "../../include/linux/atomisp.h"
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-subdev.h>

#समावेश "atomisp_internal.h"

#समावेश "ia_css_types.h"
#समावेश "ia_css.h"

काष्ठा atomisp_device;
काष्ठा ia_css_frame;

#घोषणा MSI_ENABLE_BIT		16
#घोषणा INTR_DISABLE_BIT	10
#घोषणा BUS_MASTER_ENABLE	2
#घोषणा MEMORY_SPACE_ENABLE	1
#घोषणा INTR_IER		24
#घोषणा INTR_IIR		16

/* ISP2401 */
#घोषणा RUNMODE_MASK (ATOMISP_RUN_MODE_VIDEO | ATOMISP_RUN_MODE_STILL_CAPTURE \
			| ATOMISP_RUN_MODE_PREVIEW)

/* FIXME: check अगर can go */
बाह्य पूर्णांक atomisp_punit_hpll_freq;

/*
 * Helper function
 */
व्योम dump_sp_dmem(काष्ठा atomisp_device *isp, अचिन्हित पूर्णांक addr,
		  अचिन्हित पूर्णांक size);
काष्ठा camera_mipi_info *atomisp_to_sensor_mipi_info(काष्ठा v4l2_subdev *sd);
काष्ठा atomisp_video_pipe *atomisp_to_video_pipe(काष्ठा video_device *dev);
काष्ठा atomisp_acc_pipe *atomisp_to_acc_pipe(काष्ठा video_device *dev);
पूर्णांक atomisp_reset(काष्ठा atomisp_device *isp);
व्योम atomisp_flush_bufs_and_wakeup(काष्ठा atomisp_sub_device *asd);
व्योम atomisp_clear_css_buffer_counters(काष्ठा atomisp_sub_device *asd);
/* ISP2400 */
bool atomisp_buffers_queued(काष्ठा atomisp_sub_device *asd);
/* ISP2401 */
bool atomisp_buffers_queued_pipe(काष्ठा atomisp_video_pipe *pipe);

/*
 * Interrupt functions
 */
व्योम atomisp_msi_irq_init(काष्ठा atomisp_device *isp);
व्योम atomisp_msi_irq_uninit(काष्ठा atomisp_device *isp);
व्योम atomisp_wdt_work(काष्ठा work_काष्ठा *work);
व्योम atomisp_wdt(काष्ठा समयr_list *t);
व्योम atomisp_setup_flash(काष्ठा atomisp_sub_device *asd);
irqवापस_t atomisp_isr(पूर्णांक irq, व्योम *dev);
irqवापस_t atomisp_isr_thपढ़ो(पूर्णांक irq, व्योम *isp_ptr);
स्थिर काष्ठा atomisp_क्रमmat_bridge *get_atomisp_क्रमmat_bridge_from_mbus(
    u32 mbus_code);
bool atomisp_is_mbuscode_raw(uपूर्णांक32_t code);
पूर्णांक atomisp_get_frame_pgnr(काष्ठा atomisp_device *isp,
			   स्थिर काष्ठा ia_css_frame *frame, u32 *p_pgnr);
व्योम atomisp_delayed_init_work(काष्ठा work_काष्ठा *work);

/*
 * Get पूर्णांकernal fmt according to V4L2 fmt
 */

bool atomisp_is_viewfinder_support(काष्ठा atomisp_device *isp);

/*
 * ISP features control function
 */

/*
 * Function to set sensor runmode by user when
 * ATOMISP_IOC_S_SENSOR_RUNMODE ioctl was called
 */
पूर्णांक atomisp_set_sensor_runmode(काष्ठा atomisp_sub_device *asd,
			       काष्ठा atomisp_s_runmode *runmode);
/*
 * Function to enable/disable lens geometry distortion correction (GDC) and
 * chromatic aberration correction (CAC)
 */
पूर्णांक atomisp_gdc_cac(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    __s32 *value);

/*
 * Function to enable/disable low light mode (including ANR)
 */
पूर्णांक atomisp_low_light(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		      __s32 *value);

/*
 * Function to enable/disable extra noise reduction (XNR) in low light
 * condition
 */
पूर्णांक atomisp_xnr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag, पूर्णांक *arg);

पूर्णांक atomisp_क्रमmats(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    काष्ठा atomisp_क्रमmats_config *config);

/*
 * Function to configure noise reduction
 */
पूर्णांक atomisp_nr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
	       काष्ठा atomisp_nr_config *config);

/*
 * Function to configure temporal noise reduction (TNR)
 */
पूर्णांक atomisp_tnr(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		काष्ठा atomisp_tnr_config *config);

/*
 * Function to configure black level compensation
 */
पूर्णांक atomisp_black_level(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			काष्ठा atomisp_ob_config *config);

/*
 * Function to configure edge enhancement
 */
पूर्णांक atomisp_ee(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
	       काष्ठा atomisp_ee_config *config);

/*
 * Function to update Gamma table क्रम gamma, brightness and contrast config
 */
पूर्णांक atomisp_gamma(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		  काष्ठा atomisp_gamma_table *config);
/*
 * Function to update Ctc table क्रम Chroma Enhancement
 */
पूर्णांक atomisp_ctc(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		काष्ठा atomisp_ctc_table *config);

/*
 * Function to update gamma correction parameters
 */
पूर्णांक atomisp_gamma_correction(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			     काष्ठा atomisp_gc_config *config);

/*
 * Function to update Gdc table क्रम gdc
 */
पूर्णांक atomisp_gdc_cac_table(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			  काष्ठा atomisp_morph_table *config);

/*
 * Function to update table क्रम macc
 */
पूर्णांक atomisp_macc_table(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		       काष्ठा atomisp_macc_config *config);
/*
 * Function to get DIS statistics.
 */
पूर्णांक atomisp_get_dis_stat(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_dis_statistics *stats);

/*
 * Function to get DVS2 BQ resolution settings
 */
पूर्णांक atomisp_get_dvs2_bq_resolutions(काष्ठा atomisp_sub_device *asd,
				    काष्ठा atomisp_dvs2_bq_resolutions *bq_res);

/*
 * Function to set the DIS coefficients.
 */
पूर्णांक atomisp_set_dis_coefs(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_dis_coefficients *coefs);

/*
 * Function to set the DIS motion vector.
 */
पूर्णांक atomisp_set_dis_vector(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_dis_vector *vector);

/*
 * Function to set/get 3A stat from isp
 */
पूर्णांक atomisp_3a_stat(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		    काष्ठा atomisp_3a_statistics *config);

/*
 * Function to get metadata from isp
 */
पूर्णांक atomisp_get_metadata(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 काष्ठा atomisp_metadata *config);

पूर्णांक atomisp_get_metadata_by_type(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
				 काष्ठा atomisp_metadata_with_type *config);

पूर्णांक atomisp_set_parameters(काष्ठा video_device *vdev,
			   काष्ठा atomisp_parameters *arg);
/*
 * Function to set/get isp parameters to isp
 */
पूर्णांक atomisp_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		  काष्ठा atomisp_parm *config);

/*
 * Function to configure color effect of the image
 */
पूर्णांक atomisp_color_effect(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *effect);

/*
 * Function to configure bad pixel correction
 */
पूर्णांक atomisp_bad_pixel(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
		      __s32 *value);

/*
 * Function to configure bad pixel correction params
 */
पूर्णांक atomisp_bad_pixel_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			    काष्ठा atomisp_dp_config *config);

/*
 * Function to enable/disable video image stablization
 */
पूर्णांक atomisp_video_stable(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *value);

/*
 * Function to configure fixed pattern noise
 */
पूर्णांक atomisp_fixed_pattern(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			  __s32 *value);

/*
 * Function to configure fixed pattern noise table
 */
पूर्णांक atomisp_fixed_pattern_table(काष्ठा atomisp_sub_device *asd,
				काष्ठा v4l2_framebuffer *config);

/*
 * Function to configure false color correction
 */
पूर्णांक atomisp_false_color(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			__s32 *value);

/*
 * Function to configure false color correction params
 */
पूर्णांक atomisp_false_color_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			      काष्ठा atomisp_de_config *config);

/*
 * Function to configure white balance params
 */
पूर्णांक atomisp_white_balance_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
				काष्ठा atomisp_wb_config *config);

पूर्णांक atomisp_3a_config_param(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			    काष्ठा atomisp_3a_config *config);

/*
 * Function to setup digital zoom
 */
पूर्णांक atomisp_digital_zoom(काष्ठा atomisp_sub_device *asd, पूर्णांक flag,
			 __s32 *value);

/*
 * Function  set camera_prefiles.xml current sensor pixel array size
 */
पूर्णांक atomisp_set_array_res(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_resolution  *config);

/*
 * Function to calculate real zoom region क्रम every pipe
 */
पूर्णांक atomisp_calculate_real_zoom_region(काष्ठा atomisp_sub_device *asd,
				       काष्ठा ia_css_dz_config   *dz_config,
				       क्रमागत ia_css_pipe_id css_pipe_id);

पूर्णांक atomisp_cp_general_isp_parameters(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_parameters *arg,
				      काष्ठा atomisp_css_params *css_param,
				      bool from_user);

पूर्णांक atomisp_cp_lsc_table(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_shading_table *source_st,
			 काष्ठा atomisp_css_params *css_param,
			 bool from_user);

पूर्णांक atomisp_css_cp_dvs2_coefs(काष्ठा atomisp_sub_device *asd,
			      काष्ठा ia_css_dvs2_coefficients *coefs,
			      काष्ठा atomisp_css_params *css_param,
			      bool from_user);

पूर्णांक atomisp_cp_morph_table(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_morph_table *source_morph_table,
			   काष्ठा atomisp_css_params *css_param,
			   bool from_user);

पूर्णांक atomisp_cp_dvs_6axis_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा atomisp_dvs_6axis_config *user_6axis_config,
				काष्ठा atomisp_css_params *css_param,
				bool from_user);

पूर्णांक atomisp_makeup_css_parameters(काष्ठा atomisp_sub_device *asd,
				  काष्ठा atomisp_parameters *arg,
				  काष्ठा atomisp_css_params *css_param);

पूर्णांक atomisp_compare_grid(काष्ठा atomisp_sub_device *asd,
			 काष्ठा atomisp_grid_info *atomgrid);

पूर्णांक atomisp_get_sensor_mode_data(काष्ठा atomisp_sub_device *asd,
				 काष्ठा atomisp_sensor_mode_data *config);

पूर्णांक atomisp_get_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f);

/* This function looks up the बंदst available resolution. */
पूर्णांक atomisp_try_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_pix_क्रमmat *f,
		    bool *res_overflow);

पूर्णांक atomisp_set_fmt(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f);
पूर्णांक atomisp_set_fmt_file(काष्ठा video_device *vdev, काष्ठा v4l2_क्रमmat *f);

पूर्णांक atomisp_set_shading_table(काष्ठा atomisp_sub_device *asd,
			      काष्ठा atomisp_shading_table *shading_table);

पूर्णांक atomisp_offline_capture_configure(काष्ठा atomisp_sub_device *asd,
				      काष्ठा atomisp_cont_capture_conf *cvf_config);

पूर्णांक atomisp_ospm_dphy_करोwn(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_ospm_dphy_up(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_exअगर_makernote(काष्ठा atomisp_sub_device *asd,
			   काष्ठा atomisp_makernote_info *config);

व्योम atomisp_मुक्त_पूर्णांकernal_buffers(काष्ठा atomisp_sub_device *asd);

पूर्णांक atomisp_s_ae_winकरोw(काष्ठा atomisp_sub_device *asd,
			काष्ठा atomisp_ae_winकरोw *arg);

पूर्णांक  atomisp_flash_enable(काष्ठा atomisp_sub_device *asd,
			  पूर्णांक num_frames);

पूर्णांक atomisp_freq_scaling(काष्ठा atomisp_device *vdev,
			 क्रमागत atomisp_dfs_mode mode,
			 bool क्रमce);

व्योम atomisp_buf_करोne(काष्ठा atomisp_sub_device *asd, पूर्णांक error,
		      क्रमागत ia_css_buffer_type buf_type,
		      क्रमागत ia_css_pipe_id css_pipe_id,
		      bool q_buffers, क्रमागत atomisp_input_stream_id stream_id);

व्योम atomisp_css_flush(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_source_pad_to_stream_id(काष्ठा atomisp_sub_device *asd,
				    uपूर्णांक16_t source_pad);

/*
 * Events. Only one event has to be exported क्रम now.
 */
व्योम atomisp_eof_event(काष्ठा atomisp_sub_device *asd, uपूर्णांक8_t exp_id);

क्रमागत mipi_port_id __get_mipi_port(काष्ठा atomisp_device *isp,
				  क्रमागत atomisp_camera_port port);

bool atomisp_is_vf_pipe(काष्ठा atomisp_video_pipe *pipe);

व्योम atomisp_apply_css_parameters(
    काष्ठा atomisp_sub_device *asd,
    काष्ठा atomisp_css_params *css_param);
व्योम atomisp_मुक्त_css_parameters(काष्ठा atomisp_css_params *css_param);

व्योम atomisp_handle_parameter_and_buffer(काष्ठा atomisp_video_pipe *pipe);

व्योम atomisp_flush_params_queue(काष्ठा atomisp_video_pipe *asd);
/*
 * Function to करो Raw Buffer related operation, after enable Lock Unlock Raw Buffer
 */
पूर्णांक atomisp_exp_id_unlock(काष्ठा atomisp_sub_device *asd, पूर्णांक *exp_id);
पूर्णांक atomisp_exp_id_capture(काष्ठा atomisp_sub_device *asd, पूर्णांक *exp_id);

/*
 * Function to update Raw Buffer biपंचांगap
 */
पूर्णांक atomisp_set_raw_buffer_biपंचांगap(काष्ठा atomisp_sub_device *asd, पूर्णांक exp_id);
व्योम atomisp_init_raw_buffer_biपंचांगap(काष्ठा atomisp_sub_device *asd);

/*
 * Function to enable/disable zoom क्रम capture pipe
 */
पूर्णांक atomisp_enable_dz_capt_pipe(काष्ठा atomisp_sub_device *asd,
				अचिन्हित पूर्णांक *enable);

/*
 * Function to get metadata type bu pipe id
 */
क्रमागत atomisp_metadata_type
atomisp_get_metadata_type(काष्ठा atomisp_sub_device *asd,
			  क्रमागत ia_css_pipe_id pipe_id);

/*
 * Function क्रम HAL to inject a fake event to wake up poll thपढ़ो
 */
पूर्णांक atomisp_inject_a_fake_event(काष्ठा atomisp_sub_device *asd, पूर्णांक *event);

/*
 * Function क्रम HAL to query how many invalid frames at the beginning of ISP
 * pipeline output
 */
पूर्णांक atomisp_get_invalid_frame_num(काष्ठा video_device *vdev,
				  पूर्णांक *invalid_frame_num);

पूर्णांक atomisp_mrfld_घातer_up(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_mrfld_घातer_करोwn(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_runसमय_suspend(काष्ठा device *dev);
पूर्णांक atomisp_runसमय_resume(काष्ठा device *dev);
#पूर्ण_अगर /* __ATOMISP_CMD_H__ */
