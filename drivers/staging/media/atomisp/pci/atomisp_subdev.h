<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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
#अगर_अघोषित __ATOMISP_SUBDEV_H__
#घोषणा __ATOMISP_SUBDEV_H__

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf-core.h>

#समावेश "atomisp_common.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_v4l2.h"

#समावेश "ia_css.h"

/* EXP_ID's ranger is 1 ~ 250 */
#घोषणा ATOMISP_MAX_EXP_ID     (250)
क्रमागत atomisp_subdev_input_entity अणु
	ATOMISP_SUBDEV_INPUT_NONE,
	ATOMISP_SUBDEV_INPUT_MEMORY,
	ATOMISP_SUBDEV_INPUT_CSI2,
	/*
	 * The following क्रमागत क्रम CSI2 port must go together in one row.
	 * Otherwise it अवरोधs the code logic.
	 */
	ATOMISP_SUBDEV_INPUT_CSI2_PORT1,
	ATOMISP_SUBDEV_INPUT_CSI2_PORT2,
	ATOMISP_SUBDEV_INPUT_CSI2_PORT3,
पूर्ण;

#घोषणा ATOMISP_SUBDEV_PAD_SINK			0
/* capture output क्रम still frames */
#घोषणा ATOMISP_SUBDEV_PAD_SOURCE_CAPTURE	1
/* viewfinder output क्रम करोwnscaled capture output */
#घोषणा ATOMISP_SUBDEV_PAD_SOURCE_VF		2
/* preview output क्रम display */
#घोषणा ATOMISP_SUBDEV_PAD_SOURCE_PREVIEW	3
/* मुख्य output क्रम video pipeline */
#घोषणा ATOMISP_SUBDEV_PAD_SOURCE_VIDEO	4
#घोषणा ATOMISP_SUBDEV_PADS_NUM			5

काष्ठा atomisp_in_fmt_conv अणु
	u32     code;
	u8 bpp; /* bits per pixel */
	u8 depth; /* uncompressed */
	क्रमागत atomisp_input_क्रमmat atomisp_in_fmt;
	क्रमागत ia_css_bayer_order bayer_order;
पूर्ण;

काष्ठा atomisp_sub_device;

काष्ठा atomisp_video_pipe अणु
	काष्ठा video_device vdev;
	क्रमागत v4l2_buf_type type;
	काष्ठा media_pad pad;
	काष्ठा videobuf_queue capq;
	काष्ठा videobuf_queue outq;
	काष्ठा list_head activeq;
	काष्ठा list_head activeq_out;
	/*
	 * the buffers रुकोing क्रम per-frame parameters, this is only valid
	 * in per-frame setting mode.
	 */
	काष्ठा list_head buffers_रुकोing_क्रम_param;
	/* the link list to store per_frame parameters */
	काष्ठा list_head per_frame_params;

	अचिन्हित पूर्णांक buffers_in_css;

	/* irq_lock is used to protect video buffer state change operations and
	 * also to make activeq, activeq_out, capq and outq list
	 * operations atomic. */
	spinlock_t irq_lock;
	अचिन्हित पूर्णांक users;

	काष्ठा atomisp_device *isp;
	काष्ठा v4l2_pix_क्रमmat pix;
	u32 sh_fmt;

	काष्ठा atomisp_sub_device *asd;

	/*
	 * This frame_config_id is got from CSS when dequueues buffers from CSS,
	 * it is used to indicate which parameter it has applied.
	 */
	अचिन्हित पूर्णांक frame_config_id[VIDEO_MAX_FRAME];
	/*
	 * This config id is set when camera HAL enqueues buffer, it has a
	 * non-zero value to indicate which parameter it needs to applu
	 */
	अचिन्हित पूर्णांक frame_request_config_id[VIDEO_MAX_FRAME];
	काष्ठा atomisp_css_params_with_list *frame_params[VIDEO_MAX_FRAME];

	/*
	* move wdt from asd काष्ठा to create wdt क्रम each pipe
	*/
	/* ISP2401 */
	काष्ठा समयr_list wdt;
	अचिन्हित पूर्णांक wdt_duration;	/* in jअगरfies */
	अचिन्हित दीर्घ wdt_expires;
	atomic_t wdt_count;
