<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-core.h - core dataकाष्ठाures
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_CORE_H_
#घोषणा _VIVID_CORE_H_

#समावेश <linux/fb.h>
#समावेश <linux/workqueue.h>
#समावेश <media/cec.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/tpg/v4l2-tpg.h>
#समावेश "vivid-rds-gen.h"
#समावेश "vivid-vbi-gen.h"

#घोषणा dprपूर्णांकk(dev, level, fmt, arg...) \
	v4l2_dbg(level, vivid_debug, &dev->v4l2_dev, fmt, ## arg)

/* The maximum number of clip rectangles */
#घोषणा MAX_CLIPS  16
/* The maximum number of inमाला_दो */
#घोषणा MAX_INPUTS 16
/* The maximum number of outमाला_दो */
#घोषणा MAX_OUTPUTS 16
/* The maximum up or करोwn scaling factor is 4 */
#घोषणा MAX_ZOOM  4
/* The maximum image width/height are set to 4K DMT */
#घोषणा MAX_WIDTH  4096
#घोषणा MAX_HEIGHT 2160
/* The minimum image width/height */
#घोषणा MIN_WIDTH  16
#घोषणा MIN_HEIGHT 16
/* The data_offset of plane 0 क्रम the multiplanar क्रमmats */
#घोषणा PLANE0_DATA_OFFSET 128

/* The supported TV frequency range in MHz */
#घोषणा MIN_TV_FREQ (44U * 16U)
#घोषणा MAX_TV_FREQ (958U * 16U)

/* The number of samples वापसed in every SDR buffer */
#घोषणा SDR_CAP_SAMPLES_PER_BUF 0x4000

/* used by the thपढ़ोs to know when to resync पूर्णांकernal counters */
#घोषणा JIFFIES_PER_DAY (3600U * 24U * HZ)
#घोषणा JIFFIES_RESYNC (JIFFIES_PER_DAY * (0xf0000000U / JIFFIES_PER_DAY))

बाह्य स्थिर काष्ठा v4l2_rect vivid_min_rect;
बाह्य स्थिर काष्ठा v4l2_rect vivid_max_rect;
बाह्य अचिन्हित vivid_debug;

काष्ठा vivid_fmt अणु
	u32	fourcc;          /* v4l2 क्रमmat id */
	क्रमागत	tgp_color_enc color_enc;
	bool	can_करो_overlay;
	u8	vकरोwnsampling[TPG_MAX_PLANES];
	u32	alpha_mask;
	u8	planes;
	u8	buffers;
	u32	data_offset[TPG_MAX_PLANES];
	u32	bit_depth[TPG_MAX_PLANES];
पूर्ण;

बाह्य काष्ठा vivid_fmt vivid_क्रमmats[];

/* buffer क्रम one video frame */
काष्ठा vivid_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head	list;
पूर्ण;

क्रमागत vivid_input अणु
	WEBCAM,
	TV,
	SVID,
	HDMI,
पूर्ण;

क्रमागत vivid_संकेत_mode अणु
	CURRENT_DV_TIMINGS,
	CURRENT_STD = CURRENT_DV_TIMINGS,
	NO_SIGNAL,
	NO_LOCK,
	OUT_OF_RANGE,
	SELECTED_DV_TIMINGS,
	SELECTED_STD = SELECTED_DV_TIMINGS,
	CYCLE_DV_TIMINGS,
	CYCLE_STD = CYCLE_DV_TIMINGS,
	CUSTOM_DV_TIMINGS,
पूर्ण;

क्रमागत vivid_colorspace अणु
	VIVID_CS_170M,
	VIVID_CS_709,
	VIVID_CS_SRGB,
	VIVID_CS_OPRGB,
	VIVID_CS_2020,
	VIVID_CS_DCI_P3,
	VIVID_CS_240M,
	VIVID_CS_SYS_M,
	VIVID_CS_SYS_BG,
पूर्ण;

#घोषणा VIVID_INVALID_SIGNAL(mode) \
	((mode) == NO_SIGNAL || (mode) == NO_LOCK || (mode) == OUT_OF_RANGE)

काष्ठा vivid_cec_work अणु
	काष्ठा list_head	list;
	काष्ठा delayed_work	work;
	काष्ठा cec_adapter	*adap;
	काष्ठा vivid_dev	*dev;
	अचिन्हित पूर्णांक		usecs;
	अचिन्हित पूर्णांक		समयout_ms;
	u8			tx_status;
	काष्ठा cec_msg		msg;
पूर्ण;

काष्ठा vivid_dev अणु
	अचिन्हित			inst;
	काष्ठा v4l2_device		v4l2_dev;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device		mdev;
	काष्ठा media_pad		vid_cap_pad;
	काष्ठा media_pad		vid_out_pad;
	काष्ठा media_pad		vbi_cap_pad;
	काष्ठा media_pad		vbi_out_pad;
	काष्ठा media_pad		sdr_cap_pad;
	काष्ठा media_pad		meta_cap_pad;
	काष्ठा media_pad		meta_out_pad;
	काष्ठा media_pad		touch_cap_pad;
#पूर्ण_अगर
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_user_gen;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_user_vid;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_user_aud;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_streaming;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_sdtv_cap;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_loop_cap;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_fb;
	काष्ठा video_device		vid_cap_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_vid_cap;
	काष्ठा video_device		vid_out_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_vid_out;
	काष्ठा video_device		vbi_cap_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_vbi_cap;
	काष्ठा video_device		vbi_out_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_vbi_out;
	काष्ठा video_device		radio_rx_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_radio_rx;
	काष्ठा video_device		radio_tx_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_radio_tx;
	काष्ठा video_device		sdr_cap_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_sdr_cap;
	काष्ठा video_device		meta_cap_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_meta_cap;
	काष्ठा video_device		meta_out_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_meta_out;
	काष्ठा video_device		touch_cap_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_hdl_touch_cap;

	spinlock_t			slock;
	काष्ठा mutex			mutex;

	/* capabilities */
	u32				vid_cap_caps;
	u32				vid_out_caps;
	u32				vbi_cap_caps;
	u32				vbi_out_caps;
	u32				sdr_cap_caps;
	u32				radio_rx_caps;
	u32				radio_tx_caps;
	u32				meta_cap_caps;
	u32				meta_out_caps;
	u32				touch_cap_caps;

	/* supported features */
	bool				multiplanar;
	अचिन्हित			num_inमाला_दो;
	अचिन्हित पूर्णांक			num_hdmi_inमाला_दो;
	u8				input_type[MAX_INPUTS];
	u8				input_name_counter[MAX_INPUTS];
	अचिन्हित			num_outमाला_दो;
	अचिन्हित पूर्णांक			num_hdmi_outमाला_दो;
	u8				output_type[MAX_OUTPUTS];
	u8				output_name_counter[MAX_OUTPUTS];
	bool				has_audio_inमाला_दो;
	bool				has_audio_outमाला_दो;
	bool				has_vid_cap;
	bool				has_vid_out;
	bool				has_vbi_cap;
	bool				has_raw_vbi_cap;
	bool				has_sliced_vbi_cap;
	bool				has_vbi_out;
	bool				has_raw_vbi_out;
	bool				has_sliced_vbi_out;
	bool				has_radio_rx;
	bool				has_radio_tx;
	bool				has_sdr_cap;
	bool				has_fb;
	bool				has_meta_cap;
	bool				has_meta_out;
	bool				has_tv_tuner;
	bool				has_touch_cap;

	bool				can_loop_video;

	/* controls */
	काष्ठा v4l2_ctrl		*brightness;
	काष्ठा v4l2_ctrl		*contrast;
	काष्ठा v4l2_ctrl		*saturation;
	काष्ठा v4l2_ctrl		*hue;
	काष्ठा अणु
		/* स्वतःgain/gain cluster */
		काष्ठा v4l2_ctrl	*स्वतःgain;
		काष्ठा v4l2_ctrl	*gain;
	पूर्ण;
	काष्ठा v4l2_ctrl		*volume;
	काष्ठा v4l2_ctrl		*mute;
	काष्ठा v4l2_ctrl		*alpha;
	काष्ठा v4l2_ctrl		*button;
	काष्ठा v4l2_ctrl		*boolean;
	काष्ठा v4l2_ctrl		*पूर्णांक32;
	काष्ठा v4l2_ctrl		*पूर्णांक64;
	काष्ठा v4l2_ctrl		*menu;
	काष्ठा v4l2_ctrl		*string;
	काष्ठा v4l2_ctrl		*biपंचांगask;
	काष्ठा v4l2_ctrl		*पूर्णांक_menu;
	काष्ठा v4l2_ctrl		*ro_पूर्णांक32;
	काष्ठा v4l2_ctrl		*test_pattern;
	काष्ठा v4l2_ctrl		*colorspace;
	काष्ठा v4l2_ctrl		*rgb_range_cap;
	काष्ठा v4l2_ctrl		*real_rgb_range_cap;
	काष्ठा अणु
		/* std_संकेत_mode/standard cluster */
		काष्ठा v4l2_ctrl	*ctrl_std_संकेत_mode;
		काष्ठा v4l2_ctrl	*ctrl_standard;
	पूर्ण;
	काष्ठा अणु
		/* dv_timings_संकेत_mode/timings cluster */
		काष्ठा v4l2_ctrl	*ctrl_dv_timings_संकेत_mode;
		काष्ठा v4l2_ctrl	*ctrl_dv_timings;
	पूर्ण;
	काष्ठा v4l2_ctrl		*ctrl_display_present;
	काष्ठा v4l2_ctrl		*ctrl_has_crop_cap;
	काष्ठा v4l2_ctrl		*ctrl_has_compose_cap;
	काष्ठा v4l2_ctrl		*ctrl_has_scaler_cap;
	काष्ठा v4l2_ctrl		*ctrl_has_crop_out;
	काष्ठा v4l2_ctrl		*ctrl_has_compose_out;
	काष्ठा v4l2_ctrl		*ctrl_has_scaler_out;
	काष्ठा v4l2_ctrl		*ctrl_tx_mode;
	काष्ठा v4l2_ctrl		*ctrl_tx_rgb_range;
	काष्ठा v4l2_ctrl		*ctrl_tx_edid_present;
	काष्ठा v4l2_ctrl		*ctrl_tx_hotplug;
	काष्ठा v4l2_ctrl		*ctrl_tx_rxsense;

	काष्ठा v4l2_ctrl		*ctrl_rx_घातer_present;

	काष्ठा v4l2_ctrl		*radio_tx_rds_pi;
	काष्ठा v4l2_ctrl		*radio_tx_rds_pty;
	काष्ठा v4l2_ctrl		*radio_tx_rds_mono_stereo;
	काष्ठा v4l2_ctrl		*radio_tx_rds_art_head;
	काष्ठा v4l2_ctrl		*radio_tx_rds_compressed;
	काष्ठा v4l2_ctrl		*radio_tx_rds_dyn_pty;
	काष्ठा v4l2_ctrl		*radio_tx_rds_ta;
	काष्ठा v4l2_ctrl		*radio_tx_rds_tp;
	काष्ठा v4l2_ctrl		*radio_tx_rds_ms;
	काष्ठा v4l2_ctrl		*radio_tx_rds_psname;
	काष्ठा v4l2_ctrl		*radio_tx_rds_radiotext;

	काष्ठा v4l2_ctrl		*radio_rx_rds_pty;
	काष्ठा v4l2_ctrl		*radio_rx_rds_ta;
	काष्ठा v4l2_ctrl		*radio_rx_rds_tp;
	काष्ठा v4l2_ctrl		*radio_rx_rds_ms;
	काष्ठा v4l2_ctrl		*radio_rx_rds_psname;
	काष्ठा v4l2_ctrl		*radio_rx_rds_radiotext;

	अचिन्हित			input_brightness[MAX_INPUTS];
	अचिन्हित			osd_mode;
	अचिन्हित			button_pressed;
	bool				sensor_hflip;
	bool				sensor_vflip;
	bool				hflip;
	bool				vflip;
	bool				vbi_cap_पूर्णांकerlaced;
	bool				loop_video;
	bool				reduced_fps;

	/* Framebuffer */
	अचिन्हित दीर्घ			video_pbase;
	व्योम				*video_vbase;
	u32				video_buffer_size;
	पूर्णांक				display_width;
	पूर्णांक				display_height;
	पूर्णांक				display_byte_stride;
	पूर्णांक				bits_per_pixel;
	पूर्णांक				bytes_per_pixel;
	काष्ठा fb_info			fb_info;
	काष्ठा fb_var_screeninfo	fb_defined;
	काष्ठा fb_fix_screeninfo	fb_fix;

	/* Error injection */
	bool				disconnect_error;
	bool				queue_setup_error;
	bool				buf_prepare_error;
	bool				start_streaming_error;
	bool				dqbuf_error;
	bool				req_validate_error;
	bool				seq_wrap;
	bool				समय_wrap;
	u64				समय_wrap_offset;
	अचिन्हित			perc_dropped_buffers;
	क्रमागत vivid_संकेत_mode		std_संकेत_mode[MAX_INPUTS];
	अचिन्हित पूर्णांक			query_std_last[MAX_INPUTS];
	v4l2_std_id			query_std[MAX_INPUTS];
	क्रमागत tpg_video_aspect		std_aspect_ratio[MAX_INPUTS];

	क्रमागत vivid_संकेत_mode		dv_timings_संकेत_mode[MAX_INPUTS];
	अक्षर				**query_dv_timings_qmenu;
	अक्षर				*query_dv_timings_qmenu_strings;
	अचिन्हित			query_dv_timings_size;
	अचिन्हित पूर्णांक			query_dv_timings_last[MAX_INPUTS];
	अचिन्हित पूर्णांक			query_dv_timings[MAX_INPUTS];
	क्रमागत tpg_video_aspect		dv_timings_aspect_ratio[MAX_INPUTS];

	/* Input */
	अचिन्हित			input;
	v4l2_std_id			std_cap[MAX_INPUTS];
	काष्ठा v4l2_dv_timings		dv_timings_cap[MAX_INPUTS];
	पूर्णांक				dv_timings_cap_sel[MAX_INPUTS];
	u32				service_set_cap;
	काष्ठा vivid_vbi_gen_data	vbi_gen;
	u8				*edid;
	अचिन्हित			edid_blocks;
	अचिन्हित			edid_max_blocks;
	अचिन्हित			webcam_size_idx;
	अचिन्हित			webcam_ival_idx;
	अचिन्हित			tv_freq;
	अचिन्हित			tv_audmode;
	अचिन्हित			tv_field_cap;
	अचिन्हित			tv_audio_input;

	u32				घातer_present;

	/* Capture Overlay */
	काष्ठा v4l2_framebuffer		fb_cap;
	काष्ठा v4l2_fh			*overlay_cap_owner;
	व्योम				*fb_vbase_cap;
	पूर्णांक				overlay_cap_top, overlay_cap_left;
	क्रमागत v4l2_field			overlay_cap_field;
	व्योम				*biपंचांगap_cap;
	काष्ठा v4l2_clip		clips_cap[MAX_CLIPS];
	काष्ठा v4l2_clip		try_clips_cap[MAX_CLIPS];
	अचिन्हित			clipcount_cap;

	/* Output */
	अचिन्हित			output;
	v4l2_std_id			std_out;
	काष्ठा v4l2_dv_timings		dv_timings_out;
	u32				colorspace_out;
	u32				ycbcr_enc_out;
	u32				hsv_enc_out;
	u32				quantization_out;
	u32				xfer_func_out;
	u32				service_set_out;
	अचिन्हित			bytesperline_out[TPG_MAX_PLANES];
	अचिन्हित			tv_field_out;
	अचिन्हित			tv_audio_output;
	bool				vbi_out_have_wss;
	u8				vbi_out_wss[2];
	bool				vbi_out_have_cc[2];
	u8				vbi_out_cc[2][2];
	bool				dvi_d_out;
	u8				*scaled_line;
	u8				*blended_line;
	अचिन्हित			cur_scaled_line;
	bool				display_present[MAX_OUTPUTS];

	/* Output Overlay */
	व्योम				*fb_vbase_out;
	bool				overlay_out_enabled;
	पूर्णांक				overlay_out_top, overlay_out_left;
	व्योम				*biपंचांगap_out;
	काष्ठा v4l2_clip		clips_out[MAX_CLIPS];
	काष्ठा v4l2_clip		try_clips_out[MAX_CLIPS];
	अचिन्हित			clipcount_out;
	अचिन्हित			fbuf_out_flags;
	u32				chromakey_out;
	u8				global_alpha_out;

	/* video capture */
	काष्ठा tpg_data			tpg;
	अचिन्हित			ms_vid_cap;
	bool				must_blank[VIDEO_MAX_FRAME];

	स्थिर काष्ठा vivid_fmt		*fmt_cap;
	काष्ठा v4l2_fract		समयperframe_vid_cap;
	क्रमागत v4l2_field			field_cap;
	काष्ठा v4l2_rect		src_rect;
	काष्ठा v4l2_rect		fmt_cap_rect;
	काष्ठा v4l2_rect		crop_cap;
	काष्ठा v4l2_rect		compose_cap;
	काष्ठा v4l2_rect		crop_bounds_cap;
	काष्ठा vb2_queue		vb_vid_cap_q;
	काष्ठा list_head		vid_cap_active;
	काष्ठा vb2_queue		vb_vbi_cap_q;
	काष्ठा list_head		vbi_cap_active;
	काष्ठा vb2_queue		vb_meta_cap_q;
	काष्ठा list_head		meta_cap_active;
	काष्ठा vb2_queue		vb_touch_cap_q;
	काष्ठा list_head		touch_cap_active;

	/* thपढ़ो क्रम generating video capture stream */
	काष्ठा task_काष्ठा		*kthपढ़ो_vid_cap;
	अचिन्हित दीर्घ			jअगरfies_vid_cap;
	u64				cap_stream_start;
	u64				cap_frame_period;
	u64				cap_frame_eof_offset;
	u32				cap_seq_offset;
	u32				cap_seq_count;
	bool				cap_seq_resync;
	u32				vid_cap_seq_start;
	u32				vid_cap_seq_count;
	bool				vid_cap_streaming;
	u32				vbi_cap_seq_start;
	u32				vbi_cap_seq_count;
	bool				vbi_cap_streaming;
	bool				stream_sliced_vbi_cap;
	u32				meta_cap_seq_start;
	u32				meta_cap_seq_count;
	bool				meta_cap_streaming;

	/* Touch capture */
	काष्ठा task_काष्ठा		*kthपढ़ो_touch_cap;
	अचिन्हित दीर्घ			jअगरfies_touch_cap;
	u64				touch_cap_stream_start;
	u32				touch_cap_seq_offset;
	bool				touch_cap_seq_resync;
	u32				touch_cap_seq_start;
	u32				touch_cap_seq_count;
	bool				touch_cap_streaming;
	काष्ठा v4l2_fract		समयperframe_tch_cap;
	काष्ठा v4l2_pix_क्रमmat		tch_क्रमmat;
	पूर्णांक				tch_pat_अक्रमom;

	/* video output */
	स्थिर काष्ठा vivid_fmt		*fmt_out;
	काष्ठा v4l2_fract		समयperframe_vid_out;
	क्रमागत v4l2_field			field_out;
	काष्ठा v4l2_rect		sink_rect;
	काष्ठा v4l2_rect		fmt_out_rect;
	काष्ठा v4l2_rect		crop_out;
	काष्ठा v4l2_rect		compose_out;
	काष्ठा v4l2_rect		compose_bounds_out;
	काष्ठा vb2_queue		vb_vid_out_q;
	काष्ठा list_head		vid_out_active;
	काष्ठा vb2_queue		vb_vbi_out_q;
	काष्ठा list_head		vbi_out_active;
	काष्ठा vb2_queue		vb_meta_out_q;
	काष्ठा list_head		meta_out_active;

	/* video loop precalculated rectangles */

	/*
	 * Intersection between what the output side composes and the capture side
	 * crops. I.e., what actually needs to be copied from the output buffer to
	 * the capture buffer.
	 */
	काष्ठा v4l2_rect		loop_vid_copy;
	/* The part of the output buffer that (after scaling) corresponds to loop_vid_copy. */
	काष्ठा v4l2_rect		loop_vid_out;
	/* The part of the capture buffer that (after scaling) corresponds to loop_vid_copy. */
	काष्ठा v4l2_rect		loop_vid_cap;
	/*
	 * The पूर्णांकersection of the framebuffer, the overlay output winकरोw and
	 * loop_vid_copy. I.e., the part of the framebuffer that actually should be
	 * blended with the compose_out rectangle. This uses the framebuffer origin.
	 */
	काष्ठा v4l2_rect		loop_fb_copy;
	/* The same as loop_fb_copy but with compose_out origin. */
	काष्ठा v4l2_rect		loop_vid_overlay;
	/*
	 * The part of the capture buffer that (after scaling) corresponds
	 * to loop_vid_overlay.
	 */
	काष्ठा v4l2_rect		loop_vid_overlay_cap;

	/* thपढ़ो क्रम generating video output stream */
	काष्ठा task_काष्ठा		*kthपढ़ो_vid_out;
	अचिन्हित दीर्घ			jअगरfies_vid_out;
	u32				out_seq_offset;
	u32				out_seq_count;
	bool				out_seq_resync;
	u32				vid_out_seq_start;
	u32				vid_out_seq_count;
	bool				vid_out_streaming;
	u32				vbi_out_seq_start;
	u32				vbi_out_seq_count;
	bool				vbi_out_streaming;
	bool				stream_sliced_vbi_out;
	u32				meta_out_seq_start;
	u32				meta_out_seq_count;
	bool				meta_out_streaming;

	/* SDR capture */
	काष्ठा vb2_queue		vb_sdr_cap_q;
	काष्ठा list_head		sdr_cap_active;
	u32				sdr_pixelक्रमmat; /* v4l2 क्रमmat id */
	अचिन्हित			sdr_buffersize;
	अचिन्हित			sdr_adc_freq;
	अचिन्हित			sdr_fm_freq;
	अचिन्हित			sdr_fm_deviation;
	पूर्णांक				sdr_fixp_src_phase;
	पूर्णांक				sdr_fixp_mod_phase;

	bool				tstamp_src_is_soe;
	bool				has_crop_cap;
	bool				has_compose_cap;
	bool				has_scaler_cap;
	bool				has_crop_out;
	bool				has_compose_out;
	bool				has_scaler_out;

	/* thपढ़ो क्रम generating SDR stream */
	काष्ठा task_काष्ठा		*kthपढ़ो_sdr_cap;
	अचिन्हित दीर्घ			jअगरfies_sdr_cap;
	u32				sdr_cap_seq_offset;
	u32				sdr_cap_seq_count;
	bool				sdr_cap_seq_resync;

	/* RDS generator */
	काष्ठा vivid_rds_gen		rds_gen;

	/* Radio receiver */
	अचिन्हित			radio_rx_freq;
	अचिन्हित			radio_rx_audmode;
	पूर्णांक				radio_rx_sig_qual;
	अचिन्हित			radio_rx_hw_seek_mode;
	bool				radio_rx_hw_seek_prog_lim;
	bool				radio_rx_rds_controls;
	bool				radio_rx_rds_enabled;
	अचिन्हित			radio_rx_rds_use_alternates;
	अचिन्हित			radio_rx_rds_last_block;
	काष्ठा v4l2_fh			*radio_rx_rds_owner;

	/* Radio transmitter */
	अचिन्हित			radio_tx_freq;
	अचिन्हित			radio_tx_subchans;
	bool				radio_tx_rds_controls;
	अचिन्हित			radio_tx_rds_last_block;
	काष्ठा v4l2_fh			*radio_tx_rds_owner;

	/* Shared between radio receiver and transmitter */
	bool				radio_rds_loop;
	kसमय_प्रकार				radio_rds_init_समय;

	/* CEC */
	काष्ठा cec_adapter		*cec_rx_adap;
	काष्ठा cec_adapter		*cec_tx_adap[MAX_OUTPUTS];
	काष्ठा workqueue_काष्ठा		*cec_workqueue;
	spinlock_t			cec_slock;
	काष्ठा list_head		cec_work_list;
	अचिन्हित पूर्णांक			cec_xfer_समय_jअगरfies;
	अचिन्हित दीर्घ			cec_xfer_start_jअगरfies;
	u8				cec_output2bus_map[MAX_OUTPUTS];

	/* CEC OSD String */
	अक्षर				osd[14];
	अचिन्हित दीर्घ			osd_jअगरfies;

	bool				meta_pts;
	bool				meta_scr;
पूर्ण;

अटल अंतरभूत bool vivid_is_webcam(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->input_type[dev->input] == WEBCAM;
पूर्ण

अटल अंतरभूत bool vivid_is_tv_cap(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->input_type[dev->input] == TV;
पूर्ण

अटल अंतरभूत bool vivid_is_svid_cap(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->input_type[dev->input] == SVID;
पूर्ण

अटल अंतरभूत bool vivid_is_hdmi_cap(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->input_type[dev->input] == HDMI;
पूर्ण

अटल अंतरभूत bool vivid_is_sdtv_cap(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस vivid_is_tv_cap(dev) || vivid_is_svid_cap(dev);
पूर्ण

अटल अंतरभूत bool vivid_is_svid_out(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->output_type[dev->output] == SVID;
पूर्ण

अटल अंतरभूत bool vivid_is_hdmi_out(स्थिर काष्ठा vivid_dev *dev)
अणु
	वापस dev->output_type[dev->output] == HDMI;
पूर्ण

#पूर्ण_अगर