पूर्ण;

काष्ठा atomisp_acc_pipe अणु
	काष्ठा video_device vdev;
	अचिन्हित पूर्णांक users;
	bool running;
	काष्ठा atomisp_sub_device *asd;
	काष्ठा atomisp_device *isp;
पूर्ण;

काष्ठा atomisp_pad_क्रमmat अणु
	काष्ठा v4l2_mbus_framefmt fmt;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_rect compose;
पूर्ण;

/* Internal states क्रम flash process */
क्रमागत atomisp_flash_state अणु
	ATOMISP_FLASH_IDLE,
	ATOMISP_FLASH_REQUESTED,
	ATOMISP_FLASH_ONGOING,
	ATOMISP_FLASH_DONE
पूर्ण;

/*
 * This काष्ठाure is used to cache the CSS parameters, it aligns to
 * काष्ठा ia_css_isp_config but without un-supported and deprecated parts.
 */
काष्ठा atomisp_css_params अणु
	काष्ठा ia_css_wb_config   wb_config;
	काष्ठा ia_css_cc_config   cc_config;
	काष्ठा ia_css_tnr_config  tnr_config;
	काष्ठा ia_css_ecd_config  ecd_config;
	काष्ठा ia_css_ynr_config  ynr_config;
	काष्ठा ia_css_fc_config   fc_config;
	काष्ठा ia_css_क्रमmats_config क्रमmats_config;
	काष्ठा ia_css_cnr_config  cnr_config;
	काष्ठा ia_css_macc_config macc_config;
	काष्ठा ia_css_ctc_config  ctc_config;
	काष्ठा ia_css_aa_config   aa_config;
	काष्ठा ia_css_aa_config   baa_config;
	काष्ठा ia_css_ce_config   ce_config;
	काष्ठा ia_css_ob_config   ob_config;
	काष्ठा ia_css_dp_config   dp_config;
	काष्ठा ia_css_de_config   de_config;
	काष्ठा ia_css_gc_config   gc_config;
	काष्ठा ia_css_nr_config   nr_config;
	काष्ठा ia_css_ee_config   ee_config;
	काष्ठा ia_css_anr_config  anr_config;
	काष्ठा ia_css_3a_config   s3a_config;
	काष्ठा ia_css_xnr_config  xnr_config;
	काष्ठा ia_css_dz_config   dz_config;
	काष्ठा ia_css_cc_config yuv2rgb_cc_config;
	काष्ठा ia_css_cc_config rgb2yuv_cc_config;
	काष्ठा ia_css_macc_table  macc_table;
	काष्ठा ia_css_gamma_table gamma_table;
	काष्ठा ia_css_ctc_table   ctc_table;

	काष्ठा ia_css_xnr_table   xnr_table;
	काष्ठा ia_css_rgb_gamma_table r_gamma_table;
	काष्ठा ia_css_rgb_gamma_table g_gamma_table;
	काष्ठा ia_css_rgb_gamma_table b_gamma_table;

	काष्ठा ia_css_vector      motion_vector;
	काष्ठा ia_css_anr_thres   anr_thres;

	काष्ठा ia_css_dvs_6axis_config *dvs_6axis;
	काष्ठा ia_css_dvs2_coefficients *dvs2_coeff;
	काष्ठा ia_css_shading_table *shading_table;
	काष्ठा ia_css_morph_table   *morph_table;

	/*
	 * Used to store the user poपूर्णांकer address of the frame. driver needs to
	 * translate to ia_css_frame * and then set to CSS.
	 */
	व्योम		*output_frame;
	u32	isp_config_id;

	/* Indicates which parameters need to be updated. */
	काष्ठा atomisp_parameters update_flag;
पूर्ण;

काष्ठा atomisp_subdev_params अणु
	/* FIXME: Determines whether raw capture buffer are being passed to
	 * user space. Unimplemented क्रम now. */
	पूर्णांक online_process;
	पूर्णांक yuv_ds_en;
	अचिन्हित पूर्णांक color_effect;
	bool gdc_cac_en;
	bool macc_en;
	bool bad_pixel_en;
	bool video_dis_en;
	bool sc_en;
	bool fpn_en;
	bool xnr_en;
	bool low_light;
	पूर्णांक false_color;
	अचिन्हित पूर्णांक histogram_elक्रमागत;

	/* Current grid info */
	काष्ठा ia_css_grid_info curr_grid_info;
	क्रमागत ia_css_pipe_id s3a_enabled_pipe;

	पूर्णांक s3a_output_bytes;

	bool dis_proj_data_valid;

	काष्ठा ia_css_dz_config   dz_config;  /** Digital Zoom */
	काष्ठा ia_css_capture_config   capture_config;

	काष्ठा ia_css_isp_config config;

	/* current configurations */
	काष्ठा atomisp_css_params css_param;

	/*
	 * Intermediate buffers used to communicate data between
	 * CSS and user space.
	 */
	काष्ठा ia_css_3a_statistics *s3a_user_stat;

	व्योम *metadata_user[ATOMISP_METADATA_TYPE_NUM];
	u32 metadata_width_size;

	काष्ठा ia_css_dvs2_statistics *dvs_stat;
	काष्ठा ia_css_dvs_6axis_config *dvs_6axis;
	u32 exp_id;
	पूर्णांक  dvs_hor_coef_bytes;
	पूर्णांक  dvs_ver_coef_bytes;
	पूर्णांक  dvs_ver_proj_bytes;
	पूर्णांक  dvs_hor_proj_bytes;

	/* Flash */
	पूर्णांक num_flash_frames;
	क्रमागत atomisp_flash_state flash_state;
	क्रमागत atomisp_frame_status last_frame_status;

	/* continuous capture */
	काष्ठा atomisp_cont_capture_conf offline_parm;
	/* Flag to check अगर driver needs to update params to css */
	bool css_update_params_needed;
पूर्ण;

काष्ठा atomisp_css_params_with_list अणु
	/* parameters क्रम CSS */
	काष्ठा atomisp_css_params params;
	काष्ठा list_head list;
पूर्ण;

काष्ठा atomisp_acc_fw अणु
	काष्ठा ia_css_fw_info *fw;
	अचिन्हित पूर्णांक handle;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक type;
	काष्ठा अणु
		माप_प्रकार length;
		अचिन्हित दीर्घ css_ptr;
	पूर्ण args[ATOMISP_ACC_NR_MEMORY];
	काष्ठा list_head list;
पूर्ण;

काष्ठा atomisp_map अणु
	ia_css_ptr ptr;
	माप_प्रकार length;
	काष्ठा list_head list;
	/* FIXME: should keep book which maps are currently used
	 * by binaries and not allow releasing those
	 * which are in use. Implement by reference counting.
	 */
पूर्ण;

काष्ठा atomisp_sub_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[ATOMISP_SUBDEV_PADS_NUM];
	काष्ठा atomisp_pad_क्रमmat fmt[ATOMISP_SUBDEV_PADS_NUM];
	u16 capture_pad; /* मुख्य capture pad; defines much of isp config */

	क्रमागत atomisp_subdev_input_entity input;
	अचिन्हित पूर्णांक output;
	काष्ठा atomisp_video_pipe video_in;
	काष्ठा atomisp_video_pipe video_out_capture; /* capture output */
	काष्ठा atomisp_video_pipe video_out_vf;      /* viewfinder output */
	काष्ठा atomisp_video_pipe video_out_preview; /* preview output */
	काष्ठा atomisp_acc_pipe video_acc;
	/* video pipe मुख्य output */
	काष्ठा atomisp_video_pipe video_out_video_capture;
	/* काष्ठा isp_subdev_params params; */
	spinlock_t lock;
	काष्ठा atomisp_device *isp;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *fmt_स्वतः;
	काष्ठा v4l2_ctrl *run_mode;
	काष्ठा v4l2_ctrl *depth_mode;
	काष्ठा v4l2_ctrl *vfpp;
	काष्ठा v4l2_ctrl *continuous_mode;
	काष्ठा v4l2_ctrl *continuous_raw_buffer_size;
	काष्ठा v4l2_ctrl *continuous_viewfinder;
	काष्ठा v4l2_ctrl *enable_raw_buffer_lock;

	/* ISP2401 */
	काष्ठा v4l2_ctrl *ion_dev_fd;
	काष्ठा v4l2_ctrl *select_isp_version;

	काष्ठा v4l2_ctrl *disable_dz;

	काष्ठा अणु
		काष्ठा list_head fw;
		काष्ठा list_head memory_maps;
		काष्ठा ia_css_pipe *pipeline;
		bool extension_mode;
		काष्ठा ida ida;
		काष्ठा completion acc_करोne;
		व्योम *acc_stages;
	पूर्ण acc;

	काष्ठा atomisp_subdev_params params;

	काष्ठा atomisp_stream_env stream_env[ATOMISP_INPUT_STREAM_NUM];

	काष्ठा v4l2_pix_क्रमmat dvs_envelop;
	अचिन्हित पूर्णांक s3a_bufs_in_css[IA_CSS_PIPE_ID_NUM];
	अचिन्हित पूर्णांक dis_bufs_in_css;

	अचिन्हित पूर्णांक metadata_bufs_in_css
	[ATOMISP_INPUT_STREAM_NUM][IA_CSS_PIPE_ID_NUM];
	/* The list of मुक्त and available metadata buffers क्रम CSS */
	काष्ठा list_head metadata[ATOMISP_METADATA_TYPE_NUM];
	/* The list of metadata buffers which have been en-queued to CSS */
	काष्ठा list_head metadata_in_css[ATOMISP_METADATA_TYPE_NUM];
	/* The list of metadata buffers which are पढ़ोy क्रम userspace to get */
	काष्ठा list_head metadata_पढ़ोy[ATOMISP_METADATA_TYPE_NUM];

	/* The list of मुक्त and available s3a stat buffers क्रम CSS */
	काष्ठा list_head s3a_stats;
	/* The list of s3a stat buffers which have been en-queued to CSS */
	काष्ठा list_head s3a_stats_in_css;
	/* The list of s3a stat buffers which are पढ़ोy क्रम userspace to get */
	काष्ठा list_head s3a_stats_पढ़ोy;

	काष्ठा list_head dis_stats;
	काष्ठा list_head dis_stats_in_css;
	spinlock_t dis_stats_lock;

	काष्ठा ia_css_frame *vf_frame; /* TODO: needed? */
	काष्ठा ia_css_frame *raw_output_frame;
	क्रमागत atomisp_frame_status frame_status[VIDEO_MAX_FRAME];

	/* This field specअगरies which camera (v4l2 input) is selected. */
	पूर्णांक input_curr;
	/* This field specअगरies which sensor is being selected when there
	   are multiple sensors connected to the same MIPI port. */
	पूर्णांक sensor_curr;

	atomic_t sof_count;
	atomic_t sequence;      /* Sequence value that is asचिन्हित to buffer. */
	atomic_t sequence_temp;

	अचिन्हित पूर्णांक streaming; /* Hold both mutex and lock to change this */
	bool stream_prepared; /* whether css stream is created */

	/* subdev index: will be used to show which subdev is holding the
	 * resource, like which camera is used by which subdev
	 */
	अचिन्हित पूर्णांक index;

	/* delayed memory allocation क्रम css */
	काष्ठा completion init_करोne;
	काष्ठा workqueue_काष्ठा *delayed_init_workq;
	अचिन्हित पूर्णांक delayed_init;
	काष्ठा work_काष्ठा delayed_init_work;

	अचिन्हित पूर्णांक latest_preview_exp_id; /* CSS ZSL/SDV raw buffer id */

	अचिन्हित पूर्णांक mipi_frame_size;

	bool copy_mode; /* CSI2+ use copy mode */
	bool yuvpp_mode;	/* CSI2+ yuvpp pipe */

	पूर्णांक raw_buffer_biपंचांगap[ATOMISP_MAX_EXP_ID / 32 +
						 1]; /* Record each Raw Buffer lock status */
	पूर्णांक raw_buffer_locked_count;
	spinlock_t raw_buffer_biपंचांगap_lock;

	/* ISP 2400 */
	काष्ठा समयr_list wdt;
	अचिन्हित पूर्णांक wdt_duration;	/* in jअगरfies */
	अचिन्हित दीर्घ wdt_expires;

	/* ISP2401 */
	bool re_trigger_capture;

	काष्ठा atomisp_resolution sensor_array_res;
	bool high_speed_mode; /* Indicate whether now is a high speed mode */
	पूर्णांक pending_capture_request; /* Indicates the number of pending capture requests. */

	अचिन्हित पूर्णांक preview_exp_id;
	अचिन्हित पूर्णांक postview_exp_id;
पूर्ण;

बाह्य स्थिर काष्ठा atomisp_in_fmt_conv atomisp_in_fmt_conv[];

u32 atomisp_subdev_uncompressed_code(u32 code);
bool atomisp_subdev_is_compressed(u32 code);
स्थिर काष्ठा atomisp_in_fmt_conv *atomisp_find_in_fmt_conv(u32 code);

/* ISP2400 */
स्थिर काष्ठा atomisp_in_fmt_conv *atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
    क्रमागत atomisp_input_क्रमmat atomisp_in_fmt);

/* ISP2401 */
स्थिर काष्ठा atomisp_in_fmt_conv
*atomisp_find_in_fmt_conv_by_atomisp_in_fmt(क्रमागत atomisp_input_क्रमmat
	atomisp_in_fmt);

स्थिर काष्ठा atomisp_in_fmt_conv *atomisp_find_in_fmt_conv_compressed(u32 code);
bool atomisp_subdev_क्रमmat_conversion(काष्ठा atomisp_sub_device *asd,
				      अचिन्हित पूर्णांक source_pad);
uपूर्णांक16_t atomisp_subdev_source_pad(काष्ठा video_device *vdev);

/* Get poपूर्णांकer to appropriate क्रमmat */
काष्ठा v4l2_mbus_framefmt
*atomisp_subdev_get_ffmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_pad_config *cfg, uपूर्णांक32_t which,
			 uपूर्णांक32_t pad);
काष्ठा v4l2_rect *atomisp_subdev_get_rect(काष्ठा v4l2_subdev *sd,
	काष्ठा v4l2_subdev_pad_config *cfg,
	u32 which, uपूर्णांक32_t pad,
	uपूर्णांक32_t target);
पूर्णांक atomisp_subdev_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 u32 which, uपूर्णांक32_t pad, uपूर्णांक32_t target,
				 u32 flags, काष्ठा v4l2_rect *r);
/* Actually set the क्रमmat */
व्योम atomisp_subdev_set_ffmt(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg, uपूर्णांक32_t which,
			     u32 pad, काष्ठा v4l2_mbus_framefmt *ffmt);

पूर्णांक atomisp_update_run_mode(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_subdev_cleanup_pending_events(काष्ठा atomisp_sub_device *asd);

व्योम atomisp_subdev_unरेजिस्टर_entities(काष्ठा atomisp_sub_device *asd);
पूर्णांक atomisp_subdev_रेजिस्टर_entities(काष्ठा atomisp_sub_device *asd,
				     काष्ठा v4l2_device *vdev);
पूर्णांक atomisp_subdev_init(काष्ठा atomisp_device *isp);
व्योम atomisp_subdev_cleanup(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_create_pads_links(काष्ठा atomisp_device *isp);

#पूर्ण_अगर /* __ATOMISP_SUBDEV_H__ */
